/*
 * lqr_outer_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_outer".
 *
 * Model version              : 1.559
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Thu Jan 18 12:43:43 2018
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
  { 10.000000000000036, -0.0, -0.0, -0.0, -0.0, 4.4721359549995885, -0.0, -0.0,
    -0.0, -0.0, 4.4721359549995938, -0.0, -0.0, -0.0, -0.0, 0.031622776601683805
  },

  /* Expression: Kx_lqr
   * Referenced by: '<S1>/                   '
   */
  { 13.693372885112046, 0.0, 0.0, 0.0, 6.875423048536061, 0.0, 0.0, 0.0, 0.0,
    2.0554773265844752, 0.0, 0.0, 0.0, 0.0, 2.188559980813352, 0.0, 0.0, 0.0,
    0.0, 0.099118361810886152, 0.0, 0.42764655173628585, 0.0, 0.0, 0.0, 0.0,
    0.49079397784298279, 0.0, 0.0, 0.0, 0.0, 0.13952679992692132 },

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
  { 0.99643081972575931, 0.0, 0.0, 0.996430819725766, 1.4117583502326161, 0.0,
    0.0, 1.4117583502326223 }
};
