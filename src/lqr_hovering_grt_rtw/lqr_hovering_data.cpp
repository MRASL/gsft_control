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
 * C++ source code generated on : Mon Jan 22 14:46:54 2018
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
  { -0.0, -0.0, 0.077459666924149642, -0.0, -0.0, -0.077459666924148768, -0.0,
    -0.0, 7.0710678118654569, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.044721359549995676 },

  /* Expression: Kx_lqr
   * Referenced by: '<Root>/                   '
   */
  { 0.0, 0.0, 0.17335400585420949, 0.0, 0.0, -0.1677225927194845, 0.0, 0.0,
    11.883389918474117, 0.0, 0.0, 0.0, 0.0, 0.0, 0.16816242813961285, 0.0, 0.0,
    -0.15576408385654333, 0.0, 0.0, 6.4498713901054128, 0.0, 0.0, 0.0, 0.0,
    0.80766876526459408, 0.0, 0.0, 0.0, 0.0, 0.91889022268157738, 0.0, 0.0, 0.0,
    0.0, 0.12357249705259371, 0.0, 0.23778804808554116, 0.0, 0.0, 0.0, 0.0,
    0.29110320197656175, 0.0, 0.0, 0.0, 0.0, 0.15581848175813448 },

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
