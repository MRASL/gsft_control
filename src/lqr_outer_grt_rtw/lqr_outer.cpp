/*
 * lqr_outer.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_outer".
 *
 * Model version              : 1.576
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Mon Jan 22 22:28:19 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Passed (1), Warnings (3), Error (0)
 */

#include "lqr_outer.h"
#include "lqr_outer_private.h"

static void rate_scheduler(RT_MODEL_lqr_outer_T *const lqr_outer_M);

/*
 *   This function updates active task flag for each subrate.
 * The function is called at model base rate, hence the
 * generated code self-manages all its subrates.
 */
static void rate_scheduler(RT_MODEL_lqr_outer_T *const lqr_outer_M)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (lqr_outer_M->Timing.TaskCounters.TID[2])++;
  if ((lqr_outer_M->Timing.TaskCounters.TID[2]) > 1) {/* Sample time: [0.02s, 0.0s] */
    lqr_outer_M->Timing.TaskCounters.TID[2] = 0;
  }
}

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
  int_T nXc = 4;
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
  int32_T y;
  real_T rtb_Sum2_h[4];
  real_T tmp[8];
  real_T rtb_u_0[4];
  real_T tmp_0[4];
  real_T rtb_xddydd_idx_0;
  real_T rtb_xddydd_idx_1;
  real_T rtb_rads_to_RPM;
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

  /* RateTransition: '<S3>/Rate Transition2' incorporates:
   *  Inport: '<Root>/X'
   */
  if ((rtmIsMajorTimeStep((&lqr_outer_M)) &&
       (&lqr_outer_M)->Timing.TaskCounters.TID[1] == 0) && (rtmIsMajorTimeStep((
         &lqr_outer_M)) &&
       (&lqr_outer_M)->Timing.TaskCounters.TID[2] == 0)) {
    memcpy(&lqr_outer_B.RateTransition2[0], &lqr_outer_U.X[0], 12U * sizeof
           (real_T));
  }

  /* End of RateTransition: '<S3>/Rate Transition2' */
  if (rtmIsMajorTimeStep((&lqr_outer_M)) &&
      (&lqr_outer_M)->Timing.TaskCounters.TID[2] == 0) {
    /* Gain: '<S3>/                   ' incorporates:
     *  SignalConversion: '<S3>/TmpSignal ConversionAt                   Inport1'
     */
    for (x = 0; x < 2; x++) {
      lqr_outer_B.u[x] = 0.0;
      lqr_outer_B.u[x] += lqr_outer_ConstP._Gain_a[x] *
        lqr_outer_B.RateTransition2[0];
      lqr_outer_B.u[x] += lqr_outer_ConstP._Gain_a[x + 2] *
        lqr_outer_B.RateTransition2[1];
      lqr_outer_B.u[x] += lqr_outer_ConstP._Gain_a[x + 4] *
        lqr_outer_B.RateTransition2[3];
      lqr_outer_B.u[x] += lqr_outer_ConstP._Gain_a[x + 6] *
        lqr_outer_B.RateTransition2[4];
    }

    /* End of Gain: '<S3>/                   ' */
  }

  /* Sum: '<S3>/Sum' incorporates:
   *  Gain: '<S3>/ '
   *  Integrator: '<S3>/Integrator'
   */
  rtb_xddydd_idx_0 = (-0.0 * lqr_outer_X.Integrator_CSTATE_b[0] +
                      -0.099999999999999936 * lqr_outer_X.Integrator_CSTATE_b[1])
    - lqr_outer_B.u[0];
  rtb_xddydd_idx_1 = (0.099999999999999756 * lqr_outer_X.Integrator_CSTATE_b[0]
                      + -0.0 * lqr_outer_X.Integrator_CSTATE_b[1]) -
    lqr_outer_B.u[1];

  /* Fcn: '<S3>/Fcn1' */
  lqr_outer_B.Fcn1 = rtb_xddydd_idx_0 * std::cos(lqr_outer_B.RateTransition2[8])
    + rtb_xddydd_idx_1 * std::sin(lqr_outer_B.RateTransition2[8]);

  /* Fcn: '<S3>/Fcn' */
  lqr_outer_B.Fcn = -rtb_xddydd_idx_0 * std::sin(lqr_outer_B.RateTransition2[8])
    + rtb_xddydd_idx_1 * std::cos(lqr_outer_B.RateTransition2[8]);

  /* ZeroOrderHold: '<S3>/Zero-Order Hold' */
  if (rtmIsMajorTimeStep((&lqr_outer_M)) &&
      (&lqr_outer_M)->Timing.TaskCounters.TID[2] == 0) {
    lqr_outer_B.ZeroOrderHold[0] = lqr_outer_B.Fcn1;
    lqr_outer_B.ZeroOrderHold[1] = lqr_outer_B.Fcn;

    /* Saturate: '<S1>/roll' */
    if (lqr_outer_B.ZeroOrderHold[0] > 0.52359877559829882) {
      lqr_outer_B.roll = 0.52359877559829882;
    } else if (lqr_outer_B.ZeroOrderHold[0] < -0.52359877559829882) {
      lqr_outer_B.roll = -0.52359877559829882;
    } else {
      lqr_outer_B.roll = lqr_outer_B.ZeroOrderHold[0];
    }

    /* End of Saturate: '<S1>/roll' */

    /* Saturate: '<S1>/pitch' */
    if (lqr_outer_B.ZeroOrderHold[1] > 0.52359877559829882) {
      lqr_outer_B.pitch = 0.52359877559829882;
    } else if (lqr_outer_B.ZeroOrderHold[1] < -0.52359877559829882) {
      lqr_outer_B.pitch = -0.52359877559829882;
    } else {
      lqr_outer_B.pitch = lqr_outer_B.ZeroOrderHold[1];
    }

    /* End of Saturate: '<S1>/pitch' */
  }

  /* End of ZeroOrderHold: '<S3>/Zero-Order Hold' */

  /* SignalConversion: '<S1>/TmpSignal ConversionAt                   Inport1' incorporates:
   *  Gain: '<S1>/                   '
   *  Inport: '<Root>/X'
   */
  tmp[0] = lqr_outer_U.X[2];
  for (x = 0; x < 7; x++) {
    tmp[x + 1] = lqr_outer_U.X[5 + x];
  }

  /* End of SignalConversion: '<S1>/TmpSignal ConversionAt                   Inport1' */

  /* Sum: '<S1>/Sum' incorporates:
   *  Gain: '<S1>/ '
   *  Integrator: '<S1>/Integrator'
   */
  rtb_u_0[0] = 9.9999999999999751 * lqr_outer_X.Integrator_CSTATE[0] + -0.0 *
    lqr_outer_X.Integrator_CSTATE[1];
  rtb_u_0[1] = lqr_outer_B.roll;
  rtb_u_0[2] = lqr_outer_B.pitch;
  rtb_u_0[3] = -0.0 * lqr_outer_X.Integrator_CSTATE[0] + 0.036514837167011018 *
    lqr_outer_X.Integrator_CSTATE[1];
  for (x = 0; x < 4; x++) {
    /* Gain: '<S1>/                   ' incorporates:
     *  Sum: '<S1>/Sum'
     */
    tmp_0[x] = 0.0;
    for (y = 0; y < 8; y++) {
      tmp_0[x] += lqr_outer_ConstP._Gain_c[(y << 2) + x] * tmp[y];
    }

    /* Sum: '<Root>/Sum2' incorporates:
     *  Constant: '<Root>/              '
     *  Sum: '<S1>/Sum'
     */
    rtb_Sum2_h[x] = (rtb_u_0[x] - tmp_0[x]) + lqr_outer_ConstP._Value[x];
  }

  /* Outport: '<Root>/virtual_control' */
  lqr_outer_Y.virtual_control[0] = rtb_Sum2_h[0];
  lqr_outer_Y.virtual_control[1] = rtb_Sum2_h[1];
  lqr_outer_Y.virtual_control[2] = rtb_Sum2_h[2];
  lqr_outer_Y.virtual_control[3] = rtb_Sum2_h[3];
  for (x = 0; x < 6; x++) {
    /* Gain: '<Root>/Gain' incorporates:
     *  Gain: '<Root>/Gain2'
     */
    rtb_xddydd_idx_0 = lqr_outer_ConstP.Gain_Gain[x + 18] * rtb_Sum2_h[3] +
      (lqr_outer_ConstP.Gain_Gain[x + 12] * rtb_Sum2_h[2] +
       (lqr_outer_ConstP.Gain_Gain[x + 6] * rtb_Sum2_h[1] +
        lqr_outer_ConstP.Gain_Gain[x] * rtb_Sum2_h[0]));

    /* Sqrt: '<Root>/Sqrt1' incorporates:
     *  Gain: '<Root>/Gain2'
     */
    rtb_xddydd_idx_1 = std::sqrt(149253.73134328358 * rtb_xddydd_idx_0);

    /* Gain: '<Root>/rads_to_RPM' */
    rtb_rads_to_RPM = 9.5493 * rtb_xddydd_idx_1;

    /* Gain: '<Root>/mapping_0_200' incorporates:
     *  Constant: '<Root>/Constant1'
     *  Sum: '<Root>/Sum3'
     */
    rtb_xddydd_idx_0 = (rtb_rads_to_RPM - 1250.0) * 0.022857142857142857;

    /* Saturate: '<Root>/Saturation' */
    if (rtb_xddydd_idx_0 > 200.0) {
      /* Outport: '<Root>/motor_command' */
      lqr_outer_Y.motor_command[x] = 200.0;
    } else if (rtb_xddydd_idx_0 < 0.0) {
      /* Outport: '<Root>/motor_command' */
      lqr_outer_Y.motor_command[x] = 0.0;
    } else {
      /* Outport: '<Root>/motor_command' */
      lqr_outer_Y.motor_command[x] = rtb_xddydd_idx_0;
    }

    /* End of Saturate: '<Root>/Saturation' */

    /* Outport: '<Root>/motor_speed' */
    lqr_outer_Y.motor_speed[x] = rtb_xddydd_idx_1;

    /* Outport: '<Root>/motor_RPM' */
    lqr_outer_Y.motor_RPM[x] = rtb_rads_to_RPM;
  }

  /* Clock: '<Root>/Clock' */
  rtb_xddydd_idx_0 = (&lqr_outer_M)->Timing.t[0];

  /* MATLAB Function: '<Root>/MATLAB Function' */
  /* MATLAB Function 'MATLAB Function': '<S2>:1' */
  /* '<S2>:1:2' x = 0; */
  /* '<S2>:1:2' y = 0; */
  /* '<S2>:1:2' z = 0; */
  /* '<S2>:1:2' psi = 0; */
  /* '<S2>:1:3' if t <= 10 */
  if (rtb_xddydd_idx_0 <= 10.0) {
    /* '<S2>:1:4' x = 0; */
    x = 0;

    /* '<S2>:1:5' y = 0; */
    y = 0;

    /* '<S2>:1:6' z = 0.5; */
    /* '<S2>:1:7' psi = 0; */
  } else if (rtb_xddydd_idx_0 <= 30.0) {
    /* '<S2>:1:8' elseif t <= 30 */
    /* '<S2>:1:9' x = -1; */
    x = -1;

    /* '<S2>:1:10' y = 0; */
    y = 0;

    /* '<S2>:1:11' z = 0.5; */
    /* '<S2>:1:12' psi = 0; */
  } else if (rtb_xddydd_idx_0 <= 50.0) {
    /* '<S2>:1:13' elseif t <= 50 */
    /* '<S2>:1:14' x = -1; */
    x = -1;

    /* '<S2>:1:15' y = 1; */
    y = 1;

    /* '<S2>:1:16' z = 0.5; */
    /* '<S2>:1:17' psi = 0; */
  } else {
    /* '<S2>:1:18' else */
    /* '<S2>:1:19' x = -1; */
    x = -1;

    /* '<S2>:1:20' y = 1; */
    y = 1;

    /* '<S2>:1:21' z = 0.5; */
    /* '<S2>:1:22' psi = 0; */
  }

  /* '<S2>:1:24' ref = [x;y;z;psi]; */
  lqr_outer_B.ref[0] = x;
  lqr_outer_B.ref[1] = y;
  lqr_outer_B.ref[2] = 0.5;
  lqr_outer_B.ref[3] = 0.0;

  /* End of MATLAB Function: '<Root>/MATLAB Function' */

  /* Outport: '<Root>/ref' */
  lqr_outer_Y.ref[0] = lqr_outer_B.ref[0];
  lqr_outer_Y.ref[1] = lqr_outer_B.ref[1];
  lqr_outer_Y.ref[2] = lqr_outer_B.ref[2];
  lqr_outer_Y.ref[3] = lqr_outer_B.ref[3];

  /* Saturate: '<S1>/z' */
  if (lqr_outer_B.ref[2] > 1.0) {
    rtb_xddydd_idx_0 = 1.0;
  } else if (lqr_outer_B.ref[2] < 0.0) {
    rtb_xddydd_idx_0 = 0.0;
  } else {
    rtb_xddydd_idx_0 = lqr_outer_B.ref[2];
  }

  /* End of Saturate: '<S1>/z' */

  /* Sum: '<S1>/Sum7' incorporates:
   *  Inport: '<Root>/X'
   */
  lqr_outer_B.Sum7 = rtb_xddydd_idx_0 - lqr_outer_U.X[2];

  /* Saturate: '<S1>/yaw' */
  if (lqr_outer_B.ref[3] > 6.2831853071795862) {
    rtb_xddydd_idx_0 = 6.2831853071795862;
  } else if (lqr_outer_B.ref[3] < -6.2831853071795862) {
    rtb_xddydd_idx_0 = -6.2831853071795862;
  } else {
    rtb_xddydd_idx_0 = lqr_outer_B.ref[3];
  }

  /* End of Saturate: '<S1>/yaw' */

  /* Sum: '<S1>/Sum4' incorporates:
   *  Inport: '<Root>/X'
   */
  rtb_xddydd_idx_0 -= lqr_outer_U.X[8];

  /* Saturate: '<S1>/psi_e' */
  if (rtb_xddydd_idx_0 > 0.52359877559829882) {
    lqr_outer_B.psi_e = 0.52359877559829882;
  } else if (rtb_xddydd_idx_0 < -0.52359877559829882) {
    lqr_outer_B.psi_e = -0.52359877559829882;
  } else {
    lqr_outer_B.psi_e = rtb_xddydd_idx_0;
  }

  /* End of Saturate: '<S1>/psi_e' */

  /* RateTransition: '<S3>/Rate Transition' incorporates:
   *  RateTransition: '<S3>/Rate Transition1'
   */
  if ((rtmIsMajorTimeStep((&lqr_outer_M)) &&
       (&lqr_outer_M)->Timing.TaskCounters.TID[1] == 0) && (rtmIsMajorTimeStep((
         &lqr_outer_M)) &&
       (&lqr_outer_M)->Timing.TaskCounters.TID[2] == 0)) {
    lqr_outer_B.RateTransition = lqr_outer_B.ref[0];
    lqr_outer_B.RateTransition1 = lqr_outer_B.ref[1];
  }

  /* End of RateTransition: '<S3>/Rate Transition' */
  if (rtmIsMajorTimeStep((&lqr_outer_M)) &&
      (&lqr_outer_M)->Timing.TaskCounters.TID[2] == 0) {
    /* Saturate: '<S3>/x' */
    if (lqr_outer_B.RateTransition > 1.0) {
      rtb_xddydd_idx_0 = 1.0;
    } else if (lqr_outer_B.RateTransition < -1.0) {
      rtb_xddydd_idx_0 = -1.0;
    } else {
      rtb_xddydd_idx_0 = lqr_outer_B.RateTransition;
    }

    /* End of Saturate: '<S3>/x' */

    /* Sum: '<S3>/Sum1' */
    rtb_xddydd_idx_0 -= lqr_outer_B.RateTransition2[0];

    /* Saturate: '<S3>/xe' */
    if (rtb_xddydd_idx_0 > 1.0) {
      lqr_outer_B.xe = 1.0;
    } else if (rtb_xddydd_idx_0 < -1.0) {
      lqr_outer_B.xe = -1.0;
    } else {
      lqr_outer_B.xe = rtb_xddydd_idx_0;
    }

    /* End of Saturate: '<S3>/xe' */

    /* Saturate: '<S3>/y' */
    if (lqr_outer_B.RateTransition1 > 1.0) {
      rtb_xddydd_idx_0 = 1.0;
    } else if (lqr_outer_B.RateTransition1 < -1.0) {
      rtb_xddydd_idx_0 = -1.0;
    } else {
      rtb_xddydd_idx_0 = lqr_outer_B.RateTransition1;
    }

    /* End of Saturate: '<S3>/y' */

    /* Sum: '<S3>/Sum2' */
    rtb_xddydd_idx_0 -= lqr_outer_B.RateTransition2[1];

    /* Saturate: '<S3>/ye' */
    if (rtb_xddydd_idx_0 > 1.0) {
      lqr_outer_B.ye = 1.0;
    } else if (rtb_xddydd_idx_0 < -1.0) {
      lqr_outer_B.ye = -1.0;
    } else {
      lqr_outer_B.ye = rtb_xddydd_idx_0;
    }

    /* End of Saturate: '<S3>/ye' */
  }

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

    rate_scheduler((&lqr_outer_M));
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void lqr_outerModelClass::lqr_outer_derivatives()
{
  XDot_lqr_outer_T *_rtXdot;
  _rtXdot = ((XDot_lqr_outer_T *) (&lqr_outer_M)->derivs);

  /* Derivatives for Integrator: '<S1>/Integrator' */
  _rtXdot->Integrator_CSTATE[0] = lqr_outer_B.Sum7;
  _rtXdot->Integrator_CSTATE[1] = lqr_outer_B.psi_e;

  /* Derivatives for Integrator: '<S3>/Integrator' */
  _rtXdot->Integrator_CSTATE_b[0] = lqr_outer_B.xe;
  _rtXdot->Integrator_CSTATE_b[1] = lqr_outer_B.ye;
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

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  lqr_outer_X.Integrator_CSTATE_b[0] = 0.0;

  /* InitializeConditions for Integrator: '<S1>/Integrator' */
  lqr_outer_X.Integrator_CSTATE[1] = 0.0;

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
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
