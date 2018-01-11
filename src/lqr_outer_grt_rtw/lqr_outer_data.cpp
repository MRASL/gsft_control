/*
 * lqr_outer_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_outer".
 *
 * Model version              : 1.538
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Thu Jan 11 15:47:24 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Passed (1), Warnings (3), Error (0)
 */

#include "lqr_outer.h"
#include "lqr_outer_private.h"

/* Constant parameters (auto storage) */
const ConstP_lqr_outer_T lqr_outer_ConstP = {
  /* Expression: [mass*gra+2 0 0 0]'
   * Referenced by: '<Root>/              '
   */
  { 17.141735000000004, 0.0, 0.0, 0.0 },

  /* Expression: Ki_lqr
   * Referenced by: '<S1>/ '
   */
  { 15.811388300841909, -0.0, -0.0, -0.0, -0.0, 7.0710678118654657, -0.0, -0.0,
    -0.0, -0.0, 7.0710678118654817, -0.0, -0.0, -0.0, -0.0, 0.099999999999999908
  },

  /* Expression: Kx_lqr
   * Referenced by: '<S1>/                   '
   */
  { 17.027102046229935, 0.0, 0.0, 0.0, 7.5870062618078666, 0.0, 0.0, 0.0, 0.0,
    2.9715679370375239, 0.0, 0.0, 0.0, 0.0, 3.1307891240251058, 0.0, 0.0, 0.0,
    0.0, 0.39915930102252667, 0.0, 0.55367988348874841, 0.0, 0.0, 0.0, 0.0,
    0.62238411321300957, 0.0, 0.0, 0.0, 0.0, 0.29664073796395835 },

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
    10.416666666666657, -10.416666666666661, 10.416666666666661 },

  /* Expression: Kxo_lqr
   * Referenced by: '<S3>/                   '
   */
  { 0.0, 0.10878573202013068, -0.10878573202013052, 0.0, 0.0,
    0.15549449713141306, -0.15549449713141292, 0.0 }
};
