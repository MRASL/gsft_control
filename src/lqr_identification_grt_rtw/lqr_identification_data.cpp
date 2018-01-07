/*
 * lqr_identification_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_identification".
 *
 * Model version              : 1.517
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Sun Jan  7 15:37:06 2018
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
  { 14.611908499999998, 0.0, 0.0, 0.0 },

  /* Expression: Ki_lqr
   * Referenced by: '<Root>/ '
   */
  { -0.0, -0.0, 0.099999999999999048, -0.0, -0.0, -0.099999999999998729, -0.0,
    -0.0, 8.6602540378444441, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.044721359549995836 },

  /* Expression: Kx_lqr
   * Referenced by: '<Root>/                   '
   */
  { 0.0, 0.0, 0.26361939369077741, 0.0, 0.0, -0.25730003892230718, 0.0, 0.0,
    13.591333913792237, 0.0, 0.0, 0.0, 0.0, 0.0, 0.24747592364946916, 0.0, 0.0,
    -0.23101655014710981, 0.0, 0.0, 7.7783144101470292, 0.0, 0.0, 0.0, 0.0,
    1.0262852891538057, 0.0, 0.0, 0.0, 0.0, 1.1710897651635397, 0.0, 0.0, 0.0,
    0.0, 0.1410829155986689, 0.0, 0.26896051530072634, 0.0, 0.0, 0.0, 0.0,
    0.32937730791198566, 0.0, 0.0, 0.0, 0.0, 0.16663613566084606 },

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
