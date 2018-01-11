/*
 * lqr_inner.h
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "lqr_inner".
 *
 * Model version              : 1.530
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Wed Jan 10 21:31:40 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Passed (1), Warnings (3), Error (0)
 */

#ifndef RTW_HEADER_lqr_inner_h_
#define RTW_HEADER_lqr_inner_h_
#include <cmath>
#include <string.h>
#ifndef lqr_inner_COMMON_INCLUDES_
# define lqr_inner_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* lqr_inner_COMMON_INCLUDES_ */

#include "lqr_inner_types.h"

/* Shared type includes */
#include "multiword_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetBlkStateChangeFlag
# define rtmGetBlkStateChangeFlag(rtm) ((rtm)->blkStateChange)
#endif

#ifndef rtmSetBlkStateChangeFlag
# define rtmSetBlkStateChangeFlag(rtm, val) ((rtm)->blkStateChange = (val))
#endif

#ifndef rtmGetContStateDisabled
# define rtmGetContStateDisabled(rtm)  ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
# define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
# define rtmGetContStates(rtm)         ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
# define rtmSetContStates(rtm, val)    ((rtm)->contStates = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
# define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
# define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetIntgData
# define rtmGetIntgData(rtm)           ((rtm)->intgData)
#endif

#ifndef rtmSetIntgData
# define rtmSetIntgData(rtm, val)      ((rtm)->intgData = (val))
#endif

#ifndef rtmGetOdeF
# define rtmGetOdeF(rtm)               ((rtm)->odeF)
#endif

#ifndef rtmSetOdeF
# define rtmSetOdeF(rtm, val)          ((rtm)->odeF = (val))
#endif

#ifndef rtmGetOdeY
# define rtmGetOdeY(rtm)               ((rtm)->odeY)
#endif

#ifndef rtmSetOdeY
# define rtmSetOdeY(rtm, val)          ((rtm)->odeY = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
# define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
# define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
# define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
# define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetZCCacheNeedsReset
# define rtmGetZCCacheNeedsReset(rtm)  ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
# define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
# define rtmGetdX(rtm)                 ((rtm)->derivs)
#endif

#ifndef rtmSetdX
# define rtmSetdX(rtm, val)            ((rtm)->derivs = (val))
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

/* Block signals (auto storage) */
typedef struct {
  real_T Saturation4;                  /* '<Root>/Saturation4' */
  real_T Saturation6;                  /* '<Root>/Saturation6' */
  real_T Saturation7;                  /* '<Root>/Saturation7' */
  real_T Saturation8;                  /* '<Root>/Saturation8' */
} B_lqr_inner_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T Integrator_CSTATE[4];         /* '<Root>/Integrator' */
} X_lqr_inner_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T Integrator_CSTATE[4];         /* '<Root>/Integrator' */
} XDot_lqr_inner_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE[4];      /* '<Root>/Integrator' */
} XDis_lqr_inner_T;

#ifndef ODE5_INTG
#define ODE5_INTG

/* ODE5 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[6];                        /* derivatives */
} ODE5_IntgData;

#endif

/* Constant parameters (auto storage) */
typedef struct {
  /* Expression: [mass*gra 0 0 0]'
   * Referenced by: '<Root>/              '
   */
  real_T _Value[4];

  /* Expression: Ki_lqr
   * Referenced by: '<Root>/ '
   */
  real_T _Gain[16];

  /* Expression: Kx_lqr
   * Referenced by: '<Root>/                   '
   */
  real_T _Gain_g[32];

  /* Expression: B_ENU_inv
   * Referenced by: '<Root>/Gain'
   */
  real_T Gain_Gain[24];
} ConstP_lqr_inner_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T X[12];                        /* '<Root>/X' */
} ExtU_lqr_inner_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T motor_command[6];             /* '<Root>/motor_command' */
  real_T virtual_control[4];           /* '<Root>/virtual_control' */
  real_T motor_speed[6];               /* '<Root>/motor_speed' */
  real_T motor_RPM[6];                 /* '<Root>/motor_RPM' */
  real_T ref[4];                       /* '<Root>/ref' */
} ExtY_lqr_inner_T;

/* Real-time Model Data Structure */
struct tag_RTM_lqr_inner_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_lqr_inner_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T blkStateChange;
  real_T odeY[4];
  real_T odeF[6][4];
  ODE5_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

#ifdef __cplusplus

extern "C" {

#endif

#ifdef __cplusplus

}
#endif

/* Constant parameters (auto storage) */
extern const ConstP_lqr_inner_T lqr_inner_ConstP;

/* Class declaration for model lqr_inner */
class lqr_innerModelClass {
  /* public data and function members */
 public:
  /* External inputs */
  ExtU_lqr_inner_T lqr_inner_U;

  /* External outputs */
  ExtY_lqr_inner_T lqr_inner_Y;

  /* model initialize function */
  void initialize();

  /* model step function */
  void step();

  /* model terminate function */
  void terminate();

  /* Constructor */
  lqr_innerModelClass();

  /* Destructor */
  ~lqr_innerModelClass();

  /* Real-Time Model get method */
  RT_MODEL_lqr_inner_T * getRTM();

  /* private data and function members */
 private:
  /* Block signals */
  B_lqr_inner_T lqr_inner_B;
  X_lqr_inner_T lqr_inner_X;           /* Block continuous states */

  /* Real-Time Model */
  RT_MODEL_lqr_inner_T lqr_inner_M;

  /* Continuous states update member function*/
  void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si );

  /* Derivatives member function */
  void lqr_inner_derivatives();
};

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'lqr_inner'
 * '<S1>'   : 'lqr_inner/MATLAB Function'
 */
#endif                                 /* RTW_HEADER_lqr_inner_h_ */
