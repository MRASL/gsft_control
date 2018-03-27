/*
 * tunning_lqr.h
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "tunning_lqr".
 *
 * Model version              : 1.1069
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Tue Mar 27 12:15:31 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Passed (1), Warnings (3), Error (0)
 */

#ifndef RTW_HEADER_tunning_lqr_h_
#define RTW_HEADER_tunning_lqr_h_
#include <cmath>
#include <string.h>
#ifndef tunning_lqr_COMMON_INCLUDES_
# define tunning_lqr_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* tunning_lqr_COMMON_INCLUDES_ */

#include "tunning_lqr_types.h"

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
  real_T dz;                           /* '<Root>/Sum5' */
  real_T dz_h;                         /* '<Root>/Rate Transition   ' */
  real_T dzd;                          /* '<Root>/Rate Transition   ' */
  real_T Sum1;                         /* '<S9>/Sum1' */
  real_T T;                            /* '<Root>/               ' */
  real_T dx;                           /* '<Root>/Sum1' */
  real_T dx_o;                         /* '<Root>/Rate Transition   ' */
  real_T dxd;                          /* '<Root>/Rate Transition   ' */
  real_T dy;                           /* '<Root>/Sum4' */
  real_T dy_m;                         /* '<Root>/Rate Transition   ' */
  real_T dyd;                          /* '<Root>/Rate Transition   ' */
  real_T RateTransition;               /* '<Root>/Rate Transition  ' */
  real_T Fcn1;                         /* '<Root>/Fcn1' */
  real_T u;                            /* '<Root>/                        ' */
  real_T roll;                         /* '<S5>/roll' */
  real_T Fcn;                          /* '<Root>/Fcn' */
  real_T u_c;                          /* '<Root>/         ' */
  real_T pitch;                        /* '<S4>/pitch' */
  real_T Sum[4];                       /* '<Root>/Sum' */
  real_T RateTransition_g[4];          /* '<Root>/Rate Transition ' */
  real_T x_e;                          /* '<S6>/x_e' */
  real_T y_e;                          /* '<S7>/y_e' */
  real_T yaw_e;                        /* '<S8>/yaw_e' */
  real_T z_e;                          /* '<S9>/z_e' */
} B_tunning_lqr_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T Integrator1_CSTATE;           /* '<S9>/Integrator1' */
  real_T Integrator1_CSTATE_h;         /* '<S6>/Integrator1' */
  real_T Integrator1_CSTATE_g;         /* '<S7>/Integrator1' */
  real_T Integrator1_CSTATE_j;         /* '<S8>/Integrator1' */
} X_tunning_lqr_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T Integrator1_CSTATE;           /* '<S9>/Integrator1' */
  real_T Integrator1_CSTATE_h;         /* '<S6>/Integrator1' */
  real_T Integrator1_CSTATE_g;         /* '<S7>/Integrator1' */
  real_T Integrator1_CSTATE_j;         /* '<S8>/Integrator1' */
} XDot_tunning_lqr_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator1_CSTATE;        /* '<S9>/Integrator1' */
  boolean_T Integrator1_CSTATE_h;      /* '<S6>/Integrator1' */
  boolean_T Integrator1_CSTATE_g;      /* '<S7>/Integrator1' */
  boolean_T Integrator1_CSTATE_j;      /* '<S8>/Integrator1' */
} XDis_tunning_lqr_T;

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
   * Referenced by: '<Root>/                 '
   */
  real_T _Gain[24];
} ConstP_tunning_lqr_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T gain[16];                     /* '<Root>/gain' */
  real_T LOE_a[6];                     /* '<Root>/LOE_a' */
  real_T X[12];                        /* '<Root>/X' */
  real_T mode;                         /* '<Root>/mode' */
  real_T ref[4];                       /* '<Root>/ref' */
  real_T Y0[4];                        /* '<Root>/Y0' */
  real_T LOE_t[6];                     /* '<Root>/LOE_t' */
} ExtU_tunning_lqr_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T motor_command[6];             /* '<Root>/motor_command' */
  real_T virtual_control[4];           /* '<Root>/virtual_control' */
  real_T ref_out[4];                   /* '<Root>/ref_out' */
  real_T LOE[6];                       /* '<Root>/LOE' */
} ExtY_tunning_lqr_T;

/* Real-time Model Data Structure */
struct tag_RTM_tunning_lqr_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_tunning_lqr_T *contStates;
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
extern const ConstP_tunning_lqr_T tunning_lqr_ConstP;

/* Class declaration for model tunning_lqr */
class tunning_lqrModelClass {
  /* public data and function members */
 public:
  /* External inputs */
  ExtU_tunning_lqr_T tunning_lqr_U;

  /* External outputs */
  ExtY_tunning_lqr_T tunning_lqr_Y;

  /* model initialize function */
  void initialize();

  /* model step function */
  void step();

  /* model terminate function */
  void terminate();

  /* Constructor */
  tunning_lqrModelClass();

  /* Destructor */
  ~tunning_lqrModelClass();

  /* Real-Time Model get method */
  RT_MODEL_tunning_lqr_T * getRTM();

  /* private data and function members */
 private:
  /* Block signals */
  B_tunning_lqr_T tunning_lqr_B;
  X_tunning_lqr_T tunning_lqr_X;       /* Block continuous states */

  /* Real-Time Model */
  RT_MODEL_tunning_lqr_T tunning_lqr_M;

  /* Continuous states update member function*/
  void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si );

  /* Derivatives member function */
  void tunning_lqr_derivatives();
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
 * '<Root>' : 'tunning_lqr'
 * '<S1>'   : 'tunning_lqr/Actuator_Fault'
 * '<S2>'   : 'tunning_lqr/LOE_'
 * '<S3>'   : 'tunning_lqr/MATLAB Function'
 * '<S4>'   : 'tunning_lqr/pitch_controller'
 * '<S5>'   : 'tunning_lqr/roll_controller'
 * '<S6>'   : 'tunning_lqr/x_controller '
 * '<S7>'   : 'tunning_lqr/y_controller'
 * '<S8>'   : 'tunning_lqr/yaw_controller'
 * '<S9>'   : 'tunning_lqr/z_controller'
 */
#endif                                 /* RTW_HEADER_tunning_lqr_h_ */
