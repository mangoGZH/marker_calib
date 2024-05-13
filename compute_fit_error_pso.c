/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: compute_fit_error_pso.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 2024-05-13 17:23:46
 */

/* Include Files */
#include "compute_fit_error_pso.h"
#include "PSO_marker_extric_estimate_emxutil.h"
#include "PSO_marker_extric_estimate_types.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>

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
  emxArray_real32_T *b_marker_xyz_imu;
  emxArray_real32_T *marker_xyz_imu;
  emxArray_real_T *marker_xyz_ned;
  emxArray_real_T *x;
  emxArray_real_T *xv;
  double R_c2b_comp[9];
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
  float b_R_c2b_comp[9];
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
  /*  替换掉eul2rotm */
  ct_idx_0 = cos(eulerCompens_xyz[0]);
  eulerCompens_xyz[0] = sin(eulerCompens_xyz[0]);
  ct_idx_1 = cos(eulerCompens_xyz[1]);
  eulerCompens_xyz[1] = sin(eulerCompens_xyz[1]);
  R_c2b_comp[0] = ct_idx_1;
  R_c2b_comp[3] = -ct_idx_1 * 0.0;
  R_c2b_comp[6] = eulerCompens_xyz[1];
  t = eulerCompens_xyz[0] * eulerCompens_xyz[1];
  R_c2b_comp[1] = ct_idx_0 * 0.0 + t;
  R_c2b_comp[4] = ct_idx_0 - t * 0.0;
  R_c2b_comp[7] = -ct_idx_1 * eulerCompens_xyz[0];
  t = ct_idx_0 * eulerCompens_xyz[1];
  R_c2b_comp[2] = eulerCompens_xyz[0] * 0.0 - t;
  R_c2b_comp[5] = eulerCompens_xyz[0] + t * 0.0;
  R_c2b_comp[8] = ct_idx_0 * ct_idx_1;
  /*  R_c2b0 = [0 1 0; 1 0 0; 0 0 -1]; */
  /*  x = eulerCompens_xyz(1); */
  /*  y = eulerCompens_xyz(2); */
  /*  z = 0; */
  /*  Rx = [1 0 0; 0 cos(x) -sin(x); 0 sin(x) cos(x)]; */
  /*  Ry = [cos(y) 0 sin(y); 0 1 0; -sin(y) 0 cos(y)]; */
  /*  Rz = [cos(z) -sin(z) 0; sin(z) cos(z) 0; 0 0 1]; */
  /*  R_c2b_comp = Rz*Ry*Rx; */
  for (lastBlockLength = 0; lastBlockLength < 3; lastBlockLength++) {
    d = R_c2b_comp[lastBlockLength];
    ct_idx_0 = R_c2b_comp[lastBlockLength + 3];
    ct_idx_1 = R_c2b_comp[lastBlockLength + 6];
    for (nblocks = 0; nblocks < 3; nblocks++) {
      b_R_c2b_comp[lastBlockLength + 3 * nblocks] =
          (float)((d * b[3 * nblocks] + ct_idx_0 * b[3 * nblocks + 1]) +
                  ct_idx_1 * b[3 * nblocks + 2]);
    }
  }
  emxInit_real32_T(&marker_xyz_imu, 2);
  firstBlockLength = fit_data_marker_location->size[0];
  lastBlockLength = marker_xyz_imu->size[0] * marker_xyz_imu->size[1];
  marker_xyz_imu->size[0] = fit_data_marker_location->size[0];
  marker_xyz_imu->size[1] = 3;
  emxEnsureCapacity_real32_T(marker_xyz_imu, lastBlockLength);
  marker_xyz_imu_data = marker_xyz_imu->data;
  for (lastBlockLength = 0; lastBlockLength < firstBlockLength;
       lastBlockLength++) {
    for (nblocks = 0; nblocks < 3; nblocks++) {
      marker_xyz_imu_data[lastBlockLength + marker_xyz_imu->size[0] * nblocks] =
          (b_R_c2b_comp[nblocks] *
               fit_data_marker_location_data[lastBlockLength] +
           b_R_c2b_comp[nblocks + 3] *
               fit_data_marker_location_data
                   [lastBlockLength + fit_data_marker_location->size[0]]) +
          b_R_c2b_comp[nblocks + 6] *
              fit_data_marker_location_data[lastBlockLength +
                                            fit_data_marker_location->size[0] *
                                                2];
    }
  }
  xpageoffset = marker_xyz_imu->size[0] - 1;
  emxInit_real32_T(&b_marker_xyz_imu, 2);
  lastBlockLength = b_marker_xyz_imu->size[0] * b_marker_xyz_imu->size[1];
  b_marker_xyz_imu->size[0] = fit_data_marker_location->size[0];
  b_marker_xyz_imu->size[1] = 3;
  emxEnsureCapacity_real32_T(b_marker_xyz_imu, lastBlockLength);
  b_marker_xyz_imu_data = b_marker_xyz_imu->data;
  for (lastBlockLength = 0; lastBlockLength < firstBlockLength;
       lastBlockLength++) {
    b_marker_xyz_imu_data[lastBlockLength] =
        marker_xyz_imu_data[lastBlockLength] - 0.108F;
  }
  for (lastBlockLength = 0; lastBlockLength <= xpageoffset; lastBlockLength++) {
    b_marker_xyz_imu_data[lastBlockLength + b_marker_xyz_imu->size[0]] =
        marker_xyz_imu_data[lastBlockLength + marker_xyz_imu->size[0]] + 0.033F;
  }
  for (lastBlockLength = 0; lastBlockLength <= xpageoffset; lastBlockLength++) {
    b_marker_xyz_imu_data[lastBlockLength + b_marker_xyz_imu->size[0] * 2] =
        marker_xyz_imu_data[lastBlockLength + marker_xyz_imu->size[0] * 2] +
        0.038F;
  }
  lastBlockLength = marker_xyz_imu->size[0] * marker_xyz_imu->size[1];
  marker_xyz_imu->size[0] = fit_data_marker_location->size[0];
  marker_xyz_imu->size[1] = 3;
  emxEnsureCapacity_real32_T(marker_xyz_imu, lastBlockLength);
  marker_xyz_imu_data = marker_xyz_imu->data;
  xpageoffset = b_marker_xyz_imu->size[0] * 3;
  for (lastBlockLength = 0; lastBlockLength < xpageoffset; lastBlockLength++) {
    marker_xyz_imu_data[lastBlockLength] =
        b_marker_xyz_imu_data[lastBlockLength];
  }
  emxFree_real32_T(&b_marker_xyz_imu);
  /*  1：imu系相对于ned的旋转矩阵R_b2e:
   * visual_data.imu_q_b2e、visual_data.marker_xyz_R_b2e */
  /*  2：marker_xyz 由vio坐标系c旋转到与imu坐标系b，再转到与ned原点坐标系e对齐
   */
  emxInit_real_T(&marker_xyz_ned, 2);
  lastBlockLength = marker_xyz_ned->size[0] * marker_xyz_ned->size[1];
  marker_xyz_ned->size[0] = fit_data_marker_location->size[0];
  marker_xyz_ned->size[1] = 3;
  emxEnsureCapacity_real_T(marker_xyz_ned, lastBlockLength);
  marker_xyz_ned_data = marker_xyz_ned->data;
  for (xpageoffset = 0; xpageoffset < firstBlockLength; xpageoffset++) {
    for (lastBlockLength = 0; lastBlockLength < 3; lastBlockLength++) {
      nblocks = lastBlockLength + 9 * xpageoffset;
      marker_xyz_ned_data[xpageoffset +
                          marker_xyz_ned->size[0] * lastBlockLength] =
          ((float)fit_data_R_b2e_data[nblocks] *
               marker_xyz_imu_data[xpageoffset] +
           (float)fit_data_R_b2e_data[nblocks + 3] *
               marker_xyz_imu_data[xpageoffset + marker_xyz_imu->size[0]]) +
          (float)fit_data_R_b2e_data[nblocks + 6] *
              marker_xyz_imu_data[xpageoffset + marker_xyz_imu->size[0] * 2];
    }
  }
  emxFree_real32_T(&marker_xyz_imu);
  /*  计算拟合误差和 */
  emxInit_real_T(&x, 2);
  if (fit_data_pe->size[0] == marker_xyz_ned->size[0]) {
    lastBlockLength = x->size[0] * x->size[1];
    x->size[0] = fit_data_pe->size[0];
    x->size[1] = 3;
    emxEnsureCapacity_real_T(x, lastBlockLength);
    xv_data = x->data;
    firstBlockLength = fit_data_pe->size[0] * 3;
    for (lastBlockLength = 0; lastBlockLength < firstBlockLength;
         lastBlockLength++) {
      xv_data[lastBlockLength] = fit_data_pe_data[lastBlockLength] -
                                 marker_xyz_ned_data[lastBlockLength];
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
    xpageoffset = x->size[0];
    firstBlockLength = fit_data_pe->size[0];
    lastBlockLength = x->size[0] * x->size[1];
    x->size[0] = fit_data_pe->size[0];
    x->size[1] = 3;
    emxEnsureCapacity_real_T(x, lastBlockLength);
    xv_data = x->data;
    for (lastBlockLength = 0; lastBlockLength < 3; lastBlockLength++) {
      for (nblocks = 0; nblocks < firstBlockLength; nblocks++) {
        xv_data[nblocks + x->size[0] * lastBlockLength] =
            fit_data_pe_data[nblocks + fit_data_pe->size[0] * lastBlockLength] -
            (marker_xyz_ned_data[nblocks +
                                 marker_xyz_ned->size[0] * lastBlockLength] +
             eulerCompens_xyz[lastBlockLength] / (double)xpageoffset);
      }
    }
    lastBlockLength = marker_xyz_ned->size[0] * marker_xyz_ned->size[1];
    marker_xyz_ned->size[0] = fit_data_pe->size[0];
    marker_xyz_ned->size[1] = 3;
    emxEnsureCapacity_real_T(marker_xyz_ned, lastBlockLength);
    marker_xyz_ned_data = marker_xyz_ned->data;
    firstBlockLength = x->size[0] * 3;
    for (lastBlockLength = 0; lastBlockLength < firstBlockLength;
         lastBlockLength++) {
      marker_xyz_ned_data[lastBlockLength] = xv_data[lastBlockLength];
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
    lastBlockLength = xv->size[0];
    xv->size[0] = xi;
    emxEnsureCapacity_real_T(xv, lastBlockLength);
    xv_data = xv->data;
    for (k = 0; k < xi; k++) {
      lastBlockLength = xpageoffset + k;
      xv_data[k] =
          marker_xyz_ned_data[lastBlockLength % marker_xyz_ned->size[0] +
                              marker_xyz_ned->size[0] *
                                  (lastBlockLength / marker_xyz_ned->size[0])];
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
