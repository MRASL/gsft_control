/*
 * scenario1_gs.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "scenario1_gs".
 *
 * Model version              : 1.673
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Wed Jan 31 11:03:25 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Passed (1), Warnings (3), Error (0)
 */

#include "scenario1_gs.h"
#include "scenario1_gs_private.h"

static void rate_scheduler(RT_MODEL_scenario1_gs_T *const scenario1_gs_M);

/*
 *   This function updates active task flag for each subrate.
 * The function is called at model base rate, hence the
 * generated code self-manages all its subrates.
 */
static void rate_scheduler(RT_MODEL_scenario1_gs_T *const scenario1_gs_M)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (scenario1_gs_M->Timing.TaskCounters.TID[2])++;
  if ((scenario1_gs_M->Timing.TaskCounters.TID[2]) > 1) {/* Sample time: [0.02s, 0.0s] */
    scenario1_gs_M->Timing.TaskCounters.TID[2] = 0;
  }
}

/*
 * This function updates continuous states using the ODE5 fixed-step
 * solver algorithm
 */
void scenario1_gsModelClass::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
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
  int_T nXc = 9;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  scenario1_gs_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE5_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[0]);
  rtsiSetdX(si, f1);
  this->step();
  scenario1_gs_derivatives();

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
  scenario1_gs_derivatives();

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
  scenario1_gs_derivatives();

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
  scenario1_gs_derivatives();

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
  scenario1_gs_derivatives();

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
void scenario1_gsModelClass::step()
{
  real_T un[6];
  static const real_T Kz1[12] = { -0.0786, -0.0786, -0.0786, -0.0786, -0.0786,
    -0.0786, 0.0283, 0.0283, 0.0283, 0.0283, 0.0283, 0.0283 };

  static const real_T Kz0[12] = { 2.3606, 2.3606, 2.3606, 2.3606, 2.3606, 2.3606,
    1.2441, 1.2441, 1.2441, 1.2441, 1.2441, 1.2441 };

  real_T y;
  real_T z;
  real_T psi;
  real_T rtb_VectorConcatenate[12];
  real_T rtb_T_f[6];
  real_T rtb_Clock;
  real_T rtb_gamma[6];
  int32_T i;
  int32_T i_0;
  real_T tmp;
  if (rtmIsMajorTimeStep((&scenario1_gs_M))) {
    /* set solver stop time */
    if (!((&scenario1_gs_M)->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&(&scenario1_gs_M)->solverInfo, (((&scenario1_gs_M
        )->Timing.clockTickH0 + 1) * (&scenario1_gs_M)->Timing.stepSize0 *
        4294967296.0));
    } else {
      rtsiSetSolverStopTime(&(&scenario1_gs_M)->solverInfo, (((&scenario1_gs_M
        )->Timing.clockTick0 + 1) * (&scenario1_gs_M)->Timing.stepSize0 +
        (&scenario1_gs_M)->Timing.clockTickH0 * (&scenario1_gs_M)
        ->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep((&scenario1_gs_M))) {
    (&scenario1_gs_M)->Timing.t[0] = rtsiGetT(&(&scenario1_gs_M)->solverInfo);
  }

  /* Clock: '<Root>/Clock' */
  rtb_Clock = (&scenario1_gs_M)->Timing.t[0];

  /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn1' incorporates:
   *  Inport: '<Root>/X0'
   */
  rtb_VectorConcatenate[0] = scenario1_gs_U.X0[0];
  rtb_VectorConcatenate[1] = scenario1_gs_U.X0[1];
  rtb_VectorConcatenate[2] = scenario1_gs_U.X0[2];

  /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn2' */
  for (i = 0; i < 5; i++) {
    rtb_VectorConcatenate[i + 3] = 0.0;
  }

  /* End of SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn2' */

  /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn3' incorporates:
   *  Inport: '<Root>/X0'
   */
  rtb_VectorConcatenate[8] = scenario1_gs_U.X0[3];

  /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn4' */
  rtb_VectorConcatenate[9] = 0.0;
  rtb_VectorConcatenate[10] = 0.0;
  rtb_VectorConcatenate[11] = 0.0;

  /* Sum: '<Root>/Sum' incorporates:
   *  Inport: '<Root>/X'
   */
  for (i = 0; i < 12; i++) {
    scenario1_gs_B.dX[i] = scenario1_gs_U.X[i] - rtb_VectorConcatenate[i];
  }

  /* End of Sum: '<Root>/Sum' */

  /* RateTransition: '<Root>/Rate Transition5' */
  if ((rtmIsMajorTimeStep((&scenario1_gs_M)) &&
       (&scenario1_gs_M)->Timing.TaskCounters.TID[1] == 0) &&
      (rtmIsMajorTimeStep((&scenario1_gs_M)) &&
       (&scenario1_gs_M)->Timing.TaskCounters.TID[2] == 0)) {
    memcpy(&scenario1_gs_B.RateTransition5[0], &scenario1_gs_B.dX[0], 12U *
           sizeof(real_T));
  }

  /* End of RateTransition: '<Root>/Rate Transition5' */
  if (rtmIsMajorTimeStep((&scenario1_gs_M)) &&
      (&scenario1_gs_M)->Timing.TaskCounters.TID[2] == 0) {
    /* Gain: '<S7>/                    ' incorporates:
     *  SignalConversion: '<S7>/TmpSignal ConversionAt                    Inport1'
     */
    scenario1_gs_B.u = 0.32349951352986844 * scenario1_gs_B.RateTransition5[0] +
      0.2732366014912686 * scenario1_gs_B.RateTransition5[3];
  }

  /* Sum: '<S7>/Sum1' incorporates:
   *  Gain: '<S7>/ '
   *  Integrator: '<S7>/Integrator1'
   */
  scenario1_gs_B.Sum1 = 0.17320508075688268 * scenario1_gs_X.Integrator1_CSTATE
    - scenario1_gs_B.u;
  if (rtmIsMajorTimeStep((&scenario1_gs_M)) &&
      (&scenario1_gs_M)->Timing.TaskCounters.TID[1] == 0) {
    /* ZeroOrderHold: '<Root>/Zero-Order Hold' */
    scenario1_gs_B.ZeroOrderHold = scenario1_gs_B.Sum1;
  }

  if (rtmIsMajorTimeStep((&scenario1_gs_M)) &&
      (&scenario1_gs_M)->Timing.TaskCounters.TID[2] == 0) {
    /* Gain: '<S8>/                     ' incorporates:
     *  SignalConversion: '<S8>/TmpSignal ConversionAt                     Inport1'
     */
    scenario1_gs_B.u_m = -0.31312578517365397 * scenario1_gs_B.RateTransition5[1]
      + -0.254171982010764 * scenario1_gs_B.RateTransition5[4];
  }

  /* Sum: '<S8>/Sum1' incorporates:
   *  Gain: '<S8>/  '
   *  Integrator: '<S8>/Integrator1'
   */
  scenario1_gs_B.Sum1_i = -0.17320508075687535 *
    scenario1_gs_X.Integrator1_CSTATE_j - scenario1_gs_B.u_m;
  if (rtmIsMajorTimeStep((&scenario1_gs_M)) &&
      (&scenario1_gs_M)->Timing.TaskCounters.TID[1] == 0) {
    /* ZeroOrderHold: '<Root>/Zero-Order Hold1' */
    scenario1_gs_B.ZeroOrderHold1 = scenario1_gs_B.Sum1_i;
  }

  /* Sum: '<S4>/Sum1' incorporates:
   *  Fcn: '<Root>/Fcn1'
   *  Inport: '<Root>/X'
   *  Saturate: '<S4>/roll'
   */
  psi = scenario1_gs_B.ZeroOrderHold1 * std::cos(scenario1_gs_U.X[8]) +
    scenario1_gs_B.ZeroOrderHold * std::sin(scenario1_gs_U.X[8]);
  if (psi > 0.52359877559829882) {
    psi = 0.52359877559829882;
  } else {
    if (psi < -0.52359877559829882) {
      psi = -0.52359877559829882;
    }
  }

  /* Sum: '<Root>/Sum2' incorporates:
   *  Gain: '<S4>/                    '
   *  SignalConversion: '<S4>/TmpSignal ConversionAt                    Inport1'
   *  Sum: '<S4>/Sum1'
   */
  y = psi - (1.1365283480217518 * scenario1_gs_B.dX[6] + 0.28178545108769576 *
             scenario1_gs_B.dX[9]);

  /* Sum: '<S6>/Sum1' incorporates:
   *  Fcn: '<Root>/Fcn'
   *  Inport: '<Root>/X'
   *  Saturate: '<S6>/pitch'
   */
  psi = -scenario1_gs_B.ZeroOrderHold1 * std::sin(scenario1_gs_U.X[8]) +
    scenario1_gs_B.ZeroOrderHold * std::cos(scenario1_gs_U.X[8]);
  if (psi > 0.52359877559829882) {
    psi = 0.52359877559829882;
  } else {
    if (psi < -0.52359877559829882) {
      psi = -0.52359877559829882;
    }
  }

  /* Sum: '<Root>/Sum2' incorporates:
   *  Gain: '<S5>/  '
   *  Gain: '<S5>/                     '
   *  Gain: '<S6>/                    '
   *  Integrator: '<S5>/Integrator1'
   *  SignalConversion: '<S5>/TmpSignal ConversionAt                     Inport1'
   *  SignalConversion: '<S6>/TmpSignal ConversionAt                    Inport1'
   *  Sum: '<S5>/Sum1'
   *  Sum: '<S6>/Sum1'
   */
  psi -= 1.2859205994736529 * scenario1_gs_B.dX[7] + 0.3441355124935061 *
    scenario1_gs_B.dX[10];
  tmp = 0.15811388300841872 * scenario1_gs_X.Integrator1_CSTATE_b -
    (0.31372450116883577 * scenario1_gs_B.dX[8] + 0.24799549900832987 *
     scenario1_gs_B.dX[11]);

  /* MATLAB Function: '<Root>/FDD' */
  /* MATLAB Function 'FDD': '<S2>:1' */
  /* '<S2>:1:2' gamma = [0 0 0 0 0 0]; */
  for (i = 0; i < 6; i++) {
    rtb_gamma[i] = 0.0;
  }

  /* '<S2>:1:3' if time >= 15 */
  if (rtb_Clock >= 15.0) {
    /* '<S2>:1:4' gamma = [0.25 0.25 0.25 0.25 0.25 0.25]; */
    for (i = 0; i < 6; i++) {
      rtb_gamma[i] = 0.25;
    }
  }

  /* End of MATLAB Function: '<Root>/FDD' */

  /* MATLAB Function: '<S9>/MATLAB Function' incorporates:
   *  Product: '<S9>/Product1'
   */
  /* MATLAB Function 'z_controller /MATLAB Function': '<S10>:1' */
  /* '<S10>:1:2' un = (u - 0.5)/0.5 */
  for (i = 0; i < 6; i++) {
    un[i] = (rtb_gamma[i] - 0.5) / 0.5;
  }

  /*   */
  /*  Kz0 = [2.3606   1.2298 */
  /*         2.3606   1.2298 */
  /*         2.3606   1.2298]; */
  /*  Kz1 = [0.0072   0.0360 */
  /*         0.0072   0.0360 */
  /*         0.0072   0.0360]; */
  /*  Kiz0 = [1.6718  */
  /*          1.6718 */
  /*          1.6718]; */
  /*  Kiz1 = [-0.0863 */
  /*          -0.0863 */
  /*          -0.0863];     */
  /*   */
  /* '<S10>:1:30' Kz0 = [2.3606   1.2441 */
  /* '<S10>:1:31'        2.3606   1.2441 */
  /* '<S10>:1:32'        2.3606   1.2441 */
  /* '<S10>:1:33'        2.3606   1.2441 */
  /* '<S10>:1:34'        2.3606   1.2441 */
  /* '<S10>:1:35'        2.3606   1.2441]; */
  /* '<S10>:1:36' Kz1 = [-0.0786   0.0283 */
  /* '<S10>:1:37'        -0.0786   0.0283 */
  /* '<S10>:1:38'        -0.0786   0.0283 */
  /* '<S10>:1:39'        -0.0786   0.0283 */
  /* '<S10>:1:40'        -0.0786   0.0283 */
  /* '<S10>:1:41'        -0.0786   0.0283]; */
  /* '<S10>:1:42' Kiz0 = [1.6718  */
  /* '<S10>:1:43'         1.6718  */
  /* '<S10>:1:44'         1.6718  */
  /* '<S10>:1:45'         1.6718 */
  /* '<S10>:1:46'         1.6718  */
  /* '<S10>:1:47'         1.6718]; */
  /* '<S10>:1:48' Kiz1 = [-0.0846 */
  /* '<S10>:1:49'         -0.0846 */
  /* '<S10>:1:50'         -0.0846 */
  /* '<S10>:1:51'         -0.0846 */
  /* '<S10>:1:52'         -0.0846 */
  /* '<S10>:1:53'         -0.0846]; */
  /* '<S10>:1:55' Kz = Kz0 + Kz1.*un(1) + Kz1.*un(2) + Kz1.*un(3) + Kz1.*un(4) + Kz1.*un(5) + Kz1.*un(6); */
  /* '<S10>:1:56' Kiz = Kiz0 + Kiz1.*un(1) + Kiz1*un(2) + Kiz1.*un(3) + Kiz1.*un(4) + Kiz1.*un(5) + Kiz1.*un(6); */
  for (i = 0; i < 2; i++) {
    for (i_0 = 0; i_0 < 6; i_0++) {
      rtb_VectorConcatenate[i_0 + 6 * i] = (((((Kz1[6 * i + i_0] * un[0] + Kz0[6
        * i + i_0]) + Kz1[6 * i + i_0] * un[1]) + Kz1[6 * i + i_0] * un[2]) +
        Kz1[6 * i + i_0] * un[3]) + Kz1[6 * i + i_0] * un[4]) + Kz1[6 * i + i_0]
        * un[5];
    }
  }

  /* MATLAB Function 'Actuator_Fault': '<S1>:1' */
  /* '<S1>:1:2' T_f = T; */
  for (i = 0; i < 6; i++) {
    /* Gain: '<Root>/                 ' incorporates:
     *  Sum: '<Root>/Sum2'
     *  Sum: '<Root>/Sum4'
     */
    z = scenario1_gs_ConstP._Gain_m[i + 18] * tmp +
      (scenario1_gs_ConstP._Gain_m[i + 12] * psi +
       (scenario1_gs_ConstP._Gain_m[i + 6] * y + scenario1_gs_ConstP._Gain_m[i] *
        15.107400000000002));

    /* Sum: '<Root>/Sum4' incorporates:
     *  Integrator: '<S9>/Integrator1'
     *  Product: '<S9>/Product1'
     *  SignalConversion: '<S9>/TmpSignal ConversionAtProduct1Inport2'
     *  Sum: '<S9>/Sum1'
     */
    z += scenario1_gs_X.Integrator1_CSTATE_k[i] - (rtb_VectorConcatenate[i + 6] *
      scenario1_gs_B.dX[5] + rtb_VectorConcatenate[i] * scenario1_gs_B.dX[2]);

    /* MATLAB Function: '<Root>/Actuator_Fault' */
    rtb_T_f[i] = z;

    /* Sum: '<Root>/Sum4' */
    rtb_gamma[i] = z;
  }

  /* MATLAB Function: '<Root>/Actuator_Fault' */
  /* '<S1>:1:3' if time >= 15 */
  if (rtb_Clock >= 15.0) {
    /* '<S1>:1:4' T1 = T(1)*0.75; */
    /* '<S1>:1:5' T2 = T(2)*0.75; */
    /* '<S1>:1:6' T3 = T(3)*0.75; */
    /* '<S1>:1:7' T4 = T(4)*0.75; */
    /* '<S1>:1:8' T5 = T(5)*0.75; */
    /* '<S1>:1:9' T6 = T(6)*0.75; */
    /* '<S1>:1:10' T_f = [T1;T2;T3;T4;T5;T6]; */
    rtb_T_f[0] = rtb_gamma[0] * 0.75;
    rtb_T_f[1] = rtb_gamma[1] * 0.75;
    rtb_T_f[2] = rtb_gamma[2] * 0.75;
    rtb_T_f[3] = rtb_gamma[3] * 0.75;
    rtb_T_f[4] = rtb_gamma[4] * 0.75;
    rtb_T_f[5] = rtb_gamma[5] * 0.75;
  }

  /* Outport: '<Root>/virtual_control' incorporates:
   *  Sum: '<Root>/Sum2'
   */
  scenario1_gs_Y.virtual_control[0] = 15.107400000000002;
  scenario1_gs_Y.virtual_control[1] = y;
  scenario1_gs_Y.virtual_control[2] = psi;
  scenario1_gs_Y.virtual_control[3] = tmp;
  for (i = 0; i < 6; i++) {
    /* Sqrt: '<Root>/Sqrt1' incorporates:
     *  Gain: '<Root>/      '
     */
    z = std::sqrt(116978.4923343994 * rtb_T_f[i]);

    /* Gain: '<Root>/rads_to_RPM' */
    y = 9.5493 * z;

    /* Gain: '<Root>/mapping_0_200' incorporates:
     *  Constant: '<Root>/Constant '
     *  Sum: '<Root>/Sum3'
     */
    psi = (y - 1250.0) * 0.022857142857142857;

    /* Saturate: '<Root>/Saturation' */
    if (psi > 200.0) {
      /* Outport: '<Root>/motor_command' */
      scenario1_gs_Y.motor_command[i] = 200.0;
    } else if (psi < 0.0) {
      /* Outport: '<Root>/motor_command' */
      scenario1_gs_Y.motor_command[i] = 0.0;
    } else {
      /* Outport: '<Root>/motor_command' */
      scenario1_gs_Y.motor_command[i] = psi;
    }

    /* End of Saturate: '<Root>/Saturation' */

    /* Outport: '<Root>/motor_speed' */
    scenario1_gs_Y.motor_speed[i] = z;

    /* Outport: '<Root>/motor_RPM' */
    scenario1_gs_Y.motor_RPM[i] = y;
  }

  /* MATLAB Function: '<Root>/MATLAB Function' incorporates:
   *  Inport: '<Root>/X0'
   */
  /* MATLAB Function 'MATLAB Function': '<S3>:1' */
  /* '<S3>:1:2' x = X0(1); */
  /* '<S3>:1:2' y = X0(2); */
  /* '<S3>:1:2' z = X0(3); */
  /* '<S3>:1:2' psi = X0(4); */
  /* '<S3>:1:3' if t <= 35 */
  if (rtb_Clock <= 35.0) {
    /* '<S3>:1:4' x = X0(1); */
    rtb_Clock = scenario1_gs_U.X0[0];

    /* '<S3>:1:5' y = X0(2); */
    y = scenario1_gs_U.X0[1];

    /* '<S3>:1:6' z = 0.75; */
    z = 0.75;

    /* '<S3>:1:7' psi = X0(4); */
    psi = scenario1_gs_U.X0[3];
  } else {
    /* '<S3>:1:8' else */
    /* '<S3>:1:9' x = X0(1); */
    rtb_Clock = scenario1_gs_U.X0[0];

    /* '<S3>:1:10' y = X0(2); */
    y = scenario1_gs_U.X0[1];

    /* '<S3>:1:11' z = X0(3); */
    z = scenario1_gs_U.X0[2];

    /* '<S3>:1:12' psi = X0(4); */
    psi = scenario1_gs_U.X0[3];
  }

  /* Outport: '<Root>/ref' incorporates:
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  /* '<S3>:1:14' ref = [x;y;z;psi]; */
  scenario1_gs_Y.ref[0] = rtb_Clock;

  /* Sum: '<Root>/Sum1' incorporates:
   *  Inport: '<Root>/X0'
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  scenario1_gs_B.d_ref[0] = rtb_Clock - scenario1_gs_U.X0[0];

  /* Outport: '<Root>/ref' incorporates:
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  scenario1_gs_Y.ref[1] = y;

  /* Sum: '<Root>/Sum1' incorporates:
   *  Inport: '<Root>/X0'
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  scenario1_gs_B.d_ref[1] = y - scenario1_gs_U.X0[1];

  /* Outport: '<Root>/ref' incorporates:
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  scenario1_gs_Y.ref[2] = z;

  /* Sum: '<Root>/Sum1' incorporates:
   *  Inport: '<Root>/X0'
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  scenario1_gs_B.d_ref[2] = z - scenario1_gs_U.X0[2];

  /* Outport: '<Root>/ref' incorporates:
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  scenario1_gs_Y.ref[3] = psi;

  /* Sum: '<Root>/Sum1' incorporates:
   *  Inport: '<Root>/X0'
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  scenario1_gs_B.d_ref[3] = psi - scenario1_gs_U.X0[3];

  /* RateTransition: '<Root>/Rate Transition' incorporates:
   *  RateTransition: '<Root>/Rate Transition1'
   */
  if ((rtmIsMajorTimeStep((&scenario1_gs_M)) &&
       (&scenario1_gs_M)->Timing.TaskCounters.TID[1] == 0) &&
      (rtmIsMajorTimeStep((&scenario1_gs_M)) &&
       (&scenario1_gs_M)->Timing.TaskCounters.TID[2] == 0)) {
    scenario1_gs_B.RateTransition = scenario1_gs_B.d_ref[0];
    scenario1_gs_B.RateTransition1 = scenario1_gs_B.d_ref[1];
  }

  /* End of RateTransition: '<Root>/Rate Transition' */

  /* Saturate: '<S5>/yaw' */
  if (scenario1_gs_B.d_ref[3] > 3.1415926535897931) {
    z = 3.1415926535897931;
  } else if (scenario1_gs_B.d_ref[3] < -3.1415926535897931) {
    z = -3.1415926535897931;
  } else {
    z = scenario1_gs_B.d_ref[3];
  }

  /* End of Saturate: '<S5>/yaw' */

  /* Sum: '<S5>/Sum3' */
  psi = z - scenario1_gs_B.dX[8];

  /* Saturate: '<S5>/psi_e' */
  if (psi > 0.78539816339744828) {
    scenario1_gs_B.psi_e = 0.78539816339744828;
  } else if (psi < -0.78539816339744828) {
    scenario1_gs_B.psi_e = -0.78539816339744828;
  } else {
    scenario1_gs_B.psi_e = psi;
  }

  /* End of Saturate: '<S5>/psi_e' */
  if (rtmIsMajorTimeStep((&scenario1_gs_M)) &&
      (&scenario1_gs_M)->Timing.TaskCounters.TID[2] == 0) {
    /* Saturate: '<S7>/x' */
    if (scenario1_gs_B.RateTransition > 1.0) {
      z = 1.0;
    } else if (scenario1_gs_B.RateTransition < -1.0) {
      z = -1.0;
    } else {
      z = scenario1_gs_B.RateTransition;
    }

    /* End of Saturate: '<S7>/x' */

    /* Sum: '<S7>/Sum3' */
    psi = z - scenario1_gs_B.RateTransition5[0];

    /* Saturate: '<S7>/xe' */
    if (psi > 1.0) {
      scenario1_gs_B.xe = 1.0;
    } else if (psi < -1.0) {
      scenario1_gs_B.xe = -1.0;
    } else {
      scenario1_gs_B.xe = psi;
    }

    /* End of Saturate: '<S7>/xe' */

    /* Saturate: '<S8>/y' */
    if (scenario1_gs_B.RateTransition1 > 1.0) {
      z = 1.0;
    } else if (scenario1_gs_B.RateTransition1 < -1.0) {
      z = -1.0;
    } else {
      z = scenario1_gs_B.RateTransition1;
    }

    /* End of Saturate: '<S8>/y' */

    /* Sum: '<S8>/Sum3' */
    psi = z - scenario1_gs_B.RateTransition5[1];

    /* Saturate: '<S8>/ye' */
    if (psi > 1.0) {
      scenario1_gs_B.ye = 1.0;
    } else if (psi < -1.0) {
      scenario1_gs_B.ye = -1.0;
    } else {
      scenario1_gs_B.ye = psi;
    }

    /* End of Saturate: '<S8>/ye' */
  }

  /* Saturate: '<S9>/z' */
  if (scenario1_gs_B.d_ref[2] > 1.0) {
    z = 1.0;
  } else if (scenario1_gs_B.d_ref[2] < 0.0) {
    z = 0.0;
  } else {
    z = scenario1_gs_B.d_ref[2];
  }

  /* End of Saturate: '<S9>/z' */

  /* Sum: '<S9>/Sum3' */
  rtb_Clock = z - scenario1_gs_B.dX[2];

  /* Saturate: '<S9>/ze' */
  if (rtb_Clock > 0.5) {
    rtb_Clock = 0.5;
  } else {
    if (rtb_Clock < -0.5) {
      rtb_Clock = -0.5;
    }
  }

  /* End of Saturate: '<S9>/ze' */

  /* Product: '<S9>/Product' incorporates:
   *  MATLAB Function: '<S9>/MATLAB Function'
   */
  for (i = 0; i < 6; i++) {
    scenario1_gs_B.Product[i] = ((((((-0.0846 * un[0] + 1.6718) + -0.0846 * un[1])
      + -0.0846 * un[2]) + -0.0846 * un[3]) + -0.0846 * un[4]) + -0.0846 * un[5])
      * rtb_Clock;
  }

  /* End of Product: '<S9>/Product' */
  if (rtmIsMajorTimeStep((&scenario1_gs_M))) {
    rt_ertODEUpdateContinuousStates(&(&scenario1_gs_M)->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++(&scenario1_gs_M)->Timing.clockTick0)) {
      ++(&scenario1_gs_M)->Timing.clockTickH0;
    }

    (&scenario1_gs_M)->Timing.t[0] = rtsiGetSolverStopTime(&(&scenario1_gs_M)
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
      (&scenario1_gs_M)->Timing.clockTick1++;
      if (!(&scenario1_gs_M)->Timing.clockTick1) {
        (&scenario1_gs_M)->Timing.clockTickH1++;
      }
    }

    rate_scheduler((&scenario1_gs_M));
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void scenario1_gsModelClass::scenario1_gs_derivatives()
{
  int32_T i;
  XDot_scenario1_gs_T *_rtXdot;
  _rtXdot = ((XDot_scenario1_gs_T *) (&scenario1_gs_M)->derivs);

  /* Derivatives for Integrator: '<S7>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = scenario1_gs_B.xe;

  /* Derivatives for Integrator: '<S8>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_j = scenario1_gs_B.ye;

  /* Derivatives for Integrator: '<S5>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_b = scenario1_gs_B.psi_e;

  /* Derivatives for Integrator: '<S9>/Integrator1' */
  for (i = 0; i < 6; i++) {
    _rtXdot->Integrator1_CSTATE_k[i] = scenario1_gs_B.Product[i];
  }

  /* End of Derivatives for Integrator: '<S9>/Integrator1' */
}

/* Model initialize function */
void scenario1_gsModelClass::initialize()
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)(&scenario1_gs_M), 0,
                sizeof(RT_MODEL_scenario1_gs_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&(&scenario1_gs_M)->solverInfo, &(&scenario1_gs_M)
                          ->Timing.simTimeStep);
    rtsiSetTPtr(&(&scenario1_gs_M)->solverInfo, &rtmGetTPtr((&scenario1_gs_M)));
    rtsiSetStepSizePtr(&(&scenario1_gs_M)->solverInfo, &(&scenario1_gs_M)
                       ->Timing.stepSize0);
    rtsiSetdXPtr(&(&scenario1_gs_M)->solverInfo, &(&scenario1_gs_M)->derivs);
    rtsiSetContStatesPtr(&(&scenario1_gs_M)->solverInfo, (real_T **)
                         &(&scenario1_gs_M)->contStates);
    rtsiSetNumContStatesPtr(&(&scenario1_gs_M)->solverInfo, &(&scenario1_gs_M)
      ->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&scenario1_gs_M)->solverInfo,
      &(&scenario1_gs_M)->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&scenario1_gs_M)->solverInfo,
      &(&scenario1_gs_M)->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&scenario1_gs_M)->solverInfo,
      &(&scenario1_gs_M)->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&(&scenario1_gs_M)->solverInfo, (&rtmGetErrorStatus
      ((&scenario1_gs_M))));
    rtsiSetRTModelPtr(&(&scenario1_gs_M)->solverInfo, (&scenario1_gs_M));
  }

  rtsiSetSimTimeStep(&(&scenario1_gs_M)->solverInfo, MAJOR_TIME_STEP);
  (&scenario1_gs_M)->intgData.y = (&scenario1_gs_M)->odeY;
  (&scenario1_gs_M)->intgData.f[0] = (&scenario1_gs_M)->odeF[0];
  (&scenario1_gs_M)->intgData.f[1] = (&scenario1_gs_M)->odeF[1];
  (&scenario1_gs_M)->intgData.f[2] = (&scenario1_gs_M)->odeF[2];
  (&scenario1_gs_M)->intgData.f[3] = (&scenario1_gs_M)->odeF[3];
  (&scenario1_gs_M)->intgData.f[4] = (&scenario1_gs_M)->odeF[4];
  (&scenario1_gs_M)->intgData.f[5] = (&scenario1_gs_M)->odeF[5];
  getRTM()->contStates = ((X_scenario1_gs_T *) &scenario1_gs_X);
  rtsiSetSolverData(&(&scenario1_gs_M)->solverInfo, (void *)&(&scenario1_gs_M)
                    ->intgData);
  rtsiSetSolverName(&(&scenario1_gs_M)->solverInfo,"ode5");
  rtmSetTPtr(getRTM(), &(&scenario1_gs_M)->Timing.tArray[0]);
  (&scenario1_gs_M)->Timing.stepSize0 = 0.01;

  /* block I/O */
  (void) memset(((void *) &scenario1_gs_B), 0,
                sizeof(B_scenario1_gs_T));

  /* states (continuous) */
  {
    (void) memset((void *)&scenario1_gs_X, 0,
                  sizeof(X_scenario1_gs_T));
  }

  /* external inputs */
  (void)memset((void *)&scenario1_gs_U, 0, sizeof(ExtU_scenario1_gs_T));

  /* external outputs */
  (void) memset((void *)&scenario1_gs_Y, 0,
                sizeof(ExtY_scenario1_gs_T));

  {
    int32_T i;

    /* InitializeConditions for Integrator: '<S7>/Integrator1' */
    scenario1_gs_X.Integrator1_CSTATE = 0.0;

    /* InitializeConditions for Integrator: '<S8>/Integrator1' */
    scenario1_gs_X.Integrator1_CSTATE_j = 0.0;

    /* InitializeConditions for Integrator: '<S5>/Integrator1' */
    scenario1_gs_X.Integrator1_CSTATE_b = 0.0;

    /* InitializeConditions for Integrator: '<S9>/Integrator1' */
    for (i = 0; i < 6; i++) {
      scenario1_gs_X.Integrator1_CSTATE_k[i] = 0.0;
    }

    /* End of InitializeConditions for Integrator: '<S9>/Integrator1' */
  }
}

/* Model terminate function */
void scenario1_gsModelClass::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
scenario1_gsModelClass::scenario1_gsModelClass()
{
}

/* Destructor */
scenario1_gsModelClass::~scenario1_gsModelClass()
{
  /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_scenario1_gs_T * scenario1_gsModelClass::getRTM()
{
  return (&scenario1_gs_M);
}
