/*
 * lqr_hovering_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_hovering".
 *
 * Model version              : 1.520
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Mon Jan 15 19:16:10 2018
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
  { -0.0, -0.0, 0.031622776601684062, -0.0, -0.0, -0.031622776601684055, -0.0,
    -0.0, 10.00000000000002, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.0316227766016837 },

  /* Expression: Kx_lqr
   * Referenced by: '<Root>/                   '
   */
  { 0.0, 0.0, 0.083901026401874079, 0.0, 0.0, -0.080952013050699045, 0.0, 0.0,
    11.420306280892625, 0.0, 0.0, 0.0, 0.0, 0.0, 0.09549101755609668, 0.0, 0.0,
    -0.087804250823832364, 0.0, 0.0, 6.0211697774697814, 0.0, 0.0, 0.0, 0.0,
    0.53662342324995416, 0.0, 0.0, 0.0, 0.0, 0.61701326577535009, 0.0, 0.0, 0.0,
    0.0, 0.0991183618108861, 0.0, 0.19339619792282595, 0.0, 0.0, 0.0, 0.0,
    0.23818701939820958, 0.0, 0.0, 0.0, 0.0, 0.13952679992692141 },

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
