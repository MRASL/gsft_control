/*
 * tuning_nominal.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "tuning_nominal".
 *
 * Model version              : 1.1507
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Mon Jul 15 09:42:31 2019
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Passed (1), Warnings (3), Error (0)
 */

#include "tuning_nominal.h"
#include "tuning_nominal_private.h"

static void rate_scheduler(RT_MODEL_tuning_nominal_T *const tuning_nominal_M);

/*
 *   This function updates active task flag for each subrate.
 * The function is called at model base rate, hence the
 * generated code self-manages all its subrates.
 */
static void rate_scheduler(RT_MODEL_tuning_nominal_T *const tuning_nominal_M)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (tuning_nominal_M->Timing.TaskCounters.TID[2])++;
  if ((tuning_nominal_M->Timing.TaskCounters.TID[2]) > 4) {/* Sample time: [0.005s, 0.0s] */
    tuning_nominal_M->Timing.TaskCounters.TID[2] = 0;
  }
}

/*
 * This function updates continuous states using the ODE4 fixed-step
 * solver algorithm
 */
void tuning_nominalModelClass::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si
  )
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
  tuning_nominal_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  this->step();
  tuning_nominal_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  this->step();
  tuning_nominal_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  this->step();
  tuning_nominal_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void tuning_nominalModelClass::step()
{
  /* local block i/o variables */
  real_T rtb_Add[6];
  if (rtmIsMajorTimeStep((&tuning_nominal_M))) {
    /* set solver stop time */
    if (!((&tuning_nominal_M)->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&(&tuning_nominal_M)->solverInfo,
                            (((&tuning_nominal_M)->Timing.clockTickH0 + 1) *
        (&tuning_nominal_M)->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&(&tuning_nominal_M)->solverInfo,
                            (((&tuning_nominal_M)->Timing.clockTick0 + 1) *
        (&tuning_nominal_M)->Timing.stepSize0 + (&tuning_nominal_M)
        ->Timing.clockTickH0 * (&tuning_nominal_M)->Timing.stepSize0 *
        4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep((&tuning_nominal_M))) {
    (&tuning_nominal_M)->Timing.t[0] = rtsiGetT(&(&tuning_nominal_M)->solverInfo);
  }

  {
    real_T rtb_d_z;
    real_T rtb_d_x;
    real_T rtb_d_y;
    real_T rtb_d_psi;
    real_T rtb_T_f[6];
    real_T rtb_LOE_out[6];
    real_T rtb_Sum1_l[3];
    real_T rtb_Add_a[6];
    real_T rtb_Sum3_i[3];
    real_T rtb_Clock;
    real_T rtb_MemoryX[6];
    int32_T i;
    real_T rtb_Add_f[3];
    real_T rtb_Add_f_0[3];
    int32_T i_0;
    real_T rtb_ref_idx_3;
    real_T rtb_ref_idx_0;
    real_T rtb_ff_idx_1;
    real_T rtb_ff_idx_0;
    real_T u0;

    /* Sum: '<S5>/Sum5' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/Y0'
     */
    rtb_d_z = tuning_nominal_U.X[2] - tuning_nominal_U.Y0[2];

    /* Sum: '<S5>/Sum1' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/Y0'
     */
    rtb_d_x = tuning_nominal_U.X[0] - tuning_nominal_U.Y0[0];

    /* Sum: '<S56>/Sum2' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/gain'
     *  Integrator: '<S56>/Integrator1'
     *  Product: '<S56>/Product2'
     *  Product: '<S56>/Product3'
     *  SignalConversion: '<S56>/TmpSignal ConversionAtProduct3Inport2'
     */
    tuning_nominal_B.Sum2 = tuning_nominal_U.gain[2] *
      tuning_nominal_X.Integrator1_CSTATE_f - (tuning_nominal_U.gain[0] *
      rtb_d_x + tuning_nominal_U.gain[1] * tuning_nominal_U.X[3]);

    /* Sum: '<S5>/Sum4' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/Y0'
     */
    rtb_d_y = tuning_nominal_U.X[1] - tuning_nominal_U.Y0[1];

    /* Sum: '<S56>/Sum3' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/gain'
     *  Integrator: '<S56>/Integrator'
     *  Product: '<S56>/Product1'
     *  Product: '<S56>/Product4'
     *  SignalConversion: '<S56>/TmpSignal ConversionAtProduct1Inport2'
     */
    tuning_nominal_B.Sum3 = tuning_nominal_U.gain[5] *
      tuning_nominal_X.Integrator_CSTATE - (tuning_nominal_U.gain[3] * rtb_d_y +
      tuning_nominal_U.gain[4] * tuning_nominal_U.X[4]);

    /* RateTransition: '<S4>/T_outer' incorporates:
     *  Inport: '<Root>/X'
     */
    if ((rtmIsMajorTimeStep((&tuning_nominal_M)) &&
         (&tuning_nominal_M)->Timing.TaskCounters.TID[1] == 0) &&
        (rtmIsMajorTimeStep((&tuning_nominal_M)) &&
         (&tuning_nominal_M)->Timing.TaskCounters.TID[2] == 0)) {
      tuning_nominal_B.T_outer[0] = tuning_nominal_B.Sum2;
      tuning_nominal_B.T_outer[1] = tuning_nominal_B.Sum3;
      tuning_nominal_B.T_outer[2] = tuning_nominal_U.X[8];
    }

    /* End of RateTransition: '<S4>/T_outer' */
    if (rtmIsMajorTimeStep((&tuning_nominal_M)) &&
        (&tuning_nominal_M)->Timing.TaskCounters.TID[2] == 0) {
      /* Fcn: '<S4>/Fcn1' */
      tuning_nominal_B.Fcn1 = tuning_nominal_B.T_outer[1] * std::cos
        (tuning_nominal_B.T_outer[2]) + tuning_nominal_B.T_outer[0] * std::sin
        (tuning_nominal_B.T_outer[2]);
    }

    /* Clock: '<Root>/Clock' */
    rtb_Clock = (&tuning_nominal_M)->Timing.t[0];

    /* MATLAB Function: '<S5>/FFW' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/mode'
     */
    /* MATLAB Function 'Test_config_and_data/FFW': '<S61>:1' */
    /* '<S61>:1:2' ff = [0;0]; */
    rtb_ff_idx_0 = 0.0;
    rtb_ff_idx_1 = 0.0;

    /* '<S61>:1:3' g = 9.81; */
    /*  [x;y] = [cos(t); sin(t)] */
    /* '<S61>:1:5' if (test_mode == 2) */
    if ((tuning_nominal_U.mode == 2.0) && ((rtb_Clock >= 10.0) && (rtb_Clock <=
          50.0))) {
      /* '<S61>:1:6' if (t >=10) && (t<= 50) */
      /* '<S61>:1:7' axref_N = -cos(t); */
      /* '<S61>:1:8' ayref_N = -sin(t); */
      /* '<S61>:1:10' axref_b = cos(X(8))*cos(X(9))*axref_N + cos(X(8))*sin(X(9))*ayref_N; */
      /* '<S61>:1:11' ayref_b = (sin(X(7))*sin(X(8))*cos(X(9)) - cos(X(7))*sin(X(9)))*axref_N + (sin(X(7))*sin(X(8))*sin(X(9)) + cos(X(7))*cos(X(9)))*ayref_N; */
      /*  azref_b = (cos(X(7))*sin(X(8))*cos(X(9)) + sin(X(7))*sin(X(9)))*axref_N + (cos(X(7))*sin(X(8))*sin(X(9)) - sin(X(7))*cos(X(9)))*ayref_N; */
      /*   */
      /* '<S61>:1:14' ff = [-ayref_b/g; axref_b/g]; */
      rtb_ff_idx_0 = -((std::sin(tuning_nominal_U.X[6]) * std::sin
                        (tuning_nominal_U.X[7]) * std::cos(tuning_nominal_U.X[8])
                        - std::cos(tuning_nominal_U.X[6]) * std::sin
                        (tuning_nominal_U.X[8])) * -std::cos(rtb_Clock) + (std::
        sin(tuning_nominal_U.X[6]) * std::sin(tuning_nominal_U.X[7]) * std::sin
        (tuning_nominal_U.X[8]) + std::cos(tuning_nominal_U.X[6]) * std::cos
        (tuning_nominal_U.X[8])) * -std::sin(rtb_Clock)) / 9.81;
      rtb_ff_idx_1 = (std::cos(tuning_nominal_U.X[7]) * std::cos
                      (tuning_nominal_U.X[8]) * -std::cos(rtb_Clock) + std::cos
                      (tuning_nominal_U.X[7]) * std::sin(tuning_nominal_U.X[8]) *
                      -std::sin(rtb_Clock)) / 9.81;
    } else {
      /* '<S61>:1:15' else */
      /* '<S61>:1:16' ff = [0;0]; */
    }

    /* End of MATLAB Function: '<S5>/FFW' */
    if (rtmIsMajorTimeStep((&tuning_nominal_M)) &&
        (&tuning_nominal_M)->Timing.TaskCounters.TID[2] == 0) {
      /* Fcn: '<S4>/Fcn' */
      tuning_nominal_B.Fcn = -tuning_nominal_B.T_outer[1] * std::sin
        (tuning_nominal_B.T_outer[2]) + tuning_nominal_B.T_outer[0] * std::cos
        (tuning_nominal_B.T_outer[2]);
    }

    /* Sum: '<S5>/Sum6' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/Y0'
     */
    rtb_d_psi = tuning_nominal_U.X[8] - tuning_nominal_U.Y0[3];

    /* SignalConversion: '<Root>/TmpSignal ConversionAtControl AllocationInport1' incorporates:
     *  Constant: '<S4>/                     '
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/gain'
     *  Integrator: '<S60>/Integrator1'
     *  Product: '<S60>/Product'
     *  Product: '<S60>/Product1'
     *  SignalConversion: '<S60>/TmpSignal ConversionAtProduct1Inport2'
     *  Sum: '<S4>/Sum1'
     *  Sum: '<S60>/Sum1'
     */
    rtb_ref_idx_0 = (tuning_nominal_U.gain[8] *
                     tuning_nominal_X.Integrator1_CSTATE -
                     (tuning_nominal_U.gain[6] * rtb_d_z +
                      tuning_nominal_U.gain[7] * tuning_nominal_U.X[5])) +
      15.107400000000002;

    /* Saturate: '<S4>/2Nm ' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/gain'
     *  Product: '<S58>/Product'
     *  SignalConversion: '<S58>/TmpSignal ConversionAtProductInport2'
     *  Sum: '<S4>/Sum7'
     *  Sum: '<S58>/Sum1'
     */
    rtb_ff_idx_0 = (tuning_nominal_B.Fcn1 + rtb_ff_idx_0) -
      (tuning_nominal_U.gain[9] * tuning_nominal_U.X[6] + tuning_nominal_U.gain
       [10] * tuning_nominal_U.X[9]);
    if (rtb_ff_idx_0 > 2.0) {
      /* SignalConversion: '<Root>/TmpSignal ConversionAtControl AllocationInport1' */
      rtb_ff_idx_0 = 2.0;
    } else {
      if (rtb_ff_idx_0 < -2.0) {
        /* SignalConversion: '<Root>/TmpSignal ConversionAtControl AllocationInport1' */
        rtb_ff_idx_0 = -2.0;
      }
    }

    /* End of Saturate: '<S4>/2Nm ' */

    /* Saturate: '<S4>/2Nm' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/gain'
     *  Product: '<S57>/Product'
     *  SignalConversion: '<S57>/TmpSignal ConversionAtProductInport2'
     *  Sum: '<S4>/Sum8'
     *  Sum: '<S57>/Sum1'
     */
    rtb_ff_idx_1 = (tuning_nominal_B.Fcn + rtb_ff_idx_1) -
      (tuning_nominal_U.gain[12] * tuning_nominal_U.X[7] +
       tuning_nominal_U.gain[13] * tuning_nominal_U.X[10]);
    if (rtb_ff_idx_1 > 2.0) {
      /* SignalConversion: '<Root>/TmpSignal ConversionAtControl AllocationInport1' */
      rtb_ff_idx_1 = 2.0;
    } else {
      if (rtb_ff_idx_1 < -2.0) {
        /* SignalConversion: '<Root>/TmpSignal ConversionAtControl AllocationInport1' */
        rtb_ff_idx_1 = -2.0;
      }
    }

    /* End of Saturate: '<S4>/2Nm' */

    /* Saturate: '<S4>/1Nm' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/gain'
     *  Integrator: '<S59>/Integrator1'
     *  Product: '<S59>/Product'
     *  Product: '<S59>/Product1'
     *  SignalConversion: '<S59>/TmpSignal ConversionAtProduct1Inport2'
     *  Sum: '<S59>/Sum1'
     */
    rtb_ref_idx_3 = tuning_nominal_U.gain[17] *
      tuning_nominal_X.Integrator1_CSTATE_a - (tuning_nominal_U.gain[15] *
      rtb_d_psi + tuning_nominal_U.gain[16] * tuning_nominal_U.X[11]);
    if (rtb_ref_idx_3 > 1.0) {
      /* SignalConversion: '<Root>/TmpSignal ConversionAtControl AllocationInport1' */
      rtb_ref_idx_3 = 1.0;
    } else {
      if (rtb_ref_idx_3 < -1.0) {
        /* SignalConversion: '<Root>/TmpSignal ConversionAtControl AllocationInport1' */
        rtb_ref_idx_3 = -1.0;
      }
    }

    /* End of Saturate: '<S4>/1Nm' */
    /* MATLAB Function 'Test_config_and_data/LOE_': '<S62>:1' */
    /* '<S62>:1:2' LOE_out = [0;0;0;0;0;0]; */
    /* '<S62>:1:3' for i = 1:6 */
    for (i = 0; i < 6; i++) {
      /* Gain: '<Root>/Control Allocation' incorporates:
       *  Saturate: '<Root>/                  '
       */
      u0 = tuning_nominal_ConstP.ControlAllocation_Gain[i + 18] * rtb_ref_idx_3
        + (tuning_nominal_ConstP.ControlAllocation_Gain[i + 12] * rtb_ff_idx_1 +
           (tuning_nominal_ConstP.ControlAllocation_Gain[i + 6] * rtb_ff_idx_0 +
            tuning_nominal_ConstP.ControlAllocation_Gain[i] * rtb_ref_idx_0));

      /* Saturate: '<Root>/                  ' incorporates:
       *  Gain: '<Root>/Control Allocation'
       */
      if (u0 > 8.54858) {
        tuning_nominal_B.u[i] = 8.54858;
      } else if (u0 < 0.0) {
        tuning_nominal_B.u[i] = 0.0;
      } else {
        tuning_nominal_B.u[i] = u0;
      }

      /* MATLAB Function: '<S5>/LOE_' incorporates:
       *  Inport: '<Root>/LOE_a'
       *  Inport: '<Root>/LOE_t'
       */
      rtb_LOE_out[i] = 0.0;

      /* '<S62>:1:4' if t>= LOE_t(i) */
      if (rtb_Clock >= tuning_nominal_U.LOE_t[i]) {
        /* '<S62>:1:5' LOE_out(i) = LOE(i); */
        rtb_LOE_out[i] = tuning_nominal_U.LOE_a[i];
      }

      /* End of MATLAB Function: '<S5>/LOE_' */
    }

    /* MATLAB Function: '<Root>/Actuator_Fault' */
    /* MATLAB Function 'Actuator_Fault': '<S1>:1' */
    /* '<S1>:1:2' T1 = T(1)*(1-LOE(1)); */
    /* '<S1>:1:3' T2 = T(2)*(1-LOE(2)); */
    /* '<S1>:1:4' T3 = T(3)*(1-LOE(3)); */
    /* '<S1>:1:5' T4 = T(4)*(1-LOE(4)); */
    /* '<S1>:1:6' T5 = T(5)*(1-LOE(5)); */
    /* '<S1>:1:7' T6 = T(6)*(1-LOE(6)); */
    /* '<S1>:1:8' T_f = [T1;T2;T3;T4;T5;T6]; */
    rtb_T_f[0] = (1.0 - rtb_LOE_out[0]) * tuning_nominal_B.u[0];
    rtb_T_f[1] = (1.0 - rtb_LOE_out[1]) * tuning_nominal_B.u[1];
    rtb_T_f[2] = (1.0 - rtb_LOE_out[2]) * tuning_nominal_B.u[2];
    rtb_T_f[3] = (1.0 - rtb_LOE_out[3]) * tuning_nominal_B.u[3];
    rtb_T_f[4] = (1.0 - rtb_LOE_out[4]) * tuning_nominal_B.u[4];
    rtb_T_f[5] = (1.0 - rtb_LOE_out[5]) * tuning_nominal_B.u[5];

    /* Outport: '<Root>/motor_command' */
    for (i = 0; i < 6; i++) {
      /* Gain: '<S6>/mapping_0_200' incorporates:
       *  Gain: '<S6>/      '
       *  Gain: '<S6>/rads_to_RPM'
       *  Sqrt: '<S6>/Sqrt1'
       *  Sum: '<S6>/Sum3'
       */
      u0 = (std::sqrt(116978.4923343994 * rtb_T_f[i]) * 9.5493 - 1250.0) *
        0.022857142857142857;

      /* Saturate: '<S6>/Saturation' */
      if (u0 > 200.0) {
        tuning_nominal_Y.motor_command[i] = 200.0;
      } else if (u0 < 0.0) {
        tuning_nominal_Y.motor_command[i] = 0.0;
      } else {
        tuning_nominal_Y.motor_command[i] = u0;
      }

      /* End of Saturate: '<S6>/Saturation' */
    }

    /* End of Outport: '<Root>/motor_command' */

    /* Outport: '<Root>/virtual_control' */
    tuning_nominal_Y.virtual_control[0] = rtb_ref_idx_0;
    tuning_nominal_Y.virtual_control[1] = rtb_ff_idx_0;
    tuning_nominal_Y.virtual_control[2] = rtb_ff_idx_1;
    tuning_nominal_Y.virtual_control[3] = rtb_ref_idx_3;

    /* MATLAB Function: '<S5>/MATLAB Function' incorporates:
     *  Inport: '<Root>/Y0'
     *  Inport: '<Root>/mode'
     *  Inport: '<Root>/ref'
     */
    /* MATLAB Function 'Test_config_and_data/MATLAB Function': '<S63>:1' */
    /* '<S63>:1:2' ref = Y0; */
    /* '<S63>:1:3' switch test_mode */
    switch ((int32_T)tuning_nominal_U.mode) {
     case 0:
      /* '<S63>:1:4' case 0      % manual test */
      /*  manual test */
      /* '<S63>:1:5' ref = ref_manual; */
      rtb_ref_idx_0 = tuning_nominal_U.ref[0];
      rtb_ff_idx_0 = tuning_nominal_U.ref[1];
      rtb_ff_idx_1 = tuning_nominal_U.ref[2];
      rtb_ref_idx_3 = tuning_nominal_U.ref[3];

      /* '<S63>:1:6' if t>=25 */
      if (rtb_Clock >= 25.0) {
        /* '<S63>:1:7' ref = Y0; */
        rtb_ref_idx_0 = tuning_nominal_U.Y0[0];
        rtb_ff_idx_0 = tuning_nominal_U.Y0[1];
        rtb_ff_idx_1 = tuning_nominal_U.Y0[2];
        rtb_ref_idx_3 = tuning_nominal_U.Y0[3];
      }
      break;

     case 1:
      /* '<S63>:1:9' case 1      % waypoint */
      /*  waypoint */
      /* '<S63>:1:10' if t<=15 */
      if (rtb_Clock <= 15.0) {
        /* '<S63>:1:11' ref = [Y0(1); Y0(2); 1; Y0(4)]; */
        rtb_ref_idx_0 = tuning_nominal_U.Y0[0];
        rtb_ff_idx_0 = tuning_nominal_U.Y0[1];
        rtb_ff_idx_1 = 1.0;
        rtb_ref_idx_3 = tuning_nominal_U.Y0[3];
      } else if (rtb_Clock <= 25.0) {
        /* '<S63>:1:12' elseif t <= 25 */
        /* '<S63>:1:13' ref = [Y0(1)+1; Y0(2)-1; 1; Y0(4)]; */
        rtb_ref_idx_0 = tuning_nominal_U.Y0[0] + 1.0;
        rtb_ff_idx_0 = tuning_nominal_U.Y0[1] - 1.0;
        rtb_ff_idx_1 = 1.0;
        rtb_ref_idx_3 = tuning_nominal_U.Y0[3];
      } else if (rtb_Clock <= 35.0) {
        /* '<S63>:1:14' elseif t <=35 */
        /* '<S63>:1:15' ref = [Y0(1)-1; Y0(2)+1; 1; Y0(4)]; */
        rtb_ref_idx_0 = tuning_nominal_U.Y0[0] - 1.0;
        rtb_ff_idx_0 = tuning_nominal_U.Y0[1] + 1.0;
        rtb_ff_idx_1 = 1.0;
        rtb_ref_idx_3 = tuning_nominal_U.Y0[3];
      } else if (rtb_Clock <= 45.0) {
        /* '<S63>:1:16' elseif t <=45 */
        /* '<S63>:1:17' ref = [Y0(1)-1; Y0(2)+1; 1; Y0(4)]; */
        rtb_ref_idx_0 = tuning_nominal_U.Y0[0] - 1.0;
        rtb_ff_idx_0 = tuning_nominal_U.Y0[1] + 1.0;
        rtb_ff_idx_1 = 1.0;
        rtb_ref_idx_3 = tuning_nominal_U.Y0[3];
      } else if (rtb_Clock <= 55.0) {
        /* '<S63>:1:18' elseif t <=55 */
        /* '<S63>:1:19' ref = [Y0(1); Y0(2); 1; Y0(4)]; */
        rtb_ref_idx_0 = tuning_nominal_U.Y0[0];
        rtb_ff_idx_0 = tuning_nominal_U.Y0[1];
        rtb_ff_idx_1 = 1.0;
        rtb_ref_idx_3 = tuning_nominal_U.Y0[3];
      } else {
        /* '<S63>:1:20' else */
        /* '<S63>:1:21' ref = Y0; */
        rtb_ref_idx_0 = tuning_nominal_U.Y0[0];
        rtb_ff_idx_0 = tuning_nominal_U.Y0[1];
        rtb_ff_idx_1 = tuning_nominal_U.Y0[2];
        rtb_ref_idx_3 = tuning_nominal_U.Y0[3];
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
      /* '<S63>:1:34' case 2      % circular tracking */
      /*  circular tracking */
      /* '<S63>:1:35' if t<=10 */
      if (rtb_Clock <= 10.0) {
        /* '<S63>:1:36' ref = [Y0(1); Y0(2); 0.75; Y0(4)]; */
        rtb_ref_idx_0 = tuning_nominal_U.Y0[0];
        rtb_ff_idx_0 = tuning_nominal_U.Y0[1];
        rtb_ff_idx_1 = 0.75;
        rtb_ref_idx_3 = tuning_nominal_U.Y0[3];
      } else if (rtb_Clock <= 50.0) {
        /* '<S63>:1:37' elseif t <= 50 */
        /* '<S63>:1:38' ref = [Y0(1)+cos(t); Y0(2)+sin(t); 0.75; Y0(4)]; */
        rtb_ref_idx_0 = tuning_nominal_U.Y0[0] + std::cos(rtb_Clock);
        rtb_ff_idx_0 = tuning_nominal_U.Y0[1] + std::sin(rtb_Clock);
        rtb_ff_idx_1 = 0.75;
        rtb_ref_idx_3 = tuning_nominal_U.Y0[3];
      } else if (rtb_Clock <= 60.0) {
        /* '<S63>:1:39' elseif t <= 60 */
        /* '<S63>:1:40' ref = [Y0(1); Y0(2); 0.75; Y0(4)]; */
        rtb_ref_idx_0 = tuning_nominal_U.Y0[0];
        rtb_ff_idx_0 = tuning_nominal_U.Y0[1];
        rtb_ff_idx_1 = 0.75;
        rtb_ref_idx_3 = tuning_nominal_U.Y0[3];
      } else {
        /* '<S63>:1:41' else */
        /* '<S63>:1:42' ref = Y0; */
        rtb_ref_idx_0 = tuning_nominal_U.Y0[0];
        rtb_ff_idx_0 = tuning_nominal_U.Y0[1];
        rtb_ff_idx_1 = tuning_nominal_U.Y0[2];
        rtb_ref_idx_3 = tuning_nominal_U.Y0[3];
      }

      /*          ref = [cos(t); sin(t);min(t,15);Y0(4)]; */
      break;

     default:
      /* '<S63>:1:45' otherwise */
      /* '<S63>:1:46' ref = Y0; */
      rtb_ref_idx_0 = tuning_nominal_U.Y0[0];
      rtb_ff_idx_0 = tuning_nominal_U.Y0[1];
      rtb_ff_idx_1 = tuning_nominal_U.Y0[2];
      rtb_ref_idx_3 = tuning_nominal_U.Y0[3];
      break;
    }

    /* End of MATLAB Function: '<S5>/MATLAB Function' */

    /* Outport: '<Root>/ref_out' */
    tuning_nominal_Y.ref_out[0] = rtb_ref_idx_0;
    tuning_nominal_Y.ref_out[1] = rtb_ff_idx_0;
    tuning_nominal_Y.ref_out[2] = rtb_ff_idx_1;
    tuning_nominal_Y.ref_out[3] = rtb_ref_idx_3;

    /* Outport: '<Root>/LOE_true' */
    for (i = 0; i < 6; i++) {
      tuning_nominal_Y.LOE_true[i] = rtb_LOE_out[i];
    }

    /* End of Outport: '<Root>/LOE_true' */
    if (rtmIsMajorTimeStep((&tuning_nominal_M)) &&
        (&tuning_nominal_M)->Timing.TaskCounters.TID[1] == 0) {
      /* Delay: '<S3>/MemoryX' */
      for (i = 0; i < 6; i++) {
        if (tuning_nominal_DW.icLoad != 0) {
          tuning_nominal_DW.MemoryX_DSTATE[i] = 0.0;
        }

        rtb_MemoryX[i] = tuning_nominal_DW.MemoryX_DSTATE[i];
      }

      /* Outputs for Atomic SubSystem: '<S3>/UseCurrentEstimator' */
      /* Outputs for Enabled SubSystem: '<S34>/Enabled Subsystem' incorporates:
       *  EnablePort: '<S55>/Enable'
       */
      if (!tuning_nominal_DW.EnabledSubsystem_MODE) {
        tuning_nominal_DW.EnabledSubsystem_MODE = true;
      }

      /* Sum: '<S55>/Add1' incorporates:
       *  Constant: '<S3>/C'
       *  Delay: '<S3>/MemoryX'
       *  Inport: '<Root>/X'
       *  Product: '<S55>/Product'
       *  Product: '<S55>/Product2'
       */
      for (i = 0; i < 3; i++) {
        u0 = 0.0;
        for (i_0 = 0; i_0 < 6; i_0++) {
          u0 += tuning_nominal_ConstP.C_Value[3 * i_0 + i] *
            tuning_nominal_DW.MemoryX_DSTATE[i_0];
        }

        rtb_Sum1_l[i] = tuning_nominal_U.X[9 + i] - u0;
      }

      /* End of Sum: '<S55>/Add1' */
      for (i = 0; i < 6; i++) {
        /* Product: '<S55>/Product2' incorporates:
         *  Constant: '<S11>/KalmanGainM'
         */
        tuning_nominal_B.Product2[i] = 0.0;
        tuning_nominal_B.Product2[i] +=
          tuning_nominal_ConstP.KalmanGainM_Value[i] * rtb_Sum1_l[0];
        tuning_nominal_B.Product2[i] +=
          tuning_nominal_ConstP.KalmanGainM_Value[i + 6] * rtb_Sum1_l[1];
        tuning_nominal_B.Product2[i] +=
          tuning_nominal_ConstP.KalmanGainM_Value[i + 12] * rtb_Sum1_l[2];

        /* Sum: '<S34>/Add' incorporates:
         *  Delay: '<S3>/MemoryX'
         */
        rtb_Add_a[i] = tuning_nominal_B.Product2[i] +
          tuning_nominal_DW.MemoryX_DSTATE[i];
      }

      /* End of Outputs for SubSystem: '<S34>/Enabled Subsystem' */
      /* End of Outputs for SubSystem: '<S3>/UseCurrentEstimator' */

      /* Product: '<S2>/Product1' incorporates:
       *  Constant: '<S2>/Constant1'
       */
      for (i = 0; i < 3; i++) {
        rtb_Sum1_l[i] = tuning_nominal_ConstP.Constant1_Value[i + 6] *
          rtb_Add_a[2] + (tuning_nominal_ConstP.Constant1_Value[i + 3] *
                          rtb_Add_a[1] + tuning_nominal_ConstP.Constant1_Value[i]
                          * rtb_Add_a[0]);
      }

      /* End of Product: '<S2>/Product1' */

      /* Sum: '<S7>/Sum1' incorporates:
       *  Product: '<S10>/i x j'
       *  Product: '<S10>/j x k'
       *  Product: '<S10>/k x i'
       *  Product: '<S9>/i x k'
       *  Product: '<S9>/j x i'
       *  Product: '<S9>/k x j'
       */
      rtb_Add_f[0] = rtb_Add_a[1] * rtb_Sum1_l[2];
      rtb_Add_f[1] = rtb_Add_a[2] * rtb_Sum1_l[0];
      rtb_Add_f[2] = rtb_Add_a[0] * rtb_Sum1_l[1];
      rtb_Add_f_0[0] = rtb_Add_a[2] * rtb_Sum1_l[1];
      rtb_Add_f_0[1] = rtb_Add_a[0] * rtb_Sum1_l[2];
      rtb_Add_f_0[2] = rtb_Add_a[1] * rtb_Sum1_l[0];

      /* Sum: '<S2>/Sum3' incorporates:
       *  Constant: '<S2>/Constant'
       *  Constant: '<S2>/Constant1'
       *  Product: '<S2>/Product'
       *  Sum: '<S7>/Sum1'
       */
      for (i = 0; i < 3; i++) {
        rtb_Sum3_i[i] = (((tuning_nominal_ConstP.Constant1_Value[i + 3] *
                           rtb_Add_a[4] +
                           tuning_nominal_ConstP.Constant1_Value[i] * rtb_Add_a
                           [3]) + tuning_nominal_ConstP.Constant1_Value[i + 6] *
                          rtb_Add_a[5]) +
                         tuning_nominal_ConstP.Constant_Value_g[i]) +
          (rtb_Add_f[i] - rtb_Add_f_0[i]);
      }

      /* End of Sum: '<S2>/Sum3' */

      /* MATLAB Function: '<S2>/MATLAB Function1' */
      /* MATLAB Function 'FDD_Kalman/MATLAB Function1': '<S8>:1' */
      /* '<S8>:1:2' arm = 0.215; */
      /* '<S8>:1:2' factor = 0.0365; */
      /* '<S8>:1:4' M = [arm/2 arm arm/2; */
      /* '<S8>:1:5'       -sqrt(3)*arm/2 0 sqrt(3)*arm/2; */
      /* '<S8>:1:6'       -factor factor -factor]; */
      /* '<S8>:1:8' diff = [u(1) - u(4) ; */
      /* '<S8>:1:9'         u(2) - u(5) ; */
      /* '<S8>:1:10'         u(3) - u(6) ]; */
      /* '<S8>:1:11' Residu = diff - M\y; */
      rtb_Sum1_l[1] = rtb_Sum3_i[0] - rtb_Sum3_i[1] * -0.57735026918962584;
      rtb_Sum1_l[2] = (rtb_Sum3_i[2] - rtb_Sum3_i[1] * 0.19603055651554735) -
        rtb_Sum1_l[1] * 0.16976744186046511;
      rtb_Sum1_l[2] /= -0.10949999999999999;
      rtb_Sum1_l[0] = rtb_Sum3_i[1] - rtb_Sum1_l[2] * 0.18619546181365429;
      rtb_Sum1_l[1] -= rtb_Sum1_l[2] * 0.215;
      rtb_Sum1_l[1] /= 0.215;
      rtb_Sum1_l[0] -= rtb_Sum1_l[1] * 0.0;
      rtb_Sum1_l[0] /= -0.18619546181365429;

      /* Outport: '<Root>/LOE13_estimated' incorporates:
       *  MATLAB Function: '<S2>/MATLAB Function1'
       *  Memory: '<S2>/Memory'
       */
      /*  Residu_1_4 */
      /* '<S8>:1:14' gamma    = [Residu(1)/u(1) */
      /* '<S8>:1:15'             Residu(2)/u(2) */
      /* '<S8>:1:16'             Residu(3)/u(3)]; */
      tuning_nominal_Y.LOE13_estimated[0] =
        ((tuning_nominal_DW.Memory_PreviousInput[0] -
          tuning_nominal_DW.Memory_PreviousInput[3]) - rtb_Sum1_l[0]) /
        tuning_nominal_DW.Memory_PreviousInput[0];
      tuning_nominal_Y.LOE13_estimated[1] =
        ((tuning_nominal_DW.Memory_PreviousInput[1] -
          tuning_nominal_DW.Memory_PreviousInput[4]) - rtb_Sum1_l[1]) /
        tuning_nominal_DW.Memory_PreviousInput[1];
      tuning_nominal_Y.LOE13_estimated[2] =
        ((tuning_nominal_DW.Memory_PreviousInput[2] -
          tuning_nominal_DW.Memory_PreviousInput[5]) - rtb_Sum1_l[2]) /
        tuning_nominal_DW.Memory_PreviousInput[2];
    }

    for (i = 0; i < 6; i++) {
      /* Outport: '<Root>/thrust_pre' */
      tuning_nominal_Y.thrust_pre[i] = tuning_nominal_B.u[i];

      /* Outport: '<Root>/thrust_after' */
      tuning_nominal_Y.thrust_after[i] = rtb_T_f[i];
    }

    if (rtmIsMajorTimeStep((&tuning_nominal_M)) &&
        (&tuning_nominal_M)->Timing.TaskCounters.TID[1] == 0) {
      /* Outport: '<Root>/acc_Kalman' */
      tuning_nominal_Y.acc_Kalman[0] = rtb_Add_a[3];

      /* Outport: '<Root>/M_Kalman' */
      tuning_nominal_Y.M_Kalman[0] = rtb_Sum3_i[0];

      /* Outport: '<Root>/vel_Kalman' */
      tuning_nominal_Y.vel_Kalman[0] = rtb_Add_a[0];

      /* Outport: '<Root>/acc_Kalman' */
      tuning_nominal_Y.acc_Kalman[1] = rtb_Add_a[4];

      /* Outport: '<Root>/M_Kalman' */
      tuning_nominal_Y.M_Kalman[1] = rtb_Sum3_i[1];

      /* Outport: '<Root>/vel_Kalman' */
      tuning_nominal_Y.vel_Kalman[1] = rtb_Add_a[1];

      /* Outport: '<Root>/acc_Kalman' */
      tuning_nominal_Y.acc_Kalman[2] = rtb_Add_a[5];

      /* Outport: '<Root>/M_Kalman' */
      tuning_nominal_Y.M_Kalman[2] = rtb_Sum3_i[2];

      /* Outport: '<Root>/vel_Kalman' */
      tuning_nominal_Y.vel_Kalman[2] = rtb_Add_a[2];

      /* Outputs for Enabled SubSystem: '<S29>/MeasurementUpdate' incorporates:
       *  EnablePort: '<S54>/Enable'
       */
      if (rtmIsMajorTimeStep((&tuning_nominal_M)) &&
          (!tuning_nominal_DW.MeasurementUpdate_MODE)) {
        tuning_nominal_DW.MeasurementUpdate_MODE = true;
      }

      if (tuning_nominal_DW.MeasurementUpdate_MODE) {
        for (i = 0; i < 3; i++) {
          /* Product: '<S54>/C[k]*xhat[k|k-1]' incorporates:
           *  Constant: '<S3>/C'
           *  Sum: '<S54>/Add1'
           */
          rtb_Sum1_l[i] = 0.0;
          for (i_0 = 0; i_0 < 6; i_0++) {
            rtb_Sum1_l[i] += tuning_nominal_ConstP.C_Value[3 * i_0 + i] *
              rtb_MemoryX[i_0];
          }

          /* End of Product: '<S54>/C[k]*xhat[k|k-1]' */

          /* Sum: '<S54>/Sum' incorporates:
           *  Inport: '<Root>/X'
           *  Product: '<S54>/Product3'
           *  Sum: '<S54>/Add1'
           */
          rtb_Add_f[i] = tuning_nominal_U.X[9 + i] - rtb_Sum1_l[i];
        }

        /* Product: '<S54>/Product3' incorporates:
         *  Constant: '<S11>/KalmanGainL'
         */
        for (i = 0; i < 6; i++) {
          tuning_nominal_B.Product3[i] = 0.0;
          tuning_nominal_B.Product3[i] +=
            tuning_nominal_ConstP.KalmanGainL_Value[i] * rtb_Add_f[0];
          tuning_nominal_B.Product3[i] +=
            tuning_nominal_ConstP.KalmanGainL_Value[i + 6] * rtb_Add_f[1];
          tuning_nominal_B.Product3[i] +=
            tuning_nominal_ConstP.KalmanGainL_Value[i + 12] * rtb_Add_f[2];
        }
      }

      /* End of Outputs for SubSystem: '<S29>/MeasurementUpdate' */
      for (i = 0; i < 6; i++) {
        /* Product: '<S29>/A[k]*xhat[k|k-1]' incorporates:
         *  Constant: '<S3>/A'
         *  Sum: '<S29>/Add'
         */
        rtb_LOE_out[i] = 0.0;
        for (i_0 = 0; i_0 < 6; i_0++) {
          rtb_LOE_out[i] += tuning_nominal_ConstP.A_Value[6 * i_0 + i] *
            rtb_MemoryX[i_0];
        }

        /* End of Product: '<S29>/A[k]*xhat[k|k-1]' */

        /* Sum: '<S29>/Add' */
        rtb_Add[i] = rtb_LOE_out[i] + tuning_nominal_B.Product3[i];
      }
    }

    /* Sum: '<S5>/Sum' incorporates:
     *  Inport: '<Root>/Y0'
     */
    rtb_ref_idx_0 -= tuning_nominal_U.Y0[0];
    rtb_ff_idx_0 -= tuning_nominal_U.Y0[1];
    rtb_ff_idx_1 -= tuning_nominal_U.Y0[2];
    rtb_Clock = rtb_ref_idx_3 - tuning_nominal_U.Y0[3];

    /* Saturate: '<S56>/x' */
    if (rtb_ref_idx_0 > 2.0) {
      rtb_ref_idx_0 = 2.0;
    } else {
      if (rtb_ref_idx_0 < -2.0) {
        rtb_ref_idx_0 = -2.0;
      }
    }

    /* End of Saturate: '<S56>/x' */

    /* Sum: '<S56>/Sum1' */
    tuning_nominal_B.Sum1 = rtb_ref_idx_0 - rtb_d_x;

    /* Saturate: '<S56>/y' */
    if (rtb_ff_idx_0 > 2.0) {
      rtb_ff_idx_0 = 2.0;
    } else {
      if (rtb_ff_idx_0 < -2.0) {
        rtb_ff_idx_0 = -2.0;
      }
    }

    /* End of Saturate: '<S56>/y' */

    /* Sum: '<S56>/Sum4' */
    tuning_nominal_B.Sum4 = rtb_ff_idx_0 - rtb_d_y;

    /* Saturate: '<S59>/yaw' */
    if (rtb_Clock > 3.1415926535897931) {
      rtb_Clock = 3.1415926535897931;
    } else {
      if (rtb_Clock < -3.1415926535897931) {
        rtb_Clock = -3.1415926535897931;
      }
    }

    /* End of Saturate: '<S59>/yaw' */

    /* Sum: '<S59>/Sum3' */
    tuning_nominal_B.Sum3_f = rtb_Clock - rtb_d_psi;

    /* Saturate: '<S60>/z' */
    if (rtb_ff_idx_1 > 1.75) {
      rtb_ff_idx_1 = 1.75;
    } else {
      if (rtb_ff_idx_1 < 0.0) {
        rtb_ff_idx_1 = 0.0;
      }
    }

    /* End of Saturate: '<S60>/z' */

    /* Sum: '<S60>/Sum3' */
    tuning_nominal_B.Sum3_n = rtb_ff_idx_1 - rtb_d_z;
  }

  if (rtmIsMajorTimeStep((&tuning_nominal_M))) {
    int32_T i;
    if (rtmIsMajorTimeStep((&tuning_nominal_M)) &&
        (&tuning_nominal_M)->Timing.TaskCounters.TID[1] == 0) {
      /* Update for Delay: '<S3>/MemoryX' */
      tuning_nominal_DW.icLoad = 0U;
      for (i = 0; i < 6; i++) {
        /* Update for Memory: '<S2>/Memory' */
        tuning_nominal_DW.Memory_PreviousInput[i] = tuning_nominal_B.u[i];

        /* Update for Delay: '<S3>/MemoryX' */
        tuning_nominal_DW.MemoryX_DSTATE[i] = rtb_Add[i];
      }
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep((&tuning_nominal_M))) {
    rt_ertODEUpdateContinuousStates(&(&tuning_nominal_M)->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++(&tuning_nominal_M)->Timing.clockTick0)) {
      ++(&tuning_nominal_M)->Timing.clockTickH0;
    }

    (&tuning_nominal_M)->Timing.t[0] = rtsiGetSolverStopTime(&(&tuning_nominal_M)
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
      (&tuning_nominal_M)->Timing.clockTick1++;
      if (!(&tuning_nominal_M)->Timing.clockTick1) {
        (&tuning_nominal_M)->Timing.clockTickH1++;
      }
    }

    rate_scheduler((&tuning_nominal_M));
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void tuning_nominalModelClass::tuning_nominal_derivatives()
{
  XDot_tuning_nominal_T *_rtXdot;
  _rtXdot = ((XDot_tuning_nominal_T *) (&tuning_nominal_M)->derivs);

  /* Derivatives for Integrator: '<S60>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = tuning_nominal_B.Sum3_n;

  /* Derivatives for Integrator: '<S56>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_f = tuning_nominal_B.Sum1;

  /* Derivatives for Integrator: '<S56>/Integrator' */
  _rtXdot->Integrator_CSTATE = tuning_nominal_B.Sum4;

  /* Derivatives for Integrator: '<S59>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_a = tuning_nominal_B.Sum3_f;
}

/* Model initialize function */
void tuning_nominalModelClass::initialize()
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)(&tuning_nominal_M), 0,
                sizeof(RT_MODEL_tuning_nominal_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&(&tuning_nominal_M)->solverInfo, &(&tuning_nominal_M
                          )->Timing.simTimeStep);
    rtsiSetTPtr(&(&tuning_nominal_M)->solverInfo, &rtmGetTPtr((&tuning_nominal_M)));
    rtsiSetStepSizePtr(&(&tuning_nominal_M)->solverInfo, &(&tuning_nominal_M)
                       ->Timing.stepSize0);
    rtsiSetdXPtr(&(&tuning_nominal_M)->solverInfo, &(&tuning_nominal_M)->derivs);
    rtsiSetContStatesPtr(&(&tuning_nominal_M)->solverInfo, (real_T **)
                         &(&tuning_nominal_M)->contStates);
    rtsiSetNumContStatesPtr(&(&tuning_nominal_M)->solverInfo,
      &(&tuning_nominal_M)->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&tuning_nominal_M)->solverInfo,
      &(&tuning_nominal_M)->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&tuning_nominal_M)->solverInfo,
      &(&tuning_nominal_M)->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&tuning_nominal_M)->solverInfo,
      &(&tuning_nominal_M)->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&(&tuning_nominal_M)->solverInfo, (&rtmGetErrorStatus
      ((&tuning_nominal_M))));
    rtsiSetRTModelPtr(&(&tuning_nominal_M)->solverInfo, (&tuning_nominal_M));
  }

  rtsiSetSimTimeStep(&(&tuning_nominal_M)->solverInfo, MAJOR_TIME_STEP);
  (&tuning_nominal_M)->intgData.y = (&tuning_nominal_M)->odeY;
  (&tuning_nominal_M)->intgData.f[0] = (&tuning_nominal_M)->odeF[0];
  (&tuning_nominal_M)->intgData.f[1] = (&tuning_nominal_M)->odeF[1];
  (&tuning_nominal_M)->intgData.f[2] = (&tuning_nominal_M)->odeF[2];
  (&tuning_nominal_M)->intgData.f[3] = (&tuning_nominal_M)->odeF[3];
  getRTM()->contStates = ((X_tuning_nominal_T *) &tuning_nominal_X);
  rtsiSetSolverData(&(&tuning_nominal_M)->solverInfo, (void *)
                    &(&tuning_nominal_M)->intgData);
  rtsiSetSolverName(&(&tuning_nominal_M)->solverInfo,"ode4");
  rtmSetTPtr(getRTM(), &(&tuning_nominal_M)->Timing.tArray[0]);
  (&tuning_nominal_M)->Timing.stepSize0 = 0.001;

  /* block I/O */
  (void) memset(((void *) &tuning_nominal_B), 0,
                sizeof(B_tuning_nominal_T));

  /* states (continuous) */
  {
    (void) memset((void *)&tuning_nominal_X, 0,
                  sizeof(X_tuning_nominal_T));
  }

  /* states (dwork) */
  (void) memset((void *)&tuning_nominal_DW, 0,
                sizeof(DW_tuning_nominal_T));

  /* external inputs */
  (void)memset((void *)&tuning_nominal_U, 0, sizeof(ExtU_tuning_nominal_T));

  /* external outputs */
  (void) memset((void *)&tuning_nominal_Y, 0,
                sizeof(ExtY_tuning_nominal_T));

  {
    int32_T i;

    /* InitializeConditions for Integrator: '<S60>/Integrator1' */
    tuning_nominal_X.Integrator1_CSTATE = 0.0;

    /* InitializeConditions for Integrator: '<S56>/Integrator1' */
    tuning_nominal_X.Integrator1_CSTATE_f = 0.0;

    /* InitializeConditions for Integrator: '<S56>/Integrator' */
    tuning_nominal_X.Integrator_CSTATE = 0.0;

    /* InitializeConditions for Integrator: '<S59>/Integrator1' */
    tuning_nominal_X.Integrator1_CSTATE_a = 0.0;

    /* InitializeConditions for Delay: '<S3>/MemoryX' */
    tuning_nominal_DW.icLoad = 1U;

    /* SystemInitialize for Enabled SubSystem: '<S29>/MeasurementUpdate' */
    /* SystemInitialize for Atomic SubSystem: '<S3>/UseCurrentEstimator' */
    /* SystemInitialize for Enabled SubSystem: '<S34>/Enabled Subsystem' */
    for (i = 0; i < 6; i++) {
      /* InitializeConditions for Memory: '<S2>/Memory' */
      tuning_nominal_DW.Memory_PreviousInput[i] = 2.5179000000000005;

      /* SystemInitialize for Outport: '<S55>/deltax' */
      tuning_nominal_B.Product2[i] = 0.0;

      /* SystemInitialize for Outport: '<S54>/L*(y[k]-yhat[k|k-1])' */
      tuning_nominal_B.Product3[i] = 0.0;
    }

    /* End of SystemInitialize for SubSystem: '<S34>/Enabled Subsystem' */
    /* End of SystemInitialize for SubSystem: '<S3>/UseCurrentEstimator' */
    /* End of SystemInitialize for SubSystem: '<S29>/MeasurementUpdate' */
  }
}

/* Model terminate function */
void tuning_nominalModelClass::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
tuning_nominalModelClass::tuning_nominalModelClass()
{
}

/* Destructor */
tuning_nominalModelClass::~tuning_nominalModelClass()
{
  /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_tuning_nominal_T * tuning_nominalModelClass::getRTM()
{
  return (&tuning_nominal_M);
}
