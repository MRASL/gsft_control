/*
 * lqr_outer_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_outer".
 *
 * Model version              : 1.539
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Thu Jan 11 17:14:38 2018
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
  /* Expression: [mass*gra+2 0 0 0]'
   * Referenced by: '<Root>/              '
   */
  { 17.141735000000004, 0.0, 0.0, 0.0 },

  /* Expression: Ki_lqr
   * Referenced by: '<S1>/ '
   */
  { 15.811388300841895, -0.0, -0.0, -0.0, -0.0, 0.99999999999999489, -0.0, -0.0,
    -0.0, -0.0, 0.99999999999999734, -0.0, -0.0, -0.0, -0.0,
    0.022360679774997883 },

  /* Expression: Kx_lqr
   * Referenced by: '<S1>/                   '
   */
  { 17.027102046229896, 0.0, 0.0, 0.0, 7.5870062618078471, 0.0, 0.0, 0.0, 0.0,
    0.66737495954767956, 0.0, 0.0, 0.0, 0.0, 0.72878023117812907, 0.0, 0.0, 0.0,
    0.0, 0.10751094505248805, 0.0, 0.21769466831563414, 0.0, 0.0, 0.0, 0.0,
    0.26056031267802376, 0.0, 0.0, 0.0, 0.0, 0.14665482829847823 },

  /* Expression: B_ENU_inv
   * Referenced by: '<Root>/Gain'
   */
  { 0.16666666666666674, 0.16666666666666669, 0.16666666666666671,
    0.16666666666666671, 0.16666666666666674, 0.16666666666666671,
    0.77519379844961245, 1.5503875968992242, 0.77519379844961234,
    -0.775193798449612, -1.5503875968992249, -0.77519379844961223,
    -1.3426750446270366, 7.0851742975913985E-16, 1.3426750446270364,
    1.3426750446270364, -4.8647282483410855E-16, -1.3426750446270366,
    -10.416666666666663, 10.416666666666663, -10.416666666666655,
    10.416666666666657, -10.416666666666661, 10.416666666666661 },

  /* Expression: Kxo_lqr
   * Referenced by: '<S3>/                   '
   */
  { 0.0, 0.042699914198735672, -0.042699914198735756, 0.0, 0.0,
    0.093570215120754474, -0.093570215120754585, 0.0 }
};
