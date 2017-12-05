/*
 * lqr_firefly.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_firefly".
 *
 * Model version              : 1.450
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Mon Dec 04 20:22:35 2017
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Passed (2), Warnings (2), Error (0)
 */

#include "lqr_firefly.h"
#include "lqr_firefly_private.h"

/*
 * This function updates continuous states using the ODE5 fixed-step
 * solver algorithm
 */
void lqr_fireflyModelClass::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
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
  int_T nXc = 10;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  lqr_firefly_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE5_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[0]);
  rtsiSetdX(si, f1);
  this->step();
  lqr_firefly_derivatives();

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
  lqr_firefly_derivatives();

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
  lqr_firefly_derivatives();

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
  lqr_firefly_derivatives();

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
  lqr_firefly_derivatives();

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
void lqr_fireflyModelClass::step()
{
  int_T iy;
  int_T ci;
  real_T rtb_Gain2[6];
  real_T rtb_Sum2[4];
  real_T tmp[4];
  real_T rtb_Sum2_h;
  const real_T *tmp_0;
  if (rtmIsMajorTimeStep((&lqr_firefly_M))) {
    /* set solver stop time */
    if (!((&lqr_firefly_M)->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&(&lqr_firefly_M)->solverInfo, (((&lqr_firefly_M)
        ->Timing.clockTickH0 + 1) * (&lqr_firefly_M)->Timing.stepSize0 *
        4294967296.0));
    } else {
      rtsiSetSolverStopTime(&(&lqr_firefly_M)->solverInfo, (((&lqr_firefly_M)
        ->Timing.clockTick0 + 1) * (&lqr_firefly_M)->Timing.stepSize0 +
        (&lqr_firefly_M)->Timing.clockTickH0 * (&lqr_firefly_M)
        ->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep((&lqr_firefly_M))) {
    (&lqr_firefly_M)->Timing.t[0] = rtsiGetT(&(&lqr_firefly_M)->solverInfo);
  }

  for (iy = 0; iy < 6; iy++) {
    /* StateSpace: '<Root>/Filter' */
    rtb_Gain2[iy] = 0.0;
    for (ci = iy; ci < iy + 1; ci++) {
      rtb_Gain2[iy] += lqr_firefly_X.Filter_CSTATE[ci];
    }

    /* End of StateSpace: '<Root>/Filter' */

    /* Outport: '<Root>/omega' */
    lqr_firefly_Y.omega[iy] = rtb_Gain2[iy];
  }

  /* Sum: '<Root>/Sum3' incorporates:
   *  Gain: '<Root>/                   '
   *  Inport: '<Root>/X'
   */
  tmp_0 = &lqr_firefly_U.X[0];

  /* Sum: '<Root>/Sum1' incorporates:
   *  Inport: '<Root>/X'
   *  Inport: '<Root>/psi_ref'
   *  Inport: '<Root>/x_ref'
   *  Inport: '<Root>/y_ref'
   *  Inport: '<Root>/z_ref'
   */
  lqr_firefly_B.Sum1[0] = lqr_firefly_U.x_ref - lqr_firefly_U.X[0];
  lqr_firefly_B.Sum1[1] = lqr_firefly_U.y_ref - lqr_firefly_U.X[1];
  lqr_firefly_B.Sum1[2] = lqr_firefly_U.z_ref - lqr_firefly_U.X[2];
  lqr_firefly_B.Sum1[3] = lqr_firefly_U.psi_ref - lqr_firefly_U.X[8];
  for (iy = 0; iy < 4; iy++) {
    /* Gain: '<Root>/ ' incorporates:
     *  Integrator: '<Root>/Integrator'
     *  Sum: '<Root>/Sum'
     */
    rtb_Sum2_h = lqr_firefly_ConstP._Gain[iy + 12] *
      lqr_firefly_X.Integrator_CSTATE[3] + (lqr_firefly_ConstP._Gain[iy + 8] *
      lqr_firefly_X.Integrator_CSTATE[2] + (lqr_firefly_ConstP._Gain[iy + 4] *
      lqr_firefly_X.Integrator_CSTATE[1] + lqr_firefly_ConstP._Gain[iy] *
      lqr_firefly_X.Integrator_CSTATE[0]));

    /* Gain: '<Root>/                   ' incorporates:
     *  Sum: '<Root>/Sum'
     */
    tmp[iy] = 0.0;
    for (ci = 0; ci < 12; ci++) {
      tmp[iy] += lqr_firefly_ConstP._Gain_g[(ci << 2) + iy] * tmp_0[ci];
    }

    /* Sum: '<Root>/Sum2' incorporates:
     *  Constant: '<Root>/              '
     *  Sum: '<Root>/Sum'
     */
    rtb_Sum2_h = (rtb_Sum2_h - tmp[iy]) + lqr_firefly_ConstP._Value[iy];

    /* Outport: '<Root>/virtual_control' */
    lqr_firefly_Y.virtual_control[iy] = rtb_Sum2_h;

    /* Outport: '<Root>/error' */
    lqr_firefly_Y.error[iy] = lqr_firefly_B.Sum1[iy];

    /* Sum: '<Root>/Sum2' incorporates:
     *  Sum: '<Root>/Sum'
     */
    rtb_Sum2[iy] = rtb_Sum2_h;
  }

  for (ci = 0; ci < 6; ci++) {
    /* Gain: '<Root>/Gain' incorporates:
     *  Saturate: '<Root>/Saturation'
     */
    rtb_Sum2_h = lqr_firefly_ConstP.Gain_Gain[ci + 18] * rtb_Sum2[3] +
      (lqr_firefly_ConstP.Gain_Gain[ci + 12] * rtb_Sum2[2] +
       (lqr_firefly_ConstP.Gain_Gain[ci + 6] * rtb_Sum2[1] +
        lqr_firefly_ConstP.Gain_Gain[ci] * rtb_Sum2[0]));

    /* Sqrt: '<Root>/Sqrt1' incorporates:
     *  Gain: '<Root>/Gain'
     *  Gain: '<Root>/Gain2'
     */
    if (rtb_Sum2_h > 6.00318901352) {
      rtb_Sum2_h = 6.00318901352;
    } else {
      if (rtb_Sum2_h < 0.0) {
        rtb_Sum2_h = 0.0;
      }
    }

    lqr_firefly_B.Sqrt1[ci] = std::sqrt(116978.4923343994 * rtb_Sum2_h);

    /* End of Sqrt: '<Root>/Sqrt1' */
  }

  if (rtmIsMajorTimeStep((&lqr_firefly_M))) {
    rt_ertODEUpdateContinuousStates(&(&lqr_firefly_M)->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++(&lqr_firefly_M)->Timing.clockTick0)) {
      ++(&lqr_firefly_M)->Timing.clockTickH0;
    }

    (&lqr_firefly_M)->Timing.t[0] = rtsiGetSolverStopTime(&(&lqr_firefly_M)
      ->solverInfo);

    {
      /* Update absolute timer for sample time: [0.016666666666666666s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.016666666666666666, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      (&lqr_firefly_M)->Timing.clockTick1++;
      if (!(&lqr_firefly_M)->Timing.clockTick1) {
        (&lqr_firefly_M)->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void lqr_fireflyModelClass::lqr_firefly_derivatives()
{
  int_T is;
  int_T ci;
  XDot_lqr_firefly_T *_rtXdot;
  _rtXdot = ((XDot_lqr_firefly_T *) (&lqr_firefly_M)->derivs);

  /* Derivatives for StateSpace: '<Root>/Filter' */
  for (is = 0; is < 6; is++) {
    _rtXdot->Filter_CSTATE[is] = 0.0;
    for (ci = is; ci < is + 1; ci++) {
      _rtXdot->Filter_CSTATE[is] += -80.0 * lqr_firefly_X.Filter_CSTATE[ci];
    }
  }

  for (is = 0; is < 6; is++) {
    for (ci = is; ci < is + 1; ci++) {
      _rtXdot->Filter_CSTATE[is] += 80.0 * lqr_firefly_B.Sqrt1[ci];
    }
  }

  /* End of Derivatives for StateSpace: '<Root>/Filter' */

  /* Derivatives for Integrator: '<Root>/Integrator' */
  _rtXdot->Integrator_CSTATE[0] = lqr_firefly_B.Sum1[0];
  _rtXdot->Integrator_CSTATE[1] = lqr_firefly_B.Sum1[1];
  _rtXdot->Integrator_CSTATE[2] = lqr_firefly_B.Sum1[2];
  _rtXdot->Integrator_CSTATE[3] = lqr_firefly_B.Sum1[3];
}

/* Model initialize function */
void lqr_fireflyModelClass::initialize()
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)(&lqr_firefly_M), 0,
                sizeof(RT_MODEL_lqr_firefly_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&(&lqr_firefly_M)->solverInfo, &(&lqr_firefly_M)
                          ->Timing.simTimeStep);
    rtsiSetTPtr(&(&lqr_firefly_M)->solverInfo, &rtmGetTPtr((&lqr_firefly_M)));
    rtsiSetStepSizePtr(&(&lqr_firefly_M)->solverInfo, &(&lqr_firefly_M)
                       ->Timing.stepSize0);
    rtsiSetdXPtr(&(&lqr_firefly_M)->solverInfo, &(&lqr_firefly_M)->derivs);
    rtsiSetContStatesPtr(&(&lqr_firefly_M)->solverInfo, (real_T **)
                         &(&lqr_firefly_M)->contStates);
    rtsiSetNumContStatesPtr(&(&lqr_firefly_M)->solverInfo, &(&lqr_firefly_M)
      ->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&lqr_firefly_M)->solverInfo,
      &(&lqr_firefly_M)->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&lqr_firefly_M)->solverInfo,
      &(&lqr_firefly_M)->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&lqr_firefly_M)->solverInfo,
      &(&lqr_firefly_M)->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&(&lqr_firefly_M)->solverInfo, (&rtmGetErrorStatus
      ((&lqr_firefly_M))));
    rtsiSetRTModelPtr(&(&lqr_firefly_M)->solverInfo, (&lqr_firefly_M));
  }

  rtsiSetSimTimeStep(&(&lqr_firefly_M)->solverInfo, MAJOR_TIME_STEP);
  (&lqr_firefly_M)->intgData.y = (&lqr_firefly_M)->odeY;
  (&lqr_firefly_M)->intgData.f[0] = (&lqr_firefly_M)->odeF[0];
  (&lqr_firefly_M)->intgData.f[1] = (&lqr_firefly_M)->odeF[1];
  (&lqr_firefly_M)->intgData.f[2] = (&lqr_firefly_M)->odeF[2];
  (&lqr_firefly_M)->intgData.f[3] = (&lqr_firefly_M)->odeF[3];
  (&lqr_firefly_M)->intgData.f[4] = (&lqr_firefly_M)->odeF[4];
  (&lqr_firefly_M)->intgData.f[5] = (&lqr_firefly_M)->odeF[5];
  getRTM()->contStates = ((X_lqr_firefly_T *) &lqr_firefly_X);
  rtsiSetSolverData(&(&lqr_firefly_M)->solverInfo, (void *)&(&lqr_firefly_M)
                    ->intgData);
  rtsiSetSolverName(&(&lqr_firefly_M)->solverInfo,"ode5");
  rtmSetTPtr(getRTM(), &(&lqr_firefly_M)->Timing.tArray[0]);
  (&lqr_firefly_M)->Timing.stepSize0 = 0.016666666666666666;

  /* block I/O */
  (void) memset(((void *) &lqr_firefly_B), 0,
                sizeof(B_lqr_firefly_T));

  /* states (continuous) */
  {
    (void) memset((void *)&lqr_firefly_X, 0,
                  sizeof(X_lqr_firefly_T));
  }

  /* external inputs */
  (void)memset((void *)&lqr_firefly_U, 0, sizeof(ExtU_lqr_firefly_T));

  /* external outputs */
  (void) memset((void *)&lqr_firefly_Y, 0,
                sizeof(ExtY_lqr_firefly_T));

  {
    int_T is;

    /* InitializeConditions for StateSpace: '<Root>/Filter' */
    for (is = 0; is < 6; is++) {
      lqr_firefly_X.Filter_CSTATE[is] = 0.0;
    }

    /* End of InitializeConditions for StateSpace: '<Root>/Filter' */

    /* InitializeConditions for Integrator: '<Root>/Integrator' */
    lqr_firefly_X.Integrator_CSTATE[0] = 0.0;
    lqr_firefly_X.Integrator_CSTATE[1] = 0.0;
    lqr_firefly_X.Integrator_CSTATE[2] = 0.0;
    lqr_firefly_X.Integrator_CSTATE[3] = 0.0;
  }
}

/* Model terminate function */
void lqr_fireflyModelClass::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
lqr_fireflyModelClass::lqr_fireflyModelClass()
{
}

/* Destructor */
lqr_fireflyModelClass::~lqr_fireflyModelClass()
{
  /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_lqr_firefly_T * lqr_fireflyModelClass::getRTM()
{
  return (&lqr_firefly_M);
}
