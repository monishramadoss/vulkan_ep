#include "priorbox.h"
#include <algorithm>
#include <math.h>
namespace backend {
	namespace CPU {
		PriorBox::PriorBox() {
			one_blob_only = false;
			support_inplace = false;
		}

		int PriorBox::forward(const std::vector<Mat>& bottom_blobs, std::vector<Mat>& top_blobs, const Option& opt) const {
			int w = bottom_blobs[0].w;
			int h = bottom_blobs[0].h;

			if (bottom_blobs.size() == 1 && image_width == -233 && image_height == -233 && max_sizes.empty()) {
				// mxnet style _contrib_MultiBoxPrior
				float step_w = step_width;
				float step_h = step_height;
				if (step_w == -233)
					step_w = 1.f / (float)w;
				if (step_h == -233)
					step_h = 1.f / (float)h;

				int num_sizes = min_sizes.w;
				int num_ratios = aspect_ratios.w;

				int num_prior = num_sizes - 1 + num_ratios;

				Mat& top_blob = top_blobs[0];
				top_blob.create(4 * w * h * num_prior, 4u, opt.blob_allocator);
				if (top_blob.empty())
					return -100;

#pragma omp parallel for num_threads(opt.num_threads)
				for (int i = 0; i < h; i++)	{
					float* box = (float*)top_blob + i * w * num_prior * 4;
					float center_x = offset * step_w;
					float center_y = offset * step_h + i * step_h;

					for (int j = 0; j < w; j++)	{
						for (int k = 0; k < num_sizes; k++) {
							float size = min_sizes[k];
							float cw = size * h / w / 2;
							float ch = size / 2;
							box[0] = center_x - cw;
							box[1] = center_y - ch;
							box[2] = center_x + cw;
							box[3] = center_y + ch;
							box += 4;
						}

						float size = min_sizes[0];
						for (int p = 1; p < num_ratios; p++) {
							float ratio = sqrt(aspect_ratios[p]);
							float cw = size * h / w * ratio / 2;
							float ch = size / ratio / 2;
							box[0] = center_x - cw;
							box[1] = center_y - ch;
							box[2] = center_x + cw;
							box[3] = center_y + ch;
							box += 4;
						}

						center_x += step_w;
					}
				}

				if (clip) {
					float* box = top_blob;
					for (int i = 0; i < top_blob.w; i++)
						box[i] = std::min<float>(std::max<float>(box[i], 0.f), 1.f);
				}

				return 0;
			}

			int image_w = image_width;
			int image_h = image_height;
			if (image_w == -233)
				image_w = bottom_blobs[1].w;
			if (image_h == -233)
				image_h = bottom_blobs[1].h;

			float step_w = step_width;
			float step_h = step_height;
			if (step_w == -233)
				step_w = (float)image_w / w;
			if (step_h == -233)
				step_h = (float)image_h / h;

			int num_min_size = min_sizes.w;
			int num_max_size = max_sizes.w;
			int num_aspect_ratio = aspect_ratios.w;

			int num_prior = num_min_size * num_aspect_ratio + num_min_size + num_max_size;
			if (flip)
				num_prior += num_min_size * num_aspect_ratio;

			Mat& top_blob = top_blobs[0];
			top_blob.create(4 * w * h * num_prior, 2, 4u, opt.blob_allocator);
			if (top_blob.empty())
				return -100;

#pragma omp parallel for num_threads(opt.num_threads)
			for (int i = 0; i < h; i++) {
				float* box = (float*)top_blob + i * w * num_prior * 4;
				float center_x = offset * step_w;
				float center_y = offset * step_h + i * step_h;

				for (int j = 0; j < w; j++)	{
					float box_w;
					float box_h;

					for (int k = 0; k < num_min_size; k++)	{
						float min_size = min_sizes[k];
						box_w = box_h = min_size;
						box[0] = (center_x - box_w * 0.5f) / image_w;
						box[1] = (center_y - box_h * 0.5f) / image_h;
						box[2] = (center_x + box_w * 0.5f) / image_w;
						box[3] = (center_y + box_h * 0.5f) / image_h;
						box += 4;

						if (num_max_size > 0) {
							float max_size = max_sizes[k];
							box_w = box_h = sqrt(min_size * max_size);
							box[0] = (center_x - box_w * 0.5f) / image_w;
							box[1] = (center_y - box_h * 0.5f) / image_h;
							box[2] = (center_x + box_w * 0.5f) / image_w;
							box[3] = (center_y + box_h * 0.5f) / image_h;
							box += 4;
						}

						for (int p = 0; p < num_aspect_ratio; p++) {
							float ar = aspect_ratios[p];
							box_w = min_size * sqrt(ar);
							box_h = min_size / sqrt(ar);
							box[0] = (center_x - box_w * 0.5f) / image_w;
							box[1] = (center_y - box_h * 0.5f) / image_h;
							box[2] = (center_x + box_w * 0.5f) / image_w;
							box[3] = (center_y + box_h * 0.5f) / image_h;
							box += 4;

							if (flip) {
								box[0] = (center_x - box_h * 0.5f) / image_w;
								box[1] = (center_y - box_w * 0.5f) / image_h;
								box[2] = (center_x + box_h * 0.5f) / image_w;
								box[3] = (center_y + box_w * 0.5f) / image_h;
								box += 4;
							}
						}
					}

					center_x += step_w;
				}
			}

			if (clip) {
				float* box = top_blob;
				for (int i = 0; i < top_blob.w; i++) {
					box[i] = std::min<float>(std::max<float>(box[i], 0.f), 1.f);
				}
			}

			// set variance
			float* var = top_blob.row(1);
			for (int i = 0; i < top_blob.w / 4; i++) {
				var[0] = variances[0];
				var[1] = variances[1];
				var[2] = variances[2];
				var[3] = variances[3];
				var += 4;
			}

			return 0;
		}

	}
	namespace GPU {

	}
}