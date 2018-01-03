/*
 * lqr_outer_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_outer".
 *
 * Model version              : 1.466
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Wed Dec 20 17:57:48 2017
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
  /* Expression: Ki_lqr
   * Referenced by: '<Root>/ '
   */
  { -0.0, -0.0, 0.099999999999999728, -0.0, -0.099999999999999714, -0.0,
    8.66025403784443, -0.0, -0.0 },

  /* Expression: Kx_lqr
   * Referenced by: '<Root>/                   '
   */
  { 0.0, 0.0, 0.26361939369077891, 0.0, -0.25730003892231146, 0.0,
    13.658801770892318, 0.0, 0.0, 0.0, 0.0, 0.24747592364947085, 0.0,
    -0.23101655014711311, 0.0, 7.8844607340479964, 0.0, 0.0, 0.0,
    1.0262852891538179, 0.0, 0.0, 0.0, 1.1710897651635428, 0.0,
    0.26896051530072917, 0.0, 0.0, 0.0, 0.32937730791198644 },

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
