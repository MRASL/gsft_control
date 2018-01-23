/*
 * lqr_hovering_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_hovering".
 *
 * Model version              : 1.528
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Mon Jan 22 23:24:08 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Passed (1), Warnings (3), Error (0)
 */

#include "lqr_hovering.h"
#include "lqr_hovering_private.h"

/* Constant parameters (auto storage) */
const ConstP_lqr_hovering_T lqr_hovering_ConstP = {
  /* Expression: [mass*gra 0 0 0]'
   * Referenced by: '<Root>/              '
   */
  { 15.107400000000002, 0.0, 0.0, 0.0 },

  /* Expression: Ki_lqr
   * Referenced by: '<Root>/ '
   */
  { -0.0, -0.0, 0.17888543819998906, -0.0, -0.0, -0.17888543819998559, -0.0,
    -0.0, 8.6602540378443376, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.0591607978309958 },

  /* Expression: Kx_lqr
   * Referenced by: '<Root>/                   '
   */
  { 0.0, 0.0, 0.33508662048964044, 0.0, 0.0, -0.32442817672507696, 0.0, 0.0,
    11.651210404887731, 0.0, 0.0, 0.0, 0.0, 0.0, 0.28029962706929168, 0.0, 0.0,
    -0.26065185291634596, 0.0, 0.0, 6.3941948709007983, 0.0, 0.0, 0.0, 0.0,
    1.1534510754084901, 0.0, 0.0, 0.0, 0.0, 1.3059368019389541, 0.0, 0.0, 0.0,
    0.0, 0.16138387599630641, 0.0, 0.28386507926203286, 0.0, 0.0, 0.0, 0.0,
    0.34679454164592738, 0.0, 0.0, 0.0, 0.0, 0.177860645927305 },

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
