/*
 * lqr_inner_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_inner".
 *
 * Model version              : 1.530
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Wed Jan 10 12:21:46 2018
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
  /* Expression: [mass*gra 0 0 0]'
   * Referenced by: '<Root>/              '
   */
  { 14.679084052499999, 0.0, 0.0, 0.0 },

  /* Expression: Ki_lqr
   * Referenced by: '<Root>/ '
   */
  { 0.70710678118654813, -0.0, -0.0, -0.0, -0.0, 0.044721359549995815, -0.0,
    -0.0, -0.0, -0.0, 0.044721359549995746, -0.0, -0.0, -0.0, -0.0,
    0.0044721359549995728 },

  /* Expression: Kx_lqr
   * Referenced by: '<Root>/                   '
   */
  { 2.0056362231342546, 0.0, 0.0, 0.0, 2.4908378432160192, 0.0, 0.0, 0.0, 0.0,
    0.084735286755263733, 0.0, 0.0, 0.0, 0.0, 0.092370083734550135, 0.0, 0.0,
    0.0, 0.0, 0.033564110250243064, 0.0, 0.078039541862468351, 0.0, 0.0, 0.0,
    0.0, 0.093157189908469717, 0.0, 0.0, 0.0, 0.0, 0.0812307032032685 },

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
    10.416666666666657, -10.416666666666661, 10.416666666666661 }
};
