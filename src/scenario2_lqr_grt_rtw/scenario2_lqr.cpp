/*
 * scenario2_lqr.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "scenario2_lqr".
 *
 * Model version              : 1.746
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Wed Feb 21 09:19:42 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Passed (1), Warnings (3), Error (0)
 */

#include "scenario2_lqr.h"
#include "scenario2_lqr_private.h"

/*
 * This function updates continuous states using the ODE5 fixed-step
 * solver algorithm
 */
void scenario2_lqrModelClass::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
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
  scenario2_lqr_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE5_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[0]);
  rtsiSetdX(si, f1);
  this->step();
  scenario2_lqr_derivatives();

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
  scenario2_lqr_derivatives();

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
  scenario2_lqr_derivatives();

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
  scenario2_lqr_derivatives();

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
  scenario2_lqr_derivatives();

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
void scenario2_lqrModelClass::step()
{
  if (rtmIsMajorTimeStep((&scenario2_lqr_M))) {
    /* set solver stop time */
    if (!((&scenario2_lqr_M)->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&(&scenario2_lqr_M)->solverInfo, (((&scenario2_lqr_M)
        ->Timing.clockTickH0 + 1) * (&scenario2_lqr_M)->Timing.stepSize0 *
        4294967296.0));
    } else {
      rtsiSetSolverStopTime(&(&scenario2_lqr_M)->solverInfo, (((&scenario2_lqr_M)
        ->Timing.clockTick0 + 1) * (&scenario2_lqr_M)->Timing.stepSize0 +
        (&scenario2_lqr_M)->Timing.clockTickH0 * (&scenario2_lqr_M)
        ->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep((&scenario2_lqr_M))) {
    (&scenario2_lqr_M)->Timing.t[0] = rtsiGetT(&(&scenario2_lqr_M)->solverInfo);
  }

  {
    real_T (*lastU)[3];
    static const real_T a[9] = { 1.5503875968992249, 3.1007751937984493,
      1.5503875968992249, -2.6853500892540736, -0.0, 2.6853500892540736,
      -9.1324200913242013, 9.1324200913242013, -9.1324200913242013 };

    real_T rtb_VectorConcatenate[12];
    real_T rtb_ixj;
    real_T rtb_kxi;
    real_T rtb_jxk;
    real_T rtb_T_f[6];
    real_T rtb_Product[3];
    real_T rtb_Sum1[3];
    real_T rtb_Clock;
    int32_T i;
    real_T rtb_ref_idx_1;
    real_T rtb_Product_idx_1;
    real_T rtb_Product_idx_2;

    /* Clock: '<Root>/Clock' */
    rtb_Clock = (&scenario2_lqr_M)->Timing.t[0];

    /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn1' incorporates:
     *  Inport: '<Root>/X0'
     */
    rtb_VectorConcatenate[0] = scenario2_lqr_U.X0[0];
    rtb_VectorConcatenate[1] = scenario2_lqr_U.X0[1];
    rtb_VectorConcatenate[2] = scenario2_lqr_U.X0[2];

    /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn2' */
    for (i = 0; i < 5; i++) {
      rtb_VectorConcatenate[i + 3] = 0.0;
    }

    /* End of SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn2' */

    /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn3' incorporates:
     *  Inport: '<Root>/X0'
     */
    rtb_VectorConcatenate[8] = scenario2_lqr_U.X0[3];

    /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn4' */
    rtb_VectorConcatenate[9] = 0.0;
    rtb_VectorConcatenate[10] = 0.0;
    rtb_VectorConcatenate[11] = 0.0;

    /* Sum: '<Root>/Sum' incorporates:
     *  Inport: '<Root>/X'
     */
    for (i = 0; i < 12; i++) {
      rtb_VectorConcatenate[i] = scenario2_lqr_U.X[i] - rtb_VectorConcatenate[i];
    }

    /* End of Sum: '<Root>/Sum' */

    /* Sum: '<S7>/Sum1' incorporates:
     *  Gain: '<S7>/ '
     *  Gain: '<S7>/                    '
     *  Integrator: '<S7>/Integrator1'
     *  SignalConversion: '<S7>/TmpSignal ConversionAt                    Inport1'
     */
    rtb_ixj = 0.17320508075688992 * scenario2_lqr_X.Integrator1_CSTATE_h -
      (0.32349951352987977 * rtb_VectorConcatenate[0] + 0.2732366014912751 *
       rtb_VectorConcatenate[3]);

    /* Sum: '<S8>/Sum1' incorporates:
     *  Gain: '<S8>/  '
     *  Gain: '<S8>/                     '
     *  Integrator: '<S8>/Integrator1'
     *  SignalConversion: '<S8>/TmpSignal ConversionAt                     Inport1'
     */
    rtb_kxi = -0.173205080756885 * scenario2_lqr_X.Integrator1_CSTATE_j -
      (-0.31312578517366968 * rtb_VectorConcatenate[1] + -0.25417198201077484 *
       rtb_VectorConcatenate[4]);

    /* Fcn: '<Root>/Fcn1' incorporates:
     *  Inport: '<Root>/X'
     */
    rtb_jxk = rtb_kxi * std::cos(scenario2_lqr_U.X[8]) + rtb_ixj * std::sin
      (scenario2_lqr_U.X[8]);

    /* Saturate: '<S4>/roll' */
    if (rtb_jxk > 0.52359877559829882) {
      rtb_jxk = 0.52359877559829882;
    } else {
      if (rtb_jxk < -0.52359877559829882) {
        rtb_jxk = -0.52359877559829882;
      }
    }

    /* End of Saturate: '<S4>/roll' */

    /* Sum: '<S4>/Sum1' incorporates:
     *  Gain: '<S4>/                    '
     *  SignalConversion: '<S4>/TmpSignal ConversionAt                    Inport1'
     */
    rtb_jxk -= 1.1365283480217869 * rtb_VectorConcatenate[6] +
      0.28178545108770103 * rtb_VectorConcatenate[9];

    /* Fcn: '<Root>/Fcn' incorporates:
     *  Inport: '<Root>/X'
     */
    rtb_ixj = -rtb_kxi * std::sin(scenario2_lqr_U.X[8]) + rtb_ixj * std::cos
      (scenario2_lqr_U.X[8]);

    /* Sum: '<Root>/Sum2' incorporates:
     *  Gain: '<S9>/  '
     *  Gain: '<S9>/                     '
     *  Integrator: '<S9>/Integrator1'
     *  SignalConversion: '<S9>/TmpSignal ConversionAt                     Inport1'
     *  Sum: '<S9>/Sum1'
     */
    rtb_ref_idx_1 = 10.000000000000018 * scenario2_lqr_X.Integrator1_CSTATE -
      (12.219481695651957 * rtb_VectorConcatenate[2] + 6.215786645518647 *
       rtb_VectorConcatenate[5]);

    /* Sum: '<S6>/Sum1' incorporates:
     *  Saturate: '<S6>/pitch'
     */
    if (rtb_ixj > 0.52359877559829882) {
      rtb_ixj = 0.52359877559829882;
    } else {
      if (rtb_ixj < -0.52359877559829882) {
        rtb_ixj = -0.52359877559829882;
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
    rtb_ixj -= 1.2859205994736729 * rtb_VectorConcatenate[7] +
      0.34413551249350854 * rtb_VectorConcatenate[10];
    rtb_kxi = 0.15811388300841925 * scenario2_lqr_X.Integrator1_CSTATE_b -
      (0.3035552054947866 * rtb_VectorConcatenate[8] + 0.24395632222527311 *
       rtb_VectorConcatenate[11]);

    /* MATLAB Function 'Actuator_Fault': '<S1>:1' */
    /* '<S1>:1:2' T_f = T; */
    for (i = 0; i < 6; i++) {
      /* Gain: '<Root>/                 ' incorporates:
       *  Sum: '<Root>/Sum2'
       */
      scenario2_lqr_B.u[i] = 0.0;
      scenario2_lqr_B.u[i] += (rtb_ref_idx_1 + 15.107400000000002) *
        scenario2_lqr_ConstP._Gain_m[i];
      scenario2_lqr_B.u[i] += scenario2_lqr_ConstP._Gain_m[i + 6] * rtb_jxk;
      scenario2_lqr_B.u[i] += scenario2_lqr_ConstP._Gain_m[i + 12] * rtb_ixj;
      scenario2_lqr_B.u[i] += scenario2_lqr_ConstP._Gain_m[i + 18] * rtb_kxi;

      /* MATLAB Function: '<Root>/Actuator_Fault' */
      rtb_T_f[i] = scenario2_lqr_B.u[i];
    }

    /* MATLAB Function: '<Root>/Actuator_Fault' */
    /* '<S1>:1:3' if time >= 30 */
    if (rtb_Clock >= 30.0) {
      /* '<S1>:1:4' T1 = T(1)*0.65; */
      /* '<S1>:1:5' T2 = T(2)*1; */
      /* '<S1>:1:6' T3 = T(3)*1; */
      /* '<S1>:1:7' T4 = T(4)*1; */
      /* '<S1>:1:8' T5 = T(5)*1; */
      /* '<S1>:1:9' T6 = T(6)*1; */
      /* '<S1>:1:10' T_f = [T1;T2;T3;T4;T5;T6]; */
      rtb_T_f[0] = scenario2_lqr_B.u[0] * 0.65;
      rtb_T_f[1] = scenario2_lqr_B.u[1];
      rtb_T_f[2] = scenario2_lqr_B.u[2];
      rtb_T_f[3] = scenario2_lqr_B.u[3];
      rtb_T_f[4] = scenario2_lqr_B.u[4];
      rtb_T_f[5] = scenario2_lqr_B.u[5];
    }

    /* Outport: '<Root>/virtual_control' incorporates:
     *  Sum: '<Root>/Sum2'
     */
    scenario2_lqr_Y.virtual_control[0] = rtb_ref_idx_1 + 15.107400000000002;
    scenario2_lqr_Y.virtual_control[1] = rtb_jxk;
    scenario2_lqr_Y.virtual_control[2] = rtb_ixj;
    scenario2_lqr_Y.virtual_control[3] = rtb_kxi;
    for (i = 0; i < 6; i++) {
      /* Sqrt: '<Root>/Sqrt1' incorporates:
       *  Gain: '<Root>/      '
       */
      rtb_ref_idx_1 = std::sqrt(116978.4923343994 * rtb_T_f[i]);

      /* Gain: '<Root>/rads_to_RPM' */
      rtb_ixj = 9.5493 * rtb_ref_idx_1;

      /* Gain: '<Root>/mapping_0_200' incorporates:
       *  Constant: '<Root>/Constant '
       *  Sum: '<Root>/Sum3'
       */
      rtb_jxk = (rtb_ixj - 1250.0) * 0.022857142857142857;

      /* Saturate: '<Root>/Saturation' */
      if (rtb_jxk > 200.0) {
        /* Outport: '<Root>/motor_command' */
        scenario2_lqr_Y.motor_command[i] = 200.0;
      } else if (rtb_jxk < 0.0) {
        /* Outport: '<Root>/motor_command' */
        scenario2_lqr_Y.motor_command[i] = 0.0;
      } else {
        /* Outport: '<Root>/motor_command' */
        scenario2_lqr_Y.motor_command[i] = rtb_jxk;
      }

      /* End of Saturate: '<Root>/Saturation' */

      /* Outport: '<Root>/motor_speed' */
      scenario2_lqr_Y.motor_speed[i] = rtb_ref_idx_1;

      /* Outport: '<Root>/motor_RPM' */
      scenario2_lqr_Y.motor_RPM[i] = rtb_ixj;
    }

    /* MATLAB Function: '<Root>/MATLAB Function' incorporates:
     *  Inport: '<Root>/X0'
     */
    /* MATLAB Function 'MATLAB Function': '<S3>:1' */
    /* '<S3>:1:2' x = X0(1); */
    /* '<S3>:1:2' y = X0(2); */
    /* '<S3>:1:2' z = X0(3); */
    /* '<S3>:1:2' psi = X0(4); */
    /* '<S3>:1:3' if t <= 10 */
    if (rtb_Clock <= 10.0) {
      /* '<S3>:1:4' x = X0(1); */
      rtb_ixj = scenario2_lqr_U.X0[0];

      /* '<S3>:1:5' y = X0(2); */
      rtb_Clock = scenario2_lqr_U.X0[1];

      /* '<S3>:1:6' z = 0.75; */
      rtb_kxi = 0.75;

      /* '<S3>:1:7' psi = X0(4); */
      rtb_jxk = scenario2_lqr_U.X0[3];
    } else if (rtb_Clock <= 60.0) {
      /* '<S3>:1:8' elseif t <=60 */
      /* '<S3>:1:9' x = cos(0.4*(t)); */
      rtb_ixj = std::cos(0.4 * rtb_Clock);

      /* '<S3>:1:10' y = sin(0.4*(t)); */
      rtb_Clock = std::sin(0.4 * rtb_Clock);

      /* '<S3>:1:11' z = 0.75; */
      rtb_kxi = 0.75;

      /* '<S3>:1:12' psi = X0(4); */
      rtb_jxk = scenario2_lqr_U.X0[3];
    } else if (rtb_Clock <= 70.0) {
      /* '<S3>:1:13' elseif t <=70 */
      /* '<S3>:1:14' x = X0(1); */
      rtb_ixj = scenario2_lqr_U.X0[0];

      /* '<S3>:1:15' y = X0(2); */
      rtb_Clock = scenario2_lqr_U.X0[1];

      /* '<S3>:1:16' z = 0.75; */
      rtb_kxi = 0.75;

      /* '<S3>:1:17' psi = X0(4); */
      rtb_jxk = scenario2_lqr_U.X0[3];
    } else {
      /* '<S3>:1:18' else */
      /* '<S3>:1:19' x = X0(1); */
      rtb_ixj = scenario2_lqr_U.X0[0];

      /* '<S3>:1:20' y = X0(2); */
      rtb_Clock = scenario2_lqr_U.X0[1];

      /* '<S3>:1:21' z = 0; */
      rtb_kxi = 0.0;

      /* '<S3>:1:22' psi = X0(4); */
      rtb_jxk = scenario2_lqr_U.X0[3];
    }

    /* '<S3>:1:24' ref = [x;y;z;psi]; */
    rtb_ref_idx_1 = rtb_Clock;

    /* Outport: '<Root>/ref' incorporates:
     *  MATLAB Function: '<Root>/MATLAB Function'
     */
    scenario2_lqr_Y.ref[0] = rtb_ixj;
    scenario2_lqr_Y.ref[1] = rtb_Clock;
    scenario2_lqr_Y.ref[2] = rtb_kxi;
    scenario2_lqr_Y.ref[3] = rtb_jxk;
    if (rtmIsMajorTimeStep((&scenario2_lqr_M))) {
      /* Memory: '<S2>/Memory' */
      for (i = 0; i < 6; i++) {
        scenario2_lqr_B.Memory[i] = scenario2_lqr_DW.Memory_PreviousInput[i];
      }

      /* End of Memory: '<S2>/Memory' */
    }

    /* Derivative: '<S2>/Derivative' incorporates:
     *  Inport: '<Root>/X'
     */
    if ((scenario2_lqr_DW.TimeStampA >= (&scenario2_lqr_M)->Timing.t[0]) &&
        (scenario2_lqr_DW.TimeStampB >= (&scenario2_lqr_M)->Timing.t[0])) {
      rtb_Sum1[0] = 0.0;
      rtb_Sum1[1] = 0.0;
      rtb_Sum1[2] = 0.0;
    } else {
      rtb_Clock = scenario2_lqr_DW.TimeStampA;
      lastU = (real_T (*)[3])scenario2_lqr_DW.LastUAtTimeA;
      if (scenario2_lqr_DW.TimeStampA < scenario2_lqr_DW.TimeStampB) {
        if (scenario2_lqr_DW.TimeStampB < (&scenario2_lqr_M)->Timing.t[0]) {
          rtb_Clock = scenario2_lqr_DW.TimeStampB;
          lastU = (real_T (*)[3])scenario2_lqr_DW.LastUAtTimeB;
        }
      } else {
        if (scenario2_lqr_DW.TimeStampA >= (&scenario2_lqr_M)->Timing.t[0]) {
          rtb_Clock = scenario2_lqr_DW.TimeStampB;
          lastU = (real_T (*)[3])scenario2_lqr_DW.LastUAtTimeB;
        }
      }

      rtb_Clock = (&scenario2_lqr_M)->Timing.t[0] - rtb_Clock;
      rtb_Sum1[0] = (scenario2_lqr_U.X[9] - (*lastU)[0]) / rtb_Clock;
      rtb_Sum1[1] = (scenario2_lqr_U.X[10] - (*lastU)[1]) / rtb_Clock;
      rtb_Sum1[2] = (scenario2_lqr_U.X[11] - (*lastU)[2]) / rtb_Clock;
    }

    /* End of Derivative: '<S2>/Derivative' */

    /* Product: '<S2>/Product' incorporates:
     *  Constant: '<S2>/Constant1'
     */
    for (i = 0; i < 3; i++) {
      rtb_Product[i] = scenario2_lqr_ConstP.Constant1_Value[i + 6] * rtb_Sum1[2]
        + (scenario2_lqr_ConstP.Constant1_Value[i + 3] * rtb_Sum1[1] +
           scenario2_lqr_ConstP.Constant1_Value[i] * rtb_Sum1[0]);
    }

    /* End of Product: '<S2>/Product' */

    /* Product: '<S2>/Product1' incorporates:
     *  Constant: '<S2>/Constant1'
     *  Inport: '<Root>/X'
     */
    for (i = 0; i < 3; i++) {
      rtb_Sum1[i] = scenario2_lqr_ConstP.Constant1_Value[i + 6] *
        scenario2_lqr_U.X[11] + (scenario2_lqr_ConstP.Constant1_Value[i + 3] *
        scenario2_lqr_U.X[10] + scenario2_lqr_ConstP.Constant1_Value[i] *
        scenario2_lqr_U.X[9]);
    }

    /* End of Product: '<S2>/Product1' */

    /* Sum: '<S2>/Sum3' incorporates:
     *  Inport: '<Root>/X'
     *  MATLAB Function: '<S2>/MATLAB Function1'
     *  Product: '<S12>/i x k'
     *  Product: '<S12>/j x i'
     *  Product: '<S12>/k x j'
     *  Product: '<S13>/i x j'
     *  Product: '<S13>/j x k'
     *  Product: '<S13>/k x i'
     *  Sum: '<S10>/Sum1'
     */
    /* MATLAB Function 'FDD  /MATLAB Function1': '<S11>:1' */
    /* '<S11>:1:2' arm = 0.215; */
    /* '<S11>:1:2' gra = 9.81; */
    /* '<S11>:1:2' factor = 0.0365; */
    /* '<S11>:1:4' M = [arm/2 arm arm/2; */
    /* '<S11>:1:5'       -sqrt(3)*arm/2 0 sqrt(3)*arm/2; */
    /* '<S11>:1:6'       -factor factor -factor]; */
    /* '<S11>:1:8' diff = [u(1) - u(4) ; */
    /* '<S11>:1:9'         u(2) - u(5) ; */
    /* '<S11>:1:10'         u(3) - u(6) ]; */
    /* '<S11>:1:11' Residu_1_4 = diff - inv(M)*y; */
    rtb_Clock = (scenario2_lqr_U.X[10] * rtb_Sum1[2] - scenario2_lqr_U.X[11] *
                 rtb_Sum1[1]) + rtb_Product[0];
    rtb_Product_idx_1 = (scenario2_lqr_U.X[11] * rtb_Sum1[0] -
                         scenario2_lqr_U.X[9] * rtb_Sum1[2]) + rtb_Product[1];
    rtb_Product_idx_2 = (scenario2_lqr_U.X[9] * rtb_Sum1[1] - scenario2_lqr_U.X
                         [10] * rtb_Sum1[0]) + rtb_Product[2];

    /* MATLAB Function: '<S2>/MATLAB Function1' */
    rtb_Sum1[0] = scenario2_lqr_B.Memory[0] - scenario2_lqr_B.Memory[3];
    rtb_Sum1[1] = scenario2_lqr_B.Memory[1] - scenario2_lqr_B.Memory[4];
    rtb_Sum1[2] = scenario2_lqr_B.Memory[2] - scenario2_lqr_B.Memory[5];
    for (i = 0; i < 3; i++) {
      rtb_Product[i] = rtb_Sum1[i] - (a[i + 6] * rtb_Product_idx_2 + (a[i + 3] *
        rtb_Product_idx_1 + a[i] * rtb_Clock));
    }

    /* Outport: '<Root>/gamma' incorporates:
     *  MATLAB Function: '<S2>/MATLAB Function1'
     */
    /*  Residu_1_4 */
    /* '<S11>:1:14' gamma    = [1-(-Residu_1_4(1) + u(1))/u(1) */
    /* '<S11>:1:15'             1-(-Residu_1_4(2) + u(2))/u(2) */
    /* '<S11>:1:16'             1-(-Residu_1_4(3) + u(3))/u(3)]; */
    scenario2_lqr_Y.gamma[0] = 1.0 - (-rtb_Product[0] + scenario2_lqr_B.Memory[0])
      / scenario2_lqr_B.Memory[0];
    scenario2_lqr_Y.gamma[1] = 1.0 - (-rtb_Product[1] + scenario2_lqr_B.Memory[1])
      / scenario2_lqr_B.Memory[1];
    scenario2_lqr_Y.gamma[2] = 1.0 - (-rtb_Product[2] + scenario2_lqr_B.Memory[2])
      / scenario2_lqr_B.Memory[2];

    /* Sum: '<Root>/Sum1' incorporates:
     *  Inport: '<Root>/X0'
     *  MATLAB Function: '<Root>/MATLAB Function'
     */
    rtb_Clock = rtb_ixj - scenario2_lqr_U.X0[0];
    rtb_ref_idx_1 -= scenario2_lqr_U.X0[1];
    rtb_ixj = rtb_kxi - scenario2_lqr_U.X0[2];
    rtb_jxk -= scenario2_lqr_U.X0[3];

    /* Saturate: '<S5>/yaw' */
    if (rtb_jxk > 3.1415926535897931) {
      rtb_jxk = 3.1415926535897931;
    } else {
      if (rtb_jxk < -3.1415926535897931) {
        rtb_jxk = -3.1415926535897931;
      }
    }

    /* End of Saturate: '<S5>/yaw' */

    /* Sum: '<S5>/Sum3' */
    rtb_jxk -= rtb_VectorConcatenate[8];

    /* Saturate: '<S5>/psi_e' */
    if (rtb_jxk > 0.78539816339744828) {
      scenario2_lqr_B.psi_e = 0.78539816339744828;
    } else if (rtb_jxk < -0.78539816339744828) {
      scenario2_lqr_B.psi_e = -0.78539816339744828;
    } else {
      scenario2_lqr_B.psi_e = rtb_jxk;
    }

    /* End of Saturate: '<S5>/psi_e' */

    /* Saturate: '<S7>/x' */
    if (rtb_Clock > 1.0) {
      rtb_Clock = 1.0;
    } else {
      if (rtb_Clock < -1.0) {
        rtb_Clock = -1.0;
      }
    }

    /* End of Saturate: '<S7>/x' */

    /* Sum: '<S7>/Sum3' */
    rtb_jxk = rtb_Clock - rtb_VectorConcatenate[0];

    /* Saturate: '<S7>/xe' */
    if (rtb_jxk > 1.0) {
      scenario2_lqr_B.xe = 1.0;
    } else if (rtb_jxk < -1.0) {
      scenario2_lqr_B.xe = -1.0;
    } else {
      scenario2_lqr_B.xe = rtb_jxk;
    }

    /* End of Saturate: '<S7>/xe' */

    /* Saturate: '<S8>/y' */
    if (rtb_ref_idx_1 > 1.0) {
      rtb_ref_idx_1 = 1.0;
    } else {
      if (rtb_ref_idx_1 < -1.0) {
        rtb_ref_idx_1 = -1.0;
      }
    }

    /* End of Saturate: '<S8>/y' */

    /* Sum: '<S8>/Sum3' */
    rtb_jxk = rtb_ref_idx_1 - rtb_VectorConcatenate[1];

    /* Saturate: '<S8>/ye' */
    if (rtb_jxk > 1.0) {
      scenario2_lqr_B.ye = 1.0;
    } else if (rtb_jxk < -1.0) {
      scenario2_lqr_B.ye = -1.0;
    } else {
      scenario2_lqr_B.ye = rtb_jxk;
    }

    /* End of Saturate: '<S8>/ye' */

    /* Saturate: '<S9>/z' */
    if (rtb_ixj > 1.0) {
      rtb_ixj = 1.0;
    } else {
      if (rtb_ixj < 0.0) {
        rtb_ixj = 0.0;
      }
    }

    /* End of Saturate: '<S9>/z' */

    /* Sum: '<S9>/Sum3' */
    rtb_jxk = rtb_ixj - rtb_VectorConcatenate[2];

    /* Saturate: '<S9>/ze' */
    if (rtb_jxk > 0.5) {
      scenario2_lqr_B.ze = 0.5;
    } else if (rtb_jxk < -0.5) {
      scenario2_lqr_B.ze = -0.5;
    } else {
      scenario2_lqr_B.ze = rtb_jxk;
    }

    /* End of Saturate: '<S9>/ze' */
  }

  if (rtmIsMajorTimeStep((&scenario2_lqr_M))) {
    real_T (*lastU)[3];
    int32_T i;
    if (rtmIsMajorTimeStep((&scenario2_lqr_M))) {
      /* Update for Memory: '<S2>/Memory' */
      for (i = 0; i < 6; i++) {
        scenario2_lqr_DW.Memory_PreviousInput[i] = scenario2_lqr_B.u[i];
      }

      /* End of Update for Memory: '<S2>/Memory' */
    }

    /* Update for Derivative: '<S2>/Derivative' incorporates:
     *  Update for Inport: '<Root>/X'
     */
    if (scenario2_lqr_DW.TimeStampA == (rtInf)) {
      scenario2_lqr_DW.TimeStampA = (&scenario2_lqr_M)->Timing.t[0];
      lastU = (real_T (*)[3])scenario2_lqr_DW.LastUAtTimeA;
    } else if (scenario2_lqr_DW.TimeStampB == (rtInf)) {
      scenario2_lqr_DW.TimeStampB = (&scenario2_lqr_M)->Timing.t[0];
      lastU = (real_T (*)[3])scenario2_lqr_DW.LastUAtTimeB;
    } else if (scenario2_lqr_DW.TimeStampA < scenario2_lqr_DW.TimeStampB) {
      scenario2_lqr_DW.TimeStampA = (&scenario2_lqr_M)->Timing.t[0];
      lastU = (real_T (*)[3])scenario2_lqr_DW.LastUAtTimeA;
    } else {
      scenario2_lqr_DW.TimeStampB = (&scenario2_lqr_M)->Timing.t[0];
      lastU = (real_T (*)[3])scenario2_lqr_DW.LastUAtTimeB;
    }

    (*lastU)[0] = scenario2_lqr_U.X[9];
    (*lastU)[1] = scenario2_lqr_U.X[10];
    (*lastU)[2] = scenario2_lqr_U.X[11];

    /* End of Update for Derivative: '<S2>/Derivative' */
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep((&scenario2_lqr_M))) {
    rt_ertODEUpdateContinuousStates(&(&scenario2_lqr_M)->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++(&scenario2_lqr_M)->Timing.clockTick0)) {
      ++(&scenario2_lqr_M)->Timing.clockTickH0;
    }

    (&scenario2_lqr_M)->Timing.t[0] = rtsiGetSolverStopTime(&(&scenario2_lqr_M
      )->solverInfo);

    {
      /* Update absolute timer for sample time: [0.005s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.005, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      (&scenario2_lqr_M)->Timing.clockTick1++;
      if (!(&scenario2_lqr_M)->Timing.clockTick1) {
        (&scenario2_lqr_M)->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void scenario2_lqrModelClass::scenario2_lqr_derivatives()
{
  XDot_scenario2_lqr_T *_rtXdot;
  _rtXdot = ((XDot_scenario2_lqr_T *) (&scenario2_lqr_M)->derivs);

  /* Derivatives for Integrator: '<S9>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = scenario2_lqr_B.ze;

  /* Derivatives for Integrator: '<S7>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_h = scenario2_lqr_B.xe;

  /* Derivatives for Integrator: '<S8>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_j = scenario2_lqr_B.ye;

  /* Derivatives for Integrator: '<S5>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_b = scenario2_lqr_B.psi_e;
}

/* Model initialize function */
void scenario2_lqrModelClass::initialize()
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)(&scenario2_lqr_M), 0,
                sizeof(RT_MODEL_scenario2_lqr_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&(&scenario2_lqr_M)->solverInfo, &(&scenario2_lqr_M)
                          ->Timing.simTimeStep);
    rtsiSetTPtr(&(&scenario2_lqr_M)->solverInfo, &rtmGetTPtr((&scenario2_lqr_M)));
    rtsiSetStepSizePtr(&(&scenario2_lqr_M)->solverInfo, &(&scenario2_lqr_M)
                       ->Timing.stepSize0);
    rtsiSetdXPtr(&(&scenario2_lqr_M)->solverInfo, &(&scenario2_lqr_M)->derivs);
    rtsiSetContStatesPtr(&(&scenario2_lqr_M)->solverInfo, (real_T **)
                         &(&scenario2_lqr_M)->contStates);
    rtsiSetNumContStatesPtr(&(&scenario2_lqr_M)->solverInfo, &(&scenario2_lqr_M
      )->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&scenario2_lqr_M)->solverInfo,
      &(&scenario2_lqr_M)->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&scenario2_lqr_M)->solverInfo,
      &(&scenario2_lqr_M)->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&scenario2_lqr_M)->solverInfo,
      &(&scenario2_lqr_M)->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&(&scenario2_lqr_M)->solverInfo, (&rtmGetErrorStatus((
      &scenario2_lqr_M))));
    rtsiSetRTModelPtr(&(&scenario2_lqr_M)->solverInfo, (&scenario2_lqr_M));
  }

  rtsiSetSimTimeStep(&(&scenario2_lqr_M)->solverInfo, MAJOR_TIME_STEP);
  (&scenario2_lqr_M)->intgData.y = (&scenario2_lqr_M)->odeY;
  (&scenario2_lqr_M)->intgData.f[0] = (&scenario2_lqr_M)->odeF[0];
  (&scenario2_lqr_M)->intgData.f[1] = (&scenario2_lqr_M)->odeF[1];
  (&scenario2_lqr_M)->intgData.f[2] = (&scenario2_lqr_M)->odeF[2];
  (&scenario2_lqr_M)->intgData.f[3] = (&scenario2_lqr_M)->odeF[3];
  (&scenario2_lqr_M)->intgData.f[4] = (&scenario2_lqr_M)->odeF[4];
  (&scenario2_lqr_M)->intgData.f[5] = (&scenario2_lqr_M)->odeF[5];
  getRTM()->contStates = ((X_scenario2_lqr_T *) &scenario2_lqr_X);
  rtsiSetSolverData(&(&scenario2_lqr_M)->solverInfo, (void *)&(&scenario2_lqr_M
                    )->intgData);
  rtsiSetSolverName(&(&scenario2_lqr_M)->solverInfo,"ode5");
  rtmSetTPtr(getRTM(), &(&scenario2_lqr_M)->Timing.tArray[0]);
  (&scenario2_lqr_M)->Timing.stepSize0 = 0.005;

  /* block I/O */
  (void) memset(((void *) &scenario2_lqr_B), 0,
                sizeof(B_scenario2_lqr_T));

  /* states (continuous) */
  {
    (void) memset((void *)&scenario2_lqr_X, 0,
                  sizeof(X_scenario2_lqr_T));
  }

  /* states (dwork) */
  (void) memset((void *)&scenario2_lqr_DW, 0,
                sizeof(DW_scenario2_lqr_T));

  /* external inputs */
  (void)memset((void *)&scenario2_lqr_U, 0, sizeof(ExtU_scenario2_lqr_T));

  /* external outputs */
  (void) memset((void *)&scenario2_lqr_Y, 0,
                sizeof(ExtY_scenario2_lqr_T));

  {
    int32_T i;

    /* InitializeConditions for Integrator: '<S9>/Integrator1' */
    scenario2_lqr_X.Integrator1_CSTATE = 0.0;

    /* InitializeConditions for Integrator: '<S7>/Integrator1' */
    scenario2_lqr_X.Integrator1_CSTATE_h = 0.0;

    /* InitializeConditions for Integrator: '<S8>/Integrator1' */
    scenario2_lqr_X.Integrator1_CSTATE_j = 0.0;

    /* InitializeConditions for Integrator: '<S5>/Integrator1' */
    scenario2_lqr_X.Integrator1_CSTATE_b = 0.0;

    /* InitializeConditions for Memory: '<S2>/Memory' */
    for (i = 0; i < 6; i++) {
      scenario2_lqr_DW.Memory_PreviousInput[i] = 2.5179000000000005;
    }

    /* End of InitializeConditions for Memory: '<S2>/Memory' */

    /* InitializeConditions for Derivative: '<S2>/Derivative' */
    scenario2_lqr_DW.TimeStampA = (rtInf);
    scenario2_lqr_DW.TimeStampB = (rtInf);
  }
}

/* Model terminate function */
void scenario2_lqrModelClass::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
scenario2_lqrModelClass::scenario2_lqrModelClass()
{
}

/* Destructor */
scenario2_lqrModelClass::~scenario2_lqrModelClass()
{
  /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_scenario2_lqr_T * scenario2_lqrModelClass::getRTM()
{
  return (&scenario2_lqr_M);
}
