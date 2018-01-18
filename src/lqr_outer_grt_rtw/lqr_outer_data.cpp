/*
 * lqr_outer_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_outer".
 *
 * Model version              : 1.563
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Thu Jan 18 15:02:37 2018
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
  /* Expression: [mass*gra 0 0 0]'
   * Referenced by: '<Root>/              '
   */
  { 15.141735000000002, 0.0, 0.0, 0.0 },

  /* Expression: Ki_lqr
   * Referenced by: '<S1>/ '
   */
  { 9.9999999999999982, -0.0, -0.0, -0.0, -0.0, 1.5811388300841833, -0.0, -0.0,
    -0.0, -0.0, 1.5811388300842111, -0.0, -0.0, -0.0, -0.0, 0.081649658092772581
  },

  /* Expression: Kx_lqr
   * Referenced by: '<S1>/                   '
   */
  { 13.693372885112032, 0.0, 0.0, 0.0, 6.8754230485360663, 0.0, 0.0, 0.0, 0.0,
    0.89378796625294743, 0.0, 0.0, 0.0, 0.0, 0.979015252708005, 0.0, 0.0, 0.0,
    0.0, 0.19755090188172186, 0.0, 0.24945846424395865, 0.0, 0.0, 0.0, 0.0,
    0.29993282278204658, 0.0, 0.0, 0.0, 0.0, 0.19816183511048516 },

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
  { 0.47820515069993652, 0.0, 0.0, 0.47820515069993963, 0.97796743371130357, 0.0,
    0.0, 0.97796743371130723 }
};
