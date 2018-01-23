/*
 * lqr_outer_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_outer".
 *
 * Model version              : 1.577
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Mon Jan 22 20:55:54 2018
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
   * Referenced by: '<S1>/              '
   */
  { 15.107400000000002, 0.0, 0.0, 0.0 },

  /* Expression: Ki_lqr
   * Referenced by: '<S1>/ '
   */
  { 7.0710678118655164, -0.0, -0.0, -0.0, -0.0, 1.0000000000000033, -0.0, -0.0,
    -0.0, -0.0, 1.0, -0.0, -0.0, -0.0, -0.0, 0.031622776601683875 },

  /* Expression: Kx_lqr
   * Referenced by: '<S1>/                   '
   */
  { 11.883389918474151, 0.0, 0.0, 0.0, 6.4498713901054145, 0.0, 0.0, 0.0, 0.0,
    0.778779672521899, 0.0, 0.0, 0.0, 0.0, 0.82868948637152384, 0.0, 0.0, 0.0,
    0.0, 0.099118361810886291, 0.0, 0.25324888916665733, 0.0, 0.0, 0.0, 0.0,
    0.29336313241135009, 0.0, 0.0, 0.0, 0.0, 0.13952679992692155 },

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
    -4.5662100456621006, 4.5662100456620989 },

  /* Expression: Kxo_lqr
   * Referenced by: '<S3>/                   '
   */
  { 0.29454926278495885, 0.0, 0.0, 0.29454926278495958, 0.76759268207162967, 0.0,
    0.0, 0.76759268207163034 }
};
