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
 * C++ source code generated on : Mon Jan 15 22:18:07 2018
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
  { -0.0, -0.0, 0.2000000000000007, -0.0, -0.0, -0.20000000000000037, -0.0, -0.0,
    9.9999999999999982, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.049999999999999913
  },

  /* Expression: Kx_lqr
   * Referenced by: '<Root>/                   '
   */
  { 0.0, 0.0, 0.32722957366451277, 0.0, 0.0, -0.31341877756534031, 0.0, 0.0,
    13.693372885112018, 0.0, 0.0, 0.0, 0.0, 0.0, 0.2576979847016459, 0.0, 0.0,
    -0.23557832532638118, 0.0, 0.0, 6.8754230485360663, 0.0, 0.0, 0.0, 0.0,
    1.0338083698290195, 0.0, 0.0, 0.0, 0.0, 1.1919586170534471, 0.0, 0.0, 0.0,
    0.0, 0.13034810469885047, 0.0, 0.26881723845128852, 0.0, 0.0, 0.0, 0.0,
    0.33136818681512631, 0.0, 0.0, 0.0, 0.0, 0.15990628398582515 },

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
