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
#include "rt_nonfinite.h"
#include <emmintrin.h>
#include <math.h>
#include <xmmintrin.h>

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
  double eulerCompens_xyz[3];
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
  /*  单位：deg */
  /*  计算当前roll、pitch值的marker location测量值 */
  /*  绕 X 轴的旋转角度    --PH5 */
  /*  绕 Y 轴的旋转角度 */
  /*  绕 Z 轴的旋转角度 */
  /*  组合欧拉角向量 */
  eulerCompens_xyz[0] = params[0] / 57.3;
  eulerCompens_xyz[1] = params[1] / 57.3;
  /*  将欧拉角转换为旋转矩阵 */
  /* --PH5 */
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

/*
 * File trailer for compute_fit_error_pso.c
 *
 * [EOF]
 */
