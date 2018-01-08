/*
 * lqr_identification_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_identification".
 *
 * Model version              : 1.517
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Mon Jan  8 10:33:08 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Passed (1), Warnings (3), Error (0)
 */

#include "lqr_identification.h"
#include "lqr_identification_private.h"

/* Constant parameters (auto storage) */
const ConstP_lqr_identification_T lqr_identification_ConstP = {
  /* Expression: [mass*gra 0 0 0]'
   * Referenced by: '<Root>/              '
   */
  { 15.136564275, 0.0, 0.0, 0.0 },

  /* Expression: Ki_lqr
   * Referenced by: '<Root>/ '
   */
  { -0.0, -0.0, 0.099999999999999215, -0.0, -0.0, -0.10000000000000199, -0.0,
    -0.0, 8.66025403784435, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.031622776601683847 },

  /* Expression: Kx_lqr
   * Referenced by: '<Root>/                   '
   */
  { 0.0, 0.0, 0.26361939369077675, 0.0, 0.0, -0.25730003892231446, 0.0, 0.0,
    13.658801770892179, 0.0, 0.0, 0.0, 0.0, 0.0, 0.24747592364946897, 0.0, 0.0,
    -0.23101655014711586, 0.0, 0.0, 7.8844607340479547, 0.0, 0.0, 0.0, 0.0,
    1.0262852891538279, 0.0, 0.0, 0.0, 0.0, 1.1710897651635377, 0.0, 0.0, 0.0,
    0.0, 0.10546655061388624, 0.0, 0.26896051530073106, 0.0, 0.0, 0.0, 0.0,
    0.329377307911986, 0.0, 0.0, 0.0, 0.0, 0.14425035178450474 },

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
