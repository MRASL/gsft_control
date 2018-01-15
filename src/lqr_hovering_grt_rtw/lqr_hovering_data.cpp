/*
 * lqr_hovering_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_hovering".
 *
 * Model version              : 1.510
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Sun Jan 14 22:45:22 2018
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
  { -0.0, -0.0, 0.044721359549995121, -0.0, -0.0, -0.044721359549995079, -0.0,
    -0.0, 2.7386127875258395, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.044721359549995877 },

  /* Expression: Kx_lqr
   * Referenced by: '<Root>/                   '
   */
  { 0.0, 0.0, 0.11680860455980965, 0.0, 0.0, -0.11330985630243004, 0.0, 0.0,
    5.3797811568485807, 0.0, 0.0, 0.0, 0.0, 0.0, 0.13018667384421437, 0.0, 0.0,
    -0.12118508520699241, 0.0, 0.0, 4.371199427067082, 0.0, 0.0, 0.0, 0.0,
    0.67832193475484792, 0.0, 0.0, 0.0, 0.0, 0.77175060083478386, 0.0, 0.0, 0.0,
    0.0, 0.16088436582897284, 0.0, 0.21760496621593822, 0.0, 0.0, 0.0, 0.0,
    0.26652532018196862, 0.0, 0.0, 0.0, 0.0, 0.17758604979834777 },

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
