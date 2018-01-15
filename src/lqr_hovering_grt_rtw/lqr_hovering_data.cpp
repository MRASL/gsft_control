/*
 * lqr_hovering_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_hovering".
 *
 * Model version              : 1.520
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Mon Jan 15 13:24:31 2018
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
  { 15.141735000000002, 0.0, 0.0, 0.0 },

  /* Expression: Ki_lqr
   * Referenced by: '<Root>/ '
   */
  { -0.0, -0.0, 0.099999999999999548, -0.0, -0.0, -0.0999999999999992, -0.0,
    -0.0, 8.6602540378443642, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.036514837167011212 },

  /* Expression: Kx_lqr
   * Referenced by: '<Root>/                   '
   */
  { 0.0, 0.0, 0.23488014884946992, 0.0, 0.0, -0.22953352505189328, 0.0, 0.0,
    12.879337068181604, 0.0, 0.0, 0.0, 0.0, 0.0, 0.22584342161774715, 0.0, 0.0,
    -0.21342819561374105, 0.0, 0.0, 6.6901803809371705, 0.0, 0.0, 0.0, 0.0,
    1.0790659897721675, 0.0, 0.0, 0.0, 0.0, 1.1913419570790988, 0.0, 0.0, 0.0,
    0.0, 0.10984384146545227, 0.0, 0.29156248476207791, 0.0, 0.0, 0.0, 0.0,
    0.34546819622661484, 0.0, 0.0, 0.0, 0.0, 0.14695856543829869 },

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
