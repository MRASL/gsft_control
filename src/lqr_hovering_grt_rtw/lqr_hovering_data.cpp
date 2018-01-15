/*
 * lqr_hovering_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_hovering".
 *
 * Model version              : 1.512
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Sun Jan 14 23:15:32 2018
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
  /* Expression: [mass*gra+2 0 0 0]'
   * Referenced by: '<Root>/              '
   */
  { 17.141735000000004, 0.0, 0.0, 0.0 },

  /* Expression: Ki_lqr
   * Referenced by: '<Root>/ '
   */
  { -0.0, -0.0, 0.10000000000000059, -0.0, -0.0, -0.099999999999999686, -0.0,
    -0.0, 8.6602540378443464, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.03162277660168384 },

  /* Expression: Kx_lqr
   * Referenced by: '<Root>/                   '
   */
  { 0.0, 0.0, 0.26361067313646652, 0.0, 0.0, -0.25729188684298832, 0.0, 0.0,
    13.658801770892175, 0.0, 0.0, 0.0, 0.0, 0.0, 0.24745293495730128, 0.0, 0.0,
    -0.23099557517612579, 0.0, 0.0, 7.88446073404796, 0.0, 0.0, 0.0, 0.0,
    1.0264565499839151, 0.0, 0.0, 0.0, 0.0, 1.171284471377775, 0.0, 0.0, 0.0,
    0.0, 0.10546655061388613, 0.0, 0.26898264549299755, 0.0, 0.0, 0.0, 0.0,
    0.32940443566076355, 0.0, 0.0, 0.0, 0.0, 0.14425035178450465 },

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
