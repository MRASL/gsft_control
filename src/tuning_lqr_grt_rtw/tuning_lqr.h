/*
 * tuning_lqr.h
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "tuning_lqr".
 *
 * Model version              : 1.1142
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Fri Apr  6 11:33:33 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Passed (1), Warnings (3), Error (0)
 */

#ifndef RTW_HEADER_tuning_lqr_h_
#define RTW_HEADER_tuning_lqr_h_
#include <cmath>
#include <string.h>
#ifndef tuning_lqr_COMMON_INCLUDES_
# define tuning_lqr_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* tuning_lqr_COMMON_INCLUDES_ */

#include "tuning_lqr_types.h"

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
  real_T d_z;                          /* '<S2>/Sum5' */
  real_T d_z_k;                        /* '<Root>/Rate Transition   ' */
  real_T vz;                           /* '<Root>/Rate Transition   ' */
  real_T Sum1;                         /* '<S9>/Sum1' */
  real_T dT;                           /* '<Root>/               ' */
  real_T d_x;                          /* '<S2>/Sum1' */
  real_T d_x_b;                        /* '<Root>/Rate Transition   ' */
  real_T vx;                           /* '<Root>/Rate Transition   ' */
  real_T d_y;                          /* '<S2>/Sum4' */
  real_T d_y_l;                        /* '<Root>/Rate Transition   ' */
  real_T vy;                           /* '<Root>/Rate Transition   ' */
  real_T RateTransition;               /* '<Root>/Rate Transition  ' */
  real_T Sum7;                         /* '<Root>/Sum7' */
  real_T u;                            /* '<Root>/                        ' */
  real_T roll;                         /* '<S5>/roll' */
  real_T Sum8;                         /* '<Root>/Sum8' */
  real_T u_c;                          /* '<Root>/         ' */
  real_T pitch;                        /* '<S4>/pitch' */
  real_T Sum[4];                       /* '<S2>/Sum' */
  real_T RateTransition_g[4];          /* '<Root>/Rate Transition ' */
  real_T x_e;                          /* '<S6>/x_e' */
  real_T y_e;                          /* '<S7>/y_e' */
  real_T yaw_e;                        /* '<S8>/yaw_e' */
  real_T z_e;                          /* '<S9>/z_e' */
} B_tuning_lqr_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T Integrator1_CSTATE;           /* '<S9>/Integrator1' */
  real_T Integrator1_CSTATE_h;         /* '<S6>/Integrator1' */
  real_T Integrator1_CSTATE_g;         /* '<S7>/Integrator1' */
  real_T Integrator1_CSTATE_j;         /* '<S8>/Integrator1' */
} X_tuning_lqr_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T Integrator1_CSTATE;           /* '<S9>/Integrator1' */
  real_T Integrator1_CSTATE_h;         /* '<S6>/Integrator1' */
  real_T Integrator1_CSTATE_g;         /* '<S7>/Integrator1' */
  real_T Integrator1_CSTATE_j;         /* '<S8>/Integrator1' */
} XDot_tuning_lqr_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator1_CSTATE;        /* '<S9>/Integrator1' */
  boolean_T Integrator1_CSTATE_h;      /* '<S6>/Integrator1' */
  boolean_T Integrator1_CSTATE_g;      /* '<S7>/Integrator1' */
  boolean_T Integrator1_CSTATE_j;      /* '<S8>/Integrator1' */
} XDis_tuning_lqr_T;

#ifndef ODE4_INTG
#define ODE4_INTG

/* ODE4 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[4];                        /* derivatives */
} ODE4_IntgData;

#endif

/* Constant parameters (auto storage) */
typedef struct {
  /* Expression: B_ENU_inv
   * Referenced by: '<Root>/Control Allocation'
   */
  real_T ControlAllocation_Gain[24];
} ConstP_tuning_lqr_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T X[12];                        /* '<Root>/X' */
  real_T Y0[4];                        /* '<Root>/Y0' */
  real_T mode;                         /* '<Root>/mode' */
  real_T ref[4];                       /* '<Root>/ref' */
  real_T LOE_t[6];                     /* '<Root>/LOE_t' */
  real_T LOE_a[6];                     /* '<Root>/LOE_a' */
  real_T gain[18];                     /* '<Root>/gain' */
} ExtU_tuning_lqr_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T motor_command[6];             /* '<Root>/motor_command' */
  real_T virtual_control[4];           /* '<Root>/virtual_control' */
  real_T ref_out[4];                   /* '<Root>/ref_out' */
  real_T LOE[6];                       /* '<Root>/LOE' */
} ExtY_tuning_lqr_T;

/* Real-time Model Data Structure */
struct tag_RTM_tuning_lqr_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_tuning_lqr_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T blkStateChange;
  real_T odeY[4];
  real_T odeF[4][4];
  ODE4_IntgData intgData;

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
    struct {
      uint8_T TID[3];
    } TaskCounters;

    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[3];
  } Timing;
};

#ifdef __cplusplus

extern "C" {

#endif

#ifdef __cplusplus

}
#endif

/* Constant parameters (auto storage) */
extern const ConstP_tuning_lqr_T tuning_lqr_ConstP;

/* Class declaration for model tuning_lqr */
class tuning_lqrModelClass {
  /* public data and function members */
 public:
  /* External inputs */
  ExtU_tuning_lqr_T tuning_lqr_U;

  /* External outputs */
  ExtY_tuning_lqr_T tuning_lqr_Y;

  /* model initialize function */
  void initialize();

  /* model step function */
  void step();

  /* model terminate function */
  void terminate();

  /* Constructor */
  tuning_lqrModelClass();

  /* Destructor */
  ~tuning_lqrModelClass();

  /* Real-Time Model get method */
  RT_MODEL_tuning_lqr_T * getRTM();

  /* private data and function members */
 private:
  /* Block signals */
  B_tuning_lqr_T tuning_lqr_B;
  X_tuning_lqr_T tuning_lqr_X;       /* Block continuous states */

  /* Real-Time Model */
  RT_MODEL_tuning_lqr_T tuning_lqr_M;

  /* Continuous states update member function*/
  void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si );

  /* Derivatives member function */
  void tuning_lqr_derivatives();
};

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S4>/Reshape' : Reshape block reduction
 * Block '<S5>/Reshape' : Reshape block reduction
 * Block '<S6>/Reshape' : Reshape block reduction
 * Block '<S7>/Reshape' : Reshape block reduction
 * Block '<S8>/Reshape' : Reshape block reduction
 * Block '<S9>/Reshape' : Reshape block reduction
 */

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
 * '<Root>' : 'tuning_lqr'
 * '<S1>'   : 'tuning_lqr/Actuator_Fault'
 * '<S2>'   : 'tuning_lqr/Test_config_and_data'
 * '<S3>'   : 'tuning_lqr/Thrust2command'
 * '<S4>'   : 'tuning_lqr/pitch_controller'
 * '<S5>'   : 'tuning_lqr/roll_controller'
 * '<S6>'   : 'tuning_lqr/x_controller '
 * '<S7>'   : 'tuning_lqr/y_controller'
 * '<S8>'   : 'tuning_lqr/yaw_controller'
 * '<S9>'   : 'tuning_lqr/z_controller'
 * '<S10>'  : 'tuning_lqr/Test_config_and_data/FFW'
 * '<S11>'  : 'tuning_lqr/Test_config_and_data/LOE_'
 * '<S12>'  : 'tuning_lqr/Test_config_and_data/MATLAB Function'
 */
#endif                                 /* RTW_HEADER_tuning_lqr_h_ */
