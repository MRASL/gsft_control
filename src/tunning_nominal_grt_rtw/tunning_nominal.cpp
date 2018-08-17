/*
 * tunning_nominal.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "tunning_nominal".
 *
 * Model version              : 1.1479
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Fri Aug 17 10:03:20 2018
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
  /* local block i/o variables */
  real_T rtb_Add[6];
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
    real_T axref_N;
    real_T ayref_N;
    real_T rtb_d_z;
    real_T rtb_ff[3];
    real_T rtb_d_psi;
    real_T rtb_LOE_out[6];
    real_T rtb_Sum1_l[3];
    real_T rtb_Clock;
    int32_T i;
    real_T rtb_LOE_out_0[3];
    real_T rtb_LOE_out_1[3];
    int32_T i_0;
    real_T rtb_ref_idx_2;
    real_T rtb_ref_idx_3;
    real_T rtb_ref_idx_1;
    real_T rtb_ref_idx_0;
    real_T u0;
    if (rtmIsMajorTimeStep((&tunning_nominal_M)) &&
        (&tunning_nominal_M)->Timing.TaskCounters.TID[1] == 0) {
      /* Product: '<Root>/Product' incorporates:
       *  Inport: '<Root>/X'
       *  Trigonometry: '<Root>/Trigonometric Function'
       *  Trigonometry: '<Root>/Trigonometric Function1'
       */
      tunning_nominal_B.Product = std::cos(tunning_nominal_U.X[7]) * std::cos
        (tunning_nominal_U.X[6]);
    }

    /* Sum: '<S4>/Sum5' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/Y0'
     */
    rtb_d_z = tunning_nominal_U.X[2] - tunning_nominal_U.Y0[2];

    /* Clock: '<Root>/Clock' */
    rtb_Clock = (&tunning_nominal_M)->Timing.t[0];

    /* MATLAB Function: '<S4>/FFW' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/mode'
     */
    /* MATLAB Function 'Test_config_and_data/FFW': '<S60>:1' */
    /* '<S60>:1:2' ff = [0;0;0]; */
    rtb_ff[0] = 0.0;
    rtb_ff[1] = 0.0;
    rtb_ff[2] = 0.0;

    /* '<S60>:1:3' g = 9.81; */
    /*  [x;y] = [cos(t); sin(t)] */
    /* '<S60>:1:5' if (test_mode == 2) */
    if (tunning_nominal_U.mode == 2.0) {
      /* '<S60>:1:6' if (t >=10) && (t<= 50) */
      if ((rtb_Clock >= 10.0) && (rtb_Clock <= 50.0)) {
        /* '<S60>:1:7' axref_N = -cos(t); */
        axref_N = -std::cos(rtb_Clock);

        /* '<S60>:1:8' ayref_N = -sin(t); */
        ayref_N = -std::sin(rtb_Clock);

        /* '<S60>:1:10' axref_b = cos(X(8))*cos(X(9))*axref_N + cos(X(8))*sin(X(9))*ayref_N; */
        /* '<S60>:1:11' ayref_b = (sin(X(7))*sin(X(8))*cos(X(9)) - cos(X(7))*sin(X(9)))*axref_N + (sin(X(7))*sin(X(8))*sin(X(9)) + cos(X(7))*cos(X(9)))*ayref_N; */
        /* '<S60>:1:12' azref_b = (cos(X(7))*sin(X(8))*cos(X(9)) + sin(X(7))*sin(X(9)))*axref_N + (cos(X(7))*sin(X(8))*sin(X(9)) - sin(X(7))*cos(X(9)))*ayref_N; */
        /*   */
        /* '<S60>:1:14' ff = [-ayref_b/g; axref_b/g; azref_b]; */
        rtb_ff[0] = -((std::sin(tunning_nominal_U.X[6]) * std::sin
                       (tunning_nominal_U.X[7]) * std::cos(tunning_nominal_U.X[8])
                       - std::cos(tunning_nominal_U.X[6]) * std::sin
                       (tunning_nominal_U.X[8])) * axref_N + (std::sin
          (tunning_nominal_U.X[6]) * std::sin(tunning_nominal_U.X[7]) * std::sin
          (tunning_nominal_U.X[8]) + std::cos(tunning_nominal_U.X[6]) * std::cos
          (tunning_nominal_U.X[8])) * ayref_N) / 9.81;
        rtb_ff[1] = (std::cos(tunning_nominal_U.X[7]) * std::cos
                     (tunning_nominal_U.X[8]) * -std::cos(rtb_Clock) + std::cos
                     (tunning_nominal_U.X[7]) * std::sin(tunning_nominal_U.X[8])
                     * -std::sin(rtb_Clock)) / 9.81;
        rtb_ff[2] = (std::cos(tunning_nominal_U.X[6]) * std::sin
                     (tunning_nominal_U.X[7]) * std::cos(tunning_nominal_U.X[8])
                     + std::sin(tunning_nominal_U.X[6]) * std::sin
                     (tunning_nominal_U.X[8])) * axref_N + (std::cos
          (tunning_nominal_U.X[6]) * std::sin(tunning_nominal_U.X[7]) * std::sin
          (tunning_nominal_U.X[8]) - std::sin(tunning_nominal_U.X[6]) * std::cos
          (tunning_nominal_U.X[8])) * ayref_N;
      } else {
        /* '<S60>:1:15' else */
        /* '<S60>:1:16' ff = [0;0;0]; */
        rtb_ff[0] = 0.0;
        rtb_ff[1] = 0.0;
        rtb_ff[2] = 0.0;
      }
    }

    /* End of MATLAB Function: '<S4>/FFW' */

    /* Sum: '<S4>/Sum1' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/Y0'
     */
    axref_N = tunning_nominal_U.X[0] - tunning_nominal_U.Y0[0];

    /* Sum: '<S6>/Sum2' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/gain'
     *  Integrator: '<S6>/Integrator1'
     *  Product: '<S6>/Product2'
     *  Product: '<S6>/Product3'
     *  SignalConversion: '<S6>/TmpSignal ConversionAtProduct3Inport2'
     */
    tunning_nominal_B.Sum2 = tunning_nominal_U.gain[2] *
      tunning_nominal_X.Integrator1_CSTATE_d - (tunning_nominal_U.gain[0] *
      axref_N + tunning_nominal_U.gain[1] * tunning_nominal_U.X[3]);

    /* Sum: '<S4>/Sum4' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/Y0'
     */
    ayref_N = tunning_nominal_U.X[1] - tunning_nominal_U.Y0[1];

    /* Sum: '<S6>/Sum3' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/gain'
     *  Integrator: '<S6>/Integrator'
     *  Product: '<S6>/Product1'
     *  Product: '<S6>/Product4'
     *  SignalConversion: '<S6>/TmpSignal ConversionAtProduct1Inport2'
     */
    tunning_nominal_B.Sum3 = tunning_nominal_U.gain[5] *
      tunning_nominal_X.Integrator_CSTATE - (tunning_nominal_U.gain[3] * ayref_N
      + tunning_nominal_U.gain[4] * tunning_nominal_U.X[4]);

    /* RateTransition: '<Root>/T_outer' incorporates:
     *  Inport: '<Root>/X'
     */
    if ((rtmIsMajorTimeStep((&tunning_nominal_M)) &&
         (&tunning_nominal_M)->Timing.TaskCounters.TID[1] == 0) &&
        (rtmIsMajorTimeStep((&tunning_nominal_M)) &&
         (&tunning_nominal_M)->Timing.TaskCounters.TID[2] == 0)) {
      tunning_nominal_B.T_outer[0] = tunning_nominal_B.Sum2;
      tunning_nominal_B.T_outer[1] = tunning_nominal_B.Sum3;
      tunning_nominal_B.T_outer[2] = tunning_nominal_U.X[8];
    }

    /* End of RateTransition: '<Root>/T_outer' */
    if (rtmIsMajorTimeStep((&tunning_nominal_M)) &&
        (&tunning_nominal_M)->Timing.TaskCounters.TID[2] == 0) {
      /* Fcn: '<Root>/Fcn1' */
      tunning_nominal_B.Fcn1 = tunning_nominal_B.T_outer[1] * std::cos
        (tunning_nominal_B.T_outer[2]) + tunning_nominal_B.T_outer[0] * std::sin
        (tunning_nominal_B.T_outer[2]);

      /* Fcn: '<Root>/Fcn' */
      tunning_nominal_B.Fcn = -tunning_nominal_B.T_outer[1] * std::sin
        (tunning_nominal_B.T_outer[2]) + tunning_nominal_B.T_outer[0] * std::cos
        (tunning_nominal_B.T_outer[2]);
    }

    /* Sum: '<S4>/Sum6' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/Y0'
     */
    rtb_d_psi = tunning_nominal_U.X[8] - tunning_nominal_U.Y0[3];

    /* SignalConversion: '<Root>/TmpSignal ConversionAtControl AllocationInport1' incorporates:
     *  Constant: '<Root>/                     '
     *  Gain: '<Root>/Gain1'
     *  Gain: '<S10>/Gain'
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/gain'
     *  Integrator: '<S10>/Integrator1'
     *  Product: '<Root>/Divide'
     *  Product: '<S10>/Product'
     *  Product: '<S10>/Product1'
     *  SignalConversion: '<S10>/TmpSignal ConversionAtProduct1Inport2'
     *  Sum: '<Root>/Sum1'
     *  Sum: '<Root>/Sum2'
     *  Sum: '<S10>/Sum1'
     */
    rtb_ref_idx_0 = (((tunning_nominal_U.gain[8] *
                       tunning_nominal_X.Integrator1_CSTATE -
                       (tunning_nominal_U.gain[6] * rtb_d_z +
                        tunning_nominal_U.gain[7] * tunning_nominal_U.X[5])) *
                      0.64935064935064934 + 9.81) * (1.0 /
      tunning_nominal_B.Product) + rtb_ff[2]) * 1.54;

    /* Saturate: '<Root>/2Nm ' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/gain'
     *  Product: '<S8>/Product'
     *  SignalConversion: '<S8>/TmpSignal ConversionAtProductInport2'
     *  Sum: '<Root>/Sum7'
     *  Sum: '<S8>/Sum1'
     */
    rtb_ref_idx_1 = (tunning_nominal_B.Fcn1 + rtb_ff[0]) -
      (tunning_nominal_U.gain[9] * tunning_nominal_U.X[6] +
       tunning_nominal_U.gain[10] * tunning_nominal_U.X[9]);
    if (rtb_ref_idx_1 > 2.0) {
      /* SignalConversion: '<Root>/TmpSignal ConversionAtControl AllocationInport1' */
      rtb_ref_idx_1 = 2.0;
    } else {
      if (rtb_ref_idx_1 < -2.0) {
        /* SignalConversion: '<Root>/TmpSignal ConversionAtControl AllocationInport1' */
        rtb_ref_idx_1 = -2.0;
      }
    }

    /* End of Saturate: '<Root>/2Nm ' */

    /* Saturate: '<Root>/2Nm' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/gain'
     *  Product: '<S7>/Product'
     *  SignalConversion: '<S7>/TmpSignal ConversionAtProductInport2'
     *  Sum: '<Root>/Sum8'
     *  Sum: '<S7>/Sum1'
     */
    rtb_ref_idx_2 = (tunning_nominal_B.Fcn + rtb_ff[1]) -
      (tunning_nominal_U.gain[12] * tunning_nominal_U.X[7] +
       tunning_nominal_U.gain[13] * tunning_nominal_U.X[10]);
    if (rtb_ref_idx_2 > 2.0) {
      /* SignalConversion: '<Root>/TmpSignal ConversionAtControl AllocationInport1' */
      rtb_ref_idx_2 = 2.0;
    } else {
      if (rtb_ref_idx_2 < -2.0) {
        /* SignalConversion: '<Root>/TmpSignal ConversionAtControl AllocationInport1' */
        rtb_ref_idx_2 = -2.0;
      }
    }

    /* End of Saturate: '<Root>/2Nm' */

    /* Saturate: '<Root>/1Nm' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/gain'
     *  Integrator: '<S9>/Integrator1'
     *  Product: '<S9>/Product'
     *  Product: '<S9>/Product1'
     *  SignalConversion: '<S9>/TmpSignal ConversionAtProduct1Inport2'
     *  Sum: '<S9>/Sum1'
     */
    rtb_ref_idx_3 = tunning_nominal_U.gain[17] *
      tunning_nominal_X.Integrator1_CSTATE_j - (tunning_nominal_U.gain[15] *
      rtb_d_psi + tunning_nominal_U.gain[16] * tunning_nominal_U.X[11]);
    if (rtb_ref_idx_3 > 1.0) {
      /* SignalConversion: '<Root>/TmpSignal ConversionAtControl AllocationInport1' */
      rtb_ref_idx_3 = 1.0;
    } else {
      if (rtb_ref_idx_3 < -1.0) {
        /* SignalConversion: '<Root>/TmpSignal ConversionAtControl AllocationInport1' */
        rtb_ref_idx_3 = -1.0;
      }
    }

    /* End of Saturate: '<Root>/1Nm' */
    /* MATLAB Function 'Test_config_and_data/LOE_': '<S61>:1' */
    /* '<S61>:1:2' LOE_out = [0;0;0;0;0;0]; */
    /* '<S61>:1:3' for i = 1:6 */
    for (i = 0; i < 6; i++) {
      /* Gain: '<Root>/Control Allocation' incorporates:
       *  Saturate: '<Root>/                  '
       */
      u0 = tunning_nominal_ConstP.ControlAllocation_Gain[i + 18] * rtb_ref_idx_3
        + (tunning_nominal_ConstP.ControlAllocation_Gain[i + 12] * rtb_ref_idx_2
           + (tunning_nominal_ConstP.ControlAllocation_Gain[i + 6] *
              rtb_ref_idx_1 + tunning_nominal_ConstP.ControlAllocation_Gain[i] *
              rtb_ref_idx_0));

      /* Saturate: '<Root>/                  ' incorporates:
       *  Gain: '<Root>/Control Allocation'
       */
      if (u0 > 8.54858) {
        tunning_nominal_B.u[i] = 8.54858;
      } else if (u0 < 0.0) {
        tunning_nominal_B.u[i] = 0.0;
      } else {
        tunning_nominal_B.u[i] = u0;
      }

      /* MATLAB Function: '<S4>/LOE_' incorporates:
       *  Inport: '<Root>/LOE_a'
       *  Inport: '<Root>/LOE_t'
       */
      rtb_LOE_out[i] = 0.0;

      /* '<S61>:1:4' if t>= LOE_t(i) */
      if (rtb_Clock >= tunning_nominal_U.LOE_t[i]) {
        /* '<S61>:1:5' LOE_out(i) = LOE(i); */
        rtb_LOE_out[i] = tunning_nominal_U.LOE_a[i];
      }

      /* End of MATLAB Function: '<S4>/LOE_' */
    }

    /* Gain: '<S5>/mapping_0_200' incorporates:
     *  Gain: '<S5>/      '
     *  Gain: '<S5>/rads_to_RPM'
     *  MATLAB Function: '<Root>/Actuator_Fault'
     *  Sqrt: '<S5>/Sqrt1'
     *  Sum: '<S5>/Sum3'
     */
    /* MATLAB Function 'Actuator_Fault': '<S1>:1' */
    /* '<S1>:1:2' T1 = T(1)*(1-LOE(1)); */
    /* '<S1>:1:3' T2 = T(2)*(1-LOE(2)); */
    /* '<S1>:1:4' T3 = T(3)*(1-LOE(3)); */
    /* '<S1>:1:5' T4 = T(4)*(1-LOE(4)); */
    /* '<S1>:1:6' T5 = T(5)*(1-LOE(5)); */
    /* '<S1>:1:7' T6 = T(6)*(1-LOE(6)); */
    /* '<S1>:1:8' T_f = [T1;T2;T3;T4;T5;T6]; */
    u0 = (std::sqrt((1.0 - rtb_LOE_out[0]) * tunning_nominal_B.u[0] *
                    116978.4923343994) * 9.5493 - 1250.0) * 0.022857142857142857;

    /* Saturate: '<S5>/Saturation' */
    if (u0 > 200.0) {
      /* Outport: '<Root>/motor_command' */
      tunning_nominal_Y.motor_command[0] = 200.0;
    } else if (u0 < 0.0) {
      /* Outport: '<Root>/motor_command' */
      tunning_nominal_Y.motor_command[0] = 0.0;
    } else {
      /* Outport: '<Root>/motor_command' */
      tunning_nominal_Y.motor_command[0] = u0;
    }

    /* Gain: '<S5>/mapping_0_200' incorporates:
     *  Gain: '<S5>/      '
     *  Gain: '<S5>/rads_to_RPM'
     *  MATLAB Function: '<Root>/Actuator_Fault'
     *  Sqrt: '<S5>/Sqrt1'
     *  Sum: '<S5>/Sum3'
     */
    u0 = (std::sqrt((1.0 - rtb_LOE_out[1]) * tunning_nominal_B.u[1] *
                    116978.4923343994) * 9.5493 - 1250.0) * 0.022857142857142857;

    /* Saturate: '<S5>/Saturation' */
    if (u0 > 200.0) {
      /* Outport: '<Root>/motor_command' */
      tunning_nominal_Y.motor_command[1] = 200.0;
    } else if (u0 < 0.0) {
      /* Outport: '<Root>/motor_command' */
      tunning_nominal_Y.motor_command[1] = 0.0;
    } else {
      /* Outport: '<Root>/motor_command' */
      tunning_nominal_Y.motor_command[1] = u0;
    }

    /* Gain: '<S5>/mapping_0_200' incorporates:
     *  Gain: '<S5>/      '
     *  Gain: '<S5>/rads_to_RPM'
     *  MATLAB Function: '<Root>/Actuator_Fault'
     *  Sqrt: '<S5>/Sqrt1'
     *  Sum: '<S5>/Sum3'
     */
    u0 = (std::sqrt((1.0 - rtb_LOE_out[2]) * tunning_nominal_B.u[2] *
                    116978.4923343994) * 9.5493 - 1250.0) * 0.022857142857142857;

    /* Saturate: '<S5>/Saturation' */
    if (u0 > 200.0) {
      /* Outport: '<Root>/motor_command' */
      tunning_nominal_Y.motor_command[2] = 200.0;
    } else if (u0 < 0.0) {
      /* Outport: '<Root>/motor_command' */
      tunning_nominal_Y.motor_command[2] = 0.0;
    } else {
      /* Outport: '<Root>/motor_command' */
      tunning_nominal_Y.motor_command[2] = u0;
    }

    /* Gain: '<S5>/mapping_0_200' incorporates:
     *  Gain: '<S5>/      '
     *  Gain: '<S5>/rads_to_RPM'
     *  MATLAB Function: '<Root>/Actuator_Fault'
     *  Sqrt: '<S5>/Sqrt1'
     *  Sum: '<S5>/Sum3'
     */
    u0 = (std::sqrt((1.0 - rtb_LOE_out[3]) * tunning_nominal_B.u[3] *
                    116978.4923343994) * 9.5493 - 1250.0) * 0.022857142857142857;

    /* Saturate: '<S5>/Saturation' */
    if (u0 > 200.0) {
      /* Outport: '<Root>/motor_command' */
      tunning_nominal_Y.motor_command[3] = 200.0;
    } else if (u0 < 0.0) {
      /* Outport: '<Root>/motor_command' */
      tunning_nominal_Y.motor_command[3] = 0.0;
    } else {
      /* Outport: '<Root>/motor_command' */
      tunning_nominal_Y.motor_command[3] = u0;
    }

    /* Gain: '<S5>/mapping_0_200' incorporates:
     *  Gain: '<S5>/      '
     *  Gain: '<S5>/rads_to_RPM'
     *  MATLAB Function: '<Root>/Actuator_Fault'
     *  Sqrt: '<S5>/Sqrt1'
     *  Sum: '<S5>/Sum3'
     */
    u0 = (std::sqrt((1.0 - rtb_LOE_out[4]) * tunning_nominal_B.u[4] *
                    116978.4923343994) * 9.5493 - 1250.0) * 0.022857142857142857;

    /* Saturate: '<S5>/Saturation' */
    if (u0 > 200.0) {
      /* Outport: '<Root>/motor_command' */
      tunning_nominal_Y.motor_command[4] = 200.0;
    } else if (u0 < 0.0) {
      /* Outport: '<Root>/motor_command' */
      tunning_nominal_Y.motor_command[4] = 0.0;
    } else {
      /* Outport: '<Root>/motor_command' */
      tunning_nominal_Y.motor_command[4] = u0;
    }

    /* Gain: '<S5>/mapping_0_200' incorporates:
     *  Gain: '<S5>/      '
     *  Gain: '<S5>/rads_to_RPM'
     *  MATLAB Function: '<Root>/Actuator_Fault'
     *  Sqrt: '<S5>/Sqrt1'
     *  Sum: '<S5>/Sum3'
     */
    u0 = (std::sqrt((1.0 - rtb_LOE_out[5]) * tunning_nominal_B.u[5] *
                    116978.4923343994) * 9.5493 - 1250.0) * 0.022857142857142857;

    /* Saturate: '<S5>/Saturation' */
    if (u0 > 200.0) {
      /* Outport: '<Root>/motor_command' */
      tunning_nominal_Y.motor_command[5] = 200.0;
    } else if (u0 < 0.0) {
      /* Outport: '<Root>/motor_command' */
      tunning_nominal_Y.motor_command[5] = 0.0;
    } else {
      /* Outport: '<Root>/motor_command' */
      tunning_nominal_Y.motor_command[5] = u0;
    }

    /* Outport: '<Root>/virtual_control' */
    tunning_nominal_Y.virtual_control[0] = rtb_ref_idx_0;
    tunning_nominal_Y.virtual_control[1] = rtb_ref_idx_1;
    tunning_nominal_Y.virtual_control[2] = rtb_ref_idx_2;
    tunning_nominal_Y.virtual_control[3] = rtb_ref_idx_3;

    /* MATLAB Function: '<S4>/MATLAB Function' incorporates:
     *  Inport: '<Root>/Y0'
     *  Inport: '<Root>/mode'
     *  Inport: '<Root>/ref'
     */
    /* MATLAB Function 'Test_config_and_data/MATLAB Function': '<S62>:1' */
    /* '<S62>:1:2' ref = Y0; */
    /* '<S62>:1:3' switch test_mode */
    switch ((int32_T)tunning_nominal_U.mode) {
     case 0:
      /* '<S62>:1:4' case 0      % manual test */
      /*  manual test */
      /* '<S62>:1:5' ref = ref_manual; */
      rtb_ref_idx_0 = tunning_nominal_U.ref[0];
      rtb_ref_idx_1 = tunning_nominal_U.ref[1];
      rtb_ref_idx_2 = tunning_nominal_U.ref[2];
      rtb_ref_idx_3 = tunning_nominal_U.ref[3];
      break;

     case 1:
      /* '<S62>:1:6' case 1      % waypoint */
      /*  waypoint */
      /* '<S62>:1:7' if t<=15 */
      if (rtb_Clock <= 15.0) {
        /* '<S62>:1:8' ref = [Y0(1); Y0(2); 1; Y0(4)]; */
        rtb_ref_idx_0 = tunning_nominal_U.Y0[0];
        rtb_ref_idx_1 = tunning_nominal_U.Y0[1];
        rtb_ref_idx_2 = 1.0;
        rtb_ref_idx_3 = tunning_nominal_U.Y0[3];
      } else if (rtb_Clock <= 25.0) {
        /* '<S62>:1:9' elseif t <= 25 */
        /* '<S62>:1:10' ref = [Y0(1)+1; Y0(2)-1; 1; Y0(4)]; */
        rtb_ref_idx_0 = tunning_nominal_U.Y0[0] + 1.0;
        rtb_ref_idx_1 = tunning_nominal_U.Y0[1] - 1.0;
        rtb_ref_idx_2 = 1.0;
        rtb_ref_idx_3 = tunning_nominal_U.Y0[3];
      } else if (rtb_Clock <= 35.0) {
        /* '<S62>:1:11' elseif t <=35 */
        /* '<S62>:1:12' ref = [Y0(1)-1; Y0(2)+1; 1; Y0(4)]; */
        rtb_ref_idx_0 = tunning_nominal_U.Y0[0] - 1.0;
        rtb_ref_idx_1 = tunning_nominal_U.Y0[1] + 1.0;
        rtb_ref_idx_2 = 1.0;
        rtb_ref_idx_3 = tunning_nominal_U.Y0[3];
      } else if (rtb_Clock <= 45.0) {
        /* '<S62>:1:13' elseif t <=45 */
        /* '<S62>:1:14' ref = [Y0(1)-1; Y0(2)+1; 1; Y0(4)]; */
        rtb_ref_idx_0 = tunning_nominal_U.Y0[0] - 1.0;
        rtb_ref_idx_1 = tunning_nominal_U.Y0[1] + 1.0;
        rtb_ref_idx_2 = 1.0;
        rtb_ref_idx_3 = tunning_nominal_U.Y0[3];
      } else if (rtb_Clock <= 55.0) {
        /* '<S62>:1:15' elseif t <=55 */
        /* '<S62>:1:16' ref = [Y0(1); Y0(2); 1; Y0(4)]; */
        rtb_ref_idx_0 = tunning_nominal_U.Y0[0];
        rtb_ref_idx_1 = tunning_nominal_U.Y0[1];
        rtb_ref_idx_2 = 1.0;
        rtb_ref_idx_3 = tunning_nominal_U.Y0[3];
      } else {
        /* '<S62>:1:17' else */
        /* '<S62>:1:18' ref = Y0; */
        rtb_ref_idx_0 = tunning_nominal_U.Y0[0];
        rtb_ref_idx_1 = tunning_nominal_U.Y0[1];
        rtb_ref_idx_2 = tunning_nominal_U.Y0[2];
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
      /* '<S62>:1:31' case 2      % circular tracking */
      /*  circular tracking */
      /* '<S62>:1:32' if t<=10 */
      if (rtb_Clock <= 10.0) {
        /* '<S62>:1:33' ref = [Y0(1); Y0(2); 0.75; Y0(4)]; */
        rtb_ref_idx_0 = tunning_nominal_U.Y0[0];
        rtb_ref_idx_1 = tunning_nominal_U.Y0[1];
        rtb_ref_idx_2 = 0.75;
        rtb_ref_idx_3 = tunning_nominal_U.Y0[3];
      } else if (rtb_Clock <= 50.0) {
        /* '<S62>:1:34' elseif t <= 50 */
        /* '<S62>:1:35' ref = [Y0(1)+cos(t); Y0(2)+sin(t); 0.75; Y0(4)]; */
        rtb_ref_idx_0 = tunning_nominal_U.Y0[0] + std::cos(rtb_Clock);
        rtb_ref_idx_1 = tunning_nominal_U.Y0[1] + std::sin(rtb_Clock);
        rtb_ref_idx_2 = 0.75;
        rtb_ref_idx_3 = tunning_nominal_U.Y0[3];
      } else if (rtb_Clock <= 60.0) {
        /* '<S62>:1:36' elseif t <= 60 */
        /* '<S62>:1:37' ref = [Y0(1); Y0(2); 0.75; Y0(4)]; */
        rtb_ref_idx_0 = tunning_nominal_U.Y0[0];
        rtb_ref_idx_1 = tunning_nominal_U.Y0[1];
        rtb_ref_idx_2 = 0.75;
        rtb_ref_idx_3 = tunning_nominal_U.Y0[3];
      } else {
        /* '<S62>:1:38' else */
        /* '<S62>:1:39' ref = Y0; */
        rtb_ref_idx_0 = tunning_nominal_U.Y0[0];
        rtb_ref_idx_1 = tunning_nominal_U.Y0[1];
        rtb_ref_idx_2 = tunning_nominal_U.Y0[2];
        rtb_ref_idx_3 = tunning_nominal_U.Y0[3];
      }

      /*          ref = [cos(t); sin(t);min(t,15);Y0(4)]; */
      break;

     default:
      /* '<S62>:1:42' otherwise */
      /* '<S62>:1:43' ref = Y0; */
      rtb_ref_idx_0 = tunning_nominal_U.Y0[0];
      rtb_ref_idx_1 = tunning_nominal_U.Y0[1];
      rtb_ref_idx_2 = tunning_nominal_U.Y0[2];
      rtb_ref_idx_3 = tunning_nominal_U.Y0[3];
      break;
    }

    /* End of MATLAB Function: '<S4>/MATLAB Function' */

    /* Outport: '<Root>/ref_out' */
    tunning_nominal_Y.ref_out[0] = rtb_ref_idx_0;
    tunning_nominal_Y.ref_out[1] = rtb_ref_idx_1;
    tunning_nominal_Y.ref_out[2] = rtb_ref_idx_2;
    tunning_nominal_Y.ref_out[3] = rtb_ref_idx_3;

    /* Outport: '<Root>/LOE_true' */
    for (i = 0; i < 6; i++) {
      tunning_nominal_Y.LOE_true[i] = rtb_LOE_out[i];
    }

    /* End of Outport: '<Root>/LOE_true' */
    if (rtmIsMajorTimeStep((&tunning_nominal_M)) &&
        (&tunning_nominal_M)->Timing.TaskCounters.TID[1] == 0) {
      /* Delay: '<S3>/MemoryX' */
      if (tunning_nominal_DW.icLoad != 0) {
        for (i = 0; i < 6; i++) {
          tunning_nominal_DW.MemoryX_DSTATE[i] = 0.0;
        }
      }

      /* Outputs for Atomic SubSystem: '<S3>/UseCurrentEstimator' */
      /* Outputs for Enabled SubSystem: '<S38>/Enabled Subsystem' incorporates:
       *  EnablePort: '<S59>/Enable'
       */
      if (!tunning_nominal_DW.EnabledSubsystem_MODE) {
        tunning_nominal_DW.EnabledSubsystem_MODE = true;
      }

      /* Sum: '<S59>/Add1' incorporates:
       *  Constant: '<S3>/C'
       *  Delay: '<S3>/MemoryX'
       *  Inport: '<Root>/X'
       *  Product: '<S59>/Product'
       *  Product: '<S59>/Product2'
       */
      for (i = 0; i < 3; i++) {
        u0 = 0.0;
        for (i_0 = 0; i_0 < 6; i_0++) {
          u0 += tunning_nominal_ConstP.C_Value[3 * i_0 + i] *
            tunning_nominal_DW.MemoryX_DSTATE[i_0];
        }

        rtb_ff[i] = tunning_nominal_U.X[9 + i] - u0;
      }

      /* End of Sum: '<S59>/Add1' */
      for (i = 0; i < 6; i++) {
        /* Product: '<S59>/Product2' incorporates:
         *  Constant: '<S15>/KalmanGainM'
         */
        tunning_nominal_B.Product2[i] = 0.0;
        tunning_nominal_B.Product2[i] +=
          tunning_nominal_ConstP.KalmanGainM_Value[i] * rtb_ff[0];
        tunning_nominal_B.Product2[i] +=
          tunning_nominal_ConstP.KalmanGainM_Value[i + 6] * rtb_ff[1];
        tunning_nominal_B.Product2[i] +=
          tunning_nominal_ConstP.KalmanGainM_Value[i + 12] * rtb_ff[2];

        /* Sum: '<S38>/Add' incorporates:
         *  Delay: '<S3>/MemoryX'
         */
        rtb_LOE_out[i] = tunning_nominal_B.Product2[i] +
          tunning_nominal_DW.MemoryX_DSTATE[i];
      }

      /* End of Outputs for SubSystem: '<S38>/Enabled Subsystem' */
      /* End of Outputs for SubSystem: '<S3>/UseCurrentEstimator' */

      /* Product: '<S2>/Product1' incorporates:
       *  Constant: '<S2>/Constant1'
       */
      for (i = 0; i < 3; i++) {
        rtb_Sum1_l[i] = tunning_nominal_ConstP.Constant1_Value[i + 6] *
          rtb_LOE_out[2] + (tunning_nominal_ConstP.Constant1_Value[i + 3] *
                            rtb_LOE_out[1] +
                            tunning_nominal_ConstP.Constant1_Value[i] *
                            rtb_LOE_out[0]);
      }

      /* End of Product: '<S2>/Product1' */

      /* Sum: '<S11>/Sum1' incorporates:
       *  Product: '<S13>/i x k'
       *  Product: '<S13>/j x i'
       *  Product: '<S13>/k x j'
       *  Product: '<S14>/i x j'
       *  Product: '<S14>/j x k'
       *  Product: '<S14>/k x i'
       */
      rtb_LOE_out_0[0] = rtb_LOE_out[1] * rtb_Sum1_l[2];
      rtb_LOE_out_0[1] = rtb_LOE_out[2] * rtb_Sum1_l[0];
      rtb_LOE_out_0[2] = rtb_LOE_out[0] * rtb_Sum1_l[1];
      rtb_LOE_out_1[0] = rtb_LOE_out[2] * rtb_Sum1_l[1];
      rtb_LOE_out_1[1] = rtb_LOE_out[0] * rtb_Sum1_l[2];
      rtb_LOE_out_1[2] = rtb_LOE_out[1] * rtb_Sum1_l[0];

      /* Sum: '<S2>/Sum3' incorporates:
       *  Constant: '<S2>/Constant'
       *  Constant: '<S2>/Constant1'
       *  Product: '<S2>/Product'
       *  Sum: '<S11>/Sum1'
       */
      for (i = 0; i < 3; i++) {
        rtb_ff[i] = (((tunning_nominal_ConstP.Constant1_Value[i + 3] *
                       rtb_LOE_out[4] + tunning_nominal_ConstP.Constant1_Value[i]
                       * rtb_LOE_out[3]) +
                      tunning_nominal_ConstP.Constant1_Value[i + 6] *
                      rtb_LOE_out[5]) +
                     tunning_nominal_ConstP.Constant_Value_g[i]) +
          (rtb_LOE_out_0[i] - rtb_LOE_out_1[i]);
      }

      /* End of Sum: '<S2>/Sum3' */

      /* MATLAB Function: '<S2>/MATLAB Function1' */
      /* MATLAB Function 'FDD_Kalman/MATLAB Function1': '<S12>:1' */
      /* '<S12>:1:2' arm = 0.215; */
      /* '<S12>:1:2' factor = 0.0365; */
      /* '<S12>:1:4' M = [arm/2 arm arm/2; */
      /* '<S12>:1:5'       -sqrt(3)*arm/2 0 sqrt(3)*arm/2; */
      /* '<S12>:1:6'       -factor factor -factor]; */
      /* '<S12>:1:8' diff = [u(1) - u(4) ; */
      /* '<S12>:1:9'         u(2) - u(5) ; */
      /* '<S12>:1:10'         u(3) - u(6) ]; */
      /* '<S12>:1:11' Residu = diff - M\y; */
      rtb_Sum1_l[1] = rtb_ff[0] - rtb_ff[1] * -0.57735026918962584;
      rtb_Sum1_l[2] = (rtb_ff[2] - rtb_ff[1] * 0.19603055651554735) -
        rtb_Sum1_l[1] * 0.16976744186046511;
      rtb_Sum1_l[2] /= -0.10949999999999999;
      rtb_Sum1_l[0] = rtb_ff[1] - rtb_Sum1_l[2] * 0.18619546181365429;
      rtb_Sum1_l[1] -= rtb_Sum1_l[2] * 0.215;
      rtb_Sum1_l[1] /= 0.215;
      rtb_Sum1_l[0] -= rtb_Sum1_l[1] * 0.0;
      rtb_Sum1_l[0] /= -0.18619546181365429;

      /* Outport: '<Root>/LOE13_estimated' incorporates:
       *  MATLAB Function: '<S2>/MATLAB Function1'
       *  Memory: '<S2>/Memory'
       */
      /*  Residu_1_4 */
      /* '<S12>:1:14' gamma    = [Residu(1)/u(1) */
      /* '<S12>:1:15'             Residu(2)/u(2) */
      /* '<S12>:1:16'             Residu(3)/u(3)]; */
      tunning_nominal_Y.LOE13_estimated[0] =
        ((tunning_nominal_DW.Memory_PreviousInput[0] -
          tunning_nominal_DW.Memory_PreviousInput[3]) - rtb_Sum1_l[0]) /
        tunning_nominal_DW.Memory_PreviousInput[0];
      tunning_nominal_Y.LOE13_estimated[1] =
        ((tunning_nominal_DW.Memory_PreviousInput[1] -
          tunning_nominal_DW.Memory_PreviousInput[4]) - rtb_Sum1_l[1]) /
        tunning_nominal_DW.Memory_PreviousInput[1];
      tunning_nominal_Y.LOE13_estimated[2] =
        ((tunning_nominal_DW.Memory_PreviousInput[2] -
          tunning_nominal_DW.Memory_PreviousInput[5]) - rtb_Sum1_l[2]) /
        tunning_nominal_DW.Memory_PreviousInput[2];

      /* Outputs for Enabled SubSystem: '<S33>/MeasurementUpdate' incorporates:
       *  EnablePort: '<S58>/Enable'
       */
      if (rtmIsMajorTimeStep((&tunning_nominal_M)) &&
          (!tunning_nominal_DW.MeasurementUpdate_MODE)) {
        tunning_nominal_DW.MeasurementUpdate_MODE = true;
      }

      if (tunning_nominal_DW.MeasurementUpdate_MODE) {
        for (i = 0; i < 3; i++) {
          /* Product: '<S58>/C[k]*xhat[k|k-1]' incorporates:
           *  Constant: '<S3>/C'
           *  Delay: '<S3>/MemoryX'
           *  Sum: '<S58>/Add1'
           */
          rtb_ff[i] = 0.0;
          for (i_0 = 0; i_0 < 6; i_0++) {
            rtb_ff[i] += tunning_nominal_ConstP.C_Value[3 * i_0 + i] *
              tunning_nominal_DW.MemoryX_DSTATE[i_0];
          }

          /* End of Product: '<S58>/C[k]*xhat[k|k-1]' */

          /* Sum: '<S58>/Sum' incorporates:
           *  Inport: '<Root>/X'
           *  Product: '<S58>/Product3'
           *  Sum: '<S58>/Add1'
           */
          rtb_Sum1_l[i] = tunning_nominal_U.X[9 + i] - rtb_ff[i];
        }

        /* Product: '<S58>/Product3' incorporates:
         *  Constant: '<S15>/KalmanGainL'
         */
        for (i = 0; i < 6; i++) {
          tunning_nominal_B.Product3[i] = 0.0;
          tunning_nominal_B.Product3[i] +=
            tunning_nominal_ConstP.KalmanGainL_Value[i] * rtb_Sum1_l[0];
          tunning_nominal_B.Product3[i] +=
            tunning_nominal_ConstP.KalmanGainL_Value[i + 6] * rtb_Sum1_l[1];
          tunning_nominal_B.Product3[i] +=
            tunning_nominal_ConstP.KalmanGainL_Value[i + 12] * rtb_Sum1_l[2];
        }
      }

      /* End of Outputs for SubSystem: '<S33>/MeasurementUpdate' */
      for (i = 0; i < 6; i++) {
        /* Product: '<S33>/A[k]*xhat[k|k-1]' incorporates:
         *  Constant: '<S3>/A'
         *  Delay: '<S3>/MemoryX'
         *  Sum: '<S33>/Add'
         */
        rtb_LOE_out[i] = 0.0;
        for (i_0 = 0; i_0 < 6; i_0++) {
          rtb_LOE_out[i] += tunning_nominal_ConstP.A_Value[6 * i_0 + i] *
            tunning_nominal_DW.MemoryX_DSTATE[i_0];
        }

        /* End of Product: '<S33>/A[k]*xhat[k|k-1]' */

        /* Sum: '<S33>/Add' */
        rtb_Add[i] = rtb_LOE_out[i] + tunning_nominal_B.Product3[i];
      }
    }

    /* Sum: '<S4>/Sum' incorporates:
     *  Inport: '<Root>/Y0'
     */
    rtb_ref_idx_0 -= tunning_nominal_U.Y0[0];
    rtb_ref_idx_1 -= tunning_nominal_U.Y0[1];
    rtb_ref_idx_2 -= tunning_nominal_U.Y0[2];
    rtb_Clock = rtb_ref_idx_3 - tunning_nominal_U.Y0[3];

    /* Saturate: '<S6>/x' */
    if (rtb_ref_idx_0 > 2.0) {
      rtb_ref_idx_0 = 2.0;
    } else {
      if (rtb_ref_idx_0 < -2.0) {
        rtb_ref_idx_0 = -2.0;
      }
    }

    /* End of Saturate: '<S6>/x' */

    /* Sum: '<S6>/Sum1' */
    tunning_nominal_B.Sum1 = rtb_ref_idx_0 - axref_N;

    /* Saturate: '<S6>/y' */
    if (rtb_ref_idx_1 > 2.0) {
      rtb_ref_idx_1 = 2.0;
    } else {
      if (rtb_ref_idx_1 < -2.0) {
        rtb_ref_idx_1 = -2.0;
      }
    }

    /* End of Saturate: '<S6>/y' */

    /* Sum: '<S6>/Sum4' */
    tunning_nominal_B.Sum4 = rtb_ref_idx_1 - ayref_N;

    /* Saturate: '<S9>/yaw' */
    if (rtb_Clock > 3.1415926535897931) {
      rtb_Clock = 3.1415926535897931;
    } else {
      if (rtb_Clock < -3.1415926535897931) {
        rtb_Clock = -3.1415926535897931;
      }
    }

    /* End of Saturate: '<S9>/yaw' */

    /* Sum: '<S9>/Sum3' */
    tunning_nominal_B.Sum3_n = rtb_Clock - rtb_d_psi;

    /* Saturate: '<S10>/z' */
    if (rtb_ref_idx_2 > 1.75) {
      rtb_ref_idx_2 = 1.75;
    } else {
      if (rtb_ref_idx_2 < 0.0) {
        rtb_ref_idx_2 = 0.0;
      }
    }

    /* End of Saturate: '<S10>/z' */

    /* Sum: '<S10>/Sum3' */
    tunning_nominal_B.Sum3_h = rtb_ref_idx_2 - rtb_d_z;
  }

  if (rtmIsMajorTimeStep((&tunning_nominal_M))) {
    int32_T i;
    if (rtmIsMajorTimeStep((&tunning_nominal_M)) &&
        (&tunning_nominal_M)->Timing.TaskCounters.TID[1] == 0) {
      /* Update for Delay: '<S3>/MemoryX' */
      tunning_nominal_DW.icLoad = 0U;
      for (i = 0; i < 6; i++) {
        /* Update for Memory: '<S2>/Memory' */
        tunning_nominal_DW.Memory_PreviousInput[i] = tunning_nominal_B.u[i];

        /* Update for Delay: '<S3>/MemoryX' */
        tunning_nominal_DW.MemoryX_DSTATE[i] = rtb_Add[i];
      }
    }
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

  /* Derivatives for Integrator: '<S10>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = tunning_nominal_B.Sum3_h;

  /* Derivatives for Integrator: '<S6>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_d = tunning_nominal_B.Sum1;

  /* Derivatives for Integrator: '<S6>/Integrator' */
  _rtXdot->Integrator_CSTATE = tunning_nominal_B.Sum4;

  /* Derivatives for Integrator: '<S9>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_j = tunning_nominal_B.Sum3_n;
}

/* Model initialize function */
void tunning_nominalModelClass::initialize()
{
  /* Registration code */

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

    /* InitializeConditions for Integrator: '<S10>/Integrator1' */
    tunning_nominal_X.Integrator1_CSTATE = 0.0;

    /* InitializeConditions for Integrator: '<S6>/Integrator1' */
    tunning_nominal_X.Integrator1_CSTATE_d = 0.0;

    /* InitializeConditions for Integrator: '<S6>/Integrator' */
    tunning_nominal_X.Integrator_CSTATE = 0.0;

    /* InitializeConditions for Integrator: '<S9>/Integrator1' */
    tunning_nominal_X.Integrator1_CSTATE_j = 0.0;

    /* InitializeConditions for Delay: '<S3>/MemoryX' */
    tunning_nominal_DW.icLoad = 1U;

    /* SystemInitialize for Enabled SubSystem: '<S33>/MeasurementUpdate' */
    /* SystemInitialize for Atomic SubSystem: '<S3>/UseCurrentEstimator' */
    /* SystemInitialize for Enabled SubSystem: '<S38>/Enabled Subsystem' */
    for (i = 0; i < 6; i++) {
      /* InitializeConditions for Memory: '<S2>/Memory' */
      tunning_nominal_DW.Memory_PreviousInput[i] = 2.5179000000000005;

      /* SystemInitialize for Outport: '<S59>/deltax' */
      tunning_nominal_B.Product2[i] = 0.0;

      /* SystemInitialize for Outport: '<S58>/L*(y[k]-yhat[k|k-1])' */
      tunning_nominal_B.Product3[i] = 0.0;
    }

    /* End of SystemInitialize for SubSystem: '<S38>/Enabled Subsystem' */
    /* End of SystemInitialize for SubSystem: '<S3>/UseCurrentEstimator' */
    /* End of SystemInitialize for SubSystem: '<S33>/MeasurementUpdate' */
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
