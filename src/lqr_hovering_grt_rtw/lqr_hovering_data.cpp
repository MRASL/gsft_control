/*
 * lqr_hovering_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_hovering".
 *
 * Model version              : 1.530
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Tue Jan 23 10:56:49 2018
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
  { -0.0, -0.0, 0.14142135623730739, -0.0, -0.0, -0.14142135623730809, -0.0,
    -0.0, 9.9999999999999609, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.15811388300841936 },

  /* Expression: Kx_lqr
   * Referenced by: '<Root>/                   '
   */
  { 0.0, 0.0, 0.28539255246474526, 0.0, 0.0, -0.27688002438732734, 0.0, 0.0,
    12.532362127200097, 0.0, 0.0, 0.0, 0.0, 0.0, 0.25261004031968776, 0.0, 0.0,
    -0.23568769837303044, 0.0, 0.0, 6.603005024364009, 0.0, 0.0, 0.0, 0.0,
    1.0895658919683064, 0.0, 0.0, 0.0, 0.0, 1.229083043763741, 0.0, 0.0, 0.0,
    0.0, 0.30355520549478648, 0.0, 0.27593216199282733, 0.0, 0.0, 0.0, 0.0,
    0.33647045997871744, 0.0, 0.0, 0.0, 0.0, 0.24395632222527322 },

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
