/*
 * lqr_identification_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_identification".
 *
 * Model version              : 1.513
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Fri Jan  5 21:13:48 2018
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
  { -0.0, -0.0, 0.10000000000000026, -0.0, -0.0, -0.099999999999997341, -0.0,
    -0.0, 10.000000000000027, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.031622776601683771 },

  /* Expression: Kx_lqr
   * Referenced by: '<Root>/                   '
   */
  { 0.0, 0.0, 0.24785457075998696, 0.0, 0.0, -0.2425772076339158, 0.0, 0.0,
    13.908804955594347, 0.0, 0.0, 0.0, 0.0, 0.0, 0.25715944123308604, 0.0, 0.0,
    -0.24421850831734815, 0.0, 0.0, 7.1727427646383157, 0.0, 0.0, 0.0, 0.0,
    1.1259251754545758, 0.0, 0.0, 0.0, 0.0, 1.2530982076163617, 0.0, 0.0, 0.0,
    0.0, 0.12604129415948229, 0.0, 0.29709592112868766, 0.0, 0.0, 0.0, 0.0,
    0.35357689611261917, 0.0, 0.0, 0.0, 0.0, 0.17212922145516951 },

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
