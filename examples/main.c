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

#define MAX_ROWS 200  // 最大行数
#define NUM_COLUMNS 15 // 列数

/* Function Declarations */
static emxArray_real_T *argInit_3x3xUnbounded_real_T(void);

static emxArray_real32_T *argInit_Unboundedx3_real32_T(void);

static emxArray_real_T *argInit_Unboundedx3_real_T(void);

static float argInit_real32_T(void);

static double argInit_real_T(void);

static struct0_T argInit_struct0_T(void);

static Result argInit_Result(void);

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : emxArray_real_T *
 */
static emxArray_real_T *argInit_3x3xUnbounded_real_T(void)
{
  emxArray_real_T *result;
  double *result_data;
  int iv[3] = {3, 3, MAX_ROWS};
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
        result_data[(idx1 + 3 * idx0) + 9 * idx2] = argInit_real_T();
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
  result = emxCreate_real32_T(MAX_ROWS, 3);
  result_data = result->data;
  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
    for (idx1 = 0; idx1 < 3; idx1++) {
      /* Set the value of the array element.
Change this value to the value that the application requires. */
      // result_data[idx0 + result->size[0] * idx1] = argInit_real32_T();
      result_data[idx1 + result->size[1] * idx0] = argInit_real32_T();
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
  result = emxCreate_real_T(MAX_ROWS, 3);
  result_data = result->data;
  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
    for (idx1 = 0; idx1 < 3; idx1++) {
      /* Set the value of the array element.
Change this value to the value that the application requires. */
      // result_data[idx0 + result->size[0] * idx1] = argInit_real_T();   //
      // 按列排列
      result_data[idx1 + result->size[1] * idx0] = argInit_real_T(); // 按行排列
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

  // 导入txt文件数据
  FILE *file;
  file = fopen("..\\datasets\\fit_data.txt", "r");
  printf("STEP 1: load txt ...\n");
  if (file == NULL) {
    printf("Error opening file\n");
    return result;
  }

  // 读取文件中的数据
  double data[MAX_ROWS][NUM_COLUMNS]; // 存储数据的数组
  int row_count = 0;                  // 行计数器
                                      // 逐行读取文件中的数据
  char line[256];
  while (fgets(line, sizeof(line), file)) {

    char *token = strtok(line, ","); // 将逗号分隔的字符串拆分为各个数据
    int column_count = 0;            // 列计数器

    while (token != NULL && column_count < NUM_COLUMNS) {
      double cur_value = atof(token); // 将字符串转换为浮点数并存储在数组中
      data[row_count][column_count] = cur_value;

      if (column_count < 3) {
        result.pe->data[column_count + row_count * 3] = cur_value;                    // 按行排列
        // printf("STEP2: %.6f\n", result.pe->data[column_count + row_count * 3]);

      } else if (column_count < 6) {
        result.marker_location->data[column_count - 3 + row_count * 3] =  cur_value;  // 按行排列
        // printf("STEP3: %.6f\n", result.marker_location->data[column_count - 3 + row_count * 3]);

      } else {
        int idx0 = (column_count - 6) / 3;  // 商
        int idx1 = (column_count - 6) % 3;  // 余数
        result.R_b2e->data[(idx1 + 3 * idx0) + 9 * row_count] = cur_value;
        // printf("STEP4: %.6f\n", result.R_b2e->data[(idx1 + 3 * idx0) + 9 * row_count]);
      }

      token = strtok(NULL, ",");
      column_count++;
      // printf("col: %d\n", column_count);
    }
    row_count++;
    printf("row: %d\n", row_count);
    result.pe->size[0] = row_count;
    result.marker_location->size[0] = row_count;
    result.R_b2e->size[0] = row_count;
  }

  fclose(file);

  // 遍历数据并输出
  // for (int i = 0; i < row_count; i++) {
  //   for (int j = 0; j < NUM_COLUMNS; j++) {
  //     printf("%.6f ", data[i][j]);
  //   }
  //   printf("\n");
  // }

  // printf(result);
  return result;
}

/*
 * Arguments    : void
 * Return Type  : Result
 */
static Result argInit_Result(void)
{
  Result result;
  /* Set the value of each structure field.
    Change this value to the value that the application requires. */
  // Set all data to zero
  memset(&result, 0, sizeof(Result));

  // 导入txt文件数据
  FILE *file;
  file = fopen("..\\datasets\\fit_data.txt", "r");
  printf("【1: load txt ...】\n");
  if (file == NULL) {
    printf("Error opening file\n");
    return result;
  }

  // 读取文件中的数据
  double data[MAX_ROWS][NUM_COLUMNS]; // 存储数据的数组
  int row_count = 0;                  // 行计数器
                                      // 逐行读取文件中的数据
  char line[256];
  while (fgets(line, sizeof(line), file)) {

    char *token = strtok(line, ","); // 将逗号分隔的字符串拆分为各个数据
    int column_count = 0;            // 列计数器

    while (token != NULL && column_count < NUM_COLUMNS) {
      double cur_value = atof(token); // 将字符串转换为浮点数并存储在数组中
      data[row_count][column_count] = cur_value;

      if (column_count < 3) {
        result.pe[row_count][column_count] = cur_value;
      } else if (column_count < 6) {
        result.marker_location[row_count][column_count - 3] = cur_value;
      } else {
        result.R_b2e[row_count][column_count - 6] = cur_value;
      }

      token = strtok(NULL, ",");
      column_count++;
    }
    row_count++;
  }

  fclose(file);

  // 遍历数据并输出
  for (int i = 0; i < row_count; i++) {
    for (int j = 0; j < NUM_COLUMNS; j++) {
      printf("%.6f ", data[i][j]);
    }
    printf("\n");
  }
  // 打印读取的数据
  for (int i = 0; i < row_count; i++) {
    printf("pe: %lf, %lf, %lf\n", result.pe[i][0], result.pe[i][1],
           result.pe[i][2]);
    printf("marker_location: %lf, %lf, %lf\n", result.marker_location[i][0],
           result.marker_location[i][1], result.marker_location[i][2]);
    printf("R_b2e: %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf\n",
           result.R_b2e[i][0], result.R_b2e[i][1], result.R_b2e[i][2],
           result.R_b2e[i][3], result.R_b2e[i][4], result.R_b2e[i][5],
           result.R_b2e[i][6], result.R_b2e[i][7], result.R_b2e[i][8]);
  }

  // print(result);
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
  // Result fit_data;
  double bestPosition[2];
  double bestValue;
  /* Initialize function 'PSO_marker_extric_estimate' input arguments. */
  /* Initialize function input argument 'fit_data'. */
  fit_data = argInit_struct0_T(); // fit_data = argInit_Result();
  /* Call the entry-point 'PSO_marker_extric_estimate'. */
  // PSO_marker_extric_estimate(&fit_data, bestPosition, &bestValue);
  PSO_marker_extric_estimate_handle(&fit_data, bestPosition, &bestValue);

  /*  打印最优结果 */
  printf("STEP7:bestPosition[0]= %f\n", bestPosition[0]);
  printf("STEP7:bestPosition[1]= %f\n", bestPosition[1]);
  printf("STEP7:best_fit_error = %f\n", bestValue);
  emxDestroy_struct0_T(fit_data);
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
