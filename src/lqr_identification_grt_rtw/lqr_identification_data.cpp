/*
 * lqr_identification_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_identification".
 *
 * Model version              : 1.526
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Wed Jan 10 09:03:02 2018
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
  { 14.679084052499999, 0.0, 0.0, 0.0 },

  /* Expression: Ki_lqr
   * Referenced by: '<Root>/ '
   */
  { -0.0, -0.0, 0.0086602540378438349, -0.0, -0.0, -0.0086602540378439164, -0.0,
    -0.0, 0.70710678118654346, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.00099999999999999633 },

  /* Expression: Kx_lqr
   * Referenced by: '<Root>/                   '
   */
  { 0.0, 0.0, 0.031598468366157435, 0.0, 0.0, -0.030527131084871349, 0.0, 0.0,
    2.0056362231342475, 0.0, 0.0, 0.0, 0.0, 0.0, 0.046099294524035724, 0.0, 0.0,
    -0.042256597154922929, 0.0, 0.0, 2.4908378432160148, 0.0, 0.0, 0.0, 0.0,
    0.32117655641210824, 0.0, 0.0, 0.0, 0.0, 0.37271213630446826, 0.0, 0.0, 0.0,
    0.0, 0.010523066998739488, 0.0, 0.14945172295845888, 0.0, 0.0, 0.0, 0.0,
    0.18498562538860847, 0.0, 0.0, 0.0, 0.0, 0.045367469529980338 },

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
