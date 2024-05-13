/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: PSO_marker_extric_estimate_initialize.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 2024-05-13 17:23:46
 */

/* Include Files */
#include "PSO_marker_extric_estimate_initialize.h"
#include "PSO_marker_extric_estimate_data.h"
#include "eml_rand_mt19937ar_stateful.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
void PSO_marker_extric_estimate_initialize(void)
{
  c_eml_rand_mt19937ar_stateful_i();
  isInitialized_PSO_marker_extric_estimate = true;
}

/*
 * File trailer for PSO_marker_extric_estimate_initialize.c
 *
 * [EOF]
 */
