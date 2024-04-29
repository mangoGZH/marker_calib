/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: PSO_marker_extric_estimate_emxAPI.h
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 2024-04-29 11:40:58
 */

#ifndef PSO_MARKER_EXTRIC_ESTIMATE_EMXAPI_H
#define PSO_MARKER_EXTRIC_ESTIMATE_EMXAPI_H

/* Include Files */
#include "PSO_marker_extric_estimate_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern emxArray_real32_T *emxCreateND_real32_T(int numDimensions,
                                               const int *size);

extern emxArray_real_T *emxCreateND_real_T(int numDimensions, const int *size);

extern emxArray_real32_T *
emxCreateWrapperND_real32_T(float *data, int numDimensions, const int *size);

extern emxArray_real_T *
emxCreateWrapperND_real_T(double *data, int numDimensions, const int *size);

extern emxArray_real32_T *emxCreateWrapper_real32_T(float *data, int rows,
                                                    int cols);

extern emxArray_real_T *emxCreateWrapper_real_T(double *data, int rows,
                                                int cols);

extern emxArray_real32_T *emxCreate_real32_T(int rows, int cols);

extern emxArray_real_T *emxCreate_real_T(int rows, int cols);

extern void emxDestroyArray_real32_T(emxArray_real32_T *emxArray);

extern void emxDestroyArray_real_T(emxArray_real_T *emxArray);

extern void emxDestroy_struct0_T(struct0_T emxArray);

extern void emxInit_struct0_T(struct0_T *pStruct);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for PSO_marker_extric_estimate_emxAPI.h
 *
 * [EOF]
 */
