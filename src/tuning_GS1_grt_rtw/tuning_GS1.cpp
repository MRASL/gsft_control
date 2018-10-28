/*
 * tuning_GS1.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "tuning_GS1".
 *
 * Model version              : 1.2101
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Mon Oct 22 19:08:51 2018
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
    real_T un[6];
    static const real_T Kz[12] = { 2.6144, 2.6144, 2.6144, 2.6144, 2.6144,
      2.6144, 1.3106, 1.3106, 1.3106, 1.3106, 1.3106, 1.3106 };

    real_T rtb_Sum1_cy[3];
    real_T rtb_Add_a[6];
    real_T rtb_LOE_out[6];
    real_T rtb_gamma_m[6];
    real_T rtb_u[6];
    real_T rtb_d_z;
    real_T rtb_d_psi;
    real_T rtb_Kix[4];
    real_T rtb_d_x;
    real_T rtb_Kiy[6];
    real_T rtb_d_y;
    real_T rtb_ref[4];
    real_T rtb_Clock;
    real_T rtb_MemoryX[6];
    real_T rtb_Kz[12];
    real_T rtb_Kxtheta[16];
    real_T rtb_Kyphi[24];
    int32_T i;
    static const real_T tmp[6] = { -1.4438, 1.4438, -1.4438, 1.4438, -1.4438,
      1.4438 };

    static const real_T tmp_0[12] = { -2.274, 2.274, -2.274, 2.274, -2.274,
      2.274, -1.4292, 1.4292, -1.4292, 1.4292, -1.4292, 1.4292 };

    real_T rtb_Add_f[3];
    real_T rtb_Add_f_0[3];
    real_T tmp_1[6];
    real_T tmp_2[6];
    int32_T i_0;
    real_T rtb_ff_idx_1;
    real_T rtb_ff_idx_0;
    real_T rtb_gamma_idx_2;
    real_T rtb_gamma_idx_1;
    real_T rtb_gamma_idx_0;
    real_T u0;

    /* Clock: '<Root>/Clock' */
    rtb_Clock = (&tuning_GS1_M)->Timing.t[0];

    /* MATLAB Function 'Test_config_and_data/LOE_': '<S72>:1' */
    /* '<S72>:1:2' LOE_out = [0;0;0;0;0;0]; */
    /* '<S72>:1:3' for i = 1:6 */
    /* MATLAB Function 'FDD': '<S2>:1' */
    /* '<S2>:1:2' gamma = [0 0 0 0 0 0]'; */
    /* '<S2>:1:3' for i = 1:6 */
    for (i = 0; i < 6; i++) {
      /* MATLAB Function: '<S7>/LOE_' incorporates:
       *  Inport: '<Root>/LOE_a'
       *  Inport: '<Root>/LOE_t'
       */
      rtb_LOE_out[i] = 0.0;

      /* '<S72>:1:4' if t>= LOE_t(i) */
      if (rtb_Clock >= tuning_GS1_U.LOE_t[i]) {
        /* '<S72>:1:5' LOE_out(i) = LOE(i); */
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
      /* Outputs for Enabled SubSystem: '<S46>/Enabled Subsystem' incorporates:
       *  EnablePort: '<S67>/Enable'
       */
      if (!tuning_GS1_DW.EnabledSubsystem_MODE) {
        tuning_GS1_DW.EnabledSubsystem_MODE = true;
      }

      /* Sum: '<S67>/Add1' incorporates:
       *  Constant: '<S5>/C'
       *  Delay: '<S5>/MemoryX'
       *  Inport: '<Root>/X'
       *  Product: '<S67>/Product'
       *  Product: '<S67>/Product2'
       */
      for (i = 0; i < 3; i++) {
        rtb_gamma_idx_1 = 0.0;
        for (i_0 = 0; i_0 < 6; i_0++) {
          rtb_gamma_idx_1 += tuning_GS1_ConstP.C_Value[3 * i_0 + i] *
            tuning_GS1_DW.MemoryX_DSTATE[i_0];
        }

        rtb_Add_f[i] = tuning_GS1_U.X[9 + i] - rtb_gamma_idx_1;
      }

      /* End of Sum: '<S67>/Add1' */
      for (i = 0; i < 6; i++) {
        /* Product: '<S67>/Product2' incorporates:
         *  Constant: '<S23>/KalmanGainM'
         */
        tuning_GS1_B.Product2[i] = 0.0;
        tuning_GS1_B.Product2[i] += tuning_GS1_ConstP.KalmanGainM_Value[i] *
          rtb_Add_f[0];
        tuning_GS1_B.Product2[i] += tuning_GS1_ConstP.KalmanGainM_Value[i + 6] *
          rtb_Add_f[1];
        tuning_GS1_B.Product2[i] += tuning_GS1_ConstP.KalmanGainM_Value[i + 12] *
          rtb_Add_f[2];

        /* Sum: '<S46>/Add' incorporates:
         *  Delay: '<S5>/MemoryX'
         */
        rtb_Add_a[i] = tuning_GS1_B.Product2[i] + tuning_GS1_DW.MemoryX_DSTATE[i];
      }

      /* End of Outputs for SubSystem: '<S46>/Enabled Subsystem' */
      /* End of Outputs for SubSystem: '<S5>/UseCurrentEstimator' */

      /* Product: '<S3>/Product1' incorporates:
       *  Constant: '<S3>/Constant1'
       */
      for (i = 0; i < 3; i++) {
        rtb_Sum1_cy[i] = tuning_GS1_ConstP.Constant1_Value[i + 6] * rtb_Add_a[2]
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
      rtb_Add_f[0] = rtb_Add_a[1] * rtb_Sum1_cy[2];
      rtb_Add_f[1] = rtb_Add_a[2] * rtb_Sum1_cy[0];
      rtb_Add_f[2] = rtb_Add_a[0] * rtb_Sum1_cy[1];
      rtb_Add_f_0[0] = rtb_Add_a[2] * rtb_Sum1_cy[1];
      rtb_Add_f_0[1] = rtb_Add_a[0] * rtb_Sum1_cy[2];
      rtb_Add_f_0[2] = rtb_Add_a[1] * rtb_Sum1_cy[0];

      /* Sum: '<S3>/Sum3' incorporates:
       *  Constant: '<S3>/Constant'
       *  Constant: '<S3>/Constant1'
       *  Product: '<S3>/Product'
       *  Sum: '<S9>/Sum1'
       */
      for (i = 0; i < 3; i++) {
        rtb_Sum1_cy[i] = (((tuning_GS1_ConstP.Constant1_Value[i + 3] *
                            rtb_Add_a[4] + tuning_GS1_ConstP.Constant1_Value[i] *
                            rtb_Add_a[3]) + tuning_GS1_ConstP.Constant1_Value[i
                           + 6] * rtb_Add_a[5]) +
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
      rtb_gamma_idx_1 = rtb_Sum1_cy[0] - rtb_Sum1_cy[1] * -0.57735026918962584;
      rtb_gamma_idx_2 = ((rtb_Sum1_cy[2] - rtb_Sum1_cy[1] * 0.19603055651554735)
                         - rtb_gamma_idx_1 * 0.16976744186046511) /
        -0.10949999999999999;
      rtb_gamma_idx_1 -= rtb_gamma_idx_2 * 0.215;
      rtb_gamma_idx_1 /= 0.215;

      /*  Residu_1_4 */
      /* '<S10>:1:14' gamma    = [Residu(1)/u(1) */
      /* '<S10>:1:15'             Residu(2)/u(2) */
      /* '<S10>:1:16'             Residu(3)/u(3)]; */
      rtb_gamma_idx_0 = ((tuning_GS1_DW.Memory_PreviousInput[0] -
                          tuning_GS1_DW.Memory_PreviousInput[3]) -
                         ((rtb_Sum1_cy[1] - rtb_gamma_idx_2 *
                           0.18619546181365429) - rtb_gamma_idx_1 * 0.0) /
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
    /* MATLAB Function 'GS_controller/z_GS_controller/MATLAB Function': '<S22>:1' */
    /*    GS_z_gain1_OK.m */
    /*  to change 1 */
    /* '<S22>:1:4' un = (u - 0.5)./0.5; */
    for (i = 0; i < 6; i++) {
      /* Saturate: '<Root>/                        ' */
      if (rtb_gamma_m[i] > 1.0) {
        rtb_d_z = 1.0;
      } else if (rtb_gamma_m[i] < 0.0) {
        rtb_d_z = 0.0;
      } else {
        rtb_d_z = rtb_gamma_m[i];
      }

      /* MATLAB Function: '<S17>/MATLAB Function' */
      un[i] = (rtb_d_z - 0.5) / 0.5;

      /* Saturate: '<Root>/                        ' */
      rtb_u[i] = rtb_d_z;
    }

    /* MATLAB Function: '<S17>/MATLAB Function' */
    /*  normalized LOE */
    /*  to change 2 */
    /* '<S22>:1:7' Kz  = ones(6,1)*[2.6144    1.3106]; */
    memcpy(&rtb_Kz[0], &Kz[0], 12U * sizeof(real_T));

    /* '<S22>:1:8' Kiz = 1.9268.*ones(6,1); */
    for (i = 0; i < 6; i++) {
      rtb_gamma_m[i] = 1.9268;
    }

    /* '<S22>:1:10' Kz_i  = [0.0345    0.0399]; */
    /* '<S22>:1:11' Kz_j  = [0.0381    0.0525]; */
    /* '<S22>:1:12' Kiz_i = -0.0554; */
    /* '<S22>:1:13' Kiz_j = -0.0597; */
    /*  */
    /* '<S22>:1:15' Kz(1,:) =  Kz(1,:) + Kz_i.*un(1) + Kz_j.*un(2) + Kz_j.*un(3); */
    /* '<S22>:1:16' Kz(2,:) =  Kz(2,:) + Kz_j.*un(1) + Kz_i.*un(2) + Kz_j.*un(3); */
    /* '<S22>:1:17' Kz(3,:) =  Kz(3,:) + Kz_j.*un(1) + Kz_j.*un(2) + Kz_i.*un(3); */
    /* '<S22>:1:18' Kz(4,:) =  Kz(4,:) + Kz_i.*un(4) + Kz_j.*un(5) + Kz_j.*un(6); */
    /* '<S22>:1:19' Kz(5,:) =  Kz(5,:) + Kz_j.*un(4) + Kz_i.*un(5) + Kz_j.*un(6); */
    /* '<S22>:1:20' Kz(6,:) =  Kz(6,:) + Kz_j.*un(4) + Kz_j.*un(5) + Kz_i.*un(6); */
    rtb_Kz[0] = ((0.0345 * un[0] + 2.6144) + 0.0381 * un[1]) + 0.0381 * un[2];
    rtb_Kz[1] = ((0.0381 * un[0] + rtb_Kz[1]) + 0.0345 * un[1]) + 0.0381 * un[2];
    rtb_Kz[2] = ((0.0381 * un[0] + rtb_Kz[2]) + 0.0381 * un[1]) + 0.0345 * un[2];
    rtb_Kz[3] = ((0.0345 * un[3] + rtb_Kz[3]) + 0.0381 * un[4]) + 0.0381 * un[5];
    rtb_Kz[4] = ((0.0381 * un[3] + rtb_Kz[4]) + 0.0345 * un[4]) + 0.0381 * un[5];
    rtb_Kz[5] = ((0.0381 * un[3] + rtb_Kz[5]) + 0.0381 * un[4]) + 0.0345 * un[5];
    rtb_Kz[6] = ((0.0399 * un[0] + 1.3106) + 0.0525 * un[1]) + 0.0525 * un[2];
    rtb_Kz[7] = ((0.0525 * un[0] + rtb_Kz[7]) + 0.0399 * un[1]) + 0.0525 * un[2];
    rtb_Kz[8] = ((0.0525 * un[0] + rtb_Kz[8]) + 0.0525 * un[1]) + 0.0399 * un[2];
    rtb_Kz[9] = ((0.0399 * un[3] + rtb_Kz[9]) + 0.0525 * un[4]) + 0.0525 * un[5];
    rtb_Kz[10] = ((0.0525 * un[3] + rtb_Kz[10]) + 0.0399 * un[4]) + 0.0525 * un
      [5];
    rtb_Kz[11] = ((0.0525 * un[3] + rtb_Kz[11]) + 0.0525 * un[4]) + 0.0399 * un
      [5];

    /* '<S22>:1:22' Kiz(1) =   Kiz(1) + Kiz_i.*un(1) + Kiz_j.*un(2) + Kiz_j.*un(3); */
    rtb_gamma_m[0] = ((-0.0554 * un[0] + 1.9268) + -0.0597 * un[1]) + -0.0597 *
      un[2];

    /* '<S22>:1:23' Kiz(2) =   Kiz(2) + Kiz_j.*un(1) + Kiz_i.*un(2) + Kiz_j.*un(3); */
    rtb_gamma_m[1] = ((-0.0597 * un[0] + rtb_gamma_m[1]) + -0.0554 * un[1]) +
      -0.0597 * un[2];

    /* '<S22>:1:24' Kiz(3) =   Kiz(3) + Kiz_j.*un(1) + Kiz_j.*un(2) + Kiz_i.*un(3); */
    rtb_gamma_m[2] = ((-0.0597 * un[0] + rtb_gamma_m[2]) + -0.0597 * un[1]) +
      -0.0554 * un[2];

    /* '<S22>:1:25' Kiz(4) =   Kiz(4) + Kiz_i.*un(4) + Kiz_j.*un(5) + Kiz_j.*un(6); */
    rtb_gamma_m[3] = ((-0.0554 * un[3] + rtb_gamma_m[3]) + -0.0597 * un[4]) +
      -0.0597 * un[5];

    /* '<S22>:1:26' Kiz(5) =   Kiz(5) + Kiz_j.*un(4) + Kiz_i.*un(5) + Kiz_j.*un(6); */
    rtb_gamma_m[4] = ((-0.0597 * un[3] + rtb_gamma_m[4]) + -0.0554 * un[4]) +
      -0.0597 * un[5];

    /* '<S22>:1:27' Kiz(6) =   Kiz(6) + Kiz_j.*un(4) + Kiz_j.*un(5) + Kiz_i.*un(6); */
    rtb_gamma_m[5] = ((-0.0597 * un[3] + rtb_gamma_m[5]) + -0.0597 * un[4]) +
      -0.0554 * un[5];

    /* Sum: '<S7>/Sum5' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/Y0'
     */
    /*      % Nominal gain */
    /*      Kz = [  2.4538    1.1346 */
    /*              2.4538    1.1346 */
    /*              2.4538    1.1346]; */
    /*   */
    /*      Kiz = [ 2.0412  2.0412  2.0412  2.0412  2.0412  2.0412  ]'; */
    /* '<S22>:1:38' gain = [Kz(1,:) Kiz(1)]; */
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
    /*  ------------------------------ */
    /*  Nominal gain: OK  */
    /*  Kz  = [14.7226 6.8078];  Kiz =  12.2474;   */
    /*  KX0  = [Kz;Kz;Kz;Kz;Kz;Kz]./6;         */
    /*  Ki0  = [Kiz;Kiz;Kiz;Kiz;Kiz;Kiz]./6; */
    /*                                  => gain motor 1  = [2.4538  1.1346  2.0412]   &    gain_z = [14.7226     6.8078   12.2474]    % nominal classique        */
    /*  ------------------------------ */
    /*  evalSurf gain: OK                                  [z        z_dot   z_int]     */
    /*  u = [0 0 0 ]                    => gain motor 1  = [2.5037  1.1657  2.0456]   =>   gain_z = [15.0222    6.9942   12.2736]    % GS nominal     */
    /*  u = [0.5 0.5 0.5 ]              => gain motor 1  = [2.6144  1.3106  1.8709]   =>   gain_z = [15.6864    7.8636   11.2254]    % GS with LOE                           */
    /*  ------------------------------ */
    /*  implementation check  */
    /*  u = [0 0 0 0 0 0]               => gain motor 1  = [2.5037  1.1657  2.1016]   =>   gain_z = [15.0222    6.9942   12.6096]    % GS nominal implementation   */
    /*  u = [0.5 0.5 0.5 0.5 0.5 0.5 ]  => gain motor 1  = [2.6144  1.3106  1.9268]   =>   gain_z = [15.6864    7.8636   11.5608]    % GS with LOE implementation  */
    /*  6*[2.6144  1.3106  1.9268] */
    rtb_d_z = tuning_GS1_U.X[2] - tuning_GS1_U.Y0[2];

    /* Sum: '<S7>/Sum6' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/Y0'
     */
    /* MATLAB Function 'GS_controller/psi_GS_controller/MATLAB Function': '<S18>:1' */
    /*  GS_psi_3gamma_gain2_OK.m */
    /*  to change 1 */
    /* '<S18>:1:4' un = (u - 0.5)./0.5; */
    /*  normalized LOE */
    /*  to change 2 */
    /*      Kpsi0  = [-2.2767   -1.6150]; */
    /*      Kipsi0 = -1.1607; */
    /*   */
    /*      Kpsi_i  = [0.0543   -0.0262]; */
    /*      Kpsi_j  = [0.0554   -0.0301]; */
    /*      Kipsi_i = 0.0966;  */
    /*      Kipsi_j = 0.0905; */
    /*   */
    /*      % [-1 1 -1 1 -1 1] */
    /*      Kpsi = zeros(6,2); Kipsi = zeros(6,1); */
    /*      Kpsi(1,:) =    Kpsi0 + Kpsi_i.*un(1) + Kpsi_j.*un(2) + Kpsi_j.*un(3); */
    /*      Kpsi(2,:) =  -(Kpsi0 + Kpsi_j.*un(1) + Kpsi_i.*un(2) + Kpsi_j.*un(3)); */
    /*      Kpsi(3,:) =    Kpsi0 + Kpsi_j.*un(1) + Kpsi_j.*un(2) + Kpsi_i.*un(3); */
    /*      Kpsi(4,:) =  -(Kpsi0 + Kpsi_i.*un(4) + Kpsi_j.*un(5) + Kpsi_j.*un(6)); */
    /*      Kpsi(5,:) =    Kpsi0 + Kpsi_j.*un(4) + Kpsi_i.*un(5) + Kpsi_j.*un(6); */
    /*      Kpsi(6,:) =  -(Kpsi0 + Kpsi_j.*un(4) + Kpsi_j.*un(5) + Kpsi_i.*un(6)); */
    /*   */
    /*      Kipsi(1) =     Kipsi0 + Kipsi_i.*un(1) + Kipsi_j.*un(2) + Kipsi_j.*un(3); */
    /*      Kipsi(2) =   -(Kipsi0 + Kipsi_j.*un(1) + Kipsi_i.*un(2) + Kipsi_j.*un(3)); */
    /*      Kipsi(3) =     Kipsi0 + Kipsi_j.*un(1) + Kipsi_j.*un(2) + Kipsi_i.*un(3); */
    /*      Kipsi(4) =   -(Kipsi0 + Kipsi_i.*un(4) + Kipsi_j.*un(5) + Kipsi_j.*un(6)); */
    /*      Kipsi(5) =     Kipsi0 + Kipsi_j.*un(4) + Kipsi_i.*un(5) + Kipsi_j.*un(6); */
    /*      Kipsi(6) =   -(Kipsi0 + Kipsi_j.*un(4) + Kipsi_j.*un(5) + Kipsi_i.*un(6)); */
    /* '<S18>:1:30' Kpsi = [-2.2740   -1.4292 */
    /* '<S18>:1:31'              2.2740    1.4292 */
    /* '<S18>:1:32'             -2.2740   -1.4292 */
    /* '<S18>:1:33'              2.2740    1.4292 */
    /* '<S18>:1:34'             -2.2740   -1.4292 */
    /* '<S18>:1:35'              2.2740    1.4292]; */
    /* '<S18>:1:36' Kipsi = [-1.4438  1.4438  -1.4438  1.4438  -1.4438  1.4438]'; */
    /* '<S18>:1:37' gain = [Kpsi(1,:) Kipsi(1)]; */
    /*  KX = */
    /*     -2.2767   -1.6150    0.0543   -0.0262    0.0554   -0.0301    0.0554   -0.0301 */
    /*      2.2767    1.6150   -0.0554    0.0301   -0.0543    0.0262   -0.0554    0.0301 */
    /*     -2.2767   -1.6150    0.0554   -0.0301    0.0554   -0.0301    0.0543   -0.0262 */
    /*      2.4517    1.8414    0.0784    0.1422    0.0784    0.1422    0.0784    0.1422 */
    /*     -2.4517   -1.8414   -0.0784   -0.1422   -0.0784   -0.1422   -0.0784   -0.1422 */
    /*      2.4517    1.8414    0.0784    0.1422    0.0784    0.1422    0.0784    0.1422 */
    /*  */
    /*  Ki = */
    /*     -1.1607    0.0966    0.0905    0.0905 */
    /*      1.1607   -0.0905   -0.0966   -0.0905 */
    /*     -1.1607    0.0905    0.0905    0.0966 */
    /*      1.2250   -0.0423   -0.0423   -0.0423 */
    /*     -1.2250    0.0423    0.0423    0.0423 */
    /*      1.2250   -0.0423   -0.0423   -0.0423 */
    /*  ------------------------------ */
    /*  Nominal gain: OK  */
    /*  Kpsi = [0.498    0.313];   Kipsi = 0.3162 */
    /*  factor = 0.0365 */
    /*  KX0  = 1/6/factor*[-1 1 -1 1 -1 1]'*Kpsi */
    /*  Ki0  = 1/6/factor*[-1 1 -1 1 -1 1]'*Kipsi */
    /*                                  => gain motor 1  = [-2.2740   -1.4292  -1.4438]   &   gain_psi = [0.498     0.3130    0.3162]    % nominal classique        */
    /*  ------------------------------ */
    /*  evalSurf gain: OK                                  [psi     psi_dot   psi_int]     */
    /*  u = [0 0 0 ]                    => gain motor 1  = [-2.4419  -1.5286  -1.4382]   =>   gain_psi = [0.5348    0.3348    0.3150 ]    % GS nominal     */
    /*  u = [0.5 0.5 0.5 ]              => gain motor 1  = [-2.276   -1.6150  -1.1607]   =>   gain_psi = [0.4984    0.3537    0.2542 ]    % GS with LOE                           */
    /*  ------------------------------ */
    /*  implementation check  */
    /*  u = [0 0 0 0 0 0]               => gain motor 1  = [-2.4418  -1.5286  -1.4383]   =>   gain_psi = [ ~ ]    % GS nominal implementation  ~   evalSurf  */
    /*  u = [0.5 0.5 0.5 0.5 0.5 0.5 ]  => gain motor 1  = [-2.2767  -1.6150  -1.1607]   =>   gain_psi = [ ~ ]    % GS with LOE implementation ~   evalSurf  */
    /*  -factor*6*[-2.4418  -1.5286  -1.4383] */
    rtb_d_psi = tuning_GS1_U.X[8] - tuning_GS1_U.Y0[3];

    /* MATLAB Function: '<S14>/MATLAB Function' */
    /* MATLAB Function 'GS_controller/x_GS_controller/MATLAB Function': '<S19>:1' */
    /*  GS_x_pitch_OK.m */
    /*  to change 1 */
    /* '<S19>:1:4' un = (u - 0.4)./0.4; */
    for (i = 0; i < 6; i++) {
      un[i] = (rtb_u[i] - 0.4) / 0.4;
    }

    /*  normalized LOE */
    /*  to change 2 */
    /* '<S19>:1:7' Kxtheta  = zeros(4,4); */
    memset(&rtb_Kxtheta[0], 0, sizeof(real_T) << 4U);

    /* '<S19>:1:8' Kix = zeros(4,1); */
    /*   */
    /* '<S19>:1:10' Kxtheta_i  = [0.0260   -0.0179   -0.0407    0.0011]; */
    /* '<S19>:1:11' Kxtheta_j  = [0.0939   -0.0281   -0.1520   -0.0374]; */
    /* '<S19>:1:12' Kix_i = 0.1062; */
    /* '<S19>:1:13' Kix_j = 0.1651; */
    /*      % [-1 1 1 -1] */
    /* '<S19>:1:16' Kxtheta(1,:) =   Kxtheta(1,:) + Kxtheta_i.*un(1) + Kxtheta_j.*un(2); */
    /* '<S19>:1:17' Kxtheta(2,:) = -(Kxtheta(2,:) + Kxtheta_j.*un(1) + Kxtheta_i.*un(2)); */
    /* '<S19>:1:18' Kxtheta(3,:) = -(Kxtheta(3,:) + Kxtheta_i.*un(3) + Kxtheta_j.*un(4)); */
    /* '<S19>:1:19' Kxtheta(4,:) =   Kxtheta(4,:) + Kxtheta_j.*un(3) + Kxtheta_i.*un(4); */
    rtb_Kxtheta[0] = 0.026 * un[0] + 0.0939 * un[1];
    rtb_Kxtheta[1] = -((0.0939 * un[0] + rtb_Kxtheta[1]) + 0.026 * un[1]);
    rtb_Kxtheta[2] = -((0.026 * un[2] + rtb_Kxtheta[2]) + 0.0939 * un[3]);
    rtb_Kxtheta[3] = (0.0939 * un[2] + rtb_Kxtheta[3]) + 0.026 * un[3];
    rtb_Kxtheta[4] = -0.0179 * un[0] + -0.0281 * un[1];
    rtb_Kxtheta[5] = -((-0.0281 * un[0] + rtb_Kxtheta[5]) + -0.0179 * un[1]);
    rtb_Kxtheta[6] = -((-0.0179 * un[2] + rtb_Kxtheta[6]) + -0.0281 * un[3]);
    rtb_Kxtheta[7] = (-0.0281 * un[2] + rtb_Kxtheta[7]) + -0.0179 * un[3];
    rtb_Kxtheta[8] = -0.0407 * un[0] + -0.152 * un[1];
    rtb_Kxtheta[9] = -((-0.152 * un[0] + rtb_Kxtheta[9]) + -0.0407 * un[1]);
    rtb_Kxtheta[10] = -((-0.0407 * un[2] + rtb_Kxtheta[10]) + -0.152 * un[3]);
    rtb_Kxtheta[11] = (-0.152 * un[2] + rtb_Kxtheta[11]) + -0.0407 * un[3];
    rtb_Kxtheta[12] = 0.0011 * un[0] + -0.0374 * un[1];
    rtb_Kxtheta[13] = -((-0.0374 * un[0] + rtb_Kxtheta[13]) + 0.0011 * un[1]);
    rtb_Kxtheta[14] = -((0.0011 * un[2] + rtb_Kxtheta[14]) + -0.0374 * un[3]);
    rtb_Kxtheta[15] = (-0.0374 * un[2] + rtb_Kxtheta[15]) + 0.0011 * un[3];

    /* '<S19>:1:21' Kix(1,:) =   Kix(1,:) + Kix_i.*un(1) + Kix_j.*un(2); */
    rtb_Kix[0] = 0.1062 * un[0] + 0.1651 * un[1];

    /* '<S19>:1:22' Kix(2,:) = -(Kix(2,:) + Kix_j.*un(1) + Kix_i.*un(2)); */
    rtb_Kix[1] = -(0.1651 * un[0] + 0.1062 * un[1]);

    /* '<S19>:1:23' Kix(3,:) = -(Kix(3,:) + Kix_i.*un(3) + Kix_j.*un(4)); */
    rtb_Kix[2] = -(0.1062 * un[2] + 0.1651 * un[3]);

    /* '<S19>:1:24' Kix(4,:) =   Kix(4,:) + Kix_j.*un(3) + Kix_i.*un(4); */
    rtb_Kix[3] = 0.1651 * un[2] + 0.1062 * un[3];

    /* Sum: '<S7>/Sum1' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/Y0'
     */
    /* '<S19>:1:26' gain = [-1.7167  -1.0582  -1.2273] + [Kxtheta(1,1:2) Kix(1)]; */
    /*   */
    /*  KX = */
    /*     -1.7167   -1.0582   -3.6042   -0.7094    0.0260   -0.0179   -0.0407    0.0011    0.0939   -0.0281   -0.1520   -0.0374 */
    /*      1.7185    1.0547    3.5986    0.7090   -0.0912    0.0228    0.1437    0.0367   -0.0270    0.0157    0.0835   -0.0026 */
    /*      1.7219    1.1497    4.1815    0.8496   -0.0318    0.0304    0.3428    0.1170   -0.0362    0.0392    0.3567    0.1182 */
    /*     -1.7219   -1.1497   -4.1815   -0.8496    0.0318   -0.0304   -0.3428   -0.1170    0.0362   -0.0392   -0.3567   -0.1182 */
    /*  */
    /*  Ki = */
    /*     -1.2273    0.1062    0.1651 */
    /*      1.2364   -0.1515   -0.1850 */
    /*      1.1313   -0.0551   -0.0778 */
    /*     -1.1313    0.0551    0.0778 */
    /*  ------------------------------ */
    /*  Nominal gain: OK  */
    /*  K_x_SFint    = [1.2426   0.7085];    Ki_x_SFint   =  0.9913;    K_pitch_SF  = [2.2946   0.4589];  */
    /*  %              [  x          xd    theta    the_dot  integral_x] */
    /*  gain_x_theta = [1.2426   0.7085    2.2946   0.4589   0.9913] */
    /*   */
    /*  arm   = 0.215; */
    /*  KX0 = 3^(1/2)/(6*arm)*[-1 1 1 -1]'*[K_x_SFint K_pitch_SF] */
    /*  Ki0 = 3^(1/2)/(6*arm)*[-1 1 1 -1]'*Ki_x_SFint */
    /*                              => gain motor 1 = [-1.6684   -0.9513   -3.0809   -0.6162  -1.3310]   &   gain_x_theta = [1.2426   0.7085   2.2946   0.4589   0.9913]    % nominal classique        */
    /*  ------------------------------ */
    /*  evalSurf gain: OK                             [  x         xd       theta    the_dot  integral_x]      */
    /*  u = [0 0 ]                  => gain motor 1 = [-1.8366   -1.0123   -3.4114   -0.6731  -1.4986]    => gain_x_theta = [1.3679   0.7539   2.5407   0.5013   1.1161 ]    % GS nominal */
    /*  u = [0.5 0.5]               => gain motor 1 = [-1.6868   -1.0697   -3.6523   -0.7185  -1.1595]    => gain_x_theta = [1.2563   0.7967   2.7202   0.5351   0.8636 ]    % GS with LOE */
    /*  ------------------------------ */
    /*  implementation check  */
    /*  u = [0 0 0 0]               => gain motor 1 = [-1.8366   -1.0122   -3.4115   -0.6731  -1.4986]    => gain_x_theta = [1.3679   0.7539   2.5408   0.5013   1.1161 ]    % GS nominal implementation */
    /*  u = [0.5 0.5 0.5 0.5]       => gain motor 1 = [-1.6867   -1.0697   -3.6524   -0.7185  -1.1595]    => gain_x_theta = [1.2562   0.7967   2.7202   0.5351   0.8636 ]    % GS with LOE implementation */
    /*  */
    /*  ll      = [-1.7167   -1.0582   -3.6042   -0.7094] */
    /*  Kxtheta =   [ll; -ll; -ll; ll]+ Kxtheta   */
    /*  Kix     = [-1.2273 1.2273 1.2273 -1.2273]' + Kix */
    /*  -(6*arm/sqrt(3)).*[-1.7167   -1.0582   -3.6042   -0.7094  -1.2273] */
    /*  =============> [x xd the the_d x_int] = [1.2786   0.7881  2.6843  0.5283  0.9141]  =========> dynamic reconfigure */
    rtb_d_x = tuning_GS1_U.X[0] - tuning_GS1_U.Y0[0];

    /* Sum: '<S14>/Sum1' incorporates:
     *  Inport: '<Root>/X'
     *  Integrator: '<S14>/Integrator1'
     *  Product: '<S14>/Product'
     *  Product: '<S14>/Product1'
     *  SignalConversion: '<S14>/TmpSignal ConversionAtProduct1Inport2'
     */
    for (i = 0; i < 4; i++) {
      rtb_ref[i] = rtb_Kix[i] * tuning_GS1_X.Integrator1_CSTATE_b -
        (((rtb_Kxtheta[i + 4] * tuning_GS1_U.X[3] + rtb_Kxtheta[i] * rtb_d_x) +
          rtb_Kxtheta[i + 8] * tuning_GS1_U.X[7]) + rtb_Kxtheta[i + 12] *
         tuning_GS1_U.X[10]);
    }

    /* End of Sum: '<S14>/Sum1' */

    /* MATLAB Function: '<S15>/MATLAB Function' */
    /* MATLAB Function 'GS_controller/y_GS_controller/MATLAB Function': '<S20>:1' */
    /*  to change 1 */
    /* '<S20>:1:4' un = (u - 0.375)./0.375; */
    for (i = 0; i < 6; i++) {
      rtb_u[i] = (rtb_u[i] - 0.375) / 0.375;
    }

    /*  normalized LOE */
    /*  to change 2 */
    /* '<S20>:1:7' Kyphi  = zeros(6,4); */
    memset(&rtb_Kyphi[0], 0, 24U * sizeof(real_T));

    /* '<S20>:1:8' Kiy    = zeros(6,1); */
    /*   */
    /*     %%  GS_y_3gamma_OK.m */
    /*      Kyphi_i  = [0.0500    0.0327   -0.0649   -0.0583]; */
    /*      Kyphi_j  = [-0.0406  -0.0468    0.1455    0.0252];          % attention */
    /*      Kiy_i = 0.0094;  */
    /*      Kiy_j = 0.0485; */
    /*     %% GS_y_3gamma_OK2.m */
    /* '<S20>:1:17' Kyphi_i  = [-0.0102   -0.0051    0.0091    0.0038]; */
    /* '<S20>:1:18' Kyphi_j  = [0.0060   -0.0063    0.0279    0.0113]; */
    /*  attention */
    /* '<S20>:1:19' Kiy_i = -0.0351; */
    /* '<S20>:1:20' Kiy_j = -0.0314; */
    /*     %%  */
    /*  [1 2 1 -1 -2 -1] */
    /* '<S20>:1:23' Kyphi(1,:) =      Kyphi(1,:) + Kyphi_i.*un(1) + Kyphi_j.*un(2) + Kyphi_j.*un(3); */
    /* '<S20>:1:24' Kyphi(2,:) =  2.*(Kyphi(2,:) + Kyphi_j.*un(1) + Kyphi_i.*un(2) + Kyphi_j.*un(3)); */
    /* '<S20>:1:25' Kyphi(3,:) =      Kyphi(3,:) + Kyphi_j.*un(1) + Kyphi_j.*un(2) + Kyphi_i.*un(3); */
    /* '<S20>:1:26' Kyphi(4,:) =    -(Kyphi(4,:) + Kyphi_i.*un(4) + Kyphi_j.*un(5) + Kyphi_j.*un(6)); */
    /* '<S20>:1:27' Kyphi(5,:) = -2.*(Kyphi(5,:) + Kyphi_j.*un(4) + Kyphi_i.*un(5) + Kyphi_j.*un(6)); */
    /* '<S20>:1:28' Kyphi(6,:) =    -(Kyphi(6,:) + Kyphi_j.*un(4) + Kyphi_j.*un(5) + Kyphi_i.*un(6)); */
    rtb_Kyphi[0] = (-0.0102 * rtb_u[0] + 0.006 * rtb_u[1]) + 0.006 * rtb_u[2];
    rtb_Kyphi[1] = (((0.006 * rtb_u[0] + rtb_Kyphi[1]) + -0.0102 * rtb_u[1]) +
                    0.006 * rtb_u[2]) * 2.0;
    rtb_Kyphi[2] = ((0.006 * rtb_u[0] + rtb_Kyphi[2]) + 0.006 * rtb_u[1]) +
      -0.0102 * rtb_u[2];
    rtb_Kyphi[3] = -(((-0.0102 * rtb_u[3] + rtb_Kyphi[3]) + 0.006 * rtb_u[4]) +
                     0.006 * rtb_u[5]);
    rtb_Kyphi[4] = (((0.006 * rtb_u[3] + rtb_Kyphi[4]) + -0.0102 * rtb_u[4]) +
                    0.006 * rtb_u[5]) * -2.0;
    rtb_Kyphi[5] = -(((0.006 * rtb_u[3] + rtb_Kyphi[5]) + 0.006 * rtb_u[4]) +
                     -0.0102 * rtb_u[5]);
    rtb_Kyphi[6] = (-0.0051 * rtb_u[0] + -0.0063 * rtb_u[1]) + -0.0063 * rtb_u[2];
    rtb_Kyphi[7] = (((-0.0063 * rtb_u[0] + rtb_Kyphi[7]) + -0.0051 * rtb_u[1]) +
                    -0.0063 * rtb_u[2]) * 2.0;
    rtb_Kyphi[8] = ((-0.0063 * rtb_u[0] + rtb_Kyphi[8]) + -0.0063 * rtb_u[1]) +
      -0.0051 * rtb_u[2];
    rtb_Kyphi[9] = -(((-0.0051 * rtb_u[3] + rtb_Kyphi[9]) + -0.0063 * rtb_u[4])
                     + -0.0063 * rtb_u[5]);
    rtb_Kyphi[10] = (((-0.0063 * rtb_u[3] + rtb_Kyphi[10]) + -0.0051 * rtb_u[4])
                     + -0.0063 * rtb_u[5]) * -2.0;
    rtb_Kyphi[11] = -(((-0.0063 * rtb_u[3] + rtb_Kyphi[11]) + -0.0063 * rtb_u[4])
                      + -0.0051 * rtb_u[5]);
    rtb_Kyphi[12] = (0.0091 * rtb_u[0] + 0.0279 * rtb_u[1]) + 0.0279 * rtb_u[2];
    rtb_Kyphi[13] = (((0.0279 * rtb_u[0] + rtb_Kyphi[13]) + 0.0091 * rtb_u[1]) +
                     0.0279 * rtb_u[2]) * 2.0;
    rtb_Kyphi[14] = ((0.0279 * rtb_u[0] + rtb_Kyphi[14]) + 0.0279 * rtb_u[1]) +
      0.0091 * rtb_u[2];
    rtb_Kyphi[15] = -(((0.0091 * rtb_u[3] + rtb_Kyphi[15]) + 0.0279 * rtb_u[4])
                      + 0.0279 * rtb_u[5]);
    rtb_Kyphi[16] = (((0.0279 * rtb_u[3] + rtb_Kyphi[16]) + 0.0091 * rtb_u[4]) +
                     0.0279 * rtb_u[5]) * -2.0;
    rtb_Kyphi[17] = -(((0.0279 * rtb_u[3] + rtb_Kyphi[17]) + 0.0279 * rtb_u[4])
                      + 0.0091 * rtb_u[5]);
    rtb_Kyphi[18] = (0.0038 * rtb_u[0] + 0.0113 * rtb_u[1]) + 0.0113 * rtb_u[2];
    rtb_Kyphi[19] = (((0.0113 * rtb_u[0] + rtb_Kyphi[19]) + 0.0038 * rtb_u[1]) +
                     0.0113 * rtb_u[2]) * 2.0;
    rtb_Kyphi[20] = ((0.0113 * rtb_u[0] + rtb_Kyphi[20]) + 0.0113 * rtb_u[1]) +
      0.0038 * rtb_u[2];
    rtb_Kyphi[21] = -(((0.0038 * rtb_u[3] + rtb_Kyphi[21]) + 0.0113 * rtb_u[4])
                      + 0.0113 * rtb_u[5]);
    rtb_Kyphi[22] = (((0.0113 * rtb_u[3] + rtb_Kyphi[22]) + 0.0038 * rtb_u[4]) +
                     0.0113 * rtb_u[5]) * -2.0;
    rtb_Kyphi[23] = -(((0.0113 * rtb_u[3] + rtb_Kyphi[23]) + 0.0113 * rtb_u[4])
                      + 0.0038 * rtb_u[5]);

    /* '<S20>:1:30' Kiy(1) =     Kiy(1) + Kiy_i.*un(1) + Kiy_j.*un(2) + Kiy_j.*un(3); */
    rtb_Kiy[0] = (-0.0351 * rtb_u[0] + -0.0314 * rtb_u[1]) + -0.0314 * rtb_u[2];

    /* '<S20>:1:31' Kiy(2) =  2*(Kiy(2) + Kiy_j.*un(1) + Kiy_i.*un(2) + Kiy_j.*un(3)); */
    rtb_Kiy[1] = ((-0.0314 * rtb_u[0] + -0.0351 * rtb_u[1]) + -0.0314 * rtb_u[2])
      * 2.0;

    /* '<S20>:1:32' Kiy(3) =     Kiy(3) + Kiy_j.*un(1) + Kiy_j.*un(2) + Kiy_i.*un(3); */
    rtb_Kiy[2] = (-0.0314 * rtb_u[0] + -0.0314 * rtb_u[1]) + -0.0351 * rtb_u[2];

    /* '<S20>:1:33' Kiy(4) =   -(Kiy(4) + Kiy_i.*un(4) + Kiy_j.*un(5) + Kiy_j.*un(6)); */
    rtb_Kiy[3] = -((-0.0351 * rtb_u[3] + -0.0314 * rtb_u[4]) + -0.0314 * rtb_u[5]);

    /* '<S20>:1:34' Kiy(5) = -2*(Kiy(5) + Kiy_j.*un(4) + Kiy_i.*un(5) + Kiy_j.*un(6)); */
    rtb_Kiy[4] = ((-0.0314 * rtb_u[3] + -0.0351 * rtb_u[4]) + -0.0314 * rtb_u[5])
      * -2.0;

    /* '<S20>:1:35' Kiy(6) =   -(Kiy(6) + Kiy_j.*un(4) + Kiy_j.*un(5) + Kiy_i.*un(6)); */
    rtb_Kiy[5] = -((-0.0314 * rtb_u[3] + -0.0314 * rtb_u[4]) + -0.0351 * rtb_u[5]);

    /* Sum: '<S7>/Sum4' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/Y0'
     */
    /* '<S20>:1:37' gain = [-0.7177   -0.4473   -0.5164] + [Kyphi(1,1:2) Kiy(1)]; */
    /*  Ky, Kyd, Kintegral */
    /*  GS_y_3gamma_OK2.m */
    /*  KX =    */
    /*     -0.7177   -0.4473    1.5543    0.3168   -0.0102   -0.0051    0.0091    0.0038    0.0009   -0.0052    0.0471    0.0209    0.0060  -0.0064    0.0278    0.0113 */
    /*     -1.4643   -0.8936    3.0410    0.6040   -0.0483   -0.0088   -0.0184   -0.0074   -0.1145   -0.0304    0.0189   -0.0198   -0.0483  -0.0087   -0.0185   -0.0076 */
    /*     -0.7177   -0.4473    1.5543    0.3168    0.0060   -0.0063    0.0279    0.0113    0.0009   -0.0051    0.0471    0.0209   -0.0102  -0.0050    0.0091    0.0036 */
    /*     -0.7544   -0.4915    1.7728    0.3588   -0.1001   -0.0530    0.1571    0.0227   -0.0576   -0.0544    0.2471    0.0621   -0.1002  -0.0531    0.1569    0.0227 */
    /*     -1.5089   -0.9829    3.5456    0.7176   -0.2003   -0.1061    0.3141    0.0455   -0.1152   -0.1087    0.4943    0.1242   -0.2004  -0.1062    0.3138    0.0454 */
    /*     -0.7544   -0.4915    1.7728    0.3588   -0.1001   -0.0530    0.1571    0.0227   -0.0576   -0.0544    0.2471    0.0621   -0.1002  -0.0531    0.1569    0.0227 */
    /*  ----------------------------------- */
    /*  Ki = */
    /*     -0.5164   -0.0351   -0.0155   -0.0314 */
    /*     -1.0621   -0.0769   -0.0214   -0.0770 */
    /*     -0.5164   -0.0313   -0.0155   -0.0352 */
    /*     -0.5253   -0.0610   -0.0277   -0.0611 */
    /*     -1.0505   -0.1219   -0.0555   -0.1221 */
    /*     -0.5253   -0.0610   -0.0277   -0.0611 */
    /*  ------------------------------ */
    /*  Nominal gain: OK  */
    /*  K_y_SFint  = [-0.9479   -0.5505];    Ki_y_SFint   =  -0.7657;     K_roll_SF  = [1.7378    0.3476];  */
    /*               [  y          yd       phi    phi_dot  integral_y] */
    /*  gain_Y_phi = [-0.9479   -0.5505    1.7378    0.3476   -0.7657] */
    /*  arm = 0.215 */
    /*  KX0 = 1/(6*arm)*[1 2 1 1 2 1]'*[K_y_SFint K_roll_SF]                                                    % !!!! not -1 -2 -1 => for better tuning */
    /*  Ki0 = 1/(6*arm)*[1 2 1 1 2 1]'*Ki_y_SFint */
    /*                                   gain motor 1 = [-0.7348   -0.4267    1.3471     0.2695   -0.5936]   &   gain_Y_phi = [-0.9479   -0.5505    1.7378    0.3476   -0.7657]    % nominal classique        */
    /*  ------------------------------ */
    /*  evalSurf gain: OK                               [  y          yd       phi    phi_dot  integral_y] */
    /*  u = [0 0 0]                   => gain motor 1 = [-0.7144   -0.4306   1.4702    0.2807     -0.4345]    => gain_Y_phi = [-0.9216   -0.5555    1.8966    0.3621   -0.5605]    % GS nominal        */
    /*  u = [0.5 0.5 0.5]             => gain motor 1 = [-0.7188   -0.4529   1.5823    0.3288     -0.5438]    => gain_Y_phi = [-0.9273   -0.5842    2.0412    0.4242   -0.7015]    % GS with LOE */
    /*  ------------------------------ */
    /*  implementation check  */
    /*  u = [0 0 0 0 0 0]             => gain motor 1 = [-0.7195   -0.4296    1.4894    0.2904    -0.4185]    => gain_Y_phi = [-0.9282   -0.5542    1.9213    0.3746   -0.5399]    % GS nominal implementation               */
    /*  u = [0.5 0.5 0.5 0.5 0.5 0.5] => gain motor 1 = [-0.7171   -0.4532    1.5759    0.3256    -0.5490]    => gain_Y_phi = [-0.9251   -0.5846    2.0329    0.4200   -0.7082]    % GS with LOE implementation   */
    /*  implementation check: old */
    /*  */
    /*  k0    = [-0.7177   -0.4473    1.5543    0.3168 ] */
    /*  Kyphi =   [k0; 2*k0; k0; -k0; -2*k0;-k0]+ Kyphi%  */
    /*  Kiy   = [-0.5164 2*(-0.5164) -0.5164 0.5164 2*0.5164 0.5164]' + Kiy */
    /*  (6*arm)*[-0.7177   -0.4473    1.5543    0.3168  -0.5164] */
    /*  !============! [y yd phi phid y_int] = [-0.9258   -0.5770    2.0050    0.4087   -0.6662]  !=========> dynamic reconfigure */
    rtb_d_y = tuning_GS1_U.X[1] - tuning_GS1_U.Y0[1];

    /* Sum: '<S68>/Sum2' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/gain'
     *  Integrator: '<S68>/Integrator1'
     *  Product: '<S68>/Product2'
     *  Product: '<S68>/Product3'
     *  SignalConversion: '<S68>/TmpSignal ConversionAtProduct3Inport2'
     */
    tuning_GS1_B.Sum2 = tuning_GS1_U.gain[2] * tuning_GS1_X.Integrator1_CSTATE_p
      - (tuning_GS1_U.gain[0] * rtb_d_x + tuning_GS1_U.gain[1] * tuning_GS1_U.X
         [3]);

    /* Sum: '<S68>/Sum3' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/gain'
     *  Integrator: '<S68>/Integrator'
     *  Product: '<S68>/Product1'
     *  Product: '<S68>/Product4'
     *  SignalConversion: '<S68>/TmpSignal ConversionAtProduct1Inport2'
     */
    tuning_GS1_B.Sum3 = tuning_GS1_U.gain[5] * tuning_GS1_X.Integrator_CSTATE -
      (tuning_GS1_U.gain[3] * rtb_d_y + tuning_GS1_U.gain[4] * tuning_GS1_U.X[4]);

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
    /* MATLAB Function 'Test_config_and_data/FFW': '<S71>:1' */
    /* '<S71>:1:2' ff = [0;0]; */
    rtb_ff_idx_0 = 0.0;
    rtb_ff_idx_1 = 0.0;

    /* '<S71>:1:3' g = 9.81; */
    /*  [x;y] = [cos(t); sin(t)] */
    /* '<S71>:1:5' if (test_mode == 2) */
    if ((tuning_GS1_U.mode == 2.0) && ((rtb_Clock >= 10.0) && (rtb_Clock <= 50.0)))
    {
      /* '<S71>:1:6' if (t >=10) && (t<= 50) */
      /* '<S71>:1:7' axref_N = -cos(t); */
      /* '<S71>:1:8' ayref_N = -sin(t); */
      /* '<S71>:1:10' axref_b = cos(X(8))*cos(X(9))*axref_N + cos(X(8))*sin(X(9))*ayref_N; */
      /* '<S71>:1:11' ayref_b = (sin(X(7))*sin(X(8))*cos(X(9)) - cos(X(7))*sin(X(9)))*axref_N + (sin(X(7))*sin(X(8))*sin(X(9)) + cos(X(7))*cos(X(9)))*ayref_N; */
      /*  azref_b = (cos(X(7))*sin(X(8))*cos(X(9)) + sin(X(7))*sin(X(9)))*axref_N + (cos(X(7))*sin(X(8))*sin(X(9)) - sin(X(7))*cos(X(9)))*ayref_N; */
      /*   */
      /* '<S71>:1:14' ff = [-ayref_b/g; axref_b/g]; */
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
      /* '<S71>:1:15' else */
      /* '<S71>:1:16' ff = [0;0]; */
    }

    /* End of MATLAB Function: '<S7>/FFW' */
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
       *  Integrator: '<S17>/Integrator1'
       *  Product: '<S17>/Product'
       *  Product: '<S17>/Product1'
       *  SignalConversion: '<S17>/TmpSignal ConversionAtProduct1Inport2'
       *  Sum: '<S17>/Sum1'
       */
      un[i] = (rtb_gamma_m[i] * tuning_GS1_X.Integrator1_CSTATE - (rtb_Kz[i + 6]
                * tuning_GS1_U.X[5] + rtb_Kz[i] * rtb_d_z)) + 2.5179000000000005;

      /* Sum: '<S13>/Sum1' incorporates:
       *  Inport: '<Root>/X'
       *  Integrator: '<S13>/Integrator1'
       *  MATLAB Function: '<S13>/MATLAB Function'
       *  Product: '<S13>/Product'
       *  SignalConversion: '<S13>/TmpSignal ConversionAtProduct1Inport2'
       *  Sum: '<S4>/Sum'
       */
      tmp_1[i] = tmp[i] * tuning_GS1_X.Integrator1_CSTATE_o - (tmp_0[i + 6] *
        tuning_GS1_U.X[11] + tmp_0[i] * rtb_d_psi);
    }

    /* Gain: '<S4>/Gain' incorporates:
     *  Constant: '<S14>/Constant'
     *  Sum: '<S4>/Sum'
     */
    tmp_2[0] = 0.0 * rtb_ref[0];
    tmp_2[1] = 0.0;
    tmp_2[4] = 0.0;
    tmp_2[5] = 0.0 * rtb_ref[3];
    tmp_2[2] = 0.0 * rtb_ref[1];
    tmp_2[3] = 0.0 * rtb_ref[2];

    /* Saturate: '<S6>/2Nm ' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/gain'
     *  Product: '<S70>/Product'
     *  SignalConversion: '<S70>/TmpSignal ConversionAtProductInport2'
     *  Sum: '<S6>/Sum7'
     *  Sum: '<S70>/Sum1'
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

    /* End of Saturate: '<S6>/2Nm ' */

    /* Saturate: '<S6>/2Nm' incorporates:
     *  Inport: '<Root>/X'
     *  Inport: '<Root>/gain'
     *  Product: '<S69>/Product'
     *  SignalConversion: '<S69>/TmpSignal ConversionAtProductInport2'
     *  Sum: '<S69>/Sum1'
     *  Sum: '<S6>/Sum8'
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
      u0 = ((rtb_Kiy[i] * tuning_GS1_X.Integrator1_CSTATE_d - (((rtb_Kyphi[i + 6]
                * tuning_GS1_U.X[4] + rtb_Kyphi[i] * rtb_d_y) + rtb_Kyphi[i + 12]
               * tuning_GS1_U.X[6]) + rtb_Kyphi[i + 18] * tuning_GS1_U.X[9])) +
            ((un[i] + tmp_1[i]) + tmp_2[i])) +
        (tuning_GS1_ConstP.ControlAllocation_Gain[i + 6] * rtb_ff_idx_1 +
         tuning_GS1_ConstP.ControlAllocation_Gain[i] * rtb_ff_idx_0);
      if (u0 > 8.54858) {
        tuning_GS1_B.u[i] = 8.54858;
      } else if (u0 < 0.0) {
        tuning_GS1_B.u[i] = 0.0;
      } else {
        tuning_GS1_B.u[i] = u0;
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
    rtb_u[0] = (1.0 - rtb_LOE_out[0]) * tuning_GS1_B.u[0];
    rtb_u[1] = (1.0 - rtb_LOE_out[1]) * tuning_GS1_B.u[1];
    rtb_u[2] = (1.0 - rtb_LOE_out[2]) * tuning_GS1_B.u[2];
    rtb_u[3] = (1.0 - rtb_LOE_out[3]) * tuning_GS1_B.u[3];
    rtb_u[4] = (1.0 - rtb_LOE_out[4]) * tuning_GS1_B.u[4];
    rtb_u[5] = (1.0 - rtb_LOE_out[5]) * tuning_GS1_B.u[5];

    /* Outport: '<Root>/motor_command' */
    for (i = 0; i < 6; i++) {
      /* Gain: '<S8>/mapping_0_200' incorporates:
       *  Gain: '<S8>/      '
       *  Gain: '<S8>/rads_to_RPM'
       *  Sqrt: '<S8>/Sqrt1'
       *  Sum: '<S8>/Sum3'
       */
      rtb_ff_idx_0 = (std::sqrt(116978.4923343994 * rtb_u[i]) * 9.5493 - 1250.0)
        * 0.022857142857142857;

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
    /* MATLAB Function 'Test_config_and_data/MATLAB Function': '<S73>:1' */
    /* '<S73>:1:2' ref = Y0; */
    /* '<S73>:1:3' switch test_mode */
    switch ((int32_T)tuning_GS1_U.mode) {
     case 0:
      /* '<S73>:1:4' case 0      % manual test */
      /*  manual test */
      /* '<S73>:1:5' ref = ref_manual; */
      rtb_ref[0] = tuning_GS1_U.ref[0];
      rtb_ref[1] = tuning_GS1_U.ref[1];
      rtb_ref[2] = tuning_GS1_U.ref[2];
      rtb_ref[3] = tuning_GS1_U.ref[3];
      break;

     case 1:
      /* '<S73>:1:6' case 1      % waypoint */
      /*  waypoint */
      /* '<S73>:1:7' if t<=15 */
      if (rtb_Clock <= 15.0) {
        /* '<S73>:1:8' ref = [Y0(1); Y0(2); 1; Y0(4)]; */
        rtb_ref[0] = tuning_GS1_U.Y0[0];
        rtb_ref[1] = tuning_GS1_U.Y0[1];
        rtb_ref[2] = 1.0;
        rtb_ref[3] = tuning_GS1_U.Y0[3];
      } else if (rtb_Clock <= 25.0) {
        /* '<S73>:1:9' elseif t <= 25 */
        /* '<S73>:1:10' ref = [Y0(1)+1; Y0(2)-1; 1; Y0(4)]; */
        rtb_ref[0] = tuning_GS1_U.Y0[0] + 1.0;
        rtb_ref[1] = tuning_GS1_U.Y0[1] - 1.0;
        rtb_ref[2] = 1.0;
        rtb_ref[3] = tuning_GS1_U.Y0[3];
      } else if (rtb_Clock <= 35.0) {
        /* '<S73>:1:11' elseif t <=35 */
        /* '<S73>:1:12' ref = [Y0(1)-1; Y0(2)+1; 1; Y0(4)]; */
        rtb_ref[0] = tuning_GS1_U.Y0[0] - 1.0;
        rtb_ref[1] = tuning_GS1_U.Y0[1] + 1.0;
        rtb_ref[2] = 1.0;
        rtb_ref[3] = tuning_GS1_U.Y0[3];
      } else if (rtb_Clock <= 45.0) {
        /* '<S73>:1:13' elseif t <=45 */
        /* '<S73>:1:14' ref = [Y0(1)-1; Y0(2)+1; 1; Y0(4)]; */
        rtb_ref[0] = tuning_GS1_U.Y0[0] - 1.0;
        rtb_ref[1] = tuning_GS1_U.Y0[1] + 1.0;
        rtb_ref[2] = 1.0;
        rtb_ref[3] = tuning_GS1_U.Y0[3];
      } else if (rtb_Clock <= 55.0) {
        /* '<S73>:1:15' elseif t <=55 */
        /* '<S73>:1:16' ref = [Y0(1); Y0(2); 1; Y0(4)]; */
        rtb_ref[0] = tuning_GS1_U.Y0[0];
        rtb_ref[1] = tuning_GS1_U.Y0[1];
        rtb_ref[2] = 1.0;
        rtb_ref[3] = tuning_GS1_U.Y0[3];
      } else {
        /* '<S73>:1:17' else */
        /* '<S73>:1:18' ref = Y0; */
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
      /* '<S73>:1:31' case 2      % circular tracking */
      /*  circular tracking */
      /* '<S73>:1:32' if t<=10 */
      if (rtb_Clock <= 10.0) {
        /* '<S73>:1:33' ref = [Y0(1); Y0(2); 0.75; Y0(4)]; */
        rtb_ref[0] = tuning_GS1_U.Y0[0];
        rtb_ref[1] = tuning_GS1_U.Y0[1];
        rtb_ref[2] = 0.75;
        rtb_ref[3] = tuning_GS1_U.Y0[3];
      } else if (rtb_Clock <= 50.0) {
        /* '<S73>:1:34' elseif t <= 50 */
        /* '<S73>:1:35' ref = [Y0(1)+cos(t); Y0(2)+sin(t); 0.75; Y0(4)]; */
        rtb_ref[0] = tuning_GS1_U.Y0[0] + std::cos(rtb_Clock);
        rtb_ref[1] = tuning_GS1_U.Y0[1] + std::sin(rtb_Clock);
        rtb_ref[2] = 0.75;
        rtb_ref[3] = tuning_GS1_U.Y0[3];
      } else if (rtb_Clock <= 60.0) {
        /* '<S73>:1:36' elseif t <= 60 */
        /* '<S73>:1:37' ref = [Y0(1); Y0(2); 0.75; Y0(4)]; */
        rtb_ref[0] = tuning_GS1_U.Y0[0];
        rtb_ref[1] = tuning_GS1_U.Y0[1];
        rtb_ref[2] = 0.75;
        rtb_ref[3] = tuning_GS1_U.Y0[3];
      } else {
        /* '<S73>:1:38' else */
        /* '<S73>:1:39' ref = Y0; */
        rtb_ref[0] = tuning_GS1_U.Y0[0];
        rtb_ref[1] = tuning_GS1_U.Y0[1];
        rtb_ref[2] = tuning_GS1_U.Y0[2];
        rtb_ref[3] = tuning_GS1_U.Y0[3];
      }

      /*          ref = [cos(t); sin(t);min(t,15);Y0(4)]; */
      break;

     default:
      /* '<S73>:1:42' otherwise */
      /* '<S73>:1:43' ref = Y0; */
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
      tuning_GS1_Y.thrust_after[i] = rtb_u[i];
    }

    if (rtmIsMajorTimeStep((&tuning_GS1_M)) &&
        (&tuning_GS1_M)->Timing.TaskCounters.TID[1] == 0) {
      /* Outport: '<Root>/acc_Kalman' */
      tuning_GS1_Y.acc_Kalman[0] = rtb_Add_a[3];

      /* Outport: '<Root>/M_Kalman' */
      tuning_GS1_Y.M_Kalman[0] = rtb_Sum1_cy[0];

      /* Outport: '<Root>/vel_Kalman' */
      tuning_GS1_Y.vel_Kalman[0] = rtb_Add_a[0];

      /* Outport: '<Root>/acc_Kalman' */
      tuning_GS1_Y.acc_Kalman[1] = rtb_Add_a[4];

      /* Outport: '<Root>/M_Kalman' */
      tuning_GS1_Y.M_Kalman[1] = rtb_Sum1_cy[1];

      /* Outport: '<Root>/vel_Kalman' */
      tuning_GS1_Y.vel_Kalman[1] = rtb_Add_a[1];

      /* Outport: '<Root>/acc_Kalman' */
      tuning_GS1_Y.acc_Kalman[2] = rtb_Add_a[5];

      /* Outport: '<Root>/M_Kalman' */
      tuning_GS1_Y.M_Kalman[2] = rtb_Sum1_cy[2];

      /* Outport: '<Root>/vel_Kalman' */
      tuning_GS1_Y.vel_Kalman[2] = rtb_Add_a[2];
    }

    /* Outport: '<Root>/gain_GS' incorporates:
     *  MATLAB Function: '<S13>/MATLAB Function'
     *  MATLAB Function: '<S14>/MATLAB Function'
     *  MATLAB Function: '<S15>/MATLAB Function'
     *  MATLAB Function: '<S17>/MATLAB Function'
     */
    tuning_GS1_Y.gain_GS[0] = rtb_Kz[0];
    tuning_GS1_Y.gain_GS[3] = -2.274;
    tuning_GS1_Y.gain_GS[6] = -1.7167 + rtb_Kxtheta[0];
    tuning_GS1_Y.gain_GS[9] = -0.7177 + rtb_Kyphi[0];
    tuning_GS1_Y.gain_GS[1] = rtb_Kz[6];
    tuning_GS1_Y.gain_GS[4] = -1.4292;
    tuning_GS1_Y.gain_GS[7] = -1.0582 + rtb_Kxtheta[4];
    tuning_GS1_Y.gain_GS[10] = -0.4473 + rtb_Kyphi[6];
    tuning_GS1_Y.gain_GS[2] = rtb_gamma_m[0];
    tuning_GS1_Y.gain_GS[5] = -1.4438;
    tuning_GS1_Y.gain_GS[8] = -1.2273 + rtb_Kix[0];
    tuning_GS1_Y.gain_GS[11] = -0.5164 + rtb_Kiy[0];

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
    tuning_GS1_B.Sum3_f = rtb_Clock - rtb_d_psi;

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
    tuning_GS1_B.Sum3_a = rtb_Clock - rtb_d_x;

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
    tuning_GS1_B.Sum3_i = rtb_Clock - rtb_d_y;

    /* Saturate: '<S17>/z' */
    if (rtb_ref[2] > 1.75) {
      rtb_Clock = 1.75;
    } else if (rtb_ref[2] < 0.0) {
      rtb_Clock = 0.0;
    } else {
      rtb_Clock = rtb_ref[2];
    }

    /* End of Saturate: '<S17>/z' */

    /* Sum: '<S17>/Sum3' */
    tuning_GS1_B.Sum3_d = rtb_Clock - rtb_d_z;
    if (rtmIsMajorTimeStep((&tuning_GS1_M)) &&
        (&tuning_GS1_M)->Timing.TaskCounters.TID[1] == 0) {
      /* Outputs for Enabled SubSystem: '<S41>/MeasurementUpdate' incorporates:
       *  EnablePort: '<S66>/Enable'
       */
      if (rtmIsMajorTimeStep((&tuning_GS1_M)) &&
          (!tuning_GS1_DW.MeasurementUpdate_MODE)) {
        tuning_GS1_DW.MeasurementUpdate_MODE = true;
      }

      if (tuning_GS1_DW.MeasurementUpdate_MODE) {
        for (i = 0; i < 3; i++) {
          /* Product: '<S66>/C[k]*xhat[k|k-1]' incorporates:
           *  Constant: '<S5>/C'
           *  Sum: '<S66>/Add1'
           */
          rtb_Add_f[i] = 0.0;
          for (i_0 = 0; i_0 < 6; i_0++) {
            rtb_Add_f[i] += tuning_GS1_ConstP.C_Value[3 * i_0 + i] *
              rtb_MemoryX[i_0];
          }

          /* End of Product: '<S66>/C[k]*xhat[k|k-1]' */

          /* Sum: '<S66>/Sum' incorporates:
           *  Inport: '<Root>/X'
           *  Product: '<S66>/Product3'
           *  Sum: '<S66>/Add1'
           */
          rtb_Add_f_0[i] = tuning_GS1_U.X[9 + i] - rtb_Add_f[i];
        }

        /* Product: '<S66>/Product3' incorporates:
         *  Constant: '<S23>/KalmanGainL'
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

      /* End of Outputs for SubSystem: '<S41>/MeasurementUpdate' */
      for (i = 0; i < 6; i++) {
        /* Product: '<S41>/A[k]*xhat[k|k-1]' incorporates:
         *  Constant: '<S5>/A'
         *  Sum: '<S41>/Add'
         */
        un[i] = 0.0;
        for (i_0 = 0; i_0 < 6; i_0++) {
          un[i] += tuning_GS1_ConstP.A_Value[6 * i_0 + i] * rtb_MemoryX[i_0];
        }

        /* End of Product: '<S41>/A[k]*xhat[k|k-1]' */

        /* Sum: '<S41>/Add' */
        rtb_Add[i] = un[i] + tuning_GS1_B.Product3[i];
      }
    }

    /* Saturate: '<S68>/x' */
    if (rtb_ref[0] > 2.0) {
      rtb_Clock = 2.0;
    } else if (rtb_ref[0] < -2.0) {
      rtb_Clock = -2.0;
    } else {
      rtb_Clock = rtb_ref[0];
    }

    /* End of Saturate: '<S68>/x' */

    /* Sum: '<S68>/Sum1' */
    tuning_GS1_B.Sum1 = rtb_Clock - rtb_d_x;

    /* Saturate: '<S68>/y' */
    if (rtb_ref[1] > 2.0) {
      rtb_Clock = 2.0;
    } else if (rtb_ref[1] < -2.0) {
      rtb_Clock = -2.0;
    } else {
      rtb_Clock = rtb_ref[1];
    }

    /* End of Saturate: '<S68>/y' */

    /* Sum: '<S68>/Sum4' */
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

  /* Derivatives for Integrator: '<S17>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = tuning_GS1_B.Sum3_d;

  /* Derivatives for Integrator: '<S13>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_o = tuning_GS1_B.Sum3_f;

  /* Derivatives for Integrator: '<S14>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_b = tuning_GS1_B.Sum3_a;

  /* Derivatives for Integrator: '<S15>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_d = tuning_GS1_B.Sum3_i;

  /* Derivatives for Integrator: '<S68>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_p = tuning_GS1_B.Sum1;

  /* Derivatives for Integrator: '<S68>/Integrator' */
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

    /* InitializeConditions for Integrator: '<S17>/Integrator1' */
    tuning_GS1_X.Integrator1_CSTATE = 0.0;

    /* InitializeConditions for Integrator: '<S13>/Integrator1' */
    tuning_GS1_X.Integrator1_CSTATE_o = 0.0;

    /* InitializeConditions for Integrator: '<S14>/Integrator1' */
    tuning_GS1_X.Integrator1_CSTATE_b = 0.0;

    /* InitializeConditions for Integrator: '<S15>/Integrator1' */
    tuning_GS1_X.Integrator1_CSTATE_d = 0.0;

    /* InitializeConditions for Integrator: '<S68>/Integrator1' */
    tuning_GS1_X.Integrator1_CSTATE_p = 0.0;

    /* InitializeConditions for Integrator: '<S68>/Integrator' */
    tuning_GS1_X.Integrator_CSTATE = 0.0;

    /* SystemInitialize for Enabled SubSystem: '<S41>/MeasurementUpdate' */
    /* SystemInitialize for Atomic SubSystem: '<S5>/UseCurrentEstimator' */
    /* SystemInitialize for Enabled SubSystem: '<S46>/Enabled Subsystem' */
    for (i = 0; i < 6; i++) {
      /* InitializeConditions for Memory: '<S3>/Memory' */
      tuning_GS1_DW.Memory_PreviousInput[i] = 2.5179000000000005;

      /* SystemInitialize for Outport: '<S67>/deltax' */
      tuning_GS1_B.Product2[i] = 0.0;

      /* SystemInitialize for Outport: '<S66>/L*(y[k]-yhat[k|k-1])' */
      tuning_GS1_B.Product3[i] = 0.0;
    }

    /* End of SystemInitialize for SubSystem: '<S46>/Enabled Subsystem' */
    /* End of SystemInitialize for SubSystem: '<S5>/UseCurrentEstimator' */
    /* End of SystemInitialize for SubSystem: '<S41>/MeasurementUpdate' */
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
