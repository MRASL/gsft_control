/*
 * gazebo_gs.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "gazebo_gs".
 *
 * Model version              : 1.737
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Tue Feb 20 11:27:16 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Passed (1), Warnings (3), Error (0)
 */

#include "gazebo_gs.h"
#include "gazebo_gs_private.h"

/*
 * This function updates continuous states using the ODE5 fixed-step
 * solver algorithm
 */
void gazebo_gsModelClass::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
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
  gazebo_gs_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE5_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[0]);
  rtsiSetdX(si, f1);
  this->step();
  gazebo_gs_derivatives();

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
  gazebo_gs_derivatives();

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
  gazebo_gs_derivatives();

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
  gazebo_gs_derivatives();

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
  gazebo_gs_derivatives();

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
void gazebo_gsModelClass::step()
{
  static const real_T b[6] = { 0.5, 0.0, 0.0, 0.0, 0.0, 0.0 };

  static const real_T a[24] = { 0.9753, -0.5034, -0.3197, 0.0422, -0.1754,
    -0.3591, -6.265, 2.1242, -2.9661, 0.2031, -5.4769, -0.3866, 6.754, 0.0,
    1.8785, 0.1553, 0.0, -0.1478, 5.963, 0.8175, -0.6746, 0.2232, -2.6684,
    -1.3679 };

  static const real_T b_a[24] = { -9.0539, 1.6726, 5.3507, -6.3659, 7.9829,
    4.3048, 2.3302, 14.9166, 18.6346, -6.9839, 15.1432, 11.2101, -4.6203, 0.0,
    -20.6684, 27.7592, 0.0, -19.5671, 4.5728, -6.5708, -4.6102, 16.6993, -3.856,
    -7.0 };

  real_T x;
  int32_T z;
  real_T rtb_VectorConcatenate[12];
  real_T rtb_Sum1_g;
  real_T rtb_Sum1_c;
  real_T rtb_Sum3_f;
  real_T rtb_T_f[6];
  real_T rtb_gamma_n[6];
  real_T rtb_Clock;
  real_T rtb_Sum2[6];
  int32_T i;
  real_T a_0[24];
  real_T rtb_ref_idx_2;
  real_T tmp;
  if (rtmIsMajorTimeStep((&gazebo_gs_M))) {
    /* set solver stop time */
    if (!((&gazebo_gs_M)->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&(&gazebo_gs_M)->solverInfo, (((&gazebo_gs_M)
        ->Timing.clockTickH0 + 1) * (&gazebo_gs_M)->Timing.stepSize0 *
        4294967296.0));
    } else {
      rtsiSetSolverStopTime(&(&gazebo_gs_M)->solverInfo, (((&gazebo_gs_M)
        ->Timing.clockTick0 + 1) * (&gazebo_gs_M)->Timing.stepSize0 +
        (&gazebo_gs_M)->Timing.clockTickH0 * (&gazebo_gs_M)->Timing.stepSize0 *
        4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep((&gazebo_gs_M))) {
    (&gazebo_gs_M)->Timing.t[0] = rtsiGetT(&(&gazebo_gs_M)->solverInfo);
  }

  /* Clock: '<Root>/Clock' */
  rtb_Clock = (&gazebo_gs_M)->Timing.t[0];

  /* MATLAB Function: '<Root>/FDD' */
  /* MATLAB Function 'FDD': '<S2>:1' */
  /* '<S2>:1:2' gamma_n = [0 0 0 0 0 0]; */
  for (i = 0; i < 6; i++) {
    rtb_gamma_n[i] = 0.0;
  }

  /* '<S2>:1:3' if time >= 20 */
  if (rtb_Clock >= 20.0) {
    /* '<S2>:1:4' gamma_n = [0.5 0 0 0 0 0]; */
    for (i = 0; i < 6; i++) {
      rtb_gamma_n[i] = b[i];
    }
  }

  /* End of MATLAB Function: '<Root>/FDD' */

  /* MATLAB Function: '<Root>/MATLAB Function2' */
  /* MATLAB Function 'MATLAB Function2': '<S4>:1' */
  /*  KK =[0.1667    0.7752   -1.3427   -4.5662    0.0199    0.3126   -0.0071    0.2467   -0.1870    0.1134   -0.0073    0.2432   -0.0664    0.2997   -0.0150    0.2219 */
  /*       0.1667    1.5504   -0.0000    4.5662   -0.0457    0.2752         0    0.0777    0.2479    0.1062         0   -0.0638    0.0011    0.2622         0    0.0210 */
  /*       0.1667    0.7752    1.3427   -4.5662   -0.0568    0.3071    0.0316    0.2265   -0.1470    0.0923    0.0321    0.2293    0.0148    0.2857    0.0184    0.1950 */
  /*       0.1667   -0.7752    1.3427    4.5662    0.1297    0.0924    0.0304   -0.2015   -0.2268   -0.1848    0.0375    0.1765    0.0223    0.0401    0.0253   -0.1498 */
  /*       0.1667   -1.5504    0.0000   -4.5662   -0.0429    0.4751         0    0.2950    0.3457    0.2891         0    0.7243   -0.0316    0.4446         0    0.3619 */
  /*       0.1667   -0.7752   -1.3427    4.5662    0.0878    0.1134   -0.0044   -0.1450   -0.2016   -0.1328    0.0015    0.2248    0.0633    0.0849   -0.0042   -0.0895]; */
  /*  K = KK(:,1:4) + KK(:,5:8)*gamma_n(1) + KK(:,9:12)*gamma_n(2) + KK(:,13:end)*gamma_n(3);   */
  /* '<S4>:1:10' KK = [ 0.1667    0.7752   -1.3427   -4.5662    0.9753   -6.2650    6.7540    5.9630   -9.0539    2.3302   -4.6203    4.5728 */
  /* '<S4>:1:11'        0.1667    1.5504   -0.0000    4.5662   -0.5034    2.1242         0    0.8175    1.6726   14.9166         0   -6.5708 */
  /* '<S4>:1:12'        0.1667    0.7752    1.3427   -4.5662   -0.3197   -2.9661    1.8785   -0.6746    5.3507   18.6346  -20.6684   -4.6102 */
  /* '<S4>:1:13'        0.1667   -0.7752    1.3427    4.5662    0.0422    0.2031    0.1553    0.2232   -6.3659   -6.9839   27.7592   16.6993 */
  /* '<S4>:1:14'        0.1667   -1.5504    0.0000   -4.5662   -0.1754   -5.4769         0   -2.6684    7.9829   15.1432         0   -3.8560 */
  /* '<S4>:1:15'        0.1667   -0.7752   -1.3427    4.5662   -0.3591   -0.3866   -0.1478   -1.3679    4.3048   11.2101  -19.5671   -7]; */
  /* '<S4>:1:16' K = KK(:,5:8)*gamma_n(1) + KK(:,9:12)*gamma_n(1)^2; */
  x = rtb_gamma_n[0] * rtb_gamma_n[0];

  /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn1' incorporates:
   *  Inport: '<Root>/X0'
   */
  /*     */
  rtb_VectorConcatenate[0] = gazebo_gs_U.X0[0];
  rtb_VectorConcatenate[1] = gazebo_gs_U.X0[1];
  rtb_VectorConcatenate[2] = gazebo_gs_U.X0[2];

  /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn2' */
  for (i = 0; i < 5; i++) {
    rtb_VectorConcatenate[i + 3] = 0.0;
  }

  /* End of SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn2' */

  /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn3' incorporates:
   *  Inport: '<Root>/X0'
   */
  rtb_VectorConcatenate[8] = gazebo_gs_U.X0[3];

  /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn4' */
  rtb_VectorConcatenate[9] = 0.0;
  rtb_VectorConcatenate[10] = 0.0;
  rtb_VectorConcatenate[11] = 0.0;

  /* Sum: '<Root>/Sum' incorporates:
   *  Inport: '<Root>/X'
   */
  for (i = 0; i < 12; i++) {
    rtb_VectorConcatenate[i] = gazebo_gs_U.X[i] - rtb_VectorConcatenate[i];
  }

  /* End of Sum: '<Root>/Sum' */

  /* Sum: '<S8>/Sum1' incorporates:
   *  Gain: '<S8>/ '
   *  Gain: '<S8>/                    '
   *  Integrator: '<S8>/Integrator1'
   *  SignalConversion: '<S8>/TmpSignal ConversionAt                    Inport1'
   */
  rtb_Sum1_g = 0.17320508075688992 * gazebo_gs_X.Integrator1_CSTATE_h -
    (0.32349951352987977 * rtb_VectorConcatenate[0] + 0.2732366014912751 *
     rtb_VectorConcatenate[3]);

  /* Sum: '<S9>/Sum1' incorporates:
   *  Gain: '<S9>/  '
   *  Gain: '<S9>/                     '
   *  Integrator: '<S9>/Integrator1'
   *  SignalConversion: '<S9>/TmpSignal ConversionAt                     Inport1'
   */
  rtb_Sum1_c = -0.173205080756885 * gazebo_gs_X.Integrator1_CSTATE_j -
    (-0.31312578517366968 * rtb_VectorConcatenate[1] + -0.25417198201077484 *
     rtb_VectorConcatenate[4]);

  /* Fcn: '<Root>/Fcn1' incorporates:
   *  Inport: '<Root>/X'
   */
  rtb_Sum3_f = rtb_Sum1_c * std::cos(gazebo_gs_U.X[8]) + rtb_Sum1_g * std::sin
    (gazebo_gs_U.X[8]);

  /* Saturate: '<S5>/roll' */
  if (rtb_Sum3_f > 0.52359877559829882) {
    rtb_Sum3_f = 0.52359877559829882;
  } else {
    if (rtb_Sum3_f < -0.52359877559829882) {
      rtb_Sum3_f = -0.52359877559829882;
    }
  }

  /* End of Saturate: '<S5>/roll' */

  /* Sum: '<S5>/Sum1' incorporates:
   *  Gain: '<S5>/                    '
   *  SignalConversion: '<S5>/TmpSignal ConversionAt                    Inport1'
   */
  rtb_Sum3_f -= 1.1365283480217869 * rtb_VectorConcatenate[6] +
    0.28178545108770103 * rtb_VectorConcatenate[9];

  /* Fcn: '<Root>/Fcn' incorporates:
   *  Inport: '<Root>/X'
   */
  rtb_Sum1_g = -rtb_Sum1_c * std::sin(gazebo_gs_U.X[8]) + rtb_Sum1_g * std::cos
    (gazebo_gs_U.X[8]);

  /* SignalConversion: '<Root>/TmpSignal ConversionAt                 Inport1' incorporates:
   *  Gain: '<S10>/  '
   *  Gain: '<S10>/                     '
   *  Integrator: '<S10>/Integrator1'
   *  SignalConversion: '<S10>/TmpSignal ConversionAt                     Inport1'
   *  Sum: '<S10>/Sum1'
   */
  rtb_Sum1_c = 10.000000000000018 * gazebo_gs_X.Integrator1_CSTATE -
    (12.219481695651957 * rtb_VectorConcatenate[2] + 6.215786645518647 *
     rtb_VectorConcatenate[5]);

  /* Sum: '<S7>/Sum1' incorporates:
   *  Saturate: '<S7>/pitch'
   */
  if (rtb_Sum1_g > 0.52359877559829882) {
    rtb_Sum1_g = 0.52359877559829882;
  } else {
    if (rtb_Sum1_g < -0.52359877559829882) {
      rtb_Sum1_g = -0.52359877559829882;
    }
  }

  /* SignalConversion: '<Root>/TmpSignal ConversionAt                 Inport1' incorporates:
   *  Gain: '<S6>/  '
   *  Gain: '<S6>/                     '
   *  Gain: '<S7>/                    '
   *  Integrator: '<S6>/Integrator1'
   *  SignalConversion: '<S6>/TmpSignal ConversionAt                     Inport1'
   *  SignalConversion: '<S7>/TmpSignal ConversionAt                    Inport1'
   *  Sum: '<S6>/Sum1'
   *  Sum: '<S7>/Sum1'
   */
  rtb_ref_idx_2 = rtb_Sum1_g - (1.2859205994736729 * rtb_VectorConcatenate[7] +
    0.34413551249350854 * rtb_VectorConcatenate[10]);
  rtb_Sum1_g = 0.15811388300841925 * gazebo_gs_X.Integrator1_CSTATE_b -
    (0.3035552054947866 * rtb_VectorConcatenate[8] + 0.24395632222527311 *
     rtb_VectorConcatenate[11]);

  /* MATLAB Function: '<Root>/MATLAB Function2' incorporates:
   *  Product: '<Root>/Product3'
   */
  for (i = 0; i < 4; i++) {
    for (z = 0; z < 6; z++) {
      a_0[z + 6 * i] = a[6 * i + z] * rtb_gamma_n[0] + b_a[6 * i + z] * x;
    }
  }

  /* MATLAB Function 'Actuator_Fault': '<S1>:1' */
  /* '<S1>:1:2' T_f = T; */
  for (i = 0; i < 6; i++) {
    /* Product: '<Root>/Product3' incorporates:
     *  SignalConversion: '<Root>/TmpSignal ConversionAt                 Inport1'
     *  Sum: '<Root>/Sum2'
     */
    x = a_0[i + 18] * rtb_Sum1_g + (a_0[i + 12] * rtb_ref_idx_2 + (a_0[i + 6] *
      rtb_Sum3_f + a_0[i] * rtb_Sum1_c));

    /* Gain: '<Root>/                 ' incorporates:
     *  SignalConversion: '<Root>/TmpSignal ConversionAt                 Inport1'
     *  Sum: '<Root>/Sum2'
     */
    tmp = gazebo_gs_ConstP._Gain_m[i + 18] * rtb_Sum1_g +
      (gazebo_gs_ConstP._Gain_m[i + 12] * rtb_ref_idx_2 +
       (gazebo_gs_ConstP._Gain_m[i + 6] * rtb_Sum3_f +
        gazebo_gs_ConstP._Gain_m[i] * rtb_Sum1_c));

    /* Sum: '<Root>/Sum2' */
    x = (x + tmp) + 2.5179000000000005;

    /* MATLAB Function: '<Root>/Actuator_Fault' */
    rtb_T_f[i] = x;

    /* Sum: '<Root>/Sum2' */
    rtb_Sum2[i] = x;
  }

  /* MATLAB Function: '<Root>/Actuator_Fault' */
  /* '<S1>:1:3' if time >= 20 */
  if (rtb_Clock >= 20.0) {
    /* '<S1>:1:4' T1 = T(1)*0.5; */
    /* '<S1>:1:5' T2 = T(2)*1; */
    /* '<S1>:1:6' T3 = T(3)*1; */
    /* '<S1>:1:7' T4 = T(4)*1; */
    /* '<S1>:1:8' T5 = T(5)*1; */
    /* '<S1>:1:9' T6 = T(6)*1; */
    /* '<S1>:1:10' T_f = [T1;T2;T3;T4;T5;T6]; */
    rtb_T_f[0] = rtb_Sum2[0] * 0.5;
    rtb_T_f[1] = rtb_Sum2[1];
    rtb_T_f[2] = rtb_Sum2[2];
    rtb_T_f[3] = rtb_Sum2[3];
    rtb_T_f[4] = rtb_Sum2[4];
    rtb_T_f[5] = rtb_Sum2[5];
  }

  /* Outport: '<Root>/virtual_control' incorporates:
   *  SignalConversion: '<Root>/TmpSignal ConversionAt                 Inport1'
   */
  gazebo_gs_Y.virtual_control[0] = rtb_Sum1_c;
  gazebo_gs_Y.virtual_control[1] = rtb_Sum3_f;
  gazebo_gs_Y.virtual_control[2] = rtb_ref_idx_2;
  gazebo_gs_Y.virtual_control[3] = rtb_Sum1_g;
  for (i = 0; i < 6; i++) {
    /* Saturate: '<Root>/Saturation1' */
    if (rtb_T_f[i] > 8.54858) {
      rtb_Sum1_c = 8.54858;
    } else if (rtb_T_f[i] < 0.0) {
      rtb_Sum1_c = 0.0;
    } else {
      rtb_Sum1_c = rtb_T_f[i];
    }

    /* End of Saturate: '<Root>/Saturation1' */

    /* Sqrt: '<Root>/Sqrt1' incorporates:
     *  Gain: '<Root>/      '
     */
    x = std::sqrt(116978.4923343994 * rtb_Sum1_c);

    /* Gain: '<Root>/rads_to_RPM' */
    rtb_Sum1_c = 9.5493 * x;

    /* Gain: '<Root>/mapping_0_200' incorporates:
     *  Constant: '<Root>/Constant '
     *  Sum: '<Root>/Sum3'
     */
    rtb_Sum3_f = (rtb_Sum1_c - 1250.0) * 0.022857142857142857;

    /* Saturate: '<Root>/Saturation' */
    if (rtb_Sum3_f < 0.0) {
      /* Outport: '<Root>/motor_command' */
      gazebo_gs_Y.motor_command[i] = 0.0;
    } else {
      /* Outport: '<Root>/motor_command' */
      gazebo_gs_Y.motor_command[i] = rtb_Sum3_f;
    }

    /* End of Saturate: '<Root>/Saturation' */

    /* Outport: '<Root>/motor_speed' */
    gazebo_gs_Y.motor_speed[i] = x;

    /* Outport: '<Root>/motor_RPM' */
    gazebo_gs_Y.motor_RPM[i] = rtb_Sum1_c;
  }

  /* MATLAB Function: '<Root>/MATLAB Function' incorporates:
   *  Inport: '<Root>/X0'
   */
  /* MATLAB Function 'MATLAB Function': '<S3>:1' */
  /* '<S3>:1:2' x = X0(1); */
  /* '<S3>:1:2' y = X0(2); */
  /* '<S3>:1:2' z = X0(3); */
  /* '<S3>:1:2' psi = X0(4); */
  /* '<S3>:1:3' if t <= 40 */
  if (rtb_Clock <= 40.0) {
    /* '<S3>:1:4' x = cos(0.4*(t)); */
    x = std::cos(0.4 * rtb_Clock);

    /* '<S3>:1:5' y = sin(0.4*(t)); */
    rtb_Clock = std::sin(0.4 * rtb_Clock);

    /* '<S3>:1:6' z = 1; */
    z = 1;

    /* '<S3>:1:7' psi = X0(4); */
    rtb_Sum1_g = gazebo_gs_U.X0[3];
  } else {
    /* '<S3>:1:8' else */
    /* '<S3>:1:9' x = X0(1); */
    x = gazebo_gs_U.X0[0];

    /* '<S3>:1:10' y = X0(2); */
    rtb_Clock = gazebo_gs_U.X0[1];

    /* '<S3>:1:11' z = 0.0; */
    z = 0;

    /* '<S3>:1:12' psi = X0(4); */
    rtb_Sum1_g = gazebo_gs_U.X0[3];
  }

  /* Outport: '<Root>/ref' incorporates:
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  /* '<S3>:1:14' ref = [x;y;z;psi]; */
  gazebo_gs_Y.ref[0] = x;
  gazebo_gs_Y.ref[1] = rtb_Clock;
  gazebo_gs_Y.ref[2] = z;
  gazebo_gs_Y.ref[3] = rtb_Sum1_g;

  /* Outport: '<Root>/gamma' */
  for (i = 0; i < 6; i++) {
    gazebo_gs_Y.gamma[i] = rtb_gamma_n[i];
  }

  /* End of Outport: '<Root>/gamma' */

  /* Sum: '<Root>/Sum1' incorporates:
   *  Inport: '<Root>/X0'
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  rtb_Sum1_c = x - gazebo_gs_U.X0[0];
  rtb_Clock -= gazebo_gs_U.X0[1];
  rtb_ref_idx_2 = (real_T)z - gazebo_gs_U.X0[2];
  rtb_Sum3_f = rtb_Sum1_g - gazebo_gs_U.X0[3];

  /* Saturate: '<S6>/yaw' */
  if (rtb_Sum3_f > 3.1415926535897931) {
    rtb_Sum3_f = 3.1415926535897931;
  } else {
    if (rtb_Sum3_f < -3.1415926535897931) {
      rtb_Sum3_f = -3.1415926535897931;
    }
  }

  /* End of Saturate: '<S6>/yaw' */

  /* Sum: '<S6>/Sum3' */
  rtb_Sum3_f -= rtb_VectorConcatenate[8];

  /* Saturate: '<S6>/psi_e' */
  if (rtb_Sum3_f > 0.78539816339744828) {
    gazebo_gs_B.psi_e = 0.78539816339744828;
  } else if (rtb_Sum3_f < -0.78539816339744828) {
    gazebo_gs_B.psi_e = -0.78539816339744828;
  } else {
    gazebo_gs_B.psi_e = rtb_Sum3_f;
  }

  /* End of Saturate: '<S6>/psi_e' */

  /* Saturate: '<S8>/x' */
  if (rtb_Sum1_c > 1.0) {
    rtb_Sum1_c = 1.0;
  } else {
    if (rtb_Sum1_c < -1.0) {
      rtb_Sum1_c = -1.0;
    }
  }

  /* End of Saturate: '<S8>/x' */

  /* Sum: '<S8>/Sum3' */
  rtb_Sum3_f = rtb_Sum1_c - rtb_VectorConcatenate[0];

  /* Saturate: '<S8>/xe' */
  if (rtb_Sum3_f > 1.0) {
    gazebo_gs_B.xe = 1.0;
  } else if (rtb_Sum3_f < -1.0) {
    gazebo_gs_B.xe = -1.0;
  } else {
    gazebo_gs_B.xe = rtb_Sum3_f;
  }

  /* End of Saturate: '<S8>/xe' */

  /* Saturate: '<S9>/y' */
  if (rtb_Clock > 1.0) {
    rtb_Clock = 1.0;
  } else {
    if (rtb_Clock < -1.0) {
      rtb_Clock = -1.0;
    }
  }

  /* End of Saturate: '<S9>/y' */

  /* Sum: '<S9>/Sum3' */
  rtb_Sum3_f = rtb_Clock - rtb_VectorConcatenate[1];

  /* Saturate: '<S9>/ye' */
  if (rtb_Sum3_f > 1.0) {
    gazebo_gs_B.ye = 1.0;
  } else if (rtb_Sum3_f < -1.0) {
    gazebo_gs_B.ye = -1.0;
  } else {
    gazebo_gs_B.ye = rtb_Sum3_f;
  }

  /* End of Saturate: '<S9>/ye' */

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
  rtb_Sum3_f = rtb_ref_idx_2 - rtb_VectorConcatenate[2];

  /* Saturate: '<S10>/ze' */
  if (rtb_Sum3_f > 0.5) {
    gazebo_gs_B.ze = 0.5;
  } else if (rtb_Sum3_f < -0.5) {
    gazebo_gs_B.ze = -0.5;
  } else {
    gazebo_gs_B.ze = rtb_Sum3_f;
  }

  /* End of Saturate: '<S10>/ze' */
  if (rtmIsMajorTimeStep((&gazebo_gs_M))) {
    rt_ertODEUpdateContinuousStates(&(&gazebo_gs_M)->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++(&gazebo_gs_M)->Timing.clockTick0)) {
      ++(&gazebo_gs_M)->Timing.clockTickH0;
    }

    (&gazebo_gs_M)->Timing.t[0] = rtsiGetSolverStopTime(&(&gazebo_gs_M)
      ->solverInfo);

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
      (&gazebo_gs_M)->Timing.clockTick1++;
      if (!(&gazebo_gs_M)->Timing.clockTick1) {
        (&gazebo_gs_M)->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void gazebo_gsModelClass::gazebo_gs_derivatives()
{
  XDot_gazebo_gs_T *_rtXdot;
  _rtXdot = ((XDot_gazebo_gs_T *) (&gazebo_gs_M)->derivs);

  /* Derivatives for Integrator: '<S10>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = gazebo_gs_B.ze;

  /* Derivatives for Integrator: '<S8>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_h = gazebo_gs_B.xe;

  /* Derivatives for Integrator: '<S9>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_j = gazebo_gs_B.ye;

  /* Derivatives for Integrator: '<S6>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_b = gazebo_gs_B.psi_e;
}

/* Model initialize function */
void gazebo_gsModelClass::initialize()
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)(&gazebo_gs_M), 0,
                sizeof(RT_MODEL_gazebo_gs_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&(&gazebo_gs_M)->solverInfo, &(&gazebo_gs_M)
                          ->Timing.simTimeStep);
    rtsiSetTPtr(&(&gazebo_gs_M)->solverInfo, &rtmGetTPtr((&gazebo_gs_M)));
    rtsiSetStepSizePtr(&(&gazebo_gs_M)->solverInfo, &(&gazebo_gs_M)
                       ->Timing.stepSize0);
    rtsiSetdXPtr(&(&gazebo_gs_M)->solverInfo, &(&gazebo_gs_M)->derivs);
    rtsiSetContStatesPtr(&(&gazebo_gs_M)->solverInfo, (real_T **) &(&gazebo_gs_M)
                         ->contStates);
    rtsiSetNumContStatesPtr(&(&gazebo_gs_M)->solverInfo, &(&gazebo_gs_M)
      ->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&gazebo_gs_M)->solverInfo, &(&gazebo_gs_M
      )->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&gazebo_gs_M)->solverInfo,
      &(&gazebo_gs_M)->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&gazebo_gs_M)->solverInfo,
      &(&gazebo_gs_M)->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&(&gazebo_gs_M)->solverInfo, (&rtmGetErrorStatus
      ((&gazebo_gs_M))));
    rtsiSetRTModelPtr(&(&gazebo_gs_M)->solverInfo, (&gazebo_gs_M));
  }

  rtsiSetSimTimeStep(&(&gazebo_gs_M)->solverInfo, MAJOR_TIME_STEP);
  (&gazebo_gs_M)->intgData.y = (&gazebo_gs_M)->odeY;
  (&gazebo_gs_M)->intgData.f[0] = (&gazebo_gs_M)->odeF[0];
  (&gazebo_gs_M)->intgData.f[1] = (&gazebo_gs_M)->odeF[1];
  (&gazebo_gs_M)->intgData.f[2] = (&gazebo_gs_M)->odeF[2];
  (&gazebo_gs_M)->intgData.f[3] = (&gazebo_gs_M)->odeF[3];
  (&gazebo_gs_M)->intgData.f[4] = (&gazebo_gs_M)->odeF[4];
  (&gazebo_gs_M)->intgData.f[5] = (&gazebo_gs_M)->odeF[5];
  getRTM()->contStates = ((X_gazebo_gs_T *) &gazebo_gs_X);
  rtsiSetSolverData(&(&gazebo_gs_M)->solverInfo, (void *)&(&gazebo_gs_M)
                    ->intgData);
  rtsiSetSolverName(&(&gazebo_gs_M)->solverInfo,"ode5");
  rtmSetTPtr(getRTM(), &(&gazebo_gs_M)->Timing.tArray[0]);
  (&gazebo_gs_M)->Timing.stepSize0 = 0.005;

  /* block I/O */
  (void) memset(((void *) &gazebo_gs_B), 0,
                sizeof(B_gazebo_gs_T));

  /* states (continuous) */
  {
    (void) memset((void *)&gazebo_gs_X, 0,
                  sizeof(X_gazebo_gs_T));
  }

  /* external inputs */
  (void)memset((void *)&gazebo_gs_U, 0, sizeof(ExtU_gazebo_gs_T));

  /* external outputs */
  (void) memset((void *)&gazebo_gs_Y, 0,
                sizeof(ExtY_gazebo_gs_T));

  /* InitializeConditions for Integrator: '<S10>/Integrator1' */
  gazebo_gs_X.Integrator1_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S8>/Integrator1' */
  gazebo_gs_X.Integrator1_CSTATE_h = 0.0;

  /* InitializeConditions for Integrator: '<S9>/Integrator1' */
  gazebo_gs_X.Integrator1_CSTATE_j = 0.0;

  /* InitializeConditions for Integrator: '<S6>/Integrator1' */
  gazebo_gs_X.Integrator1_CSTATE_b = 0.0;
}

/* Model terminate function */
void gazebo_gsModelClass::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
gazebo_gsModelClass::gazebo_gsModelClass()
{
}

/* Destructor */
gazebo_gsModelClass::~gazebo_gsModelClass()
{
  /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_gazebo_gs_T * gazebo_gsModelClass::getRTM()
{
  return (&gazebo_gs_M);
}
