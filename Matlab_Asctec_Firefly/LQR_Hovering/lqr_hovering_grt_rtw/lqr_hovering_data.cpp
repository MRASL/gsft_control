/*
 * lqr_hovering_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_hovering".
 *
 * Model version              : 1.499
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Mon Jan  8 09:25:30 2018
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
  /* Expression: Ki_lqr
   * Referenced by: '<Root>/ '
   */
  { -0.0, -0.0, 0.099999999999998979, -0.0, -0.0, -0.1000000000000016, -0.0,
    -0.0, 8.66025403784445, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.0316227766016838 },

  /* Expression: Kx_lqr
   * Referenced by: '<Root>/                   '
   */
  { 0.0, 0.0, 0.26361939369077797, 0.0, 0.0, -0.25730003892231568, 0.0, 0.0,
    13.591333913792237, 0.0, 0.0, 0.0, 0.0, 0.0, 0.2474759236494698, 0.0, 0.0,
    -0.23101655014711625, 0.0, 0.0, 7.778314410147015, 0.0, 0.0, 0.0, 0.0,
    1.0262852891538292, 0.0, 0.0, 0.0, 0.0, 1.1710897651635412, 0.0, 0.0, 0.0,
    0.0, 0.10546655061388613, 0.0, 0.268960515300731, 0.0, 0.0, 0.0, 0.0,
    0.32937730791198633, 0.0, 0.0, 0.0, 0.0, 0.14425035178450482 },

  /* Expression: [mass*gra 0 0 0]'
   * Referenced by: '<Root>/              '
   */
  { 14.611908499999998, 0.0, 0.0, 0.0 },

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
