/*
 * lqr_tracking_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_tracking".
 *
 * Model version              : 1.507
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Mon Jan  8 08:00:28 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Passed (1), Warnings (3), Error (0)
 */

#include "lqr_tracking.h"
#include "lqr_tracking_private.h"

/* Constant parameters (auto storage) */
const ConstP_lqr_tracking_T lqr_tracking_ConstP = {
  /* Expression: [mass*gra 0 0 0]'
   * Referenced by: '<Root>/              '
   */
  { 15.3747678035, 0.0, 0.0, 0.0 },

  /* Expression: Ki_lqr
   * Referenced by: '<Root>/ '
   */
  { -0.0, -0.0, 0.10000000000000032, -0.0, -0.0, -0.099999999999998437, -0.0,
    -0.0, 8.6602540378443518, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.0316227766016839 },

  /* Expression: Kx_lqr
   * Referenced by: '<Root>/                   '
   */
  { 0.0, 0.0, 0.26361939369077958, 0.0, 0.0, -0.25730003892230685, 0.0, 0.0,
    13.689186213677161, 0.0, 0.0, 0.0, 0.0, 0.0, 0.247475923649472, 0.0, 0.0,
    -0.23101655014711053, 0.0, 0.0, 7.9324358495913438, 0.0, 0.0, 0.0, 0.0,
    1.026285289153811, 0.0, 0.0, 0.0, 0.0, 1.1710897651635492, 0.0, 0.0, 0.0,
    0.0, 0.10546655061388642, 0.0, 0.26896051530072757, 0.0, 0.0, 0.0, 0.0,
    0.32937730791198777, 0.0, 0.0, 0.0, 0.0, 0.14425035178450488 },

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
