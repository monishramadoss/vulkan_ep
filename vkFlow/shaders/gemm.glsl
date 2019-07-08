#version 460
#define WIDTH 4u                     // The vector-width (in number of floats)
#define TSM 128u                     // The tile-size in dimension M
#define TSN 128u                     // The tile-size in dimension N
#define TSK 16u                      // The tile-size in dimension K
#define WPTM 8u                      // The amount of work-per-thread in dimension M
#define WPTN 8u                      // The amount of work-per-thread in dimension N
#define LPTA ((TSK*WPTM*WPTN)/(TSN)) // The amount of loads-per-thread for A
#define LPTB ((TSK*WPTM*WPTN)/(TSM)) // The amount of loads-per-thread for B
#define RTSM 16u    // The reduced tile-size in dimension M (TSM/WPTM number of threads)
#define RTSN 16u    // The reduced tile-size in dimension N (TSN/WPTN number of threads)
#define MOD2(x,y) ((x) % (y))
#define DIV2(x,y) ((x) / (y))

layout (local_size_x = RTSM, local_size_y = RTSN, local_size_z = 1) in;
layout (std430, binding = 0)  buffer ssbA {
  vec4 A[];
};
layout (std430, binding = 1)  buffer ssbB {
  vec4 B[];
};
layout (std430, binding = 2)  buffer ssbC {
  float C[];
};
  uniform uvec3 MNK;
  shared float Asub[TSK][TSM];    // Local memory to fit a tile of A and B
  shared float Bsub[TSK][TSN];
void main() {
    uint M = MNK.x, N = MNK.y, K = MNK.z;

    // Thread identifiers
    uint tidm = gl_LocalInvocationID.x; // Local row ID (max: TSM/WPTM == RTSM)
    uint tidn = gl_LocalInvocationID.y; // Local col ID (max: TSN/WPTN == RTSN)
    uint offsetM = TSM*gl_WorkGroupID.x; // Work-group offset
    uint offsetN = TSN*gl_WorkGroupID.y; // Work-group offset

    // Allocate register space
    float Areg;
    float Breg[WPTN];
    float acc[WPTM][WPTN];

    // Initialise the accumulation registers
    for (uint wm=0u; wm < WPTM; wm++) {
        for (uint wn=0u; wn < WPTN; wn++) {
            acc[wm][wn] = 0.0;
        }
    }
    // Loop over all tiles
    uint numTiles = K/TSK;
    uint t=0u;
    do {
        // Load one tile of A and B into local memory
        for (uint la=0u; la < LPTA/WIDTH; la++) {
            uint tid = tidn*RTSM + tidm;
            uint id = la*RTSN*RTSM + tid;
            uint row = MOD2(id,TSM/WIDTH);
            uint col = DIV2(id,TSM/WIDTH);

            // Load the values (wide vector load)
            uint tiledIndex = TSK*t + col;
            vec4 vecA = A[tiledIndex*(M/WIDTH) + offsetM/WIDTH + row];
            vec4 vecB = B[tiledIndex*(N/WIDTH) + offsetN/WIDTH + row];

            // Store the loaded vectors into local memory
            Asub[col][WIDTH*row + 0u] = vecA.x;
            Asub[col][WIDTH*row + 1u] = vecA.y;
            Asub[col][WIDTH*row + 2u] = vecA.z;
            Asub[col][WIDTH*row + 3u] = vecA.w;
            Bsub[col][WIDTH*row + 0u] = vecB.x;
            Bsub[col][WIDTH*row + 1u] = vecB.y;
            Bsub[col][WIDTH*row + 2u] = vecB.z;
            Bsub[col][WIDTH*row + 3u] = vecB.w;
        }
        // Synchronise to make sure the tile is loaded
        barrier();

        // Loop over the values of a single tile
        for (uint k=0u; k < TSK; k++) {

            // Cache the values of Bsub in registers
            for (uint wn=0u; wn < WPTN; wn++) {
                uint col = tidn + wn*RTSN;
                Breg[wn] = Bsub[k][col];
            }

            // Perform the computation
            for (uint wm=0u; wm < WPTM; wm++) {
                uint row = tidm + wm*RTSM;
                Areg = Asub[k][row];
                for (uint wn=0u; wn < WPTN; wn++) {
                    acc[wm][wn] += Areg * Breg[wn];
                }
            }
        }
        // Synchronise before loading the next tile
        barrier();

        // Next tile
        t++;
    } while (t < numTiles);

    // Store the final result in C
    for (uint wm=0u; wm < WPTM; wm++) {
        uint globalRow = offsetM + tidm + wm*RTSM;
        for (uint wn=0u; wn < WPTN; wn++) {
            uint globalCol = offsetN + tidn + wn*RTSN;
            C[globalCol*M + globalRow] = acc[wm][wn];
        }
    }
}
