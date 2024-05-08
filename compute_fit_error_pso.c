/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: compute_fit_error_pso.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 2024-04-29 11:40:58
 */

/* Include Files */
#include "compute_fit_error_pso.h"
#include "PSO_marker_extric_estimate_emxutil.h"
#include "PSO_marker_extric_estimate_types.h"
#include "rt_nonfinite.h"
#include <emmintrin.h>
#include <math.h>
#include <xmmintrin.h>

#define M_PI 3.14159265358979323846

/* Function Declarations */
static void binary_expand_op(emxArray_real_T *in1, const emxArray_real_T *in2,
                             const double in3[3], const emxArray_real_T *in4);

static void minus(emxArray_real_T *in1, const emxArray_real_T *in2,
                  const emxArray_real_T *in3);

/* Function Definitions */
/*
 * Arguments    : emxArray_real_T *in1
 *                const emxArray_real_T *in2
 *                const double in3[3]
 *                const emxArray_real_T *in4
 * Return Type  : void
 */
static void binary_expand_op(emxArray_real_T *in1, const emxArray_real_T *in2,
                             const double in3[3], const emxArray_real_T *in4)
{
  emxArray_real_T *b_in2;
  const double *in2_data;
  double *b_in2_data;
  double *in1_data;
  int b_in4;
  int i;
  int i1;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  in2_data = in2->data;
  in1_data = in1->data;
  b_in4 = in4->size[0];
  emxInit_real_T(&b_in2, 2);
  if (in1->size[0] == 1) {
    loop_ub = in2->size[0];
  } else {
    loop_ub = in1->size[0];
  }
  i = b_in2->size[0] * b_in2->size[1];
  b_in2->size[0] = loop_ub;
  b_in2->size[1] = 3;
  emxEnsureCapacity_real_T(b_in2, i);
  b_in2_data = b_in2->data;
  stride_0_0 = (in2->size[0] != 1);
  stride_1_0 = (in1->size[0] != 1);
  for (i = 0; i < 3; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      b_in2_data[i1 + b_in2->size[0] * i] =
          in2_data[i1 * stride_0_0 + in2->size[0] * i] -
          (in1_data[i1 * stride_1_0 + in1->size[0] * i] +
           in3[i] / (double)b_in4);
    }
  }
  i = in1->size[0] * in1->size[1];
  in1->size[0] = loop_ub;
  in1->size[1] = 3;
  emxEnsureCapacity_real_T(in1, i);
  in1_data = in1->data;
  for (i = 0; i < 3; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      in1_data[i1 + in1->size[0] * i] = b_in2_data[i1 + b_in2->size[0] * i];
    }
  }
  emxFree_real_T(&b_in2);
}

/*
 * Arguments    : emxArray_real_T *in1
 *                const emxArray_real_T *in2
 *                const emxArray_real_T *in3
 * Return Type  : void
 */
static void minus(emxArray_real_T *in1, const emxArray_real_T *in2,
                  const emxArray_real_T *in3)
{
  const double *in2_data;
  const double *in3_data;
  double *in1_data;
  int i;
  int i1;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  in3_data = in3->data;
  in2_data = in2->data;
  if (in3->size[0] == 1) {
    loop_ub = in2->size[0];
  } else {
    loop_ub = in3->size[0];
  }
  i = in1->size[0] * in1->size[1];
  in1->size[0] = loop_ub;
  in1->size[1] = 3;
  emxEnsureCapacity_real_T(in1, i);
  in1_data = in1->data;
  stride_0_0 = (in2->size[0] != 1);
  stride_1_0 = (in3->size[0] != 1);
  for (i = 0; i < 3; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      in1_data[i1 + in1->size[0] * i] =
          in2_data[i1 * stride_0_0 + in2->size[0] * i] -
          in3_data[i1 * stride_1_0 + in3->size[0] * i];
    }
  }
}

/*
 * 根据 roll 和 pitch 计算 marker_xyz_ned
 *
 * Arguments    : const double params[2]
 *                const emxArray_real_T *fit_data_pe
 *                const emxArray_real32_T *fit_data_marker_location
 *                const emxArray_real_T *fit_data_R_b2e
 * Return Type  : double
 */
double compute_fit_error_pso(const double params[2],
                             const emxArray_real_T *fit_data_pe,
                             const emxArray_real32_T *fit_data_marker_location,
                             const emxArray_real_T *fit_data_R_b2e)
{
  static const double b[9] = {6.123233995736766E-17,
                              1.0,
                              -0.0,
                              1.0,
                              -6.123233995736766E-17,
                              1.2246467991473532E-16,
                              1.2246467991473532E-16,
                              -7.498798913309288E-33,
                              -1.0};
  __m128 r;
  __m128d r1;
  emxArray_real32_T *b_marker_xyz_imu;
  emxArray_real32_T *marker_xyz_imu;
  emxArray_real_T *marker_xyz_ned;
  emxArray_real_T *x;
  emxArray_real_T *xv;
  double a[9];
  double R_c2b0[3][3];
  double R_c2b_compens[3][3];
  double eulerCompens_xyz[3];
  double markerxyz_imu[3];
  double markerxyz_ned[3];
  double markerxyz_imu_list[fit_data_marker_location->size[0]][3];
  double markerxyz_ned_list[fit_data_marker_location->size[0]][3];
  const double *fit_data_R_b2e_data;
  const double *fit_data_pe_data;
  double ct_idx_0;
  double ct_idx_1;
  double d;
  double fit_error;
  double scale;
  double t;
  double *marker_xyz_ned_data;
  double *xv_data;
  float b_a[9];
  const float *fit_data_marker_location_data;
  float *b_marker_xyz_imu_data;
  float *marker_xyz_imu_data;
  int firstBlockLength;
  int hi;
  int ib;
  int k;
  int lastBlockLength;
  int nblocks;
  int p;
  int xblockoffset;
  int xi;
  int xpageoffset;
  fit_data_R_b2e_data = fit_data_R_b2e->data;
  fit_data_marker_location_data = fit_data_marker_location->data;
  fit_data_pe_data = fit_data_pe->data;

  /*  计算当前roll、pitch值的marker location测量值 */
  double roll_init = M_PI;    // 绕 X 轴的旋转角度    --PH5
  double pitch_init = 0;      // 绕 Y 轴的旋转角度
  double yaw_init = M_PI / 2; // 绕 Z 轴的旋转角度
  double eulerAngles0[3] = {roll_init, pitch_init, yaw_init};
  euler2rotm(eulerAngles0, R_c2b0);
  R_c2b0[0][0] = 0;
  R_c2b0[0][1] = 1;
  R_c2b0[0][2] = 0;

  R_c2b0[1][0] = 1;
  R_c2b0[1][1] = 0;
  R_c2b0[1][2] = 0;

  R_c2b0[2][0] = 0;
  R_c2b0[2][1] = 0;
  R_c2b0[2][2] = -1;

  // debug
  // printf("STEP7:R_c2b0[0][0]= %f, [0][1]= %f, [0][2]= %f\n",
  // R_c2b0[0][0],R_c2b0[0][1], R_c2b0[0][2]); printf("STEP7:R_c2b0[1][0]= %f,
  // [1][1]= %f, [1][2]= %f\n", R_c2b0[1][0], R_c2b0[1][1], R_c2b0[1][2]);
  // printf("STEP7:R_c2b0[2][0]= %f, [2][1]= %f, [2][2]= %f\n", R_c2b0[2][0],
  // R_c2b0[2][1], R_c2b0[2][2]);

  /*  组合欧拉角向量 */
  eulerCompens_xyz[0] = params[0] / 57.3; // [roll, pitch, yaw]
  eulerCompens_xyz[1] = params[1] / 57.3; /*  单位：deg to rad */
  eulerCompens_xyz[2] = 0;
  euler2rotm(eulerCompens_xyz, R_c2b_compens);

  // debug
  // printf("STEP6:params[0]= %f, params[1]= %f\n", params[0], params[1]);

  // printf("STEP7:R_c2b_compens[0][0]= %f, [0][1]= %f, [0][2]= %f\n",
  //        R_c2b_compens[0][0], R_c2b_compens[0][1], R_c2b_compens[0][2]);
  // printf("STEP7:R_c2b_compens[1][0]= %f, [1][1]= %f, [1][2]= %f\n",
  //        R_c2b_compens[1][0], R_c2b_compens[1][1], R_c2b_compens[1][2]);
  // printf("STEP7:R_c2b_compens[2][0]= %f, [2][1]= %f, [2][2]= %f\n",
  //        R_c2b_compens[2][0], R_c2b_compens[2][1], R_c2b_compens[2][2]);
  
  double t_c2b[3] = {-0.108, 0.033, 0.038}; // --PH5

  // fit_data_marker_location_data
  for (int i = 0; i < fit_data_marker_location->size[0]; i++) {
    markerxyz_imu[0] =
        R_c2b_compens[0][1] * fit_data_marker_location_data[i * 3 + 0] +
        R_c2b_compens[0][0] * fit_data_marker_location_data[i * 3 + 1] -
        R_c2b_compens[0][2] * fit_data_marker_location_data[i * 3 + 2] +
        t_c2b[1];
    markerxyz_imu[1] =
        R_c2b_compens[1][1] * fit_data_marker_location_data[i * 3 + 0] +
        R_c2b_compens[1][0] * fit_data_marker_location_data[i * 3 + 1] -
        R_c2b_compens[1][2] * fit_data_marker_location_data[i * 3 + 2] +
        t_c2b[2];
    markerxyz_imu[2] =
        R_c2b_compens[2][1] * fit_data_marker_location_data[i * 3 + 0] +
        R_c2b_compens[2][0] * fit_data_marker_location_data[i * 3 + 1] -
        R_c2b_compens[2][2] * fit_data_marker_location_data[i * 3 + 2] +
        t_c2b[3];
    for (int j = 0; j < 3; j++) {
      markerxyz_imu_list[i][j] = markerxyz_imu[j];
    }
    // debug
    // printf("STEP7:markerxyz_imu_list[%d][:]: [%f,%f,%f]\n", i,
    //  markerxyz_imu_list[i][0], markerxyz_imu_list[i][1],
    //  markerxyz_imu_list[i][2]);
  }

  /*  将欧拉角转换为旋转矩阵 */
  ct_idx_0 = cos(eulerCompens_xyz[0]);
  eulerCompens_xyz[0] = sin(eulerCompens_xyz[0]);
  ct_idx_1 = cos(eulerCompens_xyz[1]);
  eulerCompens_xyz[1] = sin(eulerCompens_xyz[1]);
  a[0] = ct_idx_1;
  a[3] = -ct_idx_1 * 0.0;
  a[6] = eulerCompens_xyz[1];
  t = eulerCompens_xyz[0] * eulerCompens_xyz[1];
  a[1] = ct_idx_0 * 0.0 + t;
  a[4] = ct_idx_0 - t * 0.0;
  a[7] = -ct_idx_1 * eulerCompens_xyz[0];
  t = ct_idx_0 * eulerCompens_xyz[1];
  a[2] = eulerCompens_xyz[0] * 0.0 - t;
  a[5] = eulerCompens_xyz[0] + t * 0.0;
  a[8] = ct_idx_0 * ct_idx_1;
  for (hi = 0; hi < 3; hi++) {
    d = a[hi];
    ct_idx_0 = a[hi + 3];
    ct_idx_1 = a[hi + 6];
    for (xblockoffset = 0; xblockoffset < 3; xblockoffset++) {
      b_a[hi + 3 * xblockoffset] =
          (float)((d * b[3 * xblockoffset] +
                   ct_idx_0 * b[3 * xblockoffset + 1]) +
                  ct_idx_1 * b[3 * xblockoffset + 2]);
    }
  }
  emxInit_real32_T(&marker_xyz_imu, 2);
  lastBlockLength = fit_data_marker_location->size[0];
  hi = marker_xyz_imu->size[0] * marker_xyz_imu->size[1];
  marker_xyz_imu->size[0] = fit_data_marker_location->size[0];
  marker_xyz_imu->size[1] = 3;
  emxEnsureCapacity_real32_T(marker_xyz_imu, hi);
  marker_xyz_imu_data = marker_xyz_imu->data;
  for (hi = 0; hi < lastBlockLength; hi++) {
    for (xblockoffset = 0; xblockoffset < 3; xblockoffset++) {
      marker_xyz_imu_data[hi + marker_xyz_imu->size[0] * xblockoffset] =
          (b_a[xblockoffset] * fit_data_marker_location_data[hi] +
           b_a[xblockoffset + 3] *
               fit_data_marker_location_data[hi + fit_data_marker_location
                                                      ->size[0]]) +
          b_a[xblockoffset + 6] *
              fit_data_marker_location_data[hi +
                                            fit_data_marker_location->size[0] *
                                                2];
    }
  }
  xpageoffset = marker_xyz_imu->size[0] - 1;
  emxInit_real32_T(&b_marker_xyz_imu, 2);
  hi = b_marker_xyz_imu->size[0] * b_marker_xyz_imu->size[1];
  b_marker_xyz_imu->size[0] = fit_data_marker_location->size[0];
  b_marker_xyz_imu->size[1] = 3;
  emxEnsureCapacity_real32_T(b_marker_xyz_imu, hi);
  b_marker_xyz_imu_data = b_marker_xyz_imu->data;
  firstBlockLength = (marker_xyz_imu->size[0] / 4) << 2;
  nblocks = firstBlockLength - 4;
  for (hi = 0; hi <= nblocks; hi += 4) {
    r = _mm_loadu_ps(&marker_xyz_imu_data[hi]);
    _mm_storeu_ps(&b_marker_xyz_imu_data[hi],
                  _mm_sub_ps(r, _mm_set1_ps(0.108F)));
  }
  for (hi = firstBlockLength; hi < lastBlockLength; hi++) {
    b_marker_xyz_imu_data[hi] = marker_xyz_imu_data[hi] - 0.108F;
  }
  for (hi = 0; hi <= nblocks; hi += 4) {
    r = _mm_loadu_ps(&marker_xyz_imu_data[hi + marker_xyz_imu->size[0]]);
    _mm_storeu_ps(&b_marker_xyz_imu_data[hi + b_marker_xyz_imu->size[0]],
                  _mm_add_ps(r, _mm_set1_ps(0.033F)));
  }
  for (hi = firstBlockLength; hi <= xpageoffset; hi++) {
    b_marker_xyz_imu_data[hi + b_marker_xyz_imu->size[0]] =
        marker_xyz_imu_data[hi + marker_xyz_imu->size[0]] + 0.033F;
  }
  for (hi = 0; hi <= nblocks; hi += 4) {
    r = _mm_loadu_ps(&marker_xyz_imu_data[hi + marker_xyz_imu->size[0] * 2]);
    _mm_storeu_ps(&b_marker_xyz_imu_data[hi + b_marker_xyz_imu->size[0] * 2],
                  _mm_add_ps(r, _mm_set1_ps(0.038F)));
  }
  for (hi = firstBlockLength; hi <= xpageoffset; hi++) {
    b_marker_xyz_imu_data[hi + b_marker_xyz_imu->size[0] * 2] =
        marker_xyz_imu_data[hi + marker_xyz_imu->size[0] * 2] + 0.038F;
  }
  hi = marker_xyz_imu->size[0] * marker_xyz_imu->size[1];
  marker_xyz_imu->size[0] = b_marker_xyz_imu->size[0];
  marker_xyz_imu->size[1] = 3;
  emxEnsureCapacity_real32_T(marker_xyz_imu, hi);
  marker_xyz_imu_data = marker_xyz_imu->data;
  xpageoffset = b_marker_xyz_imu->size[0] * 3;
  for (hi = 0; hi < xpageoffset; hi++) {
    marker_xyz_imu_data[hi] = b_marker_xyz_imu_data[hi];
  }
  emxFree_real32_T(&b_marker_xyz_imu);
  /*  1：imu系相对于ned的旋转矩阵R_b2e:
   * visual_data.imu_q_b2e、visual_data.marker_xyz_R_b2e */
  /*  2：marker_xyz 由vio坐标系c旋转到与imu坐标系b，再转到与ned原点坐标系e对齐
   */
  emxInit_real_T(&marker_xyz_ned, 2);
  hi = marker_xyz_ned->size[0] * marker_xyz_ned->size[1];
  marker_xyz_ned->size[0] = fit_data_marker_location->size[0];
  marker_xyz_ned->size[1] = 3;
  emxEnsureCapacity_real_T(marker_xyz_ned, hi);
  marker_xyz_ned_data = marker_xyz_ned->data;
  for (xpageoffset = 0; xpageoffset < lastBlockLength; xpageoffset++) {
    for (hi = 0; hi < 3; hi++) {
      xblockoffset = hi + 9 * xpageoffset;
      marker_xyz_ned_data[xpageoffset + marker_xyz_ned->size[0] * hi] =
          ((float)fit_data_R_b2e_data[xblockoffset] *
               marker_xyz_imu_data[xpageoffset] +
           (float)fit_data_R_b2e_data[xblockoffset + 3] *
               marker_xyz_imu_data[xpageoffset + marker_xyz_imu->size[0]]) +
          (float)fit_data_R_b2e_data[xblockoffset + 6] *
              marker_xyz_imu_data[xpageoffset + marker_xyz_imu->size[0] * 2];
    }
  }
  //
  for (int i = 0; i < fit_data_marker_location->size[0]; i++) {
    double markerxyz_imu_tmp[3];
    markerxyz_imu_tmp[0] = markerxyz_imu_list[i][0];
    markerxyz_imu_tmp[1] = markerxyz_imu_list[i][1];
    markerxyz_imu_tmp[2] = markerxyz_imu_list[i][2];

    markerxyz_ned[0] =
        fit_data_R_b2e_data[i * 9 + 0 * 3 + 0] * markerxyz_imu_tmp[0] +
        fit_data_R_b2e_data[i * 9 + 0 * 3 + 1] * markerxyz_imu_tmp[1] +
        fit_data_R_b2e_data[i * 9 + 0 * 3 + 2] * markerxyz_imu_tmp[2];
    markerxyz_ned[1] =
        fit_data_R_b2e_data[i * 9 + 1 * 3 + 0] * markerxyz_imu_tmp[0] +
        fit_data_R_b2e_data[i * 9 + 1 * 3 + 1] * markerxyz_imu_tmp[1] +
        fit_data_R_b2e_data[i * 9 + 1 * 3 + 2] * markerxyz_imu_tmp[2];
    markerxyz_ned[2] =
        fit_data_R_b2e_data[i * 9 + 2 * 3 + 0] * markerxyz_imu_tmp[0] +
        fit_data_R_b2e_data[i * 9 + 2 * 3 + 1] * markerxyz_imu_tmp[1] +
        fit_data_R_b2e_data[i * 9 + 2 * 3 + 2] * markerxyz_imu_tmp[2];
    for (int j = 0; j < 3; j++) {
      markerxyz_ned_list[i][j] = markerxyz_ned[j];
    }
    // debug
    // printf("STEP7:markerxyz_ned_list[%d][:]: [%f,%f,%f]\n", i,
    //  markerxyz_ned_list[i][0], markerxyz_ned_list[i][1],
    //  markerxyz_ned_list[i][2]);
  }
  /*  计算拟合误差和 */
  double mean_fit_error[3];
  double fit_error_trans[fit_data_pe->size[0]][2]; // 取xy二维误差
  mean_fit_error[0] = 0.0;
  mean_fit_error[1] = 0.0;
  mean_fit_error[2] = 0.0;
  fit_error = 0.0;

  if (fit_data_pe->size[0] == fit_data_marker_location->size[0]) {
    for (int i = 0; i < fit_data_pe->size[0] * fit_data_pe->size[1]; i++) {
      int idx0 = i / 3; // 商
      int idx1 = i % 3; // 余数
      mean_fit_error[idx1] +=
          (fit_data_pe->data[i] - markerxyz_ned_list[idx0][idx1]);

      // debug
      // printf("STEP8: fit_data_pe->data[%d]= %f, markerxyz_ned_list[%d][%d] =
      // %f \n", i, fit_data_pe->data[i], idx0, idx1,
      // markerxyz_ned_list[idx0][idx1]);
    }
    mean_fit_error[0] /= fit_data_pe->size[0];
    mean_fit_error[1] /= fit_data_pe->size[0];
    mean_fit_error[2] /= fit_data_pe->size[0];

    // debug
    //  printf("STEP9: mean_fit_error:[%f,%f,%f]\n",
    //  mean_fit_error[0],mean_fit_error[1],mean_fit_error[2]);

    for (size_t i = 0; i < fit_data_pe->size[0] * fit_data_pe->size[1]; i++) {
      int idx0 = i / 3; // 商
      int idx1 = i % 3; // 余数
      if (idx1 == 2) {  // 剔除第3维数据
        continue;
      } else {
        fit_error_trans[idx0][idx1] =
            fit_data_pe->data[i] -
            (markerxyz_ned_list[idx0][idx1] + mean_fit_error[idx1]);
        // debug
        // printf("STEP10: fit_error_trans[%d][%d]: %f,%f \n", idx0, idx1,
        // fit_error_trans[idx0][0], fit_error_trans[idx0][1]); fit_error +=
        // sqrt(fit_error_trans[idx0][0] * fit_error_trans[idx0][0] +
        //                       fit_error_trans[idx0][1] *
        //                       fit_error_trans[idx0][1]);
      }
    }
    // 计算fit_error_trans各列std
    double std_dev[2];
    double fit_error_std_mod = 0.0;

    for (int j = 0; j < 2; j++) {
      double list_sum = 0;
      for (int i = 0; i < fit_data_pe->size[0]; i++) { // 列和
        list_sum += fit_error_trans[i][j];
      }
      double list_mean = list_sum / fit_data_pe->size[0]; // 列均值
      double squar_diff_sum = 0.0;
      for (int i = 0; i < fit_data_pe->size[0]; i++) {
        double list_diff = fit_error_trans[i][j] - list_mean;
        squar_diff_sum += list_diff * list_diff; // 列方差
      }
      std_dev[j] = sqrt(squar_diff_sum / fit_data_pe->size[0]); // 列标准差
      fit_error_std_mod += std_dev[j] * std_dev[j];
    }
    fit_error_std_mod = sqrt(fit_error_std_mod); // 标准差模值
    fit_error = fit_error_std_mod;

    // debug
    // printf("STEP10: std_dev: [%f,%f]\n", std_dev[0], std_dev[1]);
    // printf("STEP11: fit_error_std_mod [%f]\n", fit_error_std_mod);
  }
  return fit_error;
  emxFree_real32_T(&marker_xyz_imu);
  /*  计算拟合误差和 */
  emxInit_real_T(&x, 2);
  if (fit_data_pe->size[0] == marker_xyz_ned->size[0]) {
    hi = x->size[0] * x->size[1];
    x->size[0] = fit_data_pe->size[0];
    x->size[1] = 3;
    emxEnsureCapacity_real_T(x, hi);
    xv_data = x->data;
    lastBlockLength = fit_data_pe->size[0] * 3;
    xpageoffset = (lastBlockLength / 2) << 1;
    firstBlockLength = xpageoffset - 2;
    for (hi = 0; hi <= firstBlockLength; hi += 2) {
      r1 = _mm_loadu_pd(&marker_xyz_ned_data[hi]);
      _mm_storeu_pd(&xv_data[hi],
                    _mm_sub_pd(_mm_loadu_pd(&fit_data_pe_data[hi]), r1));
    }
    for (hi = xpageoffset; hi < lastBlockLength; hi++) {
      xv_data[hi] = fit_data_pe_data[hi] - marker_xyz_ned_data[hi];
    }
  } else {
    minus(x, fit_data_pe, marker_xyz_ned);
    xv_data = x->data;
  }
  if (x->size[0] == 0) {
    eulerCompens_xyz[0] = 0.0;
    eulerCompens_xyz[1] = 0.0;
    eulerCompens_xyz[2] = 0.0;
  } else {
    if (x->size[0] <= 1024) {
      firstBlockLength = x->size[0];
      lastBlockLength = 0;
      nblocks = 1;
    } else {
      firstBlockLength = 1024;
      nblocks = (int)((unsigned int)x->size[0] >> 10);
      lastBlockLength = x->size[0] - (nblocks << 10);
      if (lastBlockLength > 0) {
        nblocks++;
      } else {
        lastBlockLength = 1024;
      }
    }
    for (xi = 0; xi < 3; xi++) {
      xpageoffset = xi * x->size[0];
      eulerCompens_xyz[xi] = xv_data[xpageoffset];
      for (k = 2; k <= firstBlockLength; k++) {
        eulerCompens_xyz[xi] += xv_data[(xpageoffset + k) - 1];
      }
      for (ib = 2; ib <= nblocks; ib++) {
        xblockoffset = xpageoffset + ((ib - 1) << 10);
        ct_idx_0 = xv_data[xblockoffset];
        if (ib == nblocks) {
          hi = lastBlockLength;
        } else {
          hi = 1024;
        }
        for (k = 2; k <= hi; k++) {
          ct_idx_0 += xv_data[(xblockoffset + k) - 1];
        }
        eulerCompens_xyz[xi] += ct_idx_0;
      }
    }
  }
  if (fit_data_pe->size[0] == marker_xyz_ned->size[0]) {
    nblocks = x->size[0];
    lastBlockLength = fit_data_pe->size[0];
    hi = x->size[0] * x->size[1];
    x->size[0] = fit_data_pe->size[0];
    x->size[1] = 3;
    emxEnsureCapacity_real_T(x, hi);
    xv_data = x->data;
    xpageoffset = (lastBlockLength / 2) << 1;
    firstBlockLength = xpageoffset - 2;
    for (hi = 0; hi < 3; hi++) {
      for (xblockoffset = 0; xblockoffset <= firstBlockLength;
           xblockoffset += 2) {
        r1 = _mm_loadu_pd(
            &marker_xyz_ned_data[xblockoffset + marker_xyz_ned->size[0] * hi]);
        _mm_storeu_pd(
            &xv_data[xblockoffset + x->size[0] * hi],
            _mm_sub_pd(
                _mm_loadu_pd(&fit_data_pe_data[xblockoffset +
                                               fit_data_pe->size[0] * hi]),
                _mm_add_pd(
                    r1, _mm_set1_pd(eulerCompens_xyz[hi] / (double)nblocks))));
      }
      for (xblockoffset = xpageoffset; xblockoffset < lastBlockLength;
           xblockoffset++) {
        xv_data[xblockoffset + x->size[0] * hi] =
            fit_data_pe_data[xblockoffset + fit_data_pe->size[0] * hi] -
            (marker_xyz_ned_data[xblockoffset + marker_xyz_ned->size[0] * hi] +
             eulerCompens_xyz[hi] / (double)nblocks);
      }
    }
    hi = marker_xyz_ned->size[0] * marker_xyz_ned->size[1];
    marker_xyz_ned->size[0] = x->size[0];
    marker_xyz_ned->size[1] = 3;
    emxEnsureCapacity_real_T(marker_xyz_ned, hi);
    marker_xyz_ned_data = marker_xyz_ned->data;
    lastBlockLength = x->size[0] * 3;
    for (hi = 0; hi < lastBlockLength; hi++) {
      marker_xyz_ned_data[hi] = xv_data[hi];
    }
  } else {
    binary_expand_op(marker_xyz_ned, fit_data_pe, eulerCompens_xyz, x);
    marker_xyz_ned_data = marker_xyz_ned->data;
  }
  emxFree_real_T(&x);
  xi = marker_xyz_ned->size[0];
  fit_error = 0.0;
  scale = 3.3121686421112381E-170;
  emxInit_real_T(&xv, 1);
  for (p = 0; p < 2; p++) {
    xpageoffset = p * xi;
    hi = xv->size[0];
    xv->size[0] = xi;
    emxEnsureCapacity_real_T(xv, hi);
    xv_data = xv->data;
    for (k = 0; k < xi; k++) {
      hi = xpageoffset + k;
      xv_data[k] = marker_xyz_ned_data[hi % marker_xyz_ned->size[0] +
                                       marker_xyz_ned->size[0] *
                                           (hi / marker_xyz_ned->size[0])];
    }
    if (marker_xyz_ned->size[0] == 0) {
      d = rtNaN;
    } else if (marker_xyz_ned->size[0] == 1) {
      if ((!rtIsInf(xv_data[0])) && (!rtIsNaN(xv_data[0]))) {
        d = 0.0;
      } else {
        d = rtNaN;
      }
    } else {
      double xbar;
      if (xv->size[0] == 0) {
        xbar = 0.0;
      } else {
        if (marker_xyz_ned->size[0] <= 1024) {
          firstBlockLength = xi;
          lastBlockLength = 0;
          nblocks = 1;
        } else {
          firstBlockLength = 1024;
          nblocks = (int)((unsigned int)marker_xyz_ned->size[0] >> 10);
          lastBlockLength = marker_xyz_ned->size[0] - (nblocks << 10);
          if (lastBlockLength > 0) {
            nblocks++;
          } else {
            lastBlockLength = 1024;
          }
        }
        xbar = xv_data[0];
        for (k = 2; k <= firstBlockLength; k++) {
          xbar += xv_data[k - 1];
        }
        for (ib = 2; ib <= nblocks; ib++) {
          xblockoffset = (ib - 1) << 10;
          ct_idx_0 = xv_data[xblockoffset];
          if (ib == nblocks) {
            hi = lastBlockLength;
          } else {
            hi = 1024;
          }
          for (k = 2; k <= hi; k++) {
            ct_idx_0 += xv_data[(xblockoffset + k) - 1];
          }
          xbar += ct_idx_0;
        }
      }
      xbar /= (double)marker_xyz_ned->size[0];
      ct_idx_0 = 0.0;
      ct_idx_1 = 3.3121686421112381E-170;
      for (k = 0; k < xi; k++) {
        d = fabs(xv_data[k] - xbar);
        if (d > ct_idx_1) {
          t = ct_idx_1 / d;
          ct_idx_0 = ct_idx_0 * t * t + 1.0;
          ct_idx_1 = d;
        } else {
          t = d / ct_idx_1;
          ct_idx_0 += t * t;
        }
      }
      ct_idx_0 = ct_idx_1 * sqrt(ct_idx_0);
      d = ct_idx_0 / sqrt((double)marker_xyz_ned->size[0] - 1.0);
    }
    if (d > scale) {
      t = scale / d;
      fit_error = fit_error * t * t + 1.0;
      scale = d;
    } else {
      t = d / scale;
      fit_error += t * t;
    }
  }
  emxFree_real_T(&xv);
  emxFree_real_T(&marker_xyz_ned);
  return scale * sqrt(fit_error);
  /*  fit_error = std(fit_error_trans(:,1:2)); */
  /*  显示输出 */
  /*  disp(strcat('param:[',num2str(params(1)),',',num2str(params(2)),']
   * ','res:',num2str(fit_error))); */
}

// 按ZYX顺序，欧拉角转为旋转矩阵
void euler2rotm(double eulerAngles[3], double R[3][3])
{
  double a = eulerAngles[0];
  double b = eulerAngles[1];
  double c = eulerAngles[2];

  double cos_a = cos(a);
  double sin_a = sin(a);
  double cos_b = cos(b);
  double sin_b = sin(b);
  double cos_c = cos(c);
  double sin_c = sin(c);

  R[0][0] = cos_b * cos_c;
  R[0][1] = -cos_b * sin_c;
  R[0][2] = sin_b;

  R[1][0] = sin_a * sin_b * cos_c + cos_a * sin_c;
  R[1][1] = -sin_a * sin_b * sin_c + cos_a * cos_c;
  R[1][2] = -sin_a * cos_b;

  R[2][0] = -cos_a * sin_b * cos_c + sin_a * sin_c;
  R[2][1] = cos_a * sin_b * sin_c + sin_a * cos_c;
  R[2][2] = cos_a * cos_b;
}
/*
 * File trailer for compute_fit_error_pso.c
 *
 * [EOF]
 */
