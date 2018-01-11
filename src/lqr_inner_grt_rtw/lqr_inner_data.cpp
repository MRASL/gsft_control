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
 * C++ source code generated on : Wed Jan 10 20:07:33 2018
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
  { 14.715, 0.0, 0.0, 0.0 },

  /* Expression: Ki_lqr
   * Referenced by: '<Root>/ '
   */
  { 2.2360679774998014, -0.0, -0.0, -0.0, -0.0, 0.099999999999999645, -0.0, -0.0,
    -0.0, -0.0, 0.099999999999999714, -0.0, -0.0, -0.0, -0.0,
    0.031622776601683687 },

  /* Expression: Kx_lqr
   * Referenced by: '<Root>/                   '
   */
  { 4.1774904241112649, 0.0, 0.0, 0.0, 3.6786507407382185, 0.0, 0.0, 0.0, 0.0,
    0.20257447055779934, 0.0, 0.0, 0.0, 0.0, 0.21032694055765425, 0.0, 0.0, 0.0,
    0.0, 0.10040814330163175, 0.0, 0.15518208060886449, 0.0, 0.0, 0.0, 0.0,
    0.17118710962171424, 0.0, 0.0, 0.0, 0.0, 0.14359579102863293 },

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