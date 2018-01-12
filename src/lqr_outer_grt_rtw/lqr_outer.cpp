/*
 * lqr_outer.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_outer".
 *
 * Model version              : 1.541
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Thu Jan 11 21:32:24 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Passed (1), Warnings (3), Error (0)
 */

#include "lqr_outer.h"
#include "lqr_outer_private.h"

/*
 * This function updates continuous states using the ODE5 fixed-step
 * solver algorithm
 */
void lqr_outerModelClass::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE5_A[6] = {
    1.0/5.0, 3.0/10.0, 4.0/5.0, 8.0/9.0, 1.0, 1.0
  };

  static const real_T rt_ODE5_B[6][6] = {
    { 1.0/5.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

    { 3.0/40.0, 9.0/40.0, 0.0, 0.0, 0.0, 0.0 },

    { 44.0/45.0, -56.0/15.0, 32.0/9.0, 0.0, 0.0, 0.0 },

    { 19372.0/6561.0, -25360.0/2187.0, 64448.0/6561.0, -212.0/729.0, 0.0, 0.0 },

    { 9017.0/3168.0, -355.0/33.0, 46732.0/5247.0, 49.0/176.0, -5103.0/18656.0,
      0.0 },

    { 35.0/384.0, 0.0, 500.0/1113.0, 125.0/192.0, -2187.0/6784.0, 11.0/84.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE5_IntgData *id = (ODE5_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T *f3 = id->f[3];
  real_T *f4 = id->f[4];
  real_T *f5 = id->f[5];
  real_T hB[6];
  int_T i;
  int_T nXc = 6;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  lqr_outer_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE5_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[0]);
  rtsiSetdX(si, f1);
  this->step();
  lqr_outer_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE5_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[1]);
  rtsiSetdX(si, f2);
  this->step();
  lqr_outer_derivatives();

  /* f(:,4) = feval(odefile, t + hA(3), y + f*hB(:,3), args(:)(*)); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE5_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[2]);
  rtsiSetdX(si, f3);
  this->step();
  lqr_outer_derivatives();

  /* f(:,5) = feval(odefile, t + hA(4), y + f*hB(:,4), args(:)(*)); */
  for (i = 0; i <= 3; i++) {
    hB[i] = h * rt_ODE5_B[3][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2] +
                   f3[i]*hB[3]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[3]);
  rtsiSetdX(si, f4);
  this->step();
  lqr_outer_derivatives();

  /* f(:,6) = feval(odefile, t + hA(5), y + f*hB(:,5), args(:)(*)); */
  for (i = 0; i <= 4; i++) {
    hB[i] = h * rt_ODE5_B[4][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2] +
                   f3[i]*hB[3] + f4[i]*hB[4]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f5);
  this->step();
  lqr_outer_derivatives();

  /* tnew = t + hA(6);
     ynew = y + f*hB(:,6); */
  for (i = 0; i <= 5; i++) {
    hB[i] = h * rt_ODE5_B[5][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2] +
                   f3[i]*hB[3] + f4[i]*hB[4] + f5[i]*hB[5]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void lqr_outerModelClass::step()
{
  int32_T x;
  real_T rtb_TmpSignalConversionAtInpo_h[4];
  real_T rtb_phi_refteta_ref[2];
  real_T rtb_Clock;
  real_T tmp[8];
  real_T tmp_0[4];
  int32_T i;
  real_T tmp_1[2];
  real_T u0;
  real_T rtb_phi_refteta_ref_0;
  if (rtmIsMajorTimeStep((&lqr_outer_M))) {
    /* set solver stop time */
    if (!((&lqr_outer_M)->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&(&lqr_outer_M)->solverInfo, (((&lqr_outer_M)
        ->Timing.clockTickH0 + 1) * (&lqr_outer_M)->Timing.stepSize0 *
        4294967296.0));
    } else {
      rtsiSetSolverStopTime(&(&lqr_outer_M)->solverInfo, (((&lqr_outer_M)
        ->Timing.clockTick0 + 1) * (&lqr_outer_M)->Timing.stepSize0 +
        (&lqr_outer_M)->Timing.clockTickH0 * (&lqr_outer_M)->Timing.stepSize0 *
        4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep((&lqr_outer_M))) {
    (&lqr_outer_M)->Timing.t[0] = rtsiGetT(&(&lqr_outer_M)->solverInfo);
  }

  /* SignalConversion: '<S1>/TmpSignal ConversionAt                   Inport1' incorporates:
   *  Gain: '<S1>/                   '
   *  Inport: '<Root>/X'
   */
  tmp[0] = lqr_outer_U.X[2];
  for (i = 0; i < 7; i++) {
    tmp[i + 1] = lqr_outer_U.X[5 + i];
  }

  /* End of SignalConversion: '<S1>/TmpSignal ConversionAt                   Inport1' */
  for (i = 0; i < 4; i++) {
    /* Gain: '<S1>/ ' incorporates:
     *  Integrator: '<S1>/Integrator'
     *  Sum: '<S1>/Sum'
     */
    rtb_phi_refteta_ref_0 = lqr_outer_ConstP._Gain[i + 12] *
      lqr_outer_X.Integrator_CSTATE[3] + (lqr_outer_ConstP._Gain[i + 8] *
      lqr_outer_X.Integrator_CSTATE[2] + (lqr_outer_ConstP._Gain[i + 4] *
      lqr_outer_X.Integrator_CSTATE[1] + lqr_outer_ConstP._Gain[i] *
      lqr_outer_X.Integrator_CSTATE[0]));

    /* Gain: '<S1>/                   ' incorporates:
     *  Sum: '<S1>/Sum'
     */
    tmp_0[i] = 0.0;
    for (x = 0; x < 8; x++) {
      tmp_0[i] += lqr_outer_ConstP._Gain_i[(x << 2) + i] * tmp[x];
    }

    /* Sum: '<Root>/Sum2' incorporates:
     *  Constant: '<Root>/              '
     *  Sum: '<S1>/Sum'
     */
    rtb_TmpSignalConversionAtInpo_h[i] = (rtb_phi_refteta_ref_0 - tmp_0[i]) +
      lqr_outer_ConstP._Value[i];
  }

  /* Outport: '<Root>/virtual_control' */
  lqr_outer_Y.virtual_control[0] = rtb_TmpSignalConversionAtInpo_h[0];
  lqr_outer_Y.virtual_control[1] = rtb_TmpSignalConversionAtInpo_h[1];
  lqr_outer_Y.virtual_control[2] = rtb_TmpSignalConversionAtInpo_h[2];
  lqr_outer_Y.virtual_control[3] = rtb_TmpSignalConversionAtInpo_h[3];
  for (i = 0; i < 6; i++) {
    /* Gain: '<Root>/Gain' incorporates:
     *  Gain: '<Root>/Gain2'
     */
    rtb_phi_refteta_ref_0 = lqr_outer_ConstP.Gain_Gain[i + 18] *
      rtb_TmpSignalConversionAtInpo_h[3] + (lqr_outer_ConstP.Gain_Gain[i + 12] *
      rtb_TmpSignalConversionAtInpo_h[2] + (lqr_outer_ConstP.Gain_Gain[i + 6] *
      rtb_TmpSignalConversionAtInpo_h[1] + lqr_outer_ConstP.Gain_Gain[i] *
      rtb_TmpSignalConversionAtInpo_h[0]));

    /* Sqrt: '<Root>/Sqrt1' incorporates:
     *  Gain: '<Root>/Gain2'
     */
    rtb_Clock = std::sqrt(174027.4476090369 * rtb_phi_refteta_ref_0);

    /* Gain: '<Root>/rads_to_RPM' */
    rtb_phi_refteta_ref_0 = 9.5493 * rtb_Clock;

    /* Gain: '<Root>/mapping_0_200' incorporates:
     *  Constant: '<Root>/Constant1'
     *  Sum: '<Root>/Sum3'
     */
    u0 = (rtb_phi_refteta_ref_0 - 1250.0) * 0.022857142857142857;

    /* Saturate: '<Root>/Saturation' */
    if (u0 > 200.0) {
      /* Outport: '<Root>/motor_command' */
      lqr_outer_Y.motor_command[i] = 200.0;
    } else if (u0 < 0.0) {
      /* Outport: '<Root>/motor_command' */
      lqr_outer_Y.motor_command[i] = 0.0;
    } else {
      /* Outport: '<Root>/motor_command' */
      lqr_outer_Y.motor_command[i] = u0;
    }

    /* End of Saturate: '<Root>/Saturation' */

    /* Outport: '<Root>/motor_speed' */
    lqr_outer_Y.motor_speed[i] = rtb_Clock;

    /* Outport: '<Root>/motor_RPM' */
    lqr_outer_Y.motor_RPM[i] = rtb_phi_refteta_ref_0;
  }

  /* Clock: '<Root>/Clock' */
  rtb_Clock = (&lqr_outer_M)->Timing.t[0];

  /* MATLAB Function: '<Root>/MATLAB Function' */
  /* MATLAB Function 'MATLAB Function': '<S2>:1' */
  /* '<S2>:1:2' x = 0; */
  /* '<S2>:1:2' y = 0; */
  /* '<S2>:1:2' z = 0; */
  /* '<S2>:1:2' psi = 0; */
  /* '<S2>:1:3' if t <= 25 */
  if (rtb_Clock <= 25.0) {
    /* '<S2>:1:4' x = 0; */
    x = 0;

    /* '<S2>:1:5' y = 0; */
    /* '<S2>:1:6' z = 0.5; */
    rtb_Clock = 0.5;

    /* '<S2>:1:7' psi = 0; */
  } else if (rtb_Clock <= 75.0) {
    /* '<S2>:1:8' elseif t <= 75 */
    /* '<S2>:1:9' x = -1; */
    x = -1;

    /* '<S2>:1:10' y = 0; */
    /* '<S2>:1:11' z = 0.5; */
    rtb_Clock = 0.5;

    /* '<S2>:1:12' psi = 0; */
    /*  elseif t <= 75 */
    /*      x = -1; */
    /*      y = 0; */
    /*      z = 0.5; */
    /*      psi = 0; */
    /*  elseif t <= 110 */
    /*      x = -1; */
    /*      y = 0; */
    /*      z = 0.5; */
    /*      psi = pi/6; */
  } else {
    /* '<S2>:1:23' else */
    /* '<S2>:1:24' x = -1; */
    x = -1;

    /* '<S2>:1:25' y = 0; */
    /* '<S2>:1:26' z = 0; */
    rtb_Clock = 0.0;

    /* '<S2>:1:27' psi = 0; */
  }

  /* Outport: '<Root>/x_ref' incorporates:
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  /*  if t <= 30 */
  /*      x = 0; */
  /*      y = 0;  */
  /*      z = 0.5; */
  /*      psi = 0; */
  /*  else */
  /*      x = 0; */
  /*      y = 0; */
  /*      z = 0; */
  /*      psi = 0; */
  /*  end */
  /* '<S2>:1:40' ref = [x;y;z;psi]; */
  lqr_outer_Y.x_ref = x;

  /* Outport: '<Root>/y_ref' */
  lqr_outer_Y.y_ref = 0.0;

  /* Outport: '<Root>/z_ref' incorporates:
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  lqr_outer_Y.z_ref = rtb_Clock;

  /* Outport: '<Root>/psi_ref' */
  lqr_outer_Y.psi_ref = 0.0;

  /* Sum: '<S1>/Sum4' incorporates:
   *  Inport: '<Root>/X'
   */
  lqr_outer_B.Sum4 = 0.0 - lqr_outer_U.X[8];

  /* Gain: '<S3>/ ' incorporates:
   *  Integrator: '<S3>/Integrator'
   *  Sum: '<S3>/Sum'
   */
  tmp_1[0] = -0.0 * lqr_outer_X.Integrator_CSTATE_b[0] + -0.010000000000000023 *
    lqr_outer_X.Integrator_CSTATE_b[1];
  tmp_1[1] = 0.00999999999999999 * lqr_outer_X.Integrator_CSTATE_b[0];
  tmp_1[1] += -0.0 * lqr_outer_X.Integrator_CSTATE_b[1];
  for (i = 0; i < 2; i++) {
    /* Gain: '<S3>/                   ' incorporates:
     *  Inport: '<Root>/X'
     *  SignalConversion: '<S3>/TmpSignal ConversionAt                   Inport1'
     *  Sum: '<S3>/Sum'
     */
    rtb_phi_refteta_ref_0 = lqr_outer_ConstP._Gain_a[i + 6] * lqr_outer_U.X[4] +
      (lqr_outer_ConstP._Gain_a[i + 4] * lqr_outer_U.X[3] +
       (lqr_outer_ConstP._Gain_a[i + 2] * lqr_outer_U.X[1] +
        lqr_outer_ConstP._Gain_a[i] * lqr_outer_U.X[0]));

    /* Sum: '<S3>/Sum' */
    rtb_phi_refteta_ref[i] = tmp_1[i] - rtb_phi_refteta_ref_0;
  }

  /* Saturate: '<S1>/pitch' */
  if (rtb_phi_refteta_ref[1] > 0.52359877559829882) {
    rtb_phi_refteta_ref_0 = 0.52359877559829882;
  } else if (rtb_phi_refteta_ref[1] < -0.52359877559829882) {
    rtb_phi_refteta_ref_0 = -0.52359877559829882;
  } else {
    rtb_phi_refteta_ref_0 = rtb_phi_refteta_ref[1];
  }

  /* End of Saturate: '<S1>/pitch' */

  /* Sum: '<S1>/Sum5' incorporates:
   *  Inport: '<Root>/X'
   */
  lqr_outer_B.Sum5 = rtb_phi_refteta_ref_0 - lqr_outer_U.X[7];

  /* Saturate: '<S1>/roll' */
  if (rtb_phi_refteta_ref[0] > 0.52359877559829882) {
    rtb_phi_refteta_ref_0 = 0.52359877559829882;
  } else if (rtb_phi_refteta_ref[0] < -0.52359877559829882) {
    rtb_phi_refteta_ref_0 = -0.52359877559829882;
  } else {
    rtb_phi_refteta_ref_0 = rtb_phi_refteta_ref[0];
  }

  /* End of Saturate: '<S1>/roll' */

  /* Sum: '<S1>/Sum6' incorporates:
   *  Inport: '<Root>/X'
   */
  lqr_outer_B.Sum6 = rtb_phi_refteta_ref_0 - lqr_outer_U.X[6];

  /* Sum: '<S1>/Sum7' incorporates:
   *  Inport: '<Root>/X'
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  lqr_outer_B.Sum7 = rtb_Clock - lqr_outer_U.X[2];

  /* Sum: '<S3>/Sum1' incorporates:
   *  Inport: '<Root>/X'
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  lqr_outer_B.Sum1 = (real_T)x - lqr_outer_U.X[0];

  /* Sum: '<S3>/Sum2' incorporates:
   *  Inport: '<Root>/X'
   */
  lqr_outer_B.Sum2 = 0.0 - lqr_outer_U.X[1];
  if (rtmIsMajorTimeStep((&lqr_outer_M))) {
    rt_ertODEUpdateContinuousStates(&(&lqr_outer_M)->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++(&lqr_outer_M)->Timing.clockTick0)) {
      ++(&lqr_outer_M)->Timing.clockTickH0;
    }

    (&lqr_outer_M)->Timing.t[0] = rtsiGetSolverStopTime(&(&lqr_outer_M)
      ->solverInfo);

    {
      /* Update absolute timer for sample time: [0.01s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.01, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      (&lqr_outer_M)->Timing.clockTick1++;
      if (!(&lqr_outer_M)->Timing.clockTick1) {
        (&lqr_outer_M)->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void lqr_outerModelClass::lqr_outer_derivatives()
{
  XDot_lqr_outer_T *_rtXdot;
  _rtXdot = ((XDot_lqr_outer_T *) (&lqr_outer_M)->derivs);

  /* Derivatives for Integrator: '<S1>/Integrator' */
  _rtXdot->Integrator_CSTATE[0] = lqr_outer_B.Sum7;
  _rtXdot->Integrator_CSTATE[1] = lqr_outer_B.Sum6;
  _rtXdot->Integrator_CSTATE[2] = lqr_outer_B.Sum5;
  _rtXdot->Integrator_CSTATE[3] = lqr_outer_B.Sum4;

  /* Derivatives for Integrator: '<S3>/Integrator' */
  _rtXdot->Integrator_CSTATE_b[0] = lqr_outer_B.Sum1;
  _rtXdot->Integrator_CSTATE_b[1] = lqr_outer_B.Sum2;
}

/* Model initialize function */
void lqr_outerModelClass::initialize()
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)(&lqr_outer_M), 0,
                sizeof(RT_MODEL_lqr_outer_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&(&lqr_outer_M)->solverInfo, &(&lqr_outer_M)
                          ->Timing.simTimeStep);
    rtsiSetTPtr(&(&lqr_outer_M)->solverInfo, &rtmGetTPtr((&lqr_outer_M)));
    rtsiSetStepSizePtr(&(&lqr_outer_M)->solverInfo, &(&lqr_outer_M)
                       ->Timing.stepSize0);
    rtsiSetdXPtr(&(&lqr_outer_M)->solverInfo, &(&lqr_outer_M)->derivs);
    rtsiSetContStatesPtr(&(&lqr_outer_M)->solverInfo, (real_T **) &(&lqr_outer_M)
                         ->contStates);
    rtsiSetNumContStatesPtr(&(&lqr_outer_M)->solverInfo, &(&lqr_outer_M)
      ->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&lqr_outer_M)->solverInfo, &(&lqr_outer_M
      )->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&lqr_outer_M)->solverInfo,
      &(&lqr_outer_M)->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&lqr_outer_M)->solverInfo,
      &(&lqr_outer_M)->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&(&lqr_outer_M)->solverInfo, (&rtmGetErrorStatus
      ((&lqr_outer_M))));
    rtsiSetRTModelPtr(&(&lqr_outer_M)->solverInfo, (&lqr_outer_M));
  }

  rtsiSetSimTimeStep(&(&lqr_outer_M)->solverInfo, MAJOR_TIME_STEP);
  (&lqr_outer_M)->intgData.y = (&lqr_outer_M)->odeY;
  (&lqr_outer_M)->intgData.f[0] = (&lqr_outer_M)->odeF[0];
  (&lqr_outer_M)->intgData.f[1] = (&lqr_outer_M)->odeF[1];
  (&lqr_outer_M)->intgData.f[2] = (&lqr_outer_M)->odeF[2];
  (&lqr_outer_M)->intgData.f[3] = (&lqr_outer_M)->odeF[3];
  (&lqr_outer_M)->intgData.f[4] = (&lqr_outer_M)->odeF[4];
  (&lqr_outer_M)->intgData.f[5] = (&lqr_outer_M)->odeF[5];
  getRTM()->contStates = ((X_lqr_outer_T *) &lqr_outer_X);
  rtsiSetSolverData(&(&lqr_outer_M)->solverInfo, (void *)&(&lqr_outer_M)
                    ->intgData);
  rtsiSetSolverName(&(&lqr_outer_M)->solverInfo,"ode5");
  rtmSetTPtr(getRTM(), &(&lqr_outer_M)->Timing.tArray[0]);
  (&lqr_outer_M)->Timing.stepSize0 = 0.01;

  /* block I/O */
  (void) memset(((void *) &lqr_outer_B), 0,
                sizeof(B_lqr_outer_T));

  /* states (continuous) */
  {
    (void) memset((void *)&lqr_outer_X, 0,
                  sizeof(X_lqr_outer_T));
  }

  /* external inputs */
  (void)memset((void *)&lqr_outer_U, 0, sizeof(ExtU_lqr_outer_T));

  /* external outputs */
  (void) memset((void *)&lqr_outer_Y, 0,
                sizeof(ExtY_lqr_outer_T));

  /* InitializeConditions for Integrator: '<S1>/Integrator' */
  lqr_outer_X.Integrator_CSTATE[0] = 0.0;
  lqr_outer_X.Integrator_CSTATE[1] = 0.0;
  lqr_outer_X.Integrator_CSTATE[2] = 0.0;
  lqr_outer_X.Integrator_CSTATE[3] = 0.0;

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  lqr_outer_X.Integrator_CSTATE_b[0] = 0.0;
  lqr_outer_X.Integrator_CSTATE_b[1] = 0.0;
}

/* Model terminate function */
void lqr_outerModelClass::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
lqr_outerModelClass::lqr_outerModelClass()
{
}

/* Destructor */
lqr_outerModelClass::~lqr_outerModelClass()
{
  /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_lqr_outer_T * lqr_outerModelClass::getRTM()
{
  return (&lqr_outer_M);
}
