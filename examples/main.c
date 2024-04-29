/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: main.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 2024-04-29 11:40:58
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

/* Include Files */
#include "main.h"
#include "PSO_marker_extric_estimate.h"
#include "PSO_marker_extric_estimate_emxAPI.h"
#include "PSO_marker_extric_estimate_terminate.h"
#include "PSO_marker_extric_estimate_types.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static emxArray_real_T *argInit_3x3xUnbounded_real_T(void);

static emxArray_real32_T *argInit_Unboundedx3_real32_T(void);

static emxArray_real_T *argInit_Unboundedx3_real_T(void);

static float argInit_real32_T(void);

static double argInit_real_T(void);

static struct0_T argInit_struct0_T(void);

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : emxArray_real_T *
 */
static emxArray_real_T *argInit_3x3xUnbounded_real_T(void)
{
  emxArray_real_T *result;
  double *result_data;
  int iv[3] = {3, 3, 2};
  int idx0;
  int idx1;
  int idx2;
  /* Set the size of the array.
Change this size to the value that the application requires. */
  result = emxCreateND_real_T(3, &iv[0]);
  result_data = result->data;
  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 3; idx0++) {
    for (idx1 = 0; idx1 < 3; idx1++) {
      for (idx2 = 0; idx2 < result->size[2U]; idx2++) {
        /* Set the value of the array element.
Change this value to the value that the application requires. */
        result_data[(idx0 + 3 * idx1) + 9 * idx2] = argInit_real_T();
      }
    }
  }
  return result;
}

/*
 * Arguments    : void
 * Return Type  : emxArray_real32_T *
 */
static emxArray_real32_T *argInit_Unboundedx3_real32_T(void)
{
  emxArray_real32_T *result;
  float *result_data;
  int idx0;
  int idx1;
  /* Set the size of the array.
Change this size to the value that the application requires. */
  result = emxCreate_real32_T(2, 3);
  result_data = result->data;
  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
    for (idx1 = 0; idx1 < 3; idx1++) {
      /* Set the value of the array element.
Change this value to the value that the application requires. */
      result_data[idx0 + result->size[0] * idx1] = argInit_real32_T();
    }
  }
  return result;
}

/*
 * Arguments    : void
 * Return Type  : emxArray_real_T *
 */
static emxArray_real_T *argInit_Unboundedx3_real_T(void)
{
  emxArray_real_T *result;
  double *result_data;
  int idx0;
  int idx1;
  /* Set the size of the array.
Change this size to the value that the application requires. */
  result = emxCreate_real_T(2, 3);
  result_data = result->data;
  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
    for (idx1 = 0; idx1 < 3; idx1++) {
      /* Set the value of the array element.
Change this value to the value that the application requires. */
      result_data[idx0 + result->size[0] * idx1] = argInit_real_T();
    }
  }
  return result;
}

/*
 * Arguments    : void
 * Return Type  : float
 */
static float argInit_real32_T(void)
{
  return 0.0F;
}

/*
 * Arguments    : void
 * Return Type  : double
 */
static double argInit_real_T(void)
{
  return 0.0;
}

/*
 * Arguments    : void
 * Return Type  : struct0_T
 */
static struct0_T argInit_struct0_T(void)
{
  struct0_T result;
  /* Set the value of each structure field.
Change this value to the value that the application requires. */
  result.pe = argInit_Unboundedx3_real_T();
  result.marker_location = argInit_Unboundedx3_real32_T();
  result.R_b2e = argInit_3x3xUnbounded_real_T();
  return result;
}

/*
 * Arguments    : int argc
 *                char **argv
 * Return Type  : int
 */
int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  /* The initialize function is being called automatically from your entry-point
   * function. So, a call to initialize is not included here. */
  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_PSO_marker_extric_estimate();
  
  /* Terminate the application.
     You do not need to do this more than one time. */
  PSO_marker_extric_estimate_terminate();
  return 0;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void main_PSO_marker_extric_estimate(void)
{
  struct0_T fit_data;
  double bestPosition[2];
  double bestValue;
  /* Initialize function 'PSO_marker_extric_estimate' input arguments. */
  /* Initialize function input argument 'fit_data'. */
  fit_data = argInit_struct0_T();
  /* Call the entry-point 'PSO_marker_extric_estimate'. */
  PSO_marker_extric_estimate(&fit_data, bestPosition, &bestValue);
  emxDestroy_struct0_T(fit_data);
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
