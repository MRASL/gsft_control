/*
 * lqr_identification_data.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_identification".
 *
 * Model version              : 1.526
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Wed Jan 10 09:15:36 2018
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
  { 14.679084052499999, 0.0, 0.0, 0.0 },

  /* Expression: Ki_lqr
   * Referenced by: '<Root>/ '
   */
  { -0.0, -0.0, 0.038729833462075119, -0.0, -0.0, -0.038729833462073392, -0.0,
    -0.0, 0.70710678118654524, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.0044721359549995737 },

  /* Expression: Kx_lqr
   * Referenced by: '<Root>/                   '
   */
  { 0.0, 0.0, 0.11930188051016602, 0.0, 0.0, -0.11614909018477038, 0.0, 0.0,
    2.0056362231342475, 0.0, 0.0, 0.0, 0.0, 0.0, 0.13210667047254426, 0.0, 0.0,
    -0.12252326310728738, 0.0, 0.0, 2.4908378432160121, 0.0, 0.0, 0.0, 0.0,
    0.66328010360411638, 0.0, 0.0, 0.0, 0.0, 0.76217376885654009, 0.0, 0.0, 0.0,
    0.0, 0.033564110250243084, 0.0, 0.215189043702953, 0.0, 0.0, 0.0, 0.0,
    0.264871155684254, 0.0, 0.0, 0.0, 0.0, 0.081230703203268528 },

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
