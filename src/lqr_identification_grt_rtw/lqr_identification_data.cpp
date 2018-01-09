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
 * C++ source code generated on : Tue Jan  9 16:05:02 2018
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
  { -0.0, -0.0, 0.099999999999997161, -0.0, -0.0, -0.10000000000000112, -0.0,
    -0.0, 8.6602540378443571, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.010000000000000007 },

  /* Expression: Kx_lqr
   * Referenced by: '<Root>/                   '
   */
  { 0.0, 0.0, 0.24524050356513313, 0.0, 0.0, -0.23926806701859935, 0.0, 0.0,
    13.600014649902707, 0.0, 0.0, 0.0, 0.0, 0.0, 0.2507145229444101, 0.0, 0.0,
    -0.23624603947408093, 0.0, 0.0, 7.7919422390963389, 0.0, 0.0, 0.0, 0.0,
    1.0534625734318634, 0.0, 0.0, 0.0, 0.0, 1.1929939468557025, 0.0, 0.0, 0.0,
    0.0, 0.050330788148815558, 0.0, 0.27427891366625351, 0.0, 0.0, 0.0, 0.0,
    0.33391601310405578, 0.0, 0.0, 0.0, 0.0, 0.10165941178404761 },

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
