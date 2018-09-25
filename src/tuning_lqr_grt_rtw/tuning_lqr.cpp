/*
 * tuning_lqr.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "tuning_lqr".
 *
 * Model version              : 1.1142
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Fri Apr  6 11:33:33 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Passed (1), Warnings (3), Error (0)
 */

#include "tuning_lqr.h"
#include "tuning_lqr_private.h"

static void rate_scheduler(RT_MODEL_tuning_lqr_T *const tuning_lqr_M);

/*
 *   This function updates active task flag for each subrate.
 * The function is called at model base rate, hence the
 * generated code self-manages all its subrates.
 */
static void rate_scheduler(RT_MODEL_tuning_lqr_T *const tuning_lqr_M)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (tuning_lqr_M->Timing.TaskCounters.TID[2])++;
  if ((tuning_lqr_M->Timing.TaskCounters.TID[2]) > 4) {/* Sample time: [0.005s, 0.0s] */
    tuning_lqr_M->Timing.TaskCounters.TID[2] = 0;
  }
}

/*
 * This function updates continuous states using the ODE4 fixed-step
 * solver algorithm
 */
void tuning_lqrModelClass::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
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
  tuning_lqr_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  this->step();
  tuning_lqr_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  this->step();
  tuning_lqr_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  this->step();
  tuning_lqr_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void tuning_lqrModelClass::step()
{
  real_T rtb_Sum3_b;
  real_T rtb_Sum1_g;
  real_T rtb_u[6];
  real_T rtb_LOE_out[6];
  real_T rtb_Clock;
  int32_T i;
  real_T rtb_ff_idx_0;
  real_T rtb_ff_idx_1;
  real_T u0;
  if (rtmIsMajorTimeStep((&tuning_lqr_M))) {
    /* set solver stop time */
    if (!((&tuning_lqr_M)->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&(&tuning_lqr_M)->solverInfo, (((&tuning_lqr_M)
        ->Timing.clockTickH0 + 1) * (&tuning_lqr_M)->Timing.stepSize0 *
        4294967296.0));
    } else {
      rtsiSetSolverStopTime(&(&tuning_lqr_M)->solverInfo, (((&tuning_lqr_M)
        ->Timing.clockTick0 + 1) * (&tuning_lqr_M)->Timing.stepSize0 +
        (&tuning_lqr_M)->Timing.clockTickH0 * (&tuning_lqr_M)
        ->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep((&tuning_lqr_M))) {
    (&tuning_lqr_M)->Timing.t[0] = rtsiGetT(&(&tuning_lqr_M)->solverInfo);
  }

  /* Sum: '<S2>/Sum5' incorporates:
   *  Inport: '<Root>/X'
   *  Inport: '<Root>/Y0'
   */
  tuning_lqr_B.d_z = tuning_lqr_U.X[2] - tuning_lqr_U.Y0[2];

  /* RateTransition: '<Root>/Rate Transition   ' incorporates:
   *  Inport: '<Root>/X'
   */
  if ((rtmIsMajorTimeStep((&tuning_lqr_M)) &&
       (&tuning_lqr_M)->Timing.TaskCounters.TID[1] == 0) && (rtmIsMajorTimeStep
       ((&tuning_lqr_M)) &&
       (&tuning_lqr_M)->Timing.TaskCounters.TID[2] == 0)) {
    tuning_lqr_B.d_z_k = tuning_lqr_B.d_z;
    tuning_lqr_B.vz = tuning_lqr_U.X[5];
  }

  /* Sum: '<S9>/Sum1' incorporates:
   *  Inport: '<Root>/gain'
   *  Integrator: '<S9>/Integrator1'
   *  Product: '<S9>/Product'
   *  Product: '<S9>/Product1'
   *  SignalConversion: '<S9>/TmpSignal ConversionAtProduct1Inport2'
   */
  tuning_lqr_B.Sum1 = tuning_lqr_U.gain[8] * tuning_lqr_X.Integrator1_CSTATE
    - (tuning_lqr_U.gain[6] * tuning_lqr_B.d_z_k + tuning_lqr_U.gain[7] *
       tuning_lqr_B.vz);
  if (rtmIsMajorTimeStep((&tuning_lqr_M)) &&
      (&tuning_lqr_M)->Timing.TaskCounters.TID[2] == 0) {
    /* ZeroOrderHold: '<Root>/               ' */
    tuning_lqr_B.dT = tuning_lqr_B.Sum1;
  }

  /* Sum: '<S2>/Sum1' incorporates:
   *  Inport: '<Root>/X'
   *  Inport: '<Root>/Y0'
   */
  tuning_lqr_B.d_x = tuning_lqr_U.X[0] - tuning_lqr_U.Y0[0];

  /* RateTransition: '<Root>/Rate Transition   ' incorporates:
   *  Inport: '<Root>/X'
   */
  if ((rtmIsMajorTimeStep((&tuning_lqr_M)) &&
       (&tuning_lqr_M)->Timing.TaskCounters.TID[1] == 0) && (rtmIsMajorTimeStep
       ((&tuning_lqr_M)) &&
       (&tuning_lqr_M)->Timing.TaskCounters.TID[2] == 0)) {
    tuning_lqr_B.d_x_b = tuning_lqr_B.d_x;
    tuning_lqr_B.vx = tuning_lqr_U.X[3];
  }

  /* Sum: '<S6>/Sum1' incorporates:
   *  Inport: '<Root>/gain'
   *  Integrator: '<S6>/Integrator1'
   *  Product: '<S6>/Product'
   *  Product: '<S6>/Product1'
   *  SignalConversion: '<S6>/TmpSignal ConversionAtProduct1Inport2'
   */
  rtb_Sum3_b = tuning_lqr_U.gain[2] * tuning_lqr_X.Integrator1_CSTATE_h -
    (tuning_lqr_U.gain[0] * tuning_lqr_B.d_x_b + tuning_lqr_U.gain[1] *
     tuning_lqr_B.vx);

  /* Sum: '<S2>/Sum4' incorporates:
   *  Inport: '<Root>/X'
   *  Inport: '<Root>/Y0'
   */
  tuning_lqr_B.d_y = tuning_lqr_U.X[1] - tuning_lqr_U.Y0[1];

  /* RateTransition: '<Root>/Rate Transition   ' incorporates:
   *  Inport: '<Root>/X'
   *  RateTransition: '<Root>/Rate Transition  '
   */
  if (rtmIsMajorTimeStep((&tuning_lqr_M)) &&
      (&tuning_lqr_M)->Timing.TaskCounters.TID[1] == 0) {
    if (rtmIsMajorTimeStep((&tuning_lqr_M)) &&
        (&tuning_lqr_M)->Timing.TaskCounters.TID[2] == 0) {
      tuning_lqr_B.d_y_l = tuning_lqr_B.d_y;
      tuning_lqr_B.vy = tuning_lqr_U.X[4];
    }

    if (rtmIsMajorTimeStep((&tuning_lqr_M)) &&
        (&tuning_lqr_M)->Timing.TaskCounters.TID[2] == 0) {
      tuning_lqr_B.RateTransition = tuning_lqr_U.X[8];
    }
  }

  /* Sum: '<S7>/Sum1' incorporates:
   *  Inport: '<Root>/gain'
   *  Integrator: '<S7>/Integrator1'
   *  Product: '<S7>/Product'
   *  Product: '<S7>/Product1'
   *  SignalConversion: '<S7>/TmpSignal ConversionAtProduct1Inport2'
   */
  rtb_Sum1_g = tuning_lqr_U.gain[5] * tuning_lqr_X.Integrator1_CSTATE_g -
    (tuning_lqr_U.gain[3] * tuning_lqr_B.d_y_l + tuning_lqr_U.gain[4] *
     tuning_lqr_B.vy);

  /* Clock: '<Root>/Clock' */
  rtb_Clock = (&tuning_lqr_M)->Timing.t[0];

  /* MATLAB Function: '<S2>/FFW' incorporates:
   *  Inport: '<Root>/X'
   *  Inport: '<Root>/mode'
   */
  /* MATLAB Function 'Test_config_and_data/FFW': '<S10>:1' */
  /* '<S10>:1:2' ff = [0;0]; */
  rtb_ff_idx_0 = 0.0;
  rtb_ff_idx_1 = 0.0;

  /* '<S10>:1:3' g = 9.81; */
  /*  [x;y] = [cos(t); sin(t)] */
  /* '<S10>:1:5' if (test_mode == 2) */
  if ((tuning_lqr_U.mode == 2.0) && ((rtb_Clock >= 10.0) && (rtb_Clock <= 50.0)))
  {
    /* '<S10>:1:6' if (t >=10) && (t<= 50) */
    /* '<S10>:1:7' axref_N = -cos(t); */
    /* '<S10>:1:8' ayref_N = -sin(t); */
    /* '<S10>:1:10' axref_b = cos(X(8))*cos(X(9))*axref_N + cos(X(8))*sin(X(9))*ayref_N; */
    /* '<S10>:1:11' ayref_b = (sin(X(7))*sin(X(8))*cos(X(9)) - cos(X(7))*sin(X(9)))*axref_N + (sin(X(7))*sin(X(8))*sin(X(9)) + cos(X(7))*cos(X(9)))*ayref_N; */
    /*   */
    /* '<S10>:1:13' ff = [-ayref_b/g; axref_b/g]; */
    rtb_ff_idx_0 = -((std::sin(tuning_lqr_U.X[6]) * std::sin(tuning_lqr_U.X[7])
                      * std::cos(tuning_lqr_U.X[8]) - std::cos(tuning_lqr_U.X
      [6]) * std::sin(tuning_lqr_U.X[8])) * -std::cos(rtb_Clock) + (std::sin
      (tuning_lqr_U.X[6]) * std::sin(tuning_lqr_U.X[7]) * std::sin
      (tuning_lqr_U.X[8]) + std::cos(tuning_lqr_U.X[6]) * std::cos
      (tuning_lqr_U.X[8])) * -std::sin(rtb_Clock)) / 9.81;
    rtb_ff_idx_1 = (std::cos(tuning_lqr_U.X[7]) * std::cos(tuning_lqr_U.X[8]) *
                    -std::cos(rtb_Clock) + std::cos(tuning_lqr_U.X[7]) * std::
                    sin(tuning_lqr_U.X[8]) * -std::sin(rtb_Clock)) / 9.81;
  } else {
    /* '<S10>:1:14' else */
    /* '<S10>:1:15' ff = [0;0]; */
  }

  /* End of MATLAB Function: '<S2>/FFW' */

  /* Sum: '<Root>/Sum7' incorporates:
   *  Fcn: '<Root>/Fcn1'
   */
  tuning_lqr_B.Sum7 = (rtb_Sum1_g * std::cos(tuning_lqr_B.RateTransition) +
                        rtb_Sum3_b * std::sin(tuning_lqr_B.RateTransition)) +
    rtb_ff_idx_0;

  /* Fcn: '<Root>/Fcn' */
  rtb_Sum3_b = -rtb_Sum1_g * std::sin(tuning_lqr_B.RateTransition) + rtb_Sum3_b
    * std::cos(tuning_lqr_B.RateTransition);

  /* Sum: '<Root>/Sum8' */
  tuning_lqr_B.Sum8 = rtb_Sum3_b + rtb_ff_idx_1;

  /* ZeroOrderHold: '<Root>/                        ' incorporates:
   *  ZeroOrderHold: '<Root>/         '
   */
  if (rtmIsMajorTimeStep((&tuning_lqr_M)) &&
      (&tuning_lqr_M)->Timing.TaskCounters.TID[2] == 0) {
    tuning_lqr_B.u = tuning_lqr_B.Sum7;

    /* Saturate: '<S5>/roll' */
    if (tuning_lqr_B.u > 0.52359877559829882) {
      tuning_lqr_B.roll = 0.52359877559829882;
    } else if (tuning_lqr_B.u < -0.52359877559829882) {
      tuning_lqr_B.roll = -0.52359877559829882;
    } else {
      tuning_lqr_B.roll = tuning_lqr_B.u;
    }

    /* End of Saturate: '<S5>/roll' */
    tuning_lqr_B.u_c = tuning_lqr_B.Sum8;

    /* Saturate: '<S4>/pitch' */
    if (tuning_lqr_B.u_c > 0.52359877559829882) {
      tuning_lqr_B.pitch = 0.52359877559829882;
    } else if (tuning_lqr_B.u_c < -0.52359877559829882) {
      tuning_lqr_B.pitch = -0.52359877559829882;
    } else {
      tuning_lqr_B.pitch = tuning_lqr_B.u_c;
    }

    /* End of Saturate: '<S4>/pitch' */
  }

  /* End of ZeroOrderHold: '<Root>/                        ' */

  /* Sum: '<S2>/Sum6' incorporates:
   *  Inport: '<Root>/X'
   *  Inport: '<Root>/Y0'
   */
  rtb_Sum3_b = tuning_lqr_U.X[8] - tuning_lqr_U.Y0[3];

  /* Sum: '<Root>/Sum2' incorporates:
   *  Inport: '<Root>/X'
   *  Inport: '<Root>/gain'
   *  Integrator: '<S8>/Integrator1'
   *  Product: '<S4>/Product'
   *  Product: '<S5>/Product'
   *  Product: '<S8>/Product'
   *  Product: '<S8>/Product1'
   *  SignalConversion: '<S4>/TmpSignal ConversionAtProductInport2'
   *  SignalConversion: '<S5>/TmpSignal ConversionAtProductInport2'
   *  SignalConversion: '<S8>/TmpSignal ConversionAtProduct1Inport2'
   *  Sum: '<S4>/Sum1'
   *  Sum: '<S5>/Sum1'
   *  Sum: '<S8>/Sum1'
   */
  rtb_Sum1_g = tuning_lqr_B.roll - (tuning_lqr_U.gain[9] * tuning_lqr_U.X[6]
    + tuning_lqr_U.gain[10] * tuning_lqr_U.X[9]);
  rtb_ff_idx_0 = tuning_lqr_B.pitch - (tuning_lqr_U.gain[12] *
    tuning_lqr_U.X[7] + tuning_lqr_U.gain[13] * tuning_lqr_U.X[10]);
  rtb_ff_idx_1 = tuning_lqr_U.gain[17] * tuning_lqr_X.Integrator1_CSTATE_j -
    (tuning_lqr_U.gain[15] * rtb_Sum3_b + tuning_lqr_U.gain[16] *
     tuning_lqr_U.X[11]);

  /* MATLAB Function 'Test_config_and_data/LOE_': '<S11>:1' */
  /* '<S11>:1:2' LOE_out = [0;0;0;0;0;0]; */
  /* '<S11>:1:3' for i = 1:6 */
  for (i = 0; i < 6; i++) {
    /* Gain: '<Root>/Control Allocation' incorporates:
     *  Saturate: '<Root>/                  '
     *  Sum: '<Root>/Sum2'
     */
    u0 = tuning_lqr_ConstP.ControlAllocation_Gain[i + 18] * rtb_ff_idx_1 +
      (tuning_lqr_ConstP.ControlAllocation_Gain[i + 12] * rtb_ff_idx_0 +
       (tuning_lqr_ConstP.ControlAllocation_Gain[i + 6] * rtb_Sum1_g +
        (tuning_lqr_B.dT + 15.107400000000002) *
        tuning_lqr_ConstP.ControlAllocation_Gain[i]));

    /* Saturate: '<Root>/                  ' incorporates:
     *  Gain: '<Root>/Control Allocation'
     */
    if (u0 > 8.54858) {
      rtb_u[i] = 8.54858;
    } else if (u0 < 0.0) {
      rtb_u[i] = 0.0;
    } else {
      rtb_u[i] = u0;
    }

    /* MATLAB Function: '<S2>/LOE_' incorporates:
     *  Inport: '<Root>/LOE_a'
     *  Inport: '<Root>/LOE_t'
     */
    rtb_LOE_out[i] = 0.0;

    /* '<S11>:1:4' if t>= LOE_t(i) */
    if (rtb_Clock >= tuning_lqr_U.LOE_t[i]) {
      /* '<S11>:1:5' LOE_out(i) = LOE(i); */
      rtb_LOE_out[i] = tuning_lqr_U.LOE_a[i];
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
  u0 = (std::sqrt((1.0 - rtb_LOE_out[0]) * rtb_u[0] * 116978.4923343994) *
        9.5493 - 1250.0) * 0.022857142857142857;

  /* Saturate: '<S3>/Saturation' */
  if (u0 > 200.0) {
    /* Outport: '<Root>/motor_command' */
    tuning_lqr_Y.motor_command[0] = 200.0;
  } else if (u0 < 0.0) {
    /* Outport: '<Root>/motor_command' */
    tuning_lqr_Y.motor_command[0] = 0.0;
  } else {
    /* Outport: '<Root>/motor_command' */
    tuning_lqr_Y.motor_command[0] = u0;
  }

  /* Gain: '<S3>/mapping_0_200' incorporates:
   *  Gain: '<S3>/      '
   *  Gain: '<S3>/rads_to_RPM'
   *  MATLAB Function: '<Root>/Actuator_Fault'
   *  Sqrt: '<S3>/Sqrt1'
   *  Sum: '<S3>/Sum3'
   */
  u0 = (std::sqrt((1.0 - rtb_LOE_out[1]) * rtb_u[1] * 116978.4923343994) *
        9.5493 - 1250.0) * 0.022857142857142857;

  /* Saturate: '<S3>/Saturation' */
  if (u0 > 200.0) {
    /* Outport: '<Root>/motor_command' */
    tuning_lqr_Y.motor_command[1] = 200.0;
  } else if (u0 < 0.0) {
    /* Outport: '<Root>/motor_command' */
    tuning_lqr_Y.motor_command[1] = 0.0;
  } else {
    /* Outport: '<Root>/motor_command' */
    tuning_lqr_Y.motor_command[1] = u0;
  }

  /* Gain: '<S3>/mapping_0_200' incorporates:
   *  Gain: '<S3>/      '
   *  Gain: '<S3>/rads_to_RPM'
   *  MATLAB Function: '<Root>/Actuator_Fault'
   *  Sqrt: '<S3>/Sqrt1'
   *  Sum: '<S3>/Sum3'
   */
  u0 = (std::sqrt((1.0 - rtb_LOE_out[2]) * rtb_u[2] * 116978.4923343994) *
        9.5493 - 1250.0) * 0.022857142857142857;

  /* Saturate: '<S3>/Saturation' */
  if (u0 > 200.0) {
    /* Outport: '<Root>/motor_command' */
    tuning_lqr_Y.motor_command[2] = 200.0;
  } else if (u0 < 0.0) {
    /* Outport: '<Root>/motor_command' */
    tuning_lqr_Y.motor_command[2] = 0.0;
  } else {
    /* Outport: '<Root>/motor_command' */
    tuning_lqr_Y.motor_command[2] = u0;
  }

  /* Gain: '<S3>/mapping_0_200' incorporates:
   *  Gain: '<S3>/      '
   *  Gain: '<S3>/rads_to_RPM'
   *  MATLAB Function: '<Root>/Actuator_Fault'
   *  Sqrt: '<S3>/Sqrt1'
   *  Sum: '<S3>/Sum3'
   */
  u0 = (std::sqrt((1.0 - rtb_LOE_out[3]) * rtb_u[3] * 116978.4923343994) *
        9.5493 - 1250.0) * 0.022857142857142857;

  /* Saturate: '<S3>/Saturation' */
  if (u0 > 200.0) {
    /* Outport: '<Root>/motor_command' */
    tuning_lqr_Y.motor_command[3] = 200.0;
  } else if (u0 < 0.0) {
    /* Outport: '<Root>/motor_command' */
    tuning_lqr_Y.motor_command[3] = 0.0;
  } else {
    /* Outport: '<Root>/motor_command' */
    tuning_lqr_Y.motor_command[3] = u0;
  }

  /* Gain: '<S3>/mapping_0_200' incorporates:
   *  Gain: '<S3>/      '
   *  Gain: '<S3>/rads_to_RPM'
   *  MATLAB Function: '<Root>/Actuator_Fault'
   *  Sqrt: '<S3>/Sqrt1'
   *  Sum: '<S3>/Sum3'
   */
  u0 = (std::sqrt((1.0 - rtb_LOE_out[4]) * rtb_u[4] * 116978.4923343994) *
        9.5493 - 1250.0) * 0.022857142857142857;

  /* Saturate: '<S3>/Saturation' */
  if (u0 > 200.0) {
    /* Outport: '<Root>/motor_command' */
    tuning_lqr_Y.motor_command[4] = 200.0;
  } else if (u0 < 0.0) {
    /* Outport: '<Root>/motor_command' */
    tuning_lqr_Y.motor_command[4] = 0.0;
  } else {
    /* Outport: '<Root>/motor_command' */
    tuning_lqr_Y.motor_command[4] = u0;
  }

  /* Gain: '<S3>/mapping_0_200' incorporates:
   *  Gain: '<S3>/      '
   *  Gain: '<S3>/rads_to_RPM'
   *  MATLAB Function: '<Root>/Actuator_Fault'
   *  Sqrt: '<S3>/Sqrt1'
   *  Sum: '<S3>/Sum3'
   */
  u0 = (std::sqrt((1.0 - rtb_LOE_out[5]) * rtb_u[5] * 116978.4923343994) *
        9.5493 - 1250.0) * 0.022857142857142857;

  /* Saturate: '<S3>/Saturation' */
  if (u0 > 200.0) {
    /* Outport: '<Root>/motor_command' */
    tuning_lqr_Y.motor_command[5] = 200.0;
  } else if (u0 < 0.0) {
    /* Outport: '<Root>/motor_command' */
    tuning_lqr_Y.motor_command[5] = 0.0;
  } else {
    /* Outport: '<Root>/motor_command' */
    tuning_lqr_Y.motor_command[5] = u0;
  }

  /* Outport: '<Root>/virtual_control' incorporates:
   *  Sum: '<Root>/Sum2'
   */
  tuning_lqr_Y.virtual_control[0] = tuning_lqr_B.dT + 15.107400000000002;
  tuning_lqr_Y.virtual_control[1] = rtb_Sum1_g;
  tuning_lqr_Y.virtual_control[2] = rtb_ff_idx_0;
  tuning_lqr_Y.virtual_control[3] = rtb_ff_idx_1;

  /* MATLAB Function: '<S2>/MATLAB Function' incorporates:
   *  Inport: '<Root>/Y0'
   *  Inport: '<Root>/mode'
   *  Inport: '<Root>/ref'
   */
  /* MATLAB Function 'Test_config_and_data/MATLAB Function': '<S12>:1' */
  /* '<S12>:1:2' ref = Y0; */
  /* '<S12>:1:3' switch test_mode */
  switch ((int32_T)tuning_lqr_U.mode) {
   case 0:
    /* '<S12>:1:4' case 0      % manual test */
    /*  manual test */
    /* '<S12>:1:5' ref = ref_manual; */
    rtb_Sum1_g = tuning_lqr_U.ref[0];
    rtb_Clock = tuning_lqr_U.ref[1];
    rtb_ff_idx_0 = tuning_lqr_U.ref[2];
    rtb_ff_idx_1 = tuning_lqr_U.ref[3];
    break;

   case 1:
    /* '<S12>:1:6' case 1      % waypoint */
    /*  waypoint */
    /* '<S12>:1:7' if t<=10 */
    if (rtb_Clock <= 10.0) {
      /* '<S12>:1:8' ref = [Y0(1); Y0(2); 0.5; Y0(4)]; */
      rtb_Sum1_g = tuning_lqr_U.Y0[0];
      rtb_Clock = tuning_lqr_U.Y0[1];
      rtb_ff_idx_0 = 0.5;
      rtb_ff_idx_1 = tuning_lqr_U.Y0[3];
    } else if (rtb_Clock <= 20.0) {
      /* '<S12>:1:9' elseif t <= 20 */
      /* '<S12>:1:10' ref = [Y0(1)-1.5; Y0(2)+1.5; 0.5; Y0(4)]; */
      rtb_Sum1_g = tuning_lqr_U.Y0[0] - 1.5;
      rtb_Clock = tuning_lqr_U.Y0[1] + 1.5;
      rtb_ff_idx_0 = 0.5;
      rtb_ff_idx_1 = tuning_lqr_U.Y0[3];
    } else if (rtb_Clock <= 30.0) {
      /* '<S12>:1:11' elseif t <=30 */
      /* '<S12>:1:12' ref = [Y0(1); Y0(2); 0.5; Y0(4)]; */
      rtb_Sum1_g = tuning_lqr_U.Y0[0];
      rtb_Clock = tuning_lqr_U.Y0[1];
      rtb_ff_idx_0 = 0.5;
      rtb_ff_idx_1 = tuning_lqr_U.Y0[3];
    } else if (rtb_Clock <= 40.0) {
      /* '<S12>:1:13' elseif t <=40 */
      /* '<S12>:1:14' ref = [Y0(1); Y0(2); 0.5; Y0(4)+pi/2]; */
      rtb_Sum1_g = tuning_lqr_U.Y0[0];
      rtb_Clock = tuning_lqr_U.Y0[1];
      rtb_ff_idx_0 = 0.5;
      rtb_ff_idx_1 = tuning_lqr_U.Y0[3] + 1.5707963267948966;
    } else if (rtb_Clock <= 50.0) {
      /* '<S12>:1:15' elseif t <=50 */
      /* '<S12>:1:16' ref = [Y0(1); Y0(2); 0.5; Y0(4)]; */
      rtb_Sum1_g = tuning_lqr_U.Y0[0];
      rtb_Clock = tuning_lqr_U.Y0[1];
      rtb_ff_idx_0 = 0.5;
      rtb_ff_idx_1 = tuning_lqr_U.Y0[3];
    } else {
      /* '<S12>:1:17' else */
      /* '<S12>:1:18' ref = Y0; */
      rtb_Sum1_g = tuning_lqr_U.Y0[0];
      rtb_Clock = tuning_lqr_U.Y0[1];
      rtb_ff_idx_0 = tuning_lqr_U.Y0[2];
      rtb_ff_idx_1 = tuning_lqr_U.Y0[3];
    }
    break;

   case 2:
    /* '<S12>:1:20' case 2      % circular tracking */
    /*  circular tracking */
    /* '<S12>:1:21' if t<=10 */
    if (rtb_Clock <= 10.0) {
      /* '<S12>:1:22' ref = [Y0(1); Y0(2); 0.75; Y0(4)]; */
      rtb_Sum1_g = tuning_lqr_U.Y0[0];
      rtb_Clock = tuning_lqr_U.Y0[1];
      rtb_ff_idx_0 = 0.75;
      rtb_ff_idx_1 = tuning_lqr_U.Y0[3];
    } else if (rtb_Clock <= 50.0) {
      /* '<S12>:1:23' elseif t <= 50 */
      /* '<S12>:1:24' ref = [cos(t); sin(t); 0.75; Y0(4)]; */
      rtb_Sum1_g = std::cos(rtb_Clock);
      rtb_Clock = std::sin(rtb_Clock);
      rtb_ff_idx_0 = 0.75;
      rtb_ff_idx_1 = tuning_lqr_U.Y0[3];
    } else if (rtb_Clock <= 60.0) {
      /* '<S12>:1:25' elseif t <= 60 */
      /* '<S12>:1:26' ref = [Y0(1); Y0(2); 0.75; Y0(4)]; */
      rtb_Sum1_g = tuning_lqr_U.Y0[0];
      rtb_Clock = tuning_lqr_U.Y0[1];
      rtb_ff_idx_0 = 0.75;
      rtb_ff_idx_1 = tuning_lqr_U.Y0[3];
    } else {
      /* '<S12>:1:27' else */
      /* '<S12>:1:28' ref = Y0; */
      rtb_Sum1_g = tuning_lqr_U.Y0[0];
      rtb_Clock = tuning_lqr_U.Y0[1];
      rtb_ff_idx_0 = tuning_lqr_U.Y0[2];
      rtb_ff_idx_1 = tuning_lqr_U.Y0[3];
    }

    /*          ref = [cos(t); sin(t);min(t,15);Y0(4)]; */
    break;

   default:
    /* '<S12>:1:31' otherwise */
    /* '<S12>:1:32' ref = Y0; */
    rtb_Sum1_g = tuning_lqr_U.Y0[0];
    rtb_Clock = tuning_lqr_U.Y0[1];
    rtb_ff_idx_0 = tuning_lqr_U.Y0[2];
    rtb_ff_idx_1 = tuning_lqr_U.Y0[3];
    break;
  }

  /* End of MATLAB Function: '<S2>/MATLAB Function' */

  /* Outport: '<Root>/ref_out' */
  tuning_lqr_Y.ref_out[0] = rtb_Sum1_g;
  tuning_lqr_Y.ref_out[1] = rtb_Clock;
  tuning_lqr_Y.ref_out[2] = rtb_ff_idx_0;
  tuning_lqr_Y.ref_out[3] = rtb_ff_idx_1;

  /* Outport: '<Root>/LOE' */
  for (i = 0; i < 6; i++) {
    tuning_lqr_Y.LOE[i] = rtb_LOE_out[i];
  }

  /* End of Outport: '<Root>/LOE' */

  /* Sum: '<S2>/Sum' incorporates:
   *  Inport: '<Root>/Y0'
   */
  tuning_lqr_B.Sum[0] = rtb_Sum1_g - tuning_lqr_U.Y0[0];
  tuning_lqr_B.Sum[1] = rtb_Clock - tuning_lqr_U.Y0[1];
  tuning_lqr_B.Sum[2] = rtb_ff_idx_0 - tuning_lqr_U.Y0[2];
  tuning_lqr_B.Sum[3] = rtb_ff_idx_1 - tuning_lqr_U.Y0[3];

  /* RateTransition: '<Root>/Rate Transition ' */
  if ((rtmIsMajorTimeStep((&tuning_lqr_M)) &&
       (&tuning_lqr_M)->Timing.TaskCounters.TID[1] == 0) && (rtmIsMajorTimeStep
       ((&tuning_lqr_M)) &&
       (&tuning_lqr_M)->Timing.TaskCounters.TID[2] == 0)) {
    tuning_lqr_B.RateTransition_g[0] = tuning_lqr_B.Sum[0];
    tuning_lqr_B.RateTransition_g[1] = tuning_lqr_B.Sum[1];
    tuning_lqr_B.RateTransition_g[2] = tuning_lqr_B.Sum[2];
    tuning_lqr_B.RateTransition_g[3] = tuning_lqr_B.Sum[3];
  }

  /* End of RateTransition: '<Root>/Rate Transition ' */
  if (rtmIsMajorTimeStep((&tuning_lqr_M)) &&
      (&tuning_lqr_M)->Timing.TaskCounters.TID[2] == 0) {
    /* Saturate: '<S6>/x' */
    if (tuning_lqr_B.RateTransition_g[0] > 2.0) {
      u0 = 2.0;
    } else if (tuning_lqr_B.RateTransition_g[0] < -2.0) {
      u0 = -2.0;
    } else {
      u0 = tuning_lqr_B.RateTransition_g[0];
    }

    /* End of Saturate: '<S6>/x' */

    /* Sum: '<S6>/Sum3' */
    u0 -= tuning_lqr_B.d_x_b;

    /* Saturate: '<S6>/x_e' */
    if (u0 > 2.0) {
      tuning_lqr_B.x_e = 2.0;
    } else if (u0 < -2.0) {
      tuning_lqr_B.x_e = -2.0;
    } else {
      tuning_lqr_B.x_e = u0;
    }

    /* End of Saturate: '<S6>/x_e' */

    /* Saturate: '<S7>/y' */
    if (tuning_lqr_B.RateTransition_g[1] > 2.0) {
      u0 = 2.0;
    } else if (tuning_lqr_B.RateTransition_g[1] < -2.0) {
      u0 = -2.0;
    } else {
      u0 = tuning_lqr_B.RateTransition_g[1];
    }

    /* End of Saturate: '<S7>/y' */

    /* Sum: '<S7>/Sum3' */
    u0 -= tuning_lqr_B.d_y_l;

    /* Saturate: '<S7>/y_e' */
    if (u0 > 2.0) {
      tuning_lqr_B.y_e = 2.0;
    } else if (u0 < -2.0) {
      tuning_lqr_B.y_e = -2.0;
    } else {
      tuning_lqr_B.y_e = u0;
    }

    /* End of Saturate: '<S7>/y_e' */
  }

  /* Saturate: '<S8>/yaw' */
  if (tuning_lqr_B.Sum[3] > 3.1415926535897931) {
    u0 = 3.1415926535897931;
  } else if (tuning_lqr_B.Sum[3] < -3.1415926535897931) {
    u0 = -3.1415926535897931;
  } else {
    u0 = tuning_lqr_B.Sum[3];
  }

  /* End of Saturate: '<S8>/yaw' */

  /* Sum: '<S8>/Sum3' */
  rtb_Sum3_b = u0 - rtb_Sum3_b;

  /* Saturate: '<S8>/yaw_e' */
  if (rtb_Sum3_b > 1.5707963267948966) {
    tuning_lqr_B.yaw_e = 1.5707963267948966;
  } else if (rtb_Sum3_b < -1.5707963267948966) {
    tuning_lqr_B.yaw_e = -1.5707963267948966;
  } else {
    tuning_lqr_B.yaw_e = rtb_Sum3_b;
  }

  /* End of Saturate: '<S8>/yaw_e' */
  if (rtmIsMajorTimeStep((&tuning_lqr_M)) &&
      (&tuning_lqr_M)->Timing.TaskCounters.TID[2] == 0) {
    /* Saturate: '<S9>/z' */
    if (tuning_lqr_B.RateTransition_g[2] > 1.75) {
      u0 = 1.75;
    } else if (tuning_lqr_B.RateTransition_g[2] < 0.0) {
      u0 = 0.0;
    } else {
      u0 = tuning_lqr_B.RateTransition_g[2];
    }

    /* End of Saturate: '<S9>/z' */

    /* Sum: '<S9>/Sum3' */
    u0 -= tuning_lqr_B.d_z_k;

    /* Saturate: '<S9>/z_e' */
    if (u0 > 1.0) {
      tuning_lqr_B.z_e = 1.0;
    } else if (u0 < -1.0) {
      tuning_lqr_B.z_e = -1.0;
    } else {
      tuning_lqr_B.z_e = u0;
    }

    /* End of Saturate: '<S9>/z_e' */
  }

  if (rtmIsMajorTimeStep((&tuning_lqr_M))) {
    rt_ertODEUpdateContinuousStates(&(&tuning_lqr_M)->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++(&tuning_lqr_M)->Timing.clockTick0)) {
      ++(&tuning_lqr_M)->Timing.clockTickH0;
    }

    (&tuning_lqr_M)->Timing.t[0] = rtsiGetSolverStopTime(&(&tuning_lqr_M)
      ->solverInfo);

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
      (&tuning_lqr_M)->Timing.clockTick1++;
      if (!(&tuning_lqr_M)->Timing.clockTick1) {
        (&tuning_lqr_M)->Timing.clockTickH1++;
      }
    }

    rate_scheduler((&tuning_lqr_M));
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void tuning_lqrModelClass::tuning_lqr_derivatives()
{
  XDot_tuning_lqr_T *_rtXdot;
  _rtXdot = ((XDot_tuning_lqr_T *) (&tuning_lqr_M)->derivs);

  /* Derivatives for Integrator: '<S9>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = tuning_lqr_B.z_e;

  /* Derivatives for Integrator: '<S6>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_h = tuning_lqr_B.x_e;

  /* Derivatives for Integrator: '<S7>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_g = tuning_lqr_B.y_e;

  /* Derivatives for Integrator: '<S8>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_j = tuning_lqr_B.yaw_e;
}

/* Model initialize function */
void tuning_lqrModelClass::initialize()
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)(&tuning_lqr_M), 0,
                sizeof(RT_MODEL_tuning_lqr_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&(&tuning_lqr_M)->solverInfo, &(&tuning_lqr_M)
                          ->Timing.simTimeStep);
    rtsiSetTPtr(&(&tuning_lqr_M)->solverInfo, &rtmGetTPtr((&tuning_lqr_M)));
    rtsiSetStepSizePtr(&(&tuning_lqr_M)->solverInfo, &(&tuning_lqr_M)
                       ->Timing.stepSize0);
    rtsiSetdXPtr(&(&tuning_lqr_M)->solverInfo, &(&tuning_lqr_M)->derivs);
    rtsiSetContStatesPtr(&(&tuning_lqr_M)->solverInfo, (real_T **)
                         &(&tuning_lqr_M)->contStates);
    rtsiSetNumContStatesPtr(&(&tuning_lqr_M)->solverInfo, &(&tuning_lqr_M)
      ->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&tuning_lqr_M)->solverInfo,
      &(&tuning_lqr_M)->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&tuning_lqr_M)->solverInfo,
      &(&tuning_lqr_M)->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&tuning_lqr_M)->solverInfo,
      &(&tuning_lqr_M)->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&(&tuning_lqr_M)->solverInfo, (&rtmGetErrorStatus
      ((&tuning_lqr_M))));
    rtsiSetRTModelPtr(&(&tuning_lqr_M)->solverInfo, (&tuning_lqr_M));
  }

  rtsiSetSimTimeStep(&(&tuning_lqr_M)->solverInfo, MAJOR_TIME_STEP);
  (&tuning_lqr_M)->intgData.y = (&tuning_lqr_M)->odeY;
  (&tuning_lqr_M)->intgData.f[0] = (&tuning_lqr_M)->odeF[0];
  (&tuning_lqr_M)->intgData.f[1] = (&tuning_lqr_M)->odeF[1];
  (&tuning_lqr_M)->intgData.f[2] = (&tuning_lqr_M)->odeF[2];
  (&tuning_lqr_M)->intgData.f[3] = (&tuning_lqr_M)->odeF[3];
  getRTM()->contStates = ((X_tuning_lqr_T *) &tuning_lqr_X);
  rtsiSetSolverData(&(&tuning_lqr_M)->solverInfo, (void *)&(&tuning_lqr_M)
                    ->intgData);
  rtsiSetSolverName(&(&tuning_lqr_M)->solverInfo,"ode4");
  rtmSetTPtr(getRTM(), &(&tuning_lqr_M)->Timing.tArray[0]);
  (&tuning_lqr_M)->Timing.stepSize0 = 0.001;

  /* block I/O */
  (void) memset(((void *) &tuning_lqr_B), 0,
                sizeof(B_tuning_lqr_T));

  /* states (continuous) */
  {
    (void) memset((void *)&tuning_lqr_X, 0,
                  sizeof(X_tuning_lqr_T));
  }

  /* external inputs */
  (void)memset((void *)&tuning_lqr_U, 0, sizeof(ExtU_tuning_lqr_T));

  /* external outputs */
  (void) memset((void *)&tuning_lqr_Y, 0,
                sizeof(ExtY_tuning_lqr_T));

  /* InitializeConditions for Integrator: '<S9>/Integrator1' */
  tuning_lqr_X.Integrator1_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S6>/Integrator1' */
  tuning_lqr_X.Integrator1_CSTATE_h = 0.0;

  /* InitializeConditions for Integrator: '<S7>/Integrator1' */
  tuning_lqr_X.Integrator1_CSTATE_g = 0.0;

  /* InitializeConditions for Integrator: '<S8>/Integrator1' */
  tuning_lqr_X.Integrator1_CSTATE_j = 0.0;
}

/* Model terminate function */
void tuning_lqrModelClass::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
tuning_lqrModelClass::tuning_lqrModelClass()
{
}

/* Destructor */
tuning_lqrModelClass::~tuning_lqrModelClass()
{
  /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_tuning_lqr_T * tuning_lqrModelClass::getRTM()
{
  return (&tuning_lqr_M);
}
