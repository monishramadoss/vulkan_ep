LSTM=Shape_t X_in_t;, Shape_t W_in_t;, Shape_t R_in_t;, Shape_t B_in_t;, Shape_t sequence_lens_in_t;, Shape_t initial_h_in_t;, Shape_t initial_c_in_t;, Shape_t P_in_t;, Shape_t Y_out_t;, Shape_t Y_h_out_t;, Shape_t Y_c_out_t;, int* activations_t;, float clip_t;, int direction_t;, int hidden_size_t;, int input_forget_t;
Identity=Shape_t input_in_t;, Shape_t output_out_t;
Abs=Shape_t X_in_t;, Shape_t Y_out_t;
BatchNormalization=Shape_t X_in_t;, Shape_t scale_in_t;, Shape_t B_in_t;, Shape_t mean_in_t;, Shape_t var_in_t;, Shape_t Y_out_t;, Shape_t mean_out_t;, Shape_t var_out_t;, Shape_t saved_mean_out_t;, Shape_t saved_var_out_t;, float epsilon_t;, float momentum_t;
Mean=Shape_t data_0_in_t;, Shape_t mean_out_t;
Add=Shape_t A_in_t;, Shape_t B_in_t;, Shape_t C_out_t;
GlobalMaxPool=Shape_t X_in_t;, Shape_t Y_out_t;
Cast=Shape_t input_in_t;, Shape_t output_out_t;, int to_t;
AveragePool=Shape_t X_in_t;, Shape_t Y_out_t;, int auto_pad_t;, int ceil_mode_t;, int count_include_pad_t;, Shape_t kernel_shape_t;, Shape_t pads_t;, Shape_t strides_t;
And=Shape_t A_in_t;, Shape_t B_in_t;, Shape_t C_out_t;
LRN=Shape_t X_in_t;, Shape_t Y_out_t;, float alpha_t;, float beta_t;, float bias_t;, int size_t;
ArgMax=Shape_t data_in_t;, Shape_t reduced_out_t;, int axis_t;, int keepdims_t;
Resize=Shape_t X_in_t;, Shape_t scales_in_t;, Shape_t Y_out_t;, int mode_t;
Expand=Shape_t input_in_t;, Shape_t shape_in_t;, Shape_t output_out_t;
Neg=Shape_t X_in_t;, Shape_t Y_out_t;
Mul=Shape_t A_in_t;, Shape_t B_in_t;, Shape_t C_out_t;
ArgMin=Shape_t data_in_t;, Shape_t reduced_out_t;, int axis_t;, int keepdims_t;
CastMap=Shape_t X_in_t;, Shape_t Y_out_t;, int cast_to_t;, int map_form_t;, int max_map_t;
Exp=Shape_t input_in_t;, Shape_t output_out_t;
Div=Shape_t A_in_t;, Shape_t B_in_t;, Shape_t C_out_t;
ReverseSequence=Shape_t input_in_t;, Shape_t sequence_lens_in_t;, Shape_t Y_out_t;, int batch_axis_t;, int time_axis_t;
Ceil=Shape_t X_in_t;, Shape_t Y_out_t;
DepthToSpace=Shape_t input_in_t;, Shape_t output_out_t;, int blocksize_t;
Clip=Shape_t input_in_t;, Shape_t output_out_t;, float max_t;, float min_t;
RNN=Shape_t X_in_t;, Shape_t W_in_t;, Shape_t R_in_t;, Shape_t B_in_t;, Shape_t sequence_lens_in_t;, Shape_t initial_h_in_t;, Shape_t Y_out_t;, Shape_t Y_h_out_t;, int* activations_t;, float clip_t;, int direction_t;, int hidden_size_t;
Concat=Shape_t inputs_in_t;, Shape_t concat_result_out_t;, int axis_t;
Constant=Shape_t output_out_t;
LpPool=Shape_t X_in_t;, Shape_t Y_out_t;, int auto_pad_t;, Shape_t kernel_shape_t;, int p_t;, Shape_t pads_t;, Shape_t strides_t;
Conv=Shape_t X_in_t;, Shape_t W_in_t;, Shape_t B_in_t;, Shape_t Y_out_t;, int auto_pad_t;, Shape_t dilations_t;, int group_t;, Shape_t kernel_shape_t;, Shape_t pads_t;, Shape_t strides_t;
Not=Shape_t X_in_t;, Shape_t Y_out_t;
Gather=Shape_t data_in_t;, Shape_t indices_in_t;, Shape_t output_out_t;, int axis_t;
ConvTranspose=Shape_t X_in_t;, Shape_t W_in_t;, Shape_t B_in_t;, Shape_t Y_out_t;, int auto_pad_t;, Shape_t dilations_t;, int group_t;, Shape_t kernel_shape_t;, Shape_t output_padding_t;, Shape_t output_shape_t;, Shape_t pads_t;, Shape_t strides_t;
Dropout=Shape_t data_in_t;, Shape_t output_out_t;, Shape_t mask_out_t;, float ratio_t;
LeakyRelu=Shape_t X_in_t;, Shape_t Y_out_t;, float alpha_t;
Elu=Shape_t X_in_t;, Shape_t Y_out_t;, float alpha_t;
GlobalAveragePool=Shape_t X_in_t;, Shape_t Y_out_t;
Gemm=Shape_t A_in_t;, Shape_t B_in_t;, Shape_t C_in_t;, Shape_t Y_out_t;, float alpha_t;, float beta_t;, int transA_t;, int transB_t;
MaxPool=Shape_t X_in_t;, Shape_t Y_out_t;, Shape_t Indices_out_t;, int auto_pad_t;, int ceil_mode_t;, Shape_t dilations_t;, Shape_t kernel_shape_t;, Shape_t pads_t;, int storage_order_t;, Shape_t strides_t;
Equal=Shape_t A_in_t;, Shape_t B_in_t;, Shape_t C_out_t;
Tile=Shape_t input_in_t;, Shape_t repeats_in_t;, Shape_t output_out_t;
Flatten=Shape_t input_in_t;, Shape_t output_out_t;, int axis_t;
Floor=Shape_t X_in_t;, Shape_t Y_out_t;
GRU=Shape_t X_in_t;, Shape_t W_in_t;, Shape_t R_in_t;, Shape_t B_in_t;, Shape_t sequence_lens_in_t;, Shape_t initial_h_in_t;, Shape_t Y_out_t;, Shape_t Y_h_out_t;, int* activations_t;, float clip_t;, int direction_t;, int hidden_size_t;, int linear_before_reset_t;
GlobalLpPool=Shape_t X_in_t;, Shape_t Y_out_t;, int p_t;
Greater=Shape_t A_in_t;, Shape_t B_in_t;, Shape_t C_out_t;
HardSigmoid=Shape_t X_in_t;, Shape_t Y_out_t;, float alpha_t;, float beta_t;
Selu=Shape_t X_in_t;, Shape_t Y_out_t;, float alpha_t;, float gamma_t;
Hardmax=Shape_t input_in_t;, Shape_t output_out_t;, int axis_t;
If=Shape_t cond_in_t;, Shape_t outputs_out_t;
Min=Shape_t data_0_in_t;, Shape_t min_out_t;
InstanceNormalization=Shape_t input_in_t;, Shape_t scale_in_t;, Shape_t B_in_t;, Shape_t output_out_t;, float epsilon_t;
Less=Shape_t A_in_t;, Shape_t B_in_t;, Shape_t C_out_t;
EyeLike=Shape_t input_in_t;, Shape_t output_out_t;, int dtype_t;, int k_t;
RandomNormal=Shape_t output_out_t;, int dtype_t;, float mean_t;, float scale_t;, float seed_t;, Shape_t shape_t;
Slice=Shape_t data_in_t;, Shape_t starts_in_t;, Shape_t ends_in_t;, Shape_t axes_in_t;, Shape_t steps_in_t;, Shape_t output_out_t;
PRelu=Shape_t X_in_t;, Shape_t slope_in_t;, Shape_t Y_out_t;
Log=Shape_t input_in_t;, Shape_t output_out_t;
LogSoftmax=Shape_t input_in_t;, Shape_t output_out_t;, int axis_t;
Loop=Shape_t M_in_t;, Shape_t cond_in_t;, Shape_t v_initial_in_t;, Shape_t v_final_and_scan_outputs_out_t;
LpNormalization=Shape_t input_in_t;, Shape_t output_out_t;, int axis_t;, int p_t;
MatMul=Shape_t A_in_t;, Shape_t B_in_t;, Shape_t Y_out_t;
ReduceL2=Shape_t data_in_t;, Shape_t reduced_out_t;, Shape_t axes_t;, int keepdims_t;
Max=Shape_t data_0_in_t;, Shape_t max_out_t;
MaxRoiPool=Shape_t X_in_t;, Shape_t rois_in_t;, Shape_t Y_out_t;, Shape_t pooled_shape_t;, float spatial_scale_t;
Or=Shape_t A_in_t;, Shape_t B_in_t;, Shape_t C_out_t;
Pad=Shape_t data_in_t;, Shape_t output_out_t;, int mode_t;, Shape_t pads_t;, float value_t;
RandomUniformLike=Shape_t input_in_t;, Shape_t output_out_t;, int dtype_t;, float high_t;, float low_t;, float seed_t;
Reciprocal=Shape_t X_in_t;, Shape_t Y_out_t;
Pow=Shape_t X_in_t;, Shape_t Y_in_t;, Shape_t Z_out_t;
RandomNormalLike=Shape_t input_in_t;, Shape_t output_out_t;, int dtype_t;, float mean_t;, float scale_t;, float seed_t;
OneHot=Shape_t indices_in_t;, Shape_t depth_in_t;, Shape_t values_in_t;, Shape_t output_out_t;, int axis_t;
RandomUniform=Shape_t output_out_t;, int dtype_t;, float high_t;, float low_t;, float seed_t;, Shape_t shape_t;
ReduceL1=Shape_t data_in_t;, Shape_t reduced_out_t;, Shape_t axes_t;, int keepdims_t;
ReduceLogSum=Shape_t data_in_t;, Shape_t reduced_out_t;, Shape_t axes_t;, int keepdims_t;
ReduceLogSumExp=Shape_t data_in_t;, Shape_t reduced_out_t;, Shape_t axes_t;, int keepdims_t;
ReduceMax=Shape_t data_in_t;, Shape_t reduced_out_t;, Shape_t axes_t;, int keepdims_t;
OneHotEncoder=Shape_t X_in_t;, Shape_t Y_out_t;, Shape_t cats_int64s_t;, int* cats_strings_t;, int zeros_t;
IsNaN=Shape_t X_in_t;, Shape_t Y_out_t;
ReduceMean=Shape_t data_in_t;, Shape_t reduced_out_t;, Shape_t axes_t;, int keepdims_t;
ReduceMin=Shape_t data_in_t;, Shape_t reduced_out_t;, Shape_t axes_t;, int keepdims_t;
TreeEnsembleRegressor=Shape_t X_in_t;, Shape_t Y_out_t;, int aggregate_function_t;, int n_targets_t;, Shape_t nodes_falsenodeids_t;, Shape_t nodes_featureids_t;, Shape_t nodes_missing_value_tracks_true_t;, int* nodes_modes_t;, Shape_t nodes_nodeids_t;, Shape_t nodes_treeids_t;, Shape_t nodes_truenodeids_t;, int post_transform_t;, Shape_t target_ids_t;, Shape_t target_nodeids_t;, Shape_t target_treeids_t;
ReduceProd=Shape_t data_in_t;, Shape_t reduced_out_t;, Shape_t axes_t;, int keepdims_t;
ReduceSum=Shape_t data_in_t;, Shape_t reduced_out_t;, Shape_t axes_t;, int keepdims_t;
ReduceSumSquare=Shape_t data_in_t;, Shape_t reduced_out_t;, Shape_t axes_t;, int keepdims_t;
Relu=Shape_t X_in_t;, Shape_t Y_out_t;
Reshape=Shape_t data_in_t;, Shape_t shape_in_t;, Shape_t reshaped_out_t;
Shape=Shape_t data_in_t;, Shape_t shape_out_t;
Sigmoid=Shape_t X_in_t;, Shape_t Y_out_t;
Size=Shape_t data_in_t;, Shape_t size_out_t;
Softmax=Shape_t input_in_t;, Shape_t output_out_t;, int axis_t;
Softplus=Shape_t X_in_t;, Shape_t Y_out_t;
Softsign=Shape_t input_in_t;, Shape_t output_out_t;
SpaceToDepth=Shape_t input_in_t;, Shape_t output_out_t;, int blocksize_t;
TfIdfVectorizer=Shape_t X_in_t;, Shape_t Y_out_t;, int max_gram_length_t;, int max_skip_count_t;, int min_gram_length_t;, int mode_t;, Shape_t ngram_counts_t;, Shape_t ngram_indexes_t;, Shape_t pool_int64s_t;, int* pool_strings_t;
Split=Shape_t input_in_t;, Shape_t outputs_out_t;, int axis_t;, Shape_t split_t;
Imputer=Shape_t X_in_t;, Shape_t Y_out_t;, Shape_t imputed_value_int64s_t;, float replaced_value_float_t;, int replaced_value_int64_t;
Sqrt=Shape_t X_in_t;, Shape_t Y_out_t;
Squeeze=Shape_t data_in_t;, Shape_t squeezed_out_t;, Shape_t axes_t;
TopK=Shape_t X_in_t;, Shape_t K_in_t;, Shape_t Values_out_t;, Shape_t Indices_out_t;, int axis_t;
Sub=Shape_t A_in_t;, Shape_t B_in_t;, Shape_t C_out_t;
Sum=Shape_t data_0_in_t;, Shape_t sum_out_t;
Shrink=Shape_t input_in_t;, Shape_t output_out_t;, float bias_t;, float lambd_t;
Tanh=Shape_t input_in_t;, Shape_t output_out_t;
Transpose=Shape_t data_in_t;, Shape_t transposed_out_t;, Shape_t perm_t;
Unsqueeze=Shape_t data_in_t;, Shape_t expanded_out_t;, Shape_t axes_t;
Upsample=Shape_t X_in_t;, Shape_t scales_in_t;, Shape_t Y_out_t;, int mode_t;
SVMClassifier=Shape_t X_in_t;, Shape_t Y_out_t;, Shape_t Z_out_t;, Shape_t classlabels_ints_t;, int* classlabels_strings_t;, int kernel_type_t;, int post_transform_t;, Shape_t vectors_per_class_t;
Xor=Shape_t A_in_t;, Shape_t B_in_t;, Shape_t C_out_t;
Acos=Shape_t input_in_t;, Shape_t output_out_t;
Asin=Shape_t input_in_t;, Shape_t output_out_t;
Atan=Shape_t input_in_t;, Shape_t output_out_t;
Cos=Shape_t input_in_t;, Shape_t output_out_t;
Sin=Shape_t input_in_t;, Shape_t output_out_t;
Tan=Shape_t input_in_t;, Shape_t output_out_t;
Multinomial=Shape_t input_in_t;, Shape_t output_out_t;, int dtype_t;, int sample_size_t;, float seed_t;
Scan=Shape_t initial_state_and_scan_inputs_in_t;, Shape_t final_state_and_scan_outputs_out_t;, int num_scan_inputs_t;, Shape_t scan_input_axes_t;, Shape_t scan_input_directions_t;, Shape_t scan_output_axes_t;, Shape_t scan_output_directions_t;
Compress=Shape_t input_in_t;, Shape_t condition_in_t;, Shape_t output_out_t;, int axis_t;
ConstantOfShape=Shape_t input_in_t;, Shape_t output_out_t;
MaxUnpool=Shape_t X_in_t;, Shape_t I_in_t;, Shape_t output_shape_in_t;, Shape_t output_out_t;, Shape_t kernel_shape_t;, Shape_t pads_t;, Shape_t strides_t;
Scatter=Shape_t data_in_t;, Shape_t indices_in_t;, Shape_t updates_in_t;, Shape_t output_out_t;, int axis_t;
Sinh=Shape_t input_in_t;, Shape_t output_out_t;
Cosh=Shape_t input_in_t;, Shape_t output_out_t;
Asinh=Shape_t input_in_t;, Shape_t output_out_t;
Acosh=Shape_t input_in_t;, Shape_t output_out_t;
NonMaxSuppression=Shape_t boxes_in_t;, Shape_t scores_in_t;, Shape_t max_output_boxes_per_class_in_t;, Shape_t iou_threshold_in_t;, Shape_t score_threshold_in_t;, Shape_t selected_indices_out_t;, int center_point_box_t;
Atanh=Shape_t input_in_t;, Shape_t output_out_t;
Sign=Shape_t input_in_t;, Shape_t output_out_t;
Erf=Shape_t input_in_t;, Shape_t output_out_t;
Where=Shape_t condition_in_t;, Shape_t X_in_t;, Shape_t Y_in_t;, Shape_t output_out_t;
NonZero=Shape_t X_in_t;, Shape_t Y_out_t;
MeanVarianceNormalization=Shape_t X_in_t;, Shape_t Y_out_t;, Shape_t axes_t;
StringNormalizer=Shape_t X_in_t;, Shape_t Y_out_t;, int case_change_action_t;, int is_case_sensitive_t;, int locale_t;, int* stopwords_t;
Mod=Shape_t A_in_t;, Shape_t B_in_t;, Shape_t C_out_t;, int fmod_t;
ThresholdedRelu=Shape_t X_in_t;, Shape_t Y_out_t;, float alpha_t;
MatMulInteger=Shape_t A_in_t;, Shape_t B_in_t;, Shape_t a_zero_point_in_t;, Shape_t b_zero_point_in_t;, Shape_t Y_out_t;
QLinearMatMul=Shape_t a_in_t;, Shape_t a_scale_in_t;, Shape_t a_zero_point_in_t;, Shape_t b_in_t;, Shape_t b_scale_in_t;, Shape_t b_zero_point_in_t;, Shape_t y_scale_in_t;, Shape_t y_zero_point_in_t;, Shape_t y_out_t;
ConvInteger=Shape_t x_in_t;, Shape_t w_in_t;, Shape_t x_zero_point_in_t;, Shape_t w_zero_point_in_t;, Shape_t y_out_t;, int auto_pad_t;, Shape_t dilations_t;, int group_t;, Shape_t kernel_shape_t;, Shape_t pads_t;, Shape_t strides_t;
QLinearConv=Shape_t x_in_t;, Shape_t x_scale_in_t;, Shape_t x_zero_point_in_t;, Shape_t w_in_t;, Shape_t w_scale_in_t;, Shape_t w_zero_point_in_t;, Shape_t y_scale_in_t;, Shape_t y_zero_point_in_t;, Shape_t B_in_t;, Shape_t y_out_t;, int auto_pad_t;, Shape_t dilations_t;, int group_t;, Shape_t kernel_shape_t;, Shape_t pads_t;, Shape_t strides_t;
QuantizeLinear=Shape_t x_in_t;, Shape_t y_scale_in_t;, Shape_t y_zero_point_in_t;, Shape_t y_out_t;
DequantizeLinear=Shape_t x_in_t;, Shape_t x_scale_in_t;, Shape_t x_zero_point_in_t;, Shape_t y_out_t;
IsInf=Shape_t X_in_t;, Shape_t Y_out_t;, int detect_negative_t;, int detect_positive_t;
RoiAlign=Shape_t X_in_t;, Shape_t rois_in_t;, Shape_t batch_indices_in_t;, Shape_t Y_out_t;, int mode_t;, int output_height_t;, int output_width_t;, int sampling_ratio_t;, float spatial_scale_t;
ArrayFeatureExtractor=Shape_t X_in_t;, Shape_t Y_in_t;, Shape_t Z_out_t;
Binarizer=Shape_t X_in_t;, Shape_t Y_out_t;, float threshold_t;
CategoryMapper=Shape_t X_in_t;, Shape_t Y_out_t;, Shape_t cats_int64s_t;, int* cats_strings_t;, int default_int64_t;, int default_string_t;
DictVectorizer=Shape_t X_in_t;, Shape_t Y_out_t;, Shape_t int64_vocabulary_t;, int* string_vocabulary_t;
FeatureVectorizer=Shape_t X_in_t;, Shape_t Y_out_t;, Shape_t inputdimensions_t;
LabelEncoder=Shape_t X_in_t;, Shape_t Y_out_t;, float default_float_t;, int default_int64_t;, int default_string_t;, Shape_t keys_int64s_t;, int* keys_strings_t;, Shape_t values_int64s_t;, int* values_strings_t;
LinearClassifier=Shape_t X_in_t;, Shape_t Y_out_t;, Shape_t Z_out_t;, Shape_t classlabels_ints_t;, int* classlabels_strings_t;, int multi_class_t;, int post_transform_t;
LinearRegressor=Shape_t X_in_t;, Shape_t Y_out_t;, int post_transform_t;, int targets_t;
Normalizer=Shape_t X_in_t;, Shape_t Y_out_t;, int norm_t;
SVMRegressor=Shape_t X_in_t;, Shape_t Y_out_t;, int kernel_type_t;, int n_supports_t;, int one_class_t;, int post_transform_t;
Scaler=Shape_t X_in_t;, Shape_t Y_out_t;
TreeEnsembleClassifier=Shape_t X_in_t;, Shape_t Y_out_t;, Shape_t Z_out_t;, Shape_t class_ids_t;, Shape_t class_nodeids_t;, Shape_t class_treeids_t;, Shape_t classlabels_int64s_t;, int* classlabels_strings_t;, Shape_t nodes_falsenodeids_t;, Shape_t nodes_featureids_t;, Shape_t nodes_missing_value_tracks_true_t;, int* nodes_modes_t;, Shape_t nodes_nodeids_t;, Shape_t nodes_treeids_t;, Shape_t nodes_truenodeids_t;, int post_transform_t;
ZipMap=Shape_t X_in_t;, Shape_t Z_out_t;, Shape_t classlabels_int64s_t;, int* classlabels_strings_t;
