/*
 * lqr_hovering_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_hovering".
 *
 * Model version              : 1.528
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Mon Jan 22 20:18:41 2018
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
  { 15.107400000000002, 0.0, 0.0, 0.0 },

  /* Expression: Ki_lqr
   * Referenced by: '<Root>/ '
   */
  { -0.0, -0.0, 0.15811388300841792, -0.0, -0.0, -0.15811388300841894, -0.0,
    -0.0, 7.0710678118655093, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.070710678118654668 },

  /* Expression: Kx_lqr
   * Referenced by: '<Root>/                   '
   */
  { 0.0, 0.0, 0.31424469872340383, 0.0, 0.0, -0.30601310965888079, 0.0, 0.0,
    11.883389918474206, 0.0, 0.0, 0.0, 0.0, 0.0, 0.280651290661928, 0.0, 0.0,
    -0.26450562623474577, 0.0, 0.0, 6.4498713901054376, 0.0, 0.0, 0.0, 0.0,
    1.2591241124981492, 0.0, 0.0, 0.0, 0.0, 1.3945403410113473, 0.0, 0.0, 0.0,
    0.0, 0.17716932494365581, 0.0, 0.29753149544617746, 0.0, 0.0, 0.0, 0.0,
    0.35916430896178964, 0.0, 0.0, 0.0, 0.0, 0.18659819424096863 },

  /* Expression: B_ENU_inv
   * Referenced by: '<Root>/Gain'
   */
  { 0.16666666666666674, 0.16666666666666669, 0.16666666666666671,
    0.16666666666666671, 0.16666666666666674, 0.16666666666666671,
    0.77519379844962388, 1.5503875968992147, 0.77519379844962344,
    -0.77519379844962344, -1.5503875968992149, -0.77519379844962344,
    -1.3426750446270113, -2.5529533974250051E-14, 1.3426750446270619,
    1.3426750446270113, 2.5418511671787539E-14, -1.3426750446270626,
    -4.5662100456621, 4.5662100456621, -4.5662100456620989, 4.5662100456620971,
    -4.5662100456621006, 4.5662100456620989 }
};
