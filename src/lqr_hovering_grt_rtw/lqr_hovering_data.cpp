/*
 * lqr_hovering_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_hovering".
 *
 * Model version              : 1.525
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Tue Jan 16 14:53:01 2018
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
  { -0.0, -0.0, 0.17320508075688987, -0.0, -0.0, -0.17320508075688321, -0.0,
    -0.0, 9.999999999999968, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.08164965809277272 },

  /* Expression: Kx_lqr
   * Referenced by: '<Root>/                   '
   */
  { 0.0, 0.0, 0.32349951352988271, 0.0, 0.0, -0.3131257851736659, 0.0, 0.0,
    12.538871104162496, 0.0, 0.0, 0.0, 0.0, 0.0, 0.27323660149128026, 0.0, 0.0,
    -0.25417198201077085, 0.0, 0.0, 6.6111644283401, 0.0, 0.0, 0.0, 0.0,
    1.1365283480217727, 0.0, 0.0, 0.0, 0.0, 1.285920599473698, 0.0, 0.0, 0.0,
    0.0, 0.18574358519931727, 0.0, 0.2817854510876987, 0.0, 0.0, 0.0, 0.0,
    0.34413551249351387, 0.0, 0.0, 0.0, 0.0, 0.19086023651164222 },

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
