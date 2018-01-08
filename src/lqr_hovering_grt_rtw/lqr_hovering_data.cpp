/*
 * lqr_hovering_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_hovering".
 *
 * Model version              : 1.501
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Mon Jan  8 10:25:27 2018
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
  { -0.0, -0.0, 0.100000000000001, -0.0, -0.0, -0.10000000000000031, -0.0, -0.0,
    8.6602540378443891, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.031622776601683771
  },

  /* Expression: Kx_lqr
   * Referenced by: '<Root>/                   '
   */
  { 0.0, 0.0, 0.26361939369078219, 0.0, 0.0, -0.25730003892231157, 0.0, 0.0,
    13.658801770892259, 0.0, 0.0, 0.0, 0.0, 0.0, 0.24747592364947238, 0.0, 0.0,
    -0.23101655014711334, 0.0, 0.0, 7.8844607340479813, 0.0, 0.0, 0.0, 0.0,
    1.0262852891538206, 0.0, 0.0, 0.0, 0.0, 1.1710897651635497, 0.0, 0.0, 0.0,
    0.0, 0.10546655061388585, 0.0, 0.26896051530072934, 0.0, 0.0, 0.0, 0.0,
    0.32937730791198805, 0.0, 0.0, 0.0, 0.0, 0.14425035178450443 },

  /* Expression: [mass*gra 0 0 0]'
   * Referenced by: '<Root>/              '
   */
  { 15.136564275, 0.0, 0.0, 0.0 },

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
