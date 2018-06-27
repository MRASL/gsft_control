/*
 * tunning_nominal.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "tunning_nominal".
 *
 * Model version              : 1.1193
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Wed Jun 27 10:18:49 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Passed (1), Warnings (3), Error (0)
 */

#include "tunning_nominal.h"
#include "tunning_nominal_private.h"

static void rate_scheduler(RT_MODEL_tunning_nominal_T *const tunning_nominal_M);

/*
 *   This function updates active task flag for each subrate.
 * The function is called at model base rate, hence the
 * generated code self-manages all its subrates.
 */
static void rate_scheduler(RT_MODEL_tunning_nominal_T *const tunning_nominal_M)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (tunning_nominal_M->Timing.TaskCounters.TID[2])++;
  if ((tunning_nominal_M->Timing.TaskCounters.TID[2]) > 4) {/* Sample time: [0.005s, 0.0s] */
    tunning_nominal_M->Timing.TaskCounters.TID[2] = 0;
  }
}

/*
 * This function updates continuous states using the ODE4 fixed-step
 * solver algorithm
 */
void tunning_nominalModelClass::rt_ertODEUpdateContinuousStates(RTWSolverInfo
  *si )
{
  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE4_IntgData *id = (ODE4_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T *f3 = id->f[3];
  real_T temp;
  int_T i;
  int_T nXc = 4;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  tunning_nominal_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  this->step();
  tunning_nominal_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  this->step();
  tunning_nominal_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  this->step();
  tunning_nominal_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void tunning_nominalModelClass::step()
{
  real_T rtb_Sum3_b;
  real_T rtb_Sum1_a;
  real_T rtb_u[6];
  real_T rtb_LOE_out[6];
  real_T rtb_Clock;
  int32_T i;
  real_T rateLimiterRate;
  real_T rtb_TLMN_idx_2;
  real_T rtb_TLMN_idx_1;
  real_T rtb_ff_idx_0;
  real_T rtb_ff_idx_1;
  if (rtmIsMajorTimeStep((&tunning_nominal_M))) {
    /* set solver stop time */
    if (!((&tunning_nominal_M)->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&(&tunning_nominal_M)->solverInfo,
                            (((&tunning_nominal_M)->Timing.clockTickH0 + 1) *
        (&tunning_nominal_M)->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&(&tunning_nominal_M)->solverInfo,
                            (((&tunning_nominal_M)->Timing.clockTick0 + 1) *
        (&tunning_nominal_M)->Timing.stepSize0 + (&tunning_nominal_M)
        ->Timing.clockTickH0 * (&tunning_nominal_M)->Timing.stepSize0 *
        4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep((&tunning_nominal_M))) {
    (&tunning_nominal_M)->Timing.t[0] = rtsiGetT(&(&tunning_nominal_M)
      ->solverInfo);
  }

  /* Sum: '<S2>/Sum5' incorporates:
   *  Inport: '<Root>/X'
   *  Inport: '<Root>/Y0'
   */
  tunning_nominal_B.d_z = tunning_nominal_U.X[2] - tunning_nominal_U.Y0[2];

  /* RateTransition: '<Root>/Rate Transition   ' incorporates:
   *  Inport: '<Root>/X'
   */
  if ((rtmIsMajorTimeStep((&tunning_nominal_M)) &&
       (&tunning_nominal_M)->Timing.TaskCounters.TID[1] == 0) &&
      (rtmIsMajorTimeStep((&tunning_nominal_M)) &&
       (&tunning_nominal_M)->Timing.TaskCounters.TID[2] == 0)) {
    tunning_nominal_B.d_z_k = tunning_nominal_B.d_z;
    tunning_nominal_B.vz = tunning_nominal_U.X[5];
  }

  /* Sum: '<S11>/Sum1' incorporates:
   *  Inport: '<Root>/gain'
   *  Integrator: '<S11>/Integrator1'
   *  Product: '<S11>/Product'
   *  Product: '<S11>/Product1'
   *  SignalConversion: '<S11>/TmpSignal ConversionAtProduct1Inport2'
   */
  tunning_nominal_B.Sum1 = tunning_nominal_U.gain[8] *
    tunning_nominal_X.Integrator1_CSTATE - (tunning_nominal_U.gain[6] *
    tunning_nominal_B.d_z_k + tunning_nominal_U.gain[7] * tunning_nominal_B.vz);
  if (rtmIsMajorTimeStep((&tunning_nominal_M)) &&
      (&tunning_nominal_M)->Timing.TaskCounters.TID[2] == 0) {
    /* ZeroOrderHold: '<Root>/               ' */
    tunning_nominal_B.dT = tunning_nominal_B.Sum1;
  }

  /* Sum: '<S2>/Sum1' incorporates:
   *  Inport: '<Root>/X'
   *  Inport: '<Root>/Y0'
   */
  tunning_nominal_B.d_x = tunning_nominal_U.X[0] - tunning_nominal_U.Y0[0];

  /* RateTransition: '<Root>/Rate Transition   ' incorporates:
   *  Inport: '<Root>/X'
   */
  if ((rtmIsMajorTimeStep((&tunning_nominal_M)) &&
       (&tunning_nominal_M)->Timing.TaskCounters.TID[1] == 0) &&
      (rtmIsMajorTimeStep((&tunning_nominal_M)) &&
       (&tunning_nominal_M)->Timing.TaskCounters.TID[2] == 0)) {
    tunning_nominal_B.d_x_b = tunning_nominal_B.d_x;
    tunning_nominal_B.vx = tunning_nominal_U.X[3];
  }

  /* Sum: '<S5>/Sum2' incorporates:
   *  Inport: '<Root>/gain'
   *  Integrator: '<S5>/Integrator1'
   *  Product: '<S5>/Product2'
   *  Product: '<S5>/Product3'
   *  SignalConversion: '<S5>/TmpSignal ConversionAtProduct3Inport2'
   */
  rtb_Sum3_b = tunning_nominal_U.gain[2] *
    tunning_nominal_X.Integrator1_CSTATE_d - (tunning_nominal_U.gain[0] *
    tunning_nominal_B.d_x_b + tunning_nominal_U.gain[1] * tunning_nominal_B.vx);

  /* Sum: '<S2>/Sum4' incorporates:
   *  Inport: '<Root>/X'
   *  Inport: '<Root>/Y0'
   */
  tunning_nominal_B.d_y = tunning_nominal_U.X[1] - tunning_nominal_U.Y0[1];

  /* RateTransition: '<Root>/Rate Transition   ' incorporates:
   *  Inport: '<Root>/X'
   *  RateTransition: '<Root>/Rate Transition  '
   */
  if (rtmIsMajorTimeStep((&tunning_nominal_M)) &&
      (&tunning_nominal_M)->Timing.TaskCounters.TID[1] == 0) {
    if (rtmIsMajorTimeStep((&tunning_nominal_M)) &&
        (&tunning_nominal_M)->Timing.TaskCounters.TID[2] == 0) {
      tunning_nominal_B.d_y_l = tunning_nominal_B.d_y;
      tunning_nominal_B.vy = tunning_nominal_U.X[4];
    }

    if (rtmIsMajorTimeStep((&tunning_nominal_M)) &&
        (&tunning_nominal_M)->Timing.TaskCounters.TID[2] == 0) {
      tunning_nominal_B.RateTransition = tunning_nominal_U.X[8];
    }
  }

  /* Sum: '<S5>/Sum3' incorporates:
   *  Inport: '<Root>/gain'
   *  Integrator: '<S5>/Integrator'
   *  Product: '<S5>/Product1'
   *  Product: '<S5>/Product4'
   *  SignalConversion: '<S5>/TmpSignal ConversionAtProduct1Inport2'
   */
  rtb_Sum1_a = tunning_nominal_U.gain[5] * tunning_nominal_X.Integrator_CSTATE -
    (tunning_nominal_U.gain[3] * tunning_nominal_B.d_y_l +
     tunning_nominal_U.gain[4] * tunning_nominal_B.vy);

  /* Clock: '<Root>/Clock' */
  rtb_Clock = (&tunning_nominal_M)->Timing.t[0];

  /* MATLAB Function: '<S2>/FFW' incorporates:
   *  Inport: '<Root>/X'
   *  Inport: '<Root>/mode'
   */
  /* MATLAB Function 'Test_config_and_data/FFW': '<S12>:1' */
  /* '<S12>:1:2' ff = [0;0]; */
  rtb_ff_idx_0 = 0.0;
  rtb_ff_idx_1 = 0.0;

  /* '<S12>:1:3' g = 9.81; */
  /*  [x;y] = [cos(t); sin(t)] */
  /* '<S12>:1:5' if (test_mode == 2) */
  if ((tunning_nominal_U.mode == 2.0) && ((rtb_Clock >= 10.0) && (rtb_Clock <=
        50.0))) {
    /* '<S12>:1:6' if (t >=10) && (t<= 50) */
    /* '<S12>:1:7' axref_N = -cos(t); */
    /* '<S12>:1:8' ayref_N = -sin(t); */
    /* '<S12>:1:10' axref_b = cos(X(8))*cos(X(9))*axref_N + cos(X(8))*sin(X(9))*ayref_N; */
    /* '<S12>:1:11' ayref_b = (sin(X(7))*sin(X(8))*cos(X(9)) - cos(X(7))*sin(X(9)))*axref_N + (sin(X(7))*sin(X(8))*sin(X(9)) + cos(X(7))*cos(X(9)))*ayref_N; */
    /*   */
    /* '<S12>:1:13' ff = [-ayref_b/g; axref_b/g]; */
    rtb_ff_idx_0 = -((std::sin(tunning_nominal_U.X[6]) * std::sin
                      (tunning_nominal_U.X[7]) * std::cos(tunning_nominal_U.X[8])
                      - std::cos(tunning_nominal_U.X[6]) * std::sin
                      (tunning_nominal_U.X[8])) * -std::cos(rtb_Clock) + (std::
      sin(tunning_nominal_U.X[6]) * std::sin(tunning_nominal_U.X[7]) * std::sin
      (tunning_nominal_U.X[8]) + std::cos(tunning_nominal_U.X[6]) * std::cos
      (tunning_nominal_U.X[8])) * -std::sin(rtb_Clock)) / 9.81;
    rtb_ff_idx_1 = (std::cos(tunning_nominal_U.X[7]) * std::cos
                    (tunning_nominal_U.X[8]) * -std::cos(rtb_Clock) + std::cos
                    (tunning_nominal_U.X[7]) * std::sin(tunning_nominal_U.X[8]) *
                    -std::sin(rtb_Clock)) / 9.81;
  } else {
    /* '<S12>:1:14' else */
    /* '<S12>:1:15' ff = [0;0]; */
  }

  /* End of MATLAB Function: '<S2>/FFW' */

  /* Sum: '<Root>/Sum7' incorporates:
   *  Fcn: '<Root>/Fcn1'
   */
  tunning_nominal_B.Sum7 = (rtb_Sum1_a * std::cos
    (tunning_nominal_B.RateTransition) + rtb_Sum3_b * std::sin
    (tunning_nominal_B.RateTransition)) + rtb_ff_idx_0;

  /* Fcn: '<Root>/Fcn' */
  rtb_Sum3_b = -rtb_Sum1_a * std::sin(tunning_nominal_B.RateTransition) +
    rtb_Sum3_b * std::cos(tunning_nominal_B.RateTransition);

  /* Sum: '<Root>/Sum8' */
  tunning_nominal_B.Sum8 = rtb_Sum3_b + rtb_ff_idx_1;

  /* ZeroOrderHold: '<Root>/                        ' incorporates:
   *  ZeroOrderHold: '<Root>/         '
   */
  if (rtmIsMajorTimeStep((&tunning_nominal_M)) &&
      (&tunning_nominal_M)->Timing.TaskCounters.TID[2] == 0) {
    tunning_nominal_B.u = tunning_nominal_B.Sum7;

    /* Saturate: '<S8>/roll' */
    if (tunning_nominal_B.u > 0.52359877559829882) {
      tunning_nominal_B.roll = 0.52359877559829882;
    } else if (tunning_nominal_B.u < -0.52359877559829882) {
      tunning_nominal_B.roll = -0.52359877559829882;
    } else {
      tunning_nominal_B.roll = tunning_nominal_B.u;
    }

    /* End of Saturate: '<S8>/roll' */
    tunning_nominal_B.u_c = tunning_nominal_B.Sum8;

    /* Saturate: '<S6>/pitch' */
    if (tunning_nominal_B.u_c > 0.52359877559829882) {
      tunning_nominal_B.pitch = 0.52359877559829882;
    } else if (tunning_nominal_B.u_c < -0.52359877559829882) {
      tunning_nominal_B.pitch = -0.52359877559829882;
    } else {
      tunning_nominal_B.pitch = tunning_nominal_B.u_c;
    }

    /* End of Saturate: '<S6>/pitch' */
  }

  /* End of ZeroOrderHold: '<Root>/                        ' */

  /* Sum: '<S2>/Sum6' incorporates:
   *  Inport: '<Root>/X'
   *  Inport: '<Root>/Y0'
   */
  rtb_Sum3_b = tunning_nominal_U.X[8] - tunning_nominal_U.Y0[3];

  /* Sum: '<Root>/Sum2' incorporates:
   *  Inport: '<Root>/X'
   *  Inport: '<Root>/gain'
   *  Integrator: '<S10>/Integrator1'
   *  Product: '<S10>/Product'
   *  Product: '<S10>/Product1'
   *  Product: '<S6>/Product'
   *  Product: '<S8>/Product'
   *  SignalConversion: '<S10>/TmpSignal ConversionAtProduct1Inport2'
   *  SignalConversion: '<S6>/TmpSignal ConversionAtProductInport2'
   *  SignalConversion: '<S8>/TmpSignal ConversionAtProductInport2'
   *  Sum: '<S10>/Sum1'
   *  Sum: '<S6>/Sum1'
   *  Sum: '<S8>/Sum1'
   */
  rtb_Sum1_a = tunning_nominal_B.roll - (tunning_nominal_U.gain[9] *
    tunning_nominal_U.X[6] + tunning_nominal_U.gain[10] * tunning_nominal_U.X[9]);
  rtb_ff_idx_0 = tunning_nominal_B.pitch - (tunning_nominal_U.gain[12] *
    tunning_nominal_U.X[7] + tunning_nominal_U.gain[13] * tunning_nominal_U.X[10]);
  rtb_ff_idx_1 = tunning_nominal_U.gain[17] *
    tunning_nominal_X.Integrator1_CSTATE_j - (tunning_nominal_U.gain[15] *
    rtb_Sum3_b + tunning_nominal_U.gain[16] * tunning_nominal_U.X[11]);

  /* MATLAB Function 'Test_config_and_data/LOE_': '<S13>:1' */
  /* '<S13>:1:2' LOE_out = [0;0;0;0;0;0]; */
  /* '<S13>:1:3' for i = 1:6 */
  for (i = 0; i < 6; i++) {
    /* Gain: '<Root>/Control Allocation' incorporates:
     *  Saturate: '<Root>/                  '
     *  Sum: '<Root>/Sum2'
     */
    rtb_TLMN_idx_1 = tunning_nominal_ConstP.ControlAllocation_Gain[i + 18] *
      rtb_ff_idx_1 + (tunning_nominal_ConstP.ControlAllocation_Gain[i + 12] *
                      rtb_ff_idx_0 +
                      (tunning_nominal_ConstP.ControlAllocation_Gain[i + 6] *
                       rtb_Sum1_a + (tunning_nominal_B.dT + 15.107400000000002) *
                       tunning_nominal_ConstP.ControlAllocation_Gain[i]));

    /* Saturate: '<Root>/                  ' incorporates:
     *  Gain: '<Root>/Control Allocation'
     */
    if (rtb_TLMN_idx_1 > 8.54858) {
      rtb_u[i] = 8.54858;
    } else if (rtb_TLMN_idx_1 < 0.0) {
      rtb_u[i] = 0.0;
    } else {
      rtb_u[i] = rtb_TLMN_idx_1;
    }

    /* MATLAB Function: '<S2>/LOE_' incorporates:
     *  Inport: '<Root>/LOE_a'
     *  Inport: '<Root>/LOE_t'
     */
    rtb_LOE_out[i] = 0.0;

    /* '<S13>:1:4' if t>= LOE_t(i) */
    if (rtb_Clock >= tunning_nominal_U.LOE_t[i]) {
      /* '<S13>:1:5' LOE_out(i) = LOE(i); */
      rtb_LOE_out[i] = tunning_nominal_U.LOE_a[i];
    }

    /* End of MATLAB Function: '<S2>/LOE_' */
  }

  /* Gain: '<S3>/mapping_0_200' incorporates:
   *  Gain: '<S3>/      '
   *  Gain: '<S3>/rads_to_RPM'
   *  MATLAB Function: '<Root>/Actuator_Fault'
   *  Sqrt: '<S3>/Sqrt1'
   *  Sum: '<S3>/Sum3'
   */
  /* MATLAB Function 'Actuator_Fault': '<S1>:1' */
  /* '<S1>:1:2' T1 = T(1)*(1-LOE(1)); */
  /* '<S1>:1:3' T2 = T(2)*(1-LOE(2)); */
  /* '<S1>:1:4' T3 = T(3)*(1-LOE(3)); */
  /* '<S1>:1:5' T4 = T(4)*(1-LOE(4)); */
  /* '<S1>:1:6' T5 = T(5)*(1-LOE(5)); */
  /* '<S1>:1:7' T6 = T(6)*(1-LOE(6)); */
  /* '<S1>:1:8' T_f = [T1;T2;T3;T4;T5;T6]; */
  rtb_TLMN_idx_1 = (std::sqrt((1.0 - rtb_LOE_out[0]) * rtb_u[0] *
    116978.4923343994) * 9.5493 - 1250.0) * 0.022857142857142857;

  /* Saturate: '<S3>/Saturation' */
  if (rtb_TLMN_idx_1 > 200.0) {
    /* Outport: '<Root>/motor_command' */
    tunning_nominal_Y.motor_command[0] = 200.0;
  } else if (rtb_TLMN_idx_1 < 0.0) {
    /* Outport: '<Root>/motor_command' */
    tunning_nominal_Y.motor_command[0] = 0.0;
  } else {
    /* Outport: '<Root>/motor_command' */
    tunning_nominal_Y.motor_command[0] = rtb_TLMN_idx_1;
  }

  /* Gain: '<S3>/mapping_0_200' incorporates:
   *  Gain: '<S3>/      '
   *  Gain: '<S3>/rads_to_RPM'
   *  MATLAB Function: '<Root>/Actuator_Fault'
   *  Sqrt: '<S3>/Sqrt1'
   *  Sum: '<S3>/Sum3'
   */
  rtb_TLMN_idx_1 = (std::sqrt((1.0 - rtb_LOE_out[1]) * rtb_u[1] *
    116978.4923343994) * 9.5493 - 1250.0) * 0.022857142857142857;

  /* Saturate: '<S3>/Saturation' */
  if (rtb_TLMN_idx_1 > 200.0) {
    /* Outport: '<Root>/motor_command' */
    tunning_nominal_Y.motor_command[1] = 200.0;
  } else if (rtb_TLMN_idx_1 < 0.0) {
    /* Outport: '<Root>/motor_command' */
    tunning_nominal_Y.motor_command[1] = 0.0;
  } else {
    /* Outport: '<Root>/motor_command' */
    tunning_nominal_Y.motor_command[1] = rtb_TLMN_idx_1;
  }

  /* Gain: '<S3>/mapping_0_200' incorporates:
   *  Gain: '<S3>/      '
   *  Gain: '<S3>/rads_to_RPM'
   *  MATLAB Function: '<Root>/Actuator_Fault'
   *  Sqrt: '<S3>/Sqrt1'
   *  Sum: '<S3>/Sum3'
   */
  rtb_TLMN_idx_1 = (std::sqrt((1.0 - rtb_LOE_out[2]) * rtb_u[2] *
    116978.4923343994) * 9.5493 - 1250.0) * 0.022857142857142857;

  /* Saturate: '<S3>/Saturation' */
  if (rtb_TLMN_idx_1 > 200.0) {
    /* Outport: '<Root>/motor_command' */
    tunning_nominal_Y.motor_command[2] = 200.0;
  } else if (rtb_TLMN_idx_1 < 0.0) {
    /* Outport: '<Root>/motor_command' */
    tunning_nominal_Y.motor_command[2] = 0.0;
  } else {
    /* Outport: '<Root>/motor_command' */
    tunning_nominal_Y.motor_command[2] = rtb_TLMN_idx_1;
  }

  /* Gain: '<S3>/mapping_0_200' incorporates:
   *  Gain: '<S3>/      '
   *  Gain: '<S3>/rads_to_RPM'
   *  MATLAB Function: '<Root>/Actuator_Fault'
   *  Sqrt: '<S3>/Sqrt1'
   *  Sum: '<S3>/Sum3'
   */
  rtb_TLMN_idx_1 = (std::sqrt((1.0 - rtb_LOE_out[3]) * rtb_u[3] *
    116978.4923343994) * 9.5493 - 1250.0) * 0.022857142857142857;

  /* Saturate: '<S3>/Saturation' */
  if (rtb_TLMN_idx_1 > 200.0) {
    /* Outport: '<Root>/motor_command' */
    tunning_nominal_Y.motor_command[3] = 200.0;
  } else if (rtb_TLMN_idx_1 < 0.0) {
    /* Outport: '<Root>/motor_command' */
    tunning_nominal_Y.motor_command[3] = 0.0;
  } else {
    /* Outport: '<Root>/motor_command' */
    tunning_nominal_Y.motor_command[3] = rtb_TLMN_idx_1;
  }

  /* Gain: '<S3>/mapping_0_200' incorporates:
   *  Gain: '<S3>/      '
   *  Gain: '<S3>/rads_to_RPM'
   *  MATLAB Function: '<Root>/Actuator_Fault'
   *  Sqrt: '<S3>/Sqrt1'
   *  Sum: '<S3>/Sum3'
   */
  rtb_TLMN_idx_1 = (std::sqrt((1.0 - rtb_LOE_out[4]) * rtb_u[4] *
    116978.4923343994) * 9.5493 - 1250.0) * 0.022857142857142857;

  /* Saturate: '<S3>/Saturation' */
  if (rtb_TLMN_idx_1 > 200.0) {
    /* Outport: '<Root>/motor_command' */
    tunning_nominal_Y.motor_command[4] = 200.0;
  } else if (rtb_TLMN_idx_1 < 0.0) {
    /* Outport: '<Root>/motor_command' */
    tunning_nominal_Y.motor_command[4] = 0.0;
  } else {
    /* Outport: '<Root>/motor_command' */
    tunning_nominal_Y.motor_command[4] = rtb_TLMN_idx_1;
  }

  /* Gain: '<S3>/mapping_0_200' incorporates:
   *  Gain: '<S3>/      '
   *  Gain: '<S3>/rads_to_RPM'
   *  MATLAB Function: '<Root>/Actuator_Fault'
   *  Sqrt: '<S3>/Sqrt1'
   *  Sum: '<S3>/Sum3'
   */
  rtb_TLMN_idx_1 = (std::sqrt((1.0 - rtb_LOE_out[5]) * rtb_u[5] *
    116978.4923343994) * 9.5493 - 1250.0) * 0.022857142857142857;

  /* Saturate: '<S3>/Saturation' */
  if (rtb_TLMN_idx_1 > 200.0) {
    /* Outport: '<Root>/motor_command' */
    tunning_nominal_Y.motor_command[5] = 200.0;
  } else if (rtb_TLMN_idx_1 < 0.0) {
    /* Outport: '<Root>/motor_command' */
    tunning_nominal_Y.motor_command[5] = 0.0;
  } else {
    /* Outport: '<Root>/motor_command' */
    tunning_nominal_Y.motor_command[5] = rtb_TLMN_idx_1;
  }

  /* Outport: '<Root>/virtual_control' incorporates:
   *  Sum: '<Root>/Sum2'
   */
  tunning_nominal_Y.virtual_control[0] = tunning_nominal_B.dT +
    15.107400000000002;
  tunning_nominal_Y.virtual_control[1] = rtb_Sum1_a;
  tunning_nominal_Y.virtual_control[2] = rtb_ff_idx_0;
  tunning_nominal_Y.virtual_control[3] = rtb_ff_idx_1;

  /* MATLAB Function: '<S2>/MATLAB Function' incorporates:
   *  Inport: '<Root>/Y0'
   *  Inport: '<Root>/mode'
   *  Inport: '<Root>/ref'
   */
  /* MATLAB Function 'Test_config_and_data/MATLAB Function': '<S14>:1' */
  /* '<S14>:1:2' ref = Y0; */
  /* '<S14>:1:3' switch test_mode */
  switch ((int32_T)tunning_nominal_U.mode) {
   case 0:
    /* '<S14>:1:4' case 0      % manual test */
    /*  manual test */
    /* '<S14>:1:5' ref = ref_manual; */
    rtb_ff_idx_1 = tunning_nominal_U.ref[0];
    rtb_TLMN_idx_1 = tunning_nominal_U.ref[1];
    rtb_TLMN_idx_2 = tunning_nominal_U.ref[2];
    rtb_Clock = tunning_nominal_U.ref[3];
    break;

   case 1:
    /* '<S14>:1:6' case 1      % waypoint */
    /*  waypoint */
    /*          if t<=10 */
    /*              ref = [Y0(1); Y0(2); 0.5; Y0(4)]; */
    /*          elseif t <= 20 */
    /*              ref = [Y0(1)-1.5; Y0(2)+1.5; 0.5; Y0(4)]; */
    /*          elseif t <=30 */
    /*              ref = [Y0(1); Y0(2); 0.5; Y0(4)]; */
    /*          elseif t <=40 */
    /*              ref = [Y0(1); Y0(2); 0.5; Y0(4)+pi/2]; */
    /*          elseif t <=50 */
    /*              ref = [Y0(1); Y0(2); 0.5; Y0(4)]; */
    /*          else */
    /*              ref = Y0; */
    /*          end      */
    /* '<S14>:1:20' if t<=10 */
    if (rtb_Clock <= 10.0) {
      /* '<S14>:1:21' ref = [Y0(1); Y0(2); 0.5; Y0(4)]; */
      rtb_ff_idx_1 = tunning_nominal_U.Y0[0];
      rtb_TLMN_idx_1 = tunning_nominal_U.Y0[1];
      rtb_TLMN_idx_2 = 0.5;
      rtb_Clock = tunning_nominal_U.Y0[3];
    } else if (rtb_Clock <= 30.0) {
      /* '<S14>:1:22' elseif t <= 30 */
      /* '<S14>:1:23' ref = [Y0(1)-1.5; Y0(2); 0.5; Y0(4)]; */
      rtb_ff_idx_1 = tunning_nominal_U.Y0[0] - 1.5;
      rtb_TLMN_idx_1 = tunning_nominal_U.Y0[1];
      rtb_TLMN_idx_2 = 0.5;
      rtb_Clock = tunning_nominal_U.Y0[3];
    } else if (rtb_Clock <= 50.0) {
      /* '<S14>:1:24' elseif t <= 50 */
      /* '<S14>:1:25' ref = [Y0(1)+1.5; Y0(2); 0.5; Y0(4)]; */
      rtb_ff_idx_1 = tunning_nominal_U.Y0[0] + 1.5;
      rtb_TLMN_idx_1 = tunning_nominal_U.Y0[1];
      rtb_TLMN_idx_2 = 0.5;
      rtb_Clock = tunning_nominal_U.Y0[3];
    } else if (rtb_Clock <= 60.0) {
      /* '<S14>:1:26' elseif t <= 60 */
      /* '<S14>:1:27' ref = [Y0(1); Y0(2); 0.5; Y0(4)]; */
      rtb_ff_idx_1 = tunning_nominal_U.Y0[0];
      rtb_TLMN_idx_1 = tunning_nominal_U.Y0[1];
      rtb_TLMN_idx_2 = 0.5;
      rtb_Clock = tunning_nominal_U.Y0[3];
    } else {
      /* '<S14>:1:28' else */
      /* '<S14>:1:29' ref = Y0; */
      rtb_ff_idx_1 = tunning_nominal_U.Y0[0];
      rtb_TLMN_idx_1 = tunning_nominal_U.Y0[1];
      rtb_TLMN_idx_2 = tunning_nominal_U.Y0[2];
      rtb_Clock = tunning_nominal_U.Y0[3];
    }
    break;

   case 2:
    /* '<S14>:1:31' case 2      % circular tracking */
    /*  circular tracking */
    /* '<S14>:1:32' if t<=10 */
    if (rtb_Clock <= 10.0) {
      /* '<S14>:1:33' ref = [Y0(1); Y0(2); 0.75; Y0(4)]; */
      rtb_ff_idx_1 = tunning_nominal_U.Y0[0];
      rtb_TLMN_idx_1 = tunning_nominal_U.Y0[1];
      rtb_TLMN_idx_2 = 0.75;
      rtb_Clock = tunning_nominal_U.Y0[3];
    } else if (rtb_Clock <= 50.0) {
      /* '<S14>:1:34' elseif t <= 50 */
      /* '<S14>:1:35' ref = [cos(t); sin(t); 0.75; Y0(4)]; */
      rtb_ff_idx_1 = std::cos(rtb_Clock);
      rtb_TLMN_idx_1 = std::sin(rtb_Clock);
      rtb_TLMN_idx_2 = 0.75;
      rtb_Clock = tunning_nominal_U.Y0[3];
    } else if (rtb_Clock <= 60.0) {
      /* '<S14>:1:36' elseif t <= 60 */
      /* '<S14>:1:37' ref = [Y0(1); Y0(2); 0.75; Y0(4)]; */
      rtb_ff_idx_1 = tunning_nominal_U.Y0[0];
      rtb_TLMN_idx_1 = tunning_nominal_U.Y0[1];
      rtb_TLMN_idx_2 = 0.75;
      rtb_Clock = tunning_nominal_U.Y0[3];
    } else {
      /* '<S14>:1:38' else */
      /* '<S14>:1:39' ref = Y0; */
      rtb_ff_idx_1 = tunning_nominal_U.Y0[0];
      rtb_TLMN_idx_1 = tunning_nominal_U.Y0[1];
      rtb_TLMN_idx_2 = tunning_nominal_U.Y0[2];
      rtb_Clock = tunning_nominal_U.Y0[3];
    }

    /*          ref = [cos(t); sin(t);min(t,15);Y0(4)]; */
    break;

   default:
    /* '<S14>:1:42' otherwise */
    /* '<S14>:1:43' ref = Y0; */
    rtb_ff_idx_1 = tunning_nominal_U.Y0[0];
    rtb_TLMN_idx_1 = tunning_nominal_U.Y0[1];
    rtb_TLMN_idx_2 = tunning_nominal_U.Y0[2];
    rtb_Clock = tunning_nominal_U.Y0[3];
    break;
  }

  /* End of MATLAB Function: '<S2>/MATLAB Function' */

  /* Outport: '<Root>/ref_out' */
  tunning_nominal_Y.ref_out[0] = rtb_ff_idx_1;
  tunning_nominal_Y.ref_out[1] = rtb_TLMN_idx_1;
  tunning_nominal_Y.ref_out[2] = rtb_TLMN_idx_2;
  tunning_nominal_Y.ref_out[3] = rtb_Clock;

  /* Outport: '<Root>/LOE' */
  for (i = 0; i < 6; i++) {
    tunning_nominal_Y.LOE[i] = rtb_LOE_out[i];
  }

  /* End of Outport: '<Root>/LOE' */

  /* Sum: '<S2>/Sum' incorporates:
   *  Inport: '<Root>/Y0'
   */
  rtb_ff_idx_1 -= tunning_nominal_U.Y0[0];
  rtb_TLMN_idx_1 -= tunning_nominal_U.Y0[1];
  rtb_TLMN_idx_2 -= tunning_nominal_U.Y0[2];
  rtb_ff_idx_0 = rtb_Clock - tunning_nominal_U.Y0[3];

  /* RateLimiter: '<Root>/Rate Limiter' */
  if (tunning_nominal_DW.LastMajorTime == (rtInf)) {
    tunning_nominal_B.RateLimiter[0] = rtb_ff_idx_1;
    tunning_nominal_B.RateLimiter[1] = rtb_TLMN_idx_1;
    tunning_nominal_B.RateLimiter[2] = rtb_TLMN_idx_2;
    tunning_nominal_B.RateLimiter[3] = rtb_ff_idx_0;
  } else {
    rtb_Clock = (&tunning_nominal_M)->Timing.t[0] -
      tunning_nominal_DW.LastMajorTime;
    rtb_Sum1_a = rtb_Clock;
    rtb_Clock = -rtb_Clock;
    rateLimiterRate = rtb_ff_idx_1 - tunning_nominal_DW.PrevY[0];
    if (rateLimiterRate > rtb_Sum1_a) {
      tunning_nominal_B.RateLimiter[0] = tunning_nominal_DW.PrevY[0] +
        rtb_Sum1_a;
    } else if (rateLimiterRate < rtb_Clock) {
      tunning_nominal_B.RateLimiter[0] = tunning_nominal_DW.PrevY[0] + rtb_Clock;
    } else {
      tunning_nominal_B.RateLimiter[0] = rtb_ff_idx_1;
    }

    rateLimiterRate = rtb_TLMN_idx_1 - tunning_nominal_DW.PrevY[1];
    if (rateLimiterRate > rtb_Sum1_a) {
      tunning_nominal_B.RateLimiter[1] = tunning_nominal_DW.PrevY[1] +
        rtb_Sum1_a;
    } else if (rateLimiterRate < rtb_Clock) {
      tunning_nominal_B.RateLimiter[1] = tunning_nominal_DW.PrevY[1] + rtb_Clock;
    } else {
      tunning_nominal_B.RateLimiter[1] = rtb_TLMN_idx_1;
    }

    rateLimiterRate = rtb_TLMN_idx_2 - tunning_nominal_DW.PrevY[2];
    if (rateLimiterRate > rtb_Sum1_a) {
      tunning_nominal_B.RateLimiter[2] = tunning_nominal_DW.PrevY[2] +
        rtb_Sum1_a;
    } else if (rateLimiterRate < rtb_Clock) {
      tunning_nominal_B.RateLimiter[2] = tunning_nominal_DW.PrevY[2] + rtb_Clock;
    } else {
      tunning_nominal_B.RateLimiter[2] = rtb_TLMN_idx_2;
    }

    rateLimiterRate = rtb_ff_idx_0 - tunning_nominal_DW.PrevY[3];
    if (rateLimiterRate > rtb_Sum1_a) {
      tunning_nominal_B.RateLimiter[3] = tunning_nominal_DW.PrevY[3] +
        rtb_Sum1_a;
    } else if (rateLimiterRate < rtb_Clock) {
      tunning_nominal_B.RateLimiter[3] = tunning_nominal_DW.PrevY[3] + rtb_Clock;
    } else {
      tunning_nominal_B.RateLimiter[3] = rtb_ff_idx_0;
    }
  }

  /* End of RateLimiter: '<Root>/Rate Limiter' */

  /* RateTransition: '<Root>/Rate Transition ' */
  if ((rtmIsMajorTimeStep((&tunning_nominal_M)) &&
       (&tunning_nominal_M)->Timing.TaskCounters.TID[1] == 0) &&
      (rtmIsMajorTimeStep((&tunning_nominal_M)) &&
       (&tunning_nominal_M)->Timing.TaskCounters.TID[2] == 0)) {
    tunning_nominal_B.RateTransition_g[0] = tunning_nominal_B.RateLimiter[0];
    tunning_nominal_B.RateTransition_g[1] = tunning_nominal_B.RateLimiter[1];
    tunning_nominal_B.RateTransition_g[2] = tunning_nominal_B.RateLimiter[2];
    tunning_nominal_B.RateTransition_g[3] = tunning_nominal_B.RateLimiter[3];
  }

  /* End of RateTransition: '<Root>/Rate Transition ' */
  if (rtmIsMajorTimeStep((&tunning_nominal_M)) &&
      (&tunning_nominal_M)->Timing.TaskCounters.TID[2] == 0) {
    /* Saturate: '<S5>/x' */
    if (tunning_nominal_B.RateTransition_g[0] > 2.0) {
      rtb_TLMN_idx_1 = 2.0;
    } else if (tunning_nominal_B.RateTransition_g[0] < -2.0) {
      rtb_TLMN_idx_1 = -2.0;
    } else {
      rtb_TLMN_idx_1 = tunning_nominal_B.RateTransition_g[0];
    }

    /* End of Saturate: '<S5>/x' */

    /* Sum: '<S5>/Sum1' */
    rtb_TLMN_idx_1 -= tunning_nominal_B.d_x_b;

    /* Saturate: '<S5>/x_e' */
    if (rtb_TLMN_idx_1 > 2.0) {
      tunning_nominal_B.x_e = 2.0;
    } else if (rtb_TLMN_idx_1 < -2.0) {
      tunning_nominal_B.x_e = -2.0;
    } else {
      tunning_nominal_B.x_e = rtb_TLMN_idx_1;
    }

    /* End of Saturate: '<S5>/x_e' */

    /* Saturate: '<S5>/y' */
    if (tunning_nominal_B.RateTransition_g[1] > 2.0) {
      rtb_TLMN_idx_1 = 2.0;
    } else if (tunning_nominal_B.RateTransition_g[1] < -2.0) {
      rtb_TLMN_idx_1 = -2.0;
    } else {
      rtb_TLMN_idx_1 = tunning_nominal_B.RateTransition_g[1];
    }

    /* End of Saturate: '<S5>/y' */

    /* Sum: '<S5>/Sum4' */
    rtb_TLMN_idx_1 -= tunning_nominal_B.d_y_l;

    /* Saturate: '<S5>/y_e' */
    if (rtb_TLMN_idx_1 > 2.0) {
      tunning_nominal_B.y_e = 2.0;
    } else if (rtb_TLMN_idx_1 < -2.0) {
      tunning_nominal_B.y_e = -2.0;
    } else {
      tunning_nominal_B.y_e = rtb_TLMN_idx_1;
    }

    /* End of Saturate: '<S5>/y_e' */
  }

  /* Saturate: '<S10>/yaw' */
  if (rtb_ff_idx_0 > 3.1415926535897931) {
    rtb_ff_idx_0 = 3.1415926535897931;
  } else {
    if (rtb_ff_idx_0 < -3.1415926535897931) {
      rtb_ff_idx_0 = -3.1415926535897931;
    }
  }

  /* End of Saturate: '<S10>/yaw' */

  /* Sum: '<S10>/Sum3' */
  rtb_Sum3_b = rtb_ff_idx_0 - rtb_Sum3_b;

  /* Saturate: '<S10>/yaw_e' */
  if (rtb_Sum3_b > 1.5707963267948966) {
    tunning_nominal_B.yaw_e = 1.5707963267948966;
  } else if (rtb_Sum3_b < -1.5707963267948966) {
    tunning_nominal_B.yaw_e = -1.5707963267948966;
  } else {
    tunning_nominal_B.yaw_e = rtb_Sum3_b;
  }

  /* End of Saturate: '<S10>/yaw_e' */
  if (rtmIsMajorTimeStep((&tunning_nominal_M)) &&
      (&tunning_nominal_M)->Timing.TaskCounters.TID[2] == 0) {
    /* Saturate: '<S11>/z' */
    if (tunning_nominal_B.RateTransition_g[2] > 1.75) {
      rtb_TLMN_idx_1 = 1.75;
    } else if (tunning_nominal_B.RateTransition_g[2] < 0.0) {
      rtb_TLMN_idx_1 = 0.0;
    } else {
      rtb_TLMN_idx_1 = tunning_nominal_B.RateTransition_g[2];
    }

    /* End of Saturate: '<S11>/z' */

    /* Sum: '<S11>/Sum3' */
    rtb_TLMN_idx_1 -= tunning_nominal_B.d_z_k;

    /* Saturate: '<S11>/z_e' */
    if (rtb_TLMN_idx_1 > 1.0) {
      tunning_nominal_B.z_e = 1.0;
    } else if (rtb_TLMN_idx_1 < -1.0) {
      tunning_nominal_B.z_e = -1.0;
    } else {
      tunning_nominal_B.z_e = rtb_TLMN_idx_1;
    }

    /* End of Saturate: '<S11>/z_e' */
  }

  if (rtmIsMajorTimeStep((&tunning_nominal_M))) {
    /* Update for RateLimiter: '<Root>/Rate Limiter' */
    tunning_nominal_DW.PrevY[0] = tunning_nominal_B.RateLimiter[0];
    tunning_nominal_DW.PrevY[1] = tunning_nominal_B.RateLimiter[1];
    tunning_nominal_DW.PrevY[2] = tunning_nominal_B.RateLimiter[2];
    tunning_nominal_DW.PrevY[3] = tunning_nominal_B.RateLimiter[3];
    tunning_nominal_DW.LastMajorTime = (&tunning_nominal_M)->Timing.t[0];
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep((&tunning_nominal_M))) {
    rt_ertODEUpdateContinuousStates(&(&tunning_nominal_M)->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++(&tunning_nominal_M)->Timing.clockTick0)) {
      ++(&tunning_nominal_M)->Timing.clockTickH0;
    }

    (&tunning_nominal_M)->Timing.t[0] = rtsiGetSolverStopTime
      (&(&tunning_nominal_M)->solverInfo);

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
      (&tunning_nominal_M)->Timing.clockTick1++;
      if (!(&tunning_nominal_M)->Timing.clockTick1) {
        (&tunning_nominal_M)->Timing.clockTickH1++;
      }
    }

    rate_scheduler((&tunning_nominal_M));
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void tunning_nominalModelClass::tunning_nominal_derivatives()
{
  XDot_tunning_nominal_T *_rtXdot;
  _rtXdot = ((XDot_tunning_nominal_T *) (&tunning_nominal_M)->derivs);

  /* Derivatives for Integrator: '<S11>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = tunning_nominal_B.z_e;

  /* Derivatives for Integrator: '<S5>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_d = tunning_nominal_B.x_e;

  /* Derivatives for Integrator: '<S5>/Integrator' */
  _rtXdot->Integrator_CSTATE = tunning_nominal_B.y_e;

  /* Derivatives for Integrator: '<S10>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_j = tunning_nominal_B.yaw_e;
}

/* Model initialize function */
void tunning_nominalModelClass::initialize()
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)(&tunning_nominal_M), 0,
                sizeof(RT_MODEL_tunning_nominal_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&(&tunning_nominal_M)->solverInfo,
                          &(&tunning_nominal_M)->Timing.simTimeStep);
    rtsiSetTPtr(&(&tunning_nominal_M)->solverInfo, &rtmGetTPtr
                ((&tunning_nominal_M)));
    rtsiSetStepSizePtr(&(&tunning_nominal_M)->solverInfo, &(&tunning_nominal_M
                       )->Timing.stepSize0);
    rtsiSetdXPtr(&(&tunning_nominal_M)->solverInfo, &(&tunning_nominal_M)
                 ->derivs);
    rtsiSetContStatesPtr(&(&tunning_nominal_M)->solverInfo, (real_T **)
                         &(&tunning_nominal_M)->contStates);
    rtsiSetNumContStatesPtr(&(&tunning_nominal_M)->solverInfo,
      &(&tunning_nominal_M)->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&tunning_nominal_M)->solverInfo,
      &(&tunning_nominal_M)->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&tunning_nominal_M)->solverInfo,
      &(&tunning_nominal_M)->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&tunning_nominal_M)->solverInfo,
      &(&tunning_nominal_M)->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&(&tunning_nominal_M)->solverInfo, (&rtmGetErrorStatus
      ((&tunning_nominal_M))));
    rtsiSetRTModelPtr(&(&tunning_nominal_M)->solverInfo, (&tunning_nominal_M));
  }

  rtsiSetSimTimeStep(&(&tunning_nominal_M)->solverInfo, MAJOR_TIME_STEP);
  (&tunning_nominal_M)->intgData.y = (&tunning_nominal_M)->odeY;
  (&tunning_nominal_M)->intgData.f[0] = (&tunning_nominal_M)->odeF[0];
  (&tunning_nominal_M)->intgData.f[1] = (&tunning_nominal_M)->odeF[1];
  (&tunning_nominal_M)->intgData.f[2] = (&tunning_nominal_M)->odeF[2];
  (&tunning_nominal_M)->intgData.f[3] = (&tunning_nominal_M)->odeF[3];
  getRTM()->contStates = ((X_tunning_nominal_T *) &tunning_nominal_X);
  rtsiSetSolverData(&(&tunning_nominal_M)->solverInfo, (void *)
                    &(&tunning_nominal_M)->intgData);
  rtsiSetSolverName(&(&tunning_nominal_M)->solverInfo,"ode4");
  rtmSetTPtr(getRTM(), &(&tunning_nominal_M)->Timing.tArray[0]);
  (&tunning_nominal_M)->Timing.stepSize0 = 0.001;

  /* block I/O */
  (void) memset(((void *) &tunning_nominal_B), 0,
                sizeof(B_tunning_nominal_T));

  /* states (continuous) */
  {
    (void) memset((void *)&tunning_nominal_X, 0,
                  sizeof(X_tunning_nominal_T));
  }

  /* states (dwork) */
  (void) memset((void *)&tunning_nominal_DW, 0,
                sizeof(DW_tunning_nominal_T));

  /* external inputs */
  (void)memset((void *)&tunning_nominal_U, 0, sizeof(ExtU_tunning_nominal_T));

  /* external outputs */
  (void) memset((void *)&tunning_nominal_Y, 0,
                sizeof(ExtY_tunning_nominal_T));

  /* InitializeConditions for Integrator: '<S11>/Integrator1' */
  tunning_nominal_X.Integrator1_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S5>/Integrator1' */
  tunning_nominal_X.Integrator1_CSTATE_d = 0.0;

  /* InitializeConditions for Integrator: '<S5>/Integrator' */
  tunning_nominal_X.Integrator_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S10>/Integrator1' */
  tunning_nominal_X.Integrator1_CSTATE_j = 0.0;

  /* InitializeConditions for RateLimiter: '<Root>/Rate Limiter' */
  tunning_nominal_DW.LastMajorTime = (rtInf);
}

/* Model terminate function */
void tunning_nominalModelClass::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
tunning_nominalModelClass::tunning_nominalModelClass()
{
}

/* Destructor */
tunning_nominalModelClass::~tunning_nominalModelClass()
{
  /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_tunning_nominal_T * tunning_nominalModelClass::getRTM()
{
  return (&tunning_nominal_M);
}
