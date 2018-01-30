/*
 * bsl_hovering.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "bsl_hovering".
 *
 * Model version              : 1.614
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Tue Jan 30 12:45:59 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Passed (1), Warnings (3), Error (0)
 */

#include "bsl_hovering.h"
#include "bsl_hovering_private.h"

static void rate_scheduler(RT_MODEL_bsl_hovering_T *const bsl_hovering_M);

/*
 *   This function updates active task flag for each subrate.
 * The function is called at model base rate, hence the
 * generated code self-manages all its subrates.
 */
static void rate_scheduler(RT_MODEL_bsl_hovering_T *const bsl_hovering_M)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (bsl_hovering_M->Timing.TaskCounters.TID[2])++;
  if ((bsl_hovering_M->Timing.TaskCounters.TID[2]) > 1) {/* Sample time: [0.02s, 0.0s] */
    bsl_hovering_M->Timing.TaskCounters.TID[2] = 0;
  }
}

/*
 * This function updates continuous states using the ODE5 fixed-step
 * solver algorithm
 */
void bsl_hoveringModelClass::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
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
  bsl_hovering_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE5_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[0]);
  rtsiSetdX(si, f1);
  this->step();
  bsl_hovering_derivatives();

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
  bsl_hovering_derivatives();

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
  bsl_hovering_derivatives();

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
  bsl_hovering_derivatives();

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
  bsl_hovering_derivatives();

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

void rt_mrdivide_U1d12x6_U2_zAvshA6O(const real_T u0[72], const real_T u1[36],
  real_T y[72])
{
  int32_T jp;
  real_T temp;
  real_T A[36];
  int8_T ipiv[6];
  int32_T jpiv_offset;
  int32_T j;
  int32_T idxmax;
  int32_T ix;
  real_T s;
  int32_T ijA;
  int32_T jAcol;
  int32_T kBcol;
  memcpy(&A[0], &u1[0], 36U * sizeof(real_T));
  for (j = 0; j < 6; j++) {
    ipiv[j] = (int8_T)(1 + j);
  }

  for (j = 0; j < 5; j++) {
    jp = j * 7 + 2;
    jAcol = j * 7;
    idxmax = 1;
    ix = jp - 2;
    temp = std::abs(A[jAcol]);
    for (jpiv_offset = 2; jpiv_offset <= 6 - j; jpiv_offset++) {
      ix++;
      s = std::abs(A[ix]);
      if (s > temp) {
        idxmax = jpiv_offset;
        temp = s;
      }
    }

    jpiv_offset = idxmax - 1;
    if (A[(jp + jpiv_offset) - 2] != 0.0) {
      if (jpiv_offset != 0) {
        ipiv[j] = (int8_T)((j + jpiv_offset) + 1);
        ix = j;
        kBcol = j + jpiv_offset;
        for (jpiv_offset = 0; jpiv_offset < 6; jpiv_offset++) {
          temp = A[ix];
          A[ix] = A[kBcol];
          A[kBcol] = temp;
          ix += 6;
          kBcol += 6;
        }
      }

      jpiv_offset = jp - j;
      for (ix = jp - 1; ix + 1 <= jpiv_offset + 4; ix++) {
        A[ix] /= A[jAcol];
      }
    }

    kBcol = jAcol;
    jAcol += 6;
    for (idxmax = 1; idxmax <= 5 - j; idxmax++) {
      if (A[jAcol] != 0.0) {
        temp = -A[jAcol];
        ix = jp - 1;
        jpiv_offset = kBcol - j;
        for (ijA = kBcol + 7; ijA + 1 <= jpiv_offset + 12; ijA++) {
          A[ijA] += A[ix] * temp;
          ix++;
        }
      }

      jAcol += 6;
      kBcol += 6;
    }
  }

  memcpy(&y[0], &u0[0], 72U * sizeof(real_T));
  for (j = 0; j < 6; j++) {
    jp = 12 * j;
    jAcol = 6 * j;
    for (jpiv_offset = 0; jpiv_offset + 1 <= j; jpiv_offset++) {
      kBcol = 12 * jpiv_offset;
      if (A[jpiv_offset + jAcol] != 0.0) {
        for (ix = 0; ix < 12; ix++) {
          y[ix + jp] -= A[jpiv_offset + jAcol] * y[ix + kBcol];
        }
      }
    }

    temp = 1.0 / A[j + jAcol];
    for (ix = 0; ix < 12; ix++) {
      y[ix + jp] *= temp;
    }
  }

  for (j = 5; j >= 0; j += -1) {
    jp = 12 * j;
    jAcol = 6 * j;
    for (jpiv_offset = j + 1; jpiv_offset + 1 < 7; jpiv_offset++) {
      kBcol = 12 * jpiv_offset;
      if (A[jpiv_offset + jAcol] != 0.0) {
        for (ix = 0; ix < 12; ix++) {
          y[ix + jp] -= A[jpiv_offset + jAcol] * y[ix + kBcol];
        }
      }
    }
  }

  for (j = 4; j >= 0; j += -1) {
    if (j + 1 != ipiv[j]) {
      jp = ipiv[j] - 1;
      for (ix = 0; ix < 12; ix++) {
        temp = y[12 * j + ix];
        y[ix + 12 * j] = y[12 * jp + ix];
        y[ix + 12 * jp] = temp;
      }
    }
  }
}

void rt_mrdivided6x6_snf(const real_T u0[36], const real_T u1[36], real_T y[36])
{
  int32_T jp;
  real_T temp;
  real_T A[36];
  int8_T ipiv[6];
  int32_T jpiv_offset;
  int32_T j;
  int32_T idxmax;
  int32_T ix;
  real_T s;
  int32_T ijA;
  int32_T jAcol;
  int32_T kBcol;
  memcpy(&A[0], &u1[0], 36U * sizeof(real_T));
  for (j = 0; j < 6; j++) {
    ipiv[j] = (int8_T)(1 + j);
  }

  for (j = 0; j < 5; j++) {
    jp = j * 7 + 2;
    jAcol = j * 7;
    idxmax = 1;
    ix = jp - 2;
    temp = std::abs(A[jAcol]);
    for (jpiv_offset = 2; jpiv_offset <= 6 - j; jpiv_offset++) {
      ix++;
      s = std::abs(A[ix]);
      if (s > temp) {
        idxmax = jpiv_offset;
        temp = s;
      }
    }

    jpiv_offset = idxmax - 1;
    if (A[(jp + jpiv_offset) - 2] != 0.0) {
      if (jpiv_offset != 0) {
        ipiv[j] = (int8_T)((j + jpiv_offset) + 1);
        ix = j;
        kBcol = j + jpiv_offset;
        for (jpiv_offset = 0; jpiv_offset < 6; jpiv_offset++) {
          temp = A[ix];
          A[ix] = A[kBcol];
          A[kBcol] = temp;
          ix += 6;
          kBcol += 6;
        }
      }

      jpiv_offset = jp - j;
      for (ix = jp - 1; ix + 1 <= jpiv_offset + 4; ix++) {
        A[ix] /= A[jAcol];
      }
    }

    kBcol = jAcol;
    jAcol += 6;
    for (idxmax = 1; idxmax <= 5 - j; idxmax++) {
      if (A[jAcol] != 0.0) {
        temp = -A[jAcol];
        ix = jp - 1;
        jpiv_offset = kBcol - j;
        for (ijA = kBcol + 7; ijA + 1 <= jpiv_offset + 12; ijA++) {
          A[ijA] += A[ix] * temp;
          ix++;
        }
      }

      jAcol += 6;
      kBcol += 6;
    }
  }

  memcpy(&y[0], &u0[0], 36U * sizeof(real_T));
  for (j = 0; j < 6; j++) {
    jp = 6 * j;
    jAcol = 6 * j;
    for (jpiv_offset = 0; jpiv_offset + 1 <= j; jpiv_offset++) {
      kBcol = 6 * jpiv_offset;
      if (A[jpiv_offset + jAcol] != 0.0) {
        for (ix = 0; ix < 6; ix++) {
          y[ix + jp] -= A[jpiv_offset + jAcol] * y[ix + kBcol];
        }
      }
    }

    temp = 1.0 / A[j + jAcol];
    for (ix = 0; ix < 6; ix++) {
      y[ix + jp] *= temp;
    }
  }

  for (j = 5; j >= 0; j += -1) {
    jp = 6 * j;
    jAcol = 6 * j;
    for (jpiv_offset = j + 1; jpiv_offset + 1 < 7; jpiv_offset++) {
      kBcol = 6 * jpiv_offset;
      if (A[jpiv_offset + jAcol] != 0.0) {
        for (ix = 0; ix < 6; ix++) {
          y[ix + jp] -= A[jpiv_offset + jAcol] * y[ix + kBcol];
        }
      }
    }
  }

  for (j = 4; j >= 0; j += -1) {
    if (j + 1 != ipiv[j]) {
      jp = ipiv[j] - 1;
      for (ix = 0; ix < 6; ix++) {
        temp = y[6 * j + ix];
        y[ix + 6 * j] = y[6 * jp + ix];
        y[ix + 6 * jp] = temp;
      }
    }
  }
}

/* Model step function */
void bsl_hoveringModelClass::step()
{
  /* local block i/o variables */
  real_T rtb_P_tildle_x_k1[144];
  real_T rtb_Sum1_a[72];
  real_T rtb_P_gamma_k1[36];
  if (rtmIsMajorTimeStep((&bsl_hovering_M))) {
    /* set solver stop time */
    if (!((&bsl_hovering_M)->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&(&bsl_hovering_M)->solverInfo, (((&bsl_hovering_M
        )->Timing.clockTickH0 + 1) * (&bsl_hovering_M)->Timing.stepSize0 *
        4294967296.0));
    } else {
      rtsiSetSolverStopTime(&(&bsl_hovering_M)->solverInfo, (((&bsl_hovering_M
        )->Timing.clockTick0 + 1) * (&bsl_hovering_M)->Timing.stepSize0 +
        (&bsl_hovering_M)->Timing.clockTickH0 * (&bsl_hovering_M)
        ->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep((&bsl_hovering_M))) {
    (&bsl_hovering_M)->Timing.t[0] = rtsiGetT(&(&bsl_hovering_M)->solverInfo);
  }

  {
    real_T rtb_T_f[6];
    real_T rtb_Clock;
    real_T rtb_P_gamma_k1k[36];
    real_T rtb_Product2_o[72];
    real_T rtb_H_k1k[36];
    real_T rtb_Sum4[144];
    real_T rtb_Product3[144];
    real_T rtb_Divide[72];
    real_T rtb_Product5[36];
    real_T rtb_H_k1k_0[36];
    real_T rtb_Product2_e[72];
    int32_T i;
    int32_T i_0;
    real_T rtb_Divide_0[72];
    real_T rtb_Product2_e_0[144];
    real_T rtb_Divide_1[144];
    real_T rtb_Sum4_0[72];
    real_T tmp[36];
    real_T rtb_H_k1k_1[36];
    real_T tmp_0[12];
    real_T tmp_1[12];
    real_T tmp_2[6];
    int32_T i_1;
    real_T rtb_Product1;
    real_T tmp_3;
    real_T u0;

    /* Clock: '<Root>/Clock' */
    rtb_Clock = (&bsl_hovering_M)->Timing.t[0];

    /* RateTransition: '<Root>/Rate Transition4' incorporates:
     *  Inport: '<Root>/X'
     */
    if ((rtmIsMajorTimeStep((&bsl_hovering_M)) &&
         (&bsl_hovering_M)->Timing.TaskCounters.TID[1] == 0) &&
        (rtmIsMajorTimeStep((&bsl_hovering_M)) &&
         (&bsl_hovering_M)->Timing.TaskCounters.TID[2] == 0)) {
      memcpy(&bsl_hovering_B.RateTransition4[0], &bsl_hovering_U.X[0], 12U *
             sizeof(real_T));
    }

    /* End of RateTransition: '<Root>/Rate Transition4' */
    if (rtmIsMajorTimeStep((&bsl_hovering_M)) &&
        (&bsl_hovering_M)->Timing.TaskCounters.TID[2] == 0) {
      /* Gain: '<S9>/                     ' incorporates:
       *  SignalConversion: '<S9>/TmpSignal ConversionAt                     Inport1'
       */
      bsl_hovering_B.u = 12.219481695651957 * bsl_hovering_B.RateTransition4[2]
        + 6.215786645518647 * bsl_hovering_B.RateTransition4[5];
    }

    /* Sum: '<S9>/Sum1' incorporates:
     *  Gain: '<S9>/  '
     *  Integrator: '<S9>/Integrator1'
     */
    bsl_hovering_B.Sum1 = 10.000000000000018 * bsl_hovering_X.Integrator1_CSTATE
      - bsl_hovering_B.u;
    if (rtmIsMajorTimeStep((&bsl_hovering_M)) &&
        (&bsl_hovering_M)->Timing.TaskCounters.TID[2] == 0) {
      /* ZeroOrderHold: '<Root>/Zero-Order Hold2' */
      bsl_hovering_B.ZeroOrderHold2 = bsl_hovering_B.Sum1;

      /* Gain: '<S7>/                    ' incorporates:
       *  SignalConversion: '<S7>/TmpSignal ConversionAt                    Inport1'
       */
      bsl_hovering_B.u_o = 0.32349951352987977 * bsl_hovering_B.RateTransition4
        [0] + 0.2732366014912751 * bsl_hovering_B.RateTransition4[3];
    }

    /* Sum: '<S7>/Sum1' incorporates:
     *  Gain: '<S7>/ '
     *  Integrator: '<S7>/Integrator1'
     */
    bsl_hovering_B.Sum1_l = 0.17320508075688992 *
      bsl_hovering_X.Integrator1_CSTATE_d - bsl_hovering_B.u_o;
    if (rtmIsMajorTimeStep((&bsl_hovering_M)) &&
        (&bsl_hovering_M)->Timing.TaskCounters.TID[2] == 0) {
      /* ZeroOrderHold: '<Root>/Zero-Order Hold' */
      bsl_hovering_B.ZeroOrderHold = bsl_hovering_B.Sum1_l;

      /* Gain: '<S8>/                     ' incorporates:
       *  SignalConversion: '<S8>/TmpSignal ConversionAt                     Inport1'
       */
      bsl_hovering_B.u_m = -0.31312578517366968 *
        bsl_hovering_B.RateTransition4[1] + -0.25417198201077484 *
        bsl_hovering_B.RateTransition4[4];
    }

    /* Sum: '<S8>/Sum1' incorporates:
     *  Gain: '<S8>/  '
     *  Integrator: '<S8>/Integrator1'
     */
    bsl_hovering_B.Sum1_lg = -0.173205080756885 *
      bsl_hovering_X.Integrator1_CSTATE_j - bsl_hovering_B.u_m;
    if (rtmIsMajorTimeStep((&bsl_hovering_M)) &&
        (&bsl_hovering_M)->Timing.TaskCounters.TID[2] == 0) {
      /* ZeroOrderHold: '<Root>/Zero-Order Hold1' */
      bsl_hovering_B.ZeroOrderHold1 = bsl_hovering_B.Sum1_lg;

      /* Gain: '<S5>/                     ' incorporates:
       *  SignalConversion: '<S5>/TmpSignal ConversionAt                     Inport1'
       */
      bsl_hovering_B.u_d = 0.3035552054947866 * bsl_hovering_B.RateTransition4[8]
        + 0.24395632222527311 * bsl_hovering_B.RateTransition4[11];
    }

    /* Sum: '<S5>/Sum1' incorporates:
     *  Gain: '<S5>/  '
     *  Integrator: '<S5>/Integrator1'
     */
    bsl_hovering_B.Sum1_o = 0.15811388300841925 *
      bsl_hovering_X.Integrator1_CSTATE_a - bsl_hovering_B.u_d;
    if (rtmIsMajorTimeStep((&bsl_hovering_M)) &&
        (&bsl_hovering_M)->Timing.TaskCounters.TID[2] == 0) {
      /* ZeroOrderHold: '<Root>/Zero-Order Hold3' */
      bsl_hovering_B.ZeroOrderHold3 = bsl_hovering_B.Sum1_o;
    }

    /* Sum: '<S4>/Sum1' incorporates:
     *  Fcn: '<Root>/Fcn1'
     *  Inport: '<Root>/X'
     *  Saturate: '<S4>/roll'
     */
    u0 = bsl_hovering_B.ZeroOrderHold1 * std::cos(bsl_hovering_U.X[8]) +
      bsl_hovering_B.ZeroOrderHold * std::sin(bsl_hovering_U.X[8]);
    if (u0 > 0.52359877559829882) {
      u0 = 0.52359877559829882;
    } else {
      if (u0 < -0.52359877559829882) {
        u0 = -0.52359877559829882;
      }
    }

    /* Sum: '<Root>/Sum2' incorporates:
     *  Gain: '<S4>/                    '
     *  Inport: '<Root>/X'
     *  SignalConversion: '<S4>/TmpSignal ConversionAt                    Inport1'
     *  Sum: '<S4>/Sum1'
     */
    tmp_3 = u0 - (1.1365283480217869 * bsl_hovering_U.X[6] + 0.28178545108770103
                  * bsl_hovering_U.X[9]);

    /* Sum: '<S6>/Sum1' incorporates:
     *  Fcn: '<Root>/Fcn'
     *  Inport: '<Root>/X'
     *  Saturate: '<S6>/pitch'
     */
    u0 = -bsl_hovering_B.ZeroOrderHold1 * std::sin(bsl_hovering_U.X[8]) +
      bsl_hovering_B.ZeroOrderHold * std::cos(bsl_hovering_U.X[8]);
    if (u0 > 0.52359877559829882) {
      u0 = 0.52359877559829882;
    } else {
      if (u0 < -0.52359877559829882) {
        u0 = -0.52359877559829882;
      }
    }

    /* Sum: '<Root>/Sum2' incorporates:
     *  Gain: '<S6>/                    '
     *  Inport: '<Root>/X'
     *  SignalConversion: '<S6>/TmpSignal ConversionAt                    Inport1'
     *  Sum: '<S6>/Sum1'
     */
    u0 -= 1.2859205994736729 * bsl_hovering_U.X[7] + 0.34413551249350854 *
      bsl_hovering_U.X[10];

    /* MATLAB Function 'Actuator_Fault': '<S1>:1' */
    /* '<S1>:1:2' T_f = T; */
    for (i = 0; i < 6; i++) {
      /* Gain: '<Root>/                 ' incorporates:
       *  Sum: '<Root>/Sum2'
       */
      bsl_hovering_B.u_dq[i] = 0.0;
      bsl_hovering_B.u_dq[i] += (bsl_hovering_B.ZeroOrderHold2 +
        15.107400000000002) * bsl_hovering_ConstP._Gain_dz[i];
      bsl_hovering_B.u_dq[i] += bsl_hovering_ConstP._Gain_dz[i + 6] * tmp_3;
      bsl_hovering_B.u_dq[i] += bsl_hovering_ConstP._Gain_dz[i + 12] * u0;
      bsl_hovering_B.u_dq[i] += bsl_hovering_ConstP._Gain_dz[i + 18] *
        bsl_hovering_B.ZeroOrderHold3;

      /* MATLAB Function: '<Root>/Actuator_Fault' */
      rtb_T_f[i] = bsl_hovering_B.u_dq[i];
    }

    /* MATLAB Function: '<Root>/Actuator_Fault' */
    /* '<S1>:1:3' if time >= 30 */
    if (rtb_Clock >= 30.0) {
      /* '<S1>:1:4' T1 = T(1); */
      /* '<S1>:1:5' T2 = T(2); */
      /* '<S1>:1:6' T3 = T(3); */
      /* '<S1>:1:7' T4 = T(4)*0.85; */
      /* '<S1>:1:8' T5 = T(5); */
      /* '<S1>:1:9' T6 = T(6); */
      /* '<S1>:1:10' T_f = [T1;T2;T3;T4;T5;T6]; */
      rtb_T_f[0] = bsl_hovering_B.u_dq[0];
      rtb_T_f[1] = bsl_hovering_B.u_dq[1];
      rtb_T_f[2] = bsl_hovering_B.u_dq[2];
      rtb_T_f[3] = bsl_hovering_B.u_dq[3] * 0.85;
      rtb_T_f[4] = bsl_hovering_B.u_dq[4];
      rtb_T_f[5] = bsl_hovering_B.u_dq[5];
    }

    /* Outport: '<Root>/virtual_control' incorporates:
     *  Sum: '<Root>/Sum2'
     */
    bsl_hovering_Y.virtual_control[0] = bsl_hovering_B.ZeroOrderHold2 +
      15.107400000000002;
    bsl_hovering_Y.virtual_control[1] = tmp_3;
    bsl_hovering_Y.virtual_control[2] = u0;
    bsl_hovering_Y.virtual_control[3] = bsl_hovering_B.ZeroOrderHold3;
    for (i = 0; i < 6; i++) {
      /* Sqrt: '<Root>/Sqrt1' incorporates:
       *  Gain: '<Root>/      '
       */
      tmp_3 = std::sqrt(116978.4923343994 * rtb_T_f[i]);

      /* Gain: '<Root>/rads_to_RPM' */
      rtb_Product1 = 9.5493 * tmp_3;

      /* Gain: '<Root>/mapping_0_200' incorporates:
       *  Constant: '<Root>/Constant '
       *  Sum: '<Root>/Sum3'
       */
      u0 = (rtb_Product1 - 1250.0) * 0.022857142857142857;

      /* Saturate: '<Root>/Saturation' */
      if (u0 > 200.0) {
        /* Outport: '<Root>/motor_command' */
        bsl_hovering_Y.motor_command[i] = 200.0;
      } else if (u0 < 0.0) {
        /* Outport: '<Root>/motor_command' */
        bsl_hovering_Y.motor_command[i] = 0.0;
      } else {
        /* Outport: '<Root>/motor_command' */
        bsl_hovering_Y.motor_command[i] = u0;
      }

      /* End of Saturate: '<Root>/Saturation' */

      /* Outport: '<Root>/motor_speed' */
      bsl_hovering_Y.motor_speed[i] = tmp_3;

      /* Outport: '<Root>/motor_RPM' */
      bsl_hovering_Y.motor_RPM[i] = rtb_Product1;
    }

    /* MATLAB Function: '<Root>/MATLAB Function' */
    /* MATLAB Function 'MATLAB Function': '<S2>:1' */
    /* '<S2>:1:2' x = 0; */
    /* '<S2>:1:2' y = 0; */
    /* '<S2>:1:2' z = 0; */
    /* '<S2>:1:2' psi = 0; */
    /* '<S2>:1:3' if t <= 60 */
    if (rtb_Clock <= 60.0) {
      /* '<S2>:1:4' x = 0; */
      /* '<S2>:1:5' y = 0; */
      /* '<S2>:1:6' z = 0.75; */
      rtb_Clock = 0.75;

      /* '<S2>:1:7' psi = 0; */
    } else {
      /* '<S2>:1:8' else */
      /* '<S2>:1:9' x = 0; */
      /* '<S2>:1:10' y = 0; */
      /* '<S2>:1:11' z = 0; */
      rtb_Clock = 0.0;

      /* '<S2>:1:12' psi = 0; */
    }

    /* '<S2>:1:14' ref = [x;y;z;psi]; */
    bsl_hovering_B.ref[0] = 0.0;
    bsl_hovering_B.ref[1] = 0.0;
    bsl_hovering_B.ref[2] = rtb_Clock;
    bsl_hovering_B.ref[3] = 0.0;

    /* End of MATLAB Function: '<Root>/MATLAB Function' */

    /* Outport: '<Root>/ref' */
    bsl_hovering_Y.ref[0] = bsl_hovering_B.ref[0];
    bsl_hovering_Y.ref[1] = bsl_hovering_B.ref[1];
    bsl_hovering_Y.ref[2] = bsl_hovering_B.ref[2];
    bsl_hovering_Y.ref[3] = bsl_hovering_B.ref[3];
    if (rtmIsMajorTimeStep((&bsl_hovering_M)) &&
        (&bsl_hovering_M)->Timing.TaskCounters.TID[1] == 0) {
      /* UnitDelay: '<S13>/       ' */
      for (i = 0; i < 6; i++) {
        bsl_hovering_B.gamma_hat_k1k[i] = bsl_hovering_DW._DSTATE[i];
      }

      /* End of UnitDelay: '<S13>/       ' */
      for (i = 0; i < 36; i++) {
        /* Sum: '<S13>/Sum3' incorporates:
         *  Constant: '<S13>/Q_gamma'
         *  UnitDelay: '<S13>/Unit Delay1'
         */
        rtb_P_gamma_k1k[i] = bsl_hovering_ConstP.Q_gamma_Value[i] +
          bsl_hovering_DW.UnitDelay1_DSTATE[i];

        /* S-Function (sdspdiag2): '<S11>/Create Diagonal Matrix' */
        rtb_H_k1k[i] = 0.0;
      }

      /* S-Function (sdspdiag2): '<S11>/Create Diagonal Matrix' incorporates:
       *  Memory: '<Root>/Memory1'
       */
      for (i = 0; i < 6; i++) {
        rtb_H_k1k[i * 7] = bsl_hovering_DW.Memory1_PreviousInput[i];
      }

      for (i_0 = 0; i_0 < 6; i_0++) {
        for (i = 0; i < 12; i++) {
          /* Product: '<S11>/Product7' incorporates:
           *  Constant: '<S11>/     '
           *  Sum: '<S11>/Sum4'
           *  UnitDelay: '<S11>/Unit Delay'
           */
          rtb_Product2_e[i + 12 * i_0] = 0.0;
          for (i_1 = 0; i_1 < 12; i_1++) {
            rtb_Product2_e[i + 12 * i_0] += bsl_hovering_ConstP.pooled5[12 * i_1
              + i] * bsl_hovering_DW.UnitDelay_DSTATE[12 * i_0 + i_1];
          }

          /* End of Product: '<S11>/Product7' */

          /* Product: '<S11>/Product3' incorporates:
           *  Constant: '<S11>/          '
           *  Sum: '<S11>/Sum4'
           */
          rtb_Divide[i + 12 * i_0] = 0.0;
          for (i_1 = 0; i_1 < 6; i_1++) {
            rtb_Divide[i + 12 * i_0] += bsl_hovering_ConstP.pooled6[12 * i_1 + i]
              * rtb_H_k1k[6 * i_0 + i_1];
          }

          /* End of Product: '<S11>/Product3' */
        }
      }

      /* Sum: '<S11>/Sum4' */
      for (i_0 = 0; i_0 < 6; i_0++) {
        for (i = 0; i < 12; i++) {
          rtb_Product2_o[i + 12 * i_0] = rtb_Product2_e[12 * i_0 + i] -
            rtb_Divide[12 * i_0 + i];
        }
      }

      /* Product: '<S11>/Product1' incorporates:
       *  UnitDelay: '<S13>/Unit Delay1'
       */
      for (i_0 = 0; i_0 < 6; i_0++) {
        for (i = 0; i < 12; i++) {
          rtb_Product2_e[i + 12 * i_0] = 0.0;
          for (i_1 = 0; i_1 < 6; i_1++) {
            rtb_Product2_e[i + 12 * i_0] += rtb_Product2_o[12 * i_1 + i] *
              bsl_hovering_DW.UnitDelay1_DSTATE[6 * i_0 + i_1];
          }
        }
      }

      /* End of Product: '<S11>/Product1' */

      /* Product: '<S11>/Divide' */
      rt_mrdivide_U1d12x6_U2_zAvshA6O(rtb_Product2_e, rtb_P_gamma_k1k,
        rtb_Divide);

      /* Product: '<S11>/Product4' incorporates:
       *  Constant: '<S11>/                      '
       */
      for (i_0 = 0; i_0 < 6; i_0++) {
        for (i = 0; i < 6; i++) {
          rtb_H_k1k[i + 6 * i_0] = 0.0;
          for (i_1 = 0; i_1 < 12; i_1++) {
            rtb_H_k1k[i + 6 * i_0] += bsl_hovering_ConstP.pooled4[6 * i_1 + i] *
              rtb_Divide[12 * i_0 + i_1];
          }
        }
      }

      /* End of Product: '<S11>/Product4' */

      /* Product: '<S13>/Product3' incorporates:
       *  Math: '<S13>/Transpose'
       */
      for (i_0 = 0; i_0 < 6; i_0++) {
        for (i = 0; i < 6; i++) {
          rtb_Product5[i_0 + 6 * i] = 0.0;
          for (i_1 = 0; i_1 < 6; i_1++) {
            rtb_Product5[i_0 + 6 * i] += rtb_P_gamma_k1k[6 * i_1 + i_0] *
              rtb_H_k1k[6 * i_1 + i];
          }
        }
      }

      /* End of Product: '<S13>/Product3' */
      for (i_0 = 0; i_0 < 12; i_0++) {
        /* Gain: '<S10>/A1' incorporates:
         *  UnitDelay: '<S10>/Unit Delay1'
         */
        for (i = 0; i < 12; i++) {
          rtb_Product3[i_0 + 12 * i] = 0.0;
          for (i_1 = 0; i_1 < 12; i_1++) {
            rtb_Product3[i_0 + 12 * i] += bsl_hovering_ConstP.pooled5[12 * i_1 +
              i_0] * bsl_hovering_DW.UnitDelay1_DSTATE_e[12 * i + i_1];
          }
        }

        /* End of Gain: '<S10>/A1' */
        for (i = 0; i < 6; i++) {
          /* Product: '<S10>/Product1' incorporates:
           *  Product: '<S10>/Product4'
           */
          rtb_Product2_e[i_0 + 12 * i] = 0.0;

          /* Product: '<S10>/Product5' incorporates:
           *  Product: '<S10>/Product6'
           */
          rtb_Divide_0[i_0 + 12 * i] = 0.0;
          for (i_1 = 0; i_1 < 6; i_1++) {
            /* Product: '<S10>/Product1' incorporates:
             *  Product: '<S10>/Product4'
             *  UnitDelay: '<S13>/Unit Delay1'
             */
            rtb_Product2_e[i_0 + 12 * i] += rtb_Product2_o[12 * i_1 + i_0] *
              bsl_hovering_DW.UnitDelay1_DSTATE[6 * i + i_1];

            /* Product: '<S10>/Product5' incorporates:
             *  Product: '<S10>/Product6'
             */
            rtb_Divide_0[i_0 + 12 * i] += rtb_Divide[12 * i_1 + i_0] *
              rtb_P_gamma_k1k[6 * i + i_1];
          }
        }

        for (i = 0; i < 12; i++) {
          /* Product: '<S10>/Product4' incorporates:
           *  Math: '<S10>/Transpose'
           *  Sum: '<S10>/Sum9'
           */
          rtb_Product2_e_0[i_0 + 12 * i] = 0.0;

          /* Product: '<S10>/Product6' incorporates:
           *  Math: '<S10>/Transpose1'
           *  Sum: '<S10>/Sum9'
           */
          rtb_Divide_1[i_0 + 12 * i] = 0.0;
          for (i_1 = 0; i_1 < 6; i_1++) {
            /* Product: '<S10>/Product4' incorporates:
             *  Math: '<S10>/Transpose'
             *  Sum: '<S10>/Sum9'
             */
            rtb_Product2_e_0[i_0 + 12 * i] += rtb_Product2_e[12 * i_1 + i_0] *
              rtb_Product2_o[12 * i_1 + i];

            /* Product: '<S10>/Product6' incorporates:
             *  Math: '<S10>/Transpose1'
             *  Sum: '<S10>/Sum9'
             */
            rtb_Divide_1[i_0 + 12 * i] += rtb_Divide_0[12 * i_1 + i_0] *
              rtb_Divide[12 * i_1 + i];
          }

          /* Sum: '<S10>/Sum4' incorporates:
           *  Constant: '<S10>/Q_x'
           *  Gain: '<S10>/A''
           *  Sum: '<S10>/Sum2'
           *  Sum: '<S10>/Sum9'
           */
          rtb_Clock = 0.0;
          for (i_1 = 0; i_1 < 12; i_1++) {
            rtb_Clock += rtb_Product3[12 * i_1 + i_0] *
              bsl_hovering_ConstP.A_Gain[12 * i + i_1];
          }

          rtb_Sum4[i_0 + 12 * i] = ((rtb_Product2_e_0[12 * i + i_0] -
            rtb_Divide_1[12 * i + i_0]) + rtb_Clock) +
            bsl_hovering_ConstP.Q_x_Value[12 * i + i_0];

          /* End of Sum: '<S10>/Sum4' */
        }

        /* Product: '<S14>/Product1' incorporates:
         *  Product: '<S14>/Product7'
         */
        for (i = 0; i < 6; i++) {
          rtb_Sum4_0[i_0 + 12 * i] = 0.0;
          for (i_1 = 0; i_1 < 12; i_1++) {
            rtb_Sum4_0[i_0 + 12 * i] += rtb_Sum4[12 * i_1 + i_0] *
              bsl_hovering_ConstB.Transpose[12 * i + i_1];
          }
        }

        /* End of Product: '<S14>/Product1' */
      }

      for (i_0 = 0; i_0 < 6; i_0++) {
        for (i = 0; i < 6; i++) {
          /* Product: '<S13>/Product4' incorporates:
           *  Sum: '<S13>/Sum2'
           */
          rtb_H_k1k_0[i + 6 * i_0] = 0.0;
          for (i_1 = 0; i_1 < 6; i_1++) {
            rtb_H_k1k_0[i + 6 * i_0] += rtb_H_k1k[6 * i_1 + i] * rtb_Product5[6 *
              i_0 + i_1];
          }

          /* End of Product: '<S13>/Product4' */

          /* Sum: '<S14>/Sum1' incorporates:
           *  Constant: '<S14>/     '
           *  Constant: '<S14>/R'
           *  Product: '<S14>/Product7'
           *  Sum: '<S13>/Sum2'
           */
          rtb_Clock = 0.0;
          for (i_1 = 0; i_1 < 12; i_1++) {
            rtb_Clock += bsl_hovering_ConstP.pooled4[6 * i_1 + i] * rtb_Sum4_0
              [12 * i_0 + i_1];
          }

          tmp[i + 6 * i_0] = bsl_hovering_ConstP.pooled7[6 * i_0 + i] +
            rtb_Clock;

          /* End of Sum: '<S14>/Sum1' */
        }
      }

      /* Sum: '<S13>/Sum2' */
      for (i_0 = 0; i_0 < 6; i_0++) {
        for (i = 0; i < 6; i++) {
          rtb_H_k1k_1[i + 6 * i_0] = rtb_H_k1k_0[6 * i_0 + i] + tmp[6 * i_0 + i];
        }
      }

      memcpy(&rtb_H_k1k_0[0], &rtb_H_k1k_1[0], 36U * sizeof(real_T));

      /* Product: '<S13>/Divide' */
      rt_mrdivided6x6_snf(rtb_Product5, rtb_H_k1k_0, bsl_hovering_B.K_gamma_k1);

      /* Product: '<S13>/Product' */
      for (i_0 = 0; i_0 < 6; i_0++) {
        bsl_hovering_B.Product[i_0] = 0.0;
        for (i = 0; i < 6; i++) {
          bsl_hovering_B.Product[i_0] += rtb_H_k1k[6 * i + i_0] *
            bsl_hovering_B.gamma_hat_k1k[i];
        }
      }

      /* End of Product: '<S13>/Product' */

      /* Sum: '<S10>/Sum8' */
      for (i_0 = 0; i_0 < 72; i_0++) {
        rtb_Product2_o[i_0] -= rtb_Divide[i_0];
      }

      /* End of Sum: '<S10>/Sum8' */
      for (i_0 = 0; i_0 < 12; i_0++) {
        /* Gain: '<S10>/A' incorporates:
         *  Sum: '<S10>/Sum'
         *  UnitDelay: '<S10>/Unit Delay'
         */
        tmp_0[i_0] = 0.0;
        for (i = 0; i < 12; i++) {
          tmp_0[i_0] += bsl_hovering_ConstP.pooled5[12 * i + i_0] *
            bsl_hovering_DW.UnitDelay_DSTATE_i[i];
        }

        /* End of Gain: '<S10>/A' */

        /* Gain: '<S10>/B' incorporates:
         *  Sum: '<S10>/Sum'
         */
        tmp_1[i_0] = 0.0;

        /* Sum: '<S10>/Sum1' */
        rtb_Clock = 0.0;
        for (i = 0; i < 6; i++) {
          /* Sum: '<S10>/Sum1' incorporates:
           *  Product: '<S10>/Product'
           */
          rtb_Clock += rtb_Product2_o[12 * i + i_0] *
            bsl_hovering_B.gamma_hat_k1k[i];

          /* Gain: '<S10>/B' incorporates:
           *  Memory: '<Root>/Memory1'
           *  Sum: '<S10>/Sum'
           */
          tmp_1[i_0] += bsl_hovering_ConstP.pooled6[12 * i + i_0] *
            bsl_hovering_DW.Memory1_PreviousInput[i];
        }

        /* Sum: '<S10>/Sum1' incorporates:
         *  Constant: '<S10>/Constant'
         *  Product: '<S10>/Product'
         *  Sum: '<S10>/Sum'
         */
        bsl_hovering_B.X_tildle_k1k[i_0] = ((tmp_0[i_0] + tmp_1[i_0]) +
          bsl_hovering_ConstP.Constant_Value_g[i_0]) + rtb_Clock;
      }

      /* Gain: '<S14>/C' */
      for (i_0 = 0; i_0 < 6; i_0++) {
        bsl_hovering_B.C[i_0] = 0.0;
        for (i = 0; i < 12; i++) {
          bsl_hovering_B.C[i_0] += bsl_hovering_ConstP.pooled4[6 * i + i_0] *
            bsl_hovering_B.X_tildle_k1k[i];
        }
      }

      /* End of Gain: '<S14>/C' */
    }

    /* Sum: '<S14>/Sum4' incorporates:
     *  Inport: '<Root>/X'
     */
    rtb_T_f[0] = bsl_hovering_U.X[0];
    rtb_T_f[3] = bsl_hovering_U.X[6];
    rtb_T_f[1] = bsl_hovering_U.X[1];
    rtb_T_f[4] = bsl_hovering_U.X[7];
    rtb_T_f[2] = bsl_hovering_U.X[2];
    rtb_T_f[5] = bsl_hovering_U.X[8];

    /* Sum: '<S13>/Sum4' incorporates:
     *  Product: '<S13>/Product1'
     *  Sum: '<S14>/Sum4'
     */
    for (i_0 = 0; i_0 < 6; i_0++) {
      tmp_2[i_0] = (rtb_T_f[i_0] - bsl_hovering_B.C[i_0]) -
        bsl_hovering_B.Product[i_0];
    }

    /* End of Sum: '<S13>/Sum4' */
    for (i = 0; i < 6; i++) {
      /* Sum: '<S13>/Sum1' incorporates:
       *  Product: '<S13>/Product1'
       */
      rtb_Clock = 0.0;
      for (i_0 = 0; i_0 < 6; i_0++) {
        rtb_Clock += bsl_hovering_B.K_gamma_k1[6 * i_0 + i] * tmp_2[i_0];
      }

      bsl_hovering_B.Sum1_lc[i] = bsl_hovering_B.gamma_hat_k1k[i] + rtb_Clock;

      /* End of Sum: '<S13>/Sum1' */

      /* Outport: '<Root>/gamma' */
      bsl_hovering_Y.gamma[i] = bsl_hovering_B.Sum1_lc[i];
    }

    /* RateTransition: '<Root>/Rate Transition' */
    if (rtmIsMajorTimeStep((&bsl_hovering_M)) &&
        (&bsl_hovering_M)->Timing.TaskCounters.TID[1] == 0) {
      /* RateTransition: '<Root>/Rate Transition1' incorporates:
       *  RateTransition: '<Root>/Rate Transition2'
       *  RateTransition: '<Root>/Rate Transition3'
       */
      if (rtmIsMajorTimeStep((&bsl_hovering_M)) &&
          (&bsl_hovering_M)->Timing.TaskCounters.TID[2] == 0) {
        bsl_hovering_B.RateTransition = bsl_hovering_B.ref[0];
        bsl_hovering_B.RateTransition1 = bsl_hovering_B.ref[1];
        bsl_hovering_B.RateTransition2 = bsl_hovering_B.ref[3];
        bsl_hovering_B.RateTransition3 = bsl_hovering_B.ref[2];
      }

      /* End of RateTransition: '<Root>/Rate Transition1' */
      for (i_0 = 0; i_0 < 6; i_0++) {
        /* Gain: '<S10>/C' */
        bsl_hovering_B.C_h[i_0] = 0.0;
        for (i = 0; i < 12; i++) {
          bsl_hovering_B.C_h[i_0] += bsl_hovering_ConstP.pooled4[6 * i + i_0] *
            bsl_hovering_B.X_tildle_k1k[i];

          /* Gain: '<S10>/C'' */
          rtb_Product2_o[i + 12 * i_0] = 0.0;
          for (i_1 = 0; i_1 < 12; i_1++) {
            rtb_Product2_o[i + 12 * i_0] += rtb_Sum4[12 * i_1 + i] *
              bsl_hovering_ConstP.C_Gain[12 * i_0 + i_1];
          }

          /* End of Gain: '<S10>/C'' */
        }

        /* End of Gain: '<S10>/C' */
      }

      /* Sum: '<S10>/Sum5' incorporates:
       *  Constant: '<S10>/R'
       *  Gain: '<S10>/C1'
       */
      for (i_0 = 0; i_0 < 6; i_0++) {
        for (i = 0; i < 6; i++) {
          rtb_Clock = 0.0;
          for (i_1 = 0; i_1 < 12; i_1++) {
            rtb_Clock += bsl_hovering_ConstP.pooled4[6 * i_1 + i] *
              rtb_Product2_o[12 * i_0 + i_1];
          }

          tmp[i + 6 * i_0] = bsl_hovering_ConstP.pooled7[6 * i_0 + i] +
            rtb_Clock;
        }
      }

      /* End of Sum: '<S10>/Sum5' */

      /* Product: '<S10>/Divide' */
      rt_mrdivide_U1d12x6_U2_zAvshA6O(rtb_Product2_o, tmp,
        bsl_hovering_B.K_tildle_x_k1);

      /* Product: '<S10>/Product7' incorporates:
       *  Constant: '<S10>/     '
       *  Product: '<S10>/Product3'
       */
      for (i_0 = 0; i_0 < 12; i_0++) {
        for (i = 0; i < 6; i++) {
          rtb_Product2_e[i + 6 * i_0] = 0.0;
          for (i_1 = 0; i_1 < 12; i_1++) {
            rtb_Product2_e[i + 6 * i_0] += bsl_hovering_ConstP.pooled4[6 * i_1 +
              i] * rtb_Sum4[12 * i_0 + i_1];
          }
        }
      }

      /* End of Product: '<S10>/Product7' */

      /* Product: '<S10>/Product3' */
      for (i_0 = 0; i_0 < 12; i_0++) {
        for (i = 0; i < 12; i++) {
          rtb_Product3[i + 12 * i_0] = 0.0;
          for (i_1 = 0; i_1 < 6; i_1++) {
            rtb_Product3[i + 12 * i_0] += bsl_hovering_B.K_tildle_x_k1[12 * i_1
              + i] * rtb_Product2_e[6 * i_0 + i_1];
          }
        }
      }
    }

    /* End of RateTransition: '<Root>/Rate Transition' */

    /* Sum: '<S10>/Sum6' incorporates:
     *  Inport: '<Root>/X'
     *  Product: '<S10>/Product2'
     */
    rtb_T_f[0] = bsl_hovering_U.X[0];
    rtb_T_f[3] = bsl_hovering_U.X[6];
    rtb_T_f[1] = bsl_hovering_U.X[1];
    rtb_T_f[4] = bsl_hovering_U.X[7];
    rtb_T_f[2] = bsl_hovering_U.X[2];
    rtb_T_f[5] = bsl_hovering_U.X[8];
    for (i_0 = 0; i_0 < 6; i_0++) {
      tmp_2[i_0] = rtb_T_f[i_0] - bsl_hovering_B.C_h[i_0];
    }

    /* End of Sum: '<S10>/Sum6' */

    /* Sum: '<S10>/Sum3' incorporates:
     *  Product: '<S10>/Product2'
     */
    for (i_0 = 0; i_0 < 12; i_0++) {
      rtb_Clock = 0.0;
      for (i = 0; i < 6; i++) {
        rtb_Clock += bsl_hovering_B.K_tildle_x_k1[12 * i + i_0] * tmp_2[i];
      }

      bsl_hovering_B.Sum3[i_0] = bsl_hovering_B.X_tildle_k1k[i_0] + rtb_Clock;
    }

    /* End of Sum: '<S10>/Sum3' */
    if (rtmIsMajorTimeStep((&bsl_hovering_M)) &&
        (&bsl_hovering_M)->Timing.TaskCounters.TID[1] == 0) {
      /* Sum: '<S10>/Sum7' */
      for (i = 0; i < 144; i++) {
        rtb_P_tildle_x_k1[i] = rtb_Sum4[i] - rtb_Product3[i];
      }

      /* End of Sum: '<S10>/Sum7' */
      for (i_0 = 0; i_0 < 6; i_0++) {
        /* Sum: '<S11>/Sum1' incorporates:
         *  Product: '<S11>/Product2'
         */
        for (i = 0; i < 12; i++) {
          rtb_Clock = 0.0;
          for (i_1 = 0; i_1 < 6; i_1++) {
            rtb_Clock += bsl_hovering_B.K_tildle_x_k1[12 * i_1 + i] * rtb_H_k1k
              [6 * i_0 + i_1];
          }

          rtb_Sum1_a[i + 12 * i_0] = rtb_Divide[12 * i_0 + i] - rtb_Clock;
        }

        /* End of Sum: '<S11>/Sum1' */

        /* Product: '<S13>/Product5' incorporates:
         *  Product: '<S13>/Product2'
         */
        for (i = 0; i < 6; i++) {
          rtb_H_k1k_0[i + 6 * i_0] = 0.0;
          for (i_1 = 0; i_1 < 6; i_1++) {
            rtb_H_k1k_0[i + 6 * i_0] += rtb_H_k1k[6 * i_1 + i] *
              rtb_P_gamma_k1k[6 * i_0 + i_1];
          }
        }

        /* End of Product: '<S13>/Product5' */
      }

      /* Sum: '<S13>/Sum5' incorporates:
       *  Product: '<S13>/Product2'
       */
      for (i_0 = 0; i_0 < 6; i_0++) {
        for (i = 0; i < 6; i++) {
          rtb_Clock = 0.0;
          for (i_1 = 0; i_1 < 6; i_1++) {
            rtb_Clock += bsl_hovering_B.K_gamma_k1[6 * i_1 + i] * rtb_H_k1k_0[6 *
              i_0 + i_1];
          }

          rtb_P_gamma_k1[i + 6 * i_0] = rtb_P_gamma_k1k[6 * i_0 + i] - rtb_Clock;
        }
      }

      /* End of Sum: '<S13>/Sum5' */
    }

    if (rtmIsMajorTimeStep((&bsl_hovering_M)) &&
        (&bsl_hovering_M)->Timing.TaskCounters.TID[2] == 0) {
      /* Saturate: '<S5>/yaw' */
      if (bsl_hovering_B.RateTransition2 > 3.1415926535897931) {
        rtb_Clock = 3.1415926535897931;
      } else if (bsl_hovering_B.RateTransition2 < -3.1415926535897931) {
        rtb_Clock = -3.1415926535897931;
      } else {
        rtb_Clock = bsl_hovering_B.RateTransition2;
      }

      /* End of Saturate: '<S5>/yaw' */

      /* Sum: '<S5>/Sum3' */
      u0 = rtb_Clock - bsl_hovering_B.RateTransition4[8];

      /* Saturate: '<S5>/psi_e' */
      if (u0 > 0.78539816339744828) {
        bsl_hovering_B.psi_e = 0.78539816339744828;
      } else if (u0 < -0.78539816339744828) {
        bsl_hovering_B.psi_e = -0.78539816339744828;
      } else {
        bsl_hovering_B.psi_e = u0;
      }

      /* End of Saturate: '<S5>/psi_e' */

      /* Saturate: '<S7>/x' */
      if (bsl_hovering_B.RateTransition > 1.0) {
        rtb_Clock = 1.0;
      } else if (bsl_hovering_B.RateTransition < -1.0) {
        rtb_Clock = -1.0;
      } else {
        rtb_Clock = bsl_hovering_B.RateTransition;
      }

      /* End of Saturate: '<S7>/x' */

      /* Sum: '<S7>/Sum3' */
      u0 = rtb_Clock - bsl_hovering_B.RateTransition4[0];

      /* Saturate: '<S7>/xe' */
      if (u0 > 1.0) {
        bsl_hovering_B.xe = 1.0;
      } else if (u0 < -1.0) {
        bsl_hovering_B.xe = -1.0;
      } else {
        bsl_hovering_B.xe = u0;
      }

      /* End of Saturate: '<S7>/xe' */

      /* Saturate: '<S8>/y' */
      if (bsl_hovering_B.RateTransition1 > 1.0) {
        rtb_Clock = 1.0;
      } else if (bsl_hovering_B.RateTransition1 < -1.0) {
        rtb_Clock = -1.0;
      } else {
        rtb_Clock = bsl_hovering_B.RateTransition1;
      }

      /* End of Saturate: '<S8>/y' */

      /* Sum: '<S8>/Sum3' */
      u0 = rtb_Clock - bsl_hovering_B.RateTransition4[1];

      /* Saturate: '<S8>/ye' */
      if (u0 > 1.0) {
        bsl_hovering_B.ye = 1.0;
      } else if (u0 < -1.0) {
        bsl_hovering_B.ye = -1.0;
      } else {
        bsl_hovering_B.ye = u0;
      }

      /* End of Saturate: '<S8>/ye' */

      /* Saturate: '<S9>/z' */
      if (bsl_hovering_B.RateTransition3 > 1.0) {
        rtb_Clock = 1.0;
      } else if (bsl_hovering_B.RateTransition3 < 0.0) {
        rtb_Clock = 0.0;
      } else {
        rtb_Clock = bsl_hovering_B.RateTransition3;
      }

      /* End of Saturate: '<S9>/z' */

      /* Sum: '<S9>/Sum3' */
      u0 = rtb_Clock - bsl_hovering_B.RateTransition4[2];

      /* Saturate: '<S9>/ze' */
      if (u0 > 0.5) {
        bsl_hovering_B.ze = 0.5;
      } else if (u0 < -0.5) {
        bsl_hovering_B.ze = -0.5;
      } else {
        bsl_hovering_B.ze = u0;
      }

      /* End of Saturate: '<S9>/ze' */
    }
  }

  if (rtmIsMajorTimeStep((&bsl_hovering_M))) {
    int32_T i;
    if (rtmIsMajorTimeStep((&bsl_hovering_M)) &&
        (&bsl_hovering_M)->Timing.TaskCounters.TID[1] == 0) {
      /* Update for UnitDelay: '<S13>/       ' */
      for (i = 0; i < 6; i++) {
        bsl_hovering_DW._DSTATE[i] = bsl_hovering_B.Sum1_lc[i];
      }

      /* End of Update for UnitDelay: '<S13>/       ' */

      /* Update for UnitDelay: '<S13>/Unit Delay1' */
      memcpy(&bsl_hovering_DW.UnitDelay1_DSTATE[0], &rtb_P_gamma_k1[0], 36U *
             sizeof(real_T));

      /* Update for UnitDelay: '<S11>/Unit Delay' */
      memcpy(&bsl_hovering_DW.UnitDelay_DSTATE[0], &rtb_Sum1_a[0], 72U * sizeof
             (real_T));

      /* Update for Memory: '<Root>/Memory1' */
      for (i = 0; i < 6; i++) {
        bsl_hovering_DW.Memory1_PreviousInput[i] = bsl_hovering_B.u_dq[i];
      }

      /* End of Update for Memory: '<Root>/Memory1' */

      /* Update for UnitDelay: '<S10>/Unit Delay1' */
      memcpy(&bsl_hovering_DW.UnitDelay1_DSTATE_e[0], &rtb_P_tildle_x_k1[0],
             144U * sizeof(real_T));

      /* Update for UnitDelay: '<S10>/Unit Delay' */
      memcpy(&bsl_hovering_DW.UnitDelay_DSTATE_i[0], &bsl_hovering_B.Sum3[0],
             12U * sizeof(real_T));
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep((&bsl_hovering_M))) {
    rt_ertODEUpdateContinuousStates(&(&bsl_hovering_M)->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++(&bsl_hovering_M)->Timing.clockTick0)) {
      ++(&bsl_hovering_M)->Timing.clockTickH0;
    }

    (&bsl_hovering_M)->Timing.t[0] = rtsiGetSolverStopTime(&(&bsl_hovering_M)
      ->solverInfo);

    {
      /* Update absolute timer for sample time: [0.01s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.01, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      (&bsl_hovering_M)->Timing.clockTick1++;
      if (!(&bsl_hovering_M)->Timing.clockTick1) {
        (&bsl_hovering_M)->Timing.clockTickH1++;
      }
    }

    rate_scheduler((&bsl_hovering_M));
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void bsl_hoveringModelClass::bsl_hovering_derivatives()
{
  XDot_bsl_hovering_T *_rtXdot;
  _rtXdot = ((XDot_bsl_hovering_T *) (&bsl_hovering_M)->derivs);

  /* Derivatives for Integrator: '<S9>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = bsl_hovering_B.ze;

  /* Derivatives for Integrator: '<S7>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_d = bsl_hovering_B.xe;

  /* Derivatives for Integrator: '<S8>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_j = bsl_hovering_B.ye;

  /* Derivatives for Integrator: '<S5>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_a = bsl_hovering_B.psi_e;
}

/* Model initialize function */
void bsl_hoveringModelClass::initialize()
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)(&bsl_hovering_M), 0,
                sizeof(RT_MODEL_bsl_hovering_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&(&bsl_hovering_M)->solverInfo, &(&bsl_hovering_M)
                          ->Timing.simTimeStep);
    rtsiSetTPtr(&(&bsl_hovering_M)->solverInfo, &rtmGetTPtr((&bsl_hovering_M)));
    rtsiSetStepSizePtr(&(&bsl_hovering_M)->solverInfo, &(&bsl_hovering_M)
                       ->Timing.stepSize0);
    rtsiSetdXPtr(&(&bsl_hovering_M)->solverInfo, &(&bsl_hovering_M)->derivs);
    rtsiSetContStatesPtr(&(&bsl_hovering_M)->solverInfo, (real_T **)
                         &(&bsl_hovering_M)->contStates);
    rtsiSetNumContStatesPtr(&(&bsl_hovering_M)->solverInfo, &(&bsl_hovering_M)
      ->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&bsl_hovering_M)->solverInfo,
      &(&bsl_hovering_M)->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&bsl_hovering_M)->solverInfo,
      &(&bsl_hovering_M)->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&bsl_hovering_M)->solverInfo,
      &(&bsl_hovering_M)->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&(&bsl_hovering_M)->solverInfo, (&rtmGetErrorStatus
      ((&bsl_hovering_M))));
    rtsiSetRTModelPtr(&(&bsl_hovering_M)->solverInfo, (&bsl_hovering_M));
  }

  rtsiSetSimTimeStep(&(&bsl_hovering_M)->solverInfo, MAJOR_TIME_STEP);
  (&bsl_hovering_M)->intgData.y = (&bsl_hovering_M)->odeY;
  (&bsl_hovering_M)->intgData.f[0] = (&bsl_hovering_M)->odeF[0];
  (&bsl_hovering_M)->intgData.f[1] = (&bsl_hovering_M)->odeF[1];
  (&bsl_hovering_M)->intgData.f[2] = (&bsl_hovering_M)->odeF[2];
  (&bsl_hovering_M)->intgData.f[3] = (&bsl_hovering_M)->odeF[3];
  (&bsl_hovering_M)->intgData.f[4] = (&bsl_hovering_M)->odeF[4];
  (&bsl_hovering_M)->intgData.f[5] = (&bsl_hovering_M)->odeF[5];
  getRTM()->contStates = ((X_bsl_hovering_T *) &bsl_hovering_X);
  rtsiSetSolverData(&(&bsl_hovering_M)->solverInfo, (void *)&(&bsl_hovering_M)
                    ->intgData);
  rtsiSetSolverName(&(&bsl_hovering_M)->solverInfo,"ode5");
  rtmSetTPtr(getRTM(), &(&bsl_hovering_M)->Timing.tArray[0]);
  (&bsl_hovering_M)->Timing.stepSize0 = 0.01;

  /* block I/O */
  (void) memset(((void *) &bsl_hovering_B), 0,
                sizeof(B_bsl_hovering_T));

  /* states (continuous) */
  {
    (void) memset((void *)&bsl_hovering_X, 0,
                  sizeof(X_bsl_hovering_T));
  }

  /* states (dwork) */
  (void) memset((void *)&bsl_hovering_DW, 0,
                sizeof(DW_bsl_hovering_T));

  /* external inputs */
  (void)memset((void *)&bsl_hovering_U, 0, sizeof(ExtU_bsl_hovering_T));

  /* external outputs */
  (void) memset((void *)&bsl_hovering_Y, 0,
                sizeof(ExtY_bsl_hovering_T));

  {
    int32_T i;

    /* InitializeConditions for Integrator: '<S9>/Integrator1' */
    bsl_hovering_X.Integrator1_CSTATE = 0.0;

    /* InitializeConditions for Integrator: '<S7>/Integrator1' */
    bsl_hovering_X.Integrator1_CSTATE_d = 0.0;

    /* InitializeConditions for Integrator: '<S8>/Integrator1' */
    bsl_hovering_X.Integrator1_CSTATE_j = 0.0;

    /* InitializeConditions for Integrator: '<S5>/Integrator1' */
    bsl_hovering_X.Integrator1_CSTATE_a = 0.0;

    /* InitializeConditions for UnitDelay: '<S13>/       ' */
    for (i = 0; i < 6; i++) {
      bsl_hovering_DW._DSTATE[i] = 0.0;
    }

    /* End of InitializeConditions for UnitDelay: '<S13>/       ' */

    /* InitializeConditions for UnitDelay: '<S13>/Unit Delay1' */
    memcpy(&bsl_hovering_DW.UnitDelay1_DSTATE[0],
           &bsl_hovering_ConstP.UnitDelay1_InitialCondition[0], 36U * sizeof
           (real_T));

    /* InitializeConditions for UnitDelay: '<S11>/Unit Delay' */
    memset(&bsl_hovering_DW.UnitDelay_DSTATE[0], 0, 72U * sizeof(real_T));

    /* InitializeConditions for Memory: '<Root>/Memory1' */
    for (i = 0; i < 6; i++) {
      bsl_hovering_DW.Memory1_PreviousInput[i] = 2.5179000000000005;
    }

    /* End of InitializeConditions for Memory: '<Root>/Memory1' */

    /* InitializeConditions for UnitDelay: '<S10>/Unit Delay1' */
    memcpy(&bsl_hovering_DW.UnitDelay1_DSTATE_e[0],
           &bsl_hovering_ConstP.UnitDelay1_InitialCondition_g[0], 144U * sizeof
           (real_T));

    /* InitializeConditions for UnitDelay: '<S10>/Unit Delay' */
    memset(&bsl_hovering_DW.UnitDelay_DSTATE_i[0], 0, 12U * sizeof(real_T));
  }
}

/* Model terminate function */
void bsl_hoveringModelClass::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
bsl_hoveringModelClass::bsl_hoveringModelClass()
{
}

/* Destructor */
bsl_hoveringModelClass::~bsl_hoveringModelClass()
{
  /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_bsl_hovering_T * bsl_hoveringModelClass::getRTM()
{
  return (&bsl_hovering_M);
}
