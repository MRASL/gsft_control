/*
 * lqr_inner_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_inner".
 *
 * Model version              : 1.465
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Wed Dec 20 11:54:17 2017
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Passed (1), Warnings (3), Error (0)
 */

#include "lqr_inner.h"
#include "lqr_inner_private.h"

/* Constant parameters (auto storage) */
const ConstP_lqr_inner_T lqr_inner_ConstP = {
  /* Expression: Ki_lqr
   * Referenced by: '<Root>/ '
   */
  { 8.6602540378444033, -0.0, -0.0, -0.0, 0.099999999999999867, -0.0, -0.0, -0.0,
    0.1 },

  /* Expression: Kx_lqr
   * Referenced by: '<Root>/                   '
   */
  { 13.658801770892236, 0.0, 0.0, 7.8844607340479707, 0.0, 0.0, 0.0,
    0.18279822662348033, 0.0, 0.0, 0.0, 0.19334861401762837, 0.0,
    0.11707595828344657, 0.0, 0.0, 0.0, 0.13691843271268928 },

  /* Expression: [mass*gra 0 0]'
   * Referenced by: '<Root>/              '
   */
  { 15.136564275, 0.0, 0.0 },

  /* Expression: B_inner_inv
   * Referenced by: '<Root>/Gain'
   */
  { 0.16666666666666674, 0.16666666666666669, 0.16666666666666671,
    0.16666666666666671, 0.16666666666666674, 0.16666666666666671,
    0.77519379844961256, 1.5503875968992245, 0.77519379844961245,
    -0.77519379844961211, -1.5503875968992251, -0.77519379844961223,
    -1.3426750446270364, 2.9933074321285893E-16, 1.3426750446270364,
    1.3426750446270364, -2.8139041658176531E-16, -1.3426750446270366 }
};
