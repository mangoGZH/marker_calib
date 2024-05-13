/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: minOrMax.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 2024-05-13 17:23:46
 */

/* Include Files */
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : const double x[20]
 *                int *idx
 * Return Type  : double
 */
double minimum(const double x[20], int *idx)
{
  double ex;
  int k;
  if (!rtIsNaN(x[0])) {
    *idx = 1;
  } else {
    bool exitg1;
    *idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k < 21)) {
      if (!rtIsNaN(x[k - 1])) {
        *idx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }
  if (*idx == 0) {
    ex = x[0];
    *idx = 1;
  } else {
    int i;
    ex = x[*idx - 1];
    i = *idx + 1;
    for (k = i; k < 21; k++) {
      double d;
      d = x[k - 1];
      if (ex > d) {
        ex = d;
        *idx = k;
      }
    }
  }
  return ex;
}

/*
 * File trailer for minOrMax.c
 *
 * [EOF]
 */
