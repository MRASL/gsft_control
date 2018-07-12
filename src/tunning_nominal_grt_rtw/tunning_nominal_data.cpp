/*
 * tunning_nominal_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "tunning_nominal".
 *
 * Model version              : 1.1417
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Thu Jul 12 16:22:42 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */

#include "tunning_nominal.h"
#include "tunning_nominal_private.h"

/* Constant parameters (auto storage) */
const ConstP_tunning_nominal_T tunning_nominal_ConstP = {
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

  /* Pooled Parameter (Expression: Ib)
   * Referenced by:
   *   '<S2>/Constant1'
   *   '<S3>/Constant1'
   */
  { 0.0347563, 0.0, 0.0, 0.0, 0.0458929, 0.0, 0.0, 0.0, 0.0977 },

  /* Expression: M_bias'
   * Referenced by: '<S3>/Constant'
   */
  { -0.01, -0.04, 0.0 },

  /* Expression: pInitialization.M
   * Referenced by: '<S20>/KalmanGainM'
   */
  { 0.0030895047538052538, 0.0, 0.0, 0.0047799064396672154, 0.0, 0.0, 0.0,
    0.0030895047538037862, 0.0, 0.0, 0.00477990643966447, 0.0, 0.0, 0.0,
    0.0030895047538070665, 0.0, 0.0, 0.0047799064396702477 },

  /* Expression: pInitialization.C
   * Referenced by: '<S4>/C'
   */
  { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0 },

  /* Expression: pInitialization.A
   * Referenced by: '<S4>/A'
   */
  { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.001, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.001, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.001, 0.0, 0.0, 1.0 },

  /* Expression: pInitialization.L
   * Referenced by: '<S20>/KalmanGainL'
   */
  { 0.0030942846602449213, 0.0, 0.0, 0.0047799064396672154, 0.0, 0.0, 0.0,
    0.0030942846602434503, 0.0, 0.0, 0.00477990643966447, 0.0, 0.0, 0.0,
    0.0030942846602467367, 0.0, 0.0, 0.0047799064396702477 }
};
