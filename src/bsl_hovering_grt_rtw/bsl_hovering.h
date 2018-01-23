/*
 * bsl_hovering.h
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

#ifndef RTW_HEADER_bsl_hovering_h_
#define RTW_HEADER_bsl_hovering_h_
#include <cmath>
#include <string.h>
#ifndef bsl_hovering_COMMON_INCLUDES_
# define bsl_hovering_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* bsl_hovering_COMMON_INCLUDES_ */

#include "bsl_hovering_types.h"

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
  real_T Gain[6];                      /* '<Root>/Gain' */
  real_T gamma_hat_k1k[6];             /* '<S5>/       ' */
  real_T K_gamma_k1[36];               /* '<S5>/Divide' */
  real_T Product[6];                   /* '<S5>/Product' */
  real_T X_tildle_k1k[12];             /* '<S2>/Sum1' */
  real_T C[6];                         /* '<S6>/C' */
  real_T Sum1[6];                      /* '<S5>/Sum1' */
  real_T C_p[6];                       /* '<S2>/C' */
  real_T K_tildle_x_k1[72];            /* '<S2>/Divide' */
  real_T Sum3[12];                     /* '<S2>/Sum3' */
  real_T psi_e;                        /* '<Root>/psi_e' */
  real_T xe;                           /* '<Root>/xe' */
  real_T ye;                           /* '<Root>/ye' */
  real_T ze;                           /* '<Root>/ze' */
} B_bsl_hovering_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T _DSTATE[6];                   /* '<S5>/       ' */
  real_T UnitDelay1_DSTATE[36];        /* '<S5>/Unit Delay1' */
  real_T UnitDelay_DSTATE[72];         /* '<S3>/Unit Delay' */
  real_T UnitDelay1_DSTATE_g[144];     /* '<S2>/Unit Delay1' */
  real_T UnitDelay_DSTATE_h[12];       /* '<S2>/Unit Delay' */
  real_T Memory_PreviousInput[6];      /* '<Root>/Memory' */
  real_T Divide_DWORK4[36];            /* '<S3>/Divide' */
  real_T Divide_DWORK4_k[36];          /* '<S5>/Divide' */
  real_T Divide_DWORK4_m[36];          /* '<S2>/Divide' */
} DW_bsl_hovering_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T Integrator_CSTATE[4];         /* '<Root>/Integrator' */
} X_bsl_hovering_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T Integrator_CSTATE[4];         /* '<Root>/Integrator' */
} XDot_bsl_hovering_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE[4];      /* '<Root>/Integrator' */
} XDis_bsl_hovering_T;

/* Invariant block signals (auto storage) */
typedef const struct tag_ConstB_bsl_hovering_T {
  real_T Transpose[72];                /* '<S6>/Transpose' */
} ConstB_bsl_hovering_T;

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
  real_T _Gain_g[48];

  /* Expression: B_ENU_inv
   * Referenced by: '<Root>/Gain'
   */
  real_T Gain_Gain[24];

  /* Expression: Qgamma
   * Referenced by: '<S5>/Q_gamma'
   */
  real_T Q_gamma_Value[36];

  /* Expression: Pgamma0
   * Referenced by: '<S5>/Unit Delay1'
   */
  real_T UnitDelay1_InitialCondition[36];

  /* Pooled Parameter (Expression: C)
   * Referenced by:
   *   '<S2>/     '
   *   '<S2>/C'
   *   '<S2>/C1'
   *   '<S3>/                      '
   *   '<S6>/     '
   *   '<S6>/C'
   */
  real_T pooled2[72];

  /* Pooled Parameter (Expression: A)
   * Referenced by:
   *   '<S2>/A'
   *   '<S2>/A1'
   *   '<S3>/     '
   */
  real_T pooled3[144];

  /* Pooled Parameter (Expression: B)
   * Referenced by:
   *   '<S2>/B'
   *   '<S3>/          '
   */
  real_T pooled4[72];

  /* Expression: Qx
   * Referenced by: '<S2>/Q_x'
   */
  real_T Q_x_Value[144];

  /* Expression: Px_tilde0
   * Referenced by: '<S2>/Unit Delay1'
   */
  real_T UnitDelay1_InitialCondition_g[144];

  /* Expression: A'
   * Referenced by: '<S2>/A''
   */
  real_T A_Gain[144];

  /* Pooled Parameter (Expression: R)
   * Referenced by:
   *   '<S2>/R'
   *   '<S6>/R'
   */
  real_T pooled5[36];

  /* Expression: [0 0 0 0 0 bias 0 0 0 0 0 0]
   * Referenced by: '<S2>/Constant'
   */
  real_T Constant_Value[12];

  /* Expression: C'
   * Referenced by: '<S2>/C''
   */
  real_T C_Gain[72];
} ConstP_bsl_hovering_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T X[12];                        /* '<Root>/X' */
} ExtU_bsl_hovering_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T motor_command[6];             /* '<Root>/motor_command' */
  real_T virtual_control[4];           /* '<Root>/virtual_control' */
  real_T motor_speed[6];               /* '<Root>/motor_speed' */
  real_T motor_RPM[6];                 /* '<Root>/motor_RPM' */
  real_T gamma[6];                     /* '<Root>/gamma' */
} ExtY_bsl_hovering_T;

/* Real-time Model Data Structure */
struct tag_RTM_bsl_hovering_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_bsl_hovering_T *contStates;
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

extern const ConstB_bsl_hovering_T bsl_hovering_ConstB;/* constant block i/o */

/* Constant parameters (auto storage) */
extern const ConstP_bsl_hovering_T bsl_hovering_ConstP;

/* Class declaration for model bsl_hovering */
class bsl_hoveringModelClass {
  /* public data and function members */
 public:
  /* External inputs */
  ExtU_bsl_hovering_T bsl_hovering_U;

  /* External outputs */
  ExtY_bsl_hovering_T bsl_hovering_Y;

  /* model initialize function */
  void initialize();

  /* model step function */
  void step();

  /* model terminate function */
  void terminate();

  /* Constructor */
  bsl_hoveringModelClass();

  /* Destructor */
  ~bsl_hoveringModelClass();

  /* Real-Time Model get method */
  RT_MODEL_bsl_hovering_T * getRTM();

  /* private data and function members */
 private:
  /* Block signals */
  B_bsl_hovering_T bsl_hovering_B;

  /* Block states */
  DW_bsl_hovering_T bsl_hovering_DW;
  X_bsl_hovering_T bsl_hovering_X;     /* Block continuous states */

  /* Real-Time Model */
  RT_MODEL_bsl_hovering_T bsl_hovering_M;

  /* Continuous states update member function*/
  void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si );

  /* Derivatives member function */
  void bsl_hovering_derivatives();
};

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S4>/Product' : Unused code path elimination
 * Block '<S4>/Product1' : Unused code path elimination
 * Block '<S4>/Product2' : Unused code path elimination
 * Block '<S4>/Sum1' : Unused code path elimination
 * Block '<S4>/Sum4' : Unused code path elimination
 * Block '<S4>/Transpose' : Unused code path elimination
 * Block '<S5>/Scope' : Unused code path elimination
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
 * '<Root>' : 'bsl_hovering'
 * '<S1>'   : 'bsl_hovering/Two-Stage KF1'
 * '<S2>'   : 'bsl_hovering/Two-Stage KF1/Bias-Free State Estimator'
 * '<S3>'   : 'bsl_hovering/Two-Stage KF1/Coupling'
 * '<S4>'   : 'bsl_hovering/Two-Stage KF1/Error Compensator'
 * '<S5>'   : 'bsl_hovering/Two-Stage KF1/Optimal bias estimator'
 * '<S6>'   : 'bsl_hovering/Two-Stage KF1/Residual Generator'
 */
#endif                                 /* RTW_HEADER_bsl_hovering_h_ */
