/*
 * lqr_hovering_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_hovering".
 *
 * Model version              : 1.528
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Mon Jan 22 21:11:27 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Passed (1), Warnings (3), Error (0)
 */

#include "lqr_hovering.h"
#include "lqr_hovering_private.h"

/* Constant parameters (auto storage) */
const ConstP_lqr_hovering_T lqr_hovering_ConstP = {
  /* Expression: [mass*gra 0 0 0]'
   * Referenced by: '<Root>/              '
   */
  { 15.107400000000002, 0.0, 0.0, 0.0 },

  /* Expression: Ki_lqr
   * Referenced by: '<Root>/ '
   */
  { -0.0, -0.0, 0.099999999999998174, -0.0, -0.0, -0.10000000000000012, -0.0,
    -0.0, 7.07106781186548, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.038729833462074086 },

  /* Expression: Kx_lqr
   * Referenced by: '<Root>/                   '
   */
  { 0.0, 0.0, 0.20321116122405544, 0.0, 0.0, -0.19600780490898728, 0.0, 0.0,
    10.566690931243379, 0.0, 0.0, 0.0, 0.0, 0.0, 0.18647388023014985, 0.0, 0.0,
    -0.172095297926199, 0.0, 0.0, 6.1274307885303516, 0.0, 0.0, 0.0, 0.0,
    0.85600399993994147, 0.0, 0.0, 0.0, 0.0, 0.97738473065495857, 0.0, 0.0, 0.0,
    0.0, 0.12045404308765076, 0.0, 0.2447510237899424, 0.0, 0.0, 0.0, 0.0,
    0.30018334299382687, 0.0, 0.0, 0.0, 0.0, 0.15503780190433233 },

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
    -4.5662100456621006, 4.5662100456620989 }
};
