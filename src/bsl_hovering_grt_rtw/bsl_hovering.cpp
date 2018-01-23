/*
 * bsl_hovering.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "bsl_hovering".
 *
 * Model version              : 1.536
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Tue Jan 23 12:14:15 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Passed (1), Warnings (3), Error (0)
 */

#include "bsl_hovering.h"
#include "bsl_hovering_private.h"

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
  real_T rtb_Sum1_e[72];
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
    real_T rtb_Sum2_h[4];
    real_T rtb_P_gamma_k1k[36];
    real_T rtb_Product2_o[72];
    real_T rtb_H_k1k[36];
    real_T rtb_Product5[36];
    real_T rtb_Divide[72];
    real_T rtb_Sum4_p[144];
    real_T rtb_Product3[144];
    real_T rtb_H_k1k_0[36];
    real_T rtb_Product2_h[72];
    real_T tmp[4];
    int32_T i;
    int32_T i_0;
    real_T rtb_Divide_0[72];
    real_T rtb_Product2_h_0[144];
    real_T rtb_Divide_1[144];
    real_T rtb_Sum4_g[72];
    real_T tmp_0[36];
    real_T rtb_H_k1k_1[36];
    real_T tmp_1[12];
    real_T tmp_2[12];
    real_T tmp_3[6];
    real_T tmp_4[6];
    int32_T i_1;
    real_T rtb_Sqrt;
    real_T rtb_Product1;
    real_T u0;
    for (i = 0; i < 4; i++) {
      /* Gain: '<Root>/ ' incorporates:
       *  Integrator: '<Root>/Integrator'
       *  Sum: '<Root>/Sum'
       */
      rtb_Sqrt = bsl_hovering_ConstP._Gain[i + 12] *
        bsl_hovering_X.Integrator_CSTATE[3] + (bsl_hovering_ConstP._Gain[i + 8] *
        bsl_hovering_X.Integrator_CSTATE[2] + (bsl_hovering_ConstP._Gain[i + 4] *
        bsl_hovering_X.Integrator_CSTATE[1] + bsl_hovering_ConstP._Gain[i] *
        bsl_hovering_X.Integrator_CSTATE[0]));

      /* Gain: '<Root>/                   ' incorporates:
       *  Inport: '<Root>/X'
       *  Sum: '<Root>/Sum'
       */
      tmp[i] = 0.0;
      for (i_0 = 0; i_0 < 12; i_0++) {
        tmp[i] += bsl_hovering_ConstP._Gain_g[(i_0 << 2) + i] *
          bsl_hovering_U.X[i_0];
      }

      /* End of Gain: '<Root>/                   ' */

      /* Sum: '<Root>/Sum2' incorporates:
       *  Constant: '<Root>/              '
       *  Sum: '<Root>/Sum'
       */
      rtb_Sum2_h[i] = (rtb_Sqrt - tmp[i]) + bsl_hovering_ConstP._Value[i];
    }

    /* Outport: '<Root>/virtual_control' */
    bsl_hovering_Y.virtual_control[0] = rtb_Sum2_h[0];
    bsl_hovering_Y.virtual_control[1] = rtb_Sum2_h[1];
    bsl_hovering_Y.virtual_control[2] = rtb_Sum2_h[2];
    bsl_hovering_Y.virtual_control[3] = rtb_Sum2_h[3];
    for (i_0 = 0; i_0 < 6; i_0++) {
      /* Gain: '<Root>/Gain' */
      bsl_hovering_B.Gain[i_0] = 0.0;
      bsl_hovering_B.Gain[i_0] += bsl_hovering_ConstP.Gain_Gain[i_0] *
        rtb_Sum2_h[0];
      bsl_hovering_B.Gain[i_0] += bsl_hovering_ConstP.Gain_Gain[i_0 + 6] *
        rtb_Sum2_h[1];
      bsl_hovering_B.Gain[i_0] += bsl_hovering_ConstP.Gain_Gain[i_0 + 12] *
        rtb_Sum2_h[2];
      bsl_hovering_B.Gain[i_0] += bsl_hovering_ConstP.Gain_Gain[i_0 + 18] *
        rtb_Sum2_h[3];

      /* Sqrt: '<Root>/Sqrt' incorporates:
       *  Gain: '<Root>/Gain2'
       */
      rtb_Sqrt = std::sqrt(116978.4923343994 * bsl_hovering_B.Gain[i_0]);

      /* Gain: '<Root>/rads_to_RPM' */
      rtb_Product1 = 9.5493 * rtb_Sqrt;

      /* Gain: '<Root>/mapping_0_200' incorporates:
       *  Constant: '<Root>/Constant1'
       *  Sum: '<Root>/Sum3'
       */
      u0 = (rtb_Product1 - 1250.0) * 0.022857142857142857;

      /* Saturate: '<Root>/Saturation' */
      if (u0 > 200.0) {
        /* Outport: '<Root>/motor_command' */
        bsl_hovering_Y.motor_command[i_0] = 200.0;
      } else if (u0 < 1.0) {
        /* Outport: '<Root>/motor_command' */
        bsl_hovering_Y.motor_command[i_0] = 1.0;
      } else {
        /* Outport: '<Root>/motor_command' */
        bsl_hovering_Y.motor_command[i_0] = u0;
      }

      /* End of Saturate: '<Root>/Saturation' */

      /* Outport: '<Root>/motor_speed' */
      bsl_hovering_Y.motor_speed[i_0] = rtb_Sqrt;

      /* Outport: '<Root>/motor_RPM' */
      bsl_hovering_Y.motor_RPM[i_0] = rtb_Product1;
    }

    if (rtmIsMajorTimeStep((&bsl_hovering_M))) {
      /* UnitDelay: '<S5>/       ' */
      for (i_0 = 0; i_0 < 6; i_0++) {
        bsl_hovering_B.gamma_hat_k1k[i_0] = bsl_hovering_DW._DSTATE[i_0];
      }

      /* End of UnitDelay: '<S5>/       ' */
      for (i_0 = 0; i_0 < 36; i_0++) {
        /* Sum: '<S5>/Sum3' incorporates:
         *  Constant: '<S5>/Q_gamma'
         *  UnitDelay: '<S5>/Unit Delay1'
         */
        rtb_P_gamma_k1k[i_0] = bsl_hovering_ConstP.Q_gamma_Value[i_0] +
          bsl_hovering_DW.UnitDelay1_DSTATE[i_0];

        /* S-Function (sdspdiag2): '<S3>/Create Diagonal Matrix' */
        rtb_H_k1k[i_0] = 0.0;
      }

      /* S-Function (sdspdiag2): '<S3>/Create Diagonal Matrix' incorporates:
       *  Memory: '<Root>/Memory'
       */
      for (i_0 = 0; i_0 < 6; i_0++) {
        rtb_H_k1k[i_0 * 7] = bsl_hovering_DW.Memory_PreviousInput[i_0];
      }

      for (i = 0; i < 6; i++) {
        for (i_0 = 0; i_0 < 12; i_0++) {
          /* Product: '<S3>/Product7' incorporates:
           *  Constant: '<S3>/     '
           *  Sum: '<S3>/Sum4'
           *  UnitDelay: '<S3>/Unit Delay'
           */
          rtb_Product2_h[i_0 + 12 * i] = 0.0;
          for (i_1 = 0; i_1 < 12; i_1++) {
            rtb_Product2_h[i_0 + 12 * i] += bsl_hovering_ConstP.pooled3[12 * i_1
              + i_0] * bsl_hovering_DW.UnitDelay_DSTATE[12 * i + i_1];
          }

          /* End of Product: '<S3>/Product7' */

          /* Product: '<S3>/Product3' incorporates:
           *  Constant: '<S3>/          '
           *  Sum: '<S3>/Sum4'
           */
          rtb_Divide[i_0 + 12 * i] = 0.0;
          for (i_1 = 0; i_1 < 6; i_1++) {
            rtb_Divide[i_0 + 12 * i] += bsl_hovering_ConstP.pooled4[12 * i_1 +
              i_0] * rtb_H_k1k[6 * i + i_1];
          }

          /* End of Product: '<S3>/Product3' */
        }
      }

      /* Sum: '<S3>/Sum4' */
      for (i = 0; i < 6; i++) {
        for (i_0 = 0; i_0 < 12; i_0++) {
          rtb_Product2_o[i_0 + 12 * i] = rtb_Product2_h[12 * i + i_0] -
            rtb_Divide[12 * i + i_0];
        }
      }

      /* Product: '<S3>/Product1' incorporates:
       *  UnitDelay: '<S5>/Unit Delay1'
       */
      for (i = 0; i < 6; i++) {
        for (i_0 = 0; i_0 < 12; i_0++) {
          rtb_Product2_h[i_0 + 12 * i] = 0.0;
          for (i_1 = 0; i_1 < 6; i_1++) {
            rtb_Product2_h[i_0 + 12 * i] += rtb_Product2_o[12 * i_1 + i_0] *
              bsl_hovering_DW.UnitDelay1_DSTATE[6 * i + i_1];
          }
        }
      }

      /* End of Product: '<S3>/Product1' */

      /* Product: '<S3>/Divide' */
      rt_mrdivide_U1d12x6_U2_zAvshA6O(rtb_Product2_h, rtb_P_gamma_k1k,
        rtb_Divide);

      /* Product: '<S3>/Product4' incorporates:
       *  Constant: '<S3>/                      '
       */
      for (i = 0; i < 6; i++) {
        for (i_0 = 0; i_0 < 6; i_0++) {
          rtb_H_k1k[i_0 + 6 * i] = 0.0;
          for (i_1 = 0; i_1 < 12; i_1++) {
            rtb_H_k1k[i_0 + 6 * i] += bsl_hovering_ConstP.pooled2[6 * i_1 + i_0]
              * rtb_Divide[12 * i + i_1];
          }
        }
      }

      /* End of Product: '<S3>/Product4' */

      /* Product: '<S5>/Product3' incorporates:
       *  Math: '<S5>/Transpose'
       */
      for (i = 0; i < 6; i++) {
        for (i_0 = 0; i_0 < 6; i_0++) {
          rtb_Product5[i + 6 * i_0] = 0.0;
          for (i_1 = 0; i_1 < 6; i_1++) {
            rtb_Product5[i + 6 * i_0] += rtb_P_gamma_k1k[6 * i_1 + i] *
              rtb_H_k1k[6 * i_1 + i_0];
          }
        }
      }

      /* End of Product: '<S5>/Product3' */
      for (i = 0; i < 12; i++) {
        /* Gain: '<S2>/A1' incorporates:
         *  UnitDelay: '<S2>/Unit Delay1'
         */
        for (i_0 = 0; i_0 < 12; i_0++) {
          rtb_Product3[i + 12 * i_0] = 0.0;
          for (i_1 = 0; i_1 < 12; i_1++) {
            rtb_Product3[i + 12 * i_0] += bsl_hovering_ConstP.pooled3[12 * i_1 +
              i] * bsl_hovering_DW.UnitDelay1_DSTATE_g[12 * i_0 + i_1];
          }
        }

        /* End of Gain: '<S2>/A1' */
        for (i_0 = 0; i_0 < 6; i_0++) {
          /* Product: '<S2>/Product1' incorporates:
           *  Product: '<S2>/Product4'
           */
          rtb_Product2_h[i + 12 * i_0] = 0.0;

          /* Product: '<S2>/Product5' incorporates:
           *  Product: '<S2>/Product6'
           */
          rtb_Divide_0[i + 12 * i_0] = 0.0;
          for (i_1 = 0; i_1 < 6; i_1++) {
            /* Product: '<S2>/Product1' incorporates:
             *  Product: '<S2>/Product4'
             *  UnitDelay: '<S5>/Unit Delay1'
             */
            rtb_Product2_h[i + 12 * i_0] += rtb_Product2_o[12 * i_1 + i] *
              bsl_hovering_DW.UnitDelay1_DSTATE[6 * i_0 + i_1];

            /* Product: '<S2>/Product5' incorporates:
             *  Product: '<S2>/Product6'
             */
            rtb_Divide_0[i + 12 * i_0] += rtb_Divide[12 * i_1 + i] *
              rtb_P_gamma_k1k[6 * i_0 + i_1];
          }
        }

        for (i_0 = 0; i_0 < 12; i_0++) {
          /* Product: '<S2>/Product4' incorporates:
           *  Math: '<S2>/Transpose'
           *  Sum: '<S2>/Sum9'
           */
          rtb_Product2_h_0[i + 12 * i_0] = 0.0;

          /* Product: '<S2>/Product6' incorporates:
           *  Math: '<S2>/Transpose1'
           *  Sum: '<S2>/Sum9'
           */
          rtb_Divide_1[i + 12 * i_0] = 0.0;
          for (i_1 = 0; i_1 < 6; i_1++) {
            /* Product: '<S2>/Product4' incorporates:
             *  Math: '<S2>/Transpose'
             *  Sum: '<S2>/Sum9'
             */
            rtb_Product2_h_0[i + 12 * i_0] += rtb_Product2_h[12 * i_1 + i] *
              rtb_Product2_o[12 * i_1 + i_0];

            /* Product: '<S2>/Product6' incorporates:
             *  Math: '<S2>/Transpose1'
             *  Sum: '<S2>/Sum9'
             */
            rtb_Divide_1[i + 12 * i_0] += rtb_Divide_0[12 * i_1 + i] *
              rtb_Divide[12 * i_1 + i_0];
          }

          /* Sum: '<S2>/Sum4' incorporates:
           *  Constant: '<S2>/Q_x'
           *  Gain: '<S2>/A''
           *  Sum: '<S2>/Sum2'
           *  Sum: '<S2>/Sum9'
           */
          rtb_Sqrt = 0.0;
          for (i_1 = 0; i_1 < 12; i_1++) {
            rtb_Sqrt += rtb_Product3[12 * i_1 + i] * bsl_hovering_ConstP.A_Gain
              [12 * i_0 + i_1];
          }

          rtb_Sum4_p[i + 12 * i_0] = ((rtb_Product2_h_0[12 * i_0 + i] -
            rtb_Divide_1[12 * i_0 + i]) + rtb_Sqrt) +
            bsl_hovering_ConstP.Q_x_Value[12 * i_0 + i];

          /* End of Sum: '<S2>/Sum4' */
        }

        /* Product: '<S6>/Product1' incorporates:
         *  Product: '<S6>/Product7'
         */
        for (i_0 = 0; i_0 < 6; i_0++) {
          rtb_Sum4_g[i + 12 * i_0] = 0.0;
          for (i_1 = 0; i_1 < 12; i_1++) {
            rtb_Sum4_g[i + 12 * i_0] += rtb_Sum4_p[12 * i_1 + i] *
              bsl_hovering_ConstB.Transpose[12 * i_0 + i_1];
          }
        }

        /* End of Product: '<S6>/Product1' */
      }

      for (i = 0; i < 6; i++) {
        for (i_0 = 0; i_0 < 6; i_0++) {
          /* Product: '<S5>/Product4' incorporates:
           *  Sum: '<S5>/Sum2'
           */
          rtb_H_k1k_0[i_0 + 6 * i] = 0.0;
          for (i_1 = 0; i_1 < 6; i_1++) {
            rtb_H_k1k_0[i_0 + 6 * i] += rtb_H_k1k[6 * i_1 + i_0] * rtb_Product5
              [6 * i + i_1];
          }

          /* End of Product: '<S5>/Product4' */

          /* Sum: '<S6>/Sum1' incorporates:
           *  Constant: '<S6>/     '
           *  Constant: '<S6>/R'
           *  Product: '<S6>/Product7'
           *  Sum: '<S5>/Sum2'
           */
          rtb_Sqrt = 0.0;
          for (i_1 = 0; i_1 < 12; i_1++) {
            rtb_Sqrt += bsl_hovering_ConstP.pooled2[6 * i_1 + i_0] * rtb_Sum4_g
              [12 * i + i_1];
          }

          tmp_0[i_0 + 6 * i] = bsl_hovering_ConstP.pooled5[6 * i + i_0] +
            rtb_Sqrt;

          /* End of Sum: '<S6>/Sum1' */
        }
      }

      /* Sum: '<S5>/Sum2' */
      for (i = 0; i < 6; i++) {
        for (i_0 = 0; i_0 < 6; i_0++) {
          rtb_H_k1k_1[i_0 + 6 * i] = rtb_H_k1k_0[6 * i + i_0] + tmp_0[6 * i +
            i_0];
        }
      }

      memcpy(&rtb_H_k1k_0[0], &rtb_H_k1k_1[0], 36U * sizeof(real_T));

      /* Product: '<S5>/Divide' */
      rt_mrdivided6x6_snf(rtb_Product5, rtb_H_k1k_0, bsl_hovering_B.K_gamma_k1);

      /* Product: '<S5>/Product' */
      for (i = 0; i < 6; i++) {
        bsl_hovering_B.Product[i] = 0.0;
        for (i_0 = 0; i_0 < 6; i_0++) {
          bsl_hovering_B.Product[i] += rtb_H_k1k[6 * i_0 + i] *
            bsl_hovering_B.gamma_hat_k1k[i_0];
        }
      }

      /* End of Product: '<S5>/Product' */

      /* Sum: '<S2>/Sum8' */
      for (i = 0; i < 72; i++) {
        rtb_Product2_o[i] -= rtb_Divide[i];
      }

      /* End of Sum: '<S2>/Sum8' */
      for (i = 0; i < 12; i++) {
        /* Gain: '<S2>/A' incorporates:
         *  Sum: '<S2>/Sum'
         *  UnitDelay: '<S2>/Unit Delay'
         */
        tmp_1[i] = 0.0;
        for (i_0 = 0; i_0 < 12; i_0++) {
          tmp_1[i] += bsl_hovering_ConstP.pooled3[12 * i_0 + i] *
            bsl_hovering_DW.UnitDelay_DSTATE_h[i_0];
        }

        /* End of Gain: '<S2>/A' */

        /* Gain: '<S2>/B' incorporates:
         *  Sum: '<S2>/Sum'
         */
        tmp_2[i] = 0.0;

        /* Sum: '<S2>/Sum1' */
        rtb_Sqrt = 0.0;
        for (i_0 = 0; i_0 < 6; i_0++) {
          /* Sum: '<S2>/Sum1' incorporates:
           *  Product: '<S2>/Product'
           */
          rtb_Sqrt += rtb_Product2_o[12 * i_0 + i] *
            bsl_hovering_B.gamma_hat_k1k[i_0];

          /* Gain: '<S2>/B' incorporates:
           *  Memory: '<Root>/Memory'
           *  Sum: '<S2>/Sum'
           */
          tmp_2[i] += bsl_hovering_ConstP.pooled4[12 * i_0 + i] *
            bsl_hovering_DW.Memory_PreviousInput[i_0];
        }

        /* Sum: '<S2>/Sum1' incorporates:
         *  Constant: '<S2>/Constant'
         *  Product: '<S2>/Product'
         *  Sum: '<S2>/Sum'
         */
        bsl_hovering_B.X_tildle_k1k[i] = ((tmp_1[i] + tmp_2[i]) +
          bsl_hovering_ConstP.Constant_Value[i]) + rtb_Sqrt;
      }

      /* Gain: '<S6>/C' */
      for (i = 0; i < 6; i++) {
        bsl_hovering_B.C[i] = 0.0;
        for (i_0 = 0; i_0 < 12; i_0++) {
          bsl_hovering_B.C[i] += bsl_hovering_ConstP.pooled2[6 * i_0 + i] *
            bsl_hovering_B.X_tildle_k1k[i_0];
        }
      }

      /* End of Gain: '<S6>/C' */
    }

    /* Sum: '<S6>/Sum4' incorporates:
     *  Inport: '<Root>/X'
     */
    tmp_3[0] = bsl_hovering_U.X[0];
    tmp_3[3] = bsl_hovering_U.X[6];
    tmp_3[1] = bsl_hovering_U.X[1];
    tmp_3[4] = bsl_hovering_U.X[7];
    tmp_3[2] = bsl_hovering_U.X[2];
    tmp_3[5] = bsl_hovering_U.X[8];

    /* Sum: '<S5>/Sum4' incorporates:
     *  Product: '<S5>/Product1'
     *  Sum: '<S6>/Sum4'
     */
    for (i = 0; i < 6; i++) {
      tmp_4[i] = (tmp_3[i] - bsl_hovering_B.C[i]) - bsl_hovering_B.Product[i];
    }

    /* End of Sum: '<S5>/Sum4' */
    for (i_0 = 0; i_0 < 6; i_0++) {
      /* Sum: '<S5>/Sum1' incorporates:
       *  Product: '<S5>/Product1'
       */
      rtb_Sqrt = 0.0;
      for (i = 0; i < 6; i++) {
        rtb_Sqrt += bsl_hovering_B.K_gamma_k1[6 * i + i_0] * tmp_4[i];
      }

      bsl_hovering_B.Sum1[i_0] = bsl_hovering_B.gamma_hat_k1k[i_0] + rtb_Sqrt;

      /* End of Sum: '<S5>/Sum1' */

      /* Outport: '<Root>/gamma' */
      bsl_hovering_Y.gamma[i_0] = bsl_hovering_B.Sum1[i_0];
    }

    if (rtmIsMajorTimeStep((&bsl_hovering_M))) {
      for (i = 0; i < 6; i++) {
        /* Gain: '<S2>/C' */
        bsl_hovering_B.C_p[i] = 0.0;
        for (i_0 = 0; i_0 < 12; i_0++) {
          bsl_hovering_B.C_p[i] += bsl_hovering_ConstP.pooled2[6 * i_0 + i] *
            bsl_hovering_B.X_tildle_k1k[i_0];

          /* Gain: '<S2>/C'' */
          rtb_Product2_o[i_0 + 12 * i] = 0.0;
          for (i_1 = 0; i_1 < 12; i_1++) {
            rtb_Product2_o[i_0 + 12 * i] += rtb_Sum4_p[12 * i_1 + i_0] *
              bsl_hovering_ConstP.C_Gain[12 * i + i_1];
          }

          /* End of Gain: '<S2>/C'' */
        }

        /* End of Gain: '<S2>/C' */
      }

      /* Sum: '<S2>/Sum5' incorporates:
       *  Constant: '<S2>/R'
       *  Gain: '<S2>/C1'
       */
      for (i = 0; i < 6; i++) {
        for (i_0 = 0; i_0 < 6; i_0++) {
          rtb_Sqrt = 0.0;
          for (i_1 = 0; i_1 < 12; i_1++) {
            rtb_Sqrt += bsl_hovering_ConstP.pooled2[6 * i_1 + i_0] *
              rtb_Product2_o[12 * i + i_1];
          }

          tmp_0[i_0 + 6 * i] = bsl_hovering_ConstP.pooled5[6 * i + i_0] +
            rtb_Sqrt;
        }
      }

      /* End of Sum: '<S2>/Sum5' */

      /* Product: '<S2>/Divide' */
      rt_mrdivide_U1d12x6_U2_zAvshA6O(rtb_Product2_o, tmp_0,
        bsl_hovering_B.K_tildle_x_k1);

      /* Product: '<S2>/Product7' incorporates:
       *  Constant: '<S2>/     '
       *  Product: '<S2>/Product3'
       */
      for (i = 0; i < 12; i++) {
        for (i_0 = 0; i_0 < 6; i_0++) {
          rtb_Product2_h[i_0 + 6 * i] = 0.0;
          for (i_1 = 0; i_1 < 12; i_1++) {
            rtb_Product2_h[i_0 + 6 * i] += bsl_hovering_ConstP.pooled2[6 * i_1 +
              i_0] * rtb_Sum4_p[12 * i + i_1];
          }
        }
      }

      /* End of Product: '<S2>/Product7' */

      /* Product: '<S2>/Product3' */
      for (i = 0; i < 12; i++) {
        for (i_0 = 0; i_0 < 12; i_0++) {
          rtb_Product3[i_0 + 12 * i] = 0.0;
          for (i_1 = 0; i_1 < 6; i_1++) {
            rtb_Product3[i_0 + 12 * i] += bsl_hovering_B.K_tildle_x_k1[12 * i_1
              + i_0] * rtb_Product2_h[6 * i + i_1];
          }
        }
      }
    }

    /* Sum: '<S2>/Sum6' incorporates:
     *  Inport: '<Root>/X'
     *  Product: '<S2>/Product2'
     */
    tmp_3[0] = bsl_hovering_U.X[0];
    tmp_3[3] = bsl_hovering_U.X[6];
    tmp_3[1] = bsl_hovering_U.X[1];
    tmp_3[4] = bsl_hovering_U.X[7];
    tmp_3[2] = bsl_hovering_U.X[2];
    tmp_3[5] = bsl_hovering_U.X[8];
    for (i = 0; i < 6; i++) {
      tmp_4[i] = tmp_3[i] - bsl_hovering_B.C_p[i];
    }

    /* End of Sum: '<S2>/Sum6' */

    /* Sum: '<S2>/Sum3' incorporates:
     *  Product: '<S2>/Product2'
     */
    for (i = 0; i < 12; i++) {
      rtb_Sqrt = 0.0;
      for (i_0 = 0; i_0 < 6; i_0++) {
        rtb_Sqrt += bsl_hovering_B.K_tildle_x_k1[12 * i_0 + i] * tmp_4[i_0];
      }

      bsl_hovering_B.Sum3[i] = bsl_hovering_B.X_tildle_k1k[i] + rtb_Sqrt;
    }

    /* End of Sum: '<S2>/Sum3' */
    if (rtmIsMajorTimeStep((&bsl_hovering_M))) {
      /* Sum: '<S2>/Sum7' */
      for (i_0 = 0; i_0 < 144; i_0++) {
        rtb_P_tildle_x_k1[i_0] = rtb_Sum4_p[i_0] - rtb_Product3[i_0];
      }

      /* End of Sum: '<S2>/Sum7' */
      for (i = 0; i < 6; i++) {
        /* Sum: '<S3>/Sum1' incorporates:
         *  Product: '<S3>/Product2'
         */
        for (i_0 = 0; i_0 < 12; i_0++) {
          rtb_Sqrt = 0.0;
          for (i_1 = 0; i_1 < 6; i_1++) {
            rtb_Sqrt += bsl_hovering_B.K_tildle_x_k1[12 * i_1 + i_0] *
              rtb_H_k1k[6 * i + i_1];
          }

          rtb_Sum1_e[i_0 + 12 * i] = rtb_Divide[12 * i + i_0] - rtb_Sqrt;
        }

        /* End of Sum: '<S3>/Sum1' */

        /* Product: '<S5>/Product5' incorporates:
         *  Product: '<S5>/Product2'
         */
        for (i_0 = 0; i_0 < 6; i_0++) {
          rtb_H_k1k_0[i_0 + 6 * i] = 0.0;
          for (i_1 = 0; i_1 < 6; i_1++) {
            rtb_H_k1k_0[i_0 + 6 * i] += rtb_H_k1k[6 * i_1 + i_0] *
              rtb_P_gamma_k1k[6 * i + i_1];
          }
        }

        /* End of Product: '<S5>/Product5' */
      }

      /* Sum: '<S5>/Sum5' incorporates:
       *  Product: '<S5>/Product2'
       */
      for (i = 0; i < 6; i++) {
        for (i_0 = 0; i_0 < 6; i_0++) {
          rtb_Sqrt = 0.0;
          for (i_1 = 0; i_1 < 6; i_1++) {
            rtb_Sqrt += bsl_hovering_B.K_gamma_k1[6 * i_1 + i_0] * rtb_H_k1k_0[6
              * i + i_1];
          }

          rtb_P_gamma_k1[i_0 + 6 * i] = rtb_P_gamma_k1k[6 * i + i_0] - rtb_Sqrt;
        }
      }

      /* End of Sum: '<S5>/Sum5' */
    }

    /* Saturate: '<Root>/psi_e' incorporates:
     *  Inport: '<Root>/X'
     *  Sum: '<Root>/Sum6'
     */
    if (0.0 - bsl_hovering_U.X[8] > 0.52359877559829882) {
      bsl_hovering_B.psi_e = 0.52359877559829882;
    } else if (0.0 - bsl_hovering_U.X[8] < -0.52359877559829882) {
      bsl_hovering_B.psi_e = -0.52359877559829882;
    } else {
      bsl_hovering_B.psi_e = 0.0 - bsl_hovering_U.X[8];
    }

    /* End of Saturate: '<Root>/psi_e' */

    /* Saturate: '<Root>/xe' incorporates:
     *  Inport: '<Root>/X'
     *  Sum: '<Root>/Sum1'
     */
    if (0.0 - bsl_hovering_U.X[0] > 1.0) {
      bsl_hovering_B.xe = 1.0;
    } else if (0.0 - bsl_hovering_U.X[0] < -1.0) {
      bsl_hovering_B.xe = -1.0;
    } else {
      bsl_hovering_B.xe = 0.0 - bsl_hovering_U.X[0];
    }

    /* End of Saturate: '<Root>/xe' */

    /* Saturate: '<Root>/ye' incorporates:
     *  Inport: '<Root>/X'
     *  Sum: '<Root>/Sum4'
     */
    if (0.0 - bsl_hovering_U.X[1] > 1.0) {
      bsl_hovering_B.ye = 1.0;
    } else if (0.0 - bsl_hovering_U.X[1] < -1.0) {
      bsl_hovering_B.ye = -1.0;
    } else {
      bsl_hovering_B.ye = 0.0 - bsl_hovering_U.X[1];
    }

    /* End of Saturate: '<Root>/ye' */

    /* Saturate: '<Root>/ze' incorporates:
     *  Inport: '<Root>/X'
     *  Sum: '<Root>/Sum5'
     */
    if (0.75 - bsl_hovering_U.X[2] > 0.5) {
      bsl_hovering_B.ze = 0.5;
    } else if (0.75 - bsl_hovering_U.X[2] < -0.5) {
      bsl_hovering_B.ze = -0.5;
    } else {
      bsl_hovering_B.ze = 0.75 - bsl_hovering_U.X[2];
    }

    /* End of Saturate: '<Root>/ze' */
  }

  if (rtmIsMajorTimeStep((&bsl_hovering_M))) {
    int32_T i;
    if (rtmIsMajorTimeStep((&bsl_hovering_M))) {
      /* Update for UnitDelay: '<S5>/       ' */
      for (i = 0; i < 6; i++) {
        bsl_hovering_DW._DSTATE[i] = bsl_hovering_B.Sum1[i];
      }

      /* End of Update for UnitDelay: '<S5>/       ' */

      /* Update for UnitDelay: '<S5>/Unit Delay1' */
      memcpy(&bsl_hovering_DW.UnitDelay1_DSTATE[0], &rtb_P_gamma_k1[0], 36U *
             sizeof(real_T));

      /* Update for UnitDelay: '<S3>/Unit Delay' */
      memcpy(&bsl_hovering_DW.UnitDelay_DSTATE[0], &rtb_Sum1_e[0], 72U * sizeof
             (real_T));

      /* Update for Memory: '<Root>/Memory' */
      for (i = 0; i < 6; i++) {
        bsl_hovering_DW.Memory_PreviousInput[i] = bsl_hovering_B.Gain[i];
      }

      /* End of Update for Memory: '<Root>/Memory' */

      /* Update for UnitDelay: '<S2>/Unit Delay1' */
      memcpy(&bsl_hovering_DW.UnitDelay1_DSTATE_g[0], &rtb_P_tildle_x_k1[0],
             144U * sizeof(real_T));

      /* Update for UnitDelay: '<S2>/Unit Delay' */
      memcpy(&bsl_hovering_DW.UnitDelay_DSTATE_h[0], &bsl_hovering_B.Sum3[0],
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
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void bsl_hoveringModelClass::bsl_hovering_derivatives()
{
  XDot_bsl_hovering_T *_rtXdot;
  _rtXdot = ((XDot_bsl_hovering_T *) (&bsl_hovering_M)->derivs);

  /* Derivatives for Integrator: '<Root>/Integrator' */
  _rtXdot->Integrator_CSTATE[0] = bsl_hovering_B.xe;
  _rtXdot->Integrator_CSTATE[1] = bsl_hovering_B.ye;
  _rtXdot->Integrator_CSTATE[2] = bsl_hovering_B.ze;
  _rtXdot->Integrator_CSTATE[3] = bsl_hovering_B.psi_e;
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

    /* InitializeConditions for Integrator: '<Root>/Integrator' */
    bsl_hovering_X.Integrator_CSTATE[0] = 0.0;
    bsl_hovering_X.Integrator_CSTATE[1] = 0.0;
    bsl_hovering_X.Integrator_CSTATE[2] = 0.0;
    bsl_hovering_X.Integrator_CSTATE[3] = 0.0;

    /* InitializeConditions for UnitDelay: '<S5>/       ' */
    for (i = 0; i < 6; i++) {
      bsl_hovering_DW._DSTATE[i] = 0.0;
    }

    /* End of InitializeConditions for UnitDelay: '<S5>/       ' */

    /* InitializeConditions for UnitDelay: '<S5>/Unit Delay1' */
    memcpy(&bsl_hovering_DW.UnitDelay1_DSTATE[0],
           &bsl_hovering_ConstP.UnitDelay1_InitialCondition[0], 36U * sizeof
           (real_T));

    /* InitializeConditions for UnitDelay: '<S3>/Unit Delay' */
    memset(&bsl_hovering_DW.UnitDelay_DSTATE[0], 0, 72U * sizeof(real_T));

    /* InitializeConditions for Memory: '<Root>/Memory' */
    for (i = 0; i < 6; i++) {
      bsl_hovering_DW.Memory_PreviousInput[i] = 2.5179000000000005;
    }

    /* End of InitializeConditions for Memory: '<Root>/Memory' */

    /* InitializeConditions for UnitDelay: '<S2>/Unit Delay1' */
    memcpy(&bsl_hovering_DW.UnitDelay1_DSTATE_g[0],
           &bsl_hovering_ConstP.UnitDelay1_InitialCondition_g[0], 144U * sizeof
           (real_T));

    /* InitializeConditions for UnitDelay: '<S2>/Unit Delay' */
    memset(&bsl_hovering_DW.UnitDelay_DSTATE_h[0], 0, 12U * sizeof(real_T));
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
