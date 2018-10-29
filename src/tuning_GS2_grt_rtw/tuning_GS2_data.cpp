/*
 * tuning_GS2_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "tuning_GS2".
 *
 * Model version              : 1.2316
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Mon Oct 29 11:06:21 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Passed (1), Warnings (3), Error (0)
 */

#include "tuning_GS2.h"
#include "tuning_GS2_private.h"

/* Constant parameters (auto storage) */
const ConstP_tuning_GS2_T tuning_GS2_ConstP = {
  /* Expression: M_bias'
   * Referenced by: '<S3>/Constant'
   */
  { -0.005, -0.04, 0.0 },

  /* Expression: Ib
   * Referenced by: '<S3>/Constant1'
   */
  { 0.0347563, 0.0, 0.0, 0.0, 0.0458929, 0.0, 0.0, 0.0, 0.0977 },

  /* Expression: pInitialization.M
   * Referenced by: '<S24>/KalmanGainM'
   */
  { 0.0013828503617152289, 0.0, 0.0, 0.000956799230965245, 0.0, 0.0, 0.0,
    0.001382850361721501, 0.0, 0.0, 0.00095679923096881356, 0.0, 0.0, 0.0,
    0.00055009940149860072, 0.0, 0.0, 0.00015134630638216127 },

  /* Expression: pInitialization.C
   * Referenced by: '<S5>/C'
   */
  { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0 },

  /* Expression: Trans
   * Referenced by: '<S4>/Control Allocation'
   */
  { 0.16666666666666666, 0.125, 0.25, 0.16666666666666666, 0.16666666666666666,
    0.25, 0.0, 0.16666666666666666, 0.16666666666666666, 0.125, 0.25,
    0.16666666666666666, 0.16666666666666666, 0.125, 0.25, 0.16666666666666666,
    0.16666666666666666, 0.25, 0.0, 0.16666666666666666, 0.16666666666666666,
    0.125, 0.25, 0.16666666666666666 },

  /* Expression: B_ENU_inv
   * Referenced by: '<Root>/Control Allocation'
   */
  { 0.16666666666666674, 0.16666666666666669, 0.16666666666666671,
    0.16666666666666671, 0.16666666666666674, 0.16666666666666671,
    0.77519379844962388, 1.5503875968992147, 0.77519379844962344,
    -0.77519379844962344, -1.5503875968992149, -0.77519379844962344,
    -1.3426750446270113, -2.5529533974250051E-14, 1.3426750446270619,
    1.3426750446270113, 2.5418511671787539E-14, -1.3426750446270626,
    -4.5662100456621, 4.5662100456621, -4.5662100456620989, 4.5662100456620971,
    -4.5662100456621006, 4.5662100456620989 },

  /* Expression: pInitialization.A
   * Referenced by: '<S5>/A'
   */
  { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.001, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.001, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.001, 0.0, 0.0, 1.0 },

  /* Expression: pInitialization.L
   * Referenced by: '<S24>/KalmanGainL'
   */
  { 0.001383807160946194, 0.0, 0.0, 0.000956799230965245, 0.0, 0.0, 0.0,
    0.0013838071609524698, 0.0, 0.0, 0.00095679923096881356, 0.0, 0.0, 0.0,
    0.00055025074780498283, 0.0, 0.0, 0.00015134630638216127 }
};
