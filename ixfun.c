/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: ixfun.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 2024-04-29 11:40:58
 */

/* Include Files */
#include "ixfun.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : const double a[40]
 *                double c[40]
 * Return Type  : void
 */
void expand_max(const double a[40], double c[40])
{
  int i;
  for (i = 0; i < 40; i++) {
    c[i] = fmax(a[i], -10.0);
  }
}

/*
 * Arguments    : const double a[40]
 *                double c[40]
 * Return Type  : void
 */
void expand_min(const double a[40], double c[40])
{
  int i;
  for (i = 0; i < 40; i++) {
    c[i] = fmin(a[i], 10.0);
  }
}

/*
 * File trailer for ixfun.c
 *
 * [EOF]
 */
