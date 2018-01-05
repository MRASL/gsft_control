/*
 * lqr_tracking_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_tracking".
 *
 * Model version              : 1.500
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Fri Jan  5 13:59:33 2018
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
  { 14.611908499999998, 0.0, 0.0, 0.0 },

  /* Expression: Ki_lqr
   * Referenced by: '<Root>/ '
   */
  { -0.0, -0.0, 0.31622776601684288, -0.0, -0.0, -0.31622776601684371, -0.0,
    -0.0, 7.0710678118654782, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.031622776601683777 },

  /* Expression: Kx_lqr
   * Referenced by: '<Root>/                   '
   */
  { 0.0, 0.0, 0.50350284418208013, 0.0, 0.0, -0.48715720542814361, 0.0, 0.0,
    9.9529698033241836, 0.0, 0.0, 0.0, 0.0, 0.0, 0.3850312026150049, 0.0, 0.0,
    -0.35942786691989848, 0.0, 0.0, 6.2976066893627172, 0.0, 0.0, 0.0, 0.0,
    1.4132110363427504, 0.0, 0.0, 0.0, 0.0, 1.5946833792719646, 0.0, 0.0, 0.0,
    0.0, 0.10770952525207145, 0.0, 0.32899236083058114, 0.0, 0.0, 0.0, 0.0,
    0.39543556961049953, 0.0, 0.0, 0.0, 0.0, 0.15181054388366683 },

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
