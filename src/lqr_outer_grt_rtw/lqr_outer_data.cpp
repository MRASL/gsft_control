/*
 * lqr_outer_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_outer".
 *
 * Model version              : 1.540
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Thu Jan 11 21:11:59 2018
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
  { 14.715, 0.0, 0.0, 0.0 },

  /* Expression: Ki_lqr
   * Referenced by: '<S1>/ '
   */
  { 7.0710678118654311, -0.0, -0.0, -0.0, -0.0, 0.99999999999999878, -0.0, -0.0,
    -0.0, -0.0, 1.0000000000000013, -0.0, -0.0, -0.0, -0.0, 0.014142135623730935
  },

  /* Expression: Kx_lqr
   * Referenced by: '<S1>/                   '
   */
  { 10.337787534563873, 0.0, 0.0, 0.0, 5.7890726894461668, 0.0, 0.0, 0.0, 0.0,
    0.66737495954768056, 0.0, 0.0, 0.0, 0.0, 0.72878023117812785, 0.0, 0.0, 0.0,
    0.0, 0.073587679424853725, 0.0, 0.21769466831563405, 0.0, 0.0, 0.0, 0.0,
    0.2605603126780236, 0.0, 0.0, 0.0, 0.0, 0.12074366467693615 },

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
  { 0.0, 0.030013233250540092, -0.030013233250540037, 0.0, 0.0,
    0.078351170134695947, -0.078351170134695766, 0.0 }
};
