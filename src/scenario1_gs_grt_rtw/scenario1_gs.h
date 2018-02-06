/*
 * scenario1_gs.h
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "scenario1_gs".
 *
 * Model version              : 1.683
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Wed Jan 31 12:17:48 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Passed (1), Warnings (3), Error (0)
 */

#ifndef RTW_HEADER_scenario1_gs_h_
#define RTW_HEADER_scenario1_gs_h_
#include <cmath>
#include <string.h>
#ifndef scenario1_gs_COMMON_INCLUDES_
# define scenario1_gs_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* scenario1_gs_COMMON_INCLUDES_ */

#include "scenario1_gs_types.h"

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
  real_T dX[12];                       /* '<Root>/Sum' */
  real_T RateTransition5[12];          /* '<Root>/Rate Transition5' */
  real_T u;                            /* '<S7>/                    ' */
  real_T Sum1;                         /* '<S7>/Sum1' */
  real_T ZeroOrderHold;                /* '<Root>/Zero-Order Hold' */
  real_T u_m;                          /* '<S8>/                     ' */
  real_T Sum1_i;                       /* '<S8>/Sum1' */
  real_T ZeroOrderHold1;               /* '<Root>/Zero-Order Hold1' */
  real_T d_ref[4];                     /* '<Root>/Sum1' */
  real_T RateTransition;               /* '<Root>/Rate Transition' */
  real_T RateTransition1;              /* '<Root>/Rate Transition1' */
  real_T psi_e;                        /* '<S5>/psi_e' */
  real_T xe;                           /* '<S7>/xe' */
  real_T ye;                           /* '<S8>/ye' */
  real_T Product[6];                   /* '<S9>/Product' */
} B_scenario1_gs_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T Integrator1_CSTATE;           /* '<S7>/Integrator1' */
  real_T Integrator1_CSTATE_j;         /* '<S8>/Integrator1' */
  real_T Integrator1_CSTATE_b;         /* '<S5>/Integrator1' */
  real_T Integrator1_CSTATE_k[6];      /* '<S9>/Integrator1' */
} X_scenario1_gs_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T Integrator1_CSTATE;           /* '<S7>/Integrator1' */
  real_T Integrator1_CSTATE_j;         /* '<S8>/Integrator1' */
  real_T Integrator1_CSTATE_b;         /* '<S5>/Integrator1' */
  real_T Integrator1_CSTATE_k[6];      /* '<S9>/Integrator1' */
} XDot_scenario1_gs_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator1_CSTATE;        /* '<S7>/Integrator1' */
  boolean_T Integrator1_CSTATE_j;      /* '<S8>/Integrator1' */
  boolean_T Integrator1_CSTATE_b;      /* '<S5>/Integrator1' */
  boolean_T Integrator1_CSTATE_k[6];   /* '<S9>/Integrator1' */
} XDis_scenario1_gs_T;

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
  /* Expression: B_ENU_inv
   * Referenced by: '<Root>/                 '
   */
  real_T _Gain_m[24];
} ConstP_scenario1_gs_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T X[12];                        /* '<Root>/X' */
  real_T X0[4];                        /* '<Root>/X0' */
} ExtU_scenario1_gs_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T motor_command[6];             /* '<Root>/motor_command' */
  real_T virtual_control[4];           /* '<Root>/virtual_control' */
  real_T motor_speed[6];               /* '<Root>/motor_speed' */
  real_T motor_RPM[6];                 /* '<Root>/motor_RPM' */
  real_T ref[4];                       /* '<Root>/ref' */
} ExtY_scenario1_gs_T;

/* Real-time Model Data Structure */
struct tag_RTM_scenario1_gs_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_scenario1_gs_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T blkStateChange;
  real_T odeY[9];
  real_T odeF[6][9];
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
extern const ConstP_scenario1_gs_T scenario1_gs_ConstP;

/* Class declaration for model scenario1_gs */
class scenario1_gsModelClass {
  /* public data and function members */
 public:
  /* External inputs */
  ExtU_scenario1_gs_T scenario1_gs_U;

  /* External outputs */
  ExtY_scenario1_gs_T scenario1_gs_Y;

  /* model initialize function */
  void initialize();

  /* model step function */
  void step();

  /* model terminate function */
  void terminate();

  /* Constructor */
  scenario1_gsModelClass();

  /* Destructor */
  ~scenario1_gsModelClass();

  /* Real-Time Model get method */
  RT_MODEL_scenario1_gs_T * getRTM();

  /* private data and function members */
 private:
  /* Block signals */
  B_scenario1_gs_T scenario1_gs_B;
  X_scenario1_gs_T scenario1_gs_X;     /* Block continuous states */

  /* Real-Time Model */
  RT_MODEL_scenario1_gs_T scenario1_gs_M;

  /* Continuous states update member function*/
  void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si );

  /* Derivatives member function */
  void scenario1_gs_derivatives();
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
 * '<Root>' : 'scenario1_gs'
 * '<S1>'   : 'scenario1_gs/Actuator_Fault'
 * '<S2>'   : 'scenario1_gs/FDD'
 * '<S3>'   : 'scenario1_gs/MATLAB Function'
 * '<S4>'   : 'scenario1_gs/phi_controller1'
 * '<S5>'   : 'scenario1_gs/psi_controller '
 * '<S6>'   : 'scenario1_gs/teta_controller1'
 * '<S7>'   : 'scenario1_gs/x_controller '
 * '<S8>'   : 'scenario1_gs/y_controller '
 * '<S9>'   : 'scenario1_gs/z_controller '
 * '<S10>'  : 'scenario1_gs/z_controller /MATLAB Function'
 */
#endif                                 /* RTW_HEADER_scenario1_gs_h_ */