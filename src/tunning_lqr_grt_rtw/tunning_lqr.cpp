/*
 * tunning_lqr.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "tunning_lqr".
 *
 * Model version              : 1.942
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Fri Mar 23 14:14:01 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Passed (1), Warnings (3), Error (0)
 */

#include "tunning_lqr.h"
#include "tunning_lqr_private.h"

static void rate_scheduler(RT_MODEL_tunning_lqr_T *const tunning_lqr_M);

/*
 *   This function updates active task flag for each subrate.
 * The function is called at model base rate, hence the
 * generated code self-manages all its subrates.
 */
static void rate_scheduler(RT_MODEL_tunning_lqr_T *const tunning_lqr_M)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (tunning_lqr_M->Timing.TaskCounters.TID[2])++;
  if ((tunning_lqr_M->Timing.TaskCounters.TID[2]) > 4) {/* Sample time: [0.005s, 0.0s] */
    tunning_lqr_M->Timing.TaskCounters.TID[2] = 0;
  }
}

/*
 * This function updates continuous states using the ODE4 fixed-step
 * solver algorithm
 */
void tunning_lqrModelClass::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
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
  tunning_lqr_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  this->step();
  tunning_lqr_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  this->step();
  tunning_lqr_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  this->step();
  tunning_lqr_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void tunning_lqrModelClass::step()
{
  real_T rtb_Sum1_c;
  real_T rtb_Sum1;
  real_T rtb_Saturation2[6];
  int32_T i;
  real_T tmp;
  real_T u0;
  if (rtmIsMajorTimeStep((&tunning_lqr_M))) {
    /* set solver stop time */
    if (!((&tunning_lqr_M)->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&(&tunning_lqr_M)->solverInfo, (((&tunning_lqr_M)
        ->Timing.clockTickH0 + 1) * (&tunning_lqr_M)->Timing.stepSize0 *
        4294967296.0));
    } else {
      rtsiSetSolverStopTime(&(&tunning_lqr_M)->solverInfo, (((&tunning_lqr_M)
        ->Timing.clockTick0 + 1) * (&tunning_lqr_M)->Timing.stepSize0 +
        (&tunning_lqr_M)->Timing.clockTickH0 * (&tunning_lqr_M)
        ->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep((&tunning_lqr_M))) {
    (&tunning_lqr_M)->Timing.t[0] = rtsiGetT(&(&tunning_lqr_M)->solverInfo);
  }

  /* RateTransition: '<Root>/Rate Transition   ' incorporates:
   *  Inport: '<Root>/dX'
   */
  if ((rtmIsMajorTimeStep((&tunning_lqr_M)) &&
       (&tunning_lqr_M)->Timing.TaskCounters.TID[1] == 0) && (rtmIsMajorTimeStep
       ((&tunning_lqr_M)) &&
       (&tunning_lqr_M)->Timing.TaskCounters.TID[2] == 0)) {
    tunning_lqr_B.dz = tunning_lqr_U.dX[2];
    tunning_lqr_B.dzd = tunning_lqr_U.dX[5];
  }

  /* Sum: '<S7>/Sum1' incorporates:
   *  Inport: '<Root>/gain'
   *  Integrator: '<S7>/Integrator1'
   *  Product: '<S7>/Product'
   *  Product: '<S7>/Product1'
   *  SignalConversion: '<S7>/TmpSignal ConversionAtProduct1Inport2'
   */
  tunning_lqr_B.Sum1 = tunning_lqr_U.gain[8] * tunning_lqr_X.Integrator1_CSTATE
    - (tunning_lqr_U.gain[6] * tunning_lqr_B.dz + tunning_lqr_U.gain[7] *
       tunning_lqr_B.dzd);
  if (rtmIsMajorTimeStep((&tunning_lqr_M)) &&
      (&tunning_lqr_M)->Timing.TaskCounters.TID[2] == 0) {
    /* ZeroOrderHold: '<Root>/               ' */
    tunning_lqr_B.T = tunning_lqr_B.Sum1;
  }

  /* RateTransition: '<Root>/Rate Transition   ' incorporates:
   *  Inport: '<Root>/dX'
   */
  if (rtmIsMajorTimeStep((&tunning_lqr_M)) &&
      (&tunning_lqr_M)->Timing.TaskCounters.TID[1] == 0) {
    if (rtmIsMajorTimeStep((&tunning_lqr_M)) &&
        (&tunning_lqr_M)->Timing.TaskCounters.TID[2] == 0) {
      tunning_lqr_B.dx = tunning_lqr_U.dX[0];
      tunning_lqr_B.dxd = tunning_lqr_U.dX[3];
    }

    if (rtmIsMajorTimeStep((&tunning_lqr_M)) &&
        (&tunning_lqr_M)->Timing.TaskCounters.TID[2] == 0) {
      tunning_lqr_B.dy = tunning_lqr_U.dX[1];
      tunning_lqr_B.dyd = tunning_lqr_U.dX[4];
    }
  }

  /* Sum: '<S4>/Sum1' incorporates:
   *  Inport: '<Root>/gain'
   *  Integrator: '<S4>/Integrator1'
   *  Product: '<S4>/Product'
   *  Product: '<S4>/Product1'
   *  SignalConversion: '<S4>/TmpSignal ConversionAtProduct1Inport2'
   */
  rtb_Sum1_c = tunning_lqr_U.gain[2] * tunning_lqr_X.Integrator1_CSTATE_h -
    (tunning_lqr_U.gain[0] * tunning_lqr_B.dx + tunning_lqr_U.gain[1] *
     tunning_lqr_B.dxd);

  /* Sum: '<S5>/Sum1' incorporates:
   *  Inport: '<Root>/gain'
   *  Integrator: '<S5>/Integrator1'
   *  Product: '<S5>/Product'
   *  Product: '<S5>/Product1'
   *  SignalConversion: '<S5>/TmpSignal ConversionAtProduct1Inport2'
   */
  rtb_Sum1 = tunning_lqr_U.gain[5] * tunning_lqr_X.Integrator1_CSTATE_f -
    (tunning_lqr_U.gain[3] * tunning_lqr_B.dy + tunning_lqr_U.gain[4] *
     tunning_lqr_B.dyd);

  /* RateTransition: '<Root>/Rate Transition  ' incorporates:
   *  Inport: '<Root>/yaw'
   */
  if ((rtmIsMajorTimeStep((&tunning_lqr_M)) &&
       (&tunning_lqr_M)->Timing.TaskCounters.TID[1] == 0) && (rtmIsMajorTimeStep
       ((&tunning_lqr_M)) &&
       (&tunning_lqr_M)->Timing.TaskCounters.TID[2] == 0)) {
    tunning_lqr_B.RateTransition = tunning_lqr_U.yaw;
  }

  /* End of RateTransition: '<Root>/Rate Transition  ' */

  /* Fcn: '<Root>/Fcn1' */
  tunning_lqr_B.Fcn1 = rtb_Sum1 * std::cos(tunning_lqr_B.RateTransition) +
    rtb_Sum1_c * std::sin(tunning_lqr_B.RateTransition);

  /* Fcn: '<Root>/Fcn' */
  tunning_lqr_B.Fcn = -rtb_Sum1 * std::sin(tunning_lqr_B.RateTransition) +
    rtb_Sum1_c * std::cos(tunning_lqr_B.RateTransition);

  /* ZeroOrderHold: '<Root>/                        ' incorporates:
   *  ZeroOrderHold: '<Root>/         '
   */
  if (rtmIsMajorTimeStep((&tunning_lqr_M)) &&
      (&tunning_lqr_M)->Timing.TaskCounters.TID[2] == 0) {
    tunning_lqr_B.u = tunning_lqr_B.Fcn1;

    /* Saturate: '<S3>/roll' */
    if (tunning_lqr_B.u > 0.52359877559829882) {
      tunning_lqr_B.roll = 0.52359877559829882;
    } else if (tunning_lqr_B.u < -0.52359877559829882) {
      tunning_lqr_B.roll = -0.52359877559829882;
    } else {
      tunning_lqr_B.roll = tunning_lqr_B.u;
    }

    /* End of Saturate: '<S3>/roll' */
    tunning_lqr_B.u_n = tunning_lqr_B.Fcn;

    /* Saturate: '<S2>/pitch' */
    if (tunning_lqr_B.u_n > 0.52359877559829882) {
      tunning_lqr_B.pitch = 0.52359877559829882;
    } else if (tunning_lqr_B.u_n < -0.52359877559829882) {
      tunning_lqr_B.pitch = -0.52359877559829882;
    } else {
      tunning_lqr_B.pitch = tunning_lqr_B.u_n;
    }

    /* End of Saturate: '<S2>/pitch' */
  }

  /* End of ZeroOrderHold: '<Root>/                        ' */

  /* Sum: '<Root>/Sum2' incorporates:
   *  Inport: '<Root>/dX'
   *  Inport: '<Root>/gain'
   *  Integrator: '<S6>/Integrator1'
   *  Product: '<S2>/Product'
   *  Product: '<S3>/Product'
   *  Product: '<S6>/Product'
   *  Product: '<S6>/Product1'
   *  SignalConversion: '<S2>/TmpSignal ConversionAtProductInport2'
   *  SignalConversion: '<S3>/TmpSignal ConversionAtProductInport2'
   *  SignalConversion: '<S6>/TmpSignal ConversionAtProduct1Inport2'
   *  Sum: '<S2>/Sum1'
   *  Sum: '<S3>/Sum1'
   *  Sum: '<S6>/Sum1'
   */
  rtb_Sum1_c = tunning_lqr_B.roll - (tunning_lqr_U.gain[9] * tunning_lqr_U.dX[6]
    + tunning_lqr_U.gain[10] * tunning_lqr_U.dX[9]);
  rtb_Sum1 = tunning_lqr_B.pitch - (tunning_lqr_U.gain[11] * tunning_lqr_U.dX[7]
    + tunning_lqr_U.gain[12] * tunning_lqr_U.dX[10]);
  tmp = tunning_lqr_U.gain[15] * tunning_lqr_X.Integrator1_CSTATE_n -
    (tunning_lqr_U.gain[13] * tunning_lqr_U.dX[8] + tunning_lqr_U.gain[14] *
     tunning_lqr_U.dX[11]);
  for (i = 0; i < 6; i++) {
    /* Gain: '<Root>/                 ' incorporates:
     *  Saturate: '<Root>/Saturation2'
     *  Sum: '<Root>/Sum2'
     */
    u0 = tunning_lqr_ConstP._Gain[i + 18] * tmp + (tunning_lqr_ConstP._Gain[i +
      12] * rtb_Sum1 + (tunning_lqr_ConstP._Gain[i + 6] * rtb_Sum1_c +
                        (tunning_lqr_B.T + 15.107400000000002) *
                        tunning_lqr_ConstP._Gain[i]));

    /* Saturate: '<Root>/Saturation2' incorporates:
     *  Gain: '<Root>/                 '
     */
    if (u0 > 8.54858) {
      rtb_Saturation2[i] = 8.54858;
    } else if (u0 < 0.0) {
      rtb_Saturation2[i] = 0.0;
    } else {
      rtb_Saturation2[i] = u0;
    }
  }

  /* Gain: '<Root>/mapping_0_200' incorporates:
   *  Gain: '<Root>/      '
   *  Gain: '<Root>/rads_to_RPM'
   *  Inport: '<Root>/LOE'
   *  MATLAB Function: '<Root>/Actuator_Fault'
   *  Sqrt: '<Root>/Sqrt1'
   *  Sum: '<Root>/Sum3'
   */
  /* MATLAB Function 'Actuator_Fault': '<S1>:1' */
  /* '<S1>:1:2' T1 = T(1)*(1-LOE(1)); */
  /* '<S1>:1:3' T2 = T(2)*(1-LOE(2)); */
  /* '<S1>:1:4' T3 = T(3)*(1-LOE(3)); */
  /* '<S1>:1:5' T4 = T(4)*(1-LOE(4)); */
  /* '<S1>:1:6' T5 = T(5)*(1-LOE(5)); */
  /* '<S1>:1:7' T6 = T(6)*(1-LOE(6)); */
  /* '<S1>:1:8' T_f = [T1;T2;T3;T4;T5;T6]; */
  u0 = (std::sqrt((1.0 - tunning_lqr_U.LOE[0]) * rtb_Saturation2[0] *
                  116978.4923343994) * 9.5493 - 1250.0) * 0.022857142857142857;

  /* Saturate: '<Root>/Saturation' */
  if (u0 > 200.0) {
    /* Outport: '<Root>/motor_command' */
    tunning_lqr_Y.motor_command[0] = 200.0;
  } else if (u0 < 0.0) {
    /* Outport: '<Root>/motor_command' */
    tunning_lqr_Y.motor_command[0] = 0.0;
  } else {
    /* Outport: '<Root>/motor_command' */
    tunning_lqr_Y.motor_command[0] = u0;
  }

  /* Gain: '<Root>/mapping_0_200' incorporates:
   *  Gain: '<Root>/      '
   *  Gain: '<Root>/rads_to_RPM'
   *  Inport: '<Root>/LOE'
   *  MATLAB Function: '<Root>/Actuator_Fault'
   *  Sqrt: '<Root>/Sqrt1'
   *  Sum: '<Root>/Sum3'
   */
  u0 = (std::sqrt((1.0 - tunning_lqr_U.LOE[1]) * rtb_Saturation2[1] *
                  116978.4923343994) * 9.5493 - 1250.0) * 0.022857142857142857;

  /* Saturate: '<Root>/Saturation' */
  if (u0 > 200.0) {
    /* Outport: '<Root>/motor_command' */
    tunning_lqr_Y.motor_command[1] = 200.0;
  } else if (u0 < 0.0) {
    /* Outport: '<Root>/motor_command' */
    tunning_lqr_Y.motor_command[1] = 0.0;
  } else {
    /* Outport: '<Root>/motor_command' */
    tunning_lqr_Y.motor_command[1] = u0;
  }

  /* Gain: '<Root>/mapping_0_200' incorporates:
   *  Gain: '<Root>/      '
   *  Gain: '<Root>/rads_to_RPM'
   *  Inport: '<Root>/LOE'
   *  MATLAB Function: '<Root>/Actuator_Fault'
   *  Sqrt: '<Root>/Sqrt1'
   *  Sum: '<Root>/Sum3'
   */
  u0 = (std::sqrt((1.0 - tunning_lqr_U.LOE[2]) * rtb_Saturation2[2] *
                  116978.4923343994) * 9.5493 - 1250.0) * 0.022857142857142857;

  /* Saturate: '<Root>/Saturation' */
  if (u0 > 200.0) {
    /* Outport: '<Root>/motor_command' */
    tunning_lqr_Y.motor_command[2] = 200.0;
  } else if (u0 < 0.0) {
    /* Outport: '<Root>/motor_command' */
    tunning_lqr_Y.motor_command[2] = 0.0;
  } else {
    /* Outport: '<Root>/motor_command' */
    tunning_lqr_Y.motor_command[2] = u0;
  }

  /* Gain: '<Root>/mapping_0_200' incorporates:
   *  Gain: '<Root>/      '
   *  Gain: '<Root>/rads_to_RPM'
   *  Inport: '<Root>/LOE'
   *  MATLAB Function: '<Root>/Actuator_Fault'
   *  Sqrt: '<Root>/Sqrt1'
   *  Sum: '<Root>/Sum3'
   */
  u0 = (std::sqrt((1.0 - tunning_lqr_U.LOE[3]) * rtb_Saturation2[3] *
                  116978.4923343994) * 9.5493 - 1250.0) * 0.022857142857142857;

  /* Saturate: '<Root>/Saturation' */
  if (u0 > 200.0) {
    /* Outport: '<Root>/motor_command' */
    tunning_lqr_Y.motor_command[3] = 200.0;
  } else if (u0 < 0.0) {
    /* Outport: '<Root>/motor_command' */
    tunning_lqr_Y.motor_command[3] = 0.0;
  } else {
    /* Outport: '<Root>/motor_command' */
    tunning_lqr_Y.motor_command[3] = u0;
  }

  /* Gain: '<Root>/mapping_0_200' incorporates:
   *  Gain: '<Root>/      '
   *  Gain: '<Root>/rads_to_RPM'
   *  Inport: '<Root>/LOE'
   *  MATLAB Function: '<Root>/Actuator_Fault'
   *  Sqrt: '<Root>/Sqrt1'
   *  Sum: '<Root>/Sum3'
   */
  u0 = (std::sqrt((1.0 - tunning_lqr_U.LOE[4]) * rtb_Saturation2[4] *
                  116978.4923343994) * 9.5493 - 1250.0) * 0.022857142857142857;

  /* Saturate: '<Root>/Saturation' */
  if (u0 > 200.0) {
    /* Outport: '<Root>/motor_command' */
    tunning_lqr_Y.motor_command[4] = 200.0;
  } else if (u0 < 0.0) {
    /* Outport: '<Root>/motor_command' */
    tunning_lqr_Y.motor_command[4] = 0.0;
  } else {
    /* Outport: '<Root>/motor_command' */
    tunning_lqr_Y.motor_command[4] = u0;
  }

  /* Gain: '<Root>/mapping_0_200' incorporates:
   *  Gain: '<Root>/      '
   *  Gain: '<Root>/rads_to_RPM'
   *  Inport: '<Root>/LOE'
   *  MATLAB Function: '<Root>/Actuator_Fault'
   *  Sqrt: '<Root>/Sqrt1'
   *  Sum: '<Root>/Sum3'
   */
  u0 = (std::sqrt((1.0 - tunning_lqr_U.LOE[5]) * rtb_Saturation2[5] *
                  116978.4923343994) * 9.5493 - 1250.0) * 0.022857142857142857;

  /* Saturate: '<Root>/Saturation' */
  if (u0 > 200.0) {
    /* Outport: '<Root>/motor_command' */
    tunning_lqr_Y.motor_command[5] = 200.0;
  } else if (u0 < 0.0) {
    /* Outport: '<Root>/motor_command' */
    tunning_lqr_Y.motor_command[5] = 0.0;
  } else {
    /* Outport: '<Root>/motor_command' */
    tunning_lqr_Y.motor_command[5] = u0;
  }

  /* Outport: '<Root>/virtual_control' incorporates:
   *  Sum: '<Root>/Sum2'
   */
  tunning_lqr_Y.virtual_control[0] = tunning_lqr_B.T + 15.107400000000002;
  tunning_lqr_Y.virtual_control[1] = rtb_Sum1_c;
  tunning_lqr_Y.virtual_control[2] = rtb_Sum1;
  tunning_lqr_Y.virtual_control[3] = tmp;

  /* RateTransition: '<Root>/Rate Transition ' incorporates:
   *  Inport: '<Root>/dref'
   */
  if ((rtmIsMajorTimeStep((&tunning_lqr_M)) &&
       (&tunning_lqr_M)->Timing.TaskCounters.TID[1] == 0) && (rtmIsMajorTimeStep
       ((&tunning_lqr_M)) &&
       (&tunning_lqr_M)->Timing.TaskCounters.TID[2] == 0)) {
    tunning_lqr_B.RateTransition_f[0] = tunning_lqr_U.dref[0];
    tunning_lqr_B.RateTransition_f[1] = tunning_lqr_U.dref[1];
    tunning_lqr_B.RateTransition_f[2] = tunning_lqr_U.dref[2];
    tunning_lqr_B.RateTransition_f[3] = tunning_lqr_U.dref[3];
  }

  /* End of RateTransition: '<Root>/Rate Transition ' */
  if (rtmIsMajorTimeStep((&tunning_lqr_M)) &&
      (&tunning_lqr_M)->Timing.TaskCounters.TID[2] == 0) {
    /* Saturate: '<S4>/x' */
    if (tunning_lqr_B.RateTransition_f[0] > 2.0) {
      u0 = 2.0;
    } else if (tunning_lqr_B.RateTransition_f[0] < -2.0) {
      u0 = -2.0;
    } else {
      u0 = tunning_lqr_B.RateTransition_f[0];
    }

    /* End of Saturate: '<S4>/x' */

    /* Sum: '<S4>/Sum3' */
    u0 -= tunning_lqr_B.dx;

    /* Saturate: '<S4>/x_e' */
    if (u0 > 1.0) {
      tunning_lqr_B.x_e = 1.0;
    } else if (u0 < -1.0) {
      tunning_lqr_B.x_e = -1.0;
    } else {
      tunning_lqr_B.x_e = u0;
    }

    /* End of Saturate: '<S4>/x_e' */

    /* Saturate: '<S5>/y' */
    if (tunning_lqr_B.RateTransition_f[1] > 2.0) {
      u0 = 2.0;
    } else if (tunning_lqr_B.RateTransition_f[1] < -2.0) {
      u0 = -2.0;
    } else {
      u0 = tunning_lqr_B.RateTransition_f[1];
    }

    /* End of Saturate: '<S5>/y' */

    /* Sum: '<S5>/Sum3' */
    u0 -= tunning_lqr_B.dy;

    /* Saturate: '<S5>/y_e' */
    if (u0 > 1.0) {
      tunning_lqr_B.y_e = 1.0;
    } else if (u0 < -1.0) {
      tunning_lqr_B.y_e = -1.0;
    } else {
      tunning_lqr_B.y_e = u0;
    }

    /* End of Saturate: '<S5>/y_e' */
  }

  /* Saturate: '<S6>/yaw' incorporates:
   *  Inport: '<Root>/dref'
   */
  if (tunning_lqr_U.dref[3] > 3.1415926535897931) {
    u0 = 3.1415926535897931;
  } else if (tunning_lqr_U.dref[3] < -3.1415926535897931) {
    u0 = -3.1415926535897931;
  } else {
    u0 = tunning_lqr_U.dref[3];
  }

  /* End of Saturate: '<S6>/yaw' */

  /* Sum: '<S6>/Sum3' incorporates:
   *  Inport: '<Root>/dX'
   */
  u0 -= tunning_lqr_U.dX[8];

  /* Saturate: '<S6>/yaw_e' */
  if (u0 > 0.78539816339744828) {
    tunning_lqr_B.yaw_e = 0.78539816339744828;
  } else if (u0 < -0.78539816339744828) {
    tunning_lqr_B.yaw_e = -0.78539816339744828;
  } else {
    tunning_lqr_B.yaw_e = u0;
  }

  /* End of Saturate: '<S6>/yaw_e' */
  if (rtmIsMajorTimeStep((&tunning_lqr_M)) &&
      (&tunning_lqr_M)->Timing.TaskCounters.TID[2] == 0) {
    /* Saturate: '<S7>/z' */
    if (tunning_lqr_B.RateTransition_f[2] > 1.5) {
      u0 = 1.5;
    } else if (tunning_lqr_B.RateTransition_f[2] < 0.0) {
      u0 = 0.0;
    } else {
      u0 = tunning_lqr_B.RateTransition_f[2];
    }

    /* End of Saturate: '<S7>/z' */

    /* Sum: '<S7>/Sum3' */
    u0 -= tunning_lqr_B.dz;

    /* Saturate: '<S7>/z_e' */
    if (u0 > 1.0) {
      tunning_lqr_B.z_e = 1.0;
    } else if (u0 < -1.0) {
      tunning_lqr_B.z_e = -1.0;
    } else {
      tunning_lqr_B.z_e = u0;
    }

    /* End of Saturate: '<S7>/z_e' */
  }

  if (rtmIsMajorTimeStep((&tunning_lqr_M))) {
    rt_ertODEUpdateContinuousStates(&(&tunning_lqr_M)->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++(&tunning_lqr_M)->Timing.clockTick0)) {
      ++(&tunning_lqr_M)->Timing.clockTickH0;
    }

    (&tunning_lqr_M)->Timing.t[0] = rtsiGetSolverStopTime(&(&tunning_lqr_M)
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
      (&tunning_lqr_M)->Timing.clockTick1++;
      if (!(&tunning_lqr_M)->Timing.clockTick1) {
        (&tunning_lqr_M)->Timing.clockTickH1++;
      }
    }

    rate_scheduler((&tunning_lqr_M));
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void tunning_lqrModelClass::tunning_lqr_derivatives()
{
  XDot_tunning_lqr_T *_rtXdot;
  _rtXdot = ((XDot_tunning_lqr_T *) (&tunning_lqr_M)->derivs);

  /* Derivatives for Integrator: '<S7>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = tunning_lqr_B.z_e;

  /* Derivatives for Integrator: '<S4>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_h = tunning_lqr_B.x_e;

  /* Derivatives for Integrator: '<S5>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_f = tunning_lqr_B.y_e;

  /* Derivatives for Integrator: '<S6>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_n = tunning_lqr_B.yaw_e;
}

/* Model initialize function */
void tunning_lqrModelClass::initialize()
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)(&tunning_lqr_M), 0,
                sizeof(RT_MODEL_tunning_lqr_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&(&tunning_lqr_M)->solverInfo, &(&tunning_lqr_M)
                          ->Timing.simTimeStep);
    rtsiSetTPtr(&(&tunning_lqr_M)->solverInfo, &rtmGetTPtr((&tunning_lqr_M)));
    rtsiSetStepSizePtr(&(&tunning_lqr_M)->solverInfo, &(&tunning_lqr_M)
                       ->Timing.stepSize0);
    rtsiSetdXPtr(&(&tunning_lqr_M)->solverInfo, &(&tunning_lqr_M)->derivs);
    rtsiSetContStatesPtr(&(&tunning_lqr_M)->solverInfo, (real_T **)
                         &(&tunning_lqr_M)->contStates);
    rtsiSetNumContStatesPtr(&(&tunning_lqr_M)->solverInfo, &(&tunning_lqr_M)
      ->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&tunning_lqr_M)->solverInfo,
      &(&tunning_lqr_M)->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&tunning_lqr_M)->solverInfo,
      &(&tunning_lqr_M)->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&tunning_lqr_M)->solverInfo,
      &(&tunning_lqr_M)->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&(&tunning_lqr_M)->solverInfo, (&rtmGetErrorStatus
      ((&tunning_lqr_M))));
    rtsiSetRTModelPtr(&(&tunning_lqr_M)->solverInfo, (&tunning_lqr_M));
  }

  rtsiSetSimTimeStep(&(&tunning_lqr_M)->solverInfo, MAJOR_TIME_STEP);
  (&tunning_lqr_M)->intgData.y = (&tunning_lqr_M)->odeY;
  (&tunning_lqr_M)->intgData.f[0] = (&tunning_lqr_M)->odeF[0];
  (&tunning_lqr_M)->intgData.f[1] = (&tunning_lqr_M)->odeF[1];
  (&tunning_lqr_M)->intgData.f[2] = (&tunning_lqr_M)->odeF[2];
  (&tunning_lqr_M)->intgData.f[3] = (&tunning_lqr_M)->odeF[3];
  getRTM()->contStates = ((X_tunning_lqr_T *) &tunning_lqr_X);
  rtsiSetSolverData(&(&tunning_lqr_M)->solverInfo, (void *)&(&tunning_lqr_M)
                    ->intgData);
  rtsiSetSolverName(&(&tunning_lqr_M)->solverInfo,"ode4");
  rtmSetTPtr(getRTM(), &(&tunning_lqr_M)->Timing.tArray[0]);
  (&tunning_lqr_M)->Timing.stepSize0 = 0.001;

  /* block I/O */
  (void) memset(((void *) &tunning_lqr_B), 0,
                sizeof(B_tunning_lqr_T));

  /* states (continuous) */
  {
    (void) memset((void *)&tunning_lqr_X, 0,
                  sizeof(X_tunning_lqr_T));
  }

  /* external inputs */
  (void)memset((void *)&tunning_lqr_U, 0, sizeof(ExtU_tunning_lqr_T));

  /* external outputs */
  (void) memset((void *)&tunning_lqr_Y, 0,
                sizeof(ExtY_tunning_lqr_T));

  /* InitializeConditions for Integrator: '<S7>/Integrator1' */
  tunning_lqr_X.Integrator1_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S4>/Integrator1' */
  tunning_lqr_X.Integrator1_CSTATE_h = 0.0;

  /* InitializeConditions for Integrator: '<S5>/Integrator1' */
  tunning_lqr_X.Integrator1_CSTATE_f = 0.0;

  /* InitializeConditions for Integrator: '<S6>/Integrator1' */
  tunning_lqr_X.Integrator1_CSTATE_n = 0.0;
}

/* Model terminate function */
void tunning_lqrModelClass::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
tunning_lqrModelClass::tunning_lqrModelClass()
{
}

/* Destructor */
tunning_lqrModelClass::~tunning_lqrModelClass()
{
  /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_tunning_lqr_T * tunning_lqrModelClass::getRTM()
{
  return (&tunning_lqr_M);
}
