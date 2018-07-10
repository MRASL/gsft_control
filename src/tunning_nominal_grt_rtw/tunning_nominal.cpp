/*
 * tunning_nominal.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "tunning_nominal".
 *
 * Model version              : 1.1301
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Tue Jul 10 10:02:46 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Passed (1), Warnings (3), Error (0)
 */

#include "tunning_nominal.h"
#include "tunning_nominal_private.h"

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

  {
    real_T (*lastU)[3];
    static const real_T a[9] = { 1.5503875968992249, 3.1007751937984493,
      1.5503875968992249, -2.6853500892540736, -0.0, 2.6853500892540736,
      -9.1324200913242013, 9.1324200913242013, -9.1324200913242013 };

    real_T rtb_d_z;
    real_T rtb_d_x;
    real_T rtb_d_psi;
    real_T rtb_d_y;
    real_T rtb_uNm_p;
    real_T rtb_LOE_out[6];
    real_T rtb_ZeroOrderHold1[3];
    real_T rtb_Clock;
    int32_T i;
    real_T tmp[3];
    real_T tmp_0[3];
    real_T rtb_ff_idx_0;
    real_T rtb_ff_idx_1;
    real_T rtb_ref_idx_3;
    real_T rtb_Derivative_idx_0;
    real_T rtb_Derivative_idx_1;

    /* Sum: '<S3>/Sum5' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/Y0'
     */
    rtb_d_z = tunning_nominal_U.X[2] - tunning_nominal_U.Y0[2];

    /* Sum: '<S3>/Sum1' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/Y0'
     */
    rtb_d_x = tunning_nominal_U.X[0] - tunning_nominal_U.Y0[0];

    /* Sum: '<S5>/Sum2' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/gain'
     *  Integrator: '<S5>/Integrator1'
     *  Product: '<S5>/Product2'
     *  Product: '<S5>/Product3'
     *  SignalConversion: '<S5>/TmpSignal ConversionAtProduct3Inport2'
     */
    rtb_d_psi = tunning_nominal_U.gain[2] *
      tunning_nominal_X.Integrator1_CSTATE_d - (tunning_nominal_U.gain[0] *
      rtb_d_x + tunning_nominal_U.gain[1] * tunning_nominal_U.X[3]);

    /* Sum: '<S3>/Sum4' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/Y0'
     */
    rtb_d_y = tunning_nominal_U.X[1] - tunning_nominal_U.Y0[1];

    /* MATLAB Function: '<S3>/FFW' */
    rtb_ff_idx_0 = 0.0;
    rtb_ff_idx_1 = 0.0;

    /* Sum: '<S5>/Sum3' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/gain'
     *  Integrator: '<S5>/Integrator'
     *  Product: '<S5>/Product1'
     *  Product: '<S5>/Product4'
     *  SignalConversion: '<S5>/TmpSignal ConversionAtProduct1Inport2'
     */
    rtb_uNm_p = tunning_nominal_U.gain[5] * tunning_nominal_X.Integrator_CSTATE
      - (tunning_nominal_U.gain[3] * rtb_d_y + tunning_nominal_U.gain[4] *
         tunning_nominal_U.X[4]);

    /* Clock: '<Root>/Clock' */
    rtb_Clock = (&tunning_nominal_M)->Timing.t[0];

    /* MATLAB Function: '<S3>/FFW' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/mode'
     */
    /* MATLAB Function 'Test_config_and_data/FFW': '<S14>:1' */
    /* '<S14>:1:2' ff = [0;0]; */
    /* '<S14>:1:3' g = 9.81; */
    /*  [x;y] = [cos(t); sin(t)] */
    /* '<S14>:1:5' if (test_mode == 2) */
    if ((tunning_nominal_U.mode == 2.0) && ((rtb_Clock >= 10.0) && (rtb_Clock <=
          50.0))) {
      /* '<S14>:1:6' if (t >=10) && (t<= 50) */
      /* '<S14>:1:7' axref_N = -cos(t); */
      /* '<S14>:1:8' ayref_N = -sin(t); */
      /* '<S14>:1:10' axref_b = cos(X(8))*cos(X(9))*axref_N + cos(X(8))*sin(X(9))*ayref_N; */
      /* '<S14>:1:11' ayref_b = (sin(X(7))*sin(X(8))*cos(X(9)) - cos(X(7))*sin(X(9)))*axref_N + (sin(X(7))*sin(X(8))*sin(X(9)) + cos(X(7))*cos(X(9)))*ayref_N; */
      /*   */
      /* '<S14>:1:13' ff = [-ayref_b/g; axref_b/g]; */
      rtb_ff_idx_0 = -((std::sin(tunning_nominal_U.X[6]) * std::sin
                        (tunning_nominal_U.X[7]) * std::cos(tunning_nominal_U.X
        [8]) - std::cos(tunning_nominal_U.X[6]) * std::sin(tunning_nominal_U.X[8]))
                       * -std::cos(rtb_Clock) + (std::sin(tunning_nominal_U.X[6])
        * std::sin(tunning_nominal_U.X[7]) * std::sin(tunning_nominal_U.X[8]) +
        std::cos(tunning_nominal_U.X[6]) * std::cos(tunning_nominal_U.X[8])) *
                       -std::sin(rtb_Clock)) / 9.81;
      rtb_ff_idx_1 = (std::cos(tunning_nominal_U.X[7]) * std::cos
                      (tunning_nominal_U.X[8]) * -std::cos(rtb_Clock) + std::cos
                      (tunning_nominal_U.X[7]) * std::sin(tunning_nominal_U.X[8])
                      * -std::sin(rtb_Clock)) / 9.81;
    } else {
      /* '<S14>:1:14' else */
      /* '<S14>:1:15' ff = [0;0]; */
    }

    /* Sum: '<S7>/Sum1' incorporates:
     *  Fcn: '<Root>/Fcn1'
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/gain'
     *  Product: '<S7>/Product'
     *  SignalConversion: '<S7>/TmpSignal ConversionAtProductInport2'
     *  Sum: '<Root>/Sum7'
     */
    rtb_ff_idx_0 = ((rtb_uNm_p * std::cos(tunning_nominal_U.X[8]) + rtb_d_psi *
                     std::sin(tunning_nominal_U.X[8])) + rtb_ff_idx_0) -
      (tunning_nominal_U.gain[9] * tunning_nominal_U.X[6] +
       tunning_nominal_U.gain[10] * tunning_nominal_U.X[9]);

    /* Saturate: '<Root>/2Nm ' */
    if (rtb_ff_idx_0 > 2.0) {
      rtb_ff_idx_0 = 2.0;
    } else {
      if (rtb_ff_idx_0 < -2.0) {
        rtb_ff_idx_0 = -2.0;
      }
    }

    /* End of Saturate: '<Root>/2Nm ' */

    /* Fcn: '<Root>/Fcn' incorporates:
     *  Inport: '<Root>/X'
     */
    rtb_d_psi = -rtb_uNm_p * std::sin(tunning_nominal_U.X[8]) + rtb_d_psi * std::
      cos(tunning_nominal_U.X[8]);

    /* Sum: '<S6>/Sum1' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/gain'
     *  Product: '<S6>/Product'
     *  SignalConversion: '<S6>/TmpSignal ConversionAtProductInport2'
     *  Sum: '<Root>/Sum8'
     */
    rtb_uNm_p = (rtb_d_psi + rtb_ff_idx_1) - (tunning_nominal_U.gain[12] *
      tunning_nominal_U.X[7] + tunning_nominal_U.gain[13] * tunning_nominal_U.X
      [10]);

    /* Saturate: '<Root>/2Nm' */
    if (rtb_uNm_p > 2.0) {
      rtb_uNm_p = 2.0;
    } else {
      if (rtb_uNm_p < -2.0) {
        rtb_uNm_p = -2.0;
      }
    }

    /* End of Saturate: '<Root>/2Nm' */

    /* Sum: '<S3>/Sum6' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/Y0'
     */
    rtb_d_psi = tunning_nominal_U.X[8] - tunning_nominal_U.Y0[3];

    /* Sum: '<Root>/Sum2' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/gain'
     *  Integrator: '<S9>/Integrator1'
     *  Product: '<S9>/Product'
     *  Product: '<S9>/Product1'
     *  SignalConversion: '<S9>/TmpSignal ConversionAtProduct1Inport2'
     *  Sum: '<S9>/Sum1'
     */
    rtb_ff_idx_1 = tunning_nominal_U.gain[8] *
      tunning_nominal_X.Integrator1_CSTATE - (tunning_nominal_U.gain[6] *
      rtb_d_z + tunning_nominal_U.gain[7] * tunning_nominal_U.X[5]);

    /* Saturate: '<Root>/1Nm' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/gain'
     *  Integrator: '<S8>/Integrator1'
     *  Product: '<S8>/Product'
     *  Product: '<S8>/Product1'
     *  SignalConversion: '<S8>/TmpSignal ConversionAtProduct1Inport2'
     *  Sum: '<S8>/Sum1'
     */
    rtb_ref_idx_3 = tunning_nominal_U.gain[17] *
      tunning_nominal_X.Integrator1_CSTATE_j - (tunning_nominal_U.gain[15] *
      rtb_d_psi + tunning_nominal_U.gain[16] * tunning_nominal_U.X[11]);
    if (rtb_ref_idx_3 > 1.0) {
      /* Sum: '<Root>/Sum2' */
      rtb_ref_idx_3 = 1.0;
    } else {
      if (rtb_ref_idx_3 < -1.0) {
        /* Sum: '<Root>/Sum2' */
        rtb_ref_idx_3 = -1.0;
      }
    }

    /* End of Saturate: '<Root>/1Nm' */
    /* MATLAB Function 'Test_config_and_data/LOE_': '<S15>:1' */
    /* '<S15>:1:2' LOE_out = [0;0;0;0;0;0]; */
    /* '<S15>:1:3' for i = 1:6 */
    for (i = 0; i < 6; i++) {
      /* Gain: '<Root>/Control Allocation' incorporates:
       *  Saturate: '<Root>/                  '
       *  Sum: '<Root>/Sum2'
       */
      rtb_Derivative_idx_0 = tunning_nominal_ConstP.ControlAllocation_Gain[i +
        18] * rtb_ref_idx_3 + (tunning_nominal_ConstP.ControlAllocation_Gain[i +
        12] * rtb_uNm_p + (tunning_nominal_ConstP.ControlAllocation_Gain[i + 6] *
                           rtb_ff_idx_0 + (rtb_ff_idx_1 + 15.107400000000002) *
                           tunning_nominal_ConstP.ControlAllocation_Gain[i]));

      /* Saturate: '<Root>/                  ' incorporates:
       *  Gain: '<Root>/Control Allocation'
       */
      if (rtb_Derivative_idx_0 > 8.54858) {
        tunning_nominal_B.u[i] = 8.54858;
      } else if (rtb_Derivative_idx_0 < 0.0) {
        tunning_nominal_B.u[i] = 0.0;
      } else {
        tunning_nominal_B.u[i] = rtb_Derivative_idx_0;
      }

      /* MATLAB Function: '<S3>/LOE_' incorporates:
       *  Inport: '<Root>/LOE_a'
       *  Inport: '<Root>/LOE_t'
       */
      rtb_LOE_out[i] = 0.0;

      /* '<S15>:1:4' if t>= LOE_t(i) */
      if (rtb_Clock >= tunning_nominal_U.LOE_t[i]) {
        /* '<S15>:1:5' LOE_out(i) = LOE(i); */
        rtb_LOE_out[i] = tunning_nominal_U.LOE_a[i];
      }

      /* End of MATLAB Function: '<S3>/LOE_' */
    }

    /* Gain: '<S4>/mapping_0_200' incorporates:
     *  Gain: '<S4>/      '
     *  Gain: '<S4>/rads_to_RPM'
     *  MATLAB Function: '<Root>/Actuator_Fault'
     *  Sqrt: '<S4>/Sqrt1'
     *  Sum: '<S4>/Sum3'
     */
    /* MATLAB Function 'Actuator_Fault': '<S1>:1' */
    /* '<S1>:1:2' T1 = T(1)*(1-LOE(1)); */
    /* '<S1>:1:3' T2 = T(2)*(1-LOE(2)); */
    /* '<S1>:1:4' T3 = T(3)*(1-LOE(3)); */
    /* '<S1>:1:5' T4 = T(4)*(1-LOE(4)); */
    /* '<S1>:1:6' T5 = T(5)*(1-LOE(5)); */
    /* '<S1>:1:7' T6 = T(6)*(1-LOE(6)); */
    /* '<S1>:1:8' T_f = [T1;T2;T3;T4;T5;T6]; */
    rtb_Derivative_idx_0 = (std::sqrt((1.0 - rtb_LOE_out[0]) *
      tunning_nominal_B.u[0] * 116978.4923343994) * 9.5493 - 1250.0) *
      0.022857142857142857;

    /* Saturate: '<S4>/Saturation' */
    if (rtb_Derivative_idx_0 > 200.0) {
      tunning_nominal_B.Saturation[0] = 200.0;
    } else if (rtb_Derivative_idx_0 < 0.0) {
      tunning_nominal_B.Saturation[0] = 0.0;
    } else {
      tunning_nominal_B.Saturation[0] = rtb_Derivative_idx_0;
    }

    /* Gain: '<S4>/mapping_0_200' incorporates:
     *  Gain: '<S4>/      '
     *  Gain: '<S4>/rads_to_RPM'
     *  MATLAB Function: '<Root>/Actuator_Fault'
     *  Sqrt: '<S4>/Sqrt1'
     *  Sum: '<S4>/Sum3'
     */
    rtb_Derivative_idx_0 = (std::sqrt((1.0 - rtb_LOE_out[1]) *
      tunning_nominal_B.u[1] * 116978.4923343994) * 9.5493 - 1250.0) *
      0.022857142857142857;

    /* Saturate: '<S4>/Saturation' */
    if (rtb_Derivative_idx_0 > 200.0) {
      tunning_nominal_B.Saturation[1] = 200.0;
    } else if (rtb_Derivative_idx_0 < 0.0) {
      tunning_nominal_B.Saturation[1] = 0.0;
    } else {
      tunning_nominal_B.Saturation[1] = rtb_Derivative_idx_0;
    }

    /* Gain: '<S4>/mapping_0_200' incorporates:
     *  Gain: '<S4>/      '
     *  Gain: '<S4>/rads_to_RPM'
     *  MATLAB Function: '<Root>/Actuator_Fault'
     *  Sqrt: '<S4>/Sqrt1'
     *  Sum: '<S4>/Sum3'
     */
    rtb_Derivative_idx_0 = (std::sqrt((1.0 - rtb_LOE_out[2]) *
      tunning_nominal_B.u[2] * 116978.4923343994) * 9.5493 - 1250.0) *
      0.022857142857142857;

    /* Saturate: '<S4>/Saturation' */
    if (rtb_Derivative_idx_0 > 200.0) {
      tunning_nominal_B.Saturation[2] = 200.0;
    } else if (rtb_Derivative_idx_0 < 0.0) {
      tunning_nominal_B.Saturation[2] = 0.0;
    } else {
      tunning_nominal_B.Saturation[2] = rtb_Derivative_idx_0;
    }

    /* Gain: '<S4>/mapping_0_200' incorporates:
     *  Gain: '<S4>/      '
     *  Gain: '<S4>/rads_to_RPM'
     *  MATLAB Function: '<Root>/Actuator_Fault'
     *  Sqrt: '<S4>/Sqrt1'
     *  Sum: '<S4>/Sum3'
     */
    rtb_Derivative_idx_0 = (std::sqrt((1.0 - rtb_LOE_out[3]) *
      tunning_nominal_B.u[3] * 116978.4923343994) * 9.5493 - 1250.0) *
      0.022857142857142857;

    /* Saturate: '<S4>/Saturation' */
    if (rtb_Derivative_idx_0 > 200.0) {
      tunning_nominal_B.Saturation[3] = 200.0;
    } else if (rtb_Derivative_idx_0 < 0.0) {
      tunning_nominal_B.Saturation[3] = 0.0;
    } else {
      tunning_nominal_B.Saturation[3] = rtb_Derivative_idx_0;
    }

    /* Gain: '<S4>/mapping_0_200' incorporates:
     *  Gain: '<S4>/      '
     *  Gain: '<S4>/rads_to_RPM'
     *  MATLAB Function: '<Root>/Actuator_Fault'
     *  Sqrt: '<S4>/Sqrt1'
     *  Sum: '<S4>/Sum3'
     */
    rtb_Derivative_idx_0 = (std::sqrt((1.0 - rtb_LOE_out[4]) *
      tunning_nominal_B.u[4] * 116978.4923343994) * 9.5493 - 1250.0) *
      0.022857142857142857;

    /* Saturate: '<S4>/Saturation' */
    if (rtb_Derivative_idx_0 > 200.0) {
      tunning_nominal_B.Saturation[4] = 200.0;
    } else if (rtb_Derivative_idx_0 < 0.0) {
      tunning_nominal_B.Saturation[4] = 0.0;
    } else {
      tunning_nominal_B.Saturation[4] = rtb_Derivative_idx_0;
    }

    /* Gain: '<S4>/mapping_0_200' incorporates:
     *  Gain: '<S4>/      '
     *  Gain: '<S4>/rads_to_RPM'
     *  MATLAB Function: '<Root>/Actuator_Fault'
     *  Sqrt: '<S4>/Sqrt1'
     *  Sum: '<S4>/Sum3'
     */
    rtb_Derivative_idx_0 = (std::sqrt((1.0 - rtb_LOE_out[5]) *
      tunning_nominal_B.u[5] * 116978.4923343994) * 9.5493 - 1250.0) *
      0.022857142857142857;

    /* Saturate: '<S4>/Saturation' */
    if (rtb_Derivative_idx_0 > 200.0) {
      tunning_nominal_B.Saturation[5] = 200.0;
    } else if (rtb_Derivative_idx_0 < 0.0) {
      tunning_nominal_B.Saturation[5] = 0.0;
    } else {
      tunning_nominal_B.Saturation[5] = rtb_Derivative_idx_0;
    }

    if (rtmIsMajorTimeStep((&tunning_nominal_M))) {
      /* Outport: '<Root>/motor_command' incorporates:
       *  ZeroOrderHold: '<Root>/Zero-Order Hold'
       */
      for (i = 0; i < 6; i++) {
        tunning_nominal_Y.motor_command[i] = tunning_nominal_B.Saturation[i];
      }

      /* End of Outport: '<Root>/motor_command' */
    }

    /* Outport: '<Root>/virtual_control' incorporates:
     *  Sum: '<Root>/Sum2'
     */
    tunning_nominal_Y.virtual_control[0] = rtb_ff_idx_1 + 15.107400000000002;
    tunning_nominal_Y.virtual_control[1] = rtb_ff_idx_0;
    tunning_nominal_Y.virtual_control[2] = rtb_uNm_p;
    tunning_nominal_Y.virtual_control[3] = rtb_ref_idx_3;

    /* MATLAB Function: '<S3>/MATLAB Function' incorporates:
     *  Inport: '<Root>/Y0'
     *  Inport: '<Root>/mode'
     *  Inport: '<Root>/ref'
     */
    /* MATLAB Function 'Test_config_and_data/MATLAB Function': '<S16>:1' */
    /* '<S16>:1:2' ref = Y0; */
    /* '<S16>:1:3' switch test_mode */
    switch ((int32_T)tunning_nominal_U.mode) {
     case 0:
      /* '<S16>:1:4' case 0      % manual test */
      /*  manual test */
      /* '<S16>:1:5' ref = ref_manual; */
      rtb_ff_idx_0 = tunning_nominal_U.ref[0];
      rtb_Clock = tunning_nominal_U.ref[1];
      rtb_ff_idx_1 = tunning_nominal_U.ref[2];
      rtb_ref_idx_3 = tunning_nominal_U.ref[3];
      break;

     case 1:
      /* '<S16>:1:6' case 1      % waypoint */
      /*  waypoint */
      /* '<S16>:1:7' if t<=15 */
      if (rtb_Clock <= 15.0) {
        /* '<S16>:1:8' ref = [Y0(1); Y0(2); 1; Y0(4)]; */
        rtb_ff_idx_0 = tunning_nominal_U.Y0[0];
        rtb_Clock = tunning_nominal_U.Y0[1];
        rtb_ff_idx_1 = 1.0;
        rtb_ref_idx_3 = tunning_nominal_U.Y0[3];
      } else if (rtb_Clock <= 25.0) {
        /* '<S16>:1:9' elseif t <= 25 */
        /* '<S16>:1:10' ref = [Y0(1)+1; Y0(2)-1; 1; Y0(4)]; */
        rtb_ff_idx_0 = tunning_nominal_U.Y0[0] + 1.0;
        rtb_Clock = tunning_nominal_U.Y0[1] - 1.0;
        rtb_ff_idx_1 = 1.0;
        rtb_ref_idx_3 = tunning_nominal_U.Y0[3];
      } else if (rtb_Clock <= 35.0) {
        /* '<S16>:1:11' elseif t <=35 */
        /* '<S16>:1:12' ref = [Y0(1)-1; Y0(2)+1; 1; Y0(4)]; */
        rtb_ff_idx_0 = tunning_nominal_U.Y0[0] - 1.0;
        rtb_Clock = tunning_nominal_U.Y0[1] + 1.0;
        rtb_ff_idx_1 = 1.0;
        rtb_ref_idx_3 = tunning_nominal_U.Y0[3];
      } else if (rtb_Clock <= 45.0) {
        /* '<S16>:1:13' elseif t <=45 */
        /* '<S16>:1:14' ref = [Y0(1)-1; Y0(2)+1; 1; Y0(4)]; */
        rtb_ff_idx_0 = tunning_nominal_U.Y0[0] - 1.0;
        rtb_Clock = tunning_nominal_U.Y0[1] + 1.0;
        rtb_ff_idx_1 = 1.0;
        rtb_ref_idx_3 = tunning_nominal_U.Y0[3];
      } else if (rtb_Clock <= 55.0) {
        /* '<S16>:1:15' elseif t <=55 */
        /* '<S16>:1:16' ref = [Y0(1); Y0(2); 1; Y0(4)]; */
        rtb_ff_idx_0 = tunning_nominal_U.Y0[0];
        rtb_Clock = tunning_nominal_U.Y0[1];
        rtb_ff_idx_1 = 1.0;
        rtb_ref_idx_3 = tunning_nominal_U.Y0[3];
      } else {
        /* '<S16>:1:17' else */
        /* '<S16>:1:18' ref = Y0; */
        rtb_ff_idx_0 = tunning_nominal_U.Y0[0];
        rtb_Clock = tunning_nominal_U.Y0[1];
        rtb_ff_idx_1 = tunning_nominal_U.Y0[2];
        rtb_ref_idx_3 = tunning_nominal_U.Y0[3];
      }

      /*          if t<=10 */
      /*              ref = [Y0(1); Y0(2); 0.5; Y0(4)]; */
      /*          elseif t <= 30 */
      /*              ref = [Y0(1)-1.5; Y0(2); 0.5; Y0(4)]; */
      /*          elseif t <= 50 */
      /*              ref = [Y0(1)+1.5; Y0(2); 0.5; Y0(4)]; */
      /*          elseif t <= 60 */
      /*              ref = [Y0(1); Y0(2); 0.5; Y0(4)]; */
      /*          else */
      /*              ref = Y0; */
      /*          end    */
      break;

     case 2:
      /* '<S16>:1:31' case 2      % circular tracking */
      /*  circular tracking */
      /* '<S16>:1:32' if t<=10 */
      if (rtb_Clock <= 10.0) {
        /* '<S16>:1:33' ref = [Y0(1); Y0(2); 0.75; Y0(4)]; */
        rtb_ff_idx_0 = tunning_nominal_U.Y0[0];
        rtb_Clock = tunning_nominal_U.Y0[1];
        rtb_ff_idx_1 = 0.75;
        rtb_ref_idx_3 = tunning_nominal_U.Y0[3];
      } else if (rtb_Clock <= 50.0) {
        /* '<S16>:1:34' elseif t <= 50 */
        /* '<S16>:1:35' ref = [cos(t); sin(t); 0.75; Y0(4)]; */
        rtb_ff_idx_0 = std::cos(rtb_Clock);
        rtb_Clock = std::sin(rtb_Clock);
        rtb_ff_idx_1 = 0.75;
        rtb_ref_idx_3 = tunning_nominal_U.Y0[3];
      } else if (rtb_Clock <= 60.0) {
        /* '<S16>:1:36' elseif t <= 60 */
        /* '<S16>:1:37' ref = [Y0(1); Y0(2); 0.75; Y0(4)]; */
        rtb_ff_idx_0 = tunning_nominal_U.Y0[0];
        rtb_Clock = tunning_nominal_U.Y0[1];
        rtb_ff_idx_1 = 0.75;
        rtb_ref_idx_3 = tunning_nominal_U.Y0[3];
      } else {
        /* '<S16>:1:38' else */
        /* '<S16>:1:39' ref = Y0; */
        rtb_ff_idx_0 = tunning_nominal_U.Y0[0];
        rtb_Clock = tunning_nominal_U.Y0[1];
        rtb_ff_idx_1 = tunning_nominal_U.Y0[2];
        rtb_ref_idx_3 = tunning_nominal_U.Y0[3];
      }

      /*          ref = [cos(t); sin(t);min(t,15);Y0(4)]; */
      break;

     default:
      /* '<S16>:1:42' otherwise */
      /* '<S16>:1:43' ref = Y0; */
      rtb_ff_idx_0 = tunning_nominal_U.Y0[0];
      rtb_Clock = tunning_nominal_U.Y0[1];
      rtb_ff_idx_1 = tunning_nominal_U.Y0[2];
      rtb_ref_idx_3 = tunning_nominal_U.Y0[3];
      break;
    }

    /* End of MATLAB Function: '<S3>/MATLAB Function' */

    /* Outport: '<Root>/ref_out' */
    tunning_nominal_Y.ref_out[0] = rtb_ff_idx_0;
    tunning_nominal_Y.ref_out[1] = rtb_Clock;
    tunning_nominal_Y.ref_out[2] = rtb_ff_idx_1;
    tunning_nominal_Y.ref_out[3] = rtb_ref_idx_3;

    /* Outport: '<Root>/LOE' */
    for (i = 0; i < 6; i++) {
      tunning_nominal_Y.LOE[i] = rtb_LOE_out[i];
    }

    /* End of Outport: '<Root>/LOE' */
    if (rtmIsMajorTimeStep((&tunning_nominal_M))) {
      /* Memory: '<S2>/Memory' */
      for (i = 0; i < 6; i++) {
        tunning_nominal_B.Memory[i] = tunning_nominal_DW.Memory_PreviousInput[i];
      }

      /* End of Memory: '<S2>/Memory' */
    }

    /* Derivative: '<S2>/Derivative' incorporates:
     *  Inport: '<Root>/X'
     */
    if ((tunning_nominal_DW.TimeStampA >= (&tunning_nominal_M)->Timing.t[0]) &&
        (tunning_nominal_DW.TimeStampB >= (&tunning_nominal_M)->Timing.t[0])) {
      rtb_Derivative_idx_0 = 0.0;
      rtb_Derivative_idx_1 = 0.0;
      rtb_uNm_p = 0.0;
    } else {
      rtb_uNm_p = tunning_nominal_DW.TimeStampA;
      lastU = (real_T (*)[3])tunning_nominal_DW.LastUAtTimeA;
      if (tunning_nominal_DW.TimeStampA < tunning_nominal_DW.TimeStampB) {
        if (tunning_nominal_DW.TimeStampB < (&tunning_nominal_M)->Timing.t[0]) {
          rtb_uNm_p = tunning_nominal_DW.TimeStampB;
          lastU = (real_T (*)[3])tunning_nominal_DW.LastUAtTimeB;
        }
      } else {
        if (tunning_nominal_DW.TimeStampA >= (&tunning_nominal_M)->Timing.t[0])
        {
          rtb_uNm_p = tunning_nominal_DW.TimeStampB;
          lastU = (real_T (*)[3])tunning_nominal_DW.LastUAtTimeB;
        }
      }

      rtb_uNm_p = (&tunning_nominal_M)->Timing.t[0] - rtb_uNm_p;
      rtb_Derivative_idx_0 = (tunning_nominal_U.X[9] - (*lastU)[0]) / rtb_uNm_p;
      rtb_Derivative_idx_1 = (tunning_nominal_U.X[10] - (*lastU)[1]) / rtb_uNm_p;
      rtb_uNm_p = (tunning_nominal_U.X[11] - (*lastU)[2]) / rtb_uNm_p;
    }

    /* End of Derivative: '<S2>/Derivative' */
    if (rtmIsMajorTimeStep((&tunning_nominal_M))) {
      /* Product: '<S2>/Product1' incorporates:
       *  Constant: '<S2>/Constant1'
       *  Inport: '<Root>/X'
       */
      for (i = 0; i < 3; i++) {
        rtb_ZeroOrderHold1[i] = tunning_nominal_ConstP.Constant1_Value[i + 6] *
          tunning_nominal_U.X[11] + (tunning_nominal_ConstP.Constant1_Value[i +
          3] * tunning_nominal_U.X[10] +
          tunning_nominal_ConstP.Constant1_Value[i] * tunning_nominal_U.X[9]);
      }

      /* End of Product: '<S2>/Product1' */

      /* Sum: '<S10>/Sum1' incorporates:
       *  Inport: '<Root>/X'
       *  Product: '<S12>/i x k'
       *  Product: '<S12>/j x i'
       *  Product: '<S12>/k x j'
       *  Product: '<S13>/i x j'
       *  Product: '<S13>/j x k'
       *  Product: '<S13>/k x i'
       */
      tunning_nominal_B.Sum1[0] = tunning_nominal_U.X[10] * rtb_ZeroOrderHold1[2]
        - tunning_nominal_U.X[11] * rtb_ZeroOrderHold1[1];
      tunning_nominal_B.Sum1[1] = tunning_nominal_U.X[11] * rtb_ZeroOrderHold1[0]
        - tunning_nominal_U.X[9] * rtb_ZeroOrderHold1[2];
      tunning_nominal_B.Sum1[2] = tunning_nominal_U.X[9] * rtb_ZeroOrderHold1[1]
        - tunning_nominal_U.X[10] * rtb_ZeroOrderHold1[0];
    }

    /* Sum: '<S2>/Sum3' incorporates:
     *  Constant: '<S2>/Constant1'
     *  MATLAB Function: '<S2>/MATLAB Function1'
     *  Product: '<S2>/Product'
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
    for (i = 0; i < 3; i++) {
      tmp[i] = ((tunning_nominal_ConstP.Constant1_Value[i + 3] *
                 rtb_Derivative_idx_1 + tunning_nominal_ConstP.Constant1_Value[i]
                 * rtb_Derivative_idx_0) +
                tunning_nominal_ConstP.Constant1_Value[i + 6] * rtb_uNm_p) +
        tunning_nominal_B.Sum1[i];
    }

    /* End of Sum: '<S2>/Sum3' */

    /* MATLAB Function: '<S2>/MATLAB Function1' */
    tmp_0[0] = tunning_nominal_B.Memory[0] - tunning_nominal_B.Memory[3];
    tmp_0[1] = tunning_nominal_B.Memory[1] - tunning_nominal_B.Memory[4];
    tmp_0[2] = tunning_nominal_B.Memory[2] - tunning_nominal_B.Memory[5];
    for (i = 0; i < 3; i++) {
      rtb_ZeroOrderHold1[i] = tmp_0[i] - (a[i + 6] * tmp[2] + (a[i + 3] * tmp[1]
        + a[i] * tmp[0]));
    }

    /*  Residu_1_4 */
    /* '<S11>:1:14' gamma    = [1-(-Residu_1_4(1) + u(1))/u(1) */
    /* '<S11>:1:15'             1-(-Residu_1_4(2) + u(2))/u(2) */
    /* '<S11>:1:16'             1-(-Residu_1_4(3) + u(3))/u(3)]; */
    tunning_nominal_B.gamma[0] = 1.0 - (-rtb_ZeroOrderHold1[0] +
      tunning_nominal_B.Memory[0]) / tunning_nominal_B.Memory[0];
    tunning_nominal_B.gamma[1] = 1.0 - (-rtb_ZeroOrderHold1[1] +
      tunning_nominal_B.Memory[1]) / tunning_nominal_B.Memory[1];
    tunning_nominal_B.gamma[2] = 1.0 - (-rtb_ZeroOrderHold1[2] +
      tunning_nominal_B.Memory[2]) / tunning_nominal_B.Memory[2];
    if (rtmIsMajorTimeStep((&tunning_nominal_M))) {
      /* Outport: '<Root>/gamma' incorporates:
       *  ZeroOrderHold: '<Root>/Zero-Order Hold1'
       */
      tunning_nominal_Y.gamma[0] = tunning_nominal_B.gamma[0];
      tunning_nominal_Y.gamma[1] = tunning_nominal_B.gamma[1];
      tunning_nominal_Y.gamma[2] = tunning_nominal_B.gamma[2];
    }

    /* Sum: '<S3>/Sum' incorporates:
     *  Inport: '<Root>/Y0'
     */
    rtb_ff_idx_0 -= tunning_nominal_U.Y0[0];
    rtb_Clock -= tunning_nominal_U.Y0[1];
    rtb_ff_idx_1 -= tunning_nominal_U.Y0[2];
    rtb_uNm_p = rtb_ref_idx_3 - tunning_nominal_U.Y0[3];

    /* Saturate: '<S5>/x' */
    if (rtb_ff_idx_0 > 2.0) {
      rtb_ff_idx_0 = 2.0;
    } else {
      if (rtb_ff_idx_0 < -2.0) {
        rtb_ff_idx_0 = -2.0;
      }
    }

    /* End of Saturate: '<S5>/x' */

    /* Sum: '<S5>/Sum1' */
    tunning_nominal_B.Sum1_g = rtb_ff_idx_0 - rtb_d_x;

    /* Saturate: '<S5>/y' */
    if (rtb_Clock > 2.0) {
      rtb_Clock = 2.0;
    } else {
      if (rtb_Clock < -2.0) {
        rtb_Clock = -2.0;
      }
    }

    /* End of Saturate: '<S5>/y' */

    /* Sum: '<S5>/Sum4' */
    tunning_nominal_B.Sum4 = rtb_Clock - rtb_d_y;

    /* Saturate: '<S8>/yaw' */
    if (rtb_uNm_p > 3.1415926535897931) {
      rtb_uNm_p = 3.1415926535897931;
    } else {
      if (rtb_uNm_p < -3.1415926535897931) {
        rtb_uNm_p = -3.1415926535897931;
      }
    }

    /* End of Saturate: '<S8>/yaw' */

    /* Sum: '<S8>/Sum3' */
    tunning_nominal_B.Sum3 = rtb_uNm_p - rtb_d_psi;

    /* Saturate: '<S9>/z' */
    if (rtb_ff_idx_1 > 1.75) {
      rtb_ff_idx_1 = 1.75;
    } else {
      if (rtb_ff_idx_1 < 0.0) {
        rtb_ff_idx_1 = 0.0;
      }
    }

    /* End of Saturate: '<S9>/z' */

    /* Sum: '<S9>/Sum3' */
    tunning_nominal_B.Sum3_h = rtb_ff_idx_1 - rtb_d_z;
  }

  if (rtmIsMajorTimeStep((&tunning_nominal_M))) {
    real_T (*lastU)[3];
    int32_T i;
    if (rtmIsMajorTimeStep((&tunning_nominal_M))) {
      /* Update for Memory: '<S2>/Memory' */
      for (i = 0; i < 6; i++) {
        tunning_nominal_DW.Memory_PreviousInput[i] = tunning_nominal_B.u[i];
      }

      /* End of Update for Memory: '<S2>/Memory' */
    }

    /* Update for Derivative: '<S2>/Derivative' incorporates:
     *  Update for Inport: '<Root>/X'
     */
    if (tunning_nominal_DW.TimeStampA == (rtInf)) {
      tunning_nominal_DW.TimeStampA = (&tunning_nominal_M)->Timing.t[0];
      lastU = (real_T (*)[3])tunning_nominal_DW.LastUAtTimeA;
    } else if (tunning_nominal_DW.TimeStampB == (rtInf)) {
      tunning_nominal_DW.TimeStampB = (&tunning_nominal_M)->Timing.t[0];
      lastU = (real_T (*)[3])tunning_nominal_DW.LastUAtTimeB;
    } else if (tunning_nominal_DW.TimeStampA < tunning_nominal_DW.TimeStampB) {
      tunning_nominal_DW.TimeStampA = (&tunning_nominal_M)->Timing.t[0];
      lastU = (real_T (*)[3])tunning_nominal_DW.LastUAtTimeA;
    } else {
      tunning_nominal_DW.TimeStampB = (&tunning_nominal_M)->Timing.t[0];
      lastU = (real_T (*)[3])tunning_nominal_DW.LastUAtTimeB;
    }

    (*lastU)[0] = tunning_nominal_U.X[9];
    (*lastU)[1] = tunning_nominal_U.X[10];
    (*lastU)[2] = tunning_nominal_U.X[11];

    /* End of Update for Derivative: '<S2>/Derivative' */
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
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void tunning_nominalModelClass::tunning_nominal_derivatives()
{
  XDot_tunning_nominal_T *_rtXdot;
  _rtXdot = ((XDot_tunning_nominal_T *) (&tunning_nominal_M)->derivs);

  /* Derivatives for Integrator: '<S9>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = tunning_nominal_B.Sum3_h;

  /* Derivatives for Integrator: '<S5>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_d = tunning_nominal_B.Sum1_g;

  /* Derivatives for Integrator: '<S5>/Integrator' */
  _rtXdot->Integrator_CSTATE = tunning_nominal_B.Sum4;

  /* Derivatives for Integrator: '<S8>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_j = tunning_nominal_B.Sum3;
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

  {
    int32_T i;

    /* InitializeConditions for Integrator: '<S9>/Integrator1' */
    tunning_nominal_X.Integrator1_CSTATE = 0.0;

    /* InitializeConditions for Integrator: '<S5>/Integrator1' */
    tunning_nominal_X.Integrator1_CSTATE_d = 0.0;

    /* InitializeConditions for Integrator: '<S5>/Integrator' */
    tunning_nominal_X.Integrator_CSTATE = 0.0;

    /* InitializeConditions for Integrator: '<S8>/Integrator1' */
    tunning_nominal_X.Integrator1_CSTATE_j = 0.0;

    /* InitializeConditions for Memory: '<S2>/Memory' */
    for (i = 0; i < 6; i++) {
      tunning_nominal_DW.Memory_PreviousInput[i] = 2.5179000000000005;
    }

    /* End of InitializeConditions for Memory: '<S2>/Memory' */

    /* InitializeConditions for Derivative: '<S2>/Derivative' */
    tunning_nominal_DW.TimeStampA = (rtInf);
    tunning_nominal_DW.TimeStampB = (rtInf);
  }
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
