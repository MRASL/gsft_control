/*
 * lqr_outer_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_outer".
 *
 * Model version              : 1.577
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Mon Jan 22 21:27:37 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Passed (1), Warnings (3), Error (0)
 */

#include "lqr_outer.h"
#include "lqr_outer_private.h"

/* Constant parameters (auto storage) */
const ConstP_lqr_outer_T lqr_outer_ConstP = {
  /* Expression: [mass*gra 0 0 0]'
   * Referenced by: '<S1>/              '
   */
  { 15.107400000000002, 0.0, 0.0, 0.0 },

  /* Expression: Ki_lqr
   * Referenced by: '<S1>/ '
   */
  { 7.0710678118654657, -0.0, -0.0, -0.0, -0.0, 1.2247448713915894, -0.0, -0.0,
    -0.0, -0.0, 1.2247448713915881, -0.0, -0.0, -0.0, -0.0, 0.038729833462074231
  },

  /* Expression: Kx_lqr
   * Referenced by: '<S1>/                   '
   */
  { 11.883389918474116, 0.0, 0.0, 0.0, 6.4498713901054092, 0.0, 0.0, 0.0, 0.0,
    0.8653145603148511, 0.0, 0.0, 0.0, 0.0, 0.92430500464371423, 0.0, 0.0, 0.0,
    0.0, 0.1199289782321971, 0.0, 0.26485895285102656, 0.0, 0.0, 0.0, 0.0,
    0.30795790994099653, 0.0, 0.0, 0.0, 0.0, 0.15340835161936686 },

  /* Expression: B_ENU_inv
   * Referenced by: '<Root>/Gain'
   */
  { 0.16666666666666674, 0.16666666666666669, 0.16666666666666671,
    0.16666666666666671, 0.16666666666666674, 0.16666666666666671,
    0.77519379844962388, 1.5503875968992147, 0.77519379844962344,
    -0.77519379844962344, -1.5503875968992149, -0.77519379844962344,
    -1.3426750446270113, -2.5529533974250051E-14, 1.3426750446270619,
    1.3426750446270113, 2.5418511671787539E-14, -1.3426750446270626,
    -4.5662100456621, 4.5662100456621, -4.5662100456620989, 4.5662100456620971,
    -4.5662100456621006, 4.5662100456620989 },

  /* Expression: Kxo_lqr
   * Referenced by: '<S3>/                   '
   */
  { 0.3932006775227388, 0.0, 0.0, 0.39320067752273841, 0.88684911627935814, 0.0,
    0.0, 0.88684911627935636 }
};
