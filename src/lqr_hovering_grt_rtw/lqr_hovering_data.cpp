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
 * C++ source code generated on : Mon Jan 22 23:37:30 2018
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
  { -0.0, -0.0, 0.17320508075688654, -0.0, -0.0, -0.1732050807568874, -0.0, -0.0,
    8.6602540378443642, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.051639777949432308
  },

  /* Expression: Kx_lqr
   * Referenced by: '<Root>/                   '
   */
  { 0.0, 0.0, 0.32349951352987794, 0.0, 0.0, -0.3131257851736729, 0.0, 0.0,
    11.651210404887754, 0.0, 0.0, 0.0, 0.0, 0.0, 0.27323660149127593, 0.0, 0.0,
    -0.25417198201077579, 0.0, 0.0, 6.3941948709008072, 0.0, 0.0, 0.0, 0.0,
    1.1365283480217876, 0.0, 0.0, 0.0, 0.0, 1.2859205994736798, 0.0, 0.0, 0.0,
    0.0, 0.15756946783574763, 0.0, 0.28178545108770126, 0.0, 0.0, 0.0, 0.0,
    0.3441355124935096, 0.0, 0.0, 0.0, 0.0, 0.17584768223789141 },

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
