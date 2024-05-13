/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_PSO_marker_extric_estimate_api.h
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 2024-05-13 17:23:46
 */

#ifndef _CODER_PSO_MARKER_EXTRIC_ESTIMATE_API_H
#define _CODER_PSO_MARKER_EXTRIC_ESTIMATE_API_H

/* Include Files */
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"
#include <string.h>

/* Type Definitions */
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T
struct emxArray_real_T {
  real_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};
#endif /* struct_emxArray_real_T */
#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T
typedef struct emxArray_real_T emxArray_real_T;
#endif /* typedef_emxArray_real_T */

#ifndef struct_emxArray_real32_T
#define struct_emxArray_real32_T
struct emxArray_real32_T {
  real32_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};
#endif /* struct_emxArray_real32_T */
#ifndef typedef_emxArray_real32_T
#define typedef_emxArray_real32_T
typedef struct emxArray_real32_T emxArray_real32_T;
#endif /* typedef_emxArray_real32_T */

#ifndef typedef_struct0_T
#define typedef_struct0_T
typedef struct {
  emxArray_real_T *pe;
  emxArray_real32_T *marker_location;
  emxArray_real_T *R_b2e;
} struct0_T;
#endif /* typedef_struct0_T */

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void PSO_marker_extric_estimate(struct0_T *fit_data, real_T bestPosition[2],
                                real_T *bestValue);

void PSO_marker_extric_estimate_api(const mxArray *prhs, int32_T nlhs,
                                    const mxArray *plhs[2]);

void PSO_marker_extric_estimate_atexit(void);

void PSO_marker_extric_estimate_initialize(void);

void PSO_marker_extric_estimate_terminate(void);

void PSO_marker_extric_estimate_xil_shutdown(void);

void PSO_marker_extric_estimate_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_PSO_marker_extric_estimate_api.h
 *
 * [EOF]
 */
