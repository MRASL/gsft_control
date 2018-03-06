/*
 * scenario1_lqr1khz.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "scenario1_lqr1khz".
 *
 * Model version              : 1.763
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Mon Mar  5 19:10:19 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Passed (1), Warnings (3), Error (0)
 */

#include "scenario1_lqr1khz.h"
#include "scenario1_lqr1khz_private.h"

static void rate_scheduler(RT_MODEL_scenario1_lqr1khz_T *const
  scenario1_lqr1khz_M);

/*
 *   This function updates active task flag for each subrate.
 * The function is called at model base rate, hence the
 * generated code self-manages all its subrates.
 */
static void rate_scheduler(RT_MODEL_scenario1_lqr1khz_T *const
  scenario1_lqr1khz_M)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (scenario1_lqr1khz_M->Timing.TaskCounters.TID[2])++;
  if ((scenario1_lqr1khz_M->Timing.TaskCounters.TID[2]) > 4) {/* Sample time: [0.005s, 0.0s] */
    scenario1_lqr1khz_M->Timing.TaskCounters.TID[2] = 0;
  }
}

/*
 * This function updates continuous states using the ODE5 fixed-step
 * solver algorithm
 */
void scenario1_lqr1khzModelClass::rt_ertODEUpdateContinuousStates(RTWSolverInfo *
  si )
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
  scenario1_lqr1khz_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE5_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[0]);
  rtsiSetdX(si, f1);
  this->step();
  scenario1_lqr1khz_derivatives();

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
  scenario1_lqr1khz_derivatives();

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
  scenario1_lqr1khz_derivatives();

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
  scenario1_lqr1khz_derivatives();

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
  scenario1_lqr1khz_derivatives();

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
void scenario1_lqr1khzModelClass::step()
{
  real_T z;
  real_T psi;
  real_T rtb_Integrator1;
  real_T rtb_VectorConcatenate[12];
  real_T rtb_Sum1_d;
  int32_T i;
  real_T rtb_rads_to_RPM;
  if (rtmIsMajorTimeStep((&scenario1_lqr1khz_M))) {
    /* set solver stop time */
    if (!((&scenario1_lqr1khz_M)->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&(&scenario1_lqr1khz_M)->solverInfo,
                            (((&scenario1_lqr1khz_M)->Timing.clockTickH0 + 1) *
        (&scenario1_lqr1khz_M)->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&(&scenario1_lqr1khz_M)->solverInfo,
                            (((&scenario1_lqr1khz_M)->Timing.clockTick0 + 1) * (
        &scenario1_lqr1khz_M)->Timing.stepSize0 + (&scenario1_lqr1khz_M)
        ->Timing.clockTickH0 * (&scenario1_lqr1khz_M)->Timing.stepSize0 *
        4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep((&scenario1_lqr1khz_M))) {
    (&scenario1_lqr1khz_M)->Timing.t[0] = rtsiGetT(&(&scenario1_lqr1khz_M)
      ->solverInfo);
  }

  /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn1' incorporates:
   *  Inport: '<Root>/X0'
   */
  rtb_VectorConcatenate[0] = scenario1_lqr1khz_U.X0[0];
  rtb_VectorConcatenate[1] = scenario1_lqr1khz_U.X0[1];
  rtb_VectorConcatenate[2] = scenario1_lqr1khz_U.X0[2];

  /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn2' */
  for (i = 0; i < 5; i++) {
    rtb_VectorConcatenate[i + 3] = 0.0;
  }

  /* End of SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn2' */

  /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn3' incorporates:
   *  Inport: '<Root>/X0'
   */
  rtb_VectorConcatenate[8] = scenario1_lqr1khz_U.X0[3];

  /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn4' */
  rtb_VectorConcatenate[9] = 0.0;
  rtb_VectorConcatenate[10] = 0.0;
  rtb_VectorConcatenate[11] = 0.0;

  /* Sum: '<Root>/Sum' incorporates:
   *  Inport: '<Root>/X'
   */
  for (i = 0; i < 12; i++) {
    scenario1_lqr1khz_B.dX[i] = scenario1_lqr1khz_U.X[i] -
      rtb_VectorConcatenate[i];
  }

  /* End of Sum: '<Root>/Sum' */

  /* RateTransition: '<Root>/Rate Transition3' */
  if ((rtmIsMajorTimeStep((&scenario1_lqr1khz_M)) &&
       (&scenario1_lqr1khz_M)->Timing.TaskCounters.TID[1] == 0) &&
      (rtmIsMajorTimeStep((&scenario1_lqr1khz_M)) &&
       (&scenario1_lqr1khz_M)->Timing.TaskCounters.TID[2] == 0)) {
    memcpy(&scenario1_lqr1khz_B.RateTransition3[0], &scenario1_lqr1khz_B.dX[0],
           12U * sizeof(real_T));
  }

  /* End of RateTransition: '<Root>/Rate Transition3' */
  if (rtmIsMajorTimeStep((&scenario1_lqr1khz_M)) &&
      (&scenario1_lqr1khz_M)->Timing.TaskCounters.TID[2] == 0) {
    /* Gain: '<S7>/                     ' incorporates:
     *  SignalConversion: '<S7>/TmpSignal ConversionAt                     Inport1'
     */
    scenario1_lqr1khz_B.u = 12.219481695651957 *
      scenario1_lqr1khz_B.RateTransition3[2] + 6.215786645518647 *
      scenario1_lqr1khz_B.RateTransition3[5];
  }

  /* Sum: '<S7>/Sum1' incorporates:
   *  Gain: '<S7>/  '
   *  Integrator: '<S7>/Integrator1'
   */
  scenario1_lqr1khz_B.Sum1 = 10.000000000000018 *
    scenario1_lqr1khz_X.Integrator1_CSTATE - scenario1_lqr1khz_B.u;
  if (rtmIsMajorTimeStep((&scenario1_lqr1khz_M)) &&
      (&scenario1_lqr1khz_M)->Timing.TaskCounters.TID[2] == 0) {
    /* ZeroOrderHold: '<Root>/Zero-Order Hold2' */
    scenario1_lqr1khz_B.ZeroOrderHold2 = scenario1_lqr1khz_B.Sum1;

    /* Gain: '<S5>/                    ' incorporates:
     *  SignalConversion: '<S5>/TmpSignal ConversionAt                    Inport1'
     */
    scenario1_lqr1khz_B.u_j = 0.32349951352987977 *
      scenario1_lqr1khz_B.RateTransition3[0] + 0.2732366014912751 *
      scenario1_lqr1khz_B.RateTransition3[3];

    /* Gain: '<S6>/                     ' incorporates:
     *  SignalConversion: '<S6>/TmpSignal ConversionAt                     Inport1'
     */
    scenario1_lqr1khz_B.u_m = -0.31312578517366968 *
      scenario1_lqr1khz_B.RateTransition3[1] + -0.25417198201077484 *
      scenario1_lqr1khz_B.RateTransition3[4];
  }

  /* Sum: '<S5>/Sum1' incorporates:
   *  Gain: '<S5>/ '
   *  Integrator: '<S5>/Integrator1'
   */
  rtb_Integrator1 = 0.17320508075688992 *
    scenario1_lqr1khz_X.Integrator1_CSTATE_h - scenario1_lqr1khz_B.u_j;

  /* Sum: '<S6>/Sum1' incorporates:
   *  Gain: '<S6>/  '
   *  Integrator: '<S6>/Integrator1'
   */
  rtb_Sum1_d = -0.173205080756885 * scenario1_lqr1khz_X.Integrator1_CSTATE_j -
    scenario1_lqr1khz_B.u_m;

  /* RateTransition: '<Root>/Rate Transition4' incorporates:
   *  Inport: '<Root>/X'
   */
  if ((rtmIsMajorTimeStep((&scenario1_lqr1khz_M)) &&
       (&scenario1_lqr1khz_M)->Timing.TaskCounters.TID[1] == 0) &&
      (rtmIsMajorTimeStep((&scenario1_lqr1khz_M)) &&
       (&scenario1_lqr1khz_M)->Timing.TaskCounters.TID[2] == 0)) {
    memcpy(&scenario1_lqr1khz_B.RateTransition4[0], &scenario1_lqr1khz_U.X[0],
           12U * sizeof(real_T));
  }

  /* End of RateTransition: '<Root>/Rate Transition4' */

  /* Fcn: '<Root>/Fcn1' */
  scenario1_lqr1khz_B.Fcn1 = rtb_Sum1_d * std::cos
    (scenario1_lqr1khz_B.RateTransition4[8]) + rtb_Integrator1 * std::sin
    (scenario1_lqr1khz_B.RateTransition4[8]);

  /* Fcn: '<Root>/Fcn' */
  scenario1_lqr1khz_B.Fcn = -rtb_Sum1_d * std::sin
    (scenario1_lqr1khz_B.RateTransition4[8]) + rtb_Integrator1 * std::cos
    (scenario1_lqr1khz_B.RateTransition4[8]);

  /* ZeroOrderHold: '<Root>/Zero-Order Hold' */
  if (rtmIsMajorTimeStep((&scenario1_lqr1khz_M)) &&
      (&scenario1_lqr1khz_M)->Timing.TaskCounters.TID[2] == 0) {
    scenario1_lqr1khz_B.ZeroOrderHold = scenario1_lqr1khz_B.Fcn1;

    /* Saturate: '<S2>/roll' */
    if (scenario1_lqr1khz_B.ZeroOrderHold > 0.52359877559829882) {
      scenario1_lqr1khz_B.roll = 0.52359877559829882;
    } else if (scenario1_lqr1khz_B.ZeroOrderHold < -0.52359877559829882) {
      scenario1_lqr1khz_B.roll = -0.52359877559829882;
    } else {
      scenario1_lqr1khz_B.roll = scenario1_lqr1khz_B.ZeroOrderHold;
    }

    /* End of Saturate: '<S2>/roll' */
  }

  /* End of ZeroOrderHold: '<Root>/Zero-Order Hold' */

  /* RateTransition: '<Root>/Rate Transition6' */
  if ((rtmIsMajorTimeStep((&scenario1_lqr1khz_M)) &&
       (&scenario1_lqr1khz_M)->Timing.TaskCounters.TID[1] == 0) &&
      (rtmIsMajorTimeStep((&scenario1_lqr1khz_M)) &&
       (&scenario1_lqr1khz_M)->Timing.TaskCounters.TID[2] == 0)) {
    memcpy(&scenario1_lqr1khz_B.RateTransition6[0], &scenario1_lqr1khz_B.dX[0],
           12U * sizeof(real_T));
  }

  /* End of RateTransition: '<Root>/Rate Transition6' */

  /* ZeroOrderHold: '<Root>/Zero-Order Hold1' */
  if (rtmIsMajorTimeStep((&scenario1_lqr1khz_M)) &&
      (&scenario1_lqr1khz_M)->Timing.TaskCounters.TID[2] == 0) {
    scenario1_lqr1khz_B.ZeroOrderHold1 = scenario1_lqr1khz_B.Fcn;

    /* Saturate: '<S4>/pitch' */
    if (scenario1_lqr1khz_B.ZeroOrderHold1 > 0.52359877559829882) {
      scenario1_lqr1khz_B.pitch = 0.52359877559829882;
    } else if (scenario1_lqr1khz_B.ZeroOrderHold1 < -0.52359877559829882) {
      scenario1_lqr1khz_B.pitch = -0.52359877559829882;
    } else {
      scenario1_lqr1khz_B.pitch = scenario1_lqr1khz_B.ZeroOrderHold1;
    }

    /* End of Saturate: '<S4>/pitch' */

    /* Gain: '<S3>/                     ' incorporates:
     *  SignalConversion: '<S3>/TmpSignal ConversionAt                     Inport1'
     */
    scenario1_lqr1khz_B.u_n = 0.3035552054947866 *
      scenario1_lqr1khz_B.RateTransition6[8] + 0.24395632222527311 *
      scenario1_lqr1khz_B.RateTransition6[11];
  }

  /* End of ZeroOrderHold: '<Root>/Zero-Order Hold1' */

  /* Sum: '<S3>/Sum1' incorporates:
   *  Gain: '<S3>/  '
   *  Integrator: '<S3>/Integrator1'
   */
  scenario1_lqr1khz_B.Sum1_a = 0.15811388300841925 *
    scenario1_lqr1khz_X.Integrator1_CSTATE_b - scenario1_lqr1khz_B.u_n;
  if (rtmIsMajorTimeStep((&scenario1_lqr1khz_M)) &&
      (&scenario1_lqr1khz_M)->Timing.TaskCounters.TID[2] == 0) {
    /* ZeroOrderHold: '<Root>/Zero-Order Hold3' */
    scenario1_lqr1khz_B.ZeroOrderHold3 = scenario1_lqr1khz_B.Sum1_a;
  }

  /* Sum: '<Root>/Sum2' incorporates:
   *  Gain: '<S2>/                    '
   *  Gain: '<S4>/                    '
   *  SignalConversion: '<S2>/TmpSignal ConversionAt                    Inport1'
   *  SignalConversion: '<S4>/TmpSignal ConversionAt                    Inport1'
   *  Sum: '<S2>/Sum1'
   *  Sum: '<S4>/Sum1'
   */
  rtb_Integrator1 = scenario1_lqr1khz_B.roll - (1.1365283480217869 *
    scenario1_lqr1khz_B.dX[6] + 0.28178545108770103 * scenario1_lqr1khz_B.dX[9]);
  rtb_Sum1_d = scenario1_lqr1khz_B.pitch - (1.2859205994736729 *
    scenario1_lqr1khz_B.dX[7] + 0.34413551249350854 * scenario1_lqr1khz_B.dX[10]);

  /* Outport: '<Root>/virtual_control' incorporates:
   *  Sum: '<Root>/Sum2'
   */
  scenario1_lqr1khz_Y.virtual_control[0] = scenario1_lqr1khz_B.ZeroOrderHold2 +
    15.107400000000002;
  scenario1_lqr1khz_Y.virtual_control[1] = rtb_Integrator1;
  scenario1_lqr1khz_Y.virtual_control[2] = rtb_Sum1_d;
  scenario1_lqr1khz_Y.virtual_control[3] = scenario1_lqr1khz_B.ZeroOrderHold3;
  for (i = 0; i < 6; i++) {
    /* Gain: '<Root>/                 ' incorporates:
     *  Gain: '<Root>/      '
     *  Sum: '<Root>/Sum2'
     */
    z = scenario1_lqr1khz_ConstP._Gain_m[i + 18] *
      scenario1_lqr1khz_B.ZeroOrderHold3 + (scenario1_lqr1khz_ConstP._Gain_m[i +
      12] * rtb_Sum1_d + (scenario1_lqr1khz_ConstP._Gain_m[i + 6] *
                          rtb_Integrator1 + (scenario1_lqr1khz_B.ZeroOrderHold2
      + 15.107400000000002) * scenario1_lqr1khz_ConstP._Gain_m[i]));

    /* Sqrt: '<Root>/Sqrt1' incorporates:
     *  Gain: '<Root>/      '
     */
    psi = std::sqrt(116978.4923343994 * z);

    /* Gain: '<Root>/rads_to_RPM' */
    rtb_rads_to_RPM = 9.5493 * psi;

    /* Gain: '<Root>/mapping_0_200' incorporates:
     *  Constant: '<Root>/Constant '
     *  Sum: '<Root>/Sum3'
     */
    z = (rtb_rads_to_RPM - 1250.0) * 0.022857142857142857;

    /* Saturate: '<Root>/Saturation' */
    if (z > 200.0) {
      /* Outport: '<Root>/motor_command' */
      scenario1_lqr1khz_Y.motor_command[i] = 200.0;
    } else if (z < 0.0) {
      /* Outport: '<Root>/motor_command' */
      scenario1_lqr1khz_Y.motor_command[i] = 0.0;
    } else {
      /* Outport: '<Root>/motor_command' */
      scenario1_lqr1khz_Y.motor_command[i] = z;
    }

    /* End of Saturate: '<Root>/Saturation' */

    /* Outport: '<Root>/motor_speed' */
    scenario1_lqr1khz_Y.motor_speed[i] = psi;

    /* Outport: '<Root>/motor_RPM' */
    scenario1_lqr1khz_Y.motor_RPM[i] = rtb_rads_to_RPM;
  }

  /* Clock: '<Root>/Clock' */
  rtb_Integrator1 = (&scenario1_lqr1khz_M)->Timing.t[0];

  /* MATLAB Function: '<Root>/MATLAB Function' incorporates:
   *  Inport: '<Root>/X0'
   */
  /* MATLAB Function 'MATLAB Function': '<S1>:1' */
  /* '<S1>:1:2' x = X0(1); */
  /* '<S1>:1:2' y = X0(2); */
  /* '<S1>:1:2' z = X0(3); */
  /* '<S1>:1:2' psi = X0(4); */
  /* '<S1>:1:3' if t <= 20 */
  if (rtb_Integrator1 <= 20.0) {
    /* '<S1>:1:4' x = X0(1); */
    rtb_Integrator1 = scenario1_lqr1khz_U.X0[0];

    /* '<S1>:1:5' y = X0(2); */
    rtb_Sum1_d = scenario1_lqr1khz_U.X0[1];

    /* '<S1>:1:6' z = 0.75; */
    z = 0.75;

    /* '<S1>:1:7' psi = X0(4); */
    psi = scenario1_lqr1khz_U.X0[3];
  } else if (rtb_Integrator1 <= 35.0) {
    /* '<S1>:1:8' elseif t<=35 */
    /* '<S1>:1:9' x = X0(1)-1; */
    rtb_Integrator1 = scenario1_lqr1khz_U.X0[0] - 1.0;

    /* '<S1>:1:10' y = X0(2); */
    rtb_Sum1_d = scenario1_lqr1khz_U.X0[1];

    /* '<S1>:1:11' z = 0.75; */
    z = 0.75;

    /* '<S1>:1:12' psi = X0(4); */
    psi = scenario1_lqr1khz_U.X0[3];
  } else if (rtb_Integrator1 <= 50.0) {
    /* '<S1>:1:13' elseif t<=50 */
    /* '<S1>:1:14' x = X0(1)-1; */
    rtb_Integrator1 = scenario1_lqr1khz_U.X0[0] - 1.0;

    /* '<S1>:1:15' y = X0(2)+1; */
    rtb_Sum1_d = scenario1_lqr1khz_U.X0[1] + 1.0;

    /* '<S1>:1:16' z = 0.75; */
    z = 0.75;

    /* '<S1>:1:17' psi = X0(4); */
    psi = scenario1_lqr1khz_U.X0[3];
  } else if (rtb_Integrator1 <= 80.0) {
    /* '<S1>:1:18' elseif t<=80 */
    /* '<S1>:1:19' x = X0(1)-1; */
    rtb_Integrator1 = scenario1_lqr1khz_U.X0[0] - 1.0;

    /* '<S1>:1:20' y = X0(2)+1; */
    rtb_Sum1_d = scenario1_lqr1khz_U.X0[1] + 1.0;

    /* '<S1>:1:21' z = 0.75; */
    z = 0.75;

    /* '<S1>:1:22' psi = X0(4)+pi/2; */
    psi = scenario1_lqr1khz_U.X0[3] + 1.5707963267948966;
  } else {
    /* '<S1>:1:23' else */
    /* '<S1>:1:24' x = X0(1)-1; */
    rtb_Integrator1 = scenario1_lqr1khz_U.X0[0] - 1.0;

    /* '<S1>:1:25' y = X0(2)+1; */
    rtb_Sum1_d = scenario1_lqr1khz_U.X0[1] + 1.0;

    /* '<S1>:1:26' z = 0.0; */
    z = 0.0;

    /* '<S1>:1:27' psi = X0(4)+pi/2; */
    psi = scenario1_lqr1khz_U.X0[3] + 1.5707963267948966;
  }

  /* Outport: '<Root>/ref' incorporates:
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  /* '<S1>:1:29' ref = [x;y;z;psi]; */
  scenario1_lqr1khz_Y.ref[0] = rtb_Integrator1;

  /* Sum: '<Root>/Sum1' incorporates:
   *  Inport: '<Root>/X0'
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  scenario1_lqr1khz_B.d_ref[0] = rtb_Integrator1 - scenario1_lqr1khz_U.X0[0];

  /* Outport: '<Root>/ref' incorporates:
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  scenario1_lqr1khz_Y.ref[1] = rtb_Sum1_d;

  /* Sum: '<Root>/Sum1' incorporates:
   *  Inport: '<Root>/X0'
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  scenario1_lqr1khz_B.d_ref[1] = rtb_Sum1_d - scenario1_lqr1khz_U.X0[1];

  /* Outport: '<Root>/ref' incorporates:
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  scenario1_lqr1khz_Y.ref[2] = z;

  /* Sum: '<Root>/Sum1' incorporates:
   *  Inport: '<Root>/X0'
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  scenario1_lqr1khz_B.d_ref[2] = z - scenario1_lqr1khz_U.X0[2];

  /* Outport: '<Root>/ref' incorporates:
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  scenario1_lqr1khz_Y.ref[3] = psi;

  /* Sum: '<Root>/Sum1' incorporates:
   *  Inport: '<Root>/X0'
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  scenario1_lqr1khz_B.d_ref[3] = psi - scenario1_lqr1khz_U.X0[3];

  /* RateTransition: '<Root>/Rate Transition' incorporates:
   *  RateTransition: '<Root>/Rate Transition1'
   *  RateTransition: '<Root>/Rate Transition2'
   *  RateTransition: '<Root>/Rate Transition5'
   */
  if ((rtmIsMajorTimeStep((&scenario1_lqr1khz_M)) &&
       (&scenario1_lqr1khz_M)->Timing.TaskCounters.TID[1] == 0) &&
      (rtmIsMajorTimeStep((&scenario1_lqr1khz_M)) &&
       (&scenario1_lqr1khz_M)->Timing.TaskCounters.TID[2] == 0)) {
    scenario1_lqr1khz_B.RateTransition = scenario1_lqr1khz_B.d_ref[0];
    scenario1_lqr1khz_B.RateTransition1 = scenario1_lqr1khz_B.d_ref[1];
    scenario1_lqr1khz_B.RateTransition2 = scenario1_lqr1khz_B.d_ref[2];
    scenario1_lqr1khz_B.RateTransition5 = scenario1_lqr1khz_B.d_ref[3];
  }

  /* End of RateTransition: '<Root>/Rate Transition' */
  if (rtmIsMajorTimeStep((&scenario1_lqr1khz_M)) &&
      (&scenario1_lqr1khz_M)->Timing.TaskCounters.TID[2] == 0) {
    /* Saturate: '<S3>/yaw' */
    if (scenario1_lqr1khz_B.RateTransition5 > 3.1415926535897931) {
      z = 3.1415926535897931;
    } else if (scenario1_lqr1khz_B.RateTransition5 < -3.1415926535897931) {
      z = -3.1415926535897931;
    } else {
      z = scenario1_lqr1khz_B.RateTransition5;
    }

    /* End of Saturate: '<S3>/yaw' */

    /* Sum: '<S3>/Sum3' */
    z -= scenario1_lqr1khz_B.RateTransition6[8];

    /* Saturate: '<S3>/psi_e' */
    if (z > 0.78539816339744828) {
      scenario1_lqr1khz_B.psi_e = 0.78539816339744828;
    } else if (z < -0.78539816339744828) {
      scenario1_lqr1khz_B.psi_e = -0.78539816339744828;
    } else {
      scenario1_lqr1khz_B.psi_e = z;
    }

    /* End of Saturate: '<S3>/psi_e' */

    /* Saturate: '<S5>/x' */
    if (scenario1_lqr1khz_B.RateTransition > 1.0) {
      z = 1.0;
    } else if (scenario1_lqr1khz_B.RateTransition < -1.0) {
      z = -1.0;
    } else {
      z = scenario1_lqr1khz_B.RateTransition;
    }

    /* End of Saturate: '<S5>/x' */

    /* Sum: '<S5>/Sum3' */
    z -= scenario1_lqr1khz_B.RateTransition3[0];

    /* Saturate: '<S5>/xe' */
    if (z > 1.0) {
      scenario1_lqr1khz_B.xe = 1.0;
    } else if (z < -1.0) {
      scenario1_lqr1khz_B.xe = -1.0;
    } else {
      scenario1_lqr1khz_B.xe = z;
    }

    /* End of Saturate: '<S5>/xe' */

    /* Saturate: '<S6>/y' */
    if (scenario1_lqr1khz_B.RateTransition1 > 1.0) {
      z = 1.0;
    } else if (scenario1_lqr1khz_B.RateTransition1 < -1.0) {
      z = -1.0;
    } else {
      z = scenario1_lqr1khz_B.RateTransition1;
    }

    /* End of Saturate: '<S6>/y' */

    /* Sum: '<S6>/Sum3' */
    z -= scenario1_lqr1khz_B.RateTransition3[1];

    /* Saturate: '<S6>/ye' */
    if (z > 1.0) {
      scenario1_lqr1khz_B.ye = 1.0;
    } else if (z < -1.0) {
      scenario1_lqr1khz_B.ye = -1.0;
    } else {
      scenario1_lqr1khz_B.ye = z;
    }

    /* End of Saturate: '<S6>/ye' */

    /* Saturate: '<S7>/z' */
    if (scenario1_lqr1khz_B.RateTransition2 > 1.0) {
      z = 1.0;
    } else if (scenario1_lqr1khz_B.RateTransition2 < 0.0) {
      z = 0.0;
    } else {
      z = scenario1_lqr1khz_B.RateTransition2;
    }

    /* End of Saturate: '<S7>/z' */

    /* Sum: '<S7>/Sum3' */
    z -= scenario1_lqr1khz_B.RateTransition3[2];

    /* Saturate: '<S7>/ze' */
    if (z > 0.5) {
      scenario1_lqr1khz_B.ze = 0.5;
    } else if (z < -0.5) {
      scenario1_lqr1khz_B.ze = -0.5;
    } else {
      scenario1_lqr1khz_B.ze = z;
    }

    /* End of Saturate: '<S7>/ze' */
  }

  if (rtmIsMajorTimeStep((&scenario1_lqr1khz_M))) {
    rt_ertODEUpdateContinuousStates(&(&scenario1_lqr1khz_M)->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++(&scenario1_lqr1khz_M)->Timing.clockTick0)) {
      ++(&scenario1_lqr1khz_M)->Timing.clockTickH0;
    }

    (&scenario1_lqr1khz_M)->Timing.t[0] = rtsiGetSolverStopTime
      (&(&scenario1_lqr1khz_M)->solverInfo);

    {
      /* Update absolute timer for sample time: [0.001s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.001, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      (&scenario1_lqr1khz_M)->Timing.clockTick1++;
      if (!(&scenario1_lqr1khz_M)->Timing.clockTick1) {
        (&scenario1_lqr1khz_M)->Timing.clockTickH1++;
      }
    }

    rate_scheduler((&scenario1_lqr1khz_M));
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void scenario1_lqr1khzModelClass::scenario1_lqr1khz_derivatives()
{
  XDot_scenario1_lqr1khz_T *_rtXdot;
  _rtXdot = ((XDot_scenario1_lqr1khz_T *) (&scenario1_lqr1khz_M)->derivs);

  /* Derivatives for Integrator: '<S7>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = scenario1_lqr1khz_B.ze;

  /* Derivatives for Integrator: '<S5>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_h = scenario1_lqr1khz_B.xe;

  /* Derivatives for Integrator: '<S6>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_j = scenario1_lqr1khz_B.ye;

  /* Derivatives for Integrator: '<S3>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_b = scenario1_lqr1khz_B.psi_e;
}

/* Model initialize function */
void scenario1_lqr1khzModelClass::initialize()
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)(&scenario1_lqr1khz_M), 0,
                sizeof(RT_MODEL_scenario1_lqr1khz_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&(&scenario1_lqr1khz_M)->solverInfo,
                          &(&scenario1_lqr1khz_M)->Timing.simTimeStep);
    rtsiSetTPtr(&(&scenario1_lqr1khz_M)->solverInfo, &rtmGetTPtr
                ((&scenario1_lqr1khz_M)));
    rtsiSetStepSizePtr(&(&scenario1_lqr1khz_M)->solverInfo,
                       &(&scenario1_lqr1khz_M)->Timing.stepSize0);
    rtsiSetdXPtr(&(&scenario1_lqr1khz_M)->solverInfo, &(&scenario1_lqr1khz_M)
                 ->derivs);
    rtsiSetContStatesPtr(&(&scenario1_lqr1khz_M)->solverInfo, (real_T **)
                         &(&scenario1_lqr1khz_M)->contStates);
    rtsiSetNumContStatesPtr(&(&scenario1_lqr1khz_M)->solverInfo,
      &(&scenario1_lqr1khz_M)->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&scenario1_lqr1khz_M)->solverInfo,
      &(&scenario1_lqr1khz_M)->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&scenario1_lqr1khz_M)->solverInfo,
      &(&scenario1_lqr1khz_M)->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&scenario1_lqr1khz_M)->solverInfo,
      &(&scenario1_lqr1khz_M)->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&(&scenario1_lqr1khz_M)->solverInfo,
                          (&rtmGetErrorStatus((&scenario1_lqr1khz_M))));
    rtsiSetRTModelPtr(&(&scenario1_lqr1khz_M)->solverInfo, (&scenario1_lqr1khz_M));
  }

  rtsiSetSimTimeStep(&(&scenario1_lqr1khz_M)->solverInfo, MAJOR_TIME_STEP);
  (&scenario1_lqr1khz_M)->intgData.y = (&scenario1_lqr1khz_M)->odeY;
  (&scenario1_lqr1khz_M)->intgData.f[0] = (&scenario1_lqr1khz_M)->odeF[0];
  (&scenario1_lqr1khz_M)->intgData.f[1] = (&scenario1_lqr1khz_M)->odeF[1];
  (&scenario1_lqr1khz_M)->intgData.f[2] = (&scenario1_lqr1khz_M)->odeF[2];
  (&scenario1_lqr1khz_M)->intgData.f[3] = (&scenario1_lqr1khz_M)->odeF[3];
  (&scenario1_lqr1khz_M)->intgData.f[4] = (&scenario1_lqr1khz_M)->odeF[4];
  (&scenario1_lqr1khz_M)->intgData.f[5] = (&scenario1_lqr1khz_M)->odeF[5];
  getRTM()->contStates = ((X_scenario1_lqr1khz_T *) &scenario1_lqr1khz_X);
  rtsiSetSolverData(&(&scenario1_lqr1khz_M)->solverInfo, (void *)
                    &(&scenario1_lqr1khz_M)->intgData);
  rtsiSetSolverName(&(&scenario1_lqr1khz_M)->solverInfo,"ode5");
  rtmSetTPtr(getRTM(), &(&scenario1_lqr1khz_M)->Timing.tArray[0]);
  (&scenario1_lqr1khz_M)->Timing.stepSize0 = 0.001;

  /* block I/O */
  (void) memset(((void *) &scenario1_lqr1khz_B), 0,
                sizeof(B_scenario1_lqr1khz_T));

  /* states (continuous) */
  {
    (void) memset((void *)&scenario1_lqr1khz_X, 0,
                  sizeof(X_scenario1_lqr1khz_T));
  }

  /* external inputs */
  (void)memset((void *)&scenario1_lqr1khz_U, 0, sizeof(ExtU_scenario1_lqr1khz_T));

  /* external outputs */
  (void) memset((void *)&scenario1_lqr1khz_Y, 0,
                sizeof(ExtY_scenario1_lqr1khz_T));

  /* InitializeConditions for Integrator: '<S7>/Integrator1' */
  scenario1_lqr1khz_X.Integrator1_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S5>/Integrator1' */
  scenario1_lqr1khz_X.Integrator1_CSTATE_h = 0.0;

  /* InitializeConditions for Integrator: '<S6>/Integrator1' */
  scenario1_lqr1khz_X.Integrator1_CSTATE_j = 0.0;

  /* InitializeConditions for Integrator: '<S3>/Integrator1' */
  scenario1_lqr1khz_X.Integrator1_CSTATE_b = 0.0;
}

/* Model terminate function */
void scenario1_lqr1khzModelClass::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
scenario1_lqr1khzModelClass::scenario1_lqr1khzModelClass()
{
}

/* Destructor */
scenario1_lqr1khzModelClass::~scenario1_lqr1khzModelClass()
{
  /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_scenario1_lqr1khz_T * scenario1_lqr1khzModelClass::getRTM()
{
  return (&scenario1_lqr1khz_M);
}