/*
 * bsl_hovering.h
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "bsl_hovering".
 *
 * Model version              : 1.586
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Wed Jan 24 14:14:38 2018
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
  real_T RateTransition2[12];          /* '<S3>/Rate Transition2' */
  real_T u[2];                         /* '<S3>/                   ' */
  real_T Fcn1;                         /* '<S3>/Fcn1' */
  real_T Fcn;                          /* '<S3>/Fcn' */
  real_T ZeroOrderHold[2];             /* '<S3>/Zero-Order Hold' */
  real_T roll;                         /* '<S1>/roll' */
  real_T pitch;                        /* '<S1>/pitch' */
  real_T Gain[6];                      /* '<Root>/Gain' */
  real_T gamma_hat_k1k[6];             /* '<S8>/       ' */
  real_T K_gamma_k1[36];               /* '<S8>/Divide' */
  real_T Product[6];                   /* '<S8>/Product' */
  real_T X_tildle_k1k[12];             /* '<S5>/Sum1' */
  real_T C[6];                         /* '<S9>/C' */
  real_T Sum1[6];                      /* '<S8>/Sum1' */
  real_T psi_e;                        /* '<S1>/psi_e' */
  real_T ze;                           /* '<S1>/ze' */
  real_T RateTransition;               /* '<S3>/Rate Transition' */
  real_T RateTransition1;              /* '<S3>/Rate Transition1' */
  real_T xe;                           /* '<S3>/xe' */
  real_T ye;                           /* '<S3>/ye' */
  real_T C_i[6];                       /* '<S5>/C' */
  real_T K_tildle_x_k1[72];            /* '<S5>/Divide' */
  real_T Sum3[12];                     /* '<S5>/Sum3' */
  real_T ref[4];                       /* '<Root>/MATLAB Function' */
} B_bsl_hovering_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T _DSTATE[6];                   /* '<S8>/       ' */
  real_T UnitDelay1_DSTATE[36];        /* '<S8>/Unit Delay1' */
  real_T UnitDelay_DSTATE[72];         /* '<S6>/Unit Delay' */
  real_T UnitDelay1_DSTATE_l[144];     /* '<S5>/Unit Delay1' */
  real_T UnitDelay_DSTATE_l[12];       /* '<S5>/Unit Delay' */
  real_T Memory_PreviousInput[6];      /* '<Root>/Memory' */
  real_T Divide_DWORK4[36];            /* '<S6>/Divide' */
  real_T Divide_DWORK4_e[36];          /* '<S8>/Divide' */
  real_T Divide_DWORK4_n[36];          /* '<S5>/Divide' */
} DW_bsl_hovering_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T Integrator_CSTATE[2];         /* '<S1>/Integrator' */
  real_T Integrator_CSTATE_b[2];       /* '<S3>/Integrator' */
} X_bsl_hovering_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T Integrator_CSTATE[2];         /* '<S1>/Integrator' */
  real_T Integrator_CSTATE_b[2];       /* '<S3>/Integrator' */
} XDot_bsl_hovering_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE[2];      /* '<S1>/Integrator' */
  boolean_T Integrator_CSTATE_b[2];    /* '<S3>/Integrator' */
} XDis_bsl_hovering_T;

/* Invariant block signals (auto storage) */
typedef const struct tag_ConstB_bsl_hovering_T {
  real_T Transpose[72];                /* '<S9>/Transpose' */
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
   * Referenced by: '<S1>/              '
   */
  real_T _Value[4];

  /* Expression: Kx_outer
   * Referenced by: '<S3>/                   '
   */
  real_T _Gain_a[8];

  /* Expression: Kx_inner
   * Referenced by: '<S1>/                   '
   */
  real_T _Gain_p[32];

  /* Expression: B_ENU_inv
   * Referenced by: '<Root>/Gain'
   */
  real_T Gain_Gain[24];

  /* Expression: Qgamma
   * Referenced by: '<S8>/Q_gamma'
   */
  real_T Q_gamma_Value[36];

  /* Expression: Pgamma0
   * Referenced by: '<S8>/Unit Delay1'
   */
  real_T UnitDelay1_InitialCondition[36];

  /* Pooled Parameter (Expression: C)
   * Referenced by:
   *   '<S5>/     '
   *   '<S5>/C'
   *   '<S5>/C1'
   *   '<S6>/                      '
   *   '<S9>/     '
   *   '<S9>/C'
   */
  real_T pooled5[72];

  /* Pooled Parameter (Expression: A)
   * Referenced by:
   *   '<S5>/A'
   *   '<S5>/A1'
   *   '<S6>/     '
   */
  real_T pooled6[144];

  /* Pooled Parameter (Expression: B)
   * Referenced by:
   *   '<S5>/B'
   *   '<S6>/          '
   */
  real_T pooled7[72];

  /* Expression: Qx
   * Referenced by: '<S5>/Q_x'
   */
  real_T Q_x_Value[144];

  /* Expression: Px_tilde0
   * Referenced by: '<S5>/Unit Delay1'
   */
  real_T UnitDelay1_InitialCondition_n[144];

  /* Expression: A'
   * Referenced by: '<S5>/A''
   */
  real_T A_Gain[144];

  /* Pooled Parameter (Expression: R)
   * Referenced by:
   *   '<S5>/R'
   *   '<S9>/R'
   */
  real_T pooled8[36];

  /* Expression: [0 0 0 0 0 bias 0 0 0 0 0 0]
   * Referenced by: '<S5>/Constant'
   */
  real_T Constant_Value[12];

  /* Expression: C'
   * Referenced by: '<S5>/C''
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
  real_T ref[4];                       /* '<Root>/ref' */
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
 * Block '<S7>/Product' : Unused code path elimination
 * Block '<S7>/Product1' : Unused code path elimination
 * Block '<S7>/Product2' : Unused code path elimination
 * Block '<S7>/Sum1' : Unused code path elimination
 * Block '<S7>/Sum4' : Unused code path elimination
 * Block '<S7>/Transpose' : Unused code path elimination
 * Block '<S8>/Scope' : Unused code path elimination
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
 * '<S1>'   : 'bsl_hovering/Inner'
 * '<S2>'   : 'bsl_hovering/MATLAB Function'
 * '<S3>'   : 'bsl_hovering/Outer'
 * '<S4>'   : 'bsl_hovering/Two-Stage KF1'
 * '<S5>'   : 'bsl_hovering/Two-Stage KF1/Bias-Free State Estimator'
 * '<S6>'   : 'bsl_hovering/Two-Stage KF1/Coupling'
 * '<S7>'   : 'bsl_hovering/Two-Stage KF1/Error Compensator'
 * '<S8>'   : 'bsl_hovering/Two-Stage KF1/Optimal bias estimator'
 * '<S9>'   : 'bsl_hovering/Two-Stage KF1/Residual Generator'
 */
#endif                                 /* RTW_HEADER_bsl_hovering_h_ */
