/*
 * lqr_identification_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_identification".
 *
 * Model version              : 1.525
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Tue Jan  9 15:33:54 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Passed (1), Warnings (3), Error (0)
 */

#include "lqr_identification.h"
#include "lqr_identification_private.h"

/* Constant parameters (auto storage) */
const ConstP_lqr_identification_T lqr_identification_ConstP = {
  /* Expression: [mass*gra 0 0 0]'
   * Referenced by: '<Root>/              '
   */
  { 14.679084052499999, 0.0, 0.0, 0.0 },

  /* Expression: Ki_lqr
   * Referenced by: '<Root>/ '
   */
  { -0.0, -0.0, 0.10000000000000105, -0.0, -0.0, -0.10000000000000089, -0.0,
    -0.0, 8.6602540378443571, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.031622776601683847 },

  /* Expression: Kx_lqr
   * Referenced by: '<Root>/                   '
   */
  { 0.0, 0.0, 0.23547023542013856, 0.0, 0.0, -0.22897814210821804, 0.0, 0.0,
    13.600014649902697, 0.0, 0.0, 0.0, 0.0, 0.0, 0.22723115884407619, 0.0, 0.0,
    -0.21215494781665456, 0.0, 0.0, 7.7919422390963415, 0.0, 0.0, 0.0, 0.0,
    0.9710684956162875, 0.0, 0.0, 0.0, 0.0, 1.10712848672743, 0.0, 0.0, 0.0, 0.0,
    0.10546655061388605, 0.0, 0.26172790433650162, 0.0, 0.0, 0.0, 0.0,
    0.32034149568400727, 0.0, 0.0, 0.0, 0.0, 0.1442503517845046 },

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
