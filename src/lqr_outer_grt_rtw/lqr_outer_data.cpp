/*
 * lqr_outer_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_outer".
 *
 * Model version              : 1.544
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Thu Jan 11 22:15:31 2018
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
  { 4.4721359549995725, -0.0, -0.0, -0.0, -0.0, 0.61237243569578925, -0.0, -0.0,
    -0.0, -0.0, 0.61237243569579936, -0.0, -0.0, -0.0, -0.0,
    0.014142135623730954 },

  /* Expression: Kx_lqr
   * Referenced by: '<S1>/                   '
   */
  { 7.2584605523516057, 0.0, 0.0, 0.0, 4.7723559859942135, 0.0, 0.0, 0.0, 0.0,
    0.47998146578961265, 0.0, 0.0, 0.0, 0.0, 0.52451942341178592, 0.0, 0.0, 0.0,
    0.0, 0.056295622920379471, 0.0, 0.18402380182695602, 0.0, 0.0, 0.0, 0.0,
    0.220552567188391, 0.0, 0.0, 0.0, 0.0, 0.10497697232556355 },

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
