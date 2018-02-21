/*
 * scenario1_gs.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "scenario1_gs".
 *
 * Model version              : 1.765
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Tue Feb 20 19:37:35 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Passed (1), Warnings (3), Error (0)
 */

#include "scenario1_gs.h"
#include "scenario1_gs_private.h"

/*
 * This function updates continuous states using the ODE5 fixed-step
 * solver algorithm
 */
void scenario1_gsModelClass::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
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
  scenario1_gs_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE5_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[0]);
  rtsiSetdX(si, f1);
  this->step();
  scenario1_gs_derivatives();

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
  scenario1_gs_derivatives();

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
  scenario1_gs_derivatives();

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
  scenario1_gs_derivatives();

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
  scenario1_gs_derivatives();

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
void scenario1_gsModelClass::step()
{
  if (rtmIsMajorTimeStep((&scenario1_gs_M))) {
    /* set solver stop time */
    if (!((&scenario1_gs_M)->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&(&scenario1_gs_M)->solverInfo, (((&scenario1_gs_M
        )->Timing.clockTickH0 + 1) * (&scenario1_gs_M)->Timing.stepSize0 *
        4294967296.0));
    } else {
      rtsiSetSolverStopTime(&(&scenario1_gs_M)->solverInfo, (((&scenario1_gs_M
        )->Timing.clockTick0 + 1) * (&scenario1_gs_M)->Timing.stepSize0 +
        (&scenario1_gs_M)->Timing.clockTickH0 * (&scenario1_gs_M)
        ->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep((&scenario1_gs_M))) {
    (&scenario1_gs_M)->Timing.t[0] = rtsiGetT(&(&scenario1_gs_M)->solverInfo);
  }

  {
    real_T (*lastU)[3];
    static const real_T b[6] = { 0.6, 1.0, 1.0, 1.0, 1.0, 1.0 };

    static const real_T a[24] = { 0.043, -0.0287, -0.085, 0.1249, 0.0059,
      -0.0605, 0.9809, 0.2621, 0.3024, 0.5056, 0.1418, 0.2842, -0.1072, 0.0,
      0.5768, -0.4396, 0.0, 0.4264, 0.3112, 0.5542, -0.1013, -0.9239, -0.5886,
      -1.0593 };

    static const real_T b_a[24] = { -0.0668, -0.0434, 0.0082, -0.0319, 0.0442,
      0.0043, -0.0125, 2.0588, -0.9295, -0.1525, 1.4181, -0.3712, 0.4875, 0.0,
      0.6373, 0.2278, 0.0, 0.4485, -0.4266, -1.0814, -0.861, -0.0198, 0.3327,
      -0.3422 };

    static const real_T c_a[24] = { -0.1489, -0.0304, 0.0763, -0.0873, -0.0055,
      0.1208, 0.9566, 0.645, 0.109, -0.0115, 0.1199, 0.9132, 0.7687, 0.0, 0.737,
      -0.1312, 0.0, 0.539, 0.241, 0.55, -0.1244, -0.7586, -0.5681, -1.1708 };

    int32_T z;
    static const real_T a_0[9] = { 1.5503875968992249, 3.1007751937984493,
      1.5503875968992249, -2.6853500892540736, -0.0, 2.6853500892540736,
      -9.1324200913242013, 9.1324200913242013, -9.1324200913242013 };

    real_T rtb_VectorConcatenate[12];
    real_T rtb_ixj;
    real_T rtb_kxi;
    real_T rtb_jxk;
    real_T rtb_Product[3];
    real_T rtb_Sum1[3];
    real_T rtb_Clock;
    real_T rtb_gamma_n[6];
    int32_T i;
    real_T a_1[24];
    real_T rtb_ref_idx_0;
    real_T rtb_Product_idx_2;
    real_T tmp;

    /* Clock: '<Root>/Clock' */
    rtb_Clock = (&scenario1_gs_M)->Timing.t[0];

    /* MATLAB Function: '<Root>/FDD' */
    /* MATLAB Function 'FDD': '<S2>:1' */
    /* '<S2>:1:2' gamma_n = [0 0 0 0 0 0]'; */
    for (i = 0; i < 6; i++) {
      rtb_gamma_n[i] = 0.0;
    }

    /* '<S2>:1:3' if time >= 12 */
    if (rtb_Clock >= 12.0) {
      /* '<S2>:1:4' gamma_n = [0.6 1 1 1 1 1]'; */
      for (i = 0; i < 6; i++) {
        rtb_gamma_n[i] = b[i];
      }
    }

    /* End of MATLAB Function: '<Root>/FDD' */

    /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn1' incorporates:
     *  Inport: '<Root>/X0'
     */
    /* MATLAB Function 'MATLAB Function2': '<S5>:1' */
    /* '<S5>:1:3' KK = [0.1667    0.7752   -1.3427   -4.5662    0.0430    0.9809   -0.1072    0.3112   -0.0668   -0.0125    0.4875   -0.4266   -0.1489    0.9566    0.7687    0.2410 */
    /* '<S5>:1:4'       0.1667    1.5504   -0.0000    4.5662   -0.0287    0.2621         0    0.5542   -0.0434    2.0588         0   -1.0814   -0.0304    0.6450         0    0.5500 */
    /* '<S5>:1:5'       0.1667    0.7752    1.3427   -4.5662   -0.0850    0.3024    0.5768   -0.1013    0.0082   -0.9295    0.6373   -0.8610    0.0763    0.1090    0.7370   -0.1244 */
    /* '<S5>:1:6'       0.1667   -0.7752    1.3427    4.5662    0.1249    0.5056   -0.4396   -0.9239   -0.0319   -0.1525    0.2278   -0.0198   -0.0873   -0.0115   -0.1312   -0.7586 */
    /* '<S5>:1:7'       0.1667   -1.5504    0.0000   -4.5662    0.0059    0.1418         0   -0.5886    0.0442    1.4181         0    0.3327   -0.0055    0.1199         0   -0.5681 */
    /* '<S5>:1:8'       0.1667   -0.7752   -1.3427    4.5662   -0.0605    0.2842    0.4264   -1.0593    0.0043   -0.3712    0.4485   -0.3422    0.1208    0.9132    0.5390   -1.1708] */
    /*  K = KK(:,1:4)*0.25+KK(:,5:8)*gamma_n(1)+KK(:,9:12)*gamma_n(2)+KK(:,13:end)*gamma_n(3) ;    */
    /* '<S5>:1:10' K = KK(:,5:8)*gamma_n(1)+KK(:,9:12)*gamma_n(2)+KK(:,13:end)*gamma_n(3) ; */
    /*     */
    rtb_VectorConcatenate[0] = scenario1_gs_U.X0[0];
    rtb_VectorConcatenate[1] = scenario1_gs_U.X0[1];
    rtb_VectorConcatenate[2] = scenario1_gs_U.X0[2];

    /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn2' */
    for (i = 0; i < 5; i++) {
      rtb_VectorConcatenate[i + 3] = 0.0;
    }

    /* End of SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn2' */

    /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn3' incorporates:
     *  Inport: '<Root>/X0'
     */
    rtb_VectorConcatenate[8] = scenario1_gs_U.X0[3];

    /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn4' */
    rtb_VectorConcatenate[9] = 0.0;
    rtb_VectorConcatenate[10] = 0.0;
    rtb_VectorConcatenate[11] = 0.0;

    /* Sum: '<Root>/Sum' incorporates:
     *  Inport: '<Root>/X'
     */
    for (i = 0; i < 12; i++) {
      rtb_VectorConcatenate[i] = scenario1_gs_U.X[i] - rtb_VectorConcatenate[i];
    }

    /* End of Sum: '<Root>/Sum' */

    /* Sum: '<S9>/Sum1' incorporates:
     *  Gain: '<S9>/ '
     *  Gain: '<S9>/                    '
     *  Integrator: '<S9>/Integrator1'
     *  SignalConversion: '<S9>/TmpSignal ConversionAt                    Inport1'
     */
    rtb_ixj = 0.17320508075688992 * scenario1_gs_X.Integrator1_CSTATE_h -
      (0.32349951352987977 * rtb_VectorConcatenate[0] + 0.2732366014912751 *
       rtb_VectorConcatenate[3]);

    /* Sum: '<S10>/Sum1' incorporates:
     *  Gain: '<S10>/  '
     *  Gain: '<S10>/                     '
     *  Integrator: '<S10>/Integrator1'
     *  SignalConversion: '<S10>/TmpSignal ConversionAt                     Inport1'
     */
    rtb_kxi = -0.173205080756885 * scenario1_gs_X.Integrator1_CSTATE_j -
      (-0.31312578517366968 * rtb_VectorConcatenate[1] + -0.25417198201077484 *
       rtb_VectorConcatenate[4]);

    /* Fcn: '<Root>/Fcn1' incorporates:
     *  Inport: '<Root>/X'
     */
    rtb_jxk = rtb_kxi * std::cos(scenario1_gs_U.X[8]) + rtb_ixj * std::sin
      (scenario1_gs_U.X[8]);

    /* Saturate: '<S6>/roll' */
    if (rtb_jxk > 0.52359877559829882) {
      rtb_jxk = 0.52359877559829882;
    } else {
      if (rtb_jxk < -0.52359877559829882) {
        rtb_jxk = -0.52359877559829882;
      }
    }

    /* End of Saturate: '<S6>/roll' */

    /* Sum: '<S6>/Sum1' incorporates:
     *  Gain: '<S6>/                    '
     *  SignalConversion: '<S6>/TmpSignal ConversionAt                    Inport1'
     */
    rtb_jxk -= 1.1365283480217869 * rtb_VectorConcatenate[6] +
      0.28178545108770103 * rtb_VectorConcatenate[9];

    /* Fcn: '<Root>/Fcn' incorporates:
     *  Inport: '<Root>/X'
     */
    rtb_ixj = -rtb_kxi * std::sin(scenario1_gs_U.X[8]) + rtb_ixj * std::cos
      (scenario1_gs_U.X[8]);

    /* SignalConversion: '<Root>/TmpSignal ConversionAt                 Inport1' incorporates:
     *  Gain: '<S11>/  '
     *  Gain: '<S11>/                     '
     *  Integrator: '<S11>/Integrator1'
     *  SignalConversion: '<S11>/TmpSignal ConversionAt                     Inport1'
     *  Sum: '<S11>/Sum1'
     */
    rtb_ref_idx_0 = 10.000000000000018 * scenario1_gs_X.Integrator1_CSTATE -
      (12.219481695651957 * rtb_VectorConcatenate[2] + 6.215786645518647 *
       rtb_VectorConcatenate[5]);

    /* Sum: '<S8>/Sum1' incorporates:
     *  Saturate: '<S8>/pitch'
     */
    if (rtb_ixj > 0.52359877559829882) {
      rtb_ixj = 0.52359877559829882;
    } else {
      if (rtb_ixj < -0.52359877559829882) {
        rtb_ixj = -0.52359877559829882;
      }
    }

    /* SignalConversion: '<Root>/TmpSignal ConversionAt                 Inport1' incorporates:
     *  Gain: '<S7>/  '
     *  Gain: '<S7>/                     '
     *  Gain: '<S8>/                    '
     *  Integrator: '<S7>/Integrator1'
     *  SignalConversion: '<S7>/TmpSignal ConversionAt                     Inport1'
     *  SignalConversion: '<S8>/TmpSignal ConversionAt                    Inport1'
     *  Sum: '<S7>/Sum1'
     *  Sum: '<S8>/Sum1'
     */
    rtb_ixj -= 1.2859205994736729 * rtb_VectorConcatenate[7] +
      0.34413551249350854 * rtb_VectorConcatenate[10];
    rtb_kxi = 0.15811388300841925 * scenario1_gs_X.Integrator1_CSTATE_b -
      (0.3035552054947866 * rtb_VectorConcatenate[8] + 0.24395632222527311 *
       rtb_VectorConcatenate[11]);

    /* MATLAB Function: '<Root>/MATLAB Function2' incorporates:
     *  Product: '<Root>/Product3'
     */
    for (i = 0; i < 4; i++) {
      for (z = 0; z < 6; z++) {
        a_1[z + 6 * i] = (a[6 * i + z] * rtb_gamma_n[0] + b_a[6 * i + z] *
                          rtb_gamma_n[1]) + c_a[6 * i + z] * rtb_gamma_n[2];
      }
    }

    /* End of MATLAB Function: '<Root>/MATLAB Function2' */
    /* MATLAB Function 'Actuator_Fault': '<S1>:1' */
    /* '<S1>:1:2' T_f = T; */
    for (i = 0; i < 6; i++) {
      /* Product: '<Root>/Product3' incorporates:
       *  SignalConversion: '<Root>/TmpSignal ConversionAt                 Inport1'
       *  Sum: '<Root>/Sum2'
       */
      rtb_Product_idx_2 = a_1[i + 18] * rtb_kxi + (a_1[i + 12] * rtb_ixj +
        (a_1[i + 6] * rtb_jxk + a_1[i] * rtb_ref_idx_0));

      /* Gain: '<Root>/                 ' incorporates:
       *  SignalConversion: '<Root>/TmpSignal ConversionAt                 Inport1'
       *  Sum: '<Root>/Sum2'
       */
      tmp = scenario1_gs_ConstP._Gain_m[i + 18] * rtb_kxi +
        (scenario1_gs_ConstP._Gain_m[i + 12] * rtb_ixj +
         (scenario1_gs_ConstP._Gain_m[i + 6] * rtb_jxk +
          scenario1_gs_ConstP._Gain_m[i] * rtb_ref_idx_0));

      /* Sum: '<Root>/Sum2' */
      scenario1_gs_B.Sum2[i] = (rtb_Product_idx_2 + tmp) + 2.5179000000000005;

      /* MATLAB Function: '<Root>/Actuator_Fault' */
      rtb_gamma_n[i] = scenario1_gs_B.Sum2[i];
    }

    /* MATLAB Function: '<Root>/Actuator_Fault' */
    /* '<S1>:1:3' if time >= 12 */
    if (rtb_Clock >= 12.0) {
      /* '<S1>:1:4' T1 = T(1)*0.6; */
      /* '<S1>:1:5' T2 = T(2)*1; */
      /* '<S1>:1:6' T3 = T(3)*1; */
      /* '<S1>:1:7' T4 = T(4)*1; */
      /* '<S1>:1:8' T5 = T(5)*1; */
      /* '<S1>:1:9' T6 = T(6)*1; */
      /* '<S1>:1:10' T_f = [T1;T2;T3;T4;T5;T6]; */
      rtb_gamma_n[0] = scenario1_gs_B.Sum2[0] * 0.6;
      rtb_gamma_n[1] = scenario1_gs_B.Sum2[1];
      rtb_gamma_n[2] = scenario1_gs_B.Sum2[2];
      rtb_gamma_n[3] = scenario1_gs_B.Sum2[3];
      rtb_gamma_n[4] = scenario1_gs_B.Sum2[4];
      rtb_gamma_n[5] = scenario1_gs_B.Sum2[5];
    }

    /* Outport: '<Root>/virtual_control' incorporates:
     *  SignalConversion: '<Root>/TmpSignal ConversionAt                 Inport1'
     */
    scenario1_gs_Y.virtual_control[0] = rtb_ref_idx_0;
    scenario1_gs_Y.virtual_control[1] = rtb_jxk;
    scenario1_gs_Y.virtual_control[2] = rtb_ixj;
    scenario1_gs_Y.virtual_control[3] = rtb_kxi;
    for (i = 0; i < 6; i++) {
      /* Sqrt: '<Root>/Sqrt1' incorporates:
       *  Gain: '<Root>/      '
       *  Saturate: '<Root>/Saturation1'
       */
      if (rtb_gamma_n[i] > 8.54858) {
        rtb_ref_idx_0 = 8.54858;
      } else if (rtb_gamma_n[i] < 0.0) {
        rtb_ref_idx_0 = 0.0;
      } else {
        rtb_ref_idx_0 = rtb_gamma_n[i];
      }

      rtb_ref_idx_0 = std::sqrt(116978.4923343994 * rtb_ref_idx_0);

      /* End of Sqrt: '<Root>/Sqrt1' */

      /* Gain: '<Root>/rads_to_RPM' */
      rtb_kxi = 9.5493 * rtb_ref_idx_0;

      /* Gain: '<Root>/mapping_0_200' incorporates:
       *  Constant: '<Root>/Constant '
       *  Sum: '<Root>/Sum3'
       */
      rtb_jxk = (rtb_kxi - 1250.0) * 0.022857142857142857;

      /* Saturate: '<Root>/Saturation' */
      if (rtb_jxk < 0.0) {
        /* Outport: '<Root>/motor_command' */
        scenario1_gs_Y.motor_command[i] = 0.0;
      } else {
        /* Outport: '<Root>/motor_command' */
        scenario1_gs_Y.motor_command[i] = rtb_jxk;
      }

      /* End of Saturate: '<Root>/Saturation' */

      /* Outport: '<Root>/motor_speed' */
      scenario1_gs_Y.motor_speed[i] = rtb_ref_idx_0;

      /* Outport: '<Root>/motor_RPM' */
      scenario1_gs_Y.motor_RPM[i] = rtb_kxi;
    }

    /* MATLAB Function: '<Root>/MATLAB Function' incorporates:
     *  Inport: '<Root>/X0'
     */
    /* MATLAB Function 'MATLAB Function': '<S4>:1' */
    /* '<S4>:1:2' x = X0(1); */
    /* '<S4>:1:2' y = X0(2); */
    /* '<S4>:1:2' z = X0(3); */
    /* '<S4>:1:2' psi = X0(4); */
    /* '<S4>:1:3' if t <= 30 */
    if (rtb_Clock <= 30.0) {
      /* '<S4>:1:4' x = X0(1); */
      rtb_Clock = scenario1_gs_U.X0[0];

      /* '<S4>:1:5' y = X0(2); */
      rtb_ixj = scenario1_gs_U.X0[1];

      /* '<S4>:1:6' z = 1; */
      z = 1;

      /* '<S4>:1:7' psi = X0(4); */
      rtb_kxi = scenario1_gs_U.X0[3];
    } else {
      /* '<S4>:1:8' else */
      /* '<S4>:1:9' x = X0(1); */
      rtb_Clock = scenario1_gs_U.X0[0];

      /* '<S4>:1:10' y = X0(2); */
      rtb_ixj = scenario1_gs_U.X0[1];

      /* '<S4>:1:11' z = 0.0; */
      z = 0;

      /* '<S4>:1:12' psi = X0(4); */
      rtb_kxi = scenario1_gs_U.X0[3];
    }

    /* '<S4>:1:14' ref = [x;y;z;psi]; */
    rtb_ref_idx_0 = rtb_Clock;

    /* Outport: '<Root>/ref' incorporates:
     *  MATLAB Function: '<Root>/MATLAB Function'
     */
    scenario1_gs_Y.ref[0] = rtb_Clock;
    scenario1_gs_Y.ref[1] = rtb_ixj;
    scenario1_gs_Y.ref[2] = z;
    scenario1_gs_Y.ref[3] = rtb_kxi;
    if (rtmIsMajorTimeStep((&scenario1_gs_M))) {
      /* Memory: '<S3>/Memory' */
      for (i = 0; i < 6; i++) {
        scenario1_gs_B.Memory[i] = scenario1_gs_DW.Memory_PreviousInput[i];
      }

      /* End of Memory: '<S3>/Memory' */
    }

    /* Derivative: '<S3>/Derivative' incorporates:
     *  Inport: '<Root>/X'
     */
    if ((scenario1_gs_DW.TimeStampA >= (&scenario1_gs_M)->Timing.t[0]) &&
        (scenario1_gs_DW.TimeStampB >= (&scenario1_gs_M)->Timing.t[0])) {
      rtb_Sum1[0] = 0.0;
      rtb_Sum1[1] = 0.0;
      rtb_Sum1[2] = 0.0;
    } else {
      rtb_Clock = scenario1_gs_DW.TimeStampA;
      lastU = (real_T (*)[3])scenario1_gs_DW.LastUAtTimeA;
      if (scenario1_gs_DW.TimeStampA < scenario1_gs_DW.TimeStampB) {
        if (scenario1_gs_DW.TimeStampB < (&scenario1_gs_M)->Timing.t[0]) {
          rtb_Clock = scenario1_gs_DW.TimeStampB;
          lastU = (real_T (*)[3])scenario1_gs_DW.LastUAtTimeB;
        }
      } else {
        if (scenario1_gs_DW.TimeStampA >= (&scenario1_gs_M)->Timing.t[0]) {
          rtb_Clock = scenario1_gs_DW.TimeStampB;
          lastU = (real_T (*)[3])scenario1_gs_DW.LastUAtTimeB;
        }
      }

      rtb_Clock = (&scenario1_gs_M)->Timing.t[0] - rtb_Clock;
      rtb_Sum1[0] = (scenario1_gs_U.X[9] - (*lastU)[0]) / rtb_Clock;
      rtb_Sum1[1] = (scenario1_gs_U.X[10] - (*lastU)[1]) / rtb_Clock;
      rtb_Sum1[2] = (scenario1_gs_U.X[11] - (*lastU)[2]) / rtb_Clock;
    }

    /* End of Derivative: '<S3>/Derivative' */

    /* Product: '<S3>/Product' incorporates:
     *  Constant: '<S3>/Constant1'
     */
    for (i = 0; i < 3; i++) {
      rtb_Product[i] = scenario1_gs_ConstP.Constant1_Value[i + 6] * rtb_Sum1[2]
        + (scenario1_gs_ConstP.Constant1_Value[i + 3] * rtb_Sum1[1] +
           scenario1_gs_ConstP.Constant1_Value[i] * rtb_Sum1[0]);
    }

    /* End of Product: '<S3>/Product' */

    /* Product: '<S3>/Product1' incorporates:
     *  Constant: '<S3>/Constant1'
     *  Inport: '<Root>/X'
     */
    for (i = 0; i < 3; i++) {
      rtb_Sum1[i] = scenario1_gs_ConstP.Constant1_Value[i + 6] *
        scenario1_gs_U.X[11] + (scenario1_gs_ConstP.Constant1_Value[i + 3] *
        scenario1_gs_U.X[10] + scenario1_gs_ConstP.Constant1_Value[i] *
        scenario1_gs_U.X[9]);
    }

    /* End of Product: '<S3>/Product1' */

    /* Sum: '<S3>/Sum3' incorporates:
     *  Inport: '<Root>/X'
     *  MATLAB Function: '<S3>/MATLAB Function1'
     *  Product: '<S14>/i x k'
     *  Product: '<S14>/j x i'
     *  Product: '<S14>/k x j'
     *  Product: '<S15>/i x j'
     *  Product: '<S15>/j x k'
     *  Product: '<S15>/k x i'
     *  Sum: '<S12>/Sum1'
     */
    /* MATLAB Function 'FDD  /MATLAB Function1': '<S13>:1' */
    /* '<S13>:1:2' arm = 0.215; */
    /* '<S13>:1:2' gra = 9.81; */
    /* '<S13>:1:2' factor = 0.0365; */
    /* '<S13>:1:4' M = [arm/2 arm arm/2; */
    /* '<S13>:1:5'       -sqrt(3)*arm/2 0 sqrt(3)*arm/2; */
    /* '<S13>:1:6'       -factor factor -factor]; */
    /* '<S13>:1:8' diff = [u(1) - u(4) ; */
    /* '<S13>:1:9'         u(2) - u(5) ; */
    /* '<S13>:1:10'         u(3) - u(6) ]; */
    /* '<S13>:1:11' Residu_1_4 = diff - inv(M)*y; */
    rtb_Clock = (scenario1_gs_U.X[10] * rtb_Sum1[2] - scenario1_gs_U.X[11] *
                 rtb_Sum1[1]) + rtb_Product[0];
    rtb_jxk = (scenario1_gs_U.X[11] * rtb_Sum1[0] - scenario1_gs_U.X[9] *
               rtb_Sum1[2]) + rtb_Product[1];
    rtb_Product_idx_2 = (scenario1_gs_U.X[9] * rtb_Sum1[1] - scenario1_gs_U.X[10]
                         * rtb_Sum1[0]) + rtb_Product[2];

    /* MATLAB Function: '<S3>/MATLAB Function1' */
    rtb_Sum1[0] = scenario1_gs_B.Memory[0] - scenario1_gs_B.Memory[3];
    rtb_Sum1[1] = scenario1_gs_B.Memory[1] - scenario1_gs_B.Memory[4];
    rtb_Sum1[2] = scenario1_gs_B.Memory[2] - scenario1_gs_B.Memory[5];
    for (i = 0; i < 3; i++) {
      rtb_Product[i] = rtb_Sum1[i] - (a_0[i + 6] * rtb_Product_idx_2 + (a_0[i +
        3] * rtb_jxk + a_0[i] * rtb_Clock));
    }

    /* Outport: '<Root>/gamma' incorporates:
     *  MATLAB Function: '<S3>/MATLAB Function1'
     */
    /*  Residu_1_4 */
    /* '<S13>:1:14' gamma    = [1-(-Residu_1_4(1) + u(1))/u(1) */
    /* '<S13>:1:15'             1-(-Residu_1_4(2) + u(2))/u(2) */
    /* '<S13>:1:16'             1-(-Residu_1_4(3) + u(3))/u(3)]; */
    scenario1_gs_Y.gamma[0] = 1.0 - (-rtb_Product[0] + scenario1_gs_B.Memory[0])
      / scenario1_gs_B.Memory[0];
    scenario1_gs_Y.gamma[1] = 1.0 - (-rtb_Product[1] + scenario1_gs_B.Memory[1])
      / scenario1_gs_B.Memory[1];
    scenario1_gs_Y.gamma[2] = 1.0 - (-rtb_Product[2] + scenario1_gs_B.Memory[2])
      / scenario1_gs_B.Memory[2];

    /* Sum: '<Root>/Sum1' incorporates:
     *  Inport: '<Root>/X0'
     *  MATLAB Function: '<Root>/MATLAB Function'
     */
    rtb_ref_idx_0 -= scenario1_gs_U.X0[0];
    rtb_Clock = rtb_ixj - scenario1_gs_U.X0[1];
    rtb_ixj = (real_T)z - scenario1_gs_U.X0[2];
    rtb_kxi -= scenario1_gs_U.X0[3];

    /* Saturate: '<S7>/yaw' */
    if (rtb_kxi > 3.1415926535897931) {
      rtb_kxi = 3.1415926535897931;
    } else {
      if (rtb_kxi < -3.1415926535897931) {
        rtb_kxi = -3.1415926535897931;
      }
    }

    /* End of Saturate: '<S7>/yaw' */

    /* Sum: '<S7>/Sum3' */
    rtb_jxk = rtb_kxi - rtb_VectorConcatenate[8];

    /* Saturate: '<S7>/psi_e' */
    if (rtb_jxk > 0.78539816339744828) {
      scenario1_gs_B.psi_e = 0.78539816339744828;
    } else if (rtb_jxk < -0.78539816339744828) {
      scenario1_gs_B.psi_e = -0.78539816339744828;
    } else {
      scenario1_gs_B.psi_e = rtb_jxk;
    }

    /* End of Saturate: '<S7>/psi_e' */

    /* Saturate: '<S9>/x' */
    if (rtb_ref_idx_0 > 1.0) {
      rtb_ref_idx_0 = 1.0;
    } else {
      if (rtb_ref_idx_0 < -1.0) {
        rtb_ref_idx_0 = -1.0;
      }
    }

    /* End of Saturate: '<S9>/x' */

    /* Sum: '<S9>/Sum3' */
    rtb_jxk = rtb_ref_idx_0 - rtb_VectorConcatenate[0];

    /* Saturate: '<S9>/xe' */
    if (rtb_jxk > 1.0) {
      scenario1_gs_B.xe = 1.0;
    } else if (rtb_jxk < -1.0) {
      scenario1_gs_B.xe = -1.0;
    } else {
      scenario1_gs_B.xe = rtb_jxk;
    }

    /* End of Saturate: '<S9>/xe' */

    /* Saturate: '<S10>/y' */
    if (rtb_Clock > 1.0) {
      rtb_Clock = 1.0;
    } else {
      if (rtb_Clock < -1.0) {
        rtb_Clock = -1.0;
      }
    }

    /* End of Saturate: '<S10>/y' */

    /* Sum: '<S10>/Sum3' */
    rtb_jxk = rtb_Clock - rtb_VectorConcatenate[1];

    /* Saturate: '<S10>/ye' */
    if (rtb_jxk > 1.0) {
      scenario1_gs_B.ye = 1.0;
    } else if (rtb_jxk < -1.0) {
      scenario1_gs_B.ye = -1.0;
    } else {
      scenario1_gs_B.ye = rtb_jxk;
    }

    /* End of Saturate: '<S10>/ye' */

    /* Saturate: '<S11>/z' */
    if (rtb_ixj > 1.0) {
      rtb_ixj = 1.0;
    } else {
      if (rtb_ixj < 0.0) {
        rtb_ixj = 0.0;
      }
    }

    /* End of Saturate: '<S11>/z' */

    /* Sum: '<S11>/Sum3' */
    rtb_jxk = rtb_ixj - rtb_VectorConcatenate[2];

    /* Saturate: '<S11>/ze' */
    if (rtb_jxk > 0.5) {
      scenario1_gs_B.ze = 0.5;
    } else if (rtb_jxk < -0.5) {
      scenario1_gs_B.ze = -0.5;
    } else {
      scenario1_gs_B.ze = rtb_jxk;
    }

    /* End of Saturate: '<S11>/ze' */
  }

  if (rtmIsMajorTimeStep((&scenario1_gs_M))) {
    real_T (*lastU)[3];
    int32_T i;
    if (rtmIsMajorTimeStep((&scenario1_gs_M))) {
      /* Update for Memory: '<S3>/Memory' */
      for (i = 0; i < 6; i++) {
        scenario1_gs_DW.Memory_PreviousInput[i] = scenario1_gs_B.Sum2[i];
      }

      /* End of Update for Memory: '<S3>/Memory' */
    }

    /* Update for Derivative: '<S3>/Derivative' incorporates:
     *  Update for Inport: '<Root>/X'
     */
    if (scenario1_gs_DW.TimeStampA == (rtInf)) {
      scenario1_gs_DW.TimeStampA = (&scenario1_gs_M)->Timing.t[0];
      lastU = (real_T (*)[3])scenario1_gs_DW.LastUAtTimeA;
    } else if (scenario1_gs_DW.TimeStampB == (rtInf)) {
      scenario1_gs_DW.TimeStampB = (&scenario1_gs_M)->Timing.t[0];
      lastU = (real_T (*)[3])scenario1_gs_DW.LastUAtTimeB;
    } else if (scenario1_gs_DW.TimeStampA < scenario1_gs_DW.TimeStampB) {
      scenario1_gs_DW.TimeStampA = (&scenario1_gs_M)->Timing.t[0];
      lastU = (real_T (*)[3])scenario1_gs_DW.LastUAtTimeA;
    } else {
      scenario1_gs_DW.TimeStampB = (&scenario1_gs_M)->Timing.t[0];
      lastU = (real_T (*)[3])scenario1_gs_DW.LastUAtTimeB;
    }

    (*lastU)[0] = scenario1_gs_U.X[9];
    (*lastU)[1] = scenario1_gs_U.X[10];
    (*lastU)[2] = scenario1_gs_U.X[11];

    /* End of Update for Derivative: '<S3>/Derivative' */
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep((&scenario1_gs_M))) {
    rt_ertODEUpdateContinuousStates(&(&scenario1_gs_M)->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++(&scenario1_gs_M)->Timing.clockTick0)) {
      ++(&scenario1_gs_M)->Timing.clockTickH0;
    }

    (&scenario1_gs_M)->Timing.t[0] = rtsiGetSolverStopTime(&(&scenario1_gs_M)
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
      (&scenario1_gs_M)->Timing.clockTick1++;
      if (!(&scenario1_gs_M)->Timing.clockTick1) {
        (&scenario1_gs_M)->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void scenario1_gsModelClass::scenario1_gs_derivatives()
{
  XDot_scenario1_gs_T *_rtXdot;
  _rtXdot = ((XDot_scenario1_gs_T *) (&scenario1_gs_M)->derivs);

  /* Derivatives for Integrator: '<S11>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = scenario1_gs_B.ze;

  /* Derivatives for Integrator: '<S9>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_h = scenario1_gs_B.xe;

  /* Derivatives for Integrator: '<S10>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_j = scenario1_gs_B.ye;

  /* Derivatives for Integrator: '<S7>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_b = scenario1_gs_B.psi_e;
}

/* Model initialize function */
void scenario1_gsModelClass::initialize()
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)(&scenario1_gs_M), 0,
                sizeof(RT_MODEL_scenario1_gs_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&(&scenario1_gs_M)->solverInfo, &(&scenario1_gs_M)
                          ->Timing.simTimeStep);
    rtsiSetTPtr(&(&scenario1_gs_M)->solverInfo, &rtmGetTPtr((&scenario1_gs_M)));
    rtsiSetStepSizePtr(&(&scenario1_gs_M)->solverInfo, &(&scenario1_gs_M)
                       ->Timing.stepSize0);
    rtsiSetdXPtr(&(&scenario1_gs_M)->solverInfo, &(&scenario1_gs_M)->derivs);
    rtsiSetContStatesPtr(&(&scenario1_gs_M)->solverInfo, (real_T **)
                         &(&scenario1_gs_M)->contStates);
    rtsiSetNumContStatesPtr(&(&scenario1_gs_M)->solverInfo, &(&scenario1_gs_M)
      ->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&scenario1_gs_M)->solverInfo,
      &(&scenario1_gs_M)->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&scenario1_gs_M)->solverInfo,
      &(&scenario1_gs_M)->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&scenario1_gs_M)->solverInfo,
      &(&scenario1_gs_M)->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&(&scenario1_gs_M)->solverInfo, (&rtmGetErrorStatus
      ((&scenario1_gs_M))));
    rtsiSetRTModelPtr(&(&scenario1_gs_M)->solverInfo, (&scenario1_gs_M));
  }

  rtsiSetSimTimeStep(&(&scenario1_gs_M)->solverInfo, MAJOR_TIME_STEP);
  (&scenario1_gs_M)->intgData.y = (&scenario1_gs_M)->odeY;
  (&scenario1_gs_M)->intgData.f[0] = (&scenario1_gs_M)->odeF[0];
  (&scenario1_gs_M)->intgData.f[1] = (&scenario1_gs_M)->odeF[1];
  (&scenario1_gs_M)->intgData.f[2] = (&scenario1_gs_M)->odeF[2];
  (&scenario1_gs_M)->intgData.f[3] = (&scenario1_gs_M)->odeF[3];
  (&scenario1_gs_M)->intgData.f[4] = (&scenario1_gs_M)->odeF[4];
  (&scenario1_gs_M)->intgData.f[5] = (&scenario1_gs_M)->odeF[5];
  getRTM()->contStates = ((X_scenario1_gs_T *) &scenario1_gs_X);
  rtsiSetSolverData(&(&scenario1_gs_M)->solverInfo, (void *)&(&scenario1_gs_M)
                    ->intgData);
  rtsiSetSolverName(&(&scenario1_gs_M)->solverInfo,"ode5");
  rtmSetTPtr(getRTM(), &(&scenario1_gs_M)->Timing.tArray[0]);
  (&scenario1_gs_M)->Timing.stepSize0 = 0.005;

  /* block I/O */
  (void) memset(((void *) &scenario1_gs_B), 0,
                sizeof(B_scenario1_gs_T));

  /* states (continuous) */
  {
    (void) memset((void *)&scenario1_gs_X, 0,
                  sizeof(X_scenario1_gs_T));
  }

  /* states (dwork) */
  (void) memset((void *)&scenario1_gs_DW, 0,
                sizeof(DW_scenario1_gs_T));

  /* external inputs */
  (void)memset((void *)&scenario1_gs_U, 0, sizeof(ExtU_scenario1_gs_T));

  /* external outputs */
  (void) memset((void *)&scenario1_gs_Y, 0,
                sizeof(ExtY_scenario1_gs_T));

  {
    int32_T i;

    /* InitializeConditions for Integrator: '<S11>/Integrator1' */
    scenario1_gs_X.Integrator1_CSTATE = 0.0;

    /* InitializeConditions for Integrator: '<S9>/Integrator1' */
    scenario1_gs_X.Integrator1_CSTATE_h = 0.0;

    /* InitializeConditions for Integrator: '<S10>/Integrator1' */
    scenario1_gs_X.Integrator1_CSTATE_j = 0.0;

    /* InitializeConditions for Integrator: '<S7>/Integrator1' */
    scenario1_gs_X.Integrator1_CSTATE_b = 0.0;

    /* InitializeConditions for Memory: '<S3>/Memory' */
    for (i = 0; i < 6; i++) {
      scenario1_gs_DW.Memory_PreviousInput[i] = 2.5179000000000005;
    }

    /* End of InitializeConditions for Memory: '<S3>/Memory' */

    /* InitializeConditions for Derivative: '<S3>/Derivative' */
    scenario1_gs_DW.TimeStampA = (rtInf);
    scenario1_gs_DW.TimeStampB = (rtInf);
  }
}

/* Model terminate function */
void scenario1_gsModelClass::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
scenario1_gsModelClass::scenario1_gsModelClass()
{
}

/* Destructor */
scenario1_gsModelClass::~scenario1_gsModelClass()
{
  /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_scenario1_gs_T * scenario1_gsModelClass::getRTM()
{
  return (&scenario1_gs_M);
}
