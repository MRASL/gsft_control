/*
 * lqr_inner_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_inner".
 *
 * Model version              : 1.530
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Wed Jan 10 21:14:47 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Passed (1), Warnings (3), Error (0)
 */

#include "lqr_inner.h"
#include "lqr_inner_private.h"

/* Constant parameters (auto storage) */
const ConstP_lqr_inner_T lqr_inner_ConstP = {
  /* Expression: [mass*gra 0 0 0]'
   * Referenced by: '<Root>/              '
   */
  { 15.141735000000002, 0.0, 0.0, 0.0 },

  /* Expression: Ki_lqr
   * Referenced by: '<Root>/ '
   */
  { 7.071067811865448, -0.0, -0.0, -0.0, -0.0, 0.22360679774997988, -0.0, -0.0,
    -0.0, -0.0, 0.2236067977499786, -0.0, -0.0, -0.0, -0.0, 0.010000000000000014
  },

  /* Expression: Kx_lqr
   * Referenced by: '<Root>/                   '
   */
  { 10.282092845031354, 0.0, 0.0, 0.0, 6.0614206760966356, 0.0, 0.0, 0.0, 0.0,
    0.34779160489603966, 0.0, 0.0, 0.0, 0.0, 0.36474714905919686, 0.0, 0.0, 0.0,
    0.0, 0.0652956043338572, 0.0, 0.1586691485906962, 0.0, 0.0, 0.0, 0.0,
    0.18568416430626961, 0.0, 0.0, 0.0, 0.0, 0.11317579726618109 },

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
