/*
 * gazebo_gs.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "gazebo_gs".
 *
 * Model version              : 1.912
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Fri Feb 23 00:58:11 2018
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

  {
    real_T (*lastU)[3];
    static const real_T b[6] = { 0.4, 0.3, 0.0, 0.0, 0.0, 0.0 };

    static const real_T a[24] = { -0.04, -0.1022, -0.0671, 0.0802, -0.1026,
      0.0678, 7.4219, 2.3029, -1.3929, 0.594, 5.8128, -9.2485, -3.7475, 0.0,
      1.513, -1.4171, 0.0, 3.2609, 5.6206, 9.2496, 1.5891, -4.9893, 3.8142,
      -5.1257 };

    static const real_T b_a[24] = { -0.1403, 0.0897, -0.2596, -0.0259, 0.0791,
      0.0068, 6.9843, 5.8899, 1.8251, -1.9083, 9.5731, -7.4496, -0.7774, 0.0,
      0.3326, 0.8339, 0.0, 1.8489, 3.897, 8.8995, -0.0334, -5.8534, 4.8865,
      -5.1788 };

    static const real_T c_a[24] = { -0.0755, -0.0486, -0.2776, -0.0171, -0.0476,
      0.1212, 7.2507, 0.798, 7.3404, -1.8501, 4.3847, 1.2453, 9.9725, 0.0,
      13.9626, 0.8749, 0.0, 3.3763, 1.9194, 5.8012, 3.2585, -4.4759, 2.2992,
      -4.5579 };

    static const real_T a_0[9] = { 1.5503875968992249, 3.1007751937984493,
      1.5503875968992249, -2.6853500892540736, -0.0, 2.6853500892540736,
      -9.1324200913242013, 9.1324200913242013, -9.1324200913242013 };

    real_T rtb_ixj;
    real_T rtb_kxi;
    real_T rtb_jxk;
    real_T rtb_Product[3];
    real_T rtb_Sum1[3];
    real_T rtb_Clock;
    real_T rtb_gamma_n[6];
    int32_T i;
    real_T a_1[24];
    int32_T i_0;
    real_T rtb_FMxMyMz_idx_0;
    real_T rtb_Product_idx_2;
    real_T tmp;

    /* Clock: '<Root>/Clock' */
    rtb_Clock = (&gazebo_gs_M)->Timing.t[0];

    /* MATLAB Function: '<Root>/FDD' */
    /* MATLAB Function 'FDD': '<S2>:1' */
    /* '<S2>:1:2' gamma_n = [0 0 0 0 0 0]'; */
    /* '<S2>:1:3' if time <= 10 */
    if (rtb_Clock <= 10.0) {
      /* '<S2>:1:4' gamma_n = [0 0 0 0 0 0]'; */
      for (i = 0; i < 6; i++) {
        rtb_gamma_n[i] = 0.0;
      }
    } else if (rtb_Clock <= 30.0) {
      /* '<S2>:1:5' elseif time <= 30 */
      /* '<S2>:1:6' gamma_n = [0.4 0.3 0 0 0 0]'; */
      for (i = 0; i < 6; i++) {
        rtb_gamma_n[i] = b[i];
      }
    } else {
      /* '<S2>:1:7' else */
      /* '<S2>:1:8' gamma_n = [0.4 0.3 0.0 0 0 0]'; */
      for (i = 0; i < 6; i++) {
        rtb_gamma_n[i] = b[i];
      }
    }

    /* End of MATLAB Function: '<Root>/FDD' */

    /* Sum: '<S10>/Sum1' incorporates:
     *  Gain: '<S10>/ '
     *  Gain: '<S10>/                    '
     *  Inport: '<Root>/X'
     *  Integrator: '<S10>/Integrator1'
     *  SignalConversion: '<S10>/TmpSignal ConversionAt                    Inport1'
     */
    /* MATLAB Function 'MATLAB Function2': '<S6>:1' */
    /* '<S6>:1:3' KK =  [   0.1667    0.7752   -1.3427   -4.5662   -0.0400    7.4219   -3.7475    5.6206   -0.1403    6.9843   -0.7774    3.8970   -0.0755    7.2507    9.9725    1.9194 */
    /* '<S6>:1:4'     0.1667    1.5504   -0.0000    4.5662   -0.1022    2.3029         0    9.2496    0.0897    5.8899         0    8.8995   -0.0486    0.7980         0    5.8012 */
    /* '<S6>:1:5'     0.1667    0.7752    1.3427   -4.5662   -0.0671   -1.3929    1.5130    1.5891   -0.2596    1.8251    0.3326   -0.0334   -0.2776    7.3404   13.9626    3.2585 */
    /* '<S6>:1:6'     0.1667   -0.7752    1.3427    4.5662    0.0802    0.5940   -1.4171   -4.9893   -0.0259   -1.9083    0.8339   -5.8534   -0.0171   -1.8501    0.8749   -4.4759 */
    /* '<S6>:1:7'     0.1667   -1.5504    0.0000   -4.5662   -0.1026    5.8128         0    3.8142    0.0791    9.5731         0    4.8865   -0.0476    4.3847         0    2.2992 */
    /* '<S6>:1:8'     0.1667   -0.7752   -1.3427    4.5662    0.0678   -9.2485    3.2609   -5.1257    0.0068   -7.4496    1.8489   -5.1788    0.1212    1.2453    3.3763   -4.5579]; */
    /* '<S6>:1:9' K = KK(:,5:8)*gamma_n(1)+KK(:,9:12)*gamma_n(2) +KK(:,13:end)*gamma_n(3) ; */
    /* MATLAB Function 'MATLAB Function1': '<S5>:1' */
    /* '<S5>:1:2' g = 9.81; */
    /*  ff = [sin(t)/g;cos(t)/g]; % ff(1) => teta_ref */
    /* '<S5>:1:5' axref_N = -cos(t); */
    /* '<S5>:1:6' ayref_N = -sin(t); */
    /* '<S5>:1:8' axref_b = cos(X(8))*cos(X(9))*axref_N + cos(X(8))*sin(X(9))*ayref_N; */
    /* '<S5>:1:9' ayref_b = (sin(X(7))*sin(X(8))*cos(X(9)) - cos(X(7))*sin(X(9)))*axref_N + (sin(X(7))*sin(X(8))*sin(X(9)) + cos(X(7))*cos(X(9)))*ayref_N; */
    /*   */
    /* '<S5>:1:11' phi_ff = -ayref_b/g; */
    /* '<S5>:1:12' teta_ff = axref_b/g; */
    /*   */
    /*  ff(1) => phi_ref after Fcn1 */
    /* '<S5>:1:14' ff = [phi_ff;teta_ff] % ff(1) => phi_ref after Fcn1 */
    rtb_ixj = 0.17320508075688992 * gazebo_gs_X.Integrator1_CSTATE_h -
      (0.32349951352987977 * gazebo_gs_U.X[0] + 0.2732366014912751 *
       gazebo_gs_U.X[3]);

    /* Sum: '<S11>/Sum1' incorporates:
     *  Gain: '<S11>/  '
     *  Gain: '<S11>/                     '
     *  Inport: '<Root>/X'
     *  Integrator: '<S11>/Integrator1'
     *  SignalConversion: '<S11>/TmpSignal ConversionAt                     Inport1'
     */
    rtb_kxi = -0.173205080756885 * gazebo_gs_X.Integrator1_CSTATE_j -
      (-0.31312578517366968 * gazebo_gs_U.X[1] + -0.25417198201077484 *
       gazebo_gs_U.X[4]);

    /* Sum: '<Root>/Sum1' incorporates:
     *  Fcn: '<Root>/Fcn1'
     *  Inport: '<Root>/X'
     *  MATLAB Function: '<Root>/MATLAB Function1'
     */
    rtb_FMxMyMz_idx_0 = -((std::sin(gazebo_gs_U.X[6]) * std::sin(gazebo_gs_U.X[7])
      * std::cos(gazebo_gs_U.X[8]) - std::cos(gazebo_gs_U.X[6]) * std::sin
      (gazebo_gs_U.X[8])) * -std::cos(rtb_Clock) + (std::sin(gazebo_gs_U.X[6]) *
      std::sin(gazebo_gs_U.X[7]) * std::sin(gazebo_gs_U.X[8]) + std::cos
      (gazebo_gs_U.X[6]) * std::cos(gazebo_gs_U.X[8])) * -std::sin(rtb_Clock)) /
      9.81 + (rtb_kxi * std::cos(gazebo_gs_U.X[8]) + rtb_ixj * std::sin
              (gazebo_gs_U.X[8]));

    /* Saturate: '<S7>/roll' */
    if (rtb_FMxMyMz_idx_0 > 0.52359877559829882) {
      rtb_FMxMyMz_idx_0 = 0.52359877559829882;
    } else {
      if (rtb_FMxMyMz_idx_0 < -0.52359877559829882) {
        rtb_FMxMyMz_idx_0 = -0.52359877559829882;
      }
    }

    /* End of Saturate: '<S7>/roll' */

    /* Sum: '<S7>/Sum1' incorporates:
     *  Gain: '<S7>/                    '
     *  Inport: '<Root>/X'
     *  SignalConversion: '<S7>/TmpSignal ConversionAt                    Inport1'
     */
    rtb_jxk = rtb_FMxMyMz_idx_0 - (1.1365283480217869 * gazebo_gs_U.X[6] +
      0.28178545108770103 * gazebo_gs_U.X[9]);

    /* Fcn: '<Root>/Fcn' incorporates:
     *  Inport: '<Root>/X'
     */
    rtb_ixj = -rtb_kxi * std::sin(gazebo_gs_U.X[8]) + rtb_ixj * std::cos
      (gazebo_gs_U.X[8]);

    /* Sum: '<Root>/Sum4' incorporates:
     *  Inport: '<Root>/X'
     *  MATLAB Function: '<Root>/MATLAB Function1'
     */
    rtb_ixj += (std::cos(gazebo_gs_U.X[7]) * std::cos(gazebo_gs_U.X[8]) * -std::
                cos(rtb_Clock) + std::cos(gazebo_gs_U.X[7]) * std::sin
                (gazebo_gs_U.X[8]) * -std::sin(rtb_Clock)) / 9.81;

    /* SignalConversion: '<Root>/TmpSignal ConversionAt                 Inport1' incorporates:
     *  Gain: '<S12>/  '
     *  Gain: '<S12>/                     '
     *  Inport: '<Root>/X'
     *  Integrator: '<S12>/Integrator1'
     *  SignalConversion: '<S12>/TmpSignal ConversionAt                     Inport1'
     *  Sum: '<S12>/Sum1'
     */
    rtb_FMxMyMz_idx_0 = 10.000000000000018 * gazebo_gs_X.Integrator1_CSTATE -
      (12.219481695651957 * gazebo_gs_U.X[2] + 6.215786645518647 *
       gazebo_gs_U.X[5]);

    /* Sum: '<S9>/Sum1' incorporates:
     *  Saturate: '<S9>/pitch'
     */
    if (rtb_ixj > 0.52359877559829882) {
      rtb_ixj = 0.52359877559829882;
    } else {
      if (rtb_ixj < -0.52359877559829882) {
        rtb_ixj = -0.52359877559829882;
      }
    }

    /* SignalConversion: '<Root>/TmpSignal ConversionAt                 Inport1' incorporates:
     *  Gain: '<S8>/  '
     *  Gain: '<S8>/                     '
     *  Gain: '<S9>/                    '
     *  Inport: '<Root>/X'
     *  Integrator: '<S8>/Integrator1'
     *  SignalConversion: '<S8>/TmpSignal ConversionAt                     Inport1'
     *  SignalConversion: '<S9>/TmpSignal ConversionAt                    Inport1'
     *  Sum: '<S8>/Sum1'
     *  Sum: '<S9>/Sum1'
     */
    rtb_ixj -= 1.2859205994736729 * gazebo_gs_U.X[7] + 0.34413551249350854 *
      gazebo_gs_U.X[10];
    rtb_kxi = 0.15811388300841925 * gazebo_gs_X.Integrator1_CSTATE_b -
      (0.3035552054947866 * gazebo_gs_U.X[8] + 0.24395632222527311 *
       gazebo_gs_U.X[11]);

    /* MATLAB Function: '<Root>/MATLAB Function2' incorporates:
     *  Product: '<Root>/Product3'
     */
    for (i = 0; i < 4; i++) {
      for (i_0 = 0; i_0 < 6; i_0++) {
        a_1[i_0 + 6 * i] = (a[6 * i + i_0] * rtb_gamma_n[0] + b_a[6 * i + i_0] *
                            rtb_gamma_n[1]) + c_a[6 * i + i_0] * rtb_gamma_n[2];
      }
    }

    /* End of MATLAB Function: '<Root>/MATLAB Function2' */
    for (i = 0; i < 6; i++) {
      /* Product: '<Root>/Product3' incorporates:
       *  SignalConversion: '<Root>/TmpSignal ConversionAt                 Inport1'
       *  Sum: '<Root>/Sum2'
       */
      rtb_Product_idx_2 = a_1[i + 18] * rtb_kxi + (a_1[i + 12] * rtb_ixj +
        (a_1[i + 6] * rtb_jxk + a_1[i] * rtb_FMxMyMz_idx_0));

      /* Gain: '<Root>/                 ' incorporates:
       *  SignalConversion: '<Root>/TmpSignal ConversionAt                 Inport1'
       *  Sum: '<Root>/Sum2'
       */
      tmp = gazebo_gs_ConstP._Gain_m[i + 18] * rtb_kxi +
        (gazebo_gs_ConstP._Gain_m[i + 12] * rtb_ixj +
         (gazebo_gs_ConstP._Gain_m[i + 6] * rtb_jxk + gazebo_gs_ConstP._Gain_m[i]
          * rtb_FMxMyMz_idx_0));

      /* Sum: '<Root>/Sum2' */
      gazebo_gs_B.Sum2[i] = (rtb_Product_idx_2 + tmp) + 2.5179000000000005;
    }

    /* MATLAB Function: '<Root>/Actuator_Fault' */
    /* MATLAB Function 'Actuator_Fault': '<S1>:1' */
    /* '<S1>:1:2' T_f = T; */
    /* '<S1>:1:3' if time <= 10 */
    if (rtb_Clock <= 10.0) {
      /* '<S1>:1:4' T_f = T; */
      for (i = 0; i < 6; i++) {
        rtb_gamma_n[i] = gazebo_gs_B.Sum2[i];
      }
    } else if (rtb_Clock <= 25.0) {
      /* '<S1>:1:5' elseif time <=25 */
      /* '<S1>:1:6' T1 = T(1)*0.6; */
      /* '<S1>:1:7' T2 = T(2)*0.7; */
      /* '<S1>:1:8' T3 = T(3)*1; */
      /* '<S1>:1:9' T4 = T(4)*1; */
      /* '<S1>:1:10' T5 = T(5)*1; */
      /* '<S1>:1:11' T6 = T(6)*1; */
      /* '<S1>:1:12' T_f = [T1;T2;T3;T4;T5;T6]; */
      rtb_gamma_n[0] = gazebo_gs_B.Sum2[0] * 0.6;
      rtb_gamma_n[1] = gazebo_gs_B.Sum2[1] * 0.7;
      rtb_gamma_n[2] = gazebo_gs_B.Sum2[2];
      rtb_gamma_n[3] = gazebo_gs_B.Sum2[3];
      rtb_gamma_n[4] = gazebo_gs_B.Sum2[4];
      rtb_gamma_n[5] = gazebo_gs_B.Sum2[5];
    } else {
      /* '<S1>:1:13' else */
      /* '<S1>:1:14' T1 = T(1)*0.6; */
      /* '<S1>:1:15' T2 = T(2)*0.7; */
      /* '<S1>:1:16' T3 = T(3)*1; */
      /* '<S1>:1:17' T4 = T(4)*1; */
      /* '<S1>:1:18' T5 = T(5)*1; */
      /* '<S1>:1:19' T6 = T(6)*1; */
      /* '<S1>:1:20' T_f = [T1;T2;T3;T4;T5;T6]; */
      rtb_gamma_n[0] = gazebo_gs_B.Sum2[0] * 0.6;
      rtb_gamma_n[1] = gazebo_gs_B.Sum2[1] * 0.7;
      rtb_gamma_n[2] = gazebo_gs_B.Sum2[2];
      rtb_gamma_n[3] = gazebo_gs_B.Sum2[3];
      rtb_gamma_n[4] = gazebo_gs_B.Sum2[4];
      rtb_gamma_n[5] = gazebo_gs_B.Sum2[5];
    }

    /* End of MATLAB Function: '<Root>/Actuator_Fault' */

    /* Outport: '<Root>/virtual_control' incorporates:
     *  SignalConversion: '<Root>/TmpSignal ConversionAt                 Inport1'
     */
    gazebo_gs_Y.virtual_control[0] = rtb_FMxMyMz_idx_0;
    gazebo_gs_Y.virtual_control[1] = rtb_jxk;
    gazebo_gs_Y.virtual_control[2] = rtb_ixj;
    gazebo_gs_Y.virtual_control[3] = rtb_kxi;
    for (i = 0; i < 6; i++) {
      /* Sqrt: '<Root>/Sqrt1' incorporates:
       *  Gain: '<Root>/      '
       *  Saturate: '<Root>/Saturation1'
       */
      if (rtb_gamma_n[i] > 8.54858) {
        rtb_ixj = 8.54858;
      } else if (rtb_gamma_n[i] < 0.0) {
        rtb_ixj = 0.0;
      } else {
        rtb_ixj = rtb_gamma_n[i];
      }

      rtb_ixj = std::sqrt(116978.4923343994 * rtb_ixj);

      /* End of Sqrt: '<Root>/Sqrt1' */

      /* Gain: '<Root>/rads_to_RPM' */
      rtb_jxk = 9.5493 * rtb_ixj;

      /* Gain: '<Root>/mapping_0_200' incorporates:
       *  Constant: '<Root>/Constant '
       *  Sum: '<Root>/Sum3'
       */
      rtb_FMxMyMz_idx_0 = (rtb_jxk - 1250.0) * 0.022857142857142857;

      /* Saturate: '<Root>/Saturation' */
      if (rtb_FMxMyMz_idx_0 < 0.0) {
        /* Outport: '<Root>/motor_command' */
        gazebo_gs_Y.motor_command[i] = 0.0;
      } else {
        /* Outport: '<Root>/motor_command' */
        gazebo_gs_Y.motor_command[i] = rtb_FMxMyMz_idx_0;
      }

      /* End of Saturate: '<Root>/Saturation' */

      /* Outport: '<Root>/motor_speed' */
      gazebo_gs_Y.motor_speed[i] = rtb_ixj;

      /* Outport: '<Root>/motor_RPM' */
      gazebo_gs_Y.motor_RPM[i] = rtb_jxk;
    }

    /* MATLAB Function: '<Root>/MATLAB Function' */
    /* MATLAB Function 'MATLAB Function': '<S4>:1' */
    /* '<S4>:1:2' x = cos(t); */
    /* '<S4>:1:3' y = sin(t); */
    /* '<S4>:1:4' z = min(t,15); */
    /* '<S4>:1:5' ref = [x;y;z;0]; */
    rtb_FMxMyMz_idx_0 = std::cos(rtb_Clock);
    rtb_jxk = std::sin(rtb_Clock);
    if (rtb_Clock < 15.0) {
      rtb_ixj = rtb_Clock;
    } else {
      rtb_ixj = 15.0;
    }

    /* End of MATLAB Function: '<Root>/MATLAB Function' */

    /* Outport: '<Root>/ref' */
    gazebo_gs_Y.ref[0] = rtb_FMxMyMz_idx_0;
    gazebo_gs_Y.ref[1] = rtb_jxk;
    gazebo_gs_Y.ref[2] = rtb_ixj;
    gazebo_gs_Y.ref[3] = 0.0;
    if (rtmIsMajorTimeStep((&gazebo_gs_M))) {
      /* Memory: '<S3>/Memory' */
      for (i = 0; i < 6; i++) {
        gazebo_gs_B.Memory[i] = gazebo_gs_DW.Memory_PreviousInput[i];
      }

      /* End of Memory: '<S3>/Memory' */
    }

    /* Derivative: '<S3>/Derivative' incorporates:
     *  Inport: '<Root>/X'
     */
    if ((gazebo_gs_DW.TimeStampA >= (&gazebo_gs_M)->Timing.t[0]) &&
        (gazebo_gs_DW.TimeStampB >= (&gazebo_gs_M)->Timing.t[0])) {
      rtb_Sum1[0] = 0.0;
      rtb_Sum1[1] = 0.0;
      rtb_Sum1[2] = 0.0;
    } else {
      rtb_Clock = gazebo_gs_DW.TimeStampA;
      lastU = (real_T (*)[3])gazebo_gs_DW.LastUAtTimeA;
      if (gazebo_gs_DW.TimeStampA < gazebo_gs_DW.TimeStampB) {
        if (gazebo_gs_DW.TimeStampB < (&gazebo_gs_M)->Timing.t[0]) {
          rtb_Clock = gazebo_gs_DW.TimeStampB;
          lastU = (real_T (*)[3])gazebo_gs_DW.LastUAtTimeB;
        }
      } else {
        if (gazebo_gs_DW.TimeStampA >= (&gazebo_gs_M)->Timing.t[0]) {
          rtb_Clock = gazebo_gs_DW.TimeStampB;
          lastU = (real_T (*)[3])gazebo_gs_DW.LastUAtTimeB;
        }
      }

      rtb_Clock = (&gazebo_gs_M)->Timing.t[0] - rtb_Clock;
      rtb_Sum1[0] = (gazebo_gs_U.X[9] - (*lastU)[0]) / rtb_Clock;
      rtb_Sum1[1] = (gazebo_gs_U.X[10] - (*lastU)[1]) / rtb_Clock;
      rtb_Sum1[2] = (gazebo_gs_U.X[11] - (*lastU)[2]) / rtb_Clock;
    }

    /* End of Derivative: '<S3>/Derivative' */

    /* Product: '<S3>/Product' incorporates:
     *  Constant: '<S3>/Constant1'
     */
    for (i = 0; i < 3; i++) {
      rtb_Product[i] = gazebo_gs_ConstP.Constant1_Value[i + 6] * rtb_Sum1[2] +
        (gazebo_gs_ConstP.Constant1_Value[i + 3] * rtb_Sum1[1] +
         gazebo_gs_ConstP.Constant1_Value[i] * rtb_Sum1[0]);
    }

    /* End of Product: '<S3>/Product' */

    /* Product: '<S3>/Product1' incorporates:
     *  Constant: '<S3>/Constant1'
     *  Inport: '<Root>/X'
     */
    for (i = 0; i < 3; i++) {
      rtb_Sum1[i] = gazebo_gs_ConstP.Constant1_Value[i + 6] * gazebo_gs_U.X[11]
        + (gazebo_gs_ConstP.Constant1_Value[i + 3] * gazebo_gs_U.X[10] +
           gazebo_gs_ConstP.Constant1_Value[i] * gazebo_gs_U.X[9]);
    }

    /* End of Product: '<S3>/Product1' */

    /* Sum: '<S3>/Sum3' incorporates:
     *  Inport: '<Root>/X'
     *  MATLAB Function: '<S3>/MATLAB Function1'
     *  Product: '<S15>/i x k'
     *  Product: '<S15>/j x i'
     *  Product: '<S15>/k x j'
     *  Product: '<S16>/i x j'
     *  Product: '<S16>/j x k'
     *  Product: '<S16>/k x i'
     *  Sum: '<S13>/Sum1'
     */
    /* MATLAB Function 'FDD  /MATLAB Function1': '<S14>:1' */
    /* '<S14>:1:2' arm = 0.215; */
    /* '<S14>:1:2' gra = 9.81; */
    /* '<S14>:1:2' factor = 0.0365; */
    /* '<S14>:1:4' M = [arm/2 arm arm/2; */
    /* '<S14>:1:5'       -sqrt(3)*arm/2 0 sqrt(3)*arm/2; */
    /* '<S14>:1:6'       -factor factor -factor]; */
    /* '<S14>:1:8' diff = [u(1) - u(4) ; */
    /* '<S14>:1:9'         u(2) - u(5) ; */
    /* '<S14>:1:10'         u(3) - u(6) ]; */
    /* '<S14>:1:11' Residu_1_4 = diff - inv(M)*y; */
    rtb_Clock = (gazebo_gs_U.X[10] * rtb_Sum1[2] - gazebo_gs_U.X[11] * rtb_Sum1
                 [1]) + rtb_Product[0];
    rtb_kxi = (gazebo_gs_U.X[11] * rtb_Sum1[0] - gazebo_gs_U.X[9] * rtb_Sum1[2])
      + rtb_Product[1];
    rtb_Product_idx_2 = (gazebo_gs_U.X[9] * rtb_Sum1[1] - gazebo_gs_U.X[10] *
                         rtb_Sum1[0]) + rtb_Product[2];

    /* MATLAB Function: '<S3>/MATLAB Function1' */
    rtb_Sum1[0] = gazebo_gs_B.Memory[0] - gazebo_gs_B.Memory[3];
    rtb_Sum1[1] = gazebo_gs_B.Memory[1] - gazebo_gs_B.Memory[4];
    rtb_Sum1[2] = gazebo_gs_B.Memory[2] - gazebo_gs_B.Memory[5];
    for (i = 0; i < 3; i++) {
      rtb_Product[i] = rtb_Sum1[i] - (a_0[i + 6] * rtb_Product_idx_2 + (a_0[i +
        3] * rtb_kxi + a_0[i] * rtb_Clock));
    }

    /* Outport: '<Root>/gamma' incorporates:
     *  MATLAB Function: '<S3>/MATLAB Function1'
     */
    /*  Residu_1_4 */
    /* '<S14>:1:14' gamma    = [1-(-Residu_1_4(1) + u(1))/u(1) */
    /* '<S14>:1:15'             1-(-Residu_1_4(2) + u(2))/u(2) */
    /* '<S14>:1:16'             1-(-Residu_1_4(3) + u(3))/u(3)]; */
    gazebo_gs_Y.gamma[0] = 1.0 - (-rtb_Product[0] + gazebo_gs_B.Memory[0]) /
      gazebo_gs_B.Memory[0];
    gazebo_gs_Y.gamma[1] = 1.0 - (-rtb_Product[1] + gazebo_gs_B.Memory[1]) /
      gazebo_gs_B.Memory[1];
    gazebo_gs_Y.gamma[2] = 1.0 - (-rtb_Product[2] + gazebo_gs_B.Memory[2]) /
      gazebo_gs_B.Memory[2];

    /* Saturate: '<S8>/Saturation' incorporates:
     *  Inport: '<Root>/X'
     *  Sum: '<S8>/Sum3'
     */
    if (0.0 - gazebo_gs_U.X[8] > 0.52359877559829882) {
      gazebo_gs_B.Saturation = 0.52359877559829882;
    } else if (0.0 - gazebo_gs_U.X[8] < -0.52359877559829882) {
      gazebo_gs_B.Saturation = -0.52359877559829882;
    } else {
      gazebo_gs_B.Saturation = 0.0 - gazebo_gs_U.X[8];
    }

    /* End of Saturate: '<S8>/Saturation' */

    /* Saturate: '<S10>/x' */
    if (rtb_FMxMyMz_idx_0 > 1.0) {
      rtb_FMxMyMz_idx_0 = 1.0;
    } else {
      if (rtb_FMxMyMz_idx_0 < -1.0) {
        rtb_FMxMyMz_idx_0 = -1.0;
      }
    }

    /* End of Saturate: '<S10>/x' */

    /* Sum: '<S10>/Sum3' incorporates:
     *  Inport: '<Root>/X'
     */
    rtb_FMxMyMz_idx_0 -= gazebo_gs_U.X[0];

    /* Saturate: '<S10>/x1' */
    if (rtb_FMxMyMz_idx_0 > 2.0) {
      gazebo_gs_B.x1 = 2.0;
    } else if (rtb_FMxMyMz_idx_0 < -2.0) {
      gazebo_gs_B.x1 = -2.0;
    } else {
      gazebo_gs_B.x1 = rtb_FMxMyMz_idx_0;
    }

    /* End of Saturate: '<S10>/x1' */

    /* Saturate: '<S11>/y' */
    if (rtb_jxk > 1.0) {
      rtb_jxk = 1.0;
    } else {
      if (rtb_jxk < -1.0) {
        rtb_jxk = -1.0;
      }
    }

    /* End of Saturate: '<S11>/y' */

    /* Sum: '<S11>/Sum3' incorporates:
     *  Inport: '<Root>/X'
     */
    rtb_FMxMyMz_idx_0 = rtb_jxk - gazebo_gs_U.X[1];

    /* Saturate: '<S11>/y1' */
    if (rtb_FMxMyMz_idx_0 > 2.0) {
      gazebo_gs_B.y1 = 2.0;
    } else if (rtb_FMxMyMz_idx_0 < -2.0) {
      gazebo_gs_B.y1 = -2.0;
    } else {
      gazebo_gs_B.y1 = rtb_FMxMyMz_idx_0;
    }

    /* End of Saturate: '<S11>/y1' */

    /* Sum: '<S12>/Sum3' incorporates:
     *  Inport: '<Root>/X'
     */
    rtb_FMxMyMz_idx_0 = rtb_ixj - gazebo_gs_U.X[2];

    /* Saturate: '<S12>/Saturation' */
    if (rtb_FMxMyMz_idx_0 > 1.0) {
      gazebo_gs_B.Saturation_a = 1.0;
    } else if (rtb_FMxMyMz_idx_0 < -1.0) {
      gazebo_gs_B.Saturation_a = -1.0;
    } else {
      gazebo_gs_B.Saturation_a = rtb_FMxMyMz_idx_0;
    }

    /* End of Saturate: '<S12>/Saturation' */
  }

  if (rtmIsMajorTimeStep((&gazebo_gs_M))) {
    real_T (*lastU)[3];
    int32_T i;
    if (rtmIsMajorTimeStep((&gazebo_gs_M))) {
      /* Update for Memory: '<S3>/Memory' */
      for (i = 0; i < 6; i++) {
        gazebo_gs_DW.Memory_PreviousInput[i] = gazebo_gs_B.Sum2[i];
      }

      /* End of Update for Memory: '<S3>/Memory' */
    }

    /* Update for Derivative: '<S3>/Derivative' incorporates:
     *  Update for Inport: '<Root>/X'
     */
    if (gazebo_gs_DW.TimeStampA == (rtInf)) {
      gazebo_gs_DW.TimeStampA = (&gazebo_gs_M)->Timing.t[0];
      lastU = (real_T (*)[3])gazebo_gs_DW.LastUAtTimeA;
    } else if (gazebo_gs_DW.TimeStampB == (rtInf)) {
      gazebo_gs_DW.TimeStampB = (&gazebo_gs_M)->Timing.t[0];
      lastU = (real_T (*)[3])gazebo_gs_DW.LastUAtTimeB;
    } else if (gazebo_gs_DW.TimeStampA < gazebo_gs_DW.TimeStampB) {
      gazebo_gs_DW.TimeStampA = (&gazebo_gs_M)->Timing.t[0];
      lastU = (real_T (*)[3])gazebo_gs_DW.LastUAtTimeA;
    } else {
      gazebo_gs_DW.TimeStampB = (&gazebo_gs_M)->Timing.t[0];
      lastU = (real_T (*)[3])gazebo_gs_DW.LastUAtTimeB;
    }

    (*lastU)[0] = gazebo_gs_U.X[9];
    (*lastU)[1] = gazebo_gs_U.X[10];
    (*lastU)[2] = gazebo_gs_U.X[11];

    /* End of Update for Derivative: '<S3>/Derivative' */
  }                                    /* end MajorTimeStep */

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

  /* Derivatives for Integrator: '<S12>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = gazebo_gs_B.Saturation_a;

  /* Derivatives for Integrator: '<S10>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_h = gazebo_gs_B.x1;

  /* Derivatives for Integrator: '<S11>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_j = gazebo_gs_B.y1;

  /* Derivatives for Integrator: '<S8>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_b = gazebo_gs_B.Saturation;
}

/* Model initialize function */
void gazebo_gsModelClass::initialize()
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

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

  /* states (dwork) */
  (void) memset((void *)&gazebo_gs_DW, 0,
                sizeof(DW_gazebo_gs_T));

  /* external inputs */
  (void)memset((void *)&gazebo_gs_U, 0, sizeof(ExtU_gazebo_gs_T));

  /* external outputs */
  (void) memset((void *)&gazebo_gs_Y, 0,
                sizeof(ExtY_gazebo_gs_T));

  {
    int32_T i;

    /* InitializeConditions for Integrator: '<S12>/Integrator1' */
    gazebo_gs_X.Integrator1_CSTATE = 0.0;

    /* InitializeConditions for Integrator: '<S10>/Integrator1' */
    gazebo_gs_X.Integrator1_CSTATE_h = 0.0;

    /* InitializeConditions for Integrator: '<S11>/Integrator1' */
    gazebo_gs_X.Integrator1_CSTATE_j = 0.0;

    /* InitializeConditions for Integrator: '<S8>/Integrator1' */
    gazebo_gs_X.Integrator1_CSTATE_b = 0.0;

    /* InitializeConditions for Memory: '<S3>/Memory' */
    for (i = 0; i < 6; i++) {
      gazebo_gs_DW.Memory_PreviousInput[i] = 2.5179000000000005;
    }

    /* End of InitializeConditions for Memory: '<S3>/Memory' */

    /* InitializeConditions for Derivative: '<S3>/Derivative' */
    gazebo_gs_DW.TimeStampA = (rtInf);
    gazebo_gs_DW.TimeStampB = (rtInf);
  }
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
