/*
 * lqr_identification_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_identification".
 *
 * Model version              : 1.525
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Tue Jan  9 17:01:09 2018
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
  { -0.0, -0.0, 0.044721359549995704, -0.0, -0.0, -0.044721359549994268, -0.0,
    -0.0, 2.7386127875258368, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.014142135623730906 },

  /* Expression: Kx_lqr
   * Referenced by: '<Root>/                   '
   */
  { 0.0, 0.0, 0.12762299075708827, 0.0, 0.0, -0.12399027671000551, 0.0, 0.0,
    5.3071108264056166, 0.0, 0.0, 0.0, 0.0, 0.0, 0.13737985487725493, 0.0, 0.0,
    -0.12716058761484153, 0.0, 0.0, 4.2294086680067347, 0.0, 0.0, 0.0, 0.0,
    0.67839723709012456, 0.0, 0.0, 0.0, 0.0, 0.78062540990493123, 0.0, 0.0, 0.0,
    0.0, 0.058577342223793905, 0.0, 0.21761699332301873, 0.0, 0.0, 0.0, 0.0,
    0.26804911443325508, 0.0, 0.0, 0.0, 0.0, 0.10717281684517466 },

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
