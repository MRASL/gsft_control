/*
 * tuning_GS2.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "tuning_GS2".
 *
 * Model version              : 1.2323
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Mon Oct 29 12:44:53 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Passed (1), Warnings (3), Error (0)
 */

#include "tuning_GS2.h"
#include "tuning_GS2_private.h"

static void rate_scheduler(RT_MODEL_tuning_GS2_T *const tuning_GS2_M);

/*
 *   This function updates active task flag for each subrate.
 * The function is called at model base rate, hence the
 * generated code self-manages all its subrates.
 */
static void rate_scheduler(RT_MODEL_tuning_GS2_T *const tuning_GS2_M)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (tuning_GS2_M->Timing.TaskCounters.TID[2])++;
  if ((tuning_GS2_M->Timing.TaskCounters.TID[2]) > 4) {/* Sample time: [0.005s, 0.0s] */
    tuning_GS2_M->Timing.TaskCounters.TID[2] = 0;
  }
}

/*
 * This function updates continuous states using the ODE4 fixed-step
 * solver algorithm
 */
void tuning_GS2ModelClass::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
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
  tuning_GS2_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  this->step();
  tuning_GS2_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  this->step();
  tuning_GS2_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  this->step();
  tuning_GS2_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void tuning_GS2ModelClass::step()
{
  /* local block i/o variables */
  real_T rtb_Add[6];
  if (rtmIsMajorTimeStep((&tuning_GS2_M))) {
    /* set solver stop time */
    if (!((&tuning_GS2_M)->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&(&tuning_GS2_M)->solverInfo, (((&tuning_GS2_M)
        ->Timing.clockTickH0 + 1) * (&tuning_GS2_M)->Timing.stepSize0 *
        4294967296.0));
    } else {
      rtsiSetSolverStopTime(&(&tuning_GS2_M)->solverInfo, (((&tuning_GS2_M)
        ->Timing.clockTick0 + 1) * (&tuning_GS2_M)->Timing.stepSize0 +
        (&tuning_GS2_M)->Timing.clockTickH0 * (&tuning_GS2_M)->Timing.stepSize0 *
        4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep((&tuning_GS2_M))) {
    (&tuning_GS2_M)->Timing.t[0] = rtsiGetT(&(&tuning_GS2_M)->solverInfo);
  }

  {
    real_T gamma_T;
    real_T Kix;
    real_T LOE_M;
    real_T Kiy;
    real_T LOE_L;
    real_T LOE_N;
    real_T rtb_Sum1_l[3];
    real_T rtb_Add_a[6];
    real_T rtb_LOE_out[6];
    real_T rtb_gamma_m[6];
    real_T rtb_ControlAllocation[4];
    real_T rtb_d_z;
    real_T rtb_d_x;
    real_T rtb_d_y;
    real_T rtb_d_psi;
    real_T rtb_Clock;
    real_T rtb_MemoryX[6];
    int32_T i;
    real_T rtb_Add_f[3];
    real_T rtb_Add_f_0[3];
    int32_T i_0;
    real_T rtb_Kx;
    real_T rtb_Ky;
    real_T rtb_ref_idx_3;
    real_T rtb_ff_idx_1;
    real_T rtb_ff_idx_0;
    real_T rtb_gamma_idx_2;
    real_T rtb_gamma_idx_1;
    real_T rtb_gamma_idx_0;
    real_T rtb_ref_idx_2;
    real_T rtb_Kz_idx_0;
    real_T rtb_Kz_idx_1;
    real_T rtb_Kx_idx_0;
    real_T rtb_Ky_idx_0;
    real_T rtb_Kpsi_idx_0;
    real_T rtb_Kpsi_idx_1;
    real_T y;

    /* Clock: '<Root>/Clock' */
    rtb_Clock = (&tuning_GS2_M)->Timing.t[0];

    /* MATLAB Function 'Test_config_and_data/LOE_': '<S70>:1' */
    /* '<S70>:1:2' LOE_out = [0;0;0;0;0;0]; */
    /* '<S70>:1:3' for i = 1:6 */
    /* MATLAB Function 'FDD': '<S2>:1' */
    /* '<S2>:1:2' gamma = [0 0 0 0 0 0]'; */
    /* '<S2>:1:3' for i = 1:6 */
    for (i = 0; i < 6; i++) {
      /* MATLAB Function: '<S6>/LOE_' incorporates:
       *  Inport: '<Root>/LOE_a'
       *  Inport: '<Root>/LOE_t'
       */
      rtb_LOE_out[i] = 0.0;

      /* '<S70>:1:4' if t>= LOE_t(i) */
      if (rtb_Clock >= tuning_GS2_U.LOE_t[i]) {
        /* '<S70>:1:5' LOE_out(i) = LOE(i); */
        rtb_LOE_out[i] = tuning_GS2_U.LOE_a[i];
      }

      /* End of MATLAB Function: '<S6>/LOE_' */

      /* MATLAB Function: '<Root>/FDD' incorporates:
       *  Inport: '<Root>/LOE_a'
       *  Inport: '<Root>/LOE_t'
       */
      /* '<S2>:1:4' if time <= LOE_moment(i) */
      if (rtb_Clock <= tuning_GS2_U.LOE_t[i]) {
        /* '<S2>:1:5' gamma(i) = 0; */
        rtb_gamma_m[i] = 0.0;
      } else if (rtb_Clock <= tuning_GS2_U.LOE_t[i] + 1.5) {
        /* '<S2>:1:6' elseif time <= LOE_moment(i)+1.5 */
        /* '<S2>:1:7' gamma(i) = LOE_amplitude(i)*(time - LOE_moment(i))/1.5; */
        rtb_gamma_m[i] = (rtb_Clock - tuning_GS2_U.LOE_t[i]) *
          tuning_GS2_U.LOE_a[i] / 1.5;
      } else {
        /* '<S2>:1:8' else */
        /* '<S2>:1:9' gamma(i) = LOE_amplitude(i); */
        rtb_gamma_m[i] = tuning_GS2_U.LOE_a[i];
      }

      /* End of MATLAB Function: '<Root>/FDD' */
    }

    if (rtmIsMajorTimeStep((&tuning_GS2_M)) &&
        (&tuning_GS2_M)->Timing.TaskCounters.TID[1] == 0) {
      /* Delay: '<S5>/MemoryX' */
      for (i = 0; i < 6; i++) {
        if (tuning_GS2_DW.icLoad != 0) {
          tuning_GS2_DW.MemoryX_DSTATE[i] = 0.0;
        }

        rtb_MemoryX[i] = tuning_GS2_DW.MemoryX_DSTATE[i];
      }

      /* Outputs for Atomic SubSystem: '<S5>/UseCurrentEstimator' */
      /* Outputs for Enabled SubSystem: '<S47>/Enabled Subsystem' incorporates:
       *  EnablePort: '<S68>/Enable'
       */
      if (!tuning_GS2_DW.EnabledSubsystem_MODE) {
        tuning_GS2_DW.EnabledSubsystem_MODE = true;
      }

      /* Sum: '<S68>/Add1' incorporates:
       *  Constant: '<S5>/C'
       *  Delay: '<S5>/MemoryX'
       *  Inport: '<Root>/X'
       *  Product: '<S68>/Product'
       *  Product: '<S68>/Product2'
       */
      for (i = 0; i < 3; i++) {
        rtb_ff_idx_0 = 0.0;
        for (i_0 = 0; i_0 < 6; i_0++) {
          rtb_ff_idx_0 += tuning_GS2_ConstP.C_Value[3 * i_0 + i] *
            tuning_GS2_DW.MemoryX_DSTATE[i_0];
        }

        rtb_Add_f[i] = tuning_GS2_U.X[9 + i] - rtb_ff_idx_0;
      }

      /* End of Sum: '<S68>/Add1' */
      for (i = 0; i < 6; i++) {
        /* Product: '<S68>/Product2' incorporates:
         *  Constant: '<S24>/KalmanGainM'
         */
        tuning_GS2_B.Product2[i] = 0.0;
        tuning_GS2_B.Product2[i] += tuning_GS2_ConstP.KalmanGainM_Value[i] *
          rtb_Add_f[0];
        tuning_GS2_B.Product2[i] += tuning_GS2_ConstP.KalmanGainM_Value[i + 6] *
          rtb_Add_f[1];
        tuning_GS2_B.Product2[i] += tuning_GS2_ConstP.KalmanGainM_Value[i + 12] *
          rtb_Add_f[2];

        /* Sum: '<S47>/Add' incorporates:
         *  Delay: '<S5>/MemoryX'
         */
        rtb_Add_a[i] = tuning_GS2_B.Product2[i] + tuning_GS2_DW.MemoryX_DSTATE[i];
      }

      /* End of Outputs for SubSystem: '<S47>/Enabled Subsystem' */
      /* End of Outputs for SubSystem: '<S5>/UseCurrentEstimator' */

      /* Product: '<S3>/Product1' incorporates:
       *  Constant: '<S3>/Constant1'
       */
      for (i = 0; i < 3; i++) {
        rtb_Sum1_l[i] = tuning_GS2_ConstP.Constant1_Value[i + 6] * rtb_Add_a[2]
          + (tuning_GS2_ConstP.Constant1_Value[i + 3] * rtb_Add_a[1] +
             tuning_GS2_ConstP.Constant1_Value[i] * rtb_Add_a[0]);
      }

      /* End of Product: '<S3>/Product1' */

      /* Sum: '<S8>/Sum1' incorporates:
       *  Product: '<S10>/i x k'
       *  Product: '<S10>/j x i'
       *  Product: '<S10>/k x j'
       *  Product: '<S11>/i x j'
       *  Product: '<S11>/j x k'
       *  Product: '<S11>/k x i'
       */
      rtb_Add_f[0] = rtb_Add_a[1] * rtb_Sum1_l[2];
      rtb_Add_f[1] = rtb_Add_a[2] * rtb_Sum1_l[0];
      rtb_Add_f[2] = rtb_Add_a[0] * rtb_Sum1_l[1];
      rtb_Add_f_0[0] = rtb_Add_a[2] * rtb_Sum1_l[1];
      rtb_Add_f_0[1] = rtb_Add_a[0] * rtb_Sum1_l[2];
      rtb_Add_f_0[2] = rtb_Add_a[1] * rtb_Sum1_l[0];

      /* Sum: '<S3>/Sum3' incorporates:
       *  Constant: '<S3>/Constant'
       *  Constant: '<S3>/Constant1'
       *  Product: '<S3>/Product'
       *  Sum: '<S8>/Sum1'
       */
      for (i = 0; i < 3; i++) {
        rtb_Sum1_l[i] = (((tuning_GS2_ConstP.Constant1_Value[i + 3] * rtb_Add_a
                           [4] + tuning_GS2_ConstP.Constant1_Value[i] *
                           rtb_Add_a[3]) + tuning_GS2_ConstP.Constant1_Value[i +
                          6] * rtb_Add_a[5]) +
                         tuning_GS2_ConstP.Constant_Value[i]) + (rtb_Add_f[i] -
          rtb_Add_f_0[i]);
      }

      /* End of Sum: '<S3>/Sum3' */

      /* MATLAB Function: '<S3>/MATLAB Function1' incorporates:
       *  Memory: '<S3>/Memory'
       */
      /* MATLAB Function 'FDD_Kalman/MATLAB Function1': '<S9>:1' */
      /* '<S9>:1:2' arm = 0.215; */
      /* '<S9>:1:2' factor = 0.0365; */
      /* '<S9>:1:4' M = [arm/2 arm arm/2; */
      /* '<S9>:1:5'       -sqrt(3)*arm/2 0 sqrt(3)*arm/2; */
      /* '<S9>:1:6'       -factor factor -factor]; */
      /* '<S9>:1:8' diff = [u(1) - u(4) ; */
      /* '<S9>:1:9'         u(2) - u(5) ; */
      /* '<S9>:1:10'         u(3) - u(6) ]; */
      /* '<S9>:1:11' Residu = diff - M\y; */
      rtb_gamma_idx_1 = rtb_Sum1_l[0] - rtb_Sum1_l[1] * -0.57735026918962584;
      rtb_gamma_idx_2 = ((rtb_Sum1_l[2] - rtb_Sum1_l[1] * 0.19603055651554735) -
                         rtb_gamma_idx_1 * 0.16976744186046511) /
        -0.10949999999999999;
      rtb_gamma_idx_1 -= rtb_gamma_idx_2 * 0.215;
      rtb_gamma_idx_1 /= 0.215;

      /*  Residu_1_4 */
      /* '<S9>:1:14' gamma    = [Residu(1)/u(1) */
      /* '<S9>:1:15'             Residu(2)/u(2) */
      /* '<S9>:1:16'             Residu(3)/u(3)]; */
      rtb_gamma_idx_0 = ((tuning_GS2_DW.Memory_PreviousInput[0] -
                          tuning_GS2_DW.Memory_PreviousInput[3]) - ((rtb_Sum1_l
        [1] - rtb_gamma_idx_2 * 0.18619546181365429) - rtb_gamma_idx_1 * 0.0) /
                         -0.18619546181365429) /
        tuning_GS2_DW.Memory_PreviousInput[0];
      rtb_gamma_idx_1 = ((tuning_GS2_DW.Memory_PreviousInput[1] -
                          tuning_GS2_DW.Memory_PreviousInput[4]) -
                         rtb_gamma_idx_1) / tuning_GS2_DW.Memory_PreviousInput[1];
      rtb_gamma_idx_2 = ((tuning_GS2_DW.Memory_PreviousInput[2] -
                          tuning_GS2_DW.Memory_PreviousInput[5]) -
                         rtb_gamma_idx_2) / tuning_GS2_DW.Memory_PreviousInput[2];

      /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn1' */
      tuning_GS2_B.LOE_FDD[0] = rtb_gamma_idx_0;

      /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn2' */
      tuning_GS2_B.LOE_FDD[3] = 0.0;

      /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn1' */
      tuning_GS2_B.LOE_FDD[1] = rtb_gamma_idx_1;

      /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn2' */
      tuning_GS2_B.LOE_FDD[4] = 0.0;

      /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn1' */
      tuning_GS2_B.LOE_FDD[2] = rtb_gamma_idx_2;

      /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn2' */
      tuning_GS2_B.LOE_FDD[5] = 0.0;
    }

    /* MultiPortSwitch: '<Root>/Multiport Switch' incorporates:
     *  Inport: '<Root>/LOE_cal'
     *  Inport: '<Root>/LOE_mode'
     */
    switch ((int32_T)tuning_GS2_U.LOE_mode) {
     case 1:
      for (i = 0; i < 6; i++) {
        rtb_gamma_m[i] = 0.0;
      }
      break;

     case 2:
      for (i = 0; i < 6; i++) {
        rtb_gamma_m[i] = rtb_LOE_out[i];
      }
      break;

     case 3:
      break;

     case 4:
      for (i = 0; i < 6; i++) {
        rtb_gamma_m[i] = tuning_GS2_U.LOE_cal[i];
      }
      break;

     default:
      for (i = 0; i < 6; i++) {
        rtb_gamma_m[i] = tuning_GS2_B.LOE_FDD[i];
      }
      break;
    }

    /* End of MultiPortSwitch: '<Root>/Multiport Switch' */

    /* Saturate: '<Root>/                        ' */
    for (i = 0; i < 6; i++) {
      rtb_d_z = rtb_gamma_m[i];
      if (rtb_gamma_m[i] > 1.0) {
        rtb_d_z = 1.0;
      } else {
        if (rtb_gamma_m[i] < 0.0) {
          rtb_d_z = 0.0;
        }
      }

      rtb_gamma_m[i] = rtb_d_z;
    }

    /* End of Saturate: '<Root>/                        ' */

    /* Gain: '<S4>/Control Allocation' */
    for (i = 0; i < 4; i++) {
      rtb_ControlAllocation[i] = 0.0;
      for (i_0 = 0; i_0 < 6; i_0++) {
        rtb_ControlAllocation[i] += tuning_GS2_ConstP.ControlAllocation_Gain
          [(i_0 << 2) + i] * rtb_gamma_m[i_0];
      }
    }

    /* End of Gain: '<S4>/Control Allocation' */

    /* MATLAB Function: '<S17>/MATLAB Function' */
    /* MATLAB Function 'GS2_Controller/z_GS2_controller/MATLAB Function': '<S23>:1' */
    /*    GS2_full_OK.m */
    /*  to change 1 */
    /* '<S23>:1:4' gamma_T = (u - 0.3)./0.3; */
    gamma_T = (rtb_ControlAllocation[0] - 0.3) / 0.3;

    /*  normalized LOE */
    /*  to change 2 */
    /*     %% Choice 1: GS2_full_OK */
    /*      Kz  = [16.0821   9.4270] + [1.3595   2.6192].*gamma_T; */
    /*      Kiz = 12.4380 + 0.1906*gamma_T; */
    /*     %% GS2_z => best in z but not in cooperation (x,y)   */
    /*      Kz  = [19.0258   10.6840] + [4.3032    3.8762].*gamma_T; */
    /*      Kiz = 13.9767 + 1.7293*gamma_T; */
    /*     %% Choice 2: GS2_full_OK2 */
    /* '<S23>:1:16' Kz  = [16.5633  9.6788] + [1.8443  2.8710].*gamma_T; */
    rtb_Kz_idx_0 = 1.8443 * gamma_T + 16.5633;
    rtb_Kz_idx_1 = 2.871 * gamma_T + 9.6788;

    /* '<S23>:1:17' Kiz = 12.8742 + 0.6286*gamma_T; */
    gamma_T = 0.6286 * gamma_T + 12.8742;

    /* Sum: '<S6>/Sum5' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/Y0'
     */
    /* '<S23>:1:19' gain = [Kz Kiz]; */
    /*   */
    /*  KX = */
    /*    Columns 1 through 13 */
    /*           0         0   16.0821         0         0    9.4270         0         0         0         0         0         0         0 */
    /*           0   -1.4536         0         0   -0.8915         0    3.0685         0         0    0.5927         0         0         0 */
    /*      2.0048         0         0    1.2289         0         0         0    4.1552         0         0    0.7788         0         0 */
    /*           0         0         0         0         0         0         0         0    0.6048         0         0    0.4733         0 */
    /*   */
    /*    Columns 14 through 26 */
    /*           0    1.3595         0         0    2.6192         0         0         0         0         0         0         0         0 */
    /*           0         0         0         0         0         0         0         0         0         0         0         0   -0.4937 */
    /*           0         0         0         0         0         0         0         0         0         0         0         0         0 */
    /*   */
    /*    Columns 27 through 39 */
    /*           0         0         0         0         0         0         0         0         0         0         0         0         0 */
    /*           0         0   -0.3555         0    1.2959         0         0    0.2680         0         0         0         0         0 */
    /*           0         0         0         0         0         0         0         0         0         0    0.5179         0         0 */
    /*           0         0         0         0         0         0         0         0         0         0         0         0         0 */
    /*   */
    /*    Columns 40 through 52 */
    /*           0         0         0         0         0         0         0         0         0         0         0         0         0 */
    /*      0.2023         0         0         0    0.8640         0         0    0.2009         0         0         0         0         0 */
    /*           0         0         0         0         0         0         0         0         0         0         0         0         0 */
    /*   */
    /*    Columns 53 through 60 */
    /*           0         0         0         0         0         0         0         0 */
    /*           0         0         0         0    0.1068         0         0    0.1603 */
    /*  ----------------------------------- */
    /*  Ki = */
    /*    Columns 1 through 13 */
    /*           0         0   12.4380         0         0         0    0.1906         0         0         0         0         0         0 */
    /*           0   -1.0775         0         0         0         0         0         0         0   -0.3339         0         0         0 */
    /*      1.4511         0         0         0         0         0         0         0         0         0         0         0    0.3746 */
    /*           0         0         0    0.3579         0         0         0         0         0         0         0         0         0 */
    /*   */
    /*    Columns 14 through 20 */
    /*           0         0         0         0         0         0         0 */
    /*           0         0         0         0         0         0    0.0417 */
    /*  ------------------------------ */
    /*  Nominal gain: OK  */
    /*  Kz  = [14.7226 6.8078];  Kiz =  12.2474;   */
    /*  ------------------------------ */
    /*  evalSurf gain: OK                                   */
    /*  u = [0 0 0 0]                   => Kz = [14.7190    6.8078   12.2456]   % GS nominal     */
    /*  u = [0.3 0 0 0]                 => Kz = [16.5633    9.6788   12.8742]   % GS2 with LOE   */
    rtb_d_z = tuning_GS2_U.X[2] - tuning_GS2_U.Y0[2];

    /* MATLAB Function: '<S15>/MATLAB Function' */
    /* MATLAB Function 'GS2_Controller/x_GS2_controller/MATLAB Function': '<S21>:1' */
    /*    GS_x_pitch_OK3.m */
    /*  to change 1 */
    /* '<S21>:1:4' LOE_M = (u - 0.3)/0.3; */
    LOE_M = (rtb_ControlAllocation[2] - 0.3) / 0.3;

    /*  normalized LOE */
    /*  to change 2 */
    /*     %% GS2_full_OK => pire than LQR */
    /*      Kx =  [1.1359    0.6178] +  [0.1084    0.1200]*LOE_M + [0.1183    0.2181]*LOE_M^2; */
    /*      Kix = 0.8943 + 0.0013*LOE_M + 0.0216*LOE_M^2; */
    /*     %% choice 1: GS2_x_pitch_OK => better */
    /*      Kx =  [1.4762    0.9125] +  [0.1416    0.1147]*LOE_M ; */
    /*      Kix = 1.0979  + 0.0054*LOE_M; */
    /*     %% GS2_x_pitch_OK2 => pire than GS2_x_pitch_OK */
    /*      Kx =  [1.4814    0.8619] +  [0.1435    0.1181]*LOE_M ; */
    /*      Kix = 1.1261  + 0.0646*LOE_M; */
    /*     %% Choice 2: GS2_x_pitch_OK3 => best  */
    /* '<S21>:1:20' Kx =  [1.6243    0.9372] +  [0.3078    0.1773]*LOE_M ; */
    /* '<S21>:1:21' Kix = 1.3333  + 0.2307*LOE_M; */
    Kix = 0.2307 * LOE_M + 1.3333;

    /* Sum: '<S6>/Sum1' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/Y0'
     */
    /* '<S21>:1:23' gain = [Kx  Kix]; */
    /*  KX = */
    /*      1.4814    0.8619    3.1595    0.6131    0.1435    0.1181    0.7622    0.1426 */
    /*  ----------------------------------- */
    /*  Ki = */
    /*      1.1261    0.0646 */
    /*  ------------------------------ */
    /*  Nominal gain: OK                      x        xd        theta    theta_d   int   */
    /*                                   K = [1.2426   0.7085]  [2.2946   0.4589]  [0.9913] */
    /*  ------------------------------ */
    /*  evalSurf gain: OK                                   */
    /*  u = [0]                 => K = [1.3165    0.7599]  [2.3834  0.4747]  [1.1026]       % GS nominal !!! */
    /*  u = [0.25]              => K = [1.5730    0.9077]  [3.1547  0.6105]  [1.2948]       % GS2 with LOE   */
    rtb_d_x = tuning_GS2_U.X[0] - tuning_GS2_U.Y0[0];

    /* MATLAB Function: '<S15>/MATLAB Function' */
    rtb_Kx = 0.3078 * LOE_M + 1.6243;

    /* Product: '<S15>/Product1' incorporates:
     *  SignalConversion: '<S15>/TmpSignal ConversionAtProduct1Inport2'
     */
    rtb_ff_idx_0 = rtb_Kx * rtb_d_x;

    /* MATLAB Function: '<S15>/MATLAB Function' */
    rtb_Kx_idx_0 = rtb_Kx;
    rtb_Kx = 0.1773 * LOE_M + 0.9372;

    /* Product: '<S15>/Product1' incorporates:
     *  Inport: '<Root>/X'
     *  SignalConversion: '<S15>/TmpSignal ConversionAtProduct1Inport2'
     */
    rtb_ff_idx_0 += rtb_Kx * tuning_GS2_U.X[3];

    /* Sum: '<S15>/Sum1' incorporates:
     *  Integrator: '<S15>/Integrator1'
     *  MATLAB Function: '<S15>/MATLAB Function'
     *  Product: '<S15>/Product'
     *  Product: '<S15>/Product1'
     */
    tuning_GS2_B.Sum1 = Kix * tuning_GS2_X.Integrator1_CSTATE_e - rtb_ff_idx_0;

    /* MATLAB Function: '<S16>/MATLAB Function' */
    /* MATLAB Function 'GS2_Controller/y_GS2_controller/MATLAB Function': '<S22>:1' */
    /*    GS2_full_OK.m */
    /*  to change 1 */
    /* '<S22>:1:4' LOE_L = (u - 0.3)/0.3; */
    LOE_L = (rtb_ControlAllocation[1] - 0.3) / 0.3;

    /*  normalized LOE */
    /*  to change 2 */
    /* '<S22>:1:7' Ky = [-1.4536   -0.8915] +  [-0.4937   -0.3555]*LOE_L; */
    /* '<S22>:1:8' Kiy = -1.0775 - 0.3339*LOE_L; */
    Kiy = -1.0775 - 0.3339 * LOE_L;

    /* Sum: '<S6>/Sum4' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/Y0'
     */
    /* '<S22>:1:9' gain = [Ky  Kiy]; */
    /*   */
    /*  Ky = */
    /*    Columns 1 through 13 */
    /*           0         0   16.0821         0         0    9.4270         0         0         0         0         0         0         0 */
    /*           0   -1.4536         0         0   -0.8915         0    3.0685         0         0    0.5927         0         0         0 */
    /*      2.0048         0         0    1.2289         0         0         0    4.1552         0         0    0.7788         0         0 */
    /*           0         0         0         0         0         0         0         0    0.6048         0         0    0.4733         0 */
    /*   */
    /*    Columns 14 through 26 */
    /*           0    1.3595         0         0    2.6192         0         0         0         0         0         0         0         0 */
    /*           0         0         0         0         0         0         0         0         0         0         0         0   -0.4937 */
    /*           0         0         0         0         0         0         0         0         0         0         0         0         0 */
    /*   */
    /*    Columns 27 through 39 */
    /*           0         0         0         0         0         0         0         0         0         0         0         0         0 */
    /*           0         0   -0.3555         0    1.2959         0         0    0.2680         0         0         0         0         0 */
    /*           0         0         0         0         0         0         0         0         0         0    0.5179         0         0 */
    /*           0         0         0         0         0         0         0         0         0         0         0         0         0 */
    /*   */
    /*    Columns 40 through 52 */
    /*           0         0         0         0         0         0         0         0         0         0         0         0         0 */
    /*      0.2023         0         0         0    0.8640         0         0    0.2009         0         0         0         0         0 */
    /*           0         0         0         0         0         0         0         0         0         0         0         0         0 */
    /*   */
    /*    Columns 53 through 60 */
    /*           0         0         0         0         0         0         0         0 */
    /*           0         0         0         0    0.1068         0         0    0.1603 */
    /*  ----------------------------------- */
    /*  Ki = */
    /*    Columns 1 through 13 */
    /*           0         0   12.4380         0         0         0    0.1906         0         0         0         0         0         0 */
    /*           0   -1.0775         0         0         0         0         0         0         0   -0.3339         0         0         0 */
    /*      1.4511         0         0         0         0         0         0         0         0         0         0         0    0.3746 */
    /*           0         0         0    0.3579         0         0         0         0         0         0         0         0         0 */
    /*   */
    /*    Columns 14 through 20 */
    /*           0         0         0         0         0         0         0 */
    /*           0         0         0         0         0         0    0.0417 */
    /*  ------------------------------ */
    /*  Nominal gain: OK  */
    /*  K_y_SFint   = [-0.9479 -0.5505];    Ki_y_SFint   = -0.7657;    */
    /*  ------------------------------ */
    /*  evalSurf gain: OK                                   */
    /*  u = [0 0 0 0]                   => Ky = [-0.9599   -0.5360   -0.7436 ]   % GS nominal !!! */
    /*  u = [0 0 0 0.3]                 => Ky = [-1.4536   -0.8915   -1.0775 ]   % GS2 with LOE   */
    rtb_d_y = tuning_GS2_U.X[1] - tuning_GS2_U.Y0[1];

    /* MATLAB Function: '<S16>/MATLAB Function' */
    rtb_Ky = -0.4937 * LOE_L + -1.4536;

    /* Product: '<S16>/Product1' incorporates:
     *  SignalConversion: '<S16>/TmpSignal ConversionAtProduct1Inport2'
     */
    rtb_ff_idx_0 = rtb_Ky * rtb_d_y;

    /* MATLAB Function: '<S16>/MATLAB Function' */
    rtb_Ky_idx_0 = rtb_Ky;
    rtb_Ky = -0.3555 * LOE_L + -0.8915;

    /* Product: '<S16>/Product1' incorporates:
     *  Inport: '<Root>/X'
     *  SignalConversion: '<S16>/TmpSignal ConversionAtProduct1Inport2'
     */
    rtb_ff_idx_0 += rtb_Ky * tuning_GS2_U.X[4];

    /* Sum: '<S16>/Sum1' incorporates:
     *  Integrator: '<S16>/Integrator1'
     *  MATLAB Function: '<S16>/MATLAB Function'
     *  Product: '<S16>/Product'
     *  Product: '<S16>/Product1'
     */
    tuning_GS2_B.Sum1_e = Kiy * tuning_GS2_X.Integrator1_CSTATE_p - rtb_ff_idx_0;

    /* RateTransition: '<S4>/T_outer' incorporates:
     *  Inport: '<Root>/X'
     */
    if ((rtmIsMajorTimeStep((&tuning_GS2_M)) &&
         (&tuning_GS2_M)->Timing.TaskCounters.TID[1] == 0) &&
        (rtmIsMajorTimeStep((&tuning_GS2_M)) &&
         (&tuning_GS2_M)->Timing.TaskCounters.TID[2] == 0)) {
      tuning_GS2_B.T_outer[0] = tuning_GS2_B.Sum1;
      tuning_GS2_B.T_outer[1] = tuning_GS2_B.Sum1_e;
      tuning_GS2_B.T_outer[2] = tuning_GS2_U.X[8];
    }

    /* End of RateTransition: '<S4>/T_outer' */
    if (rtmIsMajorTimeStep((&tuning_GS2_M)) &&
        (&tuning_GS2_M)->Timing.TaskCounters.TID[2] == 0) {
      /* Fcn: '<S4>/Fcn1' */
      tuning_GS2_B.Fcn1 = tuning_GS2_B.T_outer[1] * std::cos
        (tuning_GS2_B.T_outer[2]) + tuning_GS2_B.T_outer[0] * std::sin
        (tuning_GS2_B.T_outer[2]);
    }

    /* MATLAB Function: '<S6>/FFW' incorporates:
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
    if ((tuning_GS2_U.mode == 2.0) && ((rtb_Clock >= 10.0) && (rtb_Clock <= 50.0)))
    {
      /* '<S69>:1:6' if (t >=10) && (t<= 50) */
      /* '<S69>:1:7' axref_N = -cos(t); */
      /* '<S69>:1:8' ayref_N = -sin(t); */
      /* '<S69>:1:10' axref_b = cos(X(8))*cos(X(9))*axref_N + cos(X(8))*sin(X(9))*ayref_N; */
      /* '<S69>:1:11' ayref_b = (sin(X(7))*sin(X(8))*cos(X(9)) - cos(X(7))*sin(X(9)))*axref_N + (sin(X(7))*sin(X(8))*sin(X(9)) + cos(X(7))*cos(X(9)))*ayref_N; */
      /*  azref_b = (cos(X(7))*sin(X(8))*cos(X(9)) + sin(X(7))*sin(X(9)))*axref_N + (cos(X(7))*sin(X(8))*sin(X(9)) - sin(X(7))*cos(X(9)))*ayref_N; */
      /*   */
      /* '<S69>:1:14' ff = [-ayref_b/g; axref_b/g]; */
      rtb_ff_idx_0 = -((std::sin(tuning_GS2_U.X[6]) * std::sin(tuning_GS2_U.X[7])
                        * std::cos(tuning_GS2_U.X[8]) - std::cos(tuning_GS2_U.X
        [6]) * std::sin(tuning_GS2_U.X[8])) * -std::cos(rtb_Clock) + (std::sin
        (tuning_GS2_U.X[6]) * std::sin(tuning_GS2_U.X[7]) * std::sin
        (tuning_GS2_U.X[8]) + std::cos(tuning_GS2_U.X[6]) * std::cos
        (tuning_GS2_U.X[8])) * -std::sin(rtb_Clock)) / 9.81;
      rtb_ff_idx_1 = (std::cos(tuning_GS2_U.X[7]) * std::cos(tuning_GS2_U.X[8]) *
                      -std::cos(rtb_Clock) + std::cos(tuning_GS2_U.X[7]) * std::
                      sin(tuning_GS2_U.X[8]) * -std::sin(rtb_Clock)) / 9.81;
    } else {
      /* '<S69>:1:15' else */
      /* '<S69>:1:16' ff = [0;0]; */
    }

    /* End of MATLAB Function: '<S6>/FFW' */

    /* MATLAB Function: '<S14>/MATLAB Function' */
    /* MATLAB Function 'GS2_Controller/roll_GS2_controller/MATLAB Function': '<S20>:1' */
    /*    GS2_full_OK.m */
    /*  to change 1 */
    /* '<S20>:1:4' LOE_L = (u - 0.3)/0.3; */
    LOE_L = (rtb_ControlAllocation[1] - 0.3) / 0.3;

    /*  normalized LOE */
    /*  to change 2 */
    /* '<S20>:1:7' Kphi = [3.0685   0.5927] +  [1.2959  0.2680]*LOE_L; */
    /*   */
    /*  KX = */
    /*    Columns 1 through 13 */
    /*           0         0   16.0821         0         0    9.4270         0         0         0         0         0         0         0 */
    /*           0   -1.4536         0         0   -0.8915         0    3.0685         0         0    0.5927         0         0         0 */
    /*      2.0048         0         0    1.2289         0         0         0    4.1552         0         0    0.7788         0         0 */
    /*           0         0         0         0         0         0         0         0    0.6048         0         0    0.4733         0 */
    /*   */
    /*    Columns 14 through 26 */
    /*           0    1.3595         0         0    2.6192         0         0         0         0         0         0         0         0 */
    /*           0         0         0         0         0         0         0         0         0         0         0         0   -0.4937 */
    /*           0         0         0         0         0         0         0         0         0         0         0         0         0 */
    /*   */
    /*    Columns 27 through 39 */
    /*           0         0         0         0         0         0         0         0         0         0         0         0         0 */
    /*           0         0   -0.3555         0    1.2959         0         0    0.2680         0         0         0         0         0 */
    /*           0         0         0         0         0         0         0         0         0         0    0.5179         0         0 */
    /*           0         0         0         0         0         0         0         0         0         0         0         0         0 */
    /*   */
    /*    Columns 40 through 52 */
    /*           0         0         0         0         0         0         0         0         0         0         0         0         0 */
    /*      0.2023         0         0         0    0.8640         0         0    0.2009         0         0         0         0         0 */
    /*           0         0         0         0         0         0         0         0         0         0         0         0         0 */
    /*   */
    /*    Columns 53 through 60 */
    /*           0         0         0         0         0         0         0         0 */
    /*           0         0         0         0    0.1068         0         0    0.1603 */
    /*  ----------------------------------- */
    /*  Ki = */
    /*    Columns 1 through 13 */
    /*           0         0   12.4380         0         0         0    0.1906         0         0         0         0         0         0 */
    /*           0   -1.0775         0         0         0         0         0         0         0   -0.3339         0         0         0 */
    /*      1.4511         0         0         0         0         0         0         0         0         0         0         0    0.3746 */
    /*           0         0         0    0.3579         0         0         0         0         0         0         0         0         0 */
    /*   */
    /*    Columns 14 through 20 */
    /*           0         0         0         0         0         0         0 */
    /*           0         0         0         0         0         0    0.0417 */
    /*  ------------------------------ */
    /*  Nominal gain: OK  */
    /*  K_roll_SF   = [1.7378   0.3476];    */
    /*  ------------------------------ */
    /*  evalSurf gain: OK                                   */
    /*  u = [0 0 0 0]                   => Kphi = [1.7726   0.3247]   % GS nominal     */
    /*  u = [0 0 0 0.3]                 => Kphi = [3.0685   0.5927]   % GS2 with LOE   */
    if (rtmIsMajorTimeStep((&tuning_GS2_M)) &&
        (&tuning_GS2_M)->Timing.TaskCounters.TID[2] == 0) {
      /* Fcn: '<S4>/Fcn' */
      tuning_GS2_B.Fcn = -tuning_GS2_B.T_outer[1] * std::sin
        (tuning_GS2_B.T_outer[2]) + tuning_GS2_B.T_outer[0] * std::cos
        (tuning_GS2_B.T_outer[2]);
    }

    /* MATLAB Function: '<S12>/MATLAB Function' */
    /* MATLAB Function 'GS2_Controller/pitch_GS2_controller/MATLAB Function': '<S18>:1' */
    /*    GS2_full_OK.m */
    /*  to change 1 */
    /* '<S18>:1:4' LOE_M = (u - 0.3)/0.3; */
    LOE_M = (rtb_ControlAllocation[2] - 0.3) / 0.3;

    /* MATLAB Function: '<S13>/MATLAB Function' */
    /*  normalized LOE */
    /*  to change 2 */
    /*     %% GS2_full_OK => pire than LQR */
    /*      Ktheta =  [2.2946    0.4589] +  [0.6371    0.1702]*LOE_M + [0.8498    0.2122]*LOE_M^2; */
    /*     %% Choice 1: GS2_x_pitch_OK => better */
    /*      Ktheta =  [3.2979    0.6522 ] +  [ 0.7514    0.2016]*LOE_M; */
    /*     %% GS2_x_pitch_OK2 => pire than GS2_x_pitch_OK */
    /*      Ktheta =  [3.1595    0.6131] +  [0.7622    0.1426]*LOE_M; */
    /*     %% Choice 2: GS2_x_pitch_OK3 => best  */
    /* '<S18>:1:17' Ktheta =  [3.3090    0.6377] +  [0.9256    0.1630]*LOE_M; */
    /*  KX = */
    /*      1.4814    0.8619    3.1595    0.6131    0.1435    0.1181    0.7622    0.1426 */
    /*  ----------------------------------- */
    /*  Ki = */
    /*      1.1261    0.0646 */
    /*  ------------------------------ */
    /*  Nominal gain: OK                      x        xd        theta    theta_d   int   */
    /*                             K = [1.2426   0.7085]  [2.2946   0.4589]  [0.9913] */
    /*  ------------------------------ */
    /*  evalSurf gain: OK                                   */
    /*  u = [0]                 => K = [1.3165    0.7599]  [2.3834  0.4747]  [1.1026]       % GS nominal !!! */
    /*  u = [0.25]              => K = [1.5730    0.9077]  [3.1547  0.6105]  [1.2948]       % GS2 with LOE   */
    /* MATLAB Function 'GS2_Controller/psi_GS2_controller/MATLAB Function': '<S19>:1' */
    /*    GS2_full_OK.m */
    /*  to change 1 */
    /* '<S19>:1:4' LOE_N = (u - 0.3)/0.3; */
    LOE_N = (rtb_ControlAllocation[3] - 0.3) / 0.3;

    /*  normalized LOE */
    /*  to change 2 */
    /* '<S19>:1:7' Kpsi = [0.6048   0.4733] +  [0.1068   0.1603]*LOE_N; */
    rtb_Kpsi_idx_0 = 0.1068 * LOE_N + 0.6048;
    rtb_Kpsi_idx_1 = 0.1603 * LOE_N + 0.4733;

    /* '<S19>:1:8' Kipsi = 0.3579 + 0.0417*LOE_N; */
    LOE_N = 0.0417 * LOE_N + 0.3579;

    /* Sum: '<S6>/Sum6' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/Y0'
     */
    /* '<S19>:1:9' gain = [Kpsi  Kipsi]; */
    /*   */
    /*  KX = */
    /*    Columns 1 through 13 */
    /*           0         0   16.0821         0         0    9.4270         0         0         0         0         0         0         0 */
    /*           0   -1.4536         0         0   -0.8915         0    3.0685         0         0    0.5927         0         0         0 */
    /*      2.0048         0         0    1.2289         0         0         0    4.1552         0         0    0.7788         0         0 */
    /*           0         0         0         0         0         0         0         0    0.6048         0         0    0.4733         0 */
    /*   */
    /*    Columns 14 through 26 */
    /*           0    1.3595         0         0    2.6192         0         0         0         0         0         0         0         0 */
    /*           0         0         0         0         0         0         0         0         0         0         0         0   -0.4937 */
    /*           0         0         0         0         0         0         0         0         0         0         0         0         0 */
    /*   */
    /*    Columns 27 through 39 */
    /*           0         0         0         0         0         0         0         0         0         0         0         0         0 */
    /*           0         0   -0.3555         0    1.2959         0         0    0.2680         0         0         0         0         0 */
    /*           0         0         0         0         0         0         0         0         0         0    0.5179         0         0 */
    /*           0         0         0         0         0         0         0         0         0         0         0         0         0 */
    /*   */
    /*    Columns 40 through 52 */
    /*           0         0         0         0         0         0         0         0         0         0         0         0         0 */
    /*      0.2023         0         0         0    0.8640         0         0    0.2009         0         0         0         0         0 */
    /*           0         0         0         0         0         0         0         0         0         0         0         0         0 */
    /*   */
    /*    Columns 53 through 60 */
    /*           0         0         0         0         0         0         0         0 */
    /*           0         0         0         0    0.1068         0         0    0.1603 */
    /*  ----------------------------------- */
    /*  Ki = */
    /*    Columns 1 through 13 */
    /*           0         0   12.4380         0         0         0    0.1906         0         0         0         0         0         0 */
    /*           0   -1.0775         0         0         0         0         0         0         0   -0.3339         0         0         0 */
    /*      1.4511         0         0         0         0         0         0         0         0         0         0         0    0.3746 */
    /*           0         0         0    0.3579         0         0         0         0         0         0         0         0         0 */
    /*   */
    /*    Columns 14 through 20 */
    /*           0         0         0         0         0         0         0 */
    /*           0         0         0         0         0         0    0.0417 */
    /*  ------------------------------ */
    /*  Nominal gain: OK  */
    /*  K_psi_SFint = [0.4980   0.3130];    Ki_psi_SFint =  0.3162;      */
    /*  ------------------------------ */
    /*  evalSurf gain: OK                                   */
    /*  u = [0 0 0 0]                   => Kpsi = [0.4980  0.3130  0.3162]   % GS nominal     */
    /*  u = [0 0 0 0.3]                 => Kpsi = [0.6048  0.4733  0.3579]   % GS2 with LOE   */
    rtb_d_psi = tuning_GS2_U.X[8] - tuning_GS2_U.Y0[3];

    /* SignalConversion: '<Root>/TmpSignal ConversionAtControl AllocationInport1' incorporates:
     *  Constant: '<S4>/                     '
     *  Inport: '<Root>/X'
     *  Integrator: '<S17>/Integrator1'
     *  MATLAB Function: '<S17>/MATLAB Function'
     *  Product: '<S17>/Product'
     *  Product: '<S17>/Product1'
     *  SignalConversion: '<S17>/TmpSignal ConversionAtProduct1Inport2'
     *  Sum: '<S17>/Sum1'
     *  Sum: '<S4>/Sum1'
     */
    rtb_ControlAllocation[0] = (gamma_T * tuning_GS2_X.Integrator1_CSTATE -
      (rtb_Kz_idx_0 * rtb_d_z + rtb_Kz_idx_1 * tuning_GS2_U.X[5])) +
      15.107400000000002;

    /* Saturate: '<S4>/2Nm ' incorporates:
     *  Inport: '<Root>/X'
     *  MATLAB Function: '<S14>/MATLAB Function'
     *  Product: '<S14>/Product1'
     *  SignalConversion: '<S14>/TmpSignal ConversionAtProduct1Inport2'
     *  Sum: '<S14>/Sum1'
     *  Sum: '<S4>/Sum7'
     */
    LOE_L = (tuning_GS2_B.Fcn1 + rtb_ff_idx_0) - ((1.2959 * LOE_L + 3.0685) *
      tuning_GS2_U.X[6] + (0.268 * LOE_L + 0.5927) * tuning_GS2_U.X[9]);
    if (LOE_L > 2.0) {
      rtb_ref_idx_2 = 2.0;
    } else if (LOE_L < -2.0) {
      rtb_ref_idx_2 = -2.0;
    } else {
      rtb_ref_idx_2 = LOE_L;
    }

    /* Saturate: '<S4>/2Nm' incorporates:
     *  Inport: '<Root>/X'
     *  MATLAB Function: '<S12>/MATLAB Function'
     *  Product: '<S12>/Product1'
     *  SignalConversion: '<S12>/TmpSignal ConversionAtProduct1Inport2'
     *  Sum: '<S12>/Sum1'
     *  Sum: '<S4>/Sum8'
     */
    LOE_M = (tuning_GS2_B.Fcn + rtb_ff_idx_1) - ((0.9256 * LOE_M + 3.309) *
      tuning_GS2_U.X[7] + (0.163 * LOE_M + 0.6377) * tuning_GS2_U.X[10]);
    if (LOE_M > 2.0) {
      rtb_ref_idx_3 = 2.0;
    } else if (LOE_M < -2.0) {
      rtb_ref_idx_3 = -2.0;
    } else {
      rtb_ref_idx_3 = LOE_M;
    }

    /* Saturate: '<S4>/1Nm' incorporates:
     *  Inport: '<Root>/X'
     *  Integrator: '<S13>/Integrator1'
     *  MATLAB Function: '<S13>/MATLAB Function'
     *  Product: '<S13>/Product'
     *  Product: '<S13>/Product1'
     *  SignalConversion: '<S13>/TmpSignal ConversionAtProduct1Inport2'
     *  Sum: '<S13>/Sum1'
     */
    rtb_ff_idx_1 = LOE_N * tuning_GS2_X.Integrator1_CSTATE_j - (rtb_Kpsi_idx_0 *
      rtb_d_psi + rtb_Kpsi_idx_1 * tuning_GS2_U.X[11]);
    if (rtb_ff_idx_1 > 1.0) {
      y = 1.0;
    } else if (rtb_ff_idx_1 < -1.0) {
      y = -1.0;
    } else {
      y = rtb_ff_idx_1;
    }

    for (i = 0; i < 6; i++) {
      /* Gain: '<Root>/Control Allocation' incorporates:
       *  Saturate: '<Root>/                   '
       *  SignalConversion: '<Root>/TmpSignal ConversionAtControl AllocationInport1'
       */
      rtb_ff_idx_0 = tuning_GS2_ConstP.ControlAllocation_Gain_c[i + 18] * y +
        (tuning_GS2_ConstP.ControlAllocation_Gain_c[i + 12] * rtb_ref_idx_3 +
         (tuning_GS2_ConstP.ControlAllocation_Gain_c[i + 6] * rtb_ref_idx_2 +
          tuning_GS2_ConstP.ControlAllocation_Gain_c[i] * rtb_ControlAllocation
          [0]));

      /* Saturate: '<Root>/                   ' incorporates:
       *  Gain: '<Root>/Control Allocation'
       */
      if (rtb_ff_idx_0 > 8.54858) {
        tuning_GS2_B.u[i] = 8.54858;
      } else if (rtb_ff_idx_0 < 0.0) {
        tuning_GS2_B.u[i] = 0.0;
      } else {
        tuning_GS2_B.u[i] = rtb_ff_idx_0;
      }
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
    rtb_gamma_m[0] = (1.0 - rtb_LOE_out[0]) * tuning_GS2_B.u[0];
    rtb_gamma_m[1] = (1.0 - rtb_LOE_out[1]) * tuning_GS2_B.u[1];
    rtb_gamma_m[2] = (1.0 - rtb_LOE_out[2]) * tuning_GS2_B.u[2];
    rtb_gamma_m[3] = (1.0 - rtb_LOE_out[3]) * tuning_GS2_B.u[3];
    rtb_gamma_m[4] = (1.0 - rtb_LOE_out[4]) * tuning_GS2_B.u[4];
    rtb_gamma_m[5] = (1.0 - rtb_LOE_out[5]) * tuning_GS2_B.u[5];

    /* Outport: '<Root>/motor_command' */
    for (i = 0; i < 6; i++) {
      /* Gain: '<S7>/mapping_0_200' incorporates:
       *  Gain: '<S7>/      '
       *  Gain: '<S7>/rads_to_RPM'
       *  Sqrt: '<S7>/Sqrt1'
       *  Sum: '<S7>/Sum3'
       */
      rtb_ff_idx_0 = (std::sqrt(116978.4923343994 * rtb_gamma_m[i]) * 9.5493 -
                      1250.0) * 0.022857142857142857;

      /* Saturate: '<S7>/Saturation' */
      if (rtb_ff_idx_0 > 200.0) {
        tuning_GS2_Y.motor_command[i] = 200.0;
      } else if (rtb_ff_idx_0 < 0.0) {
        tuning_GS2_Y.motor_command[i] = 0.0;
      } else {
        tuning_GS2_Y.motor_command[i] = rtb_ff_idx_0;
      }

      /* End of Saturate: '<S7>/Saturation' */
    }

    /* End of Outport: '<Root>/motor_command' */

    /* MATLAB Function: '<S6>/MATLAB Function' incorporates:
     *  Inport: '<Root>/Y0'
     *  Inport: '<Root>/mode'
     *  Inport: '<Root>/ref'
     */
    /* MATLAB Function 'Test_config_and_data/MATLAB Function': '<S71>:1' */
    /* '<S71>:1:2' ref = Y0; */
    /* '<S71>:1:3' switch test_mode */
    switch ((int32_T)tuning_GS2_U.mode) {
     case 0:
      /* '<S71>:1:4' case 0      % manual test */
      /*  manual test */
      /* '<S71>:1:5' ref = ref_manual; */
      rtb_ff_idx_0 = tuning_GS2_U.ref[0];
      rtb_Clock = tuning_GS2_U.ref[1];
      rtb_ref_idx_2 = tuning_GS2_U.ref[2];
      rtb_ref_idx_3 = tuning_GS2_U.ref[3];
      break;

     case 1:
      /* '<S71>:1:6' case 1      % waypoint */
      /*  waypoint */
      /* '<S71>:1:7' if t<=15 */
      if (rtb_Clock <= 15.0) {
        /* '<S71>:1:8' ref = [Y0(1); Y0(2); 1; Y0(4)]; */
        rtb_ff_idx_0 = tuning_GS2_U.Y0[0];
        rtb_Clock = tuning_GS2_U.Y0[1];
        rtb_ref_idx_2 = 1.0;
        rtb_ref_idx_3 = tuning_GS2_U.Y0[3];
      } else if (rtb_Clock <= 25.0) {
        /* '<S71>:1:9' elseif t <= 25 */
        /* '<S71>:1:10' ref = [Y0(1)+1; Y0(2)-1; 1; Y0(4)]; */
        rtb_ff_idx_0 = tuning_GS2_U.Y0[0] + 1.0;
        rtb_Clock = tuning_GS2_U.Y0[1] - 1.0;
        rtb_ref_idx_2 = 1.0;
        rtb_ref_idx_3 = tuning_GS2_U.Y0[3];
      } else if (rtb_Clock <= 35.0) {
        /* '<S71>:1:11' elseif t <=35 */
        /* '<S71>:1:12' ref = [Y0(1)-1; Y0(2)+1; 1; Y0(4)]; */
        rtb_ff_idx_0 = tuning_GS2_U.Y0[0] - 1.0;
        rtb_Clock = tuning_GS2_U.Y0[1] + 1.0;
        rtb_ref_idx_2 = 1.0;
        rtb_ref_idx_3 = tuning_GS2_U.Y0[3];
      } else if (rtb_Clock <= 45.0) {
        /* '<S71>:1:13' elseif t <=45 */
        /* '<S71>:1:14' ref = [Y0(1)-1; Y0(2)+1; 1; Y0(4)]; */
        rtb_ff_idx_0 = tuning_GS2_U.Y0[0] - 1.0;
        rtb_Clock = tuning_GS2_U.Y0[1] + 1.0;
        rtb_ref_idx_2 = 1.0;
        rtb_ref_idx_3 = tuning_GS2_U.Y0[3];
      } else if (rtb_Clock <= 55.0) {
        /* '<S71>:1:15' elseif t <=55 */
        /* '<S71>:1:16' ref = [Y0(1); Y0(2); 1; Y0(4)]; */
        rtb_ff_idx_0 = tuning_GS2_U.Y0[0];
        rtb_Clock = tuning_GS2_U.Y0[1];
        rtb_ref_idx_2 = 1.0;
        rtb_ref_idx_3 = tuning_GS2_U.Y0[3];
      } else {
        /* '<S71>:1:17' else */
        /* '<S71>:1:18' ref = Y0; */
        rtb_ff_idx_0 = tuning_GS2_U.Y0[0];
        rtb_Clock = tuning_GS2_U.Y0[1];
        rtb_ref_idx_2 = tuning_GS2_U.Y0[2];
        rtb_ref_idx_3 = tuning_GS2_U.Y0[3];
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
      /* '<S71>:1:31' case 2      % circular tracking */
      /*  circular tracking */
      /* '<S71>:1:32' if t<=10 */
      if (rtb_Clock <= 10.0) {
        /* '<S71>:1:33' ref = [Y0(1); Y0(2); 0.75; Y0(4)]; */
        rtb_ff_idx_0 = tuning_GS2_U.Y0[0];
        rtb_Clock = tuning_GS2_U.Y0[1];
        rtb_ref_idx_2 = 0.75;
        rtb_ref_idx_3 = tuning_GS2_U.Y0[3];
      } else if (rtb_Clock <= 50.0) {
        /* '<S71>:1:34' elseif t <= 50 */
        /* '<S71>:1:35' ref = [Y0(1)+cos(t); Y0(2)+sin(t); 0.75; Y0(4)]; */
        rtb_ff_idx_0 = tuning_GS2_U.Y0[0] + std::cos(rtb_Clock);
        rtb_Clock = tuning_GS2_U.Y0[1] + std::sin(rtb_Clock);
        rtb_ref_idx_2 = 0.75;
        rtb_ref_idx_3 = tuning_GS2_U.Y0[3];
      } else if (rtb_Clock <= 60.0) {
        /* '<S71>:1:36' elseif t <= 60 */
        /* '<S71>:1:37' ref = [Y0(1); Y0(2); 0.75; Y0(4)]; */
        rtb_ff_idx_0 = tuning_GS2_U.Y0[0];
        rtb_Clock = tuning_GS2_U.Y0[1];
        rtb_ref_idx_2 = 0.75;
        rtb_ref_idx_3 = tuning_GS2_U.Y0[3];
      } else {
        /* '<S71>:1:38' else */
        /* '<S71>:1:39' ref = Y0; */
        rtb_ff_idx_0 = tuning_GS2_U.Y0[0];
        rtb_Clock = tuning_GS2_U.Y0[1];
        rtb_ref_idx_2 = tuning_GS2_U.Y0[2];
        rtb_ref_idx_3 = tuning_GS2_U.Y0[3];
      }

      /*          ref = [cos(t); sin(t);min(t,15);Y0(4)]; */
      break;

     default:
      /* '<S71>:1:42' otherwise */
      /* '<S71>:1:43' ref = Y0; */
      rtb_ff_idx_0 = tuning_GS2_U.Y0[0];
      rtb_Clock = tuning_GS2_U.Y0[1];
      rtb_ref_idx_2 = tuning_GS2_U.Y0[2];
      rtb_ref_idx_3 = tuning_GS2_U.Y0[3];
      break;
    }

    /* End of MATLAB Function: '<S6>/MATLAB Function' */

    /* Outport: '<Root>/ref_out' */
    tuning_GS2_Y.ref_out[0] = rtb_ff_idx_0;
    tuning_GS2_Y.ref_out[1] = rtb_Clock;
    tuning_GS2_Y.ref_out[2] = rtb_ref_idx_2;
    tuning_GS2_Y.ref_out[3] = rtb_ref_idx_3;

    /* Outport: '<Root>/LOE_true' */
    for (i = 0; i < 6; i++) {
      tuning_GS2_Y.LOE_true[i] = rtb_LOE_out[i];
    }

    /* End of Outport: '<Root>/LOE_true' */
    if (rtmIsMajorTimeStep((&tuning_GS2_M)) &&
        (&tuning_GS2_M)->Timing.TaskCounters.TID[1] == 0) {
      /* Outport: '<Root>/LOE13_estimated' */
      tuning_GS2_Y.LOE13_estimated[0] = rtb_gamma_idx_0;
      tuning_GS2_Y.LOE13_estimated[1] = rtb_gamma_idx_1;
      tuning_GS2_Y.LOE13_estimated[2] = rtb_gamma_idx_2;
    }

    for (i = 0; i < 6; i++) {
      /* Outport: '<Root>/thrust_pre' */
      tuning_GS2_Y.thrust_pre[i] = tuning_GS2_B.u[i];

      /* Outport: '<Root>/thrust_after' */
      tuning_GS2_Y.thrust_after[i] = rtb_gamma_m[i];
    }

    if (rtmIsMajorTimeStep((&tuning_GS2_M)) &&
        (&tuning_GS2_M)->Timing.TaskCounters.TID[1] == 0) {
      /* Outport: '<Root>/acc_Kalman' */
      tuning_GS2_Y.acc_Kalman[0] = rtb_Add_a[3];

      /* Outport: '<Root>/M_Kalman' */
      tuning_GS2_Y.M_Kalman[0] = rtb_Sum1_l[0];

      /* Outport: '<Root>/vel_Kalman' */
      tuning_GS2_Y.vel_Kalman[0] = rtb_Add_a[0];

      /* Outport: '<Root>/acc_Kalman' */
      tuning_GS2_Y.acc_Kalman[1] = rtb_Add_a[4];

      /* Outport: '<Root>/M_Kalman' */
      tuning_GS2_Y.M_Kalman[1] = rtb_Sum1_l[1];

      /* Outport: '<Root>/vel_Kalman' */
      tuning_GS2_Y.vel_Kalman[1] = rtb_Add_a[1];

      /* Outport: '<Root>/acc_Kalman' */
      tuning_GS2_Y.acc_Kalman[2] = rtb_Add_a[5];

      /* Outport: '<Root>/M_Kalman' */
      tuning_GS2_Y.M_Kalman[2] = rtb_Sum1_l[2];

      /* Outport: '<Root>/vel_Kalman' */
      tuning_GS2_Y.vel_Kalman[2] = rtb_Add_a[2];
    }

    /* Outport: '<Root>/gain_GS' incorporates:
     *  MATLAB Function: '<S13>/MATLAB Function'
     *  MATLAB Function: '<S15>/MATLAB Function'
     *  MATLAB Function: '<S16>/MATLAB Function'
     *  MATLAB Function: '<S17>/MATLAB Function'
     */
    tuning_GS2_Y.gain_GS[2] = gamma_T;
    tuning_GS2_Y.gain_GS[5] = LOE_N;
    tuning_GS2_Y.gain_GS[8] = Kix;
    tuning_GS2_Y.gain_GS[0] = rtb_Kz_idx_0;
    tuning_GS2_Y.gain_GS[3] = rtb_Kpsi_idx_0;
    tuning_GS2_Y.gain_GS[6] = rtb_Kx_idx_0;
    tuning_GS2_Y.gain_GS[9] = rtb_Ky_idx_0;
    tuning_GS2_Y.gain_GS[1] = rtb_Kz_idx_1;
    tuning_GS2_Y.gain_GS[4] = rtb_Kpsi_idx_1;
    tuning_GS2_Y.gain_GS[7] = rtb_Kx;
    tuning_GS2_Y.gain_GS[10] = rtb_Ky;
    tuning_GS2_Y.gain_GS[11] = Kiy;

    /* Outport: '<Root>/virtual_control' */
    tuning_GS2_Y.virtual_control[0] = rtb_ControlAllocation[0];

    /* Sum: '<S6>/Sum' incorporates:
     *  Inport: '<Root>/Y0'
     */
    rtb_ControlAllocation[0] = rtb_ff_idx_0 - tuning_GS2_U.Y0[0];

    /* Saturate: '<S4>/2Nm ' */
    if (LOE_L > 2.0) {
      /* Outport: '<Root>/virtual_control' */
      tuning_GS2_Y.virtual_control[1] = 2.0;
    } else if (LOE_L < -2.0) {
      /* Outport: '<Root>/virtual_control' */
      tuning_GS2_Y.virtual_control[1] = -2.0;
    } else {
      /* Outport: '<Root>/virtual_control' */
      tuning_GS2_Y.virtual_control[1] = LOE_L;
    }

    /* Sum: '<S6>/Sum' incorporates:
     *  Inport: '<Root>/Y0'
     */
    rtb_ControlAllocation[1] = rtb_Clock - tuning_GS2_U.Y0[1];

    /* Saturate: '<S4>/2Nm' */
    if (LOE_M > 2.0) {
      /* Outport: '<Root>/virtual_control' */
      tuning_GS2_Y.virtual_control[2] = 2.0;
    } else if (LOE_M < -2.0) {
      /* Outport: '<Root>/virtual_control' */
      tuning_GS2_Y.virtual_control[2] = -2.0;
    } else {
      /* Outport: '<Root>/virtual_control' */
      tuning_GS2_Y.virtual_control[2] = LOE_M;
    }

    /* Sum: '<S6>/Sum' incorporates:
     *  Inport: '<Root>/Y0'
     */
    rtb_ControlAllocation[2] = rtb_ref_idx_2 - tuning_GS2_U.Y0[2];

    /* Saturate: '<S4>/1Nm' */
    if (rtb_ff_idx_1 > 1.0) {
      /* Outport: '<Root>/virtual_control' */
      tuning_GS2_Y.virtual_control[3] = 1.0;
    } else if (rtb_ff_idx_1 < -1.0) {
      /* Outport: '<Root>/virtual_control' */
      tuning_GS2_Y.virtual_control[3] = -1.0;
    } else {
      /* Outport: '<Root>/virtual_control' */
      tuning_GS2_Y.virtual_control[3] = rtb_ff_idx_1;
    }

    /* Sum: '<S6>/Sum' incorporates:
     *  Inport: '<Root>/Y0'
     */
    rtb_gamma_idx_1 = rtb_ref_idx_3 - tuning_GS2_U.Y0[3];

    /* Saturate: '<S13>/yaw' */
    if (rtb_gamma_idx_1 > 3.1415926535897931) {
      rtb_gamma_idx_1 = 3.1415926535897931;
    } else {
      if (rtb_gamma_idx_1 < -3.1415926535897931) {
        rtb_gamma_idx_1 = -3.1415926535897931;
      }
    }

    /* End of Saturate: '<S13>/yaw' */

    /* Sum: '<S13>/Sum3' */
    tuning_GS2_B.Sum3 = rtb_gamma_idx_1 - rtb_d_psi;

    /* Saturate: '<S15>/x' */
    if (rtb_ControlAllocation[0] > 2.0) {
      rtb_gamma_idx_1 = 2.0;
    } else if (rtb_ControlAllocation[0] < -2.0) {
      rtb_gamma_idx_1 = -2.0;
    } else {
      rtb_gamma_idx_1 = rtb_ControlAllocation[0];
    }

    /* End of Saturate: '<S15>/x' */

    /* Sum: '<S15>/Sum3' */
    tuning_GS2_B.Sum3_f = rtb_gamma_idx_1 - rtb_d_x;

    /* Saturate: '<S16>/y' */
    if (rtb_ControlAllocation[1] > 2.0) {
      rtb_gamma_idx_1 = 2.0;
    } else if (rtb_ControlAllocation[1] < -2.0) {
      rtb_gamma_idx_1 = -2.0;
    } else {
      rtb_gamma_idx_1 = rtb_ControlAllocation[1];
    }

    /* End of Saturate: '<S16>/y' */

    /* Sum: '<S16>/Sum3' */
    tuning_GS2_B.Sum3_f3 = rtb_gamma_idx_1 - rtb_d_y;

    /* Saturate: '<S17>/z' */
    if (rtb_ControlAllocation[2] > 1.75) {
      rtb_gamma_idx_1 = 1.75;
    } else if (rtb_ControlAllocation[2] < 0.0) {
      rtb_gamma_idx_1 = 0.0;
    } else {
      rtb_gamma_idx_1 = rtb_ControlAllocation[2];
    }

    /* End of Saturate: '<S17>/z' */

    /* Sum: '<S17>/Sum3' */
    tuning_GS2_B.Sum3_j = rtb_gamma_idx_1 - rtb_d_z;
    if (rtmIsMajorTimeStep((&tuning_GS2_M)) &&
        (&tuning_GS2_M)->Timing.TaskCounters.TID[1] == 0) {
      /* Outputs for Enabled SubSystem: '<S42>/MeasurementUpdate' incorporates:
       *  EnablePort: '<S67>/Enable'
       */
      if (rtmIsMajorTimeStep((&tuning_GS2_M)) &&
          (!tuning_GS2_DW.MeasurementUpdate_MODE)) {
        tuning_GS2_DW.MeasurementUpdate_MODE = true;
      }

      if (tuning_GS2_DW.MeasurementUpdate_MODE) {
        for (i = 0; i < 3; i++) {
          /* Product: '<S67>/C[k]*xhat[k|k-1]' incorporates:
           *  Constant: '<S5>/C'
           *  Sum: '<S67>/Add1'
           */
          rtb_Add_f[i] = 0.0;
          for (i_0 = 0; i_0 < 6; i_0++) {
            rtb_Add_f[i] += tuning_GS2_ConstP.C_Value[3 * i_0 + i] *
              rtb_MemoryX[i_0];
          }

          /* End of Product: '<S67>/C[k]*xhat[k|k-1]' */

          /* Sum: '<S67>/Sum' incorporates:
           *  Inport: '<Root>/X'
           *  Product: '<S67>/Product3'
           *  Sum: '<S67>/Add1'
           */
          rtb_Add_f_0[i] = tuning_GS2_U.X[9 + i] - rtb_Add_f[i];
        }

        /* Product: '<S67>/Product3' incorporates:
         *  Constant: '<S24>/KalmanGainL'
         */
        for (i = 0; i < 6; i++) {
          tuning_GS2_B.Product3[i] = 0.0;
          tuning_GS2_B.Product3[i] += tuning_GS2_ConstP.KalmanGainL_Value[i] *
            rtb_Add_f_0[0];
          tuning_GS2_B.Product3[i] += tuning_GS2_ConstP.KalmanGainL_Value[i + 6]
            * rtb_Add_f_0[1];
          tuning_GS2_B.Product3[i] += tuning_GS2_ConstP.KalmanGainL_Value[i + 12]
            * rtb_Add_f_0[2];
        }
      }

      /* End of Outputs for SubSystem: '<S42>/MeasurementUpdate' */
      for (i = 0; i < 6; i++) {
        /* Product: '<S42>/A[k]*xhat[k|k-1]' incorporates:
         *  Constant: '<S5>/A'
         *  Sum: '<S42>/Add'
         */
        rtb_gamma_m[i] = 0.0;
        for (i_0 = 0; i_0 < 6; i_0++) {
          rtb_gamma_m[i] += tuning_GS2_ConstP.A_Value[6 * i_0 + i] *
            rtb_MemoryX[i_0];
        }

        /* End of Product: '<S42>/A[k]*xhat[k|k-1]' */

        /* Sum: '<S42>/Add' */
        rtb_Add[i] = rtb_gamma_m[i] + tuning_GS2_B.Product3[i];
      }
    }
  }

  if (rtmIsMajorTimeStep((&tuning_GS2_M))) {
    int32_T i;
    if (rtmIsMajorTimeStep((&tuning_GS2_M)) &&
        (&tuning_GS2_M)->Timing.TaskCounters.TID[1] == 0) {
      /* Update for Delay: '<S5>/MemoryX' */
      tuning_GS2_DW.icLoad = 0U;
      for (i = 0; i < 6; i++) {
        /* Update for Memory: '<S3>/Memory' */
        tuning_GS2_DW.Memory_PreviousInput[i] = tuning_GS2_B.u[i];

        /* Update for Delay: '<S5>/MemoryX' */
        tuning_GS2_DW.MemoryX_DSTATE[i] = rtb_Add[i];
      }
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep((&tuning_GS2_M))) {
    rt_ertODEUpdateContinuousStates(&(&tuning_GS2_M)->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++(&tuning_GS2_M)->Timing.clockTick0)) {
      ++(&tuning_GS2_M)->Timing.clockTickH0;
    }

    (&tuning_GS2_M)->Timing.t[0] = rtsiGetSolverStopTime(&(&tuning_GS2_M)
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
      (&tuning_GS2_M)->Timing.clockTick1++;
      if (!(&tuning_GS2_M)->Timing.clockTick1) {
        (&tuning_GS2_M)->Timing.clockTickH1++;
      }
    }

    rate_scheduler((&tuning_GS2_M));
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void tuning_GS2ModelClass::tuning_GS2_derivatives()
{
  XDot_tuning_GS2_T *_rtXdot;
  _rtXdot = ((XDot_tuning_GS2_T *) (&tuning_GS2_M)->derivs);

  /* Derivatives for Integrator: '<S17>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = tuning_GS2_B.Sum3_j;

  /* Derivatives for Integrator: '<S15>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_e = tuning_GS2_B.Sum3_f;

  /* Derivatives for Integrator: '<S16>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_p = tuning_GS2_B.Sum3_f3;

  /* Derivatives for Integrator: '<S13>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_j = tuning_GS2_B.Sum3;
}

/* Model initialize function */
void tuning_GS2ModelClass::initialize()
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)(&tuning_GS2_M), 0,
                sizeof(RT_MODEL_tuning_GS2_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&(&tuning_GS2_M)->solverInfo, &(&tuning_GS2_M)
                          ->Timing.simTimeStep);
    rtsiSetTPtr(&(&tuning_GS2_M)->solverInfo, &rtmGetTPtr((&tuning_GS2_M)));
    rtsiSetStepSizePtr(&(&tuning_GS2_M)->solverInfo, &(&tuning_GS2_M)
                       ->Timing.stepSize0);
    rtsiSetdXPtr(&(&tuning_GS2_M)->solverInfo, &(&tuning_GS2_M)->derivs);
    rtsiSetContStatesPtr(&(&tuning_GS2_M)->solverInfo, (real_T **)
                         &(&tuning_GS2_M)->contStates);
    rtsiSetNumContStatesPtr(&(&tuning_GS2_M)->solverInfo, &(&tuning_GS2_M)
      ->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&tuning_GS2_M)->solverInfo,
      &(&tuning_GS2_M)->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&tuning_GS2_M)->solverInfo,
      &(&tuning_GS2_M)->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&tuning_GS2_M)->solverInfo,
      &(&tuning_GS2_M)->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&(&tuning_GS2_M)->solverInfo, (&rtmGetErrorStatus
      ((&tuning_GS2_M))));
    rtsiSetRTModelPtr(&(&tuning_GS2_M)->solverInfo, (&tuning_GS2_M));
  }

  rtsiSetSimTimeStep(&(&tuning_GS2_M)->solverInfo, MAJOR_TIME_STEP);
  (&tuning_GS2_M)->intgData.y = (&tuning_GS2_M)->odeY;
  (&tuning_GS2_M)->intgData.f[0] = (&tuning_GS2_M)->odeF[0];
  (&tuning_GS2_M)->intgData.f[1] = (&tuning_GS2_M)->odeF[1];
  (&tuning_GS2_M)->intgData.f[2] = (&tuning_GS2_M)->odeF[2];
  (&tuning_GS2_M)->intgData.f[3] = (&tuning_GS2_M)->odeF[3];
  getRTM()->contStates = ((X_tuning_GS2_T *) &tuning_GS2_X);
  rtsiSetSolverData(&(&tuning_GS2_M)->solverInfo, (void *)&(&tuning_GS2_M)
                    ->intgData);
  rtsiSetSolverName(&(&tuning_GS2_M)->solverInfo,"ode4");
  rtmSetTPtr(getRTM(), &(&tuning_GS2_M)->Timing.tArray[0]);
  (&tuning_GS2_M)->Timing.stepSize0 = 0.001;

  /* block I/O */
  (void) memset(((void *) &tuning_GS2_B), 0,
                sizeof(B_tuning_GS2_T));

  /* states (continuous) */
  {
    (void) memset((void *)&tuning_GS2_X, 0,
                  sizeof(X_tuning_GS2_T));
  }

  /* states (dwork) */
  (void) memset((void *)&tuning_GS2_DW, 0,
                sizeof(DW_tuning_GS2_T));

  /* external inputs */
  (void)memset((void *)&tuning_GS2_U, 0, sizeof(ExtU_tuning_GS2_T));

  /* external outputs */
  (void) memset((void *)&tuning_GS2_Y, 0,
                sizeof(ExtY_tuning_GS2_T));

  {
    int32_T i;

    /* InitializeConditions for Delay: '<S5>/MemoryX' */
    tuning_GS2_DW.icLoad = 1U;

    /* InitializeConditions for Integrator: '<S17>/Integrator1' */
    tuning_GS2_X.Integrator1_CSTATE = 0.0;

    /* InitializeConditions for Integrator: '<S15>/Integrator1' */
    tuning_GS2_X.Integrator1_CSTATE_e = 0.0;

    /* InitializeConditions for Integrator: '<S16>/Integrator1' */
    tuning_GS2_X.Integrator1_CSTATE_p = 0.0;

    /* InitializeConditions for Integrator: '<S13>/Integrator1' */
    tuning_GS2_X.Integrator1_CSTATE_j = 0.0;

    /* SystemInitialize for Enabled SubSystem: '<S42>/MeasurementUpdate' */
    /* SystemInitialize for Atomic SubSystem: '<S5>/UseCurrentEstimator' */
    /* SystemInitialize for Enabled SubSystem: '<S47>/Enabled Subsystem' */
    for (i = 0; i < 6; i++) {
      /* InitializeConditions for Memory: '<S3>/Memory' */
      tuning_GS2_DW.Memory_PreviousInput[i] = 2.5179000000000005;

      /* SystemInitialize for Outport: '<S68>/deltax' */
      tuning_GS2_B.Product2[i] = 0.0;

      /* SystemInitialize for Outport: '<S67>/L*(y[k]-yhat[k|k-1])' */
      tuning_GS2_B.Product3[i] = 0.0;
    }

    /* End of SystemInitialize for SubSystem: '<S47>/Enabled Subsystem' */
    /* End of SystemInitialize for SubSystem: '<S5>/UseCurrentEstimator' */
    /* End of SystemInitialize for SubSystem: '<S42>/MeasurementUpdate' */
  }
}

/* Model terminate function */
void tuning_GS2ModelClass::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
tuning_GS2ModelClass::tuning_GS2ModelClass()
{
}

/* Destructor */
tuning_GS2ModelClass::~tuning_GS2ModelClass()
{
  /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_tuning_GS2_T * tuning_GS2ModelClass::getRTM()
{
  return (&tuning_GS2_M);
}
