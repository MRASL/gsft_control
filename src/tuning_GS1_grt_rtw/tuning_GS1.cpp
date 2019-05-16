/*
 * tuning_GS1.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "tuning_GS1".
 *
 * Model version              : 1.2210
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Thu May 16 10:35:48 2019
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Passed (1), Warnings (3), Error (0)
 */

#include "tuning_GS1.h"
#include "tuning_GS1_private.h"

static void rate_scheduler(RT_MODEL_tuning_GS1_T *const tuning_GS1_M);

/*
 *   This function updates active task flag for each subrate.
 * The function is called at model base rate, hence the
 * generated code self-manages all its subrates.
 */
static void rate_scheduler(RT_MODEL_tuning_GS1_T *const tuning_GS1_M)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (tuning_GS1_M->Timing.TaskCounters.TID[2])++;
  if ((tuning_GS1_M->Timing.TaskCounters.TID[2]) > 4) {/* Sample time: [0.005s, 0.0s] */
    tuning_GS1_M->Timing.TaskCounters.TID[2] = 0;
  }
}

/*
 * This function updates continuous states using the ODE4 fixed-step
 * solver algorithm
 */
void tuning_GS1ModelClass::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
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
  int_T nXc = 6;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  tuning_GS1_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  this->step();
  tuning_GS1_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  this->step();
  tuning_GS1_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  this->step();
  tuning_GS1_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void tuning_GS1ModelClass::step()
{
  /* local block i/o variables */
  real_T rtb_Add[6];
  if (rtmIsMajorTimeStep((&tuning_GS1_M))) {
    /* set solver stop time */
    if (!((&tuning_GS1_M)->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&(&tuning_GS1_M)->solverInfo, (((&tuning_GS1_M)
        ->Timing.clockTickH0 + 1) * (&tuning_GS1_M)->Timing.stepSize0 *
        4294967296.0));
    } else {
      rtsiSetSolverStopTime(&(&tuning_GS1_M)->solverInfo, (((&tuning_GS1_M)
        ->Timing.clockTick0 + 1) * (&tuning_GS1_M)->Timing.stepSize0 +
        (&tuning_GS1_M)->Timing.clockTickH0 * (&tuning_GS1_M)->Timing.stepSize0 *
        4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep((&tuning_GS1_M))) {
    (&tuning_GS1_M)->Timing.t[0] = rtsiGetT(&(&tuning_GS1_M)->solverInfo);
  }

  {
    static const real_T y[12] = { 2.759, 2.759, 2.759, 2.759, 2.759, 2.759, 1.31,
      1.31, 1.31, 1.31, 1.31, 1.31 };

    static const real_T a[12] = { 0.05217, 0.5261, 0.5261, 0.5261, 0.5261,
      0.5261, 0.1333, 0.4093, 0.4093, 0.4093, 0.4093, 0.4093 };

    static const real_T b_a[12] = { 0.5261, 0.05217, 0.5261, 0.5261, 0.5261,
      0.5261, 0.4093, 0.1333, 0.4093, 0.4093, 0.4093, 0.4093 };

    static const real_T c_a[12] = { 0.5261, 0.5261, 0.05217, 0.5261, 0.5261,
      0.5261, 0.4093, 0.4093, 0.1333, 0.4093, 0.4093, 0.4093 };

    static const real_T d_a[12] = { 0.5261, 0.5261, 0.5261, 0.05217, 0.5261,
      0.5261, 0.4093, 0.4093, 0.4093, 0.1333, 0.4093, 0.4093 };

    static const real_T e_a[12] = { 0.5261, 0.5261, 0.5261, 0.5261, 0.05217,
      0.5261, 0.4093, 0.4093, 0.4093, 0.4093, 0.1333, 0.4093 };

    static const real_T f_a[12] = { 0.5261, 0.5261, 0.5261, 0.5261, 0.5261,
      0.05217, 0.4093, 0.4093, 0.4093, 0.4093, 0.4093, 0.1333 };

    static const real_T g_a[6] = { 0.07978, 0.3163, 0.3163, 0.3163, 0.3163,
      0.3163 };

    static const real_T h_a[6] = { 0.3163, 0.07978, 0.3163, 0.3163, 0.3163,
      0.3163 };

    static const real_T i_a[6] = { 0.3163, 0.3163, 0.07978, 0.3163, 0.3163,
      0.3163 };

    static const real_T j_a[6] = { 0.3163, 0.3163, 0.3163, 0.07978, 0.3163,
      0.3163 };

    static const real_T k_a[6] = { 0.3163, 0.3163, 0.3163, 0.3163, 0.07978,
      0.3163 };

    static const real_T l_a[6] = { 0.3163, 0.3163, 0.3163, 0.3163, 0.3163,
      0.07978 };

    static const real_T y_0[12] = { -2.274, 2.274, -2.274, 2.274, -2.274, 2.274,
      -1.4292, 1.4292, -1.4292, 1.4292, -1.4292, 1.4292 };

    static const real_T b_y[6] = { -1.4438, 1.4438, -1.4438, 1.4438, -1.4438,
      1.4438 };

    static const real_T a_0[16] = { -0.1661, 0.3195, 0.3195, -0.3195, -0.1374,
      0.3305, 0.3305, -0.3305, -0.6998, 2.039, 2.039, -2.039, -0.4595, 0.5803,
      0.5803, -0.5803 };

    static const real_T b_a_0[16] = { -0.3195, 0.1661, 0.3195, -0.3195, -0.3305,
      0.1374, 0.3305, -0.3305, -2.039, 0.6998, 2.039, -2.039, -0.5803, 0.4595,
      0.5803, -0.5803 };

    static const real_T c_a_0[16] = { -0.3195, 0.3195, 0.1661, -0.3195, -0.3305,
      0.3305, 0.1374, -0.3305, -2.039, 2.039, 0.6998, -2.039, -0.5803, 0.5803,
      0.4595, -0.5803 };

    static const real_T d_a_0[16] = { -0.3195, 0.3195, 0.3195, -0.1661, -0.3305,
      0.3305, 0.3305, -0.1374, -2.039, 2.039, 2.039, -0.6998, -0.5803, 0.5803,
      0.5803, -0.4595 };

    static const real_T e_a_0[4] = { -0.03956, 0.2068, 0.2068, -0.2068 };

    static const real_T f_a_0[4] = { -0.2068, 0.03956, 0.2068, -0.2068 };

    static const real_T g_a_0[4] = { -0.2068, 0.2068, 0.03956, -0.2068 };

    static const real_T h_a_0[4] = { -0.2068, 0.2068, 0.2068, -0.03956 };

    static const real_T a_1[24] = { 0.1679, -0.3742, -0.1871, 0.1871, 0.3742,
      0.1871, 0.07127, -0.3256, -0.1628, 0.1628, 0.3256, 0.1628, 0.195, 1.465,
      0.7325, -0.7325, -1.465, -0.7325, 0.4091, 0.2348, 0.1174, -0.1174, -0.2348,
      -0.1174 };

    static const real_T b_a_1[24] = { -0.1871, 0.3358, -0.1871, 0.1871, 0.3742,
      0.1871, -0.1628, 0.14254, -0.1628, 0.1628, 0.3256, 0.1628, 0.7325, 0.39,
      0.7325, -0.7325, -1.465, -0.7325, 0.1174, 0.8182, 0.1174, -0.1174, -0.2348,
      -0.1174 };

    static const real_T c_a_1[24] = { -0.1871, -0.3742, 0.1679, 0.1871, 0.3742,
      0.1871, -0.1628, -0.3256, 0.07127, 0.1628, 0.3256, 0.1628, 0.7325, 1.465,
      0.195, -0.7325, -1.465, -0.7325, 0.1174, 0.2348, 0.4091, -0.1174, -0.2348,
      -0.1174 };

    static const real_T d_a_1[24] = { -0.1871, -0.3742, -0.1871, -0.1679, 0.3742,
      0.1871, -0.1628, -0.3256, -0.1628, -0.07127, 0.3256, 0.1628, 0.7325, 1.465,
      0.7325, -0.195, -1.465, -0.7325, 0.1174, 0.2348, 0.1174, -0.4091, -0.2348,
      -0.1174 };

    static const real_T e_a_1[24] = { -0.1871, -0.3742, -0.1871, 0.1871, -0.3358,
      0.1871, -0.1628, -0.3256, -0.1628, 0.1628, -0.14254, 0.1628, 0.7325, 1.465,
      0.7325, -0.7325, -0.39, -0.7325, 0.1174, 0.2348, 0.1174, -0.1174, -0.8182,
      -0.1174 };

    static const real_T f_a_1[24] = { -0.1871, -0.3742, -0.1871, 0.1871, 0.3742,
      -0.1679, -0.1628, -0.3256, -0.1628, 0.1628, 0.3256, -0.07127, 0.7325,
      1.465, 0.7325, -0.7325, -1.465, -0.195, 0.1174, 0.2348, 0.1174, -0.1174,
      -0.2348, -0.4091 };

    static const real_T g_a_1[6] = { 0.1702, -0.18398, -0.09199, 0.09199,
      0.18398, 0.09199 };

    static const real_T h_a_1[6] = { -0.09199, 0.3404, -0.09199, 0.09199,
      0.18398, 0.09199 };

    static const real_T i_a_0[6] = { -0.09199, -0.18398, 0.1702, 0.09199,
      0.18398, 0.09199 };

    static const real_T j_a_0[6] = { -0.09199, -0.18398, -0.09199, -0.1702,
      0.18398, 0.09199 };

    static const real_T k_a_0[6] = { -0.09199, -0.18398, -0.09199, 0.09199,
      -0.3404, 0.09199 };

    static const real_T l_a_0[6] = { -0.09199, -0.18398, -0.09199, 0.09199,
      0.18398, -0.1702 };

    real_T rtb_Sum1[3];
    real_T rtb_Add_a[6];
    real_T rtb_LOE_out[6];
    real_T rtb_gamma_m[6];
    real_T rtb_Kiz[6];
    real_T rtb_d_z;
    real_T rtb_Kipsi[6];
    real_T rtb_d_psi;
    real_T rtb_Kix[4];
    real_T rtb_d_x;
    real_T rtb_d_y;
    real_T rtb_T_f[6];
    real_T rtb_ref[4];
    real_T rtb_Clock;
    real_T rtb_MemoryX[6];
    real_T rtb_Kz[12];
    real_T rtb_Kpsi[12];
    real_T rtb_Kxtheta[16];
    real_T rtb_Kyphi[24];
    int32_T i;
    real_T rtb_Add_f[3];
    real_T rtb_Add_f_0[3];
    real_T rtb_gamma_j;
    real_T rtb_gamma_j_0;
    real_T rtb_gamma_j_1;
    real_T tmp[6];
    real_T rtb_Kipsi_0[6];
    real_T rtb_ref_0[6];
    int32_T i_0;
    real_T rtb_ff_idx_1;
    real_T rtb_ff_idx_0;
    real_T rtb_gamma_idx_2;
    real_T rtb_gamma_idx_1;
    real_T rtb_gamma_idx_0;

    /* Clock: '<Root>/Clock' */
    rtb_Clock = (&tuning_GS1_M)->Timing.t[0];

    /* MATLAB Function 'Test_config_and_data/LOE_': '<S70>:1' */
    /* '<S70>:1:2' LOE_out = [0;0;0;0;0;0]; */
    /* '<S70>:1:3' for i = 1:6 */
    /* MATLAB Function 'FDD': '<S2>:1' */
    /* '<S2>:1:2' gamma = [0 0 0 0 0 0]'; */
    /* '<S2>:1:3' for i = 1:6 */
    for (i = 0; i < 6; i++) {
      /* MATLAB Function: '<S7>/LOE_' incorporates:
       *  Inport: '<Root>/LOE_a'
       *  Inport: '<Root>/LOE_t'
       */
      rtb_LOE_out[i] = 0.0;

      /* '<S70>:1:4' if t>= LOE_t(i) */
      if (rtb_Clock >= tuning_GS1_U.LOE_t[i]) {
        /* '<S70>:1:5' LOE_out(i) = LOE(i); */
        rtb_LOE_out[i] = tuning_GS1_U.LOE_a[i];
      }

      /* End of MATLAB Function: '<S7>/LOE_' */

      /* MATLAB Function: '<Root>/FDD' incorporates:
       *  Inport: '<Root>/LOE_a'
       *  Inport: '<Root>/LOE_t'
       */
      /* '<S2>:1:4' if time <= LOE_moment(i) */
      if (rtb_Clock <= tuning_GS1_U.LOE_t[i]) {
        /* '<S2>:1:5' gamma(i) = 0; */
        rtb_gamma_m[i] = 0.0;
      } else if (rtb_Clock <= tuning_GS1_U.LOE_t[i] + 1.5) {
        /* '<S2>:1:6' elseif time <= LOE_moment(i)+1.5 */
        /* '<S2>:1:7' gamma(i) = LOE_amplitude(i)*(time - LOE_moment(i))/1.5; */
        rtb_gamma_m[i] = (rtb_Clock - tuning_GS1_U.LOE_t[i]) *
          tuning_GS1_U.LOE_a[i] / 1.5;
      } else {
        /* '<S2>:1:8' else */
        /* '<S2>:1:9' gamma(i) = LOE_amplitude(i); */
        rtb_gamma_m[i] = tuning_GS1_U.LOE_a[i];
      }

      /* End of MATLAB Function: '<Root>/FDD' */
    }

    if (rtmIsMajorTimeStep((&tuning_GS1_M)) &&
        (&tuning_GS1_M)->Timing.TaskCounters.TID[1] == 0) {
      /* Delay: '<S5>/MemoryX' */
      for (i = 0; i < 6; i++) {
        if (tuning_GS1_DW.icLoad != 0) {
          tuning_GS1_DW.MemoryX_DSTATE[i] = 0.0;
        }

        rtb_MemoryX[i] = tuning_GS1_DW.MemoryX_DSTATE[i];
      }

      /* Outputs for Atomic SubSystem: '<S5>/UseCurrentEstimator' */
      /* Outputs for Enabled SubSystem: '<S44>/Enabled Subsystem' incorporates:
       *  EnablePort: '<S65>/Enable'
       */
      if (!tuning_GS1_DW.EnabledSubsystem_MODE) {
        tuning_GS1_DW.EnabledSubsystem_MODE = true;
      }

      /* Sum: '<S65>/Add1' incorporates:
       *  Constant: '<S5>/C'
       *  Delay: '<S5>/MemoryX'
       *  Inport: '<Root>/X'
       *  Product: '<S65>/Product'
       *  Product: '<S65>/Product2'
       */
      for (i = 0; i < 3; i++) {
        rtb_d_z = 0.0;
        for (i_0 = 0; i_0 < 6; i_0++) {
          rtb_d_z += tuning_GS1_ConstP.C_Value[3 * i_0 + i] *
            tuning_GS1_DW.MemoryX_DSTATE[i_0];
        }

        rtb_Add_f[i] = tuning_GS1_U.X[9 + i] - rtb_d_z;
      }

      /* End of Sum: '<S65>/Add1' */
      for (i = 0; i < 6; i++) {
        /* Product: '<S65>/Product2' incorporates:
         *  Constant: '<S21>/KalmanGainM'
         */
        tuning_GS1_B.Product2[i] = 0.0;
        tuning_GS1_B.Product2[i] += tuning_GS1_ConstP.KalmanGainM_Value[i] *
          rtb_Add_f[0];
        tuning_GS1_B.Product2[i] += tuning_GS1_ConstP.KalmanGainM_Value[i + 6] *
          rtb_Add_f[1];
        tuning_GS1_B.Product2[i] += tuning_GS1_ConstP.KalmanGainM_Value[i + 12] *
          rtb_Add_f[2];

        /* Sum: '<S44>/Add' incorporates:
         *  Delay: '<S5>/MemoryX'
         */
        rtb_Add_a[i] = tuning_GS1_B.Product2[i] + tuning_GS1_DW.MemoryX_DSTATE[i];
      }

      /* End of Outputs for SubSystem: '<S44>/Enabled Subsystem' */
      /* End of Outputs for SubSystem: '<S5>/UseCurrentEstimator' */

      /* Product: '<S3>/Product1' incorporates:
       *  Constant: '<S3>/Constant1'
       */
      for (i = 0; i < 3; i++) {
        rtb_Sum1[i] = tuning_GS1_ConstP.Constant1_Value[i + 6] * rtb_Add_a[2] +
          (tuning_GS1_ConstP.Constant1_Value[i + 3] * rtb_Add_a[1] +
           tuning_GS1_ConstP.Constant1_Value[i] * rtb_Add_a[0]);
      }

      /* End of Product: '<S3>/Product1' */

      /* Sum: '<S9>/Sum1' incorporates:
       *  Product: '<S11>/i x k'
       *  Product: '<S11>/j x i'
       *  Product: '<S11>/k x j'
       *  Product: '<S12>/i x j'
       *  Product: '<S12>/j x k'
       *  Product: '<S12>/k x i'
       */
      rtb_Add_f[0] = rtb_Add_a[1] * rtb_Sum1[2];
      rtb_Add_f[1] = rtb_Add_a[2] * rtb_Sum1[0];
      rtb_Add_f[2] = rtb_Add_a[0] * rtb_Sum1[1];
      rtb_Add_f_0[0] = rtb_Add_a[2] * rtb_Sum1[1];
      rtb_Add_f_0[1] = rtb_Add_a[0] * rtb_Sum1[2];
      rtb_Add_f_0[2] = rtb_Add_a[1] * rtb_Sum1[0];

      /* Sum: '<S3>/Sum3' incorporates:
       *  Constant: '<S3>/Constant'
       *  Constant: '<S3>/Constant1'
       *  Product: '<S3>/Product'
       *  Sum: '<S9>/Sum1'
       */
      for (i = 0; i < 3; i++) {
        rtb_Sum1[i] = (((tuning_GS1_ConstP.Constant1_Value[i + 3] * rtb_Add_a[4]
                         + tuning_GS1_ConstP.Constant1_Value[i] * rtb_Add_a[3])
                        + tuning_GS1_ConstP.Constant1_Value[i + 6] * rtb_Add_a[5])
                       + tuning_GS1_ConstP.Constant_Value[i]) + (rtb_Add_f[i] -
          rtb_Add_f_0[i]);
      }

      /* End of Sum: '<S3>/Sum3' */

      /* MATLAB Function: '<S3>/MATLAB Function1' incorporates:
       *  Memory: '<S3>/Memory'
       */
      /* MATLAB Function 'FDD_Kalman/MATLAB Function1': '<S10>:1' */
      /* '<S10>:1:2' arm = 0.215; */
      /* '<S10>:1:2' factor = 0.0365; */
      /* '<S10>:1:4' M = [arm/2 arm arm/2; */
      /* '<S10>:1:5'       -sqrt(3)*arm/2 0 sqrt(3)*arm/2; */
      /* '<S10>:1:6'       -factor factor -factor]; */
      /* '<S10>:1:8' diff = [u(1) - u(4) ; */
      /* '<S10>:1:9'         u(2) - u(5) ; */
      /* '<S10>:1:10'         u(3) - u(6) ]; */
      /* '<S10>:1:11' Residu = diff - M\y; */
      rtb_gamma_idx_1 = rtb_Sum1[0] - rtb_Sum1[1] * -0.57735026918962584;
      rtb_gamma_idx_2 = ((rtb_Sum1[2] - rtb_Sum1[1] * 0.19603055651554735) -
                         rtb_gamma_idx_1 * 0.16976744186046511) /
        -0.10949999999999999;
      rtb_gamma_idx_1 -= rtb_gamma_idx_2 * 0.215;
      rtb_gamma_idx_1 /= 0.215;

      /*  Residu_1_4 */
      /* '<S10>:1:14' gamma    = [Residu(1)/u(1) */
      /* '<S10>:1:15'             Residu(2)/u(2) */
      /* '<S10>:1:16'             Residu(3)/u(3)]; */
      rtb_gamma_idx_0 = ((tuning_GS1_DW.Memory_PreviousInput[0] -
                          tuning_GS1_DW.Memory_PreviousInput[3]) - ((rtb_Sum1[1]
        - rtb_gamma_idx_2 * 0.18619546181365429) - rtb_gamma_idx_1 * 0.0) /
                         -0.18619546181365429) /
        tuning_GS1_DW.Memory_PreviousInput[0];
      rtb_gamma_idx_1 = ((tuning_GS1_DW.Memory_PreviousInput[1] -
                          tuning_GS1_DW.Memory_PreviousInput[4]) -
                         rtb_gamma_idx_1) / tuning_GS1_DW.Memory_PreviousInput[1];
      rtb_gamma_idx_2 = ((tuning_GS1_DW.Memory_PreviousInput[2] -
                          tuning_GS1_DW.Memory_PreviousInput[5]) -
                         rtb_gamma_idx_2) / tuning_GS1_DW.Memory_PreviousInput[2];

      /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn1' */
      tuning_GS1_B.LOE_FDD[0] = rtb_gamma_idx_0;

      /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn2' */
      tuning_GS1_B.LOE_FDD[3] = 0.0;

      /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn1' */
      tuning_GS1_B.LOE_FDD[1] = rtb_gamma_idx_1;

      /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn2' */
      tuning_GS1_B.LOE_FDD[4] = 0.0;

      /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn1' */
      tuning_GS1_B.LOE_FDD[2] = rtb_gamma_idx_2;

      /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn2' */
      tuning_GS1_B.LOE_FDD[5] = 0.0;
    }

    /* MultiPortSwitch: '<Root>/Multiport Switch' incorporates:
     *  Inport: '<Root>/LOE_cal'
     *  Inport: '<Root>/LOE_mode'
     */
    switch ((int32_T)tuning_GS1_U.LOE_mode) {
     case 0:
      for (i = 0; i < 6; i++) {
        rtb_gamma_m[i] = 0.0;
      }
      break;

     case 1:
      for (i = 0; i < 6; i++) {
        rtb_gamma_m[i] = rtb_LOE_out[i];
      }
      break;

     case 2:
      break;

     case 3:
      for (i = 0; i < 6; i++) {
        rtb_gamma_m[i] = tuning_GS1_U.LOE_cal[i];
      }
      break;

     default:
      for (i = 0; i < 6; i++) {
        rtb_gamma_m[i] = tuning_GS1_B.LOE_FDD[i];
      }
      break;
    }

    /* End of MultiPortSwitch: '<Root>/Multiport Switch' */

    /* Saturate: '<Root>/                        ' */
    for (i = 0; i < 6; i++) {
      rtb_d_y = rtb_gamma_m[i];
      if (rtb_gamma_m[i] > 1.0) {
        rtb_d_y = 1.0;
      } else {
        if (rtb_gamma_m[i] < 0.0) {
          rtb_d_y = 0.0;
        }
      }

      rtb_gamma_m[i] = rtb_d_y;
    }

    /* End of Saturate: '<Root>/                        ' */

    /* MATLAB Function: '<S16>/MATLAB Function' */
    /* MATLAB Function 'GS_controller/z_GS_controller/MATLAB Function': '<S20>:1' */
    /*  Nominal gain */
    /*  Kz =  [2.4538    1.1346 */
    /*         2.4538    1.1346 */
    /*         2.4538    1.1346]; */
    /*  Kiz = [2.0412 */
    /*         2.0412 */
    /*         2.0412];         */
    /*      Kx0 = [2.4538    1.1346];       % Kx0 = [a0 b0]   */
    /*      Kx1 = [0 0                      % Kx1 = [a1 b1 */
    /*             0 0];                    %        a2 b2] */
    /*      Ki0 =  2.0412;                  % Ki0 =  i0 */
    /*      Ki1 = [0                        % Ki1 = [i1 i2]' */
    /*             0];   */
    /*  FTC1 gain */
    /*      Kx0 = [3.633   2.0170];         % Kx0 = [a0 b0]   */
    /*      Kx1 = [0.4546  0.6222           % Kx1 = [a1 b1 */
    /*             1.009   0.4581];         %        a2 b2] */
    /*      Ki0 =  2.515;                   % Ki0 =  i0 */
    /*      Ki1 = [0.3052                   % Ki1 = [i1 i2]' */
    /*             0.7377];        */
    /* '<S20>:1:31' Kx0 = [2.759   1.31]; */
    /*  Kx0 = [a0 b0]   */
    /*  Kx1 = [a1 b1 */
    /* '<S20>:1:32' Kx1 = [0.05217   0.1333           % Kx1 = [a1 b1 */
    /* '<S20>:1:33'            0.5261   0.4093]; */
    /*         a2 b2] */
    /* '<S20>:1:34' Ki0 =  2.072; */
    /*  Ki0 =  i0 */
    /*  Ki1 = [i1 i2]' */
    /* '<S20>:1:35' Ki1 = [0.07978                   % Ki1 = [i1 i2]' */
    /* '<S20>:1:36'            0.3163]; */
    /*      */
    /*  */
    /* '<S20>:1:40' K_mapping0 = [1 1 1 1 1 1]'; */
    /* '<S20>:1:41' K_mapping1 = [1 0 0 0 0 0;0 1 1 1 1 1]'; */
    /* '<S20>:1:42' K_mapping2 = [0 1 0 0 0 0;1 0 1 1 1 1]'; */
    /* '<S20>:1:43' K_mapping3 = [0 0 1 0 0 0;1 1 0 1 1 1]'; */
    /* '<S20>:1:44' K_mapping4 = [0 0 0 1 0 0;1 1 1 0 1 1]'; */
    /* '<S20>:1:45' K_mapping5 = [0 0 0 0 1 0;1 1 1 1 0 1]'; */
    /* '<S20>:1:46' K_mapping6 = [0 0 0 0 0 1;1 1 1 1 1 0]'; */
    /* '<S20>:1:48' Kz  = K_mapping0*Kx0 + K_mapping1*Kx1*u(1) + K_mapping2*Kx1*u(2) + K_mapping3*Kx1*u(3) + K_mapping4*Kx1*u(4) + K_mapping5*Kx1*u(5) + K_mapping6*Kx1*u(6); */
    for (i = 0; i < 12; i++) {
      rtb_Kz[i] = (((((a[i] * rtb_gamma_m[0] + y[i]) + b_a[i] * rtb_gamma_m[1])
                     + c_a[i] * rtb_gamma_m[2]) + d_a[i] * rtb_gamma_m[3]) +
                   e_a[i] * rtb_gamma_m[4]) + f_a[i] * rtb_gamma_m[5];
    }

    /* '<S20>:1:49' Kiz = K_mapping0*Ki0 + K_mapping1*Ki1*u(1) + K_mapping2*Ki1*u(2) + K_mapping3*Ki1*u(3) + K_mapping4*Ki1*u(4) + K_mapping5*Ki1*u(5) + K_mapping6*Ki1*u(6); */
    for (i = 0; i < 6; i++) {
      rtb_Kiz[i] = (((((g_a[i] * rtb_gamma_m[0] + 2.072) + h_a[i] * rtb_gamma_m
                       [1]) + i_a[i] * rtb_gamma_m[2]) + j_a[i] * rtb_gamma_m[3])
                    + k_a[i] * rtb_gamma_m[4]) + l_a[i] * rtb_gamma_m[5];
    }

    /* Sum: '<S7>/Sum5' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/Y0'
     */
    /*  */
    /* '<S20>:1:52' gain = [Kz(1,:) Kiz(1)]; */
    /*  to display: gain z, zd, int for first rotor */
    rtb_d_z = tuning_GS1_U.X[2] - tuning_GS1_U.Y0[2];

    /* MATLAB Function: '<S13>/MATLAB Function' */
    /* MATLAB Function 'GS_controller/psi_GS_controller/MATLAB Function': '<S17>:1' */
    /*  LQR gain */
    /*  Kpsi = [-2.2740   -1.4292 */
    /*           2.2740    1.4292 */
    /*          -2.2740   -1.4292 */
    /*           2.2740    1.4292 */
    /*          -2.2740   -1.4292 */
    /*           2.2740    1.4292]; */
    /*  Kipsi = [-1.4438  1.4438  -1.4438  1.4438  -1.4438  1.4438]'; */
    /* '<S17>:1:11' Kx0 = [-2.2740   -1.4292 ]; */
    /*  Kx0 = [a0 b0]   */
    /*  Kx1 = [a1 b1 */
    /* '<S17>:1:12' Kx1 = [0 0                         % Kx1 = [a1 b1 */
    /* '<S17>:1:13'            0 0]; */
    /*         a2 b2] */
    /* '<S17>:1:14' Ki0 = -1.4438; */
    /*  Ki0 =  i0 */
    /*  Ki1 = [i1 i2]' */
    /* '<S17>:1:15' Ki1 = [ 0                          % Ki1 = [i1 i2]' */
    /* '<S17>:1:16'             0]; */
    /*  FTC1 gain */
    /*      Kx0 = [-2.735     -1.888 ];        % Kx0 = [a0 b0]   */
    /*      Kx1 = [ 0.01893   -0.253           % Kx1 = [a1 b1 */
    /*             -0.583     -0.7419];        %        a2 b2] */
    /*      Ki0 =  -1.243;                     % Ki0 =  i0 */
    /*      Ki1 = [ 0.126                      % Ki1 = [i1 i2]' */
    /*             -0.261]; */
    /*          */
    /* '<S17>:1:26' K_mapping0 = [1 -1  1 -1 1 -1]'; */
    /* '<S17>:1:27' K_mapping1 = [1  0  0  0 0  0;0 -1 1 -1 1 -1]'; */
    /* '<S17>:1:28' K_mapping2 = [0 -1  0  0 0  0;1  0 1 -1 1 -1]'; */
    /* '<S17>:1:29' K_mapping3 = [0  0  1  0 0  0;1 -1 0 -1 1 -1]'; */
    /* '<S17>:1:30' K_mapping4 = [0  0  0 -1 0  0;1 -1 1  0 1 -1]'; */
    /* '<S17>:1:31' K_mapping5 = [0  0  0  0 1  0;1 -1 1 -1 0 -1]'; */
    /* '<S17>:1:32' K_mapping6 = [0  0  0  0 0 -1;1 -1 1 -1 1 0]'; */
    /* '<S17>:1:34' Kpsi  = K_mapping0*Kx0 + K_mapping1*Kx1*u(1) + K_mapping2*Kx1*u(2) + K_mapping3*Kx1*u(3) + K_mapping4*Kx1*u(4) + K_mapping5*Kx1*u(5) + K_mapping6*Kx1*u(6); */
    for (i = 0; i < 12; i++) {
      rtb_Kpsi[i] = (((((0.0 * rtb_gamma_m[0] + y_0[i]) + 0.0 * rtb_gamma_m[1])
                       + 0.0 * rtb_gamma_m[2]) + 0.0 * rtb_gamma_m[3]) + 0.0 *
                     rtb_gamma_m[4]) + 0.0 * rtb_gamma_m[5];
    }

    /* '<S17>:1:35' Kipsi = K_mapping0*Ki0 + K_mapping1*Ki1*u(1) + K_mapping2*Ki1*u(2) + K_mapping3*Ki1*u(3) + K_mapping4*Ki1*u(4) + K_mapping5*Ki1*u(5) + K_mapping6*Ki1*u(6); */
    for (i = 0; i < 6; i++) {
      rtb_Kipsi[i] = (((((0.0 * rtb_gamma_m[0] + b_y[i]) + 0.0 * rtb_gamma_m[1])
                        + 0.0 * rtb_gamma_m[2]) + 0.0 * rtb_gamma_m[3]) + 0.0 *
                      rtb_gamma_m[4]) + 0.0 * rtb_gamma_m[5];
    }

    /* Sum: '<S7>/Sum6' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/Y0'
     */
    /* '<S17>:1:37' gain = [Kpsi(1,:) Kipsi(1)]; */
    /*  to display: gain psi, psid, int for first rotor */
    rtb_d_psi = tuning_GS1_U.X[8] - tuning_GS1_U.Y0[3];

    /* MATLAB Function: '<S14>/MATLAB Function' */
    /* MATLAB Function 'GS_controller/x_GS_controller/MATLAB Function': '<S18>:1' */
    /*  LQR gain */
    /*  K_lqr  = [-1.6684  -0.9513  -3.0809  -0.6162 */
    /*             1.6684   0.9513   3.0809   0.6162 */
    /*            -1.6684  -0.9513  -3.0809  -0.6162] */
    /*  Ki_lqr = [-1.3310 */
    /*             1.3310 */
    /*            -1.3310] */
    /*  FTC1 gain     */
    /*  Kx = [ a0  b0  c0  d0|      [a1  b1  c1  d1|             [a2  b2  c2  d2|            [ a2  b2  c2  d2|              [a2  b2  c2  d2| */
    /*       |-a0 -b0 -c0 -d0|   + |-a2 -b2 -c2 -d2| * gamma1 + |-a1 -b1 -c1 -d1| * gamma3 + |-a2 -b2 -c2 -d2| * gamma4 +  |-a2 -b2 -c2 -d2| * gamma6  */
    /*       |-a0 -b0 -c0 -d0|     |-a2 -b2 -c2 -d2|            |-a2 -b2 -c2 -d2|            |-a1 -b1 -c1 -d1|             |-a2 -b2 -c2 -d2| */
    /*       | a0  b0  c0  d0]      |a2  b2  c2  d2]             |a2  b2  c2  d2]            | a2  b2  c2  d2]              |a1  b1  c1  d1] */
    /*  Kix = [i0    [ i1            [ i2            [ i2            [ i2 */
    /*        -i0  +  -i2 * gamma1 +  -i1 * gamma3 +  -i2 * gamma4 +  -i2 * gamma6 */
    /*        -i0     -i2             -i2             -i1             -i2 */
    /*         i0]     i2]             i2]             i2]             i1]      */
    /* '<S18>:1:23' Kx0 = [-1.788   -1.367   -4.629   -0.7231]; */
    /*  Kx0 = [a0 b0 c0 d0]   */
    /*  Kx1 = [a1 b1 c1 d1 */
    /* '<S18>:1:24' Kx1 = [-0.1661  -0.1374  -0.6998  -0.4595          % Kx1 = [a1 b1 c1 d1 */
    /* '<S18>:1:25'            -0.3195  -0.3305  -2.039   -0.5803]; */
    /*         a2 b2 c2 d2] */
    /* '<S18>:1:26' Ki0 =  -1.036; */
    /*  Ki0 = i0 */
    /*  Ki1 = [i1 i2]' */
    /* '<S18>:1:27' Ki1 = [-0.03956                                    % Ki1 = [i1 i2]' */
    /* '<S18>:1:28'            -0.2068]; */
    /* '<S18>:1:30' K_mapping1 = [1  0  0 0;0 -1 -1 1]'; */
    /* '<S18>:1:31' K_mapping3 = [0 -1  0 0;1  0 -1 1]'; */
    /* '<S18>:1:32' K_mapping4 = [0  0 -1 0;1 -1  0 1]'; */
    /* '<S18>:1:33' K_mapping6 = [0  0  0 1;1 -1 -1 0]'; */
    /* '<S18>:1:35' Kxtheta  = K_mapping1*Kx1*u(1) + K_mapping3*Kx1*u(3) + K_mapping4*Kx1*u(4) + K_mapping6*Kx1*u(6); */
    for (i = 0; i < 16; i++) {
      rtb_Kxtheta[i] = ((a_0[i] * rtb_gamma_m[0] + b_a_0[i] * rtb_gamma_m[2]) +
                        c_a_0[i] * rtb_gamma_m[3]) + d_a_0[i] * rtb_gamma_m[5];
    }

    /* Sum: '<S7>/Sum1' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/Y0'
     */
    /* '<S18>:1:36' Kix      = K_mapping1*Ki1*u(1) + K_mapping3*Ki1*u(3) + K_mapping4*Ki1*u(4) + K_mapping6*Ki1*u(6); */
    /* '<S18>:1:38' gain = [Kx0(1:2) Ki0] + [Kxtheta(1,1:2) Kix(1)]; */
    /*  to display: gain x, xd, int for first rotor */
    rtb_d_x = tuning_GS1_U.X[0] - tuning_GS1_U.Y0[0];
    for (i = 0; i < 4; i++) {
      /* MATLAB Function: '<S14>/MATLAB Function' */
      rtb_d_y = ((e_a_0[i] * rtb_gamma_m[0] + f_a_0[i] * rtb_gamma_m[2]) +
                 g_a_0[i] * rtb_gamma_m[3]) + h_a_0[i] * rtb_gamma_m[5];

      /* Sum: '<S14>/Sum1' incorporates:
       *  Inport: '<Root>/X'
       *  Integrator: '<S14>/Integrator1'
       *  Product: '<S14>/Product'
       *  Product: '<S14>/Product1'
       *  SignalConversion: '<S14>/TmpSignal ConversionAtProduct1Inport2'
       */
      rtb_ref[i] = rtb_d_y * tuning_GS1_X.Integrator1_CSTATE_p -
        (((rtb_Kxtheta[i + 4] * tuning_GS1_U.X[3] + rtb_Kxtheta[i] * rtb_d_x) +
          rtb_Kxtheta[i + 8] * tuning_GS1_U.X[7]) + rtb_Kxtheta[i + 12] *
         tuning_GS1_U.X[10]);

      /* MATLAB Function: '<S14>/MATLAB Function' */
      rtb_Kix[i] = rtb_d_y;
    }

    /* MATLAB Function: '<S15>/MATLAB Function' */
    /* MATLAB Function 'GS_controller/y_GS_controller/MATLAB Function': '<S19>:1' */
    /*  LQR gain */
    /*  K_lqr = [-0.7348   -0.4267    1.3471    0.2695 */
    /*           -1.4696   -0.8535    2.6943    0.5389 */
    /*           -0.7348   -0.4267    1.3471    0.2695 */
    /*            0.7348    0.4267   -1.3471   -0.2695 */
    /*            1.4696    0.8535   -2.6943   -0.5389 */
    /*            0.7348    0.4267   -1.3471   -0.2695]; */
    /*  Ki_lqr = [ -0.5936 */
    /*             -1.1871 */
    /*             -0.5936 */
    /*              0.5936 */
    /*              1.1871 */
    /*              0.5936] */
    /*  FTC1 gain */
    /*      Ky0  = [-0.8246  -0.5442    1.768    0.3045];         % Ky0 = [a0 b0 c0 d0]   */
    /*      Ky1  = [ 0.1665   0.07562   0.2108   0.3924           % Ky1 = [a1 b1 c1 d1 */
    /*              -0.1798  -0.1609    0.7297   0.1203];         %        a2 b2 c2 d2] */
    /*      Kiy0 =  -0.577;                                       % Kiy0 = i0 */
    /*      Kiy1 = [ 0.1855                                       % Kiy1 = [i1 i2]' */
    /*              -0.09718]; */
    /* '<S19>:1:24' Ky0  = [-0.7825  -0.5218    1.709   0.3008]; */
    /*  Ky0 = [a0 b0 c0 d0]   */
    /*  Ky1 = [a1 b1 c1 d1 */
    /* '<S19>:1:25' Ky1  = [ 0.1679  0.07127    0.195   0.4091           % Ky1 = [a1 b1 c1 d1 */
    /* '<S19>:1:26'             -0.1871  -0.1628   0.7325   0.1174]; */
    /*         a2 b2 c2 d2] */
    /* '<S19>:1:27' Kiy0 =  -0.5773; */
    /*  Kiy0 = i0 */
    /*  Kiy1 = [i1 i2]' */
    /* '<S19>:1:28' Kiy1 = [ 0.1702                                       % Kiy1 = [i1 i2]' */
    /* '<S19>:1:29'             -0.09199]; */
    /* '<S19>:1:31' K_mapping0 = [1 2 1 -1 -2 -1]'; */
    /* '<S19>:1:32' K_mapping1 = [1 0 0  0  0  0;0 2 1 -1 -2 -1]'; */
    /* '<S19>:1:33' K_mapping2 = [0 2 0  0  0  0;1 0 1 -1 -2 -1]'; */
    /* '<S19>:1:34' K_mapping3 = [0 0 1  0  0  0;1 2 0 -1 -2 -1]'; */
    /* '<S19>:1:35' K_mapping4 = [0 0 0 -1  0  0;1 2 1  0 -2 -1]'; */
    /* '<S19>:1:36' K_mapping5 = [0 0 0  0 -2  0;1 2 1 -1  0 -1]'; */
    /* '<S19>:1:37' K_mapping6 = [0 0 0  0  0 -1;1 2 1 -1 -2  0]'; */
    /* '<S19>:1:39' Kyphi = K_mapping1*Ky1*u(1) + K_mapping2*Ky1*u(2) + K_mapping3*Ky1*u(3) + K_mapping4*Ky1*u(4) + K_mapping5*Ky1*u(5) + K_mapping6*Ky1*u(6); */
    for (i = 0; i < 24; i++) {
      rtb_Kyphi[i] = ((((a_1[i] * rtb_gamma_m[0] + b_a_1[i] * rtb_gamma_m[1]) +
                        c_a_1[i] * rtb_gamma_m[2]) + d_a_1[i] * rtb_gamma_m[3])
                      + e_a_1[i] * rtb_gamma_m[4]) + f_a_1[i] * rtb_gamma_m[5];
    }

    /* '<S19>:1:40' Kiy   = K_mapping1*Kiy1*u(1) + K_mapping2*Kiy1*u(2) + K_mapping3*Kiy1*u(3) + K_mapping4*Kiy1*u(4) + K_mapping5*Kiy1*u(5) + K_mapping6*Kiy1*u(6); */
    rtb_d_y = rtb_gamma_m[0];
    rtb_ff_idx_0 = rtb_gamma_m[1];
    rtb_ff_idx_1 = rtb_gamma_m[2];
    rtb_gamma_j = rtb_gamma_m[3];
    rtb_gamma_j_0 = rtb_gamma_m[4];
    rtb_gamma_j_1 = rtb_gamma_m[5];
    for (i = 0; i < 6; i++) {
      rtb_gamma_m[i] = ((((g_a_1[i] * rtb_d_y + h_a_1[i] * rtb_ff_idx_0) +
                          i_a_0[i] * rtb_ff_idx_1) + j_a_0[i] * rtb_gamma_j) +
                        k_a_0[i] * rtb_gamma_j_0) + l_a_0[i] * rtb_gamma_j_1;
    }

    /* Sum: '<S7>/Sum4' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/Y0'
     */
    /* '<S19>:1:42' gain = [Ky0(1:2) Kiy0] + [Kyphi(1,1:2) Kiy(1)]; */
    /*  to display: gain y, yd, int for first rotor */
    rtb_d_y = tuning_GS1_U.X[1] - tuning_GS1_U.Y0[1];

    /* Sum: '<S66>/Sum2' incorporates:
     *  Inport: '<Root>/X'
     *  Integrator: '<S66>/Integrator1'
     *  Product: '<S66>/Product2'
     *  Product: '<S66>/Product3'
     *  SignalConversion: '<S66>/TmpSignal ConversionAtProduct3Inport2'
     */
    tuning_GS1_B.Sum2 = 0.77159399375578352 * tuning_GS1_X.Integrator1_CSTATE_pc
      - (1.3316699428912557 * rtb_d_x + 1.0181167851970618 * tuning_GS1_U.X[3]);

    /* Sum: '<S66>/Sum3' incorporates:
     *  Inport: '<Root>/X'
     *  Integrator: '<S66>/Integrator'
     *  Product: '<S66>/Product1'
     *  Product: '<S66>/Product4'
     *  SignalConversion: '<S66>/TmpSignal ConversionAtProduct1Inport2'
     */
    tuning_GS1_B.Sum3 = -0.744717 * tuning_GS1_X.Integrator_CSTATE - (-1.009425 *
      rtb_d_y + -0.673122 * tuning_GS1_U.X[4]);

    /* RateTransition: '<S6>/T_outer' incorporates:
     *  Inport: '<Root>/X'
     */
    if ((rtmIsMajorTimeStep((&tuning_GS1_M)) &&
         (&tuning_GS1_M)->Timing.TaskCounters.TID[1] == 0) &&
        (rtmIsMajorTimeStep((&tuning_GS1_M)) &&
         (&tuning_GS1_M)->Timing.TaskCounters.TID[2] == 0)) {
      tuning_GS1_B.T_outer[0] = tuning_GS1_B.Sum2;
      tuning_GS1_B.T_outer[1] = tuning_GS1_B.Sum3;
      tuning_GS1_B.T_outer[2] = tuning_GS1_U.X[8];
    }

    /* End of RateTransition: '<S6>/T_outer' */
    if (rtmIsMajorTimeStep((&tuning_GS1_M)) &&
        (&tuning_GS1_M)->Timing.TaskCounters.TID[2] == 0) {
      /* Fcn: '<S6>/Fcn1' */
      tuning_GS1_B.Fcn1 = tuning_GS1_B.T_outer[1] * std::cos
        (tuning_GS1_B.T_outer[2]) + tuning_GS1_B.T_outer[0] * std::sin
        (tuning_GS1_B.T_outer[2]);
    }

    /* MATLAB Function: '<S7>/FFW' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/mode'
     */
    /* MATLAB Function 'Test_config_and_data/FFW': '<S69>:1' */
    /* '<S69>:1:2' ff = [0;0]; */
    rtb_ff_idx_0 = 0.0;
    rtb_ff_idx_1 = 0.0;

    /* '<S69>:1:3' g = 9.81; */
    /*  [x;y] = [cos(t); sin(t)] */
    /* '<S69>:1:5' if (test_mode == 2) */
    if ((tuning_GS1_U.mode == 2.0) && ((rtb_Clock >= 10.0) && (rtb_Clock <= 50.0)))
    {
      /* '<S69>:1:6' if (t >=10) && (t<= 50) */
      /* '<S69>:1:7' axref_N = -cos(t); */
      /* '<S69>:1:8' ayref_N = -sin(t); */
      /* '<S69>:1:10' axref_b = cos(X(8))*cos(X(9))*axref_N + cos(X(8))*sin(X(9))*ayref_N; */
      /* '<S69>:1:11' ayref_b = (sin(X(7))*sin(X(8))*cos(X(9)) - cos(X(7))*sin(X(9)))*axref_N + (sin(X(7))*sin(X(8))*sin(X(9)) + cos(X(7))*cos(X(9)))*ayref_N; */
      /*  azref_b = (cos(X(7))*sin(X(8))*cos(X(9)) + sin(X(7))*sin(X(9)))*axref_N + (cos(X(7))*sin(X(8))*sin(X(9)) - sin(X(7))*cos(X(9)))*ayref_N; */
      /*   */
      /* '<S69>:1:14' ff = [-ayref_b/g; axref_b/g]; */
      rtb_ff_idx_0 = -((std::sin(tuning_GS1_U.X[6]) * std::sin(tuning_GS1_U.X[7])
                        * std::cos(tuning_GS1_U.X[8]) - std::cos(tuning_GS1_U.X
        [6]) * std::sin(tuning_GS1_U.X[8])) * -std::cos(rtb_Clock) + (std::sin
        (tuning_GS1_U.X[6]) * std::sin(tuning_GS1_U.X[7]) * std::sin
        (tuning_GS1_U.X[8]) + std::cos(tuning_GS1_U.X[6]) * std::cos
        (tuning_GS1_U.X[8])) * -std::sin(rtb_Clock)) / 9.81;
      rtb_ff_idx_1 = (std::cos(tuning_GS1_U.X[7]) * std::cos(tuning_GS1_U.X[8]) *
                      -std::cos(rtb_Clock) + std::cos(tuning_GS1_U.X[7]) * std::
                      sin(tuning_GS1_U.X[8]) * -std::sin(rtb_Clock)) / 9.81;
    } else {
      /* '<S69>:1:15' else */
      /* '<S69>:1:16' ff = [0;0]; */
    }

    /* End of MATLAB Function: '<S7>/FFW' */
    if (rtmIsMajorTimeStep((&tuning_GS1_M)) &&
        (&tuning_GS1_M)->Timing.TaskCounters.TID[1] == 0) {
      /* Product: '<S68>/Product' incorporates:
       *  Inport: '<Root>/X'
       *  SignalConversion: '<S68>/TmpSignal ConversionAtProductInport2'
       */
      tuning_GS1_B.Product = 2.20461 * tuning_GS1_U.X[6] + 0.38803200000000004 *
        tuning_GS1_U.X[9];

      /* Product: '<S67>/Product' incorporates:
       *  Inport: '<Root>/X'
       *  SignalConversion: '<S67>/TmpSignal ConversionAtProductInport2'
       */
      tuning_GS1_B.Product_d = 3.4475951709416233 * tuning_GS1_U.X[7] +
        0.53855175374981368 * tuning_GS1_U.X[10];
    }

    if (rtmIsMajorTimeStep((&tuning_GS1_M)) &&
        (&tuning_GS1_M)->Timing.TaskCounters.TID[2] == 0) {
      /* Fcn: '<S6>/Fcn' */
      tuning_GS1_B.Fcn = -tuning_GS1_B.T_outer[1] * std::sin
        (tuning_GS1_B.T_outer[2]) + tuning_GS1_B.T_outer[0] * std::cos
        (tuning_GS1_B.T_outer[2]);
    }

    for (i = 0; i < 6; i++) {
      /* Sum: '<S4>/Sum' incorporates:
       *  Inport: '<Root>/X'
       *  Integrator: '<S16>/Integrator1'
       *  Product: '<S16>/Product'
       *  Product: '<S16>/Product1'
       *  SignalConversion: '<S16>/TmpSignal ConversionAtProduct1Inport2'
       *  Sum: '<S16>/Sum1'
       */
      tmp[i] = (rtb_Kiz[i] * tuning_GS1_X.Integrator1_CSTATE - (rtb_Kz[i + 6] *
                 tuning_GS1_U.X[5] + rtb_Kz[i] * rtb_d_z)) + 2.5179000000000005;

      /* Sum: '<S13>/Sum1' incorporates:
       *  Inport: '<Root>/X'
       *  Integrator: '<S13>/Integrator1'
       *  Product: '<S13>/Product'
       *  Product: '<S13>/Product1'
       *  SignalConversion: '<S13>/TmpSignal ConversionAtProduct1Inport2'
       *  Sum: '<S4>/Sum'
       */
      rtb_Kipsi_0[i] = rtb_Kipsi[i] * tuning_GS1_X.Integrator1_CSTATE_d -
        (rtb_Kpsi[i + 6] * tuning_GS1_U.X[11] + rtb_Kpsi[i] * rtb_d_psi);
    }

    /* Sum: '<S4>/Sum' incorporates:
     *  Constant: '<S14>/Constant'
     */
    rtb_ref_0[0] = rtb_ref[0];
    rtb_ref_0[1] = 0.0;
    rtb_ref_0[2] = rtb_ref[1];
    rtb_ref_0[3] = rtb_ref[2];
    rtb_ref_0[4] = 0.0;
    rtb_ref_0[5] = rtb_ref[3];

    /* Saturate: '<S6>/2Nm ' incorporates:
     *  Sum: '<S68>/Sum1'
     *  Sum: '<S6>/Sum7'
     */
    rtb_ff_idx_0 = (tuning_GS1_B.Fcn1 + rtb_ff_idx_0) - tuning_GS1_B.Product;
    if (rtb_ff_idx_0 > 2.0) {
      /* SignalConversion: '<Root>/TmpSignal ConversionAtControl AllocationInport1' */
      rtb_ff_idx_0 = 2.0;
    } else {
      if (rtb_ff_idx_0 < -2.0) {
        /* SignalConversion: '<Root>/TmpSignal ConversionAtControl AllocationInport1' */
        rtb_ff_idx_0 = -2.0;
      }
    }

    /* End of Saturate: '<S6>/2Nm ' */

    /* Saturate: '<S6>/2Nm' incorporates:
     *  Sum: '<S67>/Sum1'
     *  Sum: '<S6>/Sum8'
     */
    rtb_ff_idx_1 = (tuning_GS1_B.Fcn + rtb_ff_idx_1) - tuning_GS1_B.Product_d;
    if (rtb_ff_idx_1 > 2.0) {
      /* SignalConversion: '<Root>/TmpSignal ConversionAtControl AllocationInport1' */
      rtb_ff_idx_1 = 2.0;
    } else {
      if (rtb_ff_idx_1 < -2.0) {
        /* SignalConversion: '<Root>/TmpSignal ConversionAtControl AllocationInport1' */
        rtb_ff_idx_1 = -2.0;
      }
    }

    /* End of Saturate: '<S6>/2Nm' */
    for (i = 0; i < 6; i++) {
      /* Saturate: '<Root>/                   ' incorporates:
       *  Gain: '<Root>/Control Allocation'
       *  Inport: '<Root>/X'
       *  Integrator: '<S15>/Integrator1'
       *  Product: '<S15>/Product'
       *  Product: '<S15>/Product1'
       *  SignalConversion: '<S15>/TmpSignal ConversionAtProduct1Inport2'
       *  Sum: '<Root>/Sum'
       *  Sum: '<S15>/Sum1'
       *  Sum: '<S4>/Sum'
       */
      rtb_gamma_j = ((rtb_gamma_m[i] * tuning_GS1_X.Integrator1_CSTATE_n -
                      (((rtb_Kyphi[i + 6] * tuning_GS1_U.X[4] + rtb_Kyphi[i] *
                         rtb_d_y) + rtb_Kyphi[i + 12] * tuning_GS1_U.X[6]) +
                       rtb_Kyphi[i + 18] * tuning_GS1_U.X[9])) + ((tmp[i] +
        rtb_Kipsi_0[i]) + rtb_ref_0[i])) +
        (tuning_GS1_ConstP.ControlAllocation_Gain[i + 6] * rtb_ff_idx_1 +
         tuning_GS1_ConstP.ControlAllocation_Gain[i] * rtb_ff_idx_0);
      if (rtb_gamma_j > 8.54858) {
        tuning_GS1_B.u[i] = 8.54858;
      } else if (rtb_gamma_j < 0.0) {
        tuning_GS1_B.u[i] = 0.0;
      } else {
        tuning_GS1_B.u[i] = rtb_gamma_j;
      }

      /* End of Saturate: '<Root>/                   ' */
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
    rtb_T_f[0] = (1.0 - rtb_LOE_out[0]) * tuning_GS1_B.u[0];
    rtb_T_f[1] = (1.0 - rtb_LOE_out[1]) * tuning_GS1_B.u[1];
    rtb_T_f[2] = (1.0 - rtb_LOE_out[2]) * tuning_GS1_B.u[2];
    rtb_T_f[3] = (1.0 - rtb_LOE_out[3]) * tuning_GS1_B.u[3];
    rtb_T_f[4] = (1.0 - rtb_LOE_out[4]) * tuning_GS1_B.u[4];
    rtb_T_f[5] = (1.0 - rtb_LOE_out[5]) * tuning_GS1_B.u[5];

    /* Outport: '<Root>/motor_command' */
    for (i = 0; i < 6; i++) {
      /* Gain: '<S8>/mapping_0_200' incorporates:
       *  Gain: '<S8>/      '
       *  Gain: '<S8>/rads_to_RPM'
       *  Sqrt: '<S8>/Sqrt1'
       *  Sum: '<S8>/Sum3'
       */
      rtb_ff_idx_0 = (std::sqrt(116978.4923343994 * rtb_T_f[i]) * 9.5493 -
                      1250.0) * 0.022857142857142857;

      /* Saturate: '<S8>/Saturation' */
      if (rtb_ff_idx_0 > 200.0) {
        tuning_GS1_Y.motor_command[i] = 200.0;
      } else if (rtb_ff_idx_0 < 0.0) {
        tuning_GS1_Y.motor_command[i] = 0.0;
      } else {
        tuning_GS1_Y.motor_command[i] = rtb_ff_idx_0;
      }

      /* End of Saturate: '<S8>/Saturation' */
    }

    /* End of Outport: '<Root>/motor_command' */

    /* MATLAB Function: '<S7>/MATLAB Function' incorporates:
     *  Inport: '<Root>/Y0'
     *  Inport: '<Root>/mode'
     *  Inport: '<Root>/ref'
     */
    /* MATLAB Function 'Test_config_and_data/MATLAB Function': '<S71>:1' */
    /* '<S71>:1:2' ref = Y0; */
    /* '<S71>:1:3' switch test_mode */
    switch ((int32_T)tuning_GS1_U.mode) {
     case 0:
      /* '<S71>:1:4' case 0      % manual test */
      /*  manual test */
      /* '<S71>:1:5' ref = ref_manual; */
      rtb_ref[0] = tuning_GS1_U.ref[0];
      rtb_ref[1] = tuning_GS1_U.ref[1];
      rtb_ref[2] = tuning_GS1_U.ref[2];
      rtb_ref[3] = tuning_GS1_U.ref[3];

      /* '<S71>:1:6' if t>=25 */
      if (rtb_Clock >= 25.0) {
        /* '<S71>:1:7' ref = Y0; */
        rtb_ref[0] = tuning_GS1_U.Y0[0];
        rtb_ref[1] = tuning_GS1_U.Y0[1];
        rtb_ref[2] = tuning_GS1_U.Y0[2];
        rtb_ref[3] = tuning_GS1_U.Y0[3];
      }
      break;

     case 1:
      /* '<S71>:1:9' case 1      % waypoint */
      /*  waypoint */
      /* '<S71>:1:10' if t<=15 */
      if (rtb_Clock <= 15.0) {
        /* '<S71>:1:11' ref = [Y0(1); Y0(2); 1; Y0(4)]; */
        rtb_ref[0] = tuning_GS1_U.Y0[0];
        rtb_ref[1] = tuning_GS1_U.Y0[1];
        rtb_ref[2] = 1.0;
        rtb_ref[3] = tuning_GS1_U.Y0[3];
      } else if (rtb_Clock <= 25.0) {
        /* '<S71>:1:12' elseif t <= 25 */
        /* '<S71>:1:13' ref = [Y0(1)+1; Y0(2)-1; 1; Y0(4)]; */
        rtb_ref[0] = tuning_GS1_U.Y0[0] + 1.0;
        rtb_ref[1] = tuning_GS1_U.Y0[1] - 1.0;
        rtb_ref[2] = 1.0;
        rtb_ref[3] = tuning_GS1_U.Y0[3];
      } else if (rtb_Clock <= 35.0) {
        /* '<S71>:1:14' elseif t <=35 */
        /* '<S71>:1:15' ref = [Y0(1)-1; Y0(2)+1; 1; Y0(4)]; */
        rtb_ref[0] = tuning_GS1_U.Y0[0] - 1.0;
        rtb_ref[1] = tuning_GS1_U.Y0[1] + 1.0;
        rtb_ref[2] = 1.0;
        rtb_ref[3] = tuning_GS1_U.Y0[3];
      } else if (rtb_Clock <= 45.0) {
        /* '<S71>:1:16' elseif t <=45 */
        /* '<S71>:1:17' ref = [Y0(1)-1; Y0(2)+1; 1; Y0(4)]; */
        rtb_ref[0] = tuning_GS1_U.Y0[0] - 1.0;
        rtb_ref[1] = tuning_GS1_U.Y0[1] + 1.0;
        rtb_ref[2] = 1.0;
        rtb_ref[3] = tuning_GS1_U.Y0[3];
      } else if (rtb_Clock <= 55.0) {
        /* '<S71>:1:18' elseif t <=55 */
        /* '<S71>:1:19' ref = [Y0(1); Y0(2); 1; Y0(4)]; */
        rtb_ref[0] = tuning_GS1_U.Y0[0];
        rtb_ref[1] = tuning_GS1_U.Y0[1];
        rtb_ref[2] = 1.0;
        rtb_ref[3] = tuning_GS1_U.Y0[3];
      } else {
        /* '<S71>:1:20' else */
        /* '<S71>:1:21' ref = Y0; */
        rtb_ref[0] = tuning_GS1_U.Y0[0];
        rtb_ref[1] = tuning_GS1_U.Y0[1];
        rtb_ref[2] = tuning_GS1_U.Y0[2];
        rtb_ref[3] = tuning_GS1_U.Y0[3];
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
      /* '<S71>:1:34' case 2      % circular tracking */
      /*  circular tracking */
      /* '<S71>:1:35' if t<=10 */
      if (rtb_Clock <= 10.0) {
        /* '<S71>:1:36' ref = [Y0(1); Y0(2); 0.75; Y0(4)]; */
        rtb_ref[0] = tuning_GS1_U.Y0[0];
        rtb_ref[1] = tuning_GS1_U.Y0[1];
        rtb_ref[2] = 0.75;
        rtb_ref[3] = tuning_GS1_U.Y0[3];
      } else if (rtb_Clock <= 50.0) {
        /* '<S71>:1:37' elseif t <= 50 */
        /* '<S71>:1:38' ref = [Y0(1)+cos(t); Y0(2)+sin(t); 0.75; Y0(4)]; */
        rtb_ref[0] = tuning_GS1_U.Y0[0] + std::cos(rtb_Clock);
        rtb_ref[1] = tuning_GS1_U.Y0[1] + std::sin(rtb_Clock);
        rtb_ref[2] = 0.75;
        rtb_ref[3] = tuning_GS1_U.Y0[3];
      } else if (rtb_Clock <= 60.0) {
        /* '<S71>:1:39' elseif t <= 60 */
        /* '<S71>:1:40' ref = [Y0(1); Y0(2); 0.75; Y0(4)]; */
        rtb_ref[0] = tuning_GS1_U.Y0[0];
        rtb_ref[1] = tuning_GS1_U.Y0[1];
        rtb_ref[2] = 0.75;
        rtb_ref[3] = tuning_GS1_U.Y0[3];
      } else {
        /* '<S71>:1:41' else */
        /* '<S71>:1:42' ref = Y0; */
        rtb_ref[0] = tuning_GS1_U.Y0[0];
        rtb_ref[1] = tuning_GS1_U.Y0[1];
        rtb_ref[2] = tuning_GS1_U.Y0[2];
        rtb_ref[3] = tuning_GS1_U.Y0[3];
      }

      /*          ref = [cos(t); sin(t);min(t,15);Y0(4)]; */
      break;

     default:
      /* '<S71>:1:45' otherwise */
      /* '<S71>:1:46' ref = Y0; */
      rtb_ref[0] = tuning_GS1_U.Y0[0];
      rtb_ref[1] = tuning_GS1_U.Y0[1];
      rtb_ref[2] = tuning_GS1_U.Y0[2];
      rtb_ref[3] = tuning_GS1_U.Y0[3];
      break;
    }

    /* End of MATLAB Function: '<S7>/MATLAB Function' */

    /* Outport: '<Root>/ref_out' */
    tuning_GS1_Y.ref_out[0] = rtb_ref[0];
    tuning_GS1_Y.ref_out[1] = rtb_ref[1];
    tuning_GS1_Y.ref_out[2] = rtb_ref[2];
    tuning_GS1_Y.ref_out[3] = rtb_ref[3];

    /* Outport: '<Root>/LOE_true' */
    for (i = 0; i < 6; i++) {
      tuning_GS1_Y.LOE_true[i] = rtb_LOE_out[i];
    }

    /* End of Outport: '<Root>/LOE_true' */
    if (rtmIsMajorTimeStep((&tuning_GS1_M)) &&
        (&tuning_GS1_M)->Timing.TaskCounters.TID[1] == 0) {
      /* Outport: '<Root>/LOE13_estimated' */
      tuning_GS1_Y.LOE13_estimated[0] = rtb_gamma_idx_0;
      tuning_GS1_Y.LOE13_estimated[1] = rtb_gamma_idx_1;
      tuning_GS1_Y.LOE13_estimated[2] = rtb_gamma_idx_2;
    }

    for (i = 0; i < 6; i++) {
      /* Outport: '<Root>/thrust_pre' */
      tuning_GS1_Y.thrust_pre[i] = tuning_GS1_B.u[i];

      /* Outport: '<Root>/thrust_after' */
      tuning_GS1_Y.thrust_after[i] = rtb_T_f[i];
    }

    if (rtmIsMajorTimeStep((&tuning_GS1_M)) &&
        (&tuning_GS1_M)->Timing.TaskCounters.TID[1] == 0) {
      /* Outport: '<Root>/acc_Kalman' */
      tuning_GS1_Y.acc_Kalman[0] = rtb_Add_a[3];

      /* Outport: '<Root>/M_Kalman' */
      tuning_GS1_Y.M_Kalman[0] = rtb_Sum1[0];

      /* Outport: '<Root>/vel_Kalman' */
      tuning_GS1_Y.vel_Kalman[0] = rtb_Add_a[0];

      /* Outport: '<Root>/acc_Kalman' */
      tuning_GS1_Y.acc_Kalman[1] = rtb_Add_a[4];

      /* Outport: '<Root>/M_Kalman' */
      tuning_GS1_Y.M_Kalman[1] = rtb_Sum1[1];

      /* Outport: '<Root>/vel_Kalman' */
      tuning_GS1_Y.vel_Kalman[1] = rtb_Add_a[1];

      /* Outport: '<Root>/acc_Kalman' */
      tuning_GS1_Y.acc_Kalman[2] = rtb_Add_a[5];

      /* Outport: '<Root>/M_Kalman' */
      tuning_GS1_Y.M_Kalman[2] = rtb_Sum1[2];

      /* Outport: '<Root>/vel_Kalman' */
      tuning_GS1_Y.vel_Kalman[2] = rtb_Add_a[2];
    }

    /* Outport: '<Root>/gain_GS' incorporates:
     *  MATLAB Function: '<S13>/MATLAB Function'
     *  MATLAB Function: '<S14>/MATLAB Function'
     *  MATLAB Function: '<S15>/MATLAB Function'
     *  MATLAB Function: '<S16>/MATLAB Function'
     */
    tuning_GS1_Y.gain_GS[0] = rtb_Kz[0];
    tuning_GS1_Y.gain_GS[3] = rtb_Kpsi[0];
    tuning_GS1_Y.gain_GS[6] = -1.788 + rtb_Kxtheta[0];
    tuning_GS1_Y.gain_GS[9] = -0.7825 + rtb_Kyphi[0];
    tuning_GS1_Y.gain_GS[1] = rtb_Kz[6];
    tuning_GS1_Y.gain_GS[4] = rtb_Kpsi[6];
    tuning_GS1_Y.gain_GS[7] = -1.367 + rtb_Kxtheta[4];
    tuning_GS1_Y.gain_GS[10] = -0.5218 + rtb_Kyphi[6];
    tuning_GS1_Y.gain_GS[2] = rtb_Kiz[0];
    tuning_GS1_Y.gain_GS[5] = rtb_Kipsi[0];
    tuning_GS1_Y.gain_GS[8] = -1.036 + rtb_Kix[0];
    tuning_GS1_Y.gain_GS[11] = -0.5773 + rtb_gamma_m[0];

    /* Sum: '<S7>/Sum' incorporates:
     *  Inport: '<Root>/Y0'
     */
    rtb_ref[0] -= tuning_GS1_U.Y0[0];
    rtb_ref[1] -= tuning_GS1_U.Y0[1];
    rtb_ref[2] -= tuning_GS1_U.Y0[2];
    rtb_Clock = rtb_ref[3] - tuning_GS1_U.Y0[3];

    /* Saturate: '<S13>/yaw' */
    if (rtb_Clock > 3.1415926535897931) {
      rtb_Clock = 3.1415926535897931;
    } else {
      if (rtb_Clock < -3.1415926535897931) {
        rtb_Clock = -3.1415926535897931;
      }
    }

    /* End of Saturate: '<S13>/yaw' */

    /* Sum: '<S13>/Sum3' */
    tuning_GS1_B.Sum3_d = rtb_Clock - rtb_d_psi;

    /* Saturate: '<S14>/x' */
    if (rtb_ref[0] > 2.0) {
      rtb_Clock = 2.0;
    } else if (rtb_ref[0] < -2.0) {
      rtb_Clock = -2.0;
    } else {
      rtb_Clock = rtb_ref[0];
    }

    /* End of Saturate: '<S14>/x' */

    /* Sum: '<S14>/Sum3' */
    tuning_GS1_B.Sum3_n = rtb_Clock - rtb_d_x;

    /* Saturate: '<S15>/y' */
    if (rtb_ref[1] > 2.0) {
      rtb_Clock = 2.0;
    } else if (rtb_ref[1] < -2.0) {
      rtb_Clock = -2.0;
    } else {
      rtb_Clock = rtb_ref[1];
    }

    /* End of Saturate: '<S15>/y' */

    /* Sum: '<S15>/Sum3' */
    tuning_GS1_B.Sum3_h = rtb_Clock - rtb_d_y;

    /* Saturate: '<S16>/z' */
    if (rtb_ref[2] > 1.75) {
      rtb_Clock = 1.75;
    } else if (rtb_ref[2] < 0.0) {
      rtb_Clock = 0.0;
    } else {
      rtb_Clock = rtb_ref[2];
    }

    /* End of Saturate: '<S16>/z' */

    /* Sum: '<S16>/Sum3' */
    tuning_GS1_B.Sum3_l = rtb_Clock - rtb_d_z;
    if (rtmIsMajorTimeStep((&tuning_GS1_M)) &&
        (&tuning_GS1_M)->Timing.TaskCounters.TID[1] == 0) {
      /* Outputs for Enabled SubSystem: '<S39>/MeasurementUpdate' incorporates:
       *  EnablePort: '<S64>/Enable'
       */
      if (rtmIsMajorTimeStep((&tuning_GS1_M)) &&
          (!tuning_GS1_DW.MeasurementUpdate_MODE)) {
        tuning_GS1_DW.MeasurementUpdate_MODE = true;
      }

      if (tuning_GS1_DW.MeasurementUpdate_MODE) {
        for (i = 0; i < 3; i++) {
          /* Product: '<S64>/C[k]*xhat[k|k-1]' incorporates:
           *  Constant: '<S5>/C'
           *  Sum: '<S64>/Add1'
           */
          rtb_Add_f[i] = 0.0;
          for (i_0 = 0; i_0 < 6; i_0++) {
            rtb_Add_f[i] += tuning_GS1_ConstP.C_Value[3 * i_0 + i] *
              rtb_MemoryX[i_0];
          }

          /* End of Product: '<S64>/C[k]*xhat[k|k-1]' */

          /* Sum: '<S64>/Sum' incorporates:
           *  Inport: '<Root>/X'
           *  Product: '<S64>/Product3'
           *  Sum: '<S64>/Add1'
           */
          rtb_Add_f_0[i] = tuning_GS1_U.X[9 + i] - rtb_Add_f[i];
        }

        /* Product: '<S64>/Product3' incorporates:
         *  Constant: '<S21>/KalmanGainL'
         */
        for (i = 0; i < 6; i++) {
          tuning_GS1_B.Product3[i] = 0.0;
          tuning_GS1_B.Product3[i] += tuning_GS1_ConstP.KalmanGainL_Value[i] *
            rtb_Add_f_0[0];
          tuning_GS1_B.Product3[i] += tuning_GS1_ConstP.KalmanGainL_Value[i + 6]
            * rtb_Add_f_0[1];
          tuning_GS1_B.Product3[i] += tuning_GS1_ConstP.KalmanGainL_Value[i + 12]
            * rtb_Add_f_0[2];
        }
      }

      /* End of Outputs for SubSystem: '<S39>/MeasurementUpdate' */
      for (i = 0; i < 6; i++) {
        /* Product: '<S39>/A[k]*xhat[k|k-1]' incorporates:
         *  Constant: '<S5>/A'
         *  Sum: '<S39>/Add'
         */
        tmp[i] = 0.0;
        for (i_0 = 0; i_0 < 6; i_0++) {
          tmp[i] += tuning_GS1_ConstP.A_Value[6 * i_0 + i] * rtb_MemoryX[i_0];
        }

        /* End of Product: '<S39>/A[k]*xhat[k|k-1]' */

        /* Sum: '<S39>/Add' */
        rtb_Add[i] = tmp[i] + tuning_GS1_B.Product3[i];
      }
    }

    /* Saturate: '<S66>/x' */
    if (rtb_ref[0] > 2.0) {
      rtb_Clock = 2.0;
    } else if (rtb_ref[0] < -2.0) {
      rtb_Clock = -2.0;
    } else {
      rtb_Clock = rtb_ref[0];
    }

    /* End of Saturate: '<S66>/x' */

    /* Sum: '<S66>/Sum1' */
    tuning_GS1_B.Sum1 = rtb_Clock - rtb_d_x;

    /* Saturate: '<S66>/y' */
    if (rtb_ref[1] > 2.0) {
      rtb_Clock = 2.0;
    } else if (rtb_ref[1] < -2.0) {
      rtb_Clock = -2.0;
    } else {
      rtb_Clock = rtb_ref[1];
    }

    /* End of Saturate: '<S66>/y' */

    /* Sum: '<S66>/Sum4' */
    tuning_GS1_B.Sum4 = rtb_Clock - rtb_d_y;
  }

  if (rtmIsMajorTimeStep((&tuning_GS1_M))) {
    int32_T i;
    if (rtmIsMajorTimeStep((&tuning_GS1_M)) &&
        (&tuning_GS1_M)->Timing.TaskCounters.TID[1] == 0) {
      /* Update for Delay: '<S5>/MemoryX' */
      tuning_GS1_DW.icLoad = 0U;
      for (i = 0; i < 6; i++) {
        /* Update for Memory: '<S3>/Memory' */
        tuning_GS1_DW.Memory_PreviousInput[i] = tuning_GS1_B.u[i];

        /* Update for Delay: '<S5>/MemoryX' */
        tuning_GS1_DW.MemoryX_DSTATE[i] = rtb_Add[i];
      }
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep((&tuning_GS1_M))) {
    rt_ertODEUpdateContinuousStates(&(&tuning_GS1_M)->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++(&tuning_GS1_M)->Timing.clockTick0)) {
      ++(&tuning_GS1_M)->Timing.clockTickH0;
    }

    (&tuning_GS1_M)->Timing.t[0] = rtsiGetSolverStopTime(&(&tuning_GS1_M)
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
      (&tuning_GS1_M)->Timing.clockTick1++;
      if (!(&tuning_GS1_M)->Timing.clockTick1) {
        (&tuning_GS1_M)->Timing.clockTickH1++;
      }
    }

    rate_scheduler((&tuning_GS1_M));
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void tuning_GS1ModelClass::tuning_GS1_derivatives()
{
  XDot_tuning_GS1_T *_rtXdot;
  _rtXdot = ((XDot_tuning_GS1_T *) (&tuning_GS1_M)->derivs);

  /* Derivatives for Integrator: '<S16>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = tuning_GS1_B.Sum3_l;

  /* Derivatives for Integrator: '<S13>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_d = tuning_GS1_B.Sum3_d;

  /* Derivatives for Integrator: '<S14>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_p = tuning_GS1_B.Sum3_n;

  /* Derivatives for Integrator: '<S15>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_n = tuning_GS1_B.Sum3_h;

  /* Derivatives for Integrator: '<S66>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_pc = tuning_GS1_B.Sum1;

  /* Derivatives for Integrator: '<S66>/Integrator' */
  _rtXdot->Integrator_CSTATE = tuning_GS1_B.Sum4;
}

/* Model initialize function */
void tuning_GS1ModelClass::initialize()
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)(&tuning_GS1_M), 0,
                sizeof(RT_MODEL_tuning_GS1_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&(&tuning_GS1_M)->solverInfo, &(&tuning_GS1_M)
                          ->Timing.simTimeStep);
    rtsiSetTPtr(&(&tuning_GS1_M)->solverInfo, &rtmGetTPtr((&tuning_GS1_M)));
    rtsiSetStepSizePtr(&(&tuning_GS1_M)->solverInfo, &(&tuning_GS1_M)
                       ->Timing.stepSize0);
    rtsiSetdXPtr(&(&tuning_GS1_M)->solverInfo, &(&tuning_GS1_M)->derivs);
    rtsiSetContStatesPtr(&(&tuning_GS1_M)->solverInfo, (real_T **)
                         &(&tuning_GS1_M)->contStates);
    rtsiSetNumContStatesPtr(&(&tuning_GS1_M)->solverInfo, &(&tuning_GS1_M)
      ->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&tuning_GS1_M)->solverInfo,
      &(&tuning_GS1_M)->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&tuning_GS1_M)->solverInfo,
      &(&tuning_GS1_M)->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&tuning_GS1_M)->solverInfo,
      &(&tuning_GS1_M)->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&(&tuning_GS1_M)->solverInfo, (&rtmGetErrorStatus
      ((&tuning_GS1_M))));
    rtsiSetRTModelPtr(&(&tuning_GS1_M)->solverInfo, (&tuning_GS1_M));
  }

  rtsiSetSimTimeStep(&(&tuning_GS1_M)->solverInfo, MAJOR_TIME_STEP);
  (&tuning_GS1_M)->intgData.y = (&tuning_GS1_M)->odeY;
  (&tuning_GS1_M)->intgData.f[0] = (&tuning_GS1_M)->odeF[0];
  (&tuning_GS1_M)->intgData.f[1] = (&tuning_GS1_M)->odeF[1];
  (&tuning_GS1_M)->intgData.f[2] = (&tuning_GS1_M)->odeF[2];
  (&tuning_GS1_M)->intgData.f[3] = (&tuning_GS1_M)->odeF[3];
  getRTM()->contStates = ((X_tuning_GS1_T *) &tuning_GS1_X);
  rtsiSetSolverData(&(&tuning_GS1_M)->solverInfo, (void *)&(&tuning_GS1_M)
                    ->intgData);
  rtsiSetSolverName(&(&tuning_GS1_M)->solverInfo,"ode4");
  rtmSetTPtr(getRTM(), &(&tuning_GS1_M)->Timing.tArray[0]);
  (&tuning_GS1_M)->Timing.stepSize0 = 0.001;

  /* block I/O */
  (void) memset(((void *) &tuning_GS1_B), 0,
                sizeof(B_tuning_GS1_T));

  /* states (continuous) */
  {
    (void) memset((void *)&tuning_GS1_X, 0,
                  sizeof(X_tuning_GS1_T));
  }

  /* states (dwork) */
  (void) memset((void *)&tuning_GS1_DW, 0,
                sizeof(DW_tuning_GS1_T));

  /* external inputs */
  (void)memset((void *)&tuning_GS1_U, 0, sizeof(ExtU_tuning_GS1_T));

  /* external outputs */
  (void) memset((void *)&tuning_GS1_Y, 0,
                sizeof(ExtY_tuning_GS1_T));

  {
    int32_T i;

    /* InitializeConditions for Delay: '<S5>/MemoryX' */
    tuning_GS1_DW.icLoad = 1U;

    /* InitializeConditions for Integrator: '<S16>/Integrator1' */
    tuning_GS1_X.Integrator1_CSTATE = 0.0;

    /* InitializeConditions for Integrator: '<S13>/Integrator1' */
    tuning_GS1_X.Integrator1_CSTATE_d = 0.0;

    /* InitializeConditions for Integrator: '<S14>/Integrator1' */
    tuning_GS1_X.Integrator1_CSTATE_p = 0.0;

    /* InitializeConditions for Integrator: '<S15>/Integrator1' */
    tuning_GS1_X.Integrator1_CSTATE_n = 0.0;

    /* InitializeConditions for Integrator: '<S66>/Integrator1' */
    tuning_GS1_X.Integrator1_CSTATE_pc = 0.0;

    /* InitializeConditions for Integrator: '<S66>/Integrator' */
    tuning_GS1_X.Integrator_CSTATE = 0.0;

    /* SystemInitialize for Enabled SubSystem: '<S39>/MeasurementUpdate' */
    /* SystemInitialize for Atomic SubSystem: '<S5>/UseCurrentEstimator' */
    /* SystemInitialize for Enabled SubSystem: '<S44>/Enabled Subsystem' */
    for (i = 0; i < 6; i++) {
      /* InitializeConditions for Memory: '<S3>/Memory' */
      tuning_GS1_DW.Memory_PreviousInput[i] = 2.5179000000000005;

      /* SystemInitialize for Outport: '<S65>/deltax' */
      tuning_GS1_B.Product2[i] = 0.0;

      /* SystemInitialize for Outport: '<S64>/L*(y[k]-yhat[k|k-1])' */
      tuning_GS1_B.Product3[i] = 0.0;
    }

    /* End of SystemInitialize for SubSystem: '<S44>/Enabled Subsystem' */
    /* End of SystemInitialize for SubSystem: '<S5>/UseCurrentEstimator' */
    /* End of SystemInitialize for SubSystem: '<S39>/MeasurementUpdate' */
  }
}

/* Model terminate function */
void tuning_GS1ModelClass::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
tuning_GS1ModelClass::tuning_GS1ModelClass()
{
}

/* Destructor */
tuning_GS1ModelClass::~tuning_GS1ModelClass()
{
  /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_tuning_GS1_T * tuning_GS1ModelClass::getRTM()
{
  return (&tuning_GS1_M);
}
