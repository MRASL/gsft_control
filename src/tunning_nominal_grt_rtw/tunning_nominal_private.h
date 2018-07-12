/*
 * tunning_nominal_private.h
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "tunning_nominal".
 *
 * Model version              : 1.1412
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Thu Jul 12 13:40:46 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_tunning_nominal_private_h_
#define RTW_HEADER_tunning_nominal_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "tunning_nominal.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsMajorTimeStep
# define rtmIsMajorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
# define rtmIsMinorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               ((rtm)->Timing.t)
#endif

#ifndef rtmSetTPtr
# define rtmSetTPtr(rtm, val)          ((rtm)->Timing.t = (val))
#endif

extern void tunning_nominal_MATLABFunction1(const real_T rtu_u[6], const real_T
  rtu_y[3], B_MATLABFunction1_tunning_nom_T *localB);

/* private model entry point functions */
extern void tunning_nominal_derivatives();

#endif                                 /* RTW_HEADER_tunning_nominal_private_h_ */
