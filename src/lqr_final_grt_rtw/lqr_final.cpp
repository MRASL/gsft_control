/*
 * lqr_final.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_final".
 *
 * Model version              : 1.483
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Thu Dec 21 08:40:24 2017
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Passed (1), Warnings (3), Error (0)
 */

#include "lqr_final.h"
#include "lqr_final_private.h"

/*
 * This function updates continuous states using the ODE5 fixed-step
 * solver algorithm
 */
void lqr_finalModelClass::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
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
  lqr_final_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE5_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[0]);
  rtsiSetdX(si, f1);
  this->step();
  lqr_final_derivatives();

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
  lqr_final_derivatives();

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
  lqr_final_derivatives();

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
  lqr_final_derivatives();

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
  lqr_final_derivatives();

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
void lqr_finalModelClass::step()
{
  real_T rtb_Sum2[4];
  real_T tmp[4];
  int32_T i;
  int32_T i_0;
  real_T u0;
  real_T rtb_Sqrt1;
  real_T rtb_rads_to_RPM;
  if (rtmIsMajorTimeStep((&lqr_final_M))) {
    /* set solver stop time */
    if (!((&lqr_final_M)->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&(&lqr_final_M)->solverInfo, (((&lqr_final_M)
        ->Timing.clockTickH0 + 1) * (&lqr_final_M)->Timing.stepSize0 *
        4294967296.0));
    } else {
      rtsiSetSolverStopTime(&(&lqr_final_M)->solverInfo, (((&lqr_final_M)
        ->Timing.clockTick0 + 1) * (&lqr_final_M)->Timing.stepSize0 +
        (&lqr_final_M)->Timing.clockTickH0 * (&lqr_final_M)->Timing.stepSize0 *
        4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep((&lqr_final_M))) {
    (&lqr_final_M)->Timing.t[0] = rtsiGetT(&(&lqr_final_M)->solverInfo);
  }

  for (i_0 = 0; i_0 < 4; i_0++) {
    /* Gain: '<Root>/ ' incorporates:
     *  Integrator: '<Root>/Integrator'
     *  Sum: '<Root>/Sum'
     */
    u0 = lqr_final_ConstP._Gain[i_0 + 12] * lqr_final_X.Integrator_CSTATE[3] +
      (lqr_final_ConstP._Gain[i_0 + 8] * lqr_final_X.Integrator_CSTATE[2] +
       (lqr_final_ConstP._Gain[i_0 + 4] * lqr_final_X.Integrator_CSTATE[1] +
        lqr_final_ConstP._Gain[i_0] * lqr_final_X.Integrator_CSTATE[0]));

    /* Gain: '<Root>/                   ' incorporates:
     *  Inport: '<Root>/X'
     *  Sum: '<Root>/Sum'
     */
    tmp[i_0] = 0.0;
    for (i = 0; i < 12; i++) {
      tmp[i_0] += lqr_final_ConstP._Gain_g[(i << 2) + i_0] * lqr_final_U.X[i];
    }

    /* End of Gain: '<Root>/                   ' */

    /* Sum: '<Root>/Sum2' incorporates:
     *  Constant: '<Root>/              '
     *  Sum: '<Root>/Sum'
     */
    rtb_Sum2[i_0] = (u0 - tmp[i_0]) + lqr_final_ConstP._Value[i_0];
  }

  /* Outport: '<Root>/virtual_control' */
  lqr_final_Y.virtual_control[0] = rtb_Sum2[0];
  lqr_final_Y.virtual_control[1] = rtb_Sum2[1];
  lqr_final_Y.virtual_control[2] = rtb_Sum2[2];
  lqr_final_Y.virtual_control[3] = rtb_Sum2[3];
  for (i_0 = 0; i_0 < 6; i_0++) {
    /* Gain: '<Root>/Gain' incorporates:
     *  Gain: '<Root>/Gain2'
     */
    u0 = lqr_final_ConstP.Gain_Gain[i_0 + 18] * rtb_Sum2[3] +
      (lqr_final_ConstP.Gain_Gain[i_0 + 12] * rtb_Sum2[2] +
       (lqr_final_ConstP.Gain_Gain[i_0 + 6] * rtb_Sum2[1] +
        lqr_final_ConstP.Gain_Gain[i_0] * rtb_Sum2[0]));

    /* Sqrt: '<Root>/Sqrt1' incorporates:
     *  Gain: '<Root>/Gain2'
     */
    rtb_Sqrt1 = std::sqrt(116978.4923343994 * u0);

    /* Gain: '<Root>/rads_to_RPM' */
    rtb_rads_to_RPM = 9.5493 * rtb_Sqrt1;

    /* Gain: '<Root>/mapping_0_200' incorporates:
     *  Constant: '<Root>/Constant1'
     *  Sum: '<Root>/Sum3'
     */
    u0 = (rtb_rads_to_RPM - 1250.0) * 0.022857142857142857;

    /* Saturate: '<Root>/Saturation' */
    if (u0 > 200.0) {
      /* Outport: '<Root>/motor_command' */
      lqr_final_Y.motor_command[i_0] = 200.0;
    } else if (u0 < 0.0) {
      /* Outport: '<Root>/motor_command' */
      lqr_final_Y.motor_command[i_0] = 0.0;
    } else {
      /* Outport: '<Root>/motor_command' */
      lqr_final_Y.motor_command[i_0] = u0;
    }

    /* End of Saturate: '<Root>/Saturation' */

    /* Outport: '<Root>/motor_speed' */
    lqr_final_Y.motor_speed[i_0] = rtb_Sqrt1;

    /* Outport: '<Root>/motor_RPM' */
    lqr_final_Y.motor_RPM[i_0] = rtb_rads_to_RPM;
  }

  /* Saturate: '<Root>/Saturation1' incorporates:
   *  Inport: '<Root>/x_ref'
   */
  if (lqr_final_U.x_ref > 1.0) {
    u0 = 1.0;
  } else if (lqr_final_U.x_ref < -1.5) {
    u0 = -1.5;
  } else {
    u0 = lqr_final_U.x_ref;
  }

  /* End of Saturate: '<Root>/Saturation1' */

  /* Sum: '<Root>/Sum1' incorporates:
   *  Inport: '<Root>/X'
   */
  u0 -= lqr_final_U.X[0];

  /* Saturate: '<Root>/Saturation4' */
  if (u0 > 1.0) {
    lqr_final_B.Saturation4 = 1.0;
  } else if (u0 < -1.0) {
    lqr_final_B.Saturation4 = -1.0;
  } else {
    lqr_final_B.Saturation4 = u0;
  }

  /* End of Saturate: '<Root>/Saturation4' */

  /* Saturate: '<Root>/Saturation2' incorporates:
   *  Inport: '<Root>/y_ref'
   */
  if (lqr_final_U.y_ref > 1.5) {
    u0 = 1.5;
  } else if (lqr_final_U.y_ref < -1.5) {
    u0 = -1.5;
  } else {
    u0 = lqr_final_U.y_ref;
  }

  /* End of Saturate: '<Root>/Saturation2' */

  /* Sum: '<Root>/Sum4' incorporates:
   *  Inport: '<Root>/X'
   */
  u0 -= lqr_final_U.X[1];

  /* Saturate: '<Root>/Saturation6' */
  if (u0 > 1.0) {
    lqr_final_B.Saturation6 = 1.0;
  } else if (u0 < -1.0) {
    lqr_final_B.Saturation6 = -1.0;
  } else {
    lqr_final_B.Saturation6 = u0;
  }

  /* End of Saturate: '<Root>/Saturation6' */

  /* Saturate: '<Root>/Saturation3' incorporates:
   *  Inport: '<Root>/z_ref'
   */
  if (lqr_final_U.z_ref > 1.5) {
    u0 = 1.5;
  } else if (lqr_final_U.z_ref < 0.1) {
    u0 = 0.1;
  } else {
    u0 = lqr_final_U.z_ref;
  }

  /* End of Saturate: '<Root>/Saturation3' */

  /* Sum: '<Root>/Sum5' incorporates:
   *  Inport: '<Root>/X'
   */
  u0 -= lqr_final_U.X[2];

  /* Saturate: '<Root>/Saturation7' */
  if (u0 > 0.5) {
    lqr_final_B.Saturation7 = 0.5;
  } else if (u0 < -0.5) {
    lqr_final_B.Saturation7 = -0.5;
  } else {
    lqr_final_B.Saturation7 = u0;
  }

  /* End of Saturate: '<Root>/Saturation7' */

  /* Saturate: '<Root>/Saturation5' incorporates:
   *  Inport: '<Root>/psi_ref'
   */
  if (lqr_final_U.psi_ref > 6.2831853071795862) {
    u0 = 6.2831853071795862;
  } else if (lqr_final_U.psi_ref < -6.2831853071795862) {
    u0 = -6.2831853071795862;
  } else {
    u0 = lqr_final_U.psi_ref;
  }

  /* End of Saturate: '<Root>/Saturation5' */

  /* Sum: '<Root>/Sum6' incorporates:
   *  Inport: '<Root>/X'
   */
  u0 -= lqr_final_U.X[8];

  /* Saturate: '<Root>/Saturation8' */
  if (u0 > 0.78539816339744828) {
    lqr_final_B.Saturation8 = 0.78539816339744828;
  } else if (u0 < -0.78539816339744828) {
    lqr_final_B.Saturation8 = -0.78539816339744828;
  } else {
    lqr_final_B.Saturation8 = u0;
  }

  /* End of Saturate: '<Root>/Saturation8' */
  if (rtmIsMajorTimeStep((&lqr_final_M))) {
    rt_ertODEUpdateContinuousStates(&(&lqr_final_M)->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++(&lqr_final_M)->Timing.clockTick0)) {
      ++(&lqr_final_M)->Timing.clockTickH0;
    }

    (&lqr_final_M)->Timing.t[0] = rtsiGetSolverStopTime(&(&lqr_final_M)
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
      (&lqr_final_M)->Timing.clockTick1++;
      if (!(&lqr_final_M)->Timing.clockTick1) {
        (&lqr_final_M)->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void lqr_finalModelClass::lqr_final_derivatives()
{
  XDot_lqr_final_T *_rtXdot;
  _rtXdot = ((XDot_lqr_final_T *) (&lqr_final_M)->derivs);

  /* Derivatives for Integrator: '<Root>/Integrator' */
  _rtXdot->Integrator_CSTATE[0] = lqr_final_B.Saturation4;
  _rtXdot->Integrator_CSTATE[1] = lqr_final_B.Saturation6;
  _rtXdot->Integrator_CSTATE[2] = lqr_final_B.Saturation7;
  _rtXdot->Integrator_CSTATE[3] = lqr_final_B.Saturation8;
}

/* Model initialize function */
void lqr_finalModelClass::initialize()
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)(&lqr_final_M), 0,
                sizeof(RT_MODEL_lqr_final_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&(&lqr_final_M)->solverInfo, &(&lqr_final_M)
                          ->Timing.simTimeStep);
    rtsiSetTPtr(&(&lqr_final_M)->solverInfo, &rtmGetTPtr((&lqr_final_M)));
    rtsiSetStepSizePtr(&(&lqr_final_M)->solverInfo, &(&lqr_final_M)
                       ->Timing.stepSize0);
    rtsiSetdXPtr(&(&lqr_final_M)->solverInfo, &(&lqr_final_M)->derivs);
    rtsiSetContStatesPtr(&(&lqr_final_M)->solverInfo, (real_T **) &(&lqr_final_M)
                         ->contStates);
    rtsiSetNumContStatesPtr(&(&lqr_final_M)->solverInfo, &(&lqr_final_M)
      ->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&lqr_final_M)->solverInfo, &(&lqr_final_M
      )->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&lqr_final_M)->solverInfo,
      &(&lqr_final_M)->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&lqr_final_M)->solverInfo,
      &(&lqr_final_M)->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&(&lqr_final_M)->solverInfo, (&rtmGetErrorStatus
      ((&lqr_final_M))));
    rtsiSetRTModelPtr(&(&lqr_final_M)->solverInfo, (&lqr_final_M));
  }

  rtsiSetSimTimeStep(&(&lqr_final_M)->solverInfo, MAJOR_TIME_STEP);
  (&lqr_final_M)->intgData.y = (&lqr_final_M)->odeY;
  (&lqr_final_M)->intgData.f[0] = (&lqr_final_M)->odeF[0];
  (&lqr_final_M)->intgData.f[1] = (&lqr_final_M)->odeF[1];
  (&lqr_final_M)->intgData.f[2] = (&lqr_final_M)->odeF[2];
  (&lqr_final_M)->intgData.f[3] = (&lqr_final_M)->odeF[3];
  (&lqr_final_M)->intgData.f[4] = (&lqr_final_M)->odeF[4];
  (&lqr_final_M)->intgData.f[5] = (&lqr_final_M)->odeF[5];
  getRTM()->contStates = ((X_lqr_final_T *) &lqr_final_X);
  rtsiSetSolverData(&(&lqr_final_M)->solverInfo, (void *)&(&lqr_final_M)
                    ->intgData);
  rtsiSetSolverName(&(&lqr_final_M)->solverInfo,"ode5");
  rtmSetTPtr(getRTM(), &(&lqr_final_M)->Timing.tArray[0]);
  (&lqr_final_M)->Timing.stepSize0 = 0.016666666666666666;

  /* block I/O */
  (void) memset(((void *) &lqr_final_B), 0,
                sizeof(B_lqr_final_T));

  /* states (continuous) */
  {
    (void) memset((void *)&lqr_final_X, 0,
                  sizeof(X_lqr_final_T));
  }

  /* external inputs */
  (void)memset((void *)&lqr_final_U, 0, sizeof(ExtU_lqr_final_T));

  /* external outputs */
  (void) memset((void *)&lqr_final_Y, 0,
                sizeof(ExtY_lqr_final_T));

  /* InitializeConditions for Integrator: '<Root>/Integrator' */
  lqr_final_X.Integrator_CSTATE[0] = 0.0;
  lqr_final_X.Integrator_CSTATE[1] = 0.0;
  lqr_final_X.Integrator_CSTATE[2] = 0.0;
  lqr_final_X.Integrator_CSTATE[3] = 0.0;
}

/* Model terminate function */
void lqr_finalModelClass::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
lqr_finalModelClass::lqr_finalModelClass()
{
}

/* Destructor */
lqr_finalModelClass::~lqr_finalModelClass()
{
  /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_lqr_final_T * lqr_finalModelClass::getRTM()
{
  return (&lqr_final_M);
}
