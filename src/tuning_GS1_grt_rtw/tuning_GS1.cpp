/*
 * tuning_GS1.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "tuning_GS1".
 *
 * Model version              : 1.1548
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Sun Oct 14 15:44:34 2018
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
  int_T nXc = 4;
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
    int32_T b_j;
    static const real_T b[12] = { 2.6144, 2.6144, 2.6144, 2.6144, 2.6144, 2.6144,
      1.3106, 1.3106, 1.3106, 1.3106, 1.3106, 1.3106 };

    real_T rtb_Sum1_l[3];
    real_T rtb_Add_a[6];
    real_T rtb_LOE_out[6];
    real_T rtb_gamma_m[6];
    real_T rtb_Kiz[6];
    real_T rtb_d_z;
    real_T rtb_d_x;
    real_T rtb_d_y;
    real_T rtb_d_psi;
    real_T rtb_Clock;
    real_T rtb_MemoryX[6];
    real_T rtb_Kz[12];
    int32_T i;
    real_T rtb_Add_f[3];
    real_T rtb_Add_f_0[3];
    real_T rtb_ref_idx_3;
    real_T rtb_ref_idx_0;
    real_T rtb_ff_idx_1;
    real_T rtb_ff_idx_0;
    real_T rtb_gamma_idx_2;
    real_T rtb_gamma_idx_1;
    real_T rtb_gamma_idx_0;

    /* Clock: '<Root>/Clock' */
    rtb_Clock = (&tuning_GS1_M)->Timing.t[0];

    /* MATLAB Function 'Test_config_and_data/LOE_': '<S63>:1' */
    /* '<S63>:1:2' LOE_out = [0;0;0;0;0;0]; */
    /* '<S63>:1:3' for i = 1:6 */
    /* MATLAB Function 'FDD': '<S2>:1' */
    /* '<S2>:1:2' gamma = [0 0 0 0 0 0]'; */
    /* '<S2>:1:3' for i = 1:6 */
    for (i = 0; i < 6; i++) {
      /* MATLAB Function: '<S6>/LOE_' incorporates:
       *  Inport: '<Root>/LOE_a'
       *  Inport: '<Root>/LOE_t'
       */
      rtb_LOE_out[i] = 0.0;

      /* '<S63>:1:4' if t>= LOE_t(i) */
      if (rtb_Clock >= tuning_GS1_U.LOE_t[i]) {
        /* '<S63>:1:5' LOE_out(i) = LOE(i); */
        rtb_LOE_out[i] = tuning_GS1_U.LOE_a[i];
      }

      /* End of MATLAB Function: '<S6>/LOE_' */

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
      /* Delay: '<S4>/MemoryX' */
      for (i = 0; i < 6; i++) {
        if (tuning_GS1_DW.icLoad != 0) {
          tuning_GS1_DW.MemoryX_DSTATE[i] = 0.0;
        }

        rtb_MemoryX[i] = tuning_GS1_DW.MemoryX_DSTATE[i];
      }

      /* Outputs for Atomic SubSystem: '<S4>/UseCurrentEstimator' */
      /* Outputs for Enabled SubSystem: '<S36>/Enabled Subsystem' incorporates:
       *  EnablePort: '<S57>/Enable'
       */
      if (!tuning_GS1_DW.EnabledSubsystem_MODE) {
        tuning_GS1_DW.EnabledSubsystem_MODE = true;
      }

      /* Sum: '<S57>/Add1' incorporates:
       *  Constant: '<S4>/C'
       *  Delay: '<S4>/MemoryX'
       *  Inport: '<Root>/X'
       *  Product: '<S57>/Product'
       *  Product: '<S57>/Product2'
       */
      for (i = 0; i < 3; i++) {
        rtb_ref_idx_0 = 0.0;
        for (b_j = 0; b_j < 6; b_j++) {
          rtb_ref_idx_0 += tuning_GS1_ConstP.C_Value[3 * b_j + i] *
            tuning_GS1_DW.MemoryX_DSTATE[b_j];
        }

        rtb_Add_f[i] = tuning_GS1_U.X[9 + i] - rtb_ref_idx_0;
      }

      /* End of Sum: '<S57>/Add1' */
      for (i = 0; i < 6; i++) {
        /* Product: '<S57>/Product2' incorporates:
         *  Constant: '<S13>/KalmanGainM'
         */
        tuning_GS1_B.Product2[i] = 0.0;
        tuning_GS1_B.Product2[i] += tuning_GS1_ConstP.KalmanGainM_Value[i] *
          rtb_Add_f[0];
        tuning_GS1_B.Product2[i] += tuning_GS1_ConstP.KalmanGainM_Value[i + 6] *
          rtb_Add_f[1];
        tuning_GS1_B.Product2[i] += tuning_GS1_ConstP.KalmanGainM_Value[i + 12] *
          rtb_Add_f[2];

        /* Sum: '<S36>/Add' incorporates:
         *  Delay: '<S4>/MemoryX'
         */
        rtb_Add_a[i] = tuning_GS1_B.Product2[i] + tuning_GS1_DW.MemoryX_DSTATE[i];
      }

      /* End of Outputs for SubSystem: '<S36>/Enabled Subsystem' */
      /* End of Outputs for SubSystem: '<S4>/UseCurrentEstimator' */

      /* Product: '<S3>/Product1' incorporates:
       *  Constant: '<S3>/Constant1'
       */
      for (i = 0; i < 3; i++) {
        rtb_Sum1_l[i] = tuning_GS1_ConstP.Constant1_Value[i + 6] * rtb_Add_a[2]
          + (tuning_GS1_ConstP.Constant1_Value[i + 3] * rtb_Add_a[1] +
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
       *  Sum: '<S9>/Sum1'
       */
      for (i = 0; i < 3; i++) {
        rtb_Sum1_l[i] = (((tuning_GS1_ConstP.Constant1_Value[i + 3] * rtb_Add_a
                           [4] + tuning_GS1_ConstP.Constant1_Value[i] *
                           rtb_Add_a[3]) + tuning_GS1_ConstP.Constant1_Value[i +
                          6] * rtb_Add_a[5]) +
                         tuning_GS1_ConstP.Constant_Value[i]) + (rtb_Add_f[i] -
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
      rtb_gamma_idx_1 = rtb_Sum1_l[0] - rtb_Sum1_l[1] * -0.57735026918962584;
      rtb_gamma_idx_2 = ((rtb_Sum1_l[2] - rtb_Sum1_l[1] * 0.19603055651554735) -
                         rtb_gamma_idx_1 * 0.16976744186046511) /
        -0.10949999999999999;
      rtb_gamma_idx_1 -= rtb_gamma_idx_2 * 0.215;
      rtb_gamma_idx_1 /= 0.215;

      /*  Residu_1_4 */
      /* '<S10>:1:14' gamma    = [Residu(1)/u(1) */
      /* '<S10>:1:15'             Residu(2)/u(2) */
      /* '<S10>:1:16'             Residu(3)/u(3)]; */
      rtb_gamma_idx_0 = ((tuning_GS1_DW.Memory_PreviousInput[0] -
                          tuning_GS1_DW.Memory_PreviousInput[3]) - ((rtb_Sum1_l
        [1] - rtb_gamma_idx_2 * 0.18619546181365429) - rtb_gamma_idx_1 * 0.0) /
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
     *  Inport: '<Root>/LOE_calcul'
     *  Inport: '<Root>/LOE_mode'
     */
    switch ((int32_T)tuning_GS1_U.LOE_mode) {
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
        rtb_gamma_m[i] = tuning_GS1_U.LOE_calcul[i];
      }
      break;

     default:
      for (i = 0; i < 6; i++) {
        rtb_gamma_m[i] = tuning_GS1_B.LOE_FDD[i];
      }
      break;
    }

    /* End of MultiPortSwitch: '<Root>/Multiport Switch' */

    /* MATLAB Function: '<S8>/MATLAB Function' */
    /* MATLAB Function 'z_GS_controller/MATLAB Function': '<S65>:1' */
    /*  to change 1 */
    /* '<S65>:1:3' un = (u - 0.5)./0.5; */
    for (i = 0; i < 6; i++) {
      rtb_gamma_m[i] = (rtb_gamma_m[i] - 0.5) / 0.5;
    }

    /*  normalized LOE */
    /*  to change 2 */
    /* '<S65>:1:6' Kz  = ones(6,1)*[2.6144    1.3106]; */
    memcpy(&rtb_Kz[0], &b[0], 12U * sizeof(real_T));

    /* '<S65>:1:7' Kiz = 1.9268.*ones(6,1); */
    for (i = 0; i < 6; i++) {
      rtb_Kiz[i] = 1.9268;
    }

    /* '<S65>:1:9' Kz_i  = [0.0345    0.0399]; */
    /* '<S65>:1:10' Kz_j  = [0.0381    0.0525]; */
    /* '<S65>:1:11' Kiz_i = -0.0554; */
    /* '<S65>:1:12' Kiz_j = -0.0597; */
    /*  */
    /* '<S65>:1:15' for i = 1:3 */
    /* '<S65>:1:25' for i = 4:6 */
    for (i = 0; i < 3; i++) {
      /* '<S65>:1:16' Kz(i,:) = Kz(i,:) + Kz_i.*un(i); */
      rtb_Kz[i] += 0.0345 * rtb_gamma_m[i];
      rtb_Kz[i + 6] += 0.0399 * rtb_gamma_m[i];

      /* '<S65>:1:17' Kiz(i)  = Kiz(i)  + Kiz_i*un(i); */
      rtb_Kiz[i] += -0.0554 * rtb_gamma_m[i];

      /* '<S65>:1:18' for j = 1:3 */
      for (b_j = 0; b_j < 3; b_j++) {
        rtb_d_z = rtb_Kiz[i];

        /* '<S65>:1:19' if (j ~= i) */
        if (1 + b_j != 1 + i) {
          /* '<S65>:1:20' Kz(i,:) = Kz(i,:) + Kz_j.*un(j); */
          rtb_Kz[i] += 0.0381 * rtb_gamma_m[b_j];
          rtb_Kz[i + 6] += 0.0525 * rtb_gamma_m[b_j];

          /* '<S65>:1:21' Kiz(i)  = Kiz(i)  + Kiz_j*un(j); */
          rtb_d_z = -0.0597 * rtb_gamma_m[b_j] + rtb_Kiz[i];
        }

        rtb_Kiz[i] = rtb_d_z;
      }

      /* '<S65>:1:26' Kz(i,:) = Kz(i,:) + Kz_i.*un(i); */
      rtb_Kz[i + 3] += rtb_gamma_m[i + 3] * 0.0345;
      rtb_Kz[i + 9] += rtb_gamma_m[i + 3] * 0.0399;

      /* '<S65>:1:27' Kiz(i)  = Kiz(i)  + Kiz_i*un(i); */
      rtb_Kiz[i + 3] += rtb_gamma_m[i + 3] * -0.0554;

      /* '<S65>:1:28' for j = 4:6 */
      for (b_j = 0; b_j < 3; b_j++) {
        /* '<S65>:1:29' if (j ~= i) */
        if (4 + b_j != 4 + i) {
          /* '<S65>:1:30' Kz(i,:) = Kz(i,:) + Kz_j.*un(j); */
          rtb_Kz[i + 3] += rtb_gamma_m[b_j + 3] * 0.0381;
          rtb_Kz[i + 9] += rtb_gamma_m[b_j + 3] * 0.0525;

          /* '<S65>:1:31' Kiz(i)  = Kiz(i)  + Kiz_j*un(j); */
          rtb_Kiz[i + 3] += rtb_gamma_m[b_j + 3] * -0.0597;
        }
      }
    }

    /* End of MATLAB Function: '<S8>/MATLAB Function' */

    /* Sum: '<S6>/Sum5' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/Y0'
     */
    /*   */
    /*  KX = */
    /*      2.6144    1.3106    0.0345    0.0399    0.0381    0.0525    0.0381    0.0525 */
    /*      2.6144    1.3106    0.0381    0.0525    0.0345    0.0399    0.0381    0.0525 */
    /*      2.6144    1.3106    0.0381    0.0525    0.0381    0.0525    0.0345    0.0399 */
    /*      2.7492    1.6026    0.1543    0.1161    0.1543    0.1161    0.1543    0.1161 */
    /*  ----------------------------------- */
    /*  Ki = */
    /*      1.8709   -0.0554   -0.0597   -0.0597 */
    /*      1.8709   -0.0597   -0.0554   -0.0597 */
    /*      1.8709   -0.0597   -0.0597   -0.0554 */
    /*      1.9268    0.0233    0.0233    0.0233 */
    rtb_d_z = tuning_GS1_U.X[2] - tuning_GS1_U.Y0[2];

    /* Sum: '<S6>/Sum1' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/Y0'
     */
    rtb_d_x = tuning_GS1_U.X[0] - tuning_GS1_U.Y0[0];

    /* Sum: '<S58>/Sum2' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/gain'
     *  Integrator: '<S58>/Integrator1'
     *  Product: '<S58>/Product2'
     *  Product: '<S58>/Product3'
     *  SignalConversion: '<S58>/TmpSignal ConversionAtProduct3Inport2'
     */
    tuning_GS1_B.Sum2 = tuning_GS1_U.gain[2] * tuning_GS1_X.Integrator1_CSTATE_f
      - (tuning_GS1_U.gain[0] * rtb_d_x + tuning_GS1_U.gain[1] * tuning_GS1_U.X
         [3]);

    /* Sum: '<S6>/Sum4' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/Y0'
     */
    rtb_d_y = tuning_GS1_U.X[1] - tuning_GS1_U.Y0[1];

    /* Sum: '<S58>/Sum3' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/gain'
     *  Integrator: '<S58>/Integrator'
     *  Product: '<S58>/Product1'
     *  Product: '<S58>/Product4'
     *  SignalConversion: '<S58>/TmpSignal ConversionAtProduct1Inport2'
     */
    tuning_GS1_B.Sum3 = tuning_GS1_U.gain[5] * tuning_GS1_X.Integrator_CSTATE -
      (tuning_GS1_U.gain[3] * rtb_d_y + tuning_GS1_U.gain[4] * tuning_GS1_U.X[4]);

    /* RateTransition: '<S5>/T_outer' incorporates:
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

    /* End of RateTransition: '<S5>/T_outer' */
    if (rtmIsMajorTimeStep((&tuning_GS1_M)) &&
        (&tuning_GS1_M)->Timing.TaskCounters.TID[2] == 0) {
      /* Fcn: '<S5>/Fcn1' */
      tuning_GS1_B.Fcn1 = tuning_GS1_B.T_outer[1] * std::cos
        (tuning_GS1_B.T_outer[2]) + tuning_GS1_B.T_outer[0] * std::sin
        (tuning_GS1_B.T_outer[2]);
    }

    /* MATLAB Function: '<S6>/FFW' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/mode'
     */
    /* MATLAB Function 'Test_config_and_data/FFW': '<S62>:1' */
    /* '<S62>:1:2' ff = [0;0]; */
    rtb_ff_idx_0 = 0.0;
    rtb_ff_idx_1 = 0.0;

    /* '<S62>:1:3' g = 9.81; */
    /*  [x;y] = [cos(t); sin(t)] */
    /* '<S62>:1:5' if (test_mode == 2) */
    if ((tuning_GS1_U.mode == 2.0) && ((rtb_Clock >= 10.0) && (rtb_Clock <= 50.0)))
    {
      /* '<S62>:1:6' if (t >=10) && (t<= 50) */
      /* '<S62>:1:7' axref_N = -cos(t); */
      /* '<S62>:1:8' ayref_N = -sin(t); */
      /* '<S62>:1:10' axref_b = cos(X(8))*cos(X(9))*axref_N + cos(X(8))*sin(X(9))*ayref_N; */
      /* '<S62>:1:11' ayref_b = (sin(X(7))*sin(X(8))*cos(X(9)) - cos(X(7))*sin(X(9)))*axref_N + (sin(X(7))*sin(X(8))*sin(X(9)) + cos(X(7))*cos(X(9)))*ayref_N; */
      /*  azref_b = (cos(X(7))*sin(X(8))*cos(X(9)) + sin(X(7))*sin(X(9)))*axref_N + (cos(X(7))*sin(X(8))*sin(X(9)) - sin(X(7))*cos(X(9)))*ayref_N; */
      /*   */
      /* '<S62>:1:14' ff = [-ayref_b/g; axref_b/g]; */
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
      /* '<S62>:1:15' else */
      /* '<S62>:1:16' ff = [0;0]; */
    }

    /* End of MATLAB Function: '<S6>/FFW' */
    if (rtmIsMajorTimeStep((&tuning_GS1_M)) &&
        (&tuning_GS1_M)->Timing.TaskCounters.TID[2] == 0) {
      /* Fcn: '<S5>/Fcn' */
      tuning_GS1_B.Fcn = -tuning_GS1_B.T_outer[1] * std::sin
        (tuning_GS1_B.T_outer[2]) + tuning_GS1_B.T_outer[0] * std::cos
        (tuning_GS1_B.T_outer[2]);
    }

    /* Sum: '<S6>/Sum6' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/Y0'
     */
    rtb_d_psi = tuning_GS1_U.X[8] - tuning_GS1_U.Y0[3];

    /* Saturate: '<S5>/2Nm ' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/gain'
     *  Product: '<S60>/Product'
     *  SignalConversion: '<S60>/TmpSignal ConversionAtProductInport2'
     *  Sum: '<S5>/Sum7'
     *  Sum: '<S60>/Sum1'
     */
    rtb_ff_idx_0 = (tuning_GS1_B.Fcn1 + rtb_ff_idx_0) - (tuning_GS1_U.gain[9] *
      tuning_GS1_U.X[6] + tuning_GS1_U.gain[10] * tuning_GS1_U.X[9]);
    if (rtb_ff_idx_0 > 2.0) {
      /* SignalConversion: '<Root>/TmpSignal ConversionAtControl AllocationInport1' */
      rtb_ff_idx_0 = 2.0;
    } else {
      if (rtb_ff_idx_0 < -2.0) {
        /* SignalConversion: '<Root>/TmpSignal ConversionAtControl AllocationInport1' */
        rtb_ff_idx_0 = -2.0;
      }
    }

    /* End of Saturate: '<S5>/2Nm ' */

    /* Saturate: '<S5>/2Nm' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/gain'
     *  Product: '<S59>/Product'
     *  SignalConversion: '<S59>/TmpSignal ConversionAtProductInport2'
     *  Sum: '<S59>/Sum1'
     *  Sum: '<S5>/Sum8'
     */
    rtb_ff_idx_1 = (tuning_GS1_B.Fcn + rtb_ff_idx_1) - (tuning_GS1_U.gain[12] *
      tuning_GS1_U.X[7] + tuning_GS1_U.gain[13] * tuning_GS1_U.X[10]);
    if (rtb_ff_idx_1 > 2.0) {
      /* SignalConversion: '<Root>/TmpSignal ConversionAtControl AllocationInport1' */
      rtb_ff_idx_1 = 2.0;
    } else {
      if (rtb_ff_idx_1 < -2.0) {
        /* SignalConversion: '<Root>/TmpSignal ConversionAtControl AllocationInport1' */
        rtb_ff_idx_1 = -2.0;
      }
    }

    /* End of Saturate: '<S5>/2Nm' */

    /* Saturate: '<S5>/1Nm' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/gain'
     *  Integrator: '<S61>/Integrator1'
     *  Product: '<S61>/Product'
     *  Product: '<S61>/Product1'
     *  SignalConversion: '<S61>/TmpSignal ConversionAtProduct1Inport2'
     *  Sum: '<S61>/Sum1'
     */
    rtb_ref_idx_3 = tuning_GS1_U.gain[17] * tuning_GS1_X.Integrator1_CSTATE_a -
      (tuning_GS1_U.gain[15] * rtb_d_psi + tuning_GS1_U.gain[16] *
       tuning_GS1_U.X[11]);
    if (rtb_ref_idx_3 > 1.0) {
      /* SignalConversion: '<Root>/TmpSignal ConversionAtControl AllocationInport1' */
      rtb_ref_idx_3 = 1.0;
    } else {
      if (rtb_ref_idx_3 < -1.0) {
        /* SignalConversion: '<Root>/TmpSignal ConversionAtControl AllocationInport1' */
        rtb_ref_idx_3 = -1.0;
      }
    }

    /* End of Saturate: '<S5>/1Nm' */
    for (i = 0; i < 6; i++) {
      /* Gain: '<Root>/Control Allocation' incorporates:
       *  Saturate: '<Root>/                  '
       */
      rtb_ref_idx_0 = tuning_GS1_ConstP.ControlAllocation_Gain[i + 18] *
        rtb_ref_idx_3 + (tuning_GS1_ConstP.ControlAllocation_Gain[i + 12] *
                         rtb_ff_idx_1 +
                         (tuning_GS1_ConstP.ControlAllocation_Gain[i + 6] *
                          rtb_ff_idx_0 +
                          tuning_GS1_ConstP.ControlAllocation_Gain[i] *
                          15.107400000000002));

      /* Sum: '<Root>/Sum' incorporates:
       *  Inport: '<Root>/X'
       *  Integrator: '<S8>/Integrator1'
       *  Product: '<S8>/Product'
       *  Product: '<S8>/Product1'
       *  SignalConversion: '<S8>/TmpSignal ConversionAtProduct1Inport2'
       *  Sum: '<S8>/Sum1'
       */
      if (rtb_ref_idx_0 > 8.54858) {
        rtb_ref_idx_0 = 8.54858;
      } else {
        if (rtb_ref_idx_0 < 0.0) {
          rtb_ref_idx_0 = 0.0;
        }
      }

      tuning_GS1_B.Sum[i] = (rtb_Kiz[i] * tuning_GS1_X.Integrator1_CSTATE -
        (rtb_Kz[i + 6] * tuning_GS1_U.X[5] + rtb_Kz[i] * rtb_d_z)) +
        rtb_ref_idx_0;

      /* End of Sum: '<Root>/Sum' */
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
    rtb_gamma_m[0] = (1.0 - rtb_LOE_out[0]) * tuning_GS1_B.Sum[0];
    rtb_gamma_m[1] = (1.0 - rtb_LOE_out[1]) * tuning_GS1_B.Sum[1];
    rtb_gamma_m[2] = (1.0 - rtb_LOE_out[2]) * tuning_GS1_B.Sum[2];
    rtb_gamma_m[3] = (1.0 - rtb_LOE_out[3]) * tuning_GS1_B.Sum[3];
    rtb_gamma_m[4] = (1.0 - rtb_LOE_out[4]) * tuning_GS1_B.Sum[4];
    rtb_gamma_m[5] = (1.0 - rtb_LOE_out[5]) * tuning_GS1_B.Sum[5];

    /* Outport: '<Root>/motor_command' */
    for (i = 0; i < 6; i++) {
      /* Gain: '<S7>/mapping_0_200' incorporates:
       *  Gain: '<S7>/      '
       *  Gain: '<S7>/rads_to_RPM'
       *  Sqrt: '<S7>/Sqrt1'
       *  Sum: '<S7>/Sum3'
       */
      rtb_ref_idx_0 = (std::sqrt(116978.4923343994 * rtb_gamma_m[i]) * 9.5493 -
                       1250.0) * 0.022857142857142857;

      /* Saturate: '<S7>/Saturation' */
      if (rtb_ref_idx_0 > 200.0) {
        tuning_GS1_Y.motor_command[i] = 200.0;
      } else if (rtb_ref_idx_0 < 0.0) {
        tuning_GS1_Y.motor_command[i] = 0.0;
      } else {
        tuning_GS1_Y.motor_command[i] = rtb_ref_idx_0;
      }

      /* End of Saturate: '<S7>/Saturation' */
    }

    /* End of Outport: '<Root>/motor_command' */

    /* Outport: '<Root>/virtual_control' */
    tuning_GS1_Y.virtual_control[0] = 15.107400000000002;
    tuning_GS1_Y.virtual_control[1] = rtb_ff_idx_0;
    tuning_GS1_Y.virtual_control[2] = rtb_ff_idx_1;
    tuning_GS1_Y.virtual_control[3] = rtb_ref_idx_3;

    /* MATLAB Function: '<S6>/MATLAB Function' incorporates:
     *  Inport: '<Root>/Y0'
     *  Inport: '<Root>/mode'
     *  Inport: '<Root>/ref'
     */
    /* MATLAB Function 'Test_config_and_data/MATLAB Function': '<S64>:1' */
    /* '<S64>:1:2' ref = Y0; */
    /* '<S64>:1:3' switch test_mode */
    switch ((int32_T)tuning_GS1_U.mode) {
     case 0:
      /* '<S64>:1:4' case 0      % manual test */
      /*  manual test */
      /* '<S64>:1:5' ref = ref_manual; */
      rtb_ref_idx_0 = tuning_GS1_U.ref[0];
      rtb_ff_idx_0 = tuning_GS1_U.ref[1];
      rtb_ff_idx_1 = tuning_GS1_U.ref[2];
      rtb_ref_idx_3 = tuning_GS1_U.ref[3];
      break;

     case 1:
      /* '<S64>:1:6' case 1      % waypoint */
      /*  waypoint */
      /* '<S64>:1:7' if t<=15 */
      if (rtb_Clock <= 15.0) {
        /* '<S64>:1:8' ref = [Y0(1); Y0(2); 1; Y0(4)]; */
        rtb_ref_idx_0 = tuning_GS1_U.Y0[0];
        rtb_ff_idx_0 = tuning_GS1_U.Y0[1];
        rtb_ff_idx_1 = 1.0;
        rtb_ref_idx_3 = tuning_GS1_U.Y0[3];
      } else if (rtb_Clock <= 25.0) {
        /* '<S64>:1:9' elseif t <= 25 */
        /* '<S64>:1:10' ref = [Y0(1)+1; Y0(2)-1; 1; Y0(4)]; */
        rtb_ref_idx_0 = tuning_GS1_U.Y0[0] + 1.0;
        rtb_ff_idx_0 = tuning_GS1_U.Y0[1] - 1.0;
        rtb_ff_idx_1 = 1.0;
        rtb_ref_idx_3 = tuning_GS1_U.Y0[3];
      } else if (rtb_Clock <= 35.0) {
        /* '<S64>:1:11' elseif t <=35 */
        /* '<S64>:1:12' ref = [Y0(1)-1; Y0(2)+1; 1; Y0(4)]; */
        rtb_ref_idx_0 = tuning_GS1_U.Y0[0] - 1.0;
        rtb_ff_idx_0 = tuning_GS1_U.Y0[1] + 1.0;
        rtb_ff_idx_1 = 1.0;
        rtb_ref_idx_3 = tuning_GS1_U.Y0[3];
      } else if (rtb_Clock <= 45.0) {
        /* '<S64>:1:13' elseif t <=45 */
        /* '<S64>:1:14' ref = [Y0(1)-1; Y0(2)+1; 1; Y0(4)]; */
        rtb_ref_idx_0 = tuning_GS1_U.Y0[0] - 1.0;
        rtb_ff_idx_0 = tuning_GS1_U.Y0[1] + 1.0;
        rtb_ff_idx_1 = 1.0;
        rtb_ref_idx_3 = tuning_GS1_U.Y0[3];
      } else if (rtb_Clock <= 55.0) {
        /* '<S64>:1:15' elseif t <=55 */
        /* '<S64>:1:16' ref = [Y0(1); Y0(2); 1; Y0(4)]; */
        rtb_ref_idx_0 = tuning_GS1_U.Y0[0];
        rtb_ff_idx_0 = tuning_GS1_U.Y0[1];
        rtb_ff_idx_1 = 1.0;
        rtb_ref_idx_3 = tuning_GS1_U.Y0[3];
      } else {
        /* '<S64>:1:17' else */
        /* '<S64>:1:18' ref = Y0; */
        rtb_ref_idx_0 = tuning_GS1_U.Y0[0];
        rtb_ff_idx_0 = tuning_GS1_U.Y0[1];
        rtb_ff_idx_1 = tuning_GS1_U.Y0[2];
        rtb_ref_idx_3 = tuning_GS1_U.Y0[3];
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
      /* '<S64>:1:31' case 2      % circular tracking */
      /*  circular tracking */
      /* '<S64>:1:32' if t<=10 */
      if (rtb_Clock <= 10.0) {
        /* '<S64>:1:33' ref = [Y0(1); Y0(2); 0.75; Y0(4)]; */
        rtb_ref_idx_0 = tuning_GS1_U.Y0[0];
        rtb_ff_idx_0 = tuning_GS1_U.Y0[1];
        rtb_ff_idx_1 = 0.75;
        rtb_ref_idx_3 = tuning_GS1_U.Y0[3];
      } else if (rtb_Clock <= 50.0) {
        /* '<S64>:1:34' elseif t <= 50 */
        /* '<S64>:1:35' ref = [Y0(1)+cos(t); Y0(2)+sin(t); 0.75; Y0(4)]; */
        rtb_ref_idx_0 = tuning_GS1_U.Y0[0] + std::cos(rtb_Clock);
        rtb_ff_idx_0 = tuning_GS1_U.Y0[1] + std::sin(rtb_Clock);
        rtb_ff_idx_1 = 0.75;
        rtb_ref_idx_3 = tuning_GS1_U.Y0[3];
      } else if (rtb_Clock <= 60.0) {
        /* '<S64>:1:36' elseif t <= 60 */
        /* '<S64>:1:37' ref = [Y0(1); Y0(2); 0.75; Y0(4)]; */
        rtb_ref_idx_0 = tuning_GS1_U.Y0[0];
        rtb_ff_idx_0 = tuning_GS1_U.Y0[1];
        rtb_ff_idx_1 = 0.75;
        rtb_ref_idx_3 = tuning_GS1_U.Y0[3];
      } else {
        /* '<S64>:1:38' else */
        /* '<S64>:1:39' ref = Y0; */
        rtb_ref_idx_0 = tuning_GS1_U.Y0[0];
        rtb_ff_idx_0 = tuning_GS1_U.Y0[1];
        rtb_ff_idx_1 = tuning_GS1_U.Y0[2];
        rtb_ref_idx_3 = tuning_GS1_U.Y0[3];
      }

      /*          ref = [cos(t); sin(t);min(t,15);Y0(4)]; */
      break;

     default:
      /* '<S64>:1:42' otherwise */
      /* '<S64>:1:43' ref = Y0; */
      rtb_ref_idx_0 = tuning_GS1_U.Y0[0];
      rtb_ff_idx_0 = tuning_GS1_U.Y0[1];
      rtb_ff_idx_1 = tuning_GS1_U.Y0[2];
      rtb_ref_idx_3 = tuning_GS1_U.Y0[3];
      break;
    }

    /* End of MATLAB Function: '<S6>/MATLAB Function' */

    /* Outport: '<Root>/ref_out' */
    tuning_GS1_Y.ref_out[0] = rtb_ref_idx_0;
    tuning_GS1_Y.ref_out[1] = rtb_ff_idx_0;
    tuning_GS1_Y.ref_out[2] = rtb_ff_idx_1;
    tuning_GS1_Y.ref_out[3] = rtb_ref_idx_3;

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
      tuning_GS1_Y.thrust_pre[i] = tuning_GS1_B.Sum[i];

      /* Outport: '<Root>/thrust_after' */
      tuning_GS1_Y.thrust_after[i] = rtb_gamma_m[i];
    }

    if (rtmIsMajorTimeStep((&tuning_GS1_M)) &&
        (&tuning_GS1_M)->Timing.TaskCounters.TID[1] == 0) {
      /* Outport: '<Root>/acc_Kalman' */
      tuning_GS1_Y.acc_Kalman[0] = rtb_Add_a[3];

      /* Outport: '<Root>/M_Kalman' */
      tuning_GS1_Y.M_Kalman[0] = rtb_Sum1_l[0];

      /* Outport: '<Root>/vel_Kalman' */
      tuning_GS1_Y.vel_Kalman[0] = rtb_Add_a[0];

      /* Outport: '<Root>/acc_Kalman' */
      tuning_GS1_Y.acc_Kalman[1] = rtb_Add_a[4];

      /* Outport: '<Root>/M_Kalman' */
      tuning_GS1_Y.M_Kalman[1] = rtb_Sum1_l[1];

      /* Outport: '<Root>/vel_Kalman' */
      tuning_GS1_Y.vel_Kalman[1] = rtb_Add_a[1];

      /* Outport: '<Root>/acc_Kalman' */
      tuning_GS1_Y.acc_Kalman[2] = rtb_Add_a[5];

      /* Outport: '<Root>/M_Kalman' */
      tuning_GS1_Y.M_Kalman[2] = rtb_Sum1_l[2];

      /* Outport: '<Root>/vel_Kalman' */
      tuning_GS1_Y.vel_Kalman[2] = rtb_Add_a[2];
    }

    /* Outport: '<Root>/Kiz' */
    for (i = 0; i < 6; i++) {
      tuning_GS1_Y.Kiz[i] = rtb_Kiz[i];
    }

    /* End of Outport: '<Root>/Kiz' */
    if (rtmIsMajorTimeStep((&tuning_GS1_M)) &&
        (&tuning_GS1_M)->Timing.TaskCounters.TID[1] == 0) {
      /* Outputs for Enabled SubSystem: '<S31>/MeasurementUpdate' incorporates:
       *  EnablePort: '<S56>/Enable'
       */
      if (rtmIsMajorTimeStep((&tuning_GS1_M)) &&
          (!tuning_GS1_DW.MeasurementUpdate_MODE)) {
        tuning_GS1_DW.MeasurementUpdate_MODE = true;
      }

      if (tuning_GS1_DW.MeasurementUpdate_MODE) {
        for (i = 0; i < 3; i++) {
          /* Product: '<S56>/C[k]*xhat[k|k-1]' incorporates:
           *  Constant: '<S4>/C'
           *  Sum: '<S56>/Add1'
           */
          rtb_Add_f[i] = 0.0;
          for (b_j = 0; b_j < 6; b_j++) {
            rtb_Add_f[i] += tuning_GS1_ConstP.C_Value[3 * b_j + i] *
              rtb_MemoryX[b_j];
          }

          /* End of Product: '<S56>/C[k]*xhat[k|k-1]' */

          /* Sum: '<S56>/Sum' incorporates:
           *  Inport: '<Root>/X'
           *  Product: '<S56>/Product3'
           *  Sum: '<S56>/Add1'
           */
          rtb_Add_f_0[i] = tuning_GS1_U.X[9 + i] - rtb_Add_f[i];
        }

        /* Product: '<S56>/Product3' incorporates:
         *  Constant: '<S13>/KalmanGainL'
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

      /* End of Outputs for SubSystem: '<S31>/MeasurementUpdate' */
      for (i = 0; i < 6; i++) {
        /* Product: '<S31>/A[k]*xhat[k|k-1]' incorporates:
         *  Constant: '<S4>/A'
         *  Sum: '<S31>/Add'
         */
        rtb_gamma_m[i] = 0.0;
        for (b_j = 0; b_j < 6; b_j++) {
          rtb_gamma_m[i] += tuning_GS1_ConstP.A_Value[6 * b_j + i] *
            rtb_MemoryX[b_j];
        }

        /* End of Product: '<S31>/A[k]*xhat[k|k-1]' */

        /* Sum: '<S31>/Add' */
        rtb_Add[i] = rtb_gamma_m[i] + tuning_GS1_B.Product3[i];
      }
    }

    /* Sum: '<S6>/Sum' incorporates:
     *  Inport: '<Root>/Y0'
     */
    rtb_ref_idx_0 -= tuning_GS1_U.Y0[0];
    rtb_ff_idx_0 -= tuning_GS1_U.Y0[1];
    rtb_ff_idx_1 -= tuning_GS1_U.Y0[2];
    rtb_Clock = rtb_ref_idx_3 - tuning_GS1_U.Y0[3];

    /* Saturate: '<S58>/x' */
    if (rtb_ref_idx_0 > 2.0) {
      rtb_ref_idx_0 = 2.0;
    } else {
      if (rtb_ref_idx_0 < -2.0) {
        rtb_ref_idx_0 = -2.0;
      }
    }

    /* End of Saturate: '<S58>/x' */

    /* Sum: '<S58>/Sum1' */
    tuning_GS1_B.Sum1 = rtb_ref_idx_0 - rtb_d_x;

    /* Saturate: '<S58>/y' */
    if (rtb_ff_idx_0 > 2.0) {
      rtb_ff_idx_0 = 2.0;
    } else {
      if (rtb_ff_idx_0 < -2.0) {
        rtb_ff_idx_0 = -2.0;
      }
    }

    /* End of Saturate: '<S58>/y' */

    /* Sum: '<S58>/Sum4' */
    tuning_GS1_B.Sum4 = rtb_ff_idx_0 - rtb_d_y;

    /* Saturate: '<S61>/yaw' */
    if (rtb_Clock > 3.1415926535897931) {
      rtb_Clock = 3.1415926535897931;
    } else {
      if (rtb_Clock < -3.1415926535897931) {
        rtb_Clock = -3.1415926535897931;
      }
    }

    /* End of Saturate: '<S61>/yaw' */

    /* Sum: '<S61>/Sum3' */
    tuning_GS1_B.Sum3_f = rtb_Clock - rtb_d_psi;

    /* Saturate: '<S8>/z' */
    if (rtb_ff_idx_1 > 1.75) {
      rtb_ff_idx_1 = 1.75;
    } else {
      if (rtb_ff_idx_1 < 0.0) {
        rtb_ff_idx_1 = 0.0;
      }
    }

    /* End of Saturate: '<S8>/z' */

    /* Sum: '<S8>/Sum3' */
    tuning_GS1_B.Sum3_l = rtb_ff_idx_1 - rtb_d_z;
  }

  if (rtmIsMajorTimeStep((&tuning_GS1_M))) {
    int32_T i;
    if (rtmIsMajorTimeStep((&tuning_GS1_M)) &&
        (&tuning_GS1_M)->Timing.TaskCounters.TID[1] == 0) {
      /* Update for Delay: '<S4>/MemoryX' */
      tuning_GS1_DW.icLoad = 0U;
      for (i = 0; i < 6; i++) {
        /* Update for Memory: '<S3>/Memory' */
        tuning_GS1_DW.Memory_PreviousInput[i] = tuning_GS1_B.Sum[i];

        /* Update for Delay: '<S4>/MemoryX' */
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

  /* Derivatives for Integrator: '<S8>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = tuning_GS1_B.Sum3_l;

  /* Derivatives for Integrator: '<S58>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_f = tuning_GS1_B.Sum1;

  /* Derivatives for Integrator: '<S58>/Integrator' */
  _rtXdot->Integrator_CSTATE = tuning_GS1_B.Sum4;

  /* Derivatives for Integrator: '<S61>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_a = tuning_GS1_B.Sum3_f;
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

    /* InitializeConditions for Delay: '<S4>/MemoryX' */
    tuning_GS1_DW.icLoad = 1U;

    /* InitializeConditions for Integrator: '<S8>/Integrator1' */
    tuning_GS1_X.Integrator1_CSTATE = 0.0;

    /* InitializeConditions for Integrator: '<S58>/Integrator1' */
    tuning_GS1_X.Integrator1_CSTATE_f = 0.0;

    /* InitializeConditions for Integrator: '<S58>/Integrator' */
    tuning_GS1_X.Integrator_CSTATE = 0.0;

    /* InitializeConditions for Integrator: '<S61>/Integrator1' */
    tuning_GS1_X.Integrator1_CSTATE_a = 0.0;

    /* SystemInitialize for Enabled SubSystem: '<S31>/MeasurementUpdate' */
    /* SystemInitialize for Atomic SubSystem: '<S4>/UseCurrentEstimator' */
    /* SystemInitialize for Enabled SubSystem: '<S36>/Enabled Subsystem' */
    for (i = 0; i < 6; i++) {
      /* InitializeConditions for Memory: '<S3>/Memory' */
      tuning_GS1_DW.Memory_PreviousInput[i] = 2.5179000000000005;

      /* SystemInitialize for Outport: '<S57>/deltax' */
      tuning_GS1_B.Product2[i] = 0.0;

      /* SystemInitialize for Outport: '<S56>/L*(y[k]-yhat[k|k-1])' */
      tuning_GS1_B.Product3[i] = 0.0;
    }

    /* End of SystemInitialize for SubSystem: '<S36>/Enabled Subsystem' */
    /* End of SystemInitialize for SubSystem: '<S4>/UseCurrentEstimator' */
    /* End of SystemInitialize for SubSystem: '<S31>/MeasurementUpdate' */
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
