/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: PSO_marker_extric_estimate.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 2024-05-13 17:23:46
 */

/* Include Files */
#include "PSO_marker_extric_estimate.h"
#include "PSO_marker_extric_estimate_data.h"
#include "PSO_marker_extric_estimate_emxutil.h"
#include "PSO_marker_extric_estimate_initialize.h"
#include "PSO_marker_extric_estimate_types.h"
#include "compute_fit_error_pso.h"
#include "ixfun.h"
#include "minOrMax.h"
#include "rand.h"
#include "rt_nonfinite.h"
#include <stddef.h>
#include <stdio.h>

/* Function Definitions */
/*
 * 函数功能：粒子群算法，估计相机外参姿态角
 *  输入fit_data：pe[导航融合位置]、marker_location[marker观测数据]、R_b2e[观测更新时刻b系到ned系的旋转矩阵]
 *  输出bestPosition、bestValue：最优相机外参roll\pitch估计值与最小拟合误差值
 *
 * Arguments    : const struct0_T *fit_data
 *                double bestPosition[2]
 *                double *bestValue
 * Return Type  : void
 */
void PSO_marker_extric_estimate(const struct0_T *fit_data,
                                double bestPosition[2], double *bestValue)
{
  emxArray_char_T *b_str;
  emxArray_char_T *c_str;
  emxArray_char_T *str;
  double personalBest[40];
  double swarm[40];
  double velocity[40];
  double personalBestValue[20];
  double b_swarm[2];
  double best_fit_error;
  int i;
  int i1;
  int iter;
  int nbytes;
  char *str_data;
  if (!isInitialized_PSO_marker_extric_estimate) {
    PSO_marker_extric_estimate_initialize();
  }
  /*  主函数 */
  /*  粒子维度 */
  /*  粒子群大小 */
  /*  最大迭代次数 */
  /*  搜索空间下界 */
  /*  搜索空间上界 */
  /*  开始计时 */
  /*  tic */
  /*  调用PSO算法 */
  /*  [bestPosition, bestValue, error_data] = PSO(@compute_fit_error_pso,
   * fit_data, error_data, dim, swarmSize, maxIterations, lb, ub); */
  /*  初始化粒子群 */
  b_rand(swarm);
  for (i = 0; i < 40; i++) {
    best_fit_error = swarm[i] * 20.0 - 10.0;
    swarm[i] = best_fit_error;
    velocity[i] = 0.0;
    personalBest[i] = best_fit_error;
  }
  for (nbytes = 0; nbytes < 20; nbytes++) {
    /*  personalBestValue(i) = feval(targetFunction, swarm(i,:),fit_data); */
    b_swarm[0] = swarm[nbytes];
    b_swarm[1] = swarm[nbytes + 20];
    personalBestValue[nbytes] = compute_fit_error_pso(
        b_swarm, fit_data->pe, fit_data->marker_location, fit_data->R_b2e);
    /*      disp(strcat('roll/pitch:',num2str(swarm(i,:)),'personalBestValue:
     * ',num2str(personalBestValue(i)))); */
  }
  /*  寻找全局最优 */
  *bestValue = minimum(personalBestValue, &nbytes);
  bestPosition[0] = swarm[nbytes - 1];
  bestPosition[1] = swarm[nbytes + 19];
  /*  迭代更新粒子位置和速度 */
  for (iter = 0; iter < 10; iter++) {
    double r1[40];
    double r2[40];
    /*  更新粒子位置和速度 */
    b_rand(r1);
    b_rand(r2);
    /*  速度更新公式:v_new = w∗v + c1∗r1∗(pbest−x) + c2∗r2∗(gbest−x) */
    for (i = 0; i < 2; i++) {
      for (i1 = 0; i1 < 20; i1++) {
        nbytes = i1 + 20 * i;
        best_fit_error = swarm[nbytes];
        velocity[nbytes] =
            (0.5 * velocity[nbytes] +
             1.5 * r1[nbytes] * (personalBest[nbytes] - best_fit_error)) +
            2.0 * r2[nbytes] * (bestPosition[i] - best_fit_error);
      }
    }
    /*  边界处理 */
    for (i = 0; i < 40; i++) {
      swarm[i] += velocity[i];
    }
    expand_max(swarm, r1);
    expand_min(r1, swarm);
    /*  更新个体最优 */
    for (nbytes = 0; nbytes < 20; nbytes++) {
      double currentValue;
      double swarm_tmp;
      best_fit_error = swarm[nbytes];
      b_swarm[0] = best_fit_error;
      swarm_tmp = swarm[nbytes + 20];
      b_swarm[1] = swarm_tmp;
      currentValue = compute_fit_error_pso(
          b_swarm, fit_data->pe, fit_data->marker_location, fit_data->R_b2e);
      if (currentValue < personalBestValue[nbytes]) {
        personalBest[nbytes] = best_fit_error;
        personalBest[nbytes + 20] = swarm_tmp;
        personalBestValue[nbytes] = currentValue;
      }
      /*  添加误差数据到矩阵 */
    }
    /*  更新全局最优 */
    best_fit_error = minimum(personalBestValue, &nbytes);
    if (best_fit_error < *bestValue) {
      *bestValue = best_fit_error;
      bestPosition[0] = personalBest[nbytes - 1];
      bestPosition[1] = personalBest[nbytes + 19];
    }
  }
  /*  返回最优解和最优值 */
  /*  结束计时并输出运行时间 */
  /*  elapsedTime = toc; */
  /*  fprintf('算法运行时间：%.2f 秒\n', elapsedTime); */
  /*  计算最优拟合误差和 */
  best_fit_error = compute_fit_error_pso(
      bestPosition, fit_data->pe, fit_data->marker_location, fit_data->R_b2e);
  /*  打印最优结果 */
  nbytes = (int)snprintf(NULL, 0, "%f", bestPosition[0]) + 1;
  emxInit_char_T(&str);
  i = str->size[0] * str->size[1];
  str->size[0] = 1;
  str->size[1] = nbytes;
  emxEnsureCapacity_char_T(str, i);
  str_data = str->data;
  snprintf(&str_data[0], (size_t)nbytes, "%f", bestPosition[0]);
  emxFree_char_T(&str);
  nbytes = (int)snprintf(NULL, 0, "%f", bestPosition[1]) + 1;
  emxInit_char_T(&b_str);
  i = b_str->size[0] * b_str->size[1];
  b_str->size[0] = 1;
  b_str->size[1] = nbytes;
  emxEnsureCapacity_char_T(b_str, i);
  str_data = b_str->data;
  snprintf(&str_data[0], (size_t)nbytes, "%f", bestPosition[1]);
  emxFree_char_T(&b_str);
  nbytes = (int)snprintf(NULL, 0, "%f", best_fit_error) + 1;
  emxInit_char_T(&c_str);
  i = c_str->size[0] * c_str->size[1];
  c_str->size[0] = 1;
  c_str->size[1] = nbytes;
  emxEnsureCapacity_char_T(c_str, i);
  str_data = c_str->data;
  snprintf(&str_data[0], (size_t)nbytes, "%f", best_fit_error);
  emxFree_char_T(&c_str);
  /*  提取误差数据的分量 */
  /*  绘制三维散点图 */
  /*  添加颜色条以显示误差大小 */
  /*  添加标题和坐标轴标签 */
}

/*
 * File trailer for PSO_marker_extric_estimate.c
 *
 * [EOF]
 */
