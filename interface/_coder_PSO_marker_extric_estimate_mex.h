/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_PSO_marker_extric_estimate_mex.h
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 2024-04-29 11:40:58
 */

#ifndef _CODER_PSO_MARKER_EXTRIC_ESTIMATE_MEX_H
#define _CODER_PSO_MARKER_EXTRIC_ESTIMATE_MEX_H

/* Include Files */
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
MEXFUNCTION_LINKAGE void mexFunction(int32_T nlhs, mxArray *plhs[],
                                     int32_T nrhs, const mxArray *prhs[]);

emlrtCTX mexFunctionCreateRootTLS(void);

void unsafe_PSO_marker_extric_estimate_mexFunction(int32_T nlhs,
                                                   mxArray *plhs[2],
                                                   int32_T nrhs,
                                                   const mxArray *prhs[1]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_PSO_marker_extric_estimate_mex.h
 *
 * [EOF]
 */
