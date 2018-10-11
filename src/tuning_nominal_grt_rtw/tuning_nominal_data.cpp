/*
 * tuning_nominal_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "tuning_nominal".
 *
 * Model version              : 1.1505
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Thu Oct 11 16:37:28 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Passed (1), Warnings (3), Error (0)
 */

#include "tuning_nominal.h"
#include "tuning_nominal_private.h"

/* Constant parameters (auto storage) */
const ConstP_tuning_nominal_T tuning_nominal_ConstP = {
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

  /* Expression: M_bias'
   * Referenced by: '<S2>/Constant'
   */
  { -0.005, -0.04, 0.0 },

  /* Expression: Ib
   * Referenced by: '<S2>/Constant1'
   */
  { 0.0347563, 0.0, 0.0, 0.0, 0.0458929, 0.0, 0.0, 0.0, 0.0977 },

  /* Expression: pInitialization.M
   * Referenced by: '<S11>/KalmanGainM'
   */
  { 0.0068951521934753892, 0.0, 0.0, 0.00477077420942562, 0.0, 0.0, 0.0,
    0.0068951521934776322, 0.0, 0.0, 0.0047707742094272752, 0.0, 0.0, 0.0,
    0.0027474723704753777, 0.0, 0.0, 0.00075589920585899834 },

  /* Expression: pInitialization.C
   * Referenced by: '<S3>/C'
   */
  { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0 },

  /* Expression: pInitialization.A
   * Referenced by: '<S3>/A'
   */
  { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.005, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.005, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.005, 0.0, 0.0, 1.0 },

  /* Expression: pInitialization.L
   * Referenced by: '<S11>/KalmanGainL'
   */
  { 0.0069190060645225177, 0.0, 0.0, 0.00477077420942562, 0.0, 0.0, 0.0,
    0.0069190060645247693, 0.0, 0.0, 0.0047707742094272752, 0.0, 0.0, 0.0,
    0.0027512518665046728, 0.0, 0.0, 0.00075589920585899834 }
};
