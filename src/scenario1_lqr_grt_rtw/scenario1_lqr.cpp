/*
 * scenario1_lqr.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "scenario1_lqr".
 *
 * Model version              : 1.679
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Mon Feb  5 21:23:44 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Passed (1), Warnings (3), Error (0)
 */

#include "scenario1_lqr.h"
#include "scenario1_lqr_private.h"

static void rate_scheduler(RT_MODEL_scenario1_lqr_T *const scenario1_lqr_M);

/*
 *   This function updates active task flag for each subrate.
 * The function is called at model base rate, hence the
 * generated code self-manages all its subrates.
 */
static void rate_scheduler(RT_MODEL_scenario1_lqr_T *const scenario1_lqr_M)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (scenario1_lqr_M->Timing.TaskCounters.TID[2])++;
  if ((scenario1_lqr_M->Timing.TaskCounters.TID[2]) > 1) {/* Sample time: [0.02s, 0.0s] */
    scenario1_lqr_M->Timing.TaskCounters.TID[2] = 0;
  }
}

/*
 * This function updates continuous states using the ODE5 fixed-step
 * solver algorithm
 */
void scenario1_lqrModelClass::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
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
  scenario1_lqr_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE5_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[0]);
  rtsiSetdX(si, f1);
  this->step();
  scenario1_lqr_derivatives();

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
  scenario1_lqr_derivatives();

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
  scenario1_lqr_derivatives();

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
  scenario1_lqr_derivatives();

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
  scenario1_lqr_derivatives();

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
void scenario1_lqrModelClass::step()
{
  real_T y;
  real_T z;
  real_T psi;
  real_T rtb_VectorConcatenate[12];
  real_T rtb_u_i[6];
  real_T rtb_T_f[6];
  real_T rtb_Clock;
  int32_T i;
  real_T tmp;
  real_T u0;
  if (rtmIsMajorTimeStep((&scenario1_lqr_M))) {
    /* set solver stop time */
    if (!((&scenario1_lqr_M)->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&(&scenario1_lqr_M)->solverInfo, (((&scenario1_lqr_M)
        ->Timing.clockTickH0 + 1) * (&scenario1_lqr_M)->Timing.stepSize0 *
        4294967296.0));
    } else {
      rtsiSetSolverStopTime(&(&scenario1_lqr_M)->solverInfo, (((&scenario1_lqr_M)
        ->Timing.clockTick0 + 1) * (&scenario1_lqr_M)->Timing.stepSize0 +
        (&scenario1_lqr_M)->Timing.clockTickH0 * (&scenario1_lqr_M)
        ->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep((&scenario1_lqr_M))) {
    (&scenario1_lqr_M)->Timing.t[0] = rtsiGetT(&(&scenario1_lqr_M)->solverInfo);
  }

  /* Clock: '<Root>/Clock' */
  rtb_Clock = (&scenario1_lqr_M)->Timing.t[0];

  /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn1' incorporates:
   *  Inport: '<Root>/X0'
   */
  rtb_VectorConcatenate[0] = scenario1_lqr_U.X0[0];
  rtb_VectorConcatenate[1] = scenario1_lqr_U.X0[1];
  rtb_VectorConcatenate[2] = scenario1_lqr_U.X0[2];

  /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn2' */
  for (i = 0; i < 5; i++) {
    rtb_VectorConcatenate[i + 3] = 0.0;
  }

  /* End of SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn2' */

  /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn3' incorporates:
   *  Inport: '<Root>/X0'
   */
  rtb_VectorConcatenate[8] = scenario1_lqr_U.X0[3];

  /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn4' */
  rtb_VectorConcatenate[9] = 0.0;
  rtb_VectorConcatenate[10] = 0.0;
  rtb_VectorConcatenate[11] = 0.0;

  /* Sum: '<Root>/Sum' incorporates:
   *  Inport: '<Root>/X'
   */
  for (i = 0; i < 12; i++) {
    scenario1_lqr_B.dX[i] = scenario1_lqr_U.X[i] - rtb_VectorConcatenate[i];
  }

  /* End of Sum: '<Root>/Sum' */

  /* RateTransition: '<Root>/Rate Transition5' */
  if ((rtmIsMajorTimeStep((&scenario1_lqr_M)) &&
       (&scenario1_lqr_M)->Timing.TaskCounters.TID[1] == 0) &&
      (rtmIsMajorTimeStep((&scenario1_lqr_M)) &&
       (&scenario1_lqr_M)->Timing.TaskCounters.TID[2] == 0)) {
    memcpy(&scenario1_lqr_B.RateTransition5[0], &scenario1_lqr_B.dX[0], 12U *
           sizeof(real_T));
  }

  /* End of RateTransition: '<Root>/Rate Transition5' */
  if (rtmIsMajorTimeStep((&scenario1_lqr_M)) &&
      (&scenario1_lqr_M)->Timing.TaskCounters.TID[2] == 0) {
    /* Gain: '<S6>/                    ' incorporates:
     *  SignalConversion: '<S6>/TmpSignal ConversionAt                    Inport1'
     */
    scenario1_lqr_B.u = 0.24406724034409538 * scenario1_lqr_B.RateTransition5[0]
      + 0.21931352821081743 * scenario1_lqr_B.RateTransition5[3];
  }

  /* Sum: '<S6>/Sum1' incorporates:
   *  Gain: '<S6>/ '
   *  Integrator: '<S6>/Integrator1'
   */
  scenario1_lqr_B.Sum1 = 0.11952286093343731 *
    scenario1_lqr_X.Integrator1_CSTATE_h - scenario1_lqr_B.u;
  if (rtmIsMajorTimeStep((&scenario1_lqr_M)) &&
      (&scenario1_lqr_M)->Timing.TaskCounters.TID[1] == 0) {
    /* ZeroOrderHold: '<Root>/Zero-Order Hold' */
    scenario1_lqr_B.ZeroOrderHold = scenario1_lqr_B.Sum1;
  }

  if (rtmIsMajorTimeStep((&scenario1_lqr_M)) &&
      (&scenario1_lqr_M)->Timing.TaskCounters.TID[2] == 0) {
    /* Gain: '<S7>/                     ' incorporates:
     *  SignalConversion: '<S7>/TmpSignal ConversionAt                     Inport1'
     */
    scenario1_lqr_B.u_m = -0.31312578517367151 *
      scenario1_lqr_B.RateTransition5[1] + -0.25417198201077457 *
      scenario1_lqr_B.RateTransition5[4];
  }

  /* Sum: '<S7>/Sum1' incorporates:
   *  Gain: '<S7>/  '
   *  Integrator: '<S7>/Integrator1'
   */
  scenario1_lqr_B.Sum1_i = -0.17320508075688759 *
    scenario1_lqr_X.Integrator1_CSTATE_j - scenario1_lqr_B.u_m;
  if (rtmIsMajorTimeStep((&scenario1_lqr_M)) &&
      (&scenario1_lqr_M)->Timing.TaskCounters.TID[1] == 0) {
    /* ZeroOrderHold: '<Root>/Zero-Order Hold1' */
    scenario1_lqr_B.ZeroOrderHold1 = scenario1_lqr_B.Sum1_i;
  }

  /* Sum: '<Root>/Sum2' incorporates:
   *  Gain: '<S8>/  '
   *  Gain: '<S8>/                     '
   *  Integrator: '<S8>/Integrator1'
   *  SignalConversion: '<S8>/TmpSignal ConversionAt                     Inport1'
   *  Sum: '<S8>/Sum1'
   */
  z = 10.000000000000016 * scenario1_lqr_X.Integrator1_CSTATE -
    (12.219481695651972 * scenario1_lqr_B.dX[2] + 6.2157866455186523 *
     scenario1_lqr_B.dX[5]);

  /* Sum: '<S3>/Sum1' incorporates:
   *  Fcn: '<Root>/Fcn1'
   *  Inport: '<Root>/X'
   *  Saturate: '<S3>/roll'
   */
  u0 = scenario1_lqr_B.ZeroOrderHold1 * std::cos(scenario1_lqr_U.X[8]) +
    scenario1_lqr_B.ZeroOrderHold * std::sin(scenario1_lqr_U.X[8]);
  if (u0 > 0.52359877559829882) {
    u0 = 0.52359877559829882;
  } else {
    if (u0 < -0.52359877559829882) {
      u0 = -0.52359877559829882;
    }
  }

  /* Sum: '<Root>/Sum2' incorporates:
   *  Gain: '<S3>/                    '
   *  SignalConversion: '<S3>/TmpSignal ConversionAt                    Inport1'
   *  Sum: '<S3>/Sum1'
   */
  psi = u0 - (1.1365283480217829 * scenario1_lqr_B.dX[6] + 0.28178545108770076 *
              scenario1_lqr_B.dX[9]);

  /* Sum: '<S5>/Sum1' incorporates:
   *  Fcn: '<Root>/Fcn'
   *  Inport: '<Root>/X'
   *  Saturate: '<S5>/pitch'
   */
  u0 = -scenario1_lqr_B.ZeroOrderHold1 * std::sin(scenario1_lqr_U.X[8]) +
    scenario1_lqr_B.ZeroOrderHold * std::cos(scenario1_lqr_U.X[8]);
  if (u0 > 0.52359877559829882) {
    u0 = 0.52359877559829882;
  } else {
    if (u0 < -0.52359877559829882) {
      u0 = -0.52359877559829882;
    }
  }

  /* Sum: '<Root>/Sum2' incorporates:
   *  Gain: '<S4>/  '
   *  Gain: '<S4>/                     '
   *  Gain: '<S5>/                    '
   *  Integrator: '<S4>/Integrator1'
   *  SignalConversion: '<S4>/TmpSignal ConversionAt                     Inport1'
   *  SignalConversion: '<S5>/TmpSignal ConversionAt                    Inport1'
   *  Sum: '<S4>/Sum1'
   *  Sum: '<S5>/Sum1'
   */
  u0 -= 1.0932700003969249 * scenario1_lqr_B.dX[7] + 0.31722606432660311 *
    scenario1_lqr_B.dX[10];
  tmp = 0.0866025403784437 * scenario1_lqr_X.Integrator1_CSTATE_b -
    (0.21302635355941227 * scenario1_lqr_B.dX[8] + 0.2042678376189192 *
     scenario1_lqr_B.dX[11]);

  /* MATLAB Function 'Actuator_Fault': '<S1>:1' */
  /* '<S1>:1:2' T_f = T; */
  for (i = 0; i < 6; i++) {
    /* Gain: '<Root>/                 ' incorporates:
     *  Sum: '<Root>/Sum2'
     */
    y = scenario1_lqr_ConstP._Gain_m[i + 18] * tmp +
      (scenario1_lqr_ConstP._Gain_m[i + 12] * u0 +
       (scenario1_lqr_ConstP._Gain_m[i + 6] * psi + (z + 15.107400000000002) *
        scenario1_lqr_ConstP._Gain_m[i]));

    /* MATLAB Function: '<Root>/Actuator_Fault' */
    rtb_T_f[i] = y;

    /* Gain: '<Root>/                 ' */
    rtb_u_i[i] = y;
  }

  /* MATLAB Function: '<Root>/Actuator_Fault' */
  /* '<S1>:1:3' if time >= 25 */
  if (rtb_Clock >= 25.0) {
    /* '<S1>:1:4' T1 = T(1)*0.8; */
    /* '<S1>:1:5' T2 = T(2)*0.8; */
    /* '<S1>:1:6' T3 = T(3)*0.8; */
    /* '<S1>:1:7' T4 = T(4)*0.8; */
    /* '<S1>:1:8' T5 = T(5)*0.8; */
    /* '<S1>:1:9' T6 = T(6)*0.8; */
    /* '<S1>:1:10' T_f = [T1;T2;T3;T4;T5;T6]; */
    rtb_T_f[0] = rtb_u_i[0] * 0.8;
    rtb_T_f[1] = rtb_u_i[1] * 0.8;
    rtb_T_f[2] = rtb_u_i[2] * 0.8;
    rtb_T_f[3] = rtb_u_i[3] * 0.8;
    rtb_T_f[4] = rtb_u_i[4] * 0.8;
    rtb_T_f[5] = rtb_u_i[5] * 0.8;
  }

  /* Outport: '<Root>/virtual_control' incorporates:
   *  Sum: '<Root>/Sum2'
   */
  scenario1_lqr_Y.virtual_control[0] = z + 15.107400000000002;
  scenario1_lqr_Y.virtual_control[1] = psi;
  scenario1_lqr_Y.virtual_control[2] = u0;
  scenario1_lqr_Y.virtual_control[3] = tmp;
  for (i = 0; i < 6; i++) {
    /* Sqrt: '<Root>/Sqrt1' incorporates:
     *  Gain: '<Root>/      '
     */
    y = std::sqrt(149253.73134328358 * rtb_T_f[i]);

    /* Gain: '<Root>/rads_to_RPM' */
    z = 9.5493 * y;

    /* Gain: '<Root>/mapping_0_200' incorporates:
     *  Constant: '<Root>/Constant '
     *  Sum: '<Root>/Sum3'
     */
    u0 = (z - 1250.0) * 0.022857142857142857;

    /* Saturate: '<Root>/Saturation' */
    if (u0 > 200.0) {
      /* Outport: '<Root>/motor_command' */
      scenario1_lqr_Y.motor_command[i] = 200.0;
    } else if (u0 < 0.0) {
      /* Outport: '<Root>/motor_command' */
      scenario1_lqr_Y.motor_command[i] = 0.0;
    } else {
      /* Outport: '<Root>/motor_command' */
      scenario1_lqr_Y.motor_command[i] = u0;
    }

    /* End of Saturate: '<Root>/Saturation' */

    /* Outport: '<Root>/motor_speed' */
    scenario1_lqr_Y.motor_speed[i] = y;

    /* Outport: '<Root>/motor_RPM' */
    scenario1_lqr_Y.motor_RPM[i] = z;
  }

  /* MATLAB Function: '<Root>/MATLAB Function' incorporates:
   *  Inport: '<Root>/X0'
   */
  /* MATLAB Function 'MATLAB Function': '<S2>:1' */
  /* '<S2>:1:2' x = X0(1); */
  /* '<S2>:1:2' y = X0(2); */
  /* '<S2>:1:2' z = X0(3); */
  /* '<S2>:1:2' psi = X0(4); */
  /* '<S2>:1:3' if t <= 35 */
  if (rtb_Clock <= 35.0) {
    /* '<S2>:1:4' x = X0(1); */
    rtb_Clock = scenario1_lqr_U.X0[0];

    /* '<S2>:1:5' y = X0(2); */
    y = scenario1_lqr_U.X0[1];

    /* '<S2>:1:6' z = 0.5; */
    z = 0.5;

    /* '<S2>:1:7' psi = X0(4); */
    psi = scenario1_lqr_U.X0[3];
  } else {
    /* '<S2>:1:8' else */
    /* '<S2>:1:9' x = X0(1); */
    rtb_Clock = scenario1_lqr_U.X0[0];

    /* '<S2>:1:10' y = X0(2); */
    y = scenario1_lqr_U.X0[1];

    /* '<S2>:1:11' z = 0.0; */
    z = 0.0;

    /* '<S2>:1:12' psi = X0(4); */
    psi = scenario1_lqr_U.X0[3];
  }

  /* Outport: '<Root>/ref' incorporates:
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  /* '<S2>:1:14' ref = [x;y;z;psi]; */
  scenario1_lqr_Y.ref[0] = rtb_Clock;

  /* Sum: '<Root>/Sum1' incorporates:
   *  Inport: '<Root>/X0'
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  scenario1_lqr_B.d_ref[0] = rtb_Clock - scenario1_lqr_U.X0[0];

  /* Outport: '<Root>/ref' incorporates:
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  scenario1_lqr_Y.ref[1] = y;

  /* Sum: '<Root>/Sum1' incorporates:
   *  Inport: '<Root>/X0'
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  scenario1_lqr_B.d_ref[1] = y - scenario1_lqr_U.X0[1];

  /* Outport: '<Root>/ref' incorporates:
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  scenario1_lqr_Y.ref[2] = z;

  /* Sum: '<Root>/Sum1' incorporates:
   *  Inport: '<Root>/X0'
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  scenario1_lqr_B.d_ref[2] = z - scenario1_lqr_U.X0[2];

  /* Outport: '<Root>/ref' incorporates:
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  scenario1_lqr_Y.ref[3] = psi;

  /* Sum: '<Root>/Sum1' incorporates:
   *  Inport: '<Root>/X0'
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  scenario1_lqr_B.d_ref[3] = psi - scenario1_lqr_U.X0[3];

  /* RateTransition: '<Root>/Rate Transition' incorporates:
   *  RateTransition: '<Root>/Rate Transition1'
   */
  if ((rtmIsMajorTimeStep((&scenario1_lqr_M)) &&
       (&scenario1_lqr_M)->Timing.TaskCounters.TID[1] == 0) &&
      (rtmIsMajorTimeStep((&scenario1_lqr_M)) &&
       (&scenario1_lqr_M)->Timing.TaskCounters.TID[2] == 0)) {
    scenario1_lqr_B.RateTransition = scenario1_lqr_B.d_ref[0];
    scenario1_lqr_B.RateTransition1 = scenario1_lqr_B.d_ref[1];
  }

  /* End of RateTransition: '<Root>/Rate Transition' */

  /* Saturate: '<S4>/yaw' */
  if (scenario1_lqr_B.d_ref[3] > 3.1415926535897931) {
    rtb_Clock = 3.1415926535897931;
  } else if (scenario1_lqr_B.d_ref[3] < -3.1415926535897931) {
    rtb_Clock = -3.1415926535897931;
  } else {
    rtb_Clock = scenario1_lqr_B.d_ref[3];
  }

  /* End of Saturate: '<S4>/yaw' */

  /* Sum: '<S4>/Sum3' */
  u0 = rtb_Clock - scenario1_lqr_B.dX[8];

  /* Saturate: '<S4>/psi_e' */
  if (u0 > 0.78539816339744828) {
    scenario1_lqr_B.psi_e = 0.78539816339744828;
  } else if (u0 < -0.78539816339744828) {
    scenario1_lqr_B.psi_e = -0.78539816339744828;
  } else {
    scenario1_lqr_B.psi_e = u0;
  }

  /* End of Saturate: '<S4>/psi_e' */
  if (rtmIsMajorTimeStep((&scenario1_lqr_M)) &&
      (&scenario1_lqr_M)->Timing.TaskCounters.TID[2] == 0) {
    /* Saturate: '<S6>/x' */
    if (scenario1_lqr_B.RateTransition > 1.0) {
      rtb_Clock = 1.0;
    } else if (scenario1_lqr_B.RateTransition < -1.0) {
      rtb_Clock = -1.0;
    } else {
      rtb_Clock = scenario1_lqr_B.RateTransition;
    }

    /* End of Saturate: '<S6>/x' */

    /* Sum: '<S6>/Sum3' */
    u0 = rtb_Clock - scenario1_lqr_B.RateTransition5[0];

    /* Saturate: '<S6>/xe' */
    if (u0 > 1.0) {
      scenario1_lqr_B.xe = 1.0;
    } else if (u0 < -1.0) {
      scenario1_lqr_B.xe = -1.0;
    } else {
      scenario1_lqr_B.xe = u0;
    }

    /* End of Saturate: '<S6>/xe' */

    /* Saturate: '<S7>/y' */
    if (scenario1_lqr_B.RateTransition1 > 1.0) {
      rtb_Clock = 1.0;
    } else if (scenario1_lqr_B.RateTransition1 < -1.0) {
      rtb_Clock = -1.0;
    } else {
      rtb_Clock = scenario1_lqr_B.RateTransition1;
    }

    /* End of Saturate: '<S7>/y' */

    /* Sum: '<S7>/Sum3' */
    u0 = rtb_Clock - scenario1_lqr_B.RateTransition5[1];

    /* Saturate: '<S7>/ye' */
    if (u0 > 1.0) {
      scenario1_lqr_B.ye = 1.0;
    } else if (u0 < -1.0) {
      scenario1_lqr_B.ye = -1.0;
    } else {
      scenario1_lqr_B.ye = u0;
    }

    /* End of Saturate: '<S7>/ye' */
  }

  /* Saturate: '<S8>/z' */
  if (scenario1_lqr_B.d_ref[2] > 1.0) {
    rtb_Clock = 1.0;
  } else if (scenario1_lqr_B.d_ref[2] < 0.0) {
    rtb_Clock = 0.0;
  } else {
    rtb_Clock = scenario1_lqr_B.d_ref[2];
  }

  /* End of Saturate: '<S8>/z' */

  /* Sum: '<S8>/Sum3' */
  u0 = rtb_Clock - scenario1_lqr_B.dX[2];

  /* Saturate: '<S8>/ze' */
  if (u0 > 0.5) {
    scenario1_lqr_B.ze = 0.5;
  } else if (u0 < -0.5) {
    scenario1_lqr_B.ze = -0.5;
  } else {
    scenario1_lqr_B.ze = u0;
  }

  /* End of Saturate: '<S8>/ze' */
  if (rtmIsMajorTimeStep((&scenario1_lqr_M))) {
    rt_ertODEUpdateContinuousStates(&(&scenario1_lqr_M)->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++(&scenario1_lqr_M)->Timing.clockTick0)) {
      ++(&scenario1_lqr_M)->Timing.clockTickH0;
    }

    (&scenario1_lqr_M)->Timing.t[0] = rtsiGetSolverStopTime(&(&scenario1_lqr_M
      )->solverInfo);

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
      (&scenario1_lqr_M)->Timing.clockTick1++;
      if (!(&scenario1_lqr_M)->Timing.clockTick1) {
        (&scenario1_lqr_M)->Timing.clockTickH1++;
      }
    }

    rate_scheduler((&scenario1_lqr_M));
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void scenario1_lqrModelClass::scenario1_lqr_derivatives()
{
  XDot_scenario1_lqr_T *_rtXdot;
  _rtXdot = ((XDot_scenario1_lqr_T *) (&scenario1_lqr_M)->derivs);

  /* Derivatives for Integrator: '<S8>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = scenario1_lqr_B.ze;

  /* Derivatives for Integrator: '<S6>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_h = scenario1_lqr_B.xe;

  /* Derivatives for Integrator: '<S7>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_j = scenario1_lqr_B.ye;

  /* Derivatives for Integrator: '<S4>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_b = scenario1_lqr_B.psi_e;
}

/* Model initialize function */
void scenario1_lqrModelClass::initialize()
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)(&scenario1_lqr_M), 0,
                sizeof(RT_MODEL_scenario1_lqr_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&(&scenario1_lqr_M)->solverInfo, &(&scenario1_lqr_M)
                          ->Timing.simTimeStep);
    rtsiSetTPtr(&(&scenario1_lqr_M)->solverInfo, &rtmGetTPtr((&scenario1_lqr_M)));
    rtsiSetStepSizePtr(&(&scenario1_lqr_M)->solverInfo, &(&scenario1_lqr_M)
                       ->Timing.stepSize0);
    rtsiSetdXPtr(&(&scenario1_lqr_M)->solverInfo, &(&scenario1_lqr_M)->derivs);
    rtsiSetContStatesPtr(&(&scenario1_lqr_M)->solverInfo, (real_T **)
                         &(&scenario1_lqr_M)->contStates);
    rtsiSetNumContStatesPtr(&(&scenario1_lqr_M)->solverInfo, &(&scenario1_lqr_M
      )->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&scenario1_lqr_M)->solverInfo,
      &(&scenario1_lqr_M)->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&scenario1_lqr_M)->solverInfo,
      &(&scenario1_lqr_M)->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&scenario1_lqr_M)->solverInfo,
      &(&scenario1_lqr_M)->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&(&scenario1_lqr_M)->solverInfo, (&rtmGetErrorStatus((
      &scenario1_lqr_M))));
    rtsiSetRTModelPtr(&(&scenario1_lqr_M)->solverInfo, (&scenario1_lqr_M));
  }

  rtsiSetSimTimeStep(&(&scenario1_lqr_M)->solverInfo, MAJOR_TIME_STEP);
  (&scenario1_lqr_M)->intgData.y = (&scenario1_lqr_M)->odeY;
  (&scenario1_lqr_M)->intgData.f[0] = (&scenario1_lqr_M)->odeF[0];
  (&scenario1_lqr_M)->intgData.f[1] = (&scenario1_lqr_M)->odeF[1];
  (&scenario1_lqr_M)->intgData.f[2] = (&scenario1_lqr_M)->odeF[2];
  (&scenario1_lqr_M)->intgData.f[3] = (&scenario1_lqr_M)->odeF[3];
  (&scenario1_lqr_M)->intgData.f[4] = (&scenario1_lqr_M)->odeF[4];
  (&scenario1_lqr_M)->intgData.f[5] = (&scenario1_lqr_M)->odeF[5];
  getRTM()->contStates = ((X_scenario1_lqr_T *) &scenario1_lqr_X);
  rtsiSetSolverData(&(&scenario1_lqr_M)->solverInfo, (void *)&(&scenario1_lqr_M
                    )->intgData);
  rtsiSetSolverName(&(&scenario1_lqr_M)->solverInfo,"ode5");
  rtmSetTPtr(getRTM(), &(&scenario1_lqr_M)->Timing.tArray[0]);
  (&scenario1_lqr_M)->Timing.stepSize0 = 0.01;

  /* block I/O */
  (void) memset(((void *) &scenario1_lqr_B), 0,
                sizeof(B_scenario1_lqr_T));

  /* states (continuous) */
  {
    (void) memset((void *)&scenario1_lqr_X, 0,
                  sizeof(X_scenario1_lqr_T));
  }

  /* external inputs */
  (void)memset((void *)&scenario1_lqr_U, 0, sizeof(ExtU_scenario1_lqr_T));

  /* external outputs */
  (void) memset((void *)&scenario1_lqr_Y, 0,
                sizeof(ExtY_scenario1_lqr_T));

  /* InitializeConditions for Integrator: '<S8>/Integrator1' */
  scenario1_lqr_X.Integrator1_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S6>/Integrator1' */
  scenario1_lqr_X.Integrator1_CSTATE_h = 0.0;

  /* InitializeConditions for Integrator: '<S7>/Integrator1' */
  scenario1_lqr_X.Integrator1_CSTATE_j = 0.0;

  /* InitializeConditions for Integrator: '<S4>/Integrator1' */
  scenario1_lqr_X.Integrator1_CSTATE_b = 0.0;
}

/* Model terminate function */
void scenario1_lqrModelClass::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
scenario1_lqrModelClass::scenario1_lqrModelClass()
{
}

/* Destructor */
scenario1_lqrModelClass::~scenario1_lqrModelClass()
{
  /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_scenario1_lqr_T * scenario1_lqrModelClass::getRTM()
{
  return (&scenario1_lqr_M);
}
