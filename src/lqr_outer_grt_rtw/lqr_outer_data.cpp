/*
 * lqr_outer_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_outer".
 *
 * Model version              : 1.560
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Thu Jan 18 13:55:41 2018
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
   * Referenced by: '<Root>/              '
   */
  { 15.141735000000002, 0.0, 0.0, 0.0 },

  /* Expression: Ki_lqr
   * Referenced by: '<S1>/ '
   */
  { 10.000000000000037, -0.0, -0.0, -0.0, -0.0, 1.1180339887498947, -0.0, -0.0,
    -0.0, -0.0, 1.1180339887498916, -0.0, -0.0, -0.0, -0.0, 0.0316227766016839 },

  /* Expression: Kx_lqr
   * Referenced by: '<S1>/                   '
   */
  { 13.693372885112023, 0.0, 0.0, 0.0, 6.8754230485360583, 0.0, 0.0, 0.0, 0.0,
    0.71708826293796246, 0.0, 0.0, 0.0, 0.0, 0.78343663706302158, 0.0, 0.0, 0.0,
    0.0, 0.0989854960027909, 0.0, 0.2254920610272152, 0.0, 0.0, 0.0, 0.0,
    0.27001547822696931, 0.0, 0.0, 0.0, 0.0, 0.13911062475219266 },

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
  { 0.36073684123954791, 0.0, 0.0, 0.36073684123954813, 0.84945493257682425, 0.0,
    0.0, 0.84945493257682447 }
};
