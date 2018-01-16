/*
 * lqr_hovering_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_hovering".
 *
 * Model version              : 1.527
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Tue Jan 16 17:09:25 2018
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
  /* Expression: [mass*gra 0 0 0]'
   * Referenced by: '<Root>/              '
   */
  { 15.141735000000002, 0.0, 0.0, 0.0 },

  /* Expression: Ki_lqr
   * Referenced by: '<Root>/ '
   */
  { -0.0, -0.0, 0.16733200530681519, -0.0, -0.0, -0.16733200530681661, -0.0,
    -0.0, 9.9999999999999822, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.057735026918962415 },

  /* Expression: Kx_lqr
   * Referenced by: '<Root>/                   '
   */
  { 0.0, 0.0, 0.316532125154258, 0.0, 0.0, -0.30650066166736389, 0.0, 0.0,
    12.538871104162542, 0.0, 0.0, 0.0, 0.0, 0.0, 0.2695018986036064, 0.0, 0.0,
    -0.2508266587991223, 0.0, 0.0, 6.6111644283401221, 0.0, 0.0, 0.0, 0.0,
    1.1280904959802696, 0.0, 0.0, 0.0, 0.0, 1.2757092612014733, 0.0, 0.0, 0.0,
    0.0, 0.1527264101948439, 0.0, 0.28074277089691468, 0.0, 0.0, 0.0, 0.0,
    0.34277105348437237, 0.0, 0.0, 0.0, 0.0, 0.17313599823666312 },

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
