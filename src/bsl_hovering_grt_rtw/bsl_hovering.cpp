/*
 * bsl_hovering.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "bsl_hovering".
 *
 * Model version              : 1.607
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Tue Jan 30 11:37:36 2018
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
    int32_T x;
    int32_T y;
    real_T psi;
    real_T rtb_Clock;
    real_T rtb_P_gamma_k1k[36];
    real_T rtb_Product2_o[72];
    real_T rtb_H_k1k[36];
    real_T rtb_Sum4[144];
    real_T rtb_Product3[144];
    real_T rtb_Product5[36];
    real_T rtb_Divide[72];
    real_T rtb_H_k1k_0[36];
    real_T rtb_Product2_e[72];
    real_T rtb_Divide_0[72];
    real_T rtb_Product2_e_0[144];
    real_T rtb_Divide_1[144];
    real_T rtb_Sum4_0[72];
    real_T tmp[36];
    real_T rtb_H_k1k_1[36];
    real_T tmp_0[12];
    real_T tmp_1[12];
    real_T tmp_2[6];
    real_T tmp_3[6];
    int32_T i;
    real_T rtb_Sqrt1;
    real_T rtb_Product1;
    real_T tmp_4;
    real_T tmp_5;
    real_T tmp_6;

    /* RateTransition: '<Root>/Rate Transition2' incorporates:
     *  Inport: '<Root>/X'
     */
    if ((rtmIsMajorTimeStep((&bsl_hovering_M)) &&
         (&bsl_hovering_M)->Timing.TaskCounters.TID[1] == 0) &&
        (rtmIsMajorTimeStep((&bsl_hovering_M)) &&
         (&bsl_hovering_M)->Timing.TaskCounters.TID[2] == 0)) {
      memcpy(&bsl_hovering_B.RateTransition2[0], &bsl_hovering_U.X[0], 12U *
             sizeof(real_T));
    }

    /* End of RateTransition: '<Root>/Rate Transition2' */
    if (rtmIsMajorTimeStep((&bsl_hovering_M)) &&
        (&bsl_hovering_M)->Timing.TaskCounters.TID[2] == 0) {
      /* Gain: '<S6>/                    ' incorporates:
       *  SignalConversion: '<S6>/TmpSignal ConversionAt                    Inport1'
       */
      bsl_hovering_B.u = 0.32349951352987977 * bsl_hovering_B.RateTransition2[0]
        + 0.2732366014912751 * bsl_hovering_B.RateTransition2[3];
    }

    /* Sum: '<S6>/Sum1' incorporates:
     *  Gain: '<S6>/ '
     *  Integrator: '<S6>/Integrator1'
     */
    bsl_hovering_B.Sum1 = 0.17320508075688992 *
      bsl_hovering_X.Integrator1_CSTATE_d - bsl_hovering_B.u;
    if (rtmIsMajorTimeStep((&bsl_hovering_M)) &&
        (&bsl_hovering_M)->Timing.TaskCounters.TID[2] == 0) {
      /* ZeroOrderHold: '<Root>/Zero-Order Hold1' */
      bsl_hovering_B.ZeroOrderHold1 = bsl_hovering_B.Sum1;

      /* Gain: '<S7>/                     ' incorporates:
       *  SignalConversion: '<S7>/TmpSignal ConversionAt                     Inport1'
       */
      bsl_hovering_B.u_m = -0.31312578517366968 *
        bsl_hovering_B.RateTransition2[1] + -0.25417198201077484 *
        bsl_hovering_B.RateTransition2[4];
    }

    /* Sum: '<S7>/Sum1' incorporates:
     *  Gain: '<S7>/  '
     *  Integrator: '<S7>/Integrator1'
     */
    bsl_hovering_B.Sum1_l = -0.173205080756885 *
      bsl_hovering_X.Integrator1_CSTATE_j - bsl_hovering_B.u_m;
    if (rtmIsMajorTimeStep((&bsl_hovering_M)) &&
        (&bsl_hovering_M)->Timing.TaskCounters.TID[2] == 0) {
      /* ZeroOrderHold: '<Root>/Zero-Order Hold' */
      bsl_hovering_B.ZeroOrderHold = bsl_hovering_B.Sum1_l;
    }

    /* Sum: '<Root>/Sum2' incorporates:
     *  Gain: '<S8>/  '
     *  Gain: '<S8>/                     '
     *  Inport: '<Root>/X'
     *  Integrator: '<S8>/Integrator1'
     *  SignalConversion: '<S8>/TmpSignal ConversionAt                     Inport1'
     *  Sum: '<S8>/Sum1'
     */
    rtb_Clock = 10.000000000000018 * bsl_hovering_X.Integrator1_CSTATE -
      (12.219481695651957 * bsl_hovering_U.X[2] + 6.215786645518647 *
       bsl_hovering_U.X[5]);

    /* Sum: '<S3>/Sum1' incorporates:
     *  Fcn: '<Root>/Fcn1'
     *  Inport: '<Root>/X'
     *  Saturate: '<S3>/roll'
     */
    psi = bsl_hovering_B.ZeroOrderHold * std::cos(bsl_hovering_U.X[8]) +
      bsl_hovering_B.ZeroOrderHold1 * std::sin(bsl_hovering_U.X[8]);
    if (psi > 0.52359877559829882) {
      psi = 0.52359877559829882;
    } else {
      if (psi < -0.52359877559829882) {
        psi = -0.52359877559829882;
      }
    }

    /* Sum: '<Root>/Sum2' incorporates:
     *  Gain: '<S3>/                    '
     *  Inport: '<Root>/X'
     *  SignalConversion: '<S3>/TmpSignal ConversionAt                    Inport1'
     *  Sum: '<S3>/Sum1'
     */
    tmp_4 = psi - (1.1365283480217869 * bsl_hovering_U.X[6] +
                   0.28178545108770103 * bsl_hovering_U.X[9]);

    /* Sum: '<S5>/Sum1' incorporates:
     *  Fcn: '<Root>/Fcn'
     *  Inport: '<Root>/X'
     *  Saturate: '<S5>/pitch'
     */
    psi = -bsl_hovering_B.ZeroOrderHold * std::sin(bsl_hovering_U.X[8]) +
      bsl_hovering_B.ZeroOrderHold1 * std::cos(bsl_hovering_U.X[8]);
    if (psi > 0.52359877559829882) {
      psi = 0.52359877559829882;
    } else {
      if (psi < -0.52359877559829882) {
        psi = -0.52359877559829882;
      }
    }

    /* Sum: '<Root>/Sum2' incorporates:
     *  Gain: '<S4>/  '
     *  Gain: '<S4>/                     '
     *  Gain: '<S5>/                    '
     *  Inport: '<Root>/X'
     *  Integrator: '<S4>/Integrator1'
     *  SignalConversion: '<S4>/TmpSignal ConversionAt                     Inport1'
     *  SignalConversion: '<S5>/TmpSignal ConversionAt                    Inport1'
     *  Sum: '<S4>/Sum1'
     *  Sum: '<S5>/Sum1'
     */
    tmp_5 = psi - (1.2859205994736729 * bsl_hovering_U.X[7] +
                   0.34413551249350854 * bsl_hovering_U.X[10]);
    tmp_6 = 0.15811388300841925 * bsl_hovering_X.Integrator1_CSTATE_a -
      (0.3035552054947866 * bsl_hovering_U.X[8] + 0.24395632222527311 *
       bsl_hovering_U.X[11]);

    /* Outport: '<Root>/virtual_control' incorporates:
     *  Sum: '<Root>/Sum2'
     */
    bsl_hovering_Y.virtual_control[0] = rtb_Clock + 15.107400000000002;
    bsl_hovering_Y.virtual_control[1] = tmp_4;
    bsl_hovering_Y.virtual_control[2] = tmp_5;
    bsl_hovering_Y.virtual_control[3] = tmp_6;
    for (y = 0; y < 6; y++) {
      /* Gain: '<Root>/                 ' incorporates:
       *  Sum: '<Root>/Sum2'
       */
      bsl_hovering_B.u_d[y] = 0.0;
      bsl_hovering_B.u_d[y] += (rtb_Clock + 15.107400000000002) *
        bsl_hovering_ConstP._Gain_dz[y];
      bsl_hovering_B.u_d[y] += bsl_hovering_ConstP._Gain_dz[y + 6] * tmp_4;
      bsl_hovering_B.u_d[y] += bsl_hovering_ConstP._Gain_dz[y + 12] * tmp_5;
      bsl_hovering_B.u_d[y] += bsl_hovering_ConstP._Gain_dz[y + 18] * tmp_6;

      /* Sqrt: '<Root>/Sqrt1' incorporates:
       *  Gain: '<Root>/      '
       */
      rtb_Sqrt1 = std::sqrt(116978.4923343994 * bsl_hovering_B.u_d[y]);

      /* Gain: '<Root>/rads_to_RPM' */
      rtb_Product1 = 9.5493 * rtb_Sqrt1;

      /* Gain: '<Root>/mapping_0_200' incorporates:
       *  Constant: '<Root>/Constant '
       *  Sum: '<Root>/Sum3'
       */
      psi = (rtb_Product1 - 1250.0) * 0.022857142857142857;

      /* Saturate: '<Root>/Saturation' */
      if (psi > 200.0) {
        /* Outport: '<Root>/motor_command' */
        bsl_hovering_Y.motor_command[y] = 200.0;
      } else if (psi < 0.0) {
        /* Outport: '<Root>/motor_command' */
        bsl_hovering_Y.motor_command[y] = 0.0;
      } else {
        /* Outport: '<Root>/motor_command' */
        bsl_hovering_Y.motor_command[y] = psi;
      }

      /* End of Saturate: '<Root>/Saturation' */

      /* Outport: '<Root>/motor_speed' */
      bsl_hovering_Y.motor_speed[y] = rtb_Sqrt1;

      /* Outport: '<Root>/motor_RPM' */
      bsl_hovering_Y.motor_RPM[y] = rtb_Product1;
    }

    /* Clock: '<Root>/Clock' */
    rtb_Clock = (&bsl_hovering_M)->Timing.t[0];

    /* MATLAB Function: '<Root>/MATLAB Function' */
    /* MATLAB Function 'MATLAB Function': '<S1>:1' */
    /* '<S1>:1:2' x = 0; */
    /* '<S1>:1:2' y = 0; */
    /* '<S1>:1:2' z = 0; */
    /* '<S1>:1:2' psi = 0; */
    /* '<S1>:1:3' if t <= 20 */
    if (rtb_Clock <= 20.0) {
      /* '<S1>:1:4' x = 0; */
      x = 0;

      /* '<S1>:1:5' y = 0; */
      y = 0;

      /* '<S1>:1:6' z = 0.5; */
      rtb_Clock = 0.5;

      /* '<S1>:1:7' psi = 0; */
      psi = 0.0;
    } else if (rtb_Clock <= 40.0) {
      /* '<S1>:1:8' elseif t <= 40 */
      /* '<S1>:1:9' x = -1; */
      x = -1;

      /* '<S1>:1:10' y = 0; */
      y = 0;

      /* '<S1>:1:11' z = 0.5; */
      rtb_Clock = 0.5;

      /* '<S1>:1:12' psi = 0; */
      psi = 0.0;
    } else if (rtb_Clock <= 60.0) {
      /* '<S1>:1:13' elseif t <= 60 */
      /* '<S1>:1:14' x = -1; */
      x = -1;

      /* '<S1>:1:15' y = 1; */
      y = 1;

      /* '<S1>:1:16' z = 0.5; */
      rtb_Clock = 0.5;

      /* '<S1>:1:17' psi = 0; */
      psi = 0.0;
    } else if (rtb_Clock <= 80.0) {
      /* '<S1>:1:18' elseif t <= 80 */
      /* '<S1>:1:19' x = -1; */
      x = -1;

      /* '<S1>:1:20' y = 1; */
      y = 1;

      /* '<S1>:1:21' z = 0.5; */
      rtb_Clock = 0.5;

      /* '<S1>:1:22' psi = pi/2; */
      psi = 1.5707963267948966;
    } else {
      /* '<S1>:1:23' else */
      /* '<S1>:1:24' x = -1; */
      x = -1;

      /* '<S1>:1:25' y = 1; */
      y = 1;

      /* '<S1>:1:26' z = 0; */
      rtb_Clock = 0.0;

      /* '<S1>:1:27' psi = pi/2; */
      psi = 1.5707963267948966;
    }

    /* '<S1>:1:29' ref = [x;y;z;psi]; */
    bsl_hovering_B.ref[0] = x;
    bsl_hovering_B.ref[1] = y;
    bsl_hovering_B.ref[2] = rtb_Clock;
    bsl_hovering_B.ref[3] = psi;

    /* End of MATLAB Function: '<Root>/MATLAB Function' */

    /* Outport: '<Root>/ref' */
    bsl_hovering_Y.ref[0] = bsl_hovering_B.ref[0];
    bsl_hovering_Y.ref[1] = bsl_hovering_B.ref[1];
    bsl_hovering_Y.ref[2] = bsl_hovering_B.ref[2];
    bsl_hovering_Y.ref[3] = bsl_hovering_B.ref[3];
    if (rtmIsMajorTimeStep((&bsl_hovering_M)) &&
        (&bsl_hovering_M)->Timing.TaskCounters.TID[1] == 0) {
      /* UnitDelay: '<S12>/       ' */
      for (y = 0; y < 6; y++) {
        bsl_hovering_B.gamma_hat_k1k[y] = bsl_hovering_DW._DSTATE[y];
      }

      /* End of UnitDelay: '<S12>/       ' */
      for (x = 0; x < 36; x++) {
        /* Sum: '<S12>/Sum3' incorporates:
         *  Constant: '<S12>/Q_gamma'
         *  UnitDelay: '<S12>/Unit Delay1'
         */
        rtb_P_gamma_k1k[x] = bsl_hovering_ConstP.Q_gamma_Value[x] +
          bsl_hovering_DW.UnitDelay1_DSTATE[x];

        /* S-Function (sdspdiag2): '<S10>/Create Diagonal Matrix' */
        rtb_H_k1k[x] = 0.0;
      }

      /* S-Function (sdspdiag2): '<S10>/Create Diagonal Matrix' incorporates:
       *  Memory: '<Root>/Memory1'
       */
      for (x = 0; x < 6; x++) {
        rtb_H_k1k[x * 7] = bsl_hovering_DW.Memory1_PreviousInput[x];
      }

      for (x = 0; x < 6; x++) {
        for (y = 0; y < 12; y++) {
          /* Product: '<S10>/Product7' incorporates:
           *  Constant: '<S10>/     '
           *  Sum: '<S10>/Sum4'
           *  UnitDelay: '<S10>/Unit Delay'
           */
          rtb_Product2_e[y + 12 * x] = 0.0;
          for (i = 0; i < 12; i++) {
            rtb_Product2_e[y + 12 * x] += bsl_hovering_ConstP.pooled5[12 * i + y]
              * bsl_hovering_DW.UnitDelay_DSTATE[12 * x + i];
          }

          /* End of Product: '<S10>/Product7' */

          /* Product: '<S10>/Product3' incorporates:
           *  Constant: '<S10>/          '
           *  Sum: '<S10>/Sum4'
           */
          rtb_Divide[y + 12 * x] = 0.0;
          for (i = 0; i < 6; i++) {
            rtb_Divide[y + 12 * x] += bsl_hovering_ConstP.pooled6[12 * i + y] *
              rtb_H_k1k[6 * x + i];
          }

          /* End of Product: '<S10>/Product3' */
        }
      }

      /* Sum: '<S10>/Sum4' */
      for (x = 0; x < 6; x++) {
        for (y = 0; y < 12; y++) {
          rtb_Product2_o[y + 12 * x] = rtb_Product2_e[12 * x + y] - rtb_Divide
            [12 * x + y];
        }
      }

      /* Product: '<S10>/Product1' incorporates:
       *  UnitDelay: '<S12>/Unit Delay1'
       */
      for (x = 0; x < 6; x++) {
        for (y = 0; y < 12; y++) {
          rtb_Product2_e[y + 12 * x] = 0.0;
          for (i = 0; i < 6; i++) {
            rtb_Product2_e[y + 12 * x] += rtb_Product2_o[12 * i + y] *
              bsl_hovering_DW.UnitDelay1_DSTATE[6 * x + i];
          }
        }
      }

      /* End of Product: '<S10>/Product1' */

      /* Product: '<S10>/Divide' */
      rt_mrdivide_U1d12x6_U2_zAvshA6O(rtb_Product2_e, rtb_P_gamma_k1k,
        rtb_Divide);

      /* Product: '<S10>/Product4' incorporates:
       *  Constant: '<S10>/                      '
       */
      for (x = 0; x < 6; x++) {
        for (y = 0; y < 6; y++) {
          rtb_H_k1k[y + 6 * x] = 0.0;
          for (i = 0; i < 12; i++) {
            rtb_H_k1k[y + 6 * x] += bsl_hovering_ConstP.pooled4[6 * i + y] *
              rtb_Divide[12 * x + i];
          }
        }
      }

      /* End of Product: '<S10>/Product4' */

      /* Product: '<S12>/Product3' incorporates:
       *  Math: '<S12>/Transpose'
       */
      for (x = 0; x < 6; x++) {
        for (y = 0; y < 6; y++) {
          rtb_Product5[x + 6 * y] = 0.0;
          for (i = 0; i < 6; i++) {
            rtb_Product5[x + 6 * y] += rtb_P_gamma_k1k[6 * i + x] * rtb_H_k1k[6 *
              i + y];
          }
        }
      }

      /* End of Product: '<S12>/Product3' */
      for (x = 0; x < 12; x++) {
        /* Gain: '<S9>/A1' incorporates:
         *  UnitDelay: '<S9>/Unit Delay1'
         */
        for (y = 0; y < 12; y++) {
          rtb_Product3[x + 12 * y] = 0.0;
          for (i = 0; i < 12; i++) {
            rtb_Product3[x + 12 * y] += bsl_hovering_ConstP.pooled5[12 * i + x] *
              bsl_hovering_DW.UnitDelay1_DSTATE_e[12 * y + i];
          }
        }

        /* End of Gain: '<S9>/A1' */
        for (y = 0; y < 6; y++) {
          /* Product: '<S9>/Product1' incorporates:
           *  Product: '<S9>/Product4'
           */
          rtb_Product2_e[x + 12 * y] = 0.0;

          /* Product: '<S9>/Product5' incorporates:
           *  Product: '<S9>/Product6'
           */
          rtb_Divide_0[x + 12 * y] = 0.0;
          for (i = 0; i < 6; i++) {
            /* Product: '<S9>/Product1' incorporates:
             *  Product: '<S9>/Product4'
             *  UnitDelay: '<S12>/Unit Delay1'
             */
            rtb_Product2_e[x + 12 * y] += rtb_Product2_o[12 * i + x] *
              bsl_hovering_DW.UnitDelay1_DSTATE[6 * y + i];

            /* Product: '<S9>/Product5' incorporates:
             *  Product: '<S9>/Product6'
             */
            rtb_Divide_0[x + 12 * y] += rtb_Divide[12 * i + x] *
              rtb_P_gamma_k1k[6 * y + i];
          }
        }

        for (y = 0; y < 12; y++) {
          /* Product: '<S9>/Product4' incorporates:
           *  Math: '<S9>/Transpose'
           *  Sum: '<S9>/Sum9'
           */
          rtb_Product2_e_0[x + 12 * y] = 0.0;

          /* Product: '<S9>/Product6' incorporates:
           *  Math: '<S9>/Transpose1'
           *  Sum: '<S9>/Sum9'
           */
          rtb_Divide_1[x + 12 * y] = 0.0;
          for (i = 0; i < 6; i++) {
            /* Product: '<S9>/Product4' incorporates:
             *  Math: '<S9>/Transpose'
             *  Sum: '<S9>/Sum9'
             */
            rtb_Product2_e_0[x + 12 * y] += rtb_Product2_e[12 * i + x] *
              rtb_Product2_o[12 * i + y];

            /* Product: '<S9>/Product6' incorporates:
             *  Math: '<S9>/Transpose1'
             *  Sum: '<S9>/Sum9'
             */
            rtb_Divide_1[x + 12 * y] += rtb_Divide_0[12 * i + x] * rtb_Divide[12
              * i + y];
          }

          /* Sum: '<S9>/Sum4' incorporates:
           *  Constant: '<S9>/Q_x'
           *  Gain: '<S9>/A''
           *  Sum: '<S9>/Sum2'
           *  Sum: '<S9>/Sum9'
           */
          rtb_Clock = 0.0;
          for (i = 0; i < 12; i++) {
            rtb_Clock += rtb_Product3[12 * i + x] * bsl_hovering_ConstP.A_Gain
              [12 * y + i];
          }

          rtb_Sum4[x + 12 * y] = ((rtb_Product2_e_0[12 * y + x] - rtb_Divide_1
            [12 * y + x]) + rtb_Clock) + bsl_hovering_ConstP.Q_x_Value[12 * y +
            x];

          /* End of Sum: '<S9>/Sum4' */
        }

        /* Product: '<S13>/Product1' incorporates:
         *  Product: '<S13>/Product7'
         */
        for (y = 0; y < 6; y++) {
          rtb_Sum4_0[x + 12 * y] = 0.0;
          for (i = 0; i < 12; i++) {
            rtb_Sum4_0[x + 12 * y] += rtb_Sum4[12 * i + x] *
              bsl_hovering_ConstB.Transpose[12 * y + i];
          }
        }

        /* End of Product: '<S13>/Product1' */
      }

      for (x = 0; x < 6; x++) {
        for (y = 0; y < 6; y++) {
          /* Product: '<S12>/Product4' incorporates:
           *  Sum: '<S12>/Sum2'
           */
          rtb_H_k1k_0[y + 6 * x] = 0.0;
          for (i = 0; i < 6; i++) {
            rtb_H_k1k_0[y + 6 * x] += rtb_H_k1k[6 * i + y] * rtb_Product5[6 * x
              + i];
          }

          /* End of Product: '<S12>/Product4' */

          /* Sum: '<S13>/Sum1' incorporates:
           *  Constant: '<S13>/     '
           *  Constant: '<S13>/R'
           *  Product: '<S13>/Product7'
           *  Sum: '<S12>/Sum2'
           */
          rtb_Clock = 0.0;
          for (i = 0; i < 12; i++) {
            rtb_Clock += bsl_hovering_ConstP.pooled4[6 * i + y] * rtb_Sum4_0[12 *
              x + i];
          }

          tmp[y + 6 * x] = bsl_hovering_ConstP.pooled7[6 * x + y] + rtb_Clock;

          /* End of Sum: '<S13>/Sum1' */
        }
      }

      /* Sum: '<S12>/Sum2' */
      for (x = 0; x < 6; x++) {
        for (y = 0; y < 6; y++) {
          rtb_H_k1k_1[y + 6 * x] = rtb_H_k1k_0[6 * x + y] + tmp[6 * x + y];
        }
      }

      memcpy(&rtb_H_k1k_0[0], &rtb_H_k1k_1[0], 36U * sizeof(real_T));

      /* Product: '<S12>/Divide' */
      rt_mrdivided6x6_snf(rtb_Product5, rtb_H_k1k_0, bsl_hovering_B.K_gamma_k1);

      /* Product: '<S12>/Product' */
      for (x = 0; x < 6; x++) {
        bsl_hovering_B.Product[x] = 0.0;
        for (y = 0; y < 6; y++) {
          bsl_hovering_B.Product[x] += rtb_H_k1k[6 * y + x] *
            bsl_hovering_B.gamma_hat_k1k[y];
        }
      }

      /* End of Product: '<S12>/Product' */

      /* Sum: '<S9>/Sum8' */
      for (x = 0; x < 72; x++) {
        rtb_Product2_o[x] -= rtb_Divide[x];
      }

      /* End of Sum: '<S9>/Sum8' */
      for (x = 0; x < 12; x++) {
        /* Gain: '<S9>/A' incorporates:
         *  Sum: '<S9>/Sum'
         *  UnitDelay: '<S9>/Unit Delay'
         */
        tmp_0[x] = 0.0;
        for (y = 0; y < 12; y++) {
          tmp_0[x] += bsl_hovering_ConstP.pooled5[12 * y + x] *
            bsl_hovering_DW.UnitDelay_DSTATE_i[y];
        }

        /* End of Gain: '<S9>/A' */

        /* Gain: '<S9>/B' incorporates:
         *  Sum: '<S9>/Sum'
         */
        tmp_1[x] = 0.0;

        /* Sum: '<S9>/Sum1' */
        rtb_Clock = 0.0;
        for (y = 0; y < 6; y++) {
          /* Sum: '<S9>/Sum1' incorporates:
           *  Product: '<S9>/Product'
           */
          rtb_Clock += rtb_Product2_o[12 * y + x] *
            bsl_hovering_B.gamma_hat_k1k[y];

          /* Gain: '<S9>/B' incorporates:
           *  Memory: '<Root>/Memory1'
           *  Sum: '<S9>/Sum'
           */
          tmp_1[x] += bsl_hovering_ConstP.pooled6[12 * y + x] *
            bsl_hovering_DW.Memory1_PreviousInput[y];
        }

        /* Sum: '<S9>/Sum1' incorporates:
         *  Constant: '<S9>/Constant'
         *  Product: '<S9>/Product'
         *  Sum: '<S9>/Sum'
         */
        bsl_hovering_B.X_tildle_k1k[x] = ((tmp_0[x] + tmp_1[x]) +
          bsl_hovering_ConstP.Constant_Value_g[x]) + rtb_Clock;
      }

      /* Gain: '<S13>/C' */
      for (x = 0; x < 6; x++) {
        bsl_hovering_B.C[x] = 0.0;
        for (y = 0; y < 12; y++) {
          bsl_hovering_B.C[x] += bsl_hovering_ConstP.pooled4[6 * y + x] *
            bsl_hovering_B.X_tildle_k1k[y];
        }
      }

      /* End of Gain: '<S13>/C' */
    }

    /* Sum: '<S13>/Sum4' incorporates:
     *  Inport: '<Root>/X'
     */
    tmp_2[0] = bsl_hovering_U.X[0];
    tmp_2[3] = bsl_hovering_U.X[6];
    tmp_2[1] = bsl_hovering_U.X[1];
    tmp_2[4] = bsl_hovering_U.X[7];
    tmp_2[2] = bsl_hovering_U.X[2];
    tmp_2[5] = bsl_hovering_U.X[8];

    /* Sum: '<S12>/Sum4' incorporates:
     *  Product: '<S12>/Product1'
     *  Sum: '<S13>/Sum4'
     */
    for (x = 0; x < 6; x++) {
      tmp_3[x] = (tmp_2[x] - bsl_hovering_B.C[x]) - bsl_hovering_B.Product[x];
    }

    /* End of Sum: '<S12>/Sum4' */
    for (y = 0; y < 6; y++) {
      /* Sum: '<S12>/Sum1' incorporates:
       *  Product: '<S12>/Product1'
       */
      rtb_Clock = 0.0;
      for (x = 0; x < 6; x++) {
        rtb_Clock += bsl_hovering_B.K_gamma_k1[6 * x + y] * tmp_3[x];
      }

      bsl_hovering_B.Sum1_lc[y] = bsl_hovering_B.gamma_hat_k1k[y] + rtb_Clock;

      /* End of Sum: '<S12>/Sum1' */

      /* Outport: '<Root>/gamma' */
      bsl_hovering_Y.gamma[y] = bsl_hovering_B.Sum1_lc[y];
    }

    /* RateTransition: '<Root>/Rate Transition' */
    if (rtmIsMajorTimeStep((&bsl_hovering_M)) &&
        (&bsl_hovering_M)->Timing.TaskCounters.TID[1] == 0) {
      /* RateTransition: '<Root>/Rate Transition1' */
      if (rtmIsMajorTimeStep((&bsl_hovering_M)) &&
          (&bsl_hovering_M)->Timing.TaskCounters.TID[2] == 0) {
        bsl_hovering_B.RateTransition = bsl_hovering_B.ref[0];
        bsl_hovering_B.RateTransition1 = bsl_hovering_B.ref[1];
      }

      /* End of RateTransition: '<Root>/Rate Transition1' */
      for (x = 0; x < 6; x++) {
        /* Gain: '<S9>/C' */
        bsl_hovering_B.C_h[x] = 0.0;
        for (y = 0; y < 12; y++) {
          bsl_hovering_B.C_h[x] += bsl_hovering_ConstP.pooled4[6 * y + x] *
            bsl_hovering_B.X_tildle_k1k[y];

          /* Gain: '<S9>/C'' */
          rtb_Product2_o[y + 12 * x] = 0.0;
          for (i = 0; i < 12; i++) {
            rtb_Product2_o[y + 12 * x] += rtb_Sum4[12 * i + y] *
              bsl_hovering_ConstP.C_Gain[12 * x + i];
          }

          /* End of Gain: '<S9>/C'' */
        }

        /* End of Gain: '<S9>/C' */
      }

      /* Sum: '<S9>/Sum5' incorporates:
       *  Constant: '<S9>/R'
       *  Gain: '<S9>/C1'
       */
      for (x = 0; x < 6; x++) {
        for (y = 0; y < 6; y++) {
          rtb_Clock = 0.0;
          for (i = 0; i < 12; i++) {
            rtb_Clock += bsl_hovering_ConstP.pooled4[6 * i + y] *
              rtb_Product2_o[12 * x + i];
          }

          tmp[y + 6 * x] = bsl_hovering_ConstP.pooled7[6 * x + y] + rtb_Clock;
        }
      }

      /* End of Sum: '<S9>/Sum5' */

      /* Product: '<S9>/Divide' */
      rt_mrdivide_U1d12x6_U2_zAvshA6O(rtb_Product2_o, tmp,
        bsl_hovering_B.K_tildle_x_k1);

      /* Product: '<S9>/Product7' incorporates:
       *  Constant: '<S9>/     '
       *  Product: '<S9>/Product3'
       */
      for (x = 0; x < 12; x++) {
        for (y = 0; y < 6; y++) {
          rtb_Product2_e[y + 6 * x] = 0.0;
          for (i = 0; i < 12; i++) {
            rtb_Product2_e[y + 6 * x] += bsl_hovering_ConstP.pooled4[6 * i + y] *
              rtb_Sum4[12 * x + i];
          }
        }
      }

      /* End of Product: '<S9>/Product7' */

      /* Product: '<S9>/Product3' */
      for (x = 0; x < 12; x++) {
        for (y = 0; y < 12; y++) {
          rtb_Product3[y + 12 * x] = 0.0;
          for (i = 0; i < 6; i++) {
            rtb_Product3[y + 12 * x] += bsl_hovering_B.K_tildle_x_k1[12 * i + y]
              * rtb_Product2_e[6 * x + i];
          }
        }
      }
    }

    /* End of RateTransition: '<Root>/Rate Transition' */

    /* Sum: '<S9>/Sum6' incorporates:
     *  Inport: '<Root>/X'
     *  Product: '<S9>/Product2'
     */
    tmp_2[0] = bsl_hovering_U.X[0];
    tmp_2[3] = bsl_hovering_U.X[6];
    tmp_2[1] = bsl_hovering_U.X[1];
    tmp_2[4] = bsl_hovering_U.X[7];
    tmp_2[2] = bsl_hovering_U.X[2];
    tmp_2[5] = bsl_hovering_U.X[8];
    for (x = 0; x < 6; x++) {
      tmp_3[x] = tmp_2[x] - bsl_hovering_B.C_h[x];
    }

    /* End of Sum: '<S9>/Sum6' */

    /* Sum: '<S9>/Sum3' incorporates:
     *  Product: '<S9>/Product2'
     */
    for (x = 0; x < 12; x++) {
      rtb_Clock = 0.0;
      for (y = 0; y < 6; y++) {
        rtb_Clock += bsl_hovering_B.K_tildle_x_k1[12 * y + x] * tmp_3[y];
      }

      bsl_hovering_B.Sum3[x] = bsl_hovering_B.X_tildle_k1k[x] + rtb_Clock;
    }

    /* End of Sum: '<S9>/Sum3' */
    if (rtmIsMajorTimeStep((&bsl_hovering_M)) &&
        (&bsl_hovering_M)->Timing.TaskCounters.TID[1] == 0) {
      /* Sum: '<S9>/Sum7' */
      for (y = 0; y < 144; y++) {
        rtb_P_tildle_x_k1[y] = rtb_Sum4[y] - rtb_Product3[y];
      }

      /* End of Sum: '<S9>/Sum7' */
      for (x = 0; x < 6; x++) {
        /* Sum: '<S10>/Sum1' incorporates:
         *  Product: '<S10>/Product2'
         */
        for (y = 0; y < 12; y++) {
          rtb_Clock = 0.0;
          for (i = 0; i < 6; i++) {
            rtb_Clock += bsl_hovering_B.K_tildle_x_k1[12 * i + y] * rtb_H_k1k[6 *
              x + i];
          }

          rtb_Sum1_a[y + 12 * x] = rtb_Divide[12 * x + y] - rtb_Clock;
        }

        /* End of Sum: '<S10>/Sum1' */

        /* Product: '<S12>/Product5' incorporates:
         *  Product: '<S12>/Product2'
         */
        for (y = 0; y < 6; y++) {
          rtb_H_k1k_0[y + 6 * x] = 0.0;
          for (i = 0; i < 6; i++) {
            rtb_H_k1k_0[y + 6 * x] += rtb_H_k1k[6 * i + y] * rtb_P_gamma_k1k[6 *
              x + i];
          }
        }

        /* End of Product: '<S12>/Product5' */
      }

      /* Sum: '<S12>/Sum5' incorporates:
       *  Product: '<S12>/Product2'
       */
      for (x = 0; x < 6; x++) {
        for (y = 0; y < 6; y++) {
          rtb_Clock = 0.0;
          for (i = 0; i < 6; i++) {
            rtb_Clock += bsl_hovering_B.K_gamma_k1[6 * i + y] * rtb_H_k1k_0[6 *
              x + i];
          }

          rtb_P_gamma_k1[y + 6 * x] = rtb_P_gamma_k1k[6 * x + y] - rtb_Clock;
        }
      }

      /* End of Sum: '<S12>/Sum5' */
    }

    /* Saturate: '<S4>/yaw' */
    if (bsl_hovering_B.ref[3] > 3.1415926535897931) {
      rtb_Clock = 3.1415926535897931;
    } else if (bsl_hovering_B.ref[3] < -3.1415926535897931) {
      rtb_Clock = -3.1415926535897931;
    } else {
      rtb_Clock = bsl_hovering_B.ref[3];
    }

    /* End of Saturate: '<S4>/yaw' */

    /* Sum: '<S4>/Sum3' incorporates:
     *  Inport: '<Root>/X'
     */
    psi = rtb_Clock - bsl_hovering_U.X[8];

    /* Saturate: '<S4>/psi_e' */
    if (psi > 0.78539816339744828) {
      bsl_hovering_B.psi_e = 0.78539816339744828;
    } else if (psi < -0.78539816339744828) {
      bsl_hovering_B.psi_e = -0.78539816339744828;
    } else {
      bsl_hovering_B.psi_e = psi;
    }

    /* End of Saturate: '<S4>/psi_e' */
    if (rtmIsMajorTimeStep((&bsl_hovering_M)) &&
        (&bsl_hovering_M)->Timing.TaskCounters.TID[2] == 0) {
      /* Saturate: '<S6>/x' */
      if (bsl_hovering_B.RateTransition > 1.0) {
        rtb_Clock = 1.0;
      } else if (bsl_hovering_B.RateTransition < -1.0) {
        rtb_Clock = -1.0;
      } else {
        rtb_Clock = bsl_hovering_B.RateTransition;
      }

      /* End of Saturate: '<S6>/x' */

      /* Sum: '<S6>/Sum3' */
      psi = rtb_Clock - bsl_hovering_B.RateTransition2[0];

      /* Saturate: '<S6>/xe' */
      if (psi > 1.0) {
        bsl_hovering_B.xe = 1.0;
      } else if (psi < -1.0) {
        bsl_hovering_B.xe = -1.0;
      } else {
        bsl_hovering_B.xe = psi;
      }

      /* End of Saturate: '<S6>/xe' */

      /* Saturate: '<S7>/y' */
      if (bsl_hovering_B.RateTransition1 > 1.0) {
        rtb_Clock = 1.0;
      } else if (bsl_hovering_B.RateTransition1 < -1.0) {
        rtb_Clock = -1.0;
      } else {
        rtb_Clock = bsl_hovering_B.RateTransition1;
      }

      /* End of Saturate: '<S7>/y' */

      /* Sum: '<S7>/Sum3' */
      psi = rtb_Clock - bsl_hovering_B.RateTransition2[1];

      /* Saturate: '<S7>/ye' */
      if (psi > 1.0) {
        bsl_hovering_B.ye = 1.0;
      } else if (psi < -1.0) {
        bsl_hovering_B.ye = -1.0;
      } else {
        bsl_hovering_B.ye = psi;
      }

      /* End of Saturate: '<S7>/ye' */
    }

    /* Saturate: '<S8>/z' */
    if (bsl_hovering_B.ref[2] > 1.0) {
      rtb_Clock = 1.0;
    } else if (bsl_hovering_B.ref[2] < 0.0) {
      rtb_Clock = 0.0;
    } else {
      rtb_Clock = bsl_hovering_B.ref[2];
    }

    /* End of Saturate: '<S8>/z' */

    /* Sum: '<S8>/Sum3' incorporates:
     *  Inport: '<Root>/X'
     */
    psi = rtb_Clock - bsl_hovering_U.X[2];

    /* Saturate: '<S8>/ze' */
    if (psi > 0.5) {
      bsl_hovering_B.ze = 0.5;
    } else if (psi < -0.5) {
      bsl_hovering_B.ze = -0.5;
    } else {
      bsl_hovering_B.ze = psi;
    }

    /* End of Saturate: '<S8>/ze' */
  }

  if (rtmIsMajorTimeStep((&bsl_hovering_M))) {
    int32_T i;
    if (rtmIsMajorTimeStep((&bsl_hovering_M)) &&
        (&bsl_hovering_M)->Timing.TaskCounters.TID[1] == 0) {
      /* Update for UnitDelay: '<S12>/       ' */
      for (i = 0; i < 6; i++) {
        bsl_hovering_DW._DSTATE[i] = bsl_hovering_B.Sum1_lc[i];
      }

      /* End of Update for UnitDelay: '<S12>/       ' */

      /* Update for UnitDelay: '<S12>/Unit Delay1' */
      memcpy(&bsl_hovering_DW.UnitDelay1_DSTATE[0], &rtb_P_gamma_k1[0], 36U *
             sizeof(real_T));

      /* Update for UnitDelay: '<S10>/Unit Delay' */
      memcpy(&bsl_hovering_DW.UnitDelay_DSTATE[0], &rtb_Sum1_a[0], 72U * sizeof
             (real_T));

      /* Update for Memory: '<Root>/Memory1' */
      for (i = 0; i < 6; i++) {
        bsl_hovering_DW.Memory1_PreviousInput[i] = bsl_hovering_B.u_d[i];
      }

      /* End of Update for Memory: '<Root>/Memory1' */

      /* Update for UnitDelay: '<S9>/Unit Delay1' */
      memcpy(&bsl_hovering_DW.UnitDelay1_DSTATE_e[0], &rtb_P_tildle_x_k1[0],
             144U * sizeof(real_T));

      /* Update for UnitDelay: '<S9>/Unit Delay' */
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

  /* Derivatives for Integrator: '<S8>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = bsl_hovering_B.ze;

  /* Derivatives for Integrator: '<S6>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_d = bsl_hovering_B.xe;

  /* Derivatives for Integrator: '<S7>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_j = bsl_hovering_B.ye;

  /* Derivatives for Integrator: '<S4>/Integrator1' */
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

    /* InitializeConditions for Integrator: '<S8>/Integrator1' */
    bsl_hovering_X.Integrator1_CSTATE = 0.0;

    /* InitializeConditions for Integrator: '<S6>/Integrator1' */
    bsl_hovering_X.Integrator1_CSTATE_d = 0.0;

    /* InitializeConditions for Integrator: '<S7>/Integrator1' */
    bsl_hovering_X.Integrator1_CSTATE_j = 0.0;

    /* InitializeConditions for Integrator: '<S4>/Integrator1' */
    bsl_hovering_X.Integrator1_CSTATE_a = 0.0;

    /* InitializeConditions for UnitDelay: '<S12>/       ' */
    for (i = 0; i < 6; i++) {
      bsl_hovering_DW._DSTATE[i] = 0.0;
    }

    /* End of InitializeConditions for UnitDelay: '<S12>/       ' */

    /* InitializeConditions for UnitDelay: '<S12>/Unit Delay1' */
    memcpy(&bsl_hovering_DW.UnitDelay1_DSTATE[0],
           &bsl_hovering_ConstP.UnitDelay1_InitialCondition[0], 36U * sizeof
           (real_T));

    /* InitializeConditions for UnitDelay: '<S10>/Unit Delay' */
    memset(&bsl_hovering_DW.UnitDelay_DSTATE[0], 0, 72U * sizeof(real_T));

    /* InitializeConditions for Memory: '<Root>/Memory1' */
    for (i = 0; i < 6; i++) {
      bsl_hovering_DW.Memory1_PreviousInput[i] = 2.5179000000000005;
    }

    /* End of InitializeConditions for Memory: '<Root>/Memory1' */

    /* InitializeConditions for UnitDelay: '<S9>/Unit Delay1' */
    memcpy(&bsl_hovering_DW.UnitDelay1_DSTATE_e[0],
           &bsl_hovering_ConstP.UnitDelay1_InitialCondition_g[0], 144U * sizeof
           (real_T));

    /* InitializeConditions for UnitDelay: '<S9>/Unit Delay' */
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
