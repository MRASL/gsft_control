/*
 * tuning_GS2.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "tuning_GS2".
 *
 * Model version              : 1.2797
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Wed May 15 14:50:44 2019
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
    real_T Kiz;
    real_T Kix;
    real_T Kiy;
    real_T Kipsi;
    real_T rtb_Sum1_l[3];
    real_T rtb_Add_a[6];
    real_T rtb_LOE_out[6];
    real_T rtb_gamma_l[6];
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
    real_T rtb_Kpsi;
    real_T rtb_Sum_idx_0;
    real_T rtb_Sum_idx_3;
    real_T rtb_ff_idx_1;
    real_T rtb_ff_idx_0;
    real_T rtb_gamma_idx_2;
    real_T rtb_gamma_idx_1;
    real_T rtb_gamma_idx_0;
    real_T rtb_Kz_idx_0;
    real_T rtb_Kx_idx_0;
    real_T rtb_Kz_idx_1;
    real_T rtb_Ky_idx_0;
    real_T rtb_Kpsi_idx_0;
    real_T u0;

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
        rtb_gamma_l[i] = 0.0;
      } else if (rtb_Clock <= tuning_GS2_U.LOE_t[i] + 1.5) {
        /* '<S2>:1:6' elseif time <= LOE_moment(i)+1.5 */
        /* '<S2>:1:7' gamma(i) = LOE_amplitude(i)*(time - LOE_moment(i))/1.5; */
        rtb_gamma_l[i] = (rtb_Clock - tuning_GS2_U.LOE_t[i]) *
          tuning_GS2_U.LOE_a[i] / 1.5;
      } else {
        /* '<S2>:1:8' else */
        /* '<S2>:1:9' gamma(i) = LOE_amplitude(i); */
        rtb_gamma_l[i] = tuning_GS2_U.LOE_a[i];
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
        u0 = 0.0;
        for (i_0 = 0; i_0 < 6; i_0++) {
          u0 += tuning_GS2_ConstP.C_Value[3 * i_0 + i] *
            tuning_GS2_DW.MemoryX_DSTATE[i_0];
        }

        rtb_Add_f[i] = tuning_GS2_U.X[9 + i] - u0;
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
    switch (tuning_GS2_U.LOE_mode) {
     case 0:
      for (i = 0; i < 6; i++) {
        rtb_gamma_l[i] = 0.0;
      }
      break;

     case 1:
      for (i = 0; i < 6; i++) {
        rtb_gamma_l[i] = rtb_LOE_out[i];
      }
      break;

     case 2:
      break;

     case 3:
      for (i = 0; i < 6; i++) {
        rtb_gamma_l[i] = tuning_GS2_U.LOE_cal[i];
      }
      break;

     default:
      for (i = 0; i < 6; i++) {
        rtb_gamma_l[i] = tuning_GS2_B.LOE_FDD[i];
      }
      break;
    }

    /* End of MultiPortSwitch: '<Root>/Multiport Switch' */

    /* Saturate: '<Root>/                        ' */
    for (i = 0; i < 6; i++) {
      rtb_d_z = rtb_gamma_l[i];
      if (rtb_gamma_l[i] > 1.0) {
        rtb_d_z = 1.0;
      } else {
        if (rtb_gamma_l[i] < 0.0) {
          rtb_d_z = 0.0;
        }
      }

      rtb_gamma_l[i] = rtb_d_z;
    }

    /* End of Saturate: '<Root>/                        ' */

    /* Gain: '<S4>/Control Allocation' */
    for (i = 0; i < 4; i++) {
      rtb_ControlAllocation[i] = 0.0;
      for (i_0 = 0; i_0 < 6; i_0++) {
        rtb_ControlAllocation[i] += tuning_GS2_ConstP.ControlAllocation_Gain
          [(i_0 << 2) + i] * rtb_gamma_l[i_0];
      }
    }

    /* End of Gain: '<S4>/Control Allocation' */

    /* MATLAB Function: '<S17>/MATLAB Function' */
    /* MATLAB Function 'GS2_Controller/z_GS2_controller/MATLAB Function': '<S23>:1' */
    /*  LQR gain: K = [14.7226  6.8078  12.2474] */
    /*     %% GS2_full_OK - config 1 */
    /*      gamma_T = (u - 0.3)./0.3;                                   % normalized LOE */
    /*      Kz  = [16.0821   9.4270] + [1.3595   2.6192].*gamma_T; */
    /*      Kiz = 12.4380 + 0.1906*gamma_T;                                   */
    /*  u = 0         => K = [14.7226    6.8078   12.2474]     = LQR !!! */
    /*  u = 0.125     => K = [15.2891    7.8991   12.3268]        */
    /*  u = 0.2       => K = [15.6289    8.5539   12.3745]      */
    /*  recheck by evalSurf: Ok */
    /*     %% GS2_z_without_normalization_ML17b - config 1 (integral gain increases) */
    /* '<S23>:1:14' Kz  = [14.7226    6.8078] + [12.0004  12.5729].*u; */
    /* '<S23>:1:15' Kiz = 12.2474 + 4.2580*u; */
    Kiz = 4.258 * rtb_ControlAllocation[0] + 12.2474;

    /* Sum: '<S6>/Sum5' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/Y0'
     */
    /*  u = 0         => K = [14.7226    6.8078   12.2474]     = LQR !!! */
    /*  u = 0.125     => K = [16.2227    8.3794   12.7797]        */
    /*  u = 0.2       => K = [17.1227    9.3224   13.0990]    */
    /* '<S23>:1:20' gain = [Kz Kiz]; */
    /*  Choice 1: GS2_full_OK - config 1 */
    /*      gamma_T = (u - 0.3)./0.3;                                   % normalized LOE */
    /*      Kz  = [16.0821   9.4270] + [1.3595   2.6192].*gamma_T; */
    /*      Kiz = 12.4380 + 0.1906*gamma_T;                                   */
    /*  u = 0         => K = [14.7226    6.8078   12.2474]     = LQR !!! */
    /*  u = 0.125     => K = [15.2891    7.8991   12.3268]        */
    /*  u = 0.2       => K = [15.6289    8.5539   12.3745]      */
    /*  recheck by evalSurf: Ok */
    /*  Choice 2: GS2_z_OK - config 1 (integral gain increases) */
    /*      gamma_T = (u - 0.3)./0.3;                                   %normalized LOE */
    /*      Kz  = [18.2893 10.1732] + [3.5667   3.3654].*gamma_T; */
    /*      Kiz = 13.5460 + 1.2986*gamma_T;        */
    /*  u = 0         => K = [14.7226    6.8078   12.2474]     = LQR !!! */
    /*  u = 0.125     => K = [16.2087    8.2100   12.7885]        */
    /*  u = 0.2       => K = [17.1004    9.0514   13.1131]      */
    /*  recheck by evalSurf: Ok */
    /*  Choice 3: GS2_z_OK - config 2 (integral gain decreases)      */
    /*      gamma_T = (u - 0.3)./0.3;                                   % normalized LOE */
    /*      Kz  = [17.0549  9.6598] + [2.3323   2.8520].*gamma_T; */
    /*      Kiz = 12.1611 - 0.0863*gamma_T;        */
    /*  u = 0         => K = [14.7226    6.8078   12.2474]     = LQR !!! */
    /*  u = 0.125     => K = [15.6944    7.9961   12.2114]        */
    /*  u = 0.2       => K = [16.2775    8.7091   12.1899]      */
    /*  recheck by evalSurf: Ok */
    /*  Choice 4: GS2_z_without_normalization_ML17b - config 1 (integral gain increases) */
    /*      Kz  = [14.7226    6.8078] + [12.0004  12.5729].*u; */
    /*      Kiz = 12.2474 + 4.2580*u;        */
    /*  u = 0         => K = [14.7226    6.8078   12.2474]     = LQR !!! */
    /*  u = 0.125     => K = [16.2227    8.3794   12.7797]        */
    /*  u = 0.2       => K = [17.1227    9.3224   13.0990]      */
    /*  recheck by evalSurf: Ok */
    /*  Choice 5: GS2_z_without_normalization_ML17b - config 2 (integral gain decreases) */
    /*      Kz  = [14.7226    6.8078] + [7.4659  9.7024].*u; */
    /*      Kiz = 12.2474  -  0.5005*u;        */
    /*  u = 0         => Kz = [14.7226    6.8078   12.2474]     = LQR !!! */
    /*  u = 0.125     => Kz = [15.6558    8.0206   12.1848]        */
    /*  u = 0.2       => Kz = [16.2158    8.7483   12.1473]      */
    /*  recheck by evalSurf: Ok */
    /*  ------------------------------------------------------------------------  */
    /*   */
    /*  GS2_full_OK */
    /*  */
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
    rtb_d_z = tuning_GS2_U.X[2] - tuning_GS2_U.Y0[2];

    /* MATLAB Function: '<S15>/MATLAB Function' */
    /* MATLAB Function 'GS2_Controller/x_GS2_controller/MATLAB Function': '<S21>:1' */
    /*  LQR gain1:         x        xd     theta     theta_d     int   */
    /*             K = [1.2426   0.7085    2.2946    0.4589    0.9913] */
    /*  GS2_x_pitch_OK  */
    /*      LOE_M = (u - 0.3)/0.3;                                                 % normalized LOE */
    /*      Kx =  [1.4762    0.9125] +  [0.1416    0.1147]*LOE_M ; */
    /*      Kix = 1.0979  + 0.0054*LOE_M;     */
    /*  u = 0         => K = [1.3346    0.7978    2.5465    0.4506   1.0925]     = LQR gain2 !!! */
    /*  u = 0.125     => K = [1.3936    0.8456    2.8596    0.5346   1.0948]        */
    /*  u = 0.175     => K = [1.4172    0.8647    2.9848    0.5682   1.0957]      */
    /*  recheck by evalSurf: Ok    */
    /*  GS2_x_pitch_without_normalization_ML17b - Config 4 (all increase), biggest gain        */
    /* '<S21>:1:15' Kx =  [1.3446    0.7978] +  [0.5145  0.5524]*u ; */
    /* '<S21>:1:16' Kix = 1.0925  + 0.2053*u; */
    Kix = 0.2053 * rtb_ControlAllocation[2] + 1.0925;

    /* Sum: '<S6>/Sum1' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/Y0'
     */
    /*  u = 0         => K = [1.3346    0.7978    2.5465    0.4506   1.0925]     = LQR gain2 !!! */
    /*  u = 0.125     => K = [1.4089    0.8668    2.9154    0.5598   1.1182]        */
    /*  u = 0.175     => K = [1.4346    0.8945    3.0629    0.6035   1.1284]    */
    /*      */
    /* '<S21>:1:22' gain = [Kx  Kix]; */
    /*  Note1: GS2_full_OK.m => TOO BIG x gains */
    /*  Note 2 */
    /*  LQR gain2:         x        xd      theta    theta_d     int   */
    /*             K = [1.3346   0.7978     2.5465    0.4506   1.0925] */
    /*  compare: test3_lqr1 vs test3_lqr2 => same result */
    /*  Choice 1: GS2_x_pitch_OK  */
    /*      LOE_M = (u - 0.3)/0.3;                                                 % normalized LOE */
    /*      Kx =  [1.4762    0.9125] +  [0.1416    0.1147]*LOE_M ; */
    /*      Kix = 1.0979  + 0.0054*LOE_M;     */
    /*  u = 0         => K = [1.3346    0.7978    2.5465    0.4506   1.0925]     = LQR gain2 !!! */
    /*  u = 0.125     => K = [1.3936    0.8456    2.8596    0.5346   1.0948]        */
    /*  u = 0.175     => K = [1.4172    0.8647    2.9848    0.5682   1.0957]      */
    /*  recheck by evalSurf: Ok     */
    /*  Choice 2: GS2_x_pitch_without_normalization_ML17b - Config 1 (only integral gain decreases)        */
    /*      Kx =  [1.3446    0.7978] +  [0.1223  0.3041]*u ; */
    /*      Kix = 1.0925  - 0.2242*u; */
    /*  u = 0         => K = [1.3346    0.7978    2.5465    0.4506   1.0925]     = LQR gain2 !!! */
    /*  u = 0.125     => K = [1.3599    0.8358    2.8214    0.5413   1.0645]        */
    /*  u = 0.175     => K = [1.3660    0.8510    2.9314    0.5776   1.0533]      */
    /*  recheck by evalSurf: Ok      */
    /*  Choice 3: GS2_x_pitch_without_normalization_ML17b - Config 2 (only integral gain decreases), bigger gain        */
    /*      Kx =  [1.3446    0.7978] +  [0.2956  0.4896]*u ; */
    /*      Kix = 1.0925  - 0.0652*u; */
    /*  u = 0         => K = [1.3346    0.7978    2.5465    0.4506   1.0925]     = LQR gain2 !!! */
    /*  u = 0.125     => K = [1.3816    0.8590    2.9047    0.5649   1.0843]        */
    /*  u = 0.175     => K = [1.3963    0.8835    3.0480    0.6106   1.0811]      */
    /*  recheck by evalSurf: Ok   */
    /*  Choice 4: GS2_x_pitch_without_normalization_ML17b - Config 3 (inner loop increases, outer loop decreases)        */
    /*      Kx =  [1.3446    0.7978] -  [0.4711  0.0266]*u ; */
    /*      Kix =  1.0925  - 0.6992*u; */
    /*  u = 0         => K = [1.3346    0.7978    2.5465    0.4506   1.0925]     = LQR gain2 !!! */
    /*  u = 0.125     => K = [1.2857    0.7945    2.7136    0.5256   1.0051]        */
    /*  u = 0.175     => K = [1.2622    0.7931    2.7804    0.5556   0.9701]      */
    /*  recheck by evalSurf: Ok  */
    /*  Choice 5: GS2_x_pitch_without_normalization_ML17b - Config 4 (all increase), biggest gain        */
    /*      Kx =  [1.3446    0.7978] +  [0.5145  0.5524]*u ; */
    /*      Kix = 1.0925  + 0.2053*u; */
    /*  u = 0         => K = [1.3346    0.7978    2.5465    0.4506   1.0925]     = LQR gain2 !!! */
    /*  u = 0.125     => K = [1.4089    0.8668    2.9154    0.5598   1.1182]        */
    /*  u = 0.175     => K = [1.4346    0.8945    3.0629    0.6035   1.1284]    */
    rtb_d_x = tuning_GS2_U.X[0] - tuning_GS2_U.Y0[0];

    /* MATLAB Function: '<S17>/MATLAB Function' */
    rtb_Kz_idx_0 = 12.0004 * rtb_ControlAllocation[0] + 14.7226;

    /* MATLAB Function: '<S15>/MATLAB Function' */
    rtb_Kx = 0.5145 * rtb_ControlAllocation[2] + 1.3446;

    /* Product: '<S15>/Product1' incorporates:
     *  SignalConversion: '<S15>/TmpSignal ConversionAtProduct1Inport2'
     */
    u0 = rtb_Kx * rtb_d_x;

    /* MATLAB Function: '<S15>/MATLAB Function' */
    rtb_Kx_idx_0 = rtb_Kx;

    /* MATLAB Function: '<S17>/MATLAB Function' */
    rtb_Kz_idx_1 = 12.5729 * rtb_ControlAllocation[0] + 6.8078;

    /* MATLAB Function: '<S15>/MATLAB Function' */
    rtb_Kx = 0.5524 * rtb_ControlAllocation[2] + 0.7978;

    /* Product: '<S15>/Product1' incorporates:
     *  Inport: '<Root>/X'
     *  SignalConversion: '<S15>/TmpSignal ConversionAtProduct1Inport2'
     */
    u0 += rtb_Kx * tuning_GS2_U.X[3];

    /* Sum: '<S15>/Sum1' incorporates:
     *  Integrator: '<S15>/Integrator1'
     *  MATLAB Function: '<S15>/MATLAB Function'
     *  Product: '<S15>/Product'
     *  Product: '<S15>/Product1'
     */
    tuning_GS2_B.Sum1 = Kix * tuning_GS2_X.Integrator1_CSTATE_e - u0;

    /* MATLAB Function: '<S16>/MATLAB Function' */
    /* MATLAB Function 'GS2_Controller/y_GS2_controller/MATLAB Function': '<S22>:1' */
    /*  LQR gain          y        yd      phi       phi_d     int   */
    /*             K = [-0.9479 -0.5505    1.7378   0.3476    -0.7657] */
    /*  GS2_full_OK - config 1 */
    /*      LOE_L = (u - 0.3)/0.3;                                                 % normalized LOE */
    /*      Ky = [-1.4536   -0.8915] +  [-0.4937   -0.3555]*LOE_L; */
    /*      Kiy = -1.0775 - 0.3339*LOE_L; */
    /*  u = 0         => K = [-0.9599   -0.5360    1.7726    0.3247   -0.7436]    ~ LQR gain !!! */
    /*  u = 0.125     => K = [-1.1656   -0.6841    2.3126    0.4364   -0.8827]        */
    /*  u = 0.215     => K = [-1.3137   -0.7908    2.7013    0.5168   -0.9384]      */
    /*  recheck by evalSurf: Ok  */
    /*  GS2_y_roll_without_normalization - config 3  => bigger gain than choice 1 */
    /*      Ky = [-0.9599   -0.5360] +  [-1.8956   -1.3056]*u; */
    /*      Kiy = -0.7436 - 1.2635*u; */
    /*  u = 0         => K = [-0.9599   -0.5360    1.7720    0.3247   -0.7436]    ~ LQR gain !!! */
    /*  u = 0.125     => K = [-1.1968   -0.6992    2.3291    0.4331   -0.9015]        */
    /*  u = 0.215     => K = [-1.3675   -0.8167    2.7302    0.5111   -1.0153]      */
    /*  recheck by evalSurf: Ok   */
    /*  GS2_y_roll_without_normalization - config 4  => biggest gain */
    /* '<S22>:1:25' Ky = [-0.9599   -0.5360] +  [-2.8090   -1.7525]*u; */
    /* '<S22>:1:26' Kiy = -0.7436 - 2.1424*u; */
    Kiy = -0.7436 - 2.1424 * rtb_ControlAllocation[1];

    /* Sum: '<S6>/Sum4' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/Y0'
     */
    /*  u = 0         => K = [-0.9599   -0.5360    1.7720    0.3247   -0.7436]    ~ LQR gain !!! */
    /*  u = 0.125     => K = [-1.3110   -0.7551    2.4519    0.4502   -1.0114]        */
    /*  u = 0.215     => K = [-1.5638   -0.9128    2.9414    0.5406   -1.2042]      */
    /*  recheck by evalSurf: Ok   */
    /* '<S22>:1:32' gain = [Ky  Kiy]; */
    /*  Choice 0: GS2_full_OK - config 1 */
    /*      LOE_L = (u - 0.3)/0.3;                                                 % normalized LOE */
    /*      Ky = [-1.4536   -0.8915] +  [-0.4937   -0.3555]*LOE_L; */
    /*      Kiy = -1.0775 - 0.3339*LOE_L; */
    /*  u = 0         => K = [-0.9599   -0.5360    1.7726    0.3247   -0.7436]    ~ LQR gain !!! */
    /*  u = 0.125     => K = [-1.1656   -0.6841    2.3126    0.4364   -0.8827]        */
    /*  u = 0.215     => K = [-1.3137   -0.7908    2.7013    0.5168   -0.9384]      */
    /*  recheck by evalSurf: Ok  */
    /*  Choice 1: GS2_y_roll_without_normalization - config 1  => smaller gain than choice 1 */
    /*      Ky = [-0.9479   -0.5505] +  [-0.2841   -0.3298]*u; */
    /*      Kiy = -0.7657 - 0.0308*u; */
    /*  u = 0         => K = [-0.9479   -0.5505    1.7378    0.3476   -0.7657]    = LQR gain !!! */
    /*  u = 0.125     => K = [-0.9834   -0.5917    1.9732    0.4069   -0.7696]        */
    /*  u = 0.215     => K = [-1.0090   -0.6214    2.1426    0.4496   -0.7723]      */
    /*  recheck by evalSurf: Ok  */
    /*  Choice 2: GS2_y_roll_without_normalization - config 2  => outer loop bigger gain than choice 1, inner loop smaller gain than choice 1 */
    /*      Ky = [-0.9599   -0.5360] +  [-1.8071   -1.2476]*u; */
    /*      Kiy = -0.7436 - 1.1667*u; */
    /*  u = 0         => K = [-0.9599   -0.5360    1.7720   0.3247   -0.7436]    ~ LQR gain !!! */
    /*  u = 0.125     => K = [-1.1858   -0.6920    2.2897   0.4304   -0.8894]        */
    /*  u = 0.215     => K = [-1.3484   -0.8042    2.6625   0.5065   -0.9944]      */
    /*  recheck by evalSurf: Ok   */
    /*  Choice 3: GS2_y_roll_without_normalization - config 3  => bigger gain than choice 1 */
    /*      Ky = [-0.9599   -0.5360] +  [-1.8956   -1.3056]*u; */
    /*      Kiy = -0.7436 - 1.2635*u; */
    /*  u = 0         => K = [-0.9599   -0.5360    1.7720    0.3247   -0.7436]    ~ LQR gain !!! */
    /*  u = 0.125     => K = [-1.1968   -0.6992    2.3291    0.4331   -0.9015]        */
    /*  u = 0.215     => K = [-1.3675   -0.8167    2.7302    0.5111   -1.0153]      */
    /*  recheck by evalSurf: Ok   */
    /*  Choice 4: GS2_y_roll_without_normalization - config 4  => biggest gain */
    /*      Ky = [-0.9599   -0.5360] +  [-2.8090   -1.7525]*u; */
    /*      Kiy = -0.7436 - 2.1424*u; */
    /*  u = 0         => K = [-0.9599   -0.5360    1.7720    0.3247   -0.7436]    ~ LQR gain !!! */
    /*  u = 0.125     => K = [-1.3110   -0.7551    2.4519    0.4502   -1.0114]        */
    /*  u = 0.215     => K = [-1.5638   -0.9128    2.9414    0.5406   -1.2042]      */
    /*  recheck by evalSurf: Ok   */
    rtb_d_y = tuning_GS2_U.X[1] - tuning_GS2_U.Y0[1];

    /* MATLAB Function: '<S16>/MATLAB Function' */
    rtb_Ky = -2.809 * rtb_ControlAllocation[1] + -0.9599;

    /* Product: '<S16>/Product1' incorporates:
     *  SignalConversion: '<S16>/TmpSignal ConversionAtProduct1Inport2'
     */
    u0 = rtb_Ky * rtb_d_y;

    /* MATLAB Function: '<S16>/MATLAB Function' */
    rtb_Ky_idx_0 = rtb_Ky;
    rtb_Ky = -1.7525 * rtb_ControlAllocation[1] + -0.536;

    /* Product: '<S16>/Product1' incorporates:
     *  Inport: '<Root>/X'
     *  SignalConversion: '<S16>/TmpSignal ConversionAtProduct1Inport2'
     */
    u0 += rtb_Ky * tuning_GS2_U.X[4];

    /* Sum: '<S16>/Sum1' incorporates:
     *  Integrator: '<S16>/Integrator1'
     *  MATLAB Function: '<S16>/MATLAB Function'
     *  Product: '<S16>/Product'
     *  Product: '<S16>/Product1'
     */
    tuning_GS2_B.Sum1_e = Kiy * tuning_GS2_X.Integrator1_CSTATE_p - u0;

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
    /* MATLAB Function 'GS2_Controller/roll_GS2_controller/MATLAB Function': '<S20>:1' */
    /*  LQR gain          y        yd      phi       phi_d     int   */
    /*             K = [-0.9479 -0.5505    1.7378   0.3476    -0.7657] */
    /*  GS2_full_OK - config 1 */
    /*      LOE_L = (u - 0.3)/0.3;                                                 % normalized LOE */
    /*      Kphi = [3.0685   0.5927] +  [1.2959  0.2680]*LOE_L; */
    /*  u = 0         => K = [-0.9599   -0.5360    1.7726    0.3247   -0.7436]    ~ LQR gain !!! */
    /*  u = 0.125     => K = [-1.1656   -0.6841    2.3126    0.4364   -0.8827]        */
    /*  u = 0.215     => K = [-1.3137   -0.7908    2.7013    0.5168   -0.9384]      */
    /*  recheck by evalSurf: Ok  */
    /*  GS2_y_roll_without_normalization - config 3 => bigger gain than choice 1         */
    /*      Kphi = [1.7720   0.3247] +  [4.4567  0.8672]*u; */
    /*  u = 0         => K = [-0.9599   -0.5360    1.7720    0.3247   -0.7436]    ~ LQR gain !!! */
    /*  u = 0.125     => K = [-1.1968   -0.6992    2.3291    0.4331   -0.9015]        */
    /*  u = 0.215     => K = [-1.3675   -0.8167    2.7302    0.5111   -1.0153]      */
    /*  recheck by evalSurf: Ok    */
    /*  GS2_y_roll_without_normalization - config 4 => bigger gain than choice 1         */
    /* '<S20>:1:21' Kphi = [1.7720   0.3247] +  [5.4391  1.0041]*u; */
    /*  u = 0         => K = [-0.9599   -0.5360    1.7720    0.3247   -0.7436]    ~ LQR gain !!! */
    /*  u = 0.125     => K = [-1.3110   -0.7551    2.4519    0.4502   -1.0114]        */
    /*  u = 0.215     => K = [-1.5638   -0.9128    2.9414    0.5406   -1.2042]      */
    /*  recheck by evalSurf: Ok    */
    /*  Choice 0: GS2_full_OK - config 1 */
    /*      LOE_L = (u - 0.3)/0.3;                                                 % normalized LOE */
    /*      Kphi = [3.0685   0.5927] +  [1.2959  0.2680]*LOE_L; */
    /*  u = 0         => K = [-0.9599   -0.5360    1.7726    0.3247   -0.7436]    ~ LQR gain !!! */
    /*  u = 0.125     => K = [-1.1656   -0.6841    2.3126    0.4364   -0.8827]        */
    /*  u = 0.215     => K = [-1.3137   -0.7908    2.7013    0.5168   -0.9384]      */
    /*  recheck by evalSurf: Ok  */
    /*  Choice 1: GS2_y_roll_without_normalization - config 1  => smaller gain than choice 1 */
    /*      Kphi = [1.7378   0.3476] +  [1.8829  0.4742]*u;   */
    /*  u = 0         => K = [-0.9479   -0.5505    1.7378    0.3476   -0.7657]    = LQR gain !!! */
    /*  u = 0.125     => K = [-0.9834   -0.5917    1.9732    0.4069   -0.7696]        */
    /*  u = 0.215     => K = [-1.0090   -0.6214    2.1426    0.4496   -0.7723]      */
    /*  recheck by evalSurf: Ok  */
    /*  Choice 2: GS2_y_roll_without_normalization - config 2  => outer loop bigger gain than choice 1, inner loop smaller gain than choice 1        */
    /*      Kphi = [1.7720   0.3247] +  [4.1419  0.8457]*u; */
    /*  u = 0         => K = [-0.9599   -0.5360    1.7720   0.3247   -0.7436]    ~ LQR gain !!! */
    /*  u = 0.125     => K = [-1.1858   -0.6920    2.2897   0.4304   -0.8894]        */
    /*  u = 0.215     => K = [-1.3484   -0.8042    2.6625   0.5065   -0.9944]      */
    /*  recheck by evalSurf: Ok      */
    /*  Choice 3: GS2_y_roll_without_normalization - config 3 => bigger gain than choice 1         */
    /*      Kphi = [1.7720   0.3247] +  [4.4567  0.8672]*u; */
    /*  u = 0         => K = [-0.9599   -0.5360    1.7720    0.3247   -0.7436]    ~ LQR gain !!! */
    /*  u = 0.125     => K = [-1.1968   -0.6992    2.3291    0.4331   -0.9015]        */
    /*  u = 0.215     => K = [-1.3675   -0.8167    2.7302    0.5111   -1.0153]      */
    /*  recheck by evalSurf: Ok    */
    /*  Choice 4: GS2_y_roll_without_normalization - config 4 => bigger gain than choice 1         */
    /*      Kphi = [1.7720   0.3247] +  [5.4391  1.0041]*u; */
    /*  u = 0         => K = [-0.9599   -0.5360    1.7720    0.3247   -0.7436]    ~ LQR gain !!! */
    /*  u = 0.125     => K = [-1.3110   -0.7551    2.4519    0.4502   -1.0114]        */
    /*  u = 0.215     => K = [-1.5638   -0.9128    2.9414    0.5406   -1.2042]      */
    /*  recheck by evalSurf: Ok   */
    if (rtmIsMajorTimeStep((&tuning_GS2_M)) &&
        (&tuning_GS2_M)->Timing.TaskCounters.TID[2] == 0) {
      /* Fcn: '<S4>/Fcn' */
      tuning_GS2_B.Fcn = -tuning_GS2_B.T_outer[1] * std::sin
        (tuning_GS2_B.T_outer[2]) + tuning_GS2_B.T_outer[0] * std::cos
        (tuning_GS2_B.T_outer[2]);
    }

    /* MATLAB Function: '<S13>/MATLAB Function' */
    /* MATLAB Function 'GS2_Controller/pitch_GS2_controller/MATLAB Function': '<S18>:1' */
    /*  LQR gain1:         x        xd      theta    theta_d     int   */
    /*             K = [1.2426   0.7085]  [2.2946    0.4589]   [0.9913] */
    /*  GS2_x_pitch_OK  */
    /*      LOE_M = (u - 0.3)/0.3;                                                 % normalized LOE */
    /*      Ktheta =  [3.2979    0.6522 ] +  [ 0.7514    0.2016]*LOE_M;        */
    /*  u = 0         => K = [1.3346    0.7978    2.5465    0.4506   1.0925]     = LQR gain2 !!! */
    /*  u = 0.125     => K = [1.3936    0.8456    2.8596    0.5346   1.0948]        */
    /*  u = 0.175     => K = [1.4172    0.8647    2.9848    0.5682   1.0957]      */
    /*  recheck by evalSurf: Ok  */
    /*  GS2_x_pitch_without_normalization_ML17b - Config 4 (all increase), biggest gain        */
    /* '<S18>:1:14' Ktheta =  [2.5465  0.4506] +  [2.9509   0.8739]*u; */
    /*  u = 0         => K = [1.3346    0.7978    2.5465    0.4506   1.0925]     = LQR gain2 !!! */
    /*  u = 0.125     => K = [1.4089    0.8668    2.9154    0.5598   1.1182]        */
    /*  u = 0.175     => K = [1.4346    0.8945    3.0629    0.6035   1.1284]      */
    /*  recheck by evalSurf: Ok  */
    /*  Note1: GS2_full_OK.m => TOO BIG x gains */
    /*  Note 2 */
    /*  LQR gain2:         x        xd      theta    theta_d     int   */
    /*             K = [1.3346   0.7978]  [2.5465    0.4506]   [1.0925] */
    /*  compare: test3_lqr1 vs test3_lqr2 => same result */
    /*  GS2_x_pitch_without_normalization_ML17b - Config 1 (only integral gain decreases)      */
    /*      Ktheta =  [2.5465  0.4506] +  [2.1995   0.7256]*u;   */
    /*  u = 0         => K = [1.3346    0.7978    2.5465    0.4506   1.0925]     = LQR gain2 !!! */
    /*  u = 0.125     => K = [1.3599    0.8358    2.8214    0.5413   1.0645]        */
    /*  u = 0.175     => K = [1.3660    0.8510    2.9314    0.5776   1.0533]      */
    /*  recheck by evalSurf: Ok      */
    /*  GS2_x_pitch_without_normalization_ML17b - Config 2 (only integral gain decreases), bigger gain        */
    /*      Ktheta =  [2.5465  0.4506] +  [2.8659   0.9145]*u;   */
    /*  u = 0         => K = [1.3346    0.7978    2.5465    0.4506   1.0925]     = LQR gain2 !!! */
    /*  u = 0.125     => K = [1.3816    0.8590    2.9047    0.5649   1.0843]        */
    /*  u = 0.175     => K = [1.3963    0.8835    3.0480    0.6106   1.0811]      */
    /*  recheck by evalSurf: Ok   */
    /*  GS2_x_pitch_without_normalization_ML17b - Config 3 (inner loop increases, outer loop decreases)        */
    /*      Ktheta =  [2.5465  0.4506] +  [1.3366   0.6001]*u;   */
    /*  u = 0         => K = [1.3346    0.7978    2.5465    0.4506   1.0925]     = LQR gain2 !!! */
    /*  u = 0.125     => K = [1.2857    0.7945    2.7136    0.5256   1.0051]        */
    /*  u = 0.175     => K = [1.2622    0.7931    2.7804    0.5556   0.9701]      */
    /*  recheck by evalSurf: Ok         */
    /* MATLAB Function 'GS2_Controller/psi_GS2_controller/MATLAB Function': '<S19>:1' */
    /*  LQR gain: K = [0.4980   0.3130  0.3162];    */
    /*  Choice 1: GS2_full - config 1 */
    /*      LOE_N = (u - 0.3)/0.3;                                                 % normalized LOE */
    /*      Kpsi = [0.6048   0.4733] +  [0.1068   0.1603]*LOE_N;     */
    /*      Kipsi = 0.3579 + 0.0417*LOE_N; */
    /*  u = 0         => K = [0.4980    0.3130   0.3162]     = LQR !!! */
    /*  u = 0.125     => K = [0.5425    0.3798   0.3336]        */
    /*  u = 0.2       => K = [0.5692    0.4199   0.3440]      */
    /*  recheck by evalSurf: Ok */
    /*  Choice 2: GS2_psi_without_normalization                                            */
    /* '<S19>:1:14' Kpsi = [0.4980   0.3130] +  [0.6933   0.5620]*u; */
    /* '<S19>:1:15' Kipsi = 0.3162 + 0.4422*u; */
    Kipsi = 0.4422 * rtb_ControlAllocation[3] + 0.3162;

    /* Sum: '<S6>/Sum6' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/Y0'
     */
    /*  u = 0         => K = [0.4980    0.3130   0.3162]     = LQR !!! */
    /*  u = 0.125     => K = [0.5847    0.3832   0.3715]        */
    /*  u = 0.2       => K = [0.6367    0.4254   0.4046]      */
    /*  recheck by evalSurf: Ok */
    /*     %% */
    /* '<S19>:1:22' gain = [Kpsi  Kipsi]; */
    rtb_d_psi = tuning_GS2_U.X[8] - tuning_GS2_U.Y0[3];

    /* MATLAB Function: '<S13>/MATLAB Function' */
    rtb_Kpsi = 0.6933 * rtb_ControlAllocation[3] + 0.498;

    /* Product: '<S13>/Product1' incorporates:
     *  SignalConversion: '<S13>/TmpSignal ConversionAtProduct1Inport2'
     */
    u0 = rtb_Kpsi * rtb_d_psi;

    /* MATLAB Function: '<S13>/MATLAB Function' */
    rtb_Kpsi_idx_0 = rtb_Kpsi;
    rtb_Kpsi = 0.562 * rtb_ControlAllocation[3] + 0.313;

    /* Product: '<S13>/Product1' incorporates:
     *  Inport: '<Root>/X'
     *  SignalConversion: '<S13>/TmpSignal ConversionAtProduct1Inport2'
     */
    u0 += rtb_Kpsi * tuning_GS2_U.X[11];

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
    rtb_Sum_idx_0 = (Kiz * tuning_GS2_X.Integrator1_CSTATE - (rtb_Kz_idx_0 *
      rtb_d_z + rtb_Kz_idx_1 * tuning_GS2_U.X[5])) + 15.107400000000002;

    /* Saturate: '<S4>/2Nm ' incorporates:
     *  Inport: '<Root>/X'
     *  MATLAB Function: '<S14>/MATLAB Function'
     *  Product: '<S14>/Product1'
     *  SignalConversion: '<S14>/TmpSignal ConversionAtProduct1Inport2'
     *  Sum: '<S14>/Sum1'
     *  Sum: '<S4>/Sum7'
     */
    rtb_ff_idx_0 = (tuning_GS2_B.Fcn1 + rtb_ff_idx_0) - ((5.4391 *
      rtb_ControlAllocation[1] + 1.772) * tuning_GS2_U.X[6] + (1.0041 *
      rtb_ControlAllocation[1] + 0.3247) * tuning_GS2_U.X[9]);
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
     *  MATLAB Function: '<S12>/MATLAB Function'
     *  Product: '<S12>/Product1'
     *  SignalConversion: '<S12>/TmpSignal ConversionAtProduct1Inport2'
     *  Sum: '<S12>/Sum1'
     *  Sum: '<S4>/Sum8'
     */
    rtb_ff_idx_1 = (tuning_GS2_B.Fcn + rtb_ff_idx_1) - ((2.9509 *
      rtb_ControlAllocation[2] + 2.5465) * tuning_GS2_U.X[7] + (0.8739 *
      rtb_ControlAllocation[2] + 0.4506) * tuning_GS2_U.X[10]);
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
     *  Integrator: '<S13>/Integrator1'
     *  MATLAB Function: '<S13>/MATLAB Function'
     *  Product: '<S13>/Product'
     *  Product: '<S13>/Product1'
     *  Sum: '<S13>/Sum1'
     */
    rtb_Sum_idx_3 = Kipsi * tuning_GS2_X.Integrator1_CSTATE_j - u0;
    if (rtb_Sum_idx_3 > 1.0) {
      /* SignalConversion: '<Root>/TmpSignal ConversionAtControl AllocationInport1' */
      rtb_Sum_idx_3 = 1.0;
    } else {
      if (rtb_Sum_idx_3 < -1.0) {
        /* SignalConversion: '<Root>/TmpSignal ConversionAtControl AllocationInport1' */
        rtb_Sum_idx_3 = -1.0;
      }
    }

    /* End of Saturate: '<S4>/1Nm' */
    for (i = 0; i < 6; i++) {
      /* Gain: '<Root>/Control Allocation' */
      u0 = tuning_GS2_ConstP.ControlAllocation_Gain_c[i + 18] * rtb_Sum_idx_3 +
        (tuning_GS2_ConstP.ControlAllocation_Gain_c[i + 12] * rtb_ff_idx_1 +
         (tuning_GS2_ConstP.ControlAllocation_Gain_c[i + 6] * rtb_ff_idx_0 +
          tuning_GS2_ConstP.ControlAllocation_Gain_c[i] * rtb_Sum_idx_0));

      /* Saturate: '<Root>/                   ' incorporates:
       *  Gain: '<Root>/Control Allocation'
       */
      if (u0 > 8.54858) {
        tuning_GS2_B.u[i] = 8.54858;
      } else if (u0 < 0.0) {
        tuning_GS2_B.u[i] = 0.0;
      } else {
        tuning_GS2_B.u[i] = u0;
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
    rtb_gamma_l[0] = (1.0 - rtb_LOE_out[0]) * tuning_GS2_B.u[0];
    rtb_gamma_l[1] = (1.0 - rtb_LOE_out[1]) * tuning_GS2_B.u[1];
    rtb_gamma_l[2] = (1.0 - rtb_LOE_out[2]) * tuning_GS2_B.u[2];
    rtb_gamma_l[3] = (1.0 - rtb_LOE_out[3]) * tuning_GS2_B.u[3];
    rtb_gamma_l[4] = (1.0 - rtb_LOE_out[4]) * tuning_GS2_B.u[4];
    rtb_gamma_l[5] = (1.0 - rtb_LOE_out[5]) * tuning_GS2_B.u[5];

    /* Outport: '<Root>/motor_command' */
    for (i = 0; i < 6; i++) {
      /* Gain: '<S7>/mapping_0_200' incorporates:
       *  Gain: '<S7>/      '
       *  Gain: '<S7>/rads_to_RPM'
       *  Sqrt: '<S7>/Sqrt1'
       *  Sum: '<S7>/Sum3'
       */
      u0 = (std::sqrt(116978.4923343994 * rtb_gamma_l[i]) * 9.5493 - 1250.0) *
        0.022857142857142857;

      /* Saturate: '<S7>/Saturation' */
      if (u0 > 200.0) {
        tuning_GS2_Y.motor_command[i] = 200.0;
      } else if (u0 < 0.0) {
        tuning_GS2_Y.motor_command[i] = 0.0;
      } else {
        tuning_GS2_Y.motor_command[i] = u0;
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
      rtb_ControlAllocation[0] = tuning_GS2_U.ref[0];
      rtb_ControlAllocation[1] = tuning_GS2_U.ref[1];
      rtb_ControlAllocation[2] = tuning_GS2_U.ref[2];
      rtb_ControlAllocation[3] = tuning_GS2_U.ref[3];

      /* '<S71>:1:6' if t>=25 */
      if (rtb_Clock >= 25.0) {
        /* '<S71>:1:7' ref = Y0; */
        rtb_ControlAllocation[0] = tuning_GS2_U.Y0[0];
        rtb_ControlAllocation[1] = tuning_GS2_U.Y0[1];
        rtb_ControlAllocation[2] = tuning_GS2_U.Y0[2];
        rtb_ControlAllocation[3] = tuning_GS2_U.Y0[3];
      }
      break;

     case 1:
      /* '<S71>:1:9' case 1      % waypoint */
      /*  waypoint */
      /* '<S71>:1:10' if t<=15 */
      if (rtb_Clock <= 15.0) {
        /* '<S71>:1:11' ref = [Y0(1); Y0(2); 1; Y0(4)]; */
        rtb_ControlAllocation[0] = tuning_GS2_U.Y0[0];
        rtb_ControlAllocation[1] = tuning_GS2_U.Y0[1];
        rtb_ControlAllocation[2] = 1.0;
        rtb_ControlAllocation[3] = tuning_GS2_U.Y0[3];
      } else if (rtb_Clock <= 25.0) {
        /* '<S71>:1:12' elseif t <= 25 */
        /* '<S71>:1:13' ref = [Y0(1)+1; Y0(2)-1; 1; Y0(4)]; */
        rtb_ControlAllocation[0] = tuning_GS2_U.Y0[0] + 1.0;
        rtb_ControlAllocation[1] = tuning_GS2_U.Y0[1] - 1.0;
        rtb_ControlAllocation[2] = 1.0;
        rtb_ControlAllocation[3] = tuning_GS2_U.Y0[3];
      } else if (rtb_Clock <= 35.0) {
        /* '<S71>:1:14' elseif t <=35 */
        /* '<S71>:1:15' ref = [Y0(1)-1; Y0(2)+1; 1; Y0(4)]; */
        rtb_ControlAllocation[0] = tuning_GS2_U.Y0[0] - 1.0;
        rtb_ControlAllocation[1] = tuning_GS2_U.Y0[1] + 1.0;
        rtb_ControlAllocation[2] = 1.0;
        rtb_ControlAllocation[3] = tuning_GS2_U.Y0[3];
      } else if (rtb_Clock <= 45.0) {
        /* '<S71>:1:16' elseif t <=45 */
        /* '<S71>:1:17' ref = [Y0(1)-1; Y0(2)+1; 1; Y0(4)]; */
        rtb_ControlAllocation[0] = tuning_GS2_U.Y0[0] - 1.0;
        rtb_ControlAllocation[1] = tuning_GS2_U.Y0[1] + 1.0;
        rtb_ControlAllocation[2] = 1.0;
        rtb_ControlAllocation[3] = tuning_GS2_U.Y0[3];
      } else if (rtb_Clock <= 55.0) {
        /* '<S71>:1:18' elseif t <=55 */
        /* '<S71>:1:19' ref = [Y0(1); Y0(2); 1; Y0(4)]; */
        rtb_ControlAllocation[0] = tuning_GS2_U.Y0[0];
        rtb_ControlAllocation[1] = tuning_GS2_U.Y0[1];
        rtb_ControlAllocation[2] = 1.0;
        rtb_ControlAllocation[3] = tuning_GS2_U.Y0[3];
      } else {
        /* '<S71>:1:20' else */
        /* '<S71>:1:21' ref = Y0; */
        rtb_ControlAllocation[0] = tuning_GS2_U.Y0[0];
        rtb_ControlAllocation[1] = tuning_GS2_U.Y0[1];
        rtb_ControlAllocation[2] = tuning_GS2_U.Y0[2];
        rtb_ControlAllocation[3] = tuning_GS2_U.Y0[3];
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
        rtb_ControlAllocation[0] = tuning_GS2_U.Y0[0];
        rtb_ControlAllocation[1] = tuning_GS2_U.Y0[1];
        rtb_ControlAllocation[2] = 0.75;
        rtb_ControlAllocation[3] = tuning_GS2_U.Y0[3];
      } else if (rtb_Clock <= 50.0) {
        /* '<S71>:1:37' elseif t <= 50 */
        /* '<S71>:1:38' ref = [Y0(1)+cos(t); Y0(2)+sin(t); 0.75; Y0(4)]; */
        rtb_ControlAllocation[0] = tuning_GS2_U.Y0[0] + std::cos(rtb_Clock);
        rtb_ControlAllocation[1] = tuning_GS2_U.Y0[1] + std::sin(rtb_Clock);
        rtb_ControlAllocation[2] = 0.75;
        rtb_ControlAllocation[3] = tuning_GS2_U.Y0[3];
      } else if (rtb_Clock <= 60.0) {
        /* '<S71>:1:39' elseif t <= 60 */
        /* '<S71>:1:40' ref = [Y0(1); Y0(2); 0.75; Y0(4)]; */
        rtb_ControlAllocation[0] = tuning_GS2_U.Y0[0];
        rtb_ControlAllocation[1] = tuning_GS2_U.Y0[1];
        rtb_ControlAllocation[2] = 0.75;
        rtb_ControlAllocation[3] = tuning_GS2_U.Y0[3];
      } else {
        /* '<S71>:1:41' else */
        /* '<S71>:1:42' ref = Y0; */
        rtb_ControlAllocation[0] = tuning_GS2_U.Y0[0];
        rtb_ControlAllocation[1] = tuning_GS2_U.Y0[1];
        rtb_ControlAllocation[2] = tuning_GS2_U.Y0[2];
        rtb_ControlAllocation[3] = tuning_GS2_U.Y0[3];
      }

      /*          ref = [cos(t); sin(t);min(t,15);Y0(4)]; */
      break;

     default:
      /* '<S71>:1:45' otherwise */
      /* '<S71>:1:46' ref = Y0; */
      rtb_ControlAllocation[0] = tuning_GS2_U.Y0[0];
      rtb_ControlAllocation[1] = tuning_GS2_U.Y0[1];
      rtb_ControlAllocation[2] = tuning_GS2_U.Y0[2];
      rtb_ControlAllocation[3] = tuning_GS2_U.Y0[3];
      break;
    }

    /* End of MATLAB Function: '<S6>/MATLAB Function' */

    /* Outport: '<Root>/ref_out' */
    tuning_GS2_Y.ref_out[0] = rtb_ControlAllocation[0];
    tuning_GS2_Y.ref_out[1] = rtb_ControlAllocation[1];
    tuning_GS2_Y.ref_out[2] = rtb_ControlAllocation[2];
    tuning_GS2_Y.ref_out[3] = rtb_ControlAllocation[3];

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
      tuning_GS2_Y.thrust_after[i] = rtb_gamma_l[i];
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
    tuning_GS2_Y.gain_GS[2] = Kiz;
    tuning_GS2_Y.gain_GS[5] = Kipsi;
    tuning_GS2_Y.gain_GS[8] = Kix;
    tuning_GS2_Y.gain_GS[0] = rtb_Kz_idx_0;
    tuning_GS2_Y.gain_GS[3] = rtb_Kpsi_idx_0;
    tuning_GS2_Y.gain_GS[6] = rtb_Kx_idx_0;
    tuning_GS2_Y.gain_GS[9] = rtb_Ky_idx_0;
    tuning_GS2_Y.gain_GS[1] = rtb_Kz_idx_1;
    tuning_GS2_Y.gain_GS[4] = rtb_Kpsi;
    tuning_GS2_Y.gain_GS[7] = rtb_Kx;
    tuning_GS2_Y.gain_GS[10] = rtb_Ky;
    tuning_GS2_Y.gain_GS[11] = Kiy;

    /* Outport: '<Root>/virtual_control' */
    tuning_GS2_Y.virtual_control[0] = rtb_Sum_idx_0;

    /* Sum: '<S6>/Sum' incorporates:
     *  Inport: '<Root>/Y0'
     */
    rtb_Sum_idx_0 = rtb_ControlAllocation[0] - tuning_GS2_U.Y0[0];

    /* Outport: '<Root>/virtual_control' */
    tuning_GS2_Y.virtual_control[1] = rtb_ff_idx_0;

    /* Sum: '<S6>/Sum' incorporates:
     *  Inport: '<Root>/Y0'
     */
    rtb_ff_idx_0 = rtb_ControlAllocation[1] - tuning_GS2_U.Y0[1];

    /* Outport: '<Root>/virtual_control' */
    tuning_GS2_Y.virtual_control[2] = rtb_ff_idx_1;

    /* Sum: '<S6>/Sum' incorporates:
     *  Inport: '<Root>/Y0'
     */
    rtb_ff_idx_1 = rtb_ControlAllocation[2] - tuning_GS2_U.Y0[2];

    /* Outport: '<Root>/virtual_control' */
    tuning_GS2_Y.virtual_control[3] = rtb_Sum_idx_3;

    /* Sum: '<S6>/Sum' incorporates:
     *  Inport: '<Root>/Y0'
     */
    rtb_Clock = rtb_ControlAllocation[3] - tuning_GS2_U.Y0[3];

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
    tuning_GS2_B.Sum3 = rtb_Clock - rtb_d_psi;

    /* Saturate: '<S15>/x' */
    if (rtb_Sum_idx_0 > 2.0) {
      rtb_Sum_idx_0 = 2.0;
    } else {
      if (rtb_Sum_idx_0 < -2.0) {
        rtb_Sum_idx_0 = -2.0;
      }
    }

    /* End of Saturate: '<S15>/x' */

    /* Sum: '<S15>/Sum3' */
    tuning_GS2_B.Sum3_f = rtb_Sum_idx_0 - rtb_d_x;

    /* Saturate: '<S16>/y' */
    if (rtb_ff_idx_0 > 2.0) {
      rtb_ff_idx_0 = 2.0;
    } else {
      if (rtb_ff_idx_0 < -2.0) {
        rtb_ff_idx_0 = -2.0;
      }
    }

    /* End of Saturate: '<S16>/y' */

    /* Sum: '<S16>/Sum3' */
    tuning_GS2_B.Sum3_f3 = rtb_ff_idx_0 - rtb_d_y;

    /* Saturate: '<S17>/z' */
    if (rtb_ff_idx_1 > 1.75) {
      rtb_ff_idx_1 = 1.75;
    } else {
      if (rtb_ff_idx_1 < 0.0) {
        rtb_ff_idx_1 = 0.0;
      }
    }

    /* End of Saturate: '<S17>/z' */

    /* Sum: '<S17>/Sum3' */
    tuning_GS2_B.Sum3_j = rtb_ff_idx_1 - rtb_d_z;
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
        rtb_gamma_l[i] = 0.0;
        for (i_0 = 0; i_0 < 6; i_0++) {
          rtb_gamma_l[i] += tuning_GS2_ConstP.A_Value[6 * i_0 + i] *
            rtb_MemoryX[i_0];
        }

        /* End of Product: '<S42>/A[k]*xhat[k|k-1]' */

        /* Sum: '<S42>/Add' */
        rtb_Add[i] = rtb_gamma_l[i] + tuning_GS2_B.Product3[i];
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
