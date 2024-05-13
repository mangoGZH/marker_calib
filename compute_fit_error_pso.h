/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: compute_fit_error_pso.h
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 2024-05-13 17:23:46
 */

#ifndef COMPUTE_FIT_ERROR_PSO_H
#define COMPUTE_FIT_ERROR_PSO_H

/* Include Files */
#include "PSO_marker_extric_estimate_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
double compute_fit_error_pso(const double params[2],
                             const emxArray_real_T *fit_data_pe,
                             const emxArray_real32_T *fit_data_marker_location,
                             const emxArray_real_T *fit_data_R_b2e);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for compute_fit_error_pso.h
 *
 * [EOF]
 */
