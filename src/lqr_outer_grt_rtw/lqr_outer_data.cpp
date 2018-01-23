/*
 * lqr_outer_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_outer".
 *
 * Model version              : 1.576
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Mon Jan 22 19:32:41 2018
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
  { 7.0710678118654755, -0.0, -0.0, -0.0, -0.0, 9.999999999999968, -0.0, -0.0,
    -0.0, -0.0, 9.9999999999999769, -0.0, -0.0, -0.0, -0.0, 0.14142135623730967
  },

  /* Expression: Kx_lqr
   * Referenced by: '<S1>/                   '
   */
  { 11.883389918474132, 0.0, 0.0, 0.0, 6.449871390105403, 0.0, 0.0, 0.0, 0.0,
    3.5793968210502585, 0.0, 0.0, 0.0, 0.0, 3.7932985865056703, 0.0, 0.0, 0.0,
    0.0, 0.29806543113634354, 0.0, 0.5906040801272362, 0.0, 0.0, 0.0, 0.0,
    0.66945570831929591, 0.0, 0.0, 0.0, 0.0, 0.24339676506486571 },

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
  { 0.99654678621289183, 0.0, 0.0, 0.996546786212891, 1.4121237808442229, 0.0,
    0.0, 1.4121237808442224 }
};
