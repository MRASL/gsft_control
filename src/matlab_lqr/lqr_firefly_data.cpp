/*
 * lqr_firefly_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_firefly".
 *
 * Model version              : 1.450
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Mon Dec 04 20:22:35 2017
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Passed (2), Warnings (2), Error (0)
 */

#include "lqr_firefly.h"
#include "lqr_firefly_private.h"

/* Constant parameters (auto storage) */
const ConstP_lqr_firefly_T lqr_firefly_ConstP = {
  /* Expression: Ki_lqr
   * Referenced by: '<Root>/ '
   */
  { -0.0, -0.0, 0.22360679774997608, -0.0, -0.0, -0.223606797749976, -0.0, -0.0,
    8.6602540378443713, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.031622776601683791
  },

  /* Expression: Kx_lqr
   * Referenced by: '<Root>/                   '
   */
  { 0.0, 0.0, 0.45571693582284789, 0.0, 0.0, -0.44243991498915808, 0.0, 0.0,
    13.689186213677164, 0.0, 0.0, 0.0, 0.0, 0.0, 0.35257856018329176, 0.0, 0.0,
    -0.32591379117773306, 0.0, 0.0, 7.932435849591327, 0.0, 0.0, 0.0, 0.0,
    1.2733568997191356, 0.0, 0.0, 0.0, 0.0, 1.4647625464695362, 0.0, 0.0, 0.0,
    0.0, 0.1054665506138861, 0.0, 0.29918948649211585, 0.0, 0.0, 0.0, 0.0,
    0.36802771925188404, 0.0, 0.0, 0.0, 0.0, 0.14425035178450468 },

  /* Expression: [mass*gra 0 0 0]'
   * Referenced by: '<Root>/              '
   */
  { 15.3800199, 0.0, 0.0, 0.0 },

  /* Expression: pinv(B)
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
