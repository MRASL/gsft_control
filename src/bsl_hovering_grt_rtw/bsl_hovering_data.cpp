/*
 * bsl_hovering_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "bsl_hovering".
 *
 * Model version              : 1.606
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Mon Jan 29 22:57:53 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Passed (1), Warnings (3), Error (0)
 */

#include "bsl_hovering.h"
#include "bsl_hovering_private.h"

/* Invariant block signals (auto storage) */
const ConstB_bsl_hovering_T bsl_hovering_ConstB = {
  {
    1.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    1.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    1.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    1.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    1.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    1.0,
    0.0,
    0.0,
    0.0
  }
  /* '<S13>/Transpose' */
};

/* Constant parameters (auto storage) */
const ConstP_bsl_hovering_T bsl_hovering_ConstP = {
  /* Expression: B_ENU_inv
   * Referenced by: '<Root>/                 '
   */
  { 0.16666666666666674, 0.16666666666666669, 0.16666666666666671,
    0.16666666666666671, 0.16666666666666674, 0.16666666666666671,
    0.77519379844962388, 1.5503875968992147, 0.77519379844962344,
    -0.77519379844962344, -1.5503875968992149, -0.77519379844962344,
    -1.3426750446270113, -2.5529533974250051E-14, 1.3426750446270619,
    1.3426750446270113, 2.5418511671787539E-14, -1.3426750446270626,
    -4.5662100456621, 4.5662100456621, -4.5662100456620989, 4.5662100456620971,
    -4.5662100456621006, 4.5662100456620989 },

  /* Expression: Qgamma
   * Referenced by: '<S12>/Q_gamma'
   */
  { 0.0002, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0002, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0002, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0002, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0002, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0002 },

  /* Expression: Pgamma0
   * Referenced by: '<S12>/Unit Delay1'
   */
  { 0.01, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.01, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.01,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.01, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.01, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.01 },

  /* Pooled Parameter (Expression: C)
   * Referenced by:
   *   '<S9>/     '
   *   '<S9>/C'
   *   '<S9>/C1'
   *   '<S10>/                      '
   *   '<S13>/     '
   *   '<S13>/C'
   */
  { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  /* Pooled Parameter (Expression: A)
   * Referenced by:
   *   '<S9>/A'
   *   '<S9>/A1'
   *   '<S10>/     '
   */
  { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.010000000000000002, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.010000000000000002, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.010000000000000002, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.00049050000000000027, 0.0, 0.0,
    -0.098100000000000021, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.00049050000000000027, 0.0, 0.0, 0.098100000000000021, 0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, -1.6350000000000009E-6, 0.0, 0.0, -0.00049050000000000016, 0.0,
    0.010000000000000002, 0.0, 0.0, 1.0, 0.0, 0.0, 1.6350000000000009E-6, 0.0,
    0.0, 0.00049050000000000016, 0.0, 0.0, 0.0, 0.010000000000000002, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.010000000000000002, 0.0,
    0.0, 1.0 },

  /* Pooled Parameter (Expression: B)
   * Referenced by:
   *   '<S9>/B'
   *   '<S10>/          '
   */
  { -1.6583697046020462E-8, -1.2642492152501861E-8, 3.2467532467532474E-5,
    -6.6334788184081836E-6, -5.0569968610007424E-6, 0.0064935064935064939,
    0.00015464822204895232, -0.0002028586794620239, -1.8679631525076769E-5,
    0.030929644409790458, -0.040571735892404773, -0.0037359263050153529, 0.0,
    -2.5284984305003722E-8, 3.2467532467532474E-5, 0.0, -1.0113993722001485E-5,
    0.0064935064935064939, 0.00030929644409790464, 0.0, 1.8679631525076769E-5,
    0.061859288819580915, 0.0, 0.0037359263050153529, 1.6583697046020462E-8,
    -1.2642492152501861E-8, 3.2467532467532474E-5, 6.6334788184081836E-6,
    -5.0569968610007424E-6, 0.0064935064935064939, 0.00015464822204895232,
    0.0002028586794620239, -1.8679631525076769E-5, 0.030929644409790458,
    0.040571735892404773, -0.0037359263050153529, 1.6583697046020462E-8,
    1.2642492152501861E-8, 3.2467532467532474E-5, 6.6334788184081836E-6,
    5.0569968610007424E-6, 0.0064935064935064939, -0.00015464822204895232,
    0.0002028586794620239, 1.8679631525076769E-5, -0.030929644409790458,
    0.040571735892404773, 0.0037359263050153529, 0.0, 2.5284984305003722E-8,
    3.2467532467532474E-5, 0.0, 1.0113993722001485E-5, 0.0064935064935064939,
    -0.00030929644409790464, 0.0, -1.8679631525076769E-5, -0.061859288819580915,
    0.0, -0.0037359263050153529, -1.6583697046020462E-8, 1.2642492152501861E-8,
    3.2467532467532474E-5, -6.6334788184081836E-6, 5.0569968610007424E-6,
    0.0064935064935064939, -0.00015464822204895232, -0.0002028586794620239,
    1.8679631525076769E-5, -0.030929644409790458, -0.040571735892404773,
    0.0037359263050153529 },

  /* Expression: Qx
   * Referenced by: '<S9>/Q_x'
   */
  { 3.3333333333333342E-9, 0.0, 0.0, 5.0000000000000008E-7, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 3.3333333333333342E-9, 0.0, 0.0,
    5.0000000000000008E-7, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    3.3333333333333342E-9, 0.0, 0.0, 5.0000000000000008E-7, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 5.0000000000000008E-7, 0.0, 0.0, 0.0001, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 5.0000000000000008E-7, 0.0, 0.0, 0.0001, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 5.0000000000000008E-7, 0.0, 0.0, 0.0001, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 3.3333333333333342E-9,
    0.0, 0.0, 5.0000000000000008E-7, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    3.3333333333333342E-9, 0.0, 0.0, 5.0000000000000008E-7, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 3.3333333333333342E-9, 0.0, 0.0,
    5.0000000000000008E-7, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 5.0000000000000008E-7,
    0.0, 0.0, 0.0001, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    5.0000000000000008E-7, 0.0, 0.0, 0.0001, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 5.0000000000000008E-7, 0.0, 0.0, 0.0001 },

  /* Expression: Px_tilde0
   * Referenced by: '<S9>/Unit Delay1'
   */
  { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 },

  /* Expression: A'
   * Referenced by: '<S9>/A''
   */
  { 1.0, 0.0, 0.0, 0.010000000000000002, 0.0, 0.0, 0.0, 0.00049050000000000027,
    0.0, 0.0, 1.6350000000000009E-6, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.010000000000000002, 0.0, -0.00049050000000000027, 0.0, 0.0,
    -1.6350000000000009E-6, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.010000000000000002, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.098100000000000021, 0.0, 0.0, 0.00049050000000000016, 0.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0, -0.098100000000000021, 0.0, 0.0,
    -0.00049050000000000016, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.010000000000000002, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.010000000000000002, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.010000000000000002, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 },

  /* Pooled Parameter (Expression: R)
   * Referenced by:
   *   '<S9>/R'
   *   '<S13>/R'
   */
  { 0.001, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.001, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.001, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0001, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0001, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0001 },

  /* Expression: [0 0 0 0 0 bias 0 0 0 0 0 0]
   * Referenced by: '<S9>/Constant'
   */
  { 0.0, 0.0, 0.0, 0.0, 0.0, -0.0981, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  /* Expression: C'
   * Referenced by: '<S9>/C''
   */
  { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0 }
};