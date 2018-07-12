/*
 * tunning_nominal.h
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "tunning_nominal".
 *
 * Model version              : 1.1417
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Thu Jul 12 16:22:42 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_tunning_nominal_h_
#define RTW_HEADER_tunning_nominal_h_
#include <cmath>
#include <string.h>
#ifndef tunning_nominal_COMMON_INCLUDES_
# define tunning_nominal_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* tunning_nominal_COMMON_INCLUDES_ */

#include "tunning_nominal_types.h"

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

/* Block signals for system '<S2>/MATLAB Function1' */
typedef struct {
  real_T gamma[3];                     /* '<S2>/MATLAB Function1' */
} B_MATLABFunction1_tunning_nom_T;

/* Block signals (auto storage) */
typedef struct {
  real_T u[6];                         /* '<Root>/                  ' */
  real_T Sum1;                         /* '<S7>/Sum1' */
  real_T Sum4;                         /* '<S7>/Sum4' */
  real_T Sum3;                         /* '<S10>/Sum3' */
  real_T Sum3_h;                       /* '<S11>/Sum3' */
  real_T Product2[6];                  /* '<S64>/Product2' */
  real_T Product3[6];                  /* '<S63>/Product3' */
  B_MATLABFunction1_tunning_nom_T sf_MATLABFunction1_b;/* '<S3>/MATLAB Function1' */
  B_MATLABFunction1_tunning_nom_T sf_MATLABFunction1;/* '<S2>/MATLAB Function1' */
} B_tunning_nominal_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T MemoryX_DSTATE[6];            /* '<S4>/MemoryX' */
  real_T Memory_PreviousInput[6];      /* '<S2>/Memory' */
  real_T Memory_PreviousInput_k[6];    /* '<S3>/Memory' */
  uint8_T icLoad;                      /* '<S4>/MemoryX' */
  boolean_T MeasurementUpdate_MODE;    /* '<S38>/MeasurementUpdate' */
  boolean_T EnabledSubsystem_MODE;     /* '<S43>/Enabled Subsystem' */
} DW_tunning_nominal_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T Integrator1_CSTATE;           /* '<S11>/Integrator1' */
  real_T Integrator1_CSTATE_d;         /* '<S7>/Integrator1' */
  real_T Integrator_CSTATE;            /* '<S7>/Integrator' */
  real_T Integrator1_CSTATE_j;         /* '<S10>/Integrator1' */
} X_tunning_nominal_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T Integrator1_CSTATE;           /* '<S11>/Integrator1' */
  real_T Integrator1_CSTATE_d;         /* '<S7>/Integrator1' */
  real_T Integrator_CSTATE;            /* '<S7>/Integrator' */
  real_T Integrator1_CSTATE_j;         /* '<S10>/Integrator1' */
} XDot_tunning_nominal_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator1_CSTATE;        /* '<S11>/Integrator1' */
  boolean_T Integrator1_CSTATE_d;      /* '<S7>/Integrator1' */
  boolean_T Integrator_CSTATE;         /* '<S7>/Integrator' */
  boolean_T Integrator1_CSTATE_j;      /* '<S10>/Integrator1' */
} XDis_tunning_nominal_T;

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

  /* Pooled Parameter (Expression: Ib)
   * Referenced by:
   *   '<S2>/Constant1'
   *   '<S3>/Constant1'
   */
  real_T pooled6[9];

  /* Expression: M_bias'
   * Referenced by: '<S3>/Constant'
   */
  real_T Constant_Value_g[3];

  /* Expression: pInitialization.M
   * Referenced by: '<S20>/KalmanGainM'
   */
  real_T KalmanGainM_Value[18];

  /* Expression: pInitialization.C
   * Referenced by: '<S4>/C'
   */
  real_T C_Value[18];

  /* Expression: pInitialization.A
   * Referenced by: '<S4>/A'
   */
  real_T A_Value[36];

  /* Expression: pInitialization.L
   * Referenced by: '<S20>/KalmanGainL'
   */
  real_T KalmanGainL_Value[18];
} ConstP_tunning_nominal_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T X[15];                        /* '<Root>/X' */
  real_T Y0[4];                        /* '<Root>/Y0' */
  real_T mode;                         /* '<Root>/mode' */
  real_T ref[4];                       /* '<Root>/ref' */
  real_T LOE_t[6];                     /* '<Root>/LOE_t' */
  real_T LOE_a[6];                     /* '<Root>/LOE_a' */
  real_T gain[19];                     /* '<Root>/gain' */
} ExtU_tunning_nominal_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T motor_command[6];             /* '<Root>/motor_command' */
  real_T virtual_control[4];           /* '<Root>/virtual_control' */
  real_T ref_out[4];                   /* '<Root>/ref_out' */
  real_T LOE[6];                       /* '<Root>/LOE' */
  real_T LOE13_calcul[3];              /* '<Root>/LOE13_calcul' */
  real_T LOE13_Kalman[3];              /* '<Root>/LOE13_Kalman' */
  real_T acc_Kalman[3];                /* '<Root>/acc_Kalman' */
  real_T M_calcul[3];                  /* '<Root>/M_calcul' */
  real_T M_Kalman[3];                  /* '<Root>/M_Kalman' */
} ExtY_tunning_nominal_T;

/* Real-time Model Data Structure */
struct tag_RTM_tunning_nominal_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_tunning_nominal_T *contStates;
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
extern const ConstP_tunning_nominal_T tunning_nominal_ConstP;

/* Class declaration for model tunning_nominal */
class tunning_nominalModelClass {
  /* public data and function members */
 public:
  /* External inputs */
  ExtU_tunning_nominal_T tunning_nominal_U;

  /* External outputs */
  ExtY_tunning_nominal_T tunning_nominal_Y;

  /* model initialize function */
  void initialize();

  /* model step function */
  void step();

  /* model terminate function */
  void terminate();

  /* Constructor */
  tunning_nominalModelClass();

  /* Destructor */
  ~tunning_nominalModelClass();

  /* Real-Time Model get method */
  RT_MODEL_tunning_nominal_T * getRTM();

  /* private data and function members */
 private:
  /* Block signals */
  B_tunning_nominal_T tunning_nominal_B;

  /* Block states */
  DW_tunning_nominal_T tunning_nominal_DW;
  X_tunning_nominal_T tunning_nominal_X;/* Block continuous states */

  /* Real-Time Model */
  RT_MODEL_tunning_nominal_T tunning_nominal_M;

  /* Continuous states update member function*/
  void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si );

  /* Derivatives member function */
  void tunning_nominal_derivatives();
};

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S20>/ConstantP' : Unused code path elimination
 * Block '<S20>/CovarianceZ' : Unused code path elimination
 * Block '<S59>/Data Type Duplicate' : Unused code path elimination
 * Block '<S60>/Data Type Duplicate' : Unused code path elimination
 * Block '<S61>/Conversion' : Unused code path elimination
 * Block '<S61>/Data Type Duplicate' : Unused code path elimination
 * Block '<S62>/Conversion' : Unused code path elimination
 * Block '<S62>/Data Type Duplicate' : Unused code path elimination
 * Block '<S21>/Add1' : Unused code path elimination
 * Block '<S21>/Product' : Unused code path elimination
 * Block '<S21>/Product1' : Unused code path elimination
 * Block '<S22>/Data Type Duplicate' : Unused code path elimination
 * Block '<S23>/Data Type Duplicate' : Unused code path elimination
 * Block '<S24>/Data Type Duplicate' : Unused code path elimination
 * Block '<S25>/Data Type Duplicate' : Unused code path elimination
 * Block '<S26>/Conversion' : Unused code path elimination
 * Block '<S26>/Data Type Duplicate' : Unused code path elimination
 * Block '<S27>/Conversion' : Unused code path elimination
 * Block '<S27>/Data Type Duplicate' : Unused code path elimination
 * Block '<S28>/Conversion' : Unused code path elimination
 * Block '<S28>/Data Type Duplicate' : Unused code path elimination
 * Block '<S29>/Conversion' : Unused code path elimination
 * Block '<S29>/Data Type Duplicate' : Unused code path elimination
 * Block '<S30>/Conversion' : Unused code path elimination
 * Block '<S30>/Data Type Duplicate' : Unused code path elimination
 * Block '<S31>/Conversion' : Unused code path elimination
 * Block '<S31>/Data Type Duplicate' : Unused code path elimination
 * Block '<S32>/Conversion' : Unused code path elimination
 * Block '<S32>/Data Type Duplicate' : Unused code path elimination
 * Block '<S33>/Conversion' : Unused code path elimination
 * Block '<S33>/Data Type Duplicate' : Unused code path elimination
 * Block '<S34>/Data Type Duplicate' : Unused code path elimination
 * Block '<S35>/Data Type Duplicate' : Unused code path elimination
 * Block '<S36>/Data Type Duplicate' : Unused code path elimination
 * Block '<S4>/G' : Unused code path elimination
 * Block '<S4>/H' : Unused code path elimination
 * Block '<S4>/ManualSwitchPZ' : Unused code path elimination
 * Block '<S4>/N' : Unused code path elimination
 * Block '<S4>/P0' : Unused code path elimination
 * Block '<S4>/Q' : Unused code path elimination
 * Block '<S4>/R' : Unused code path elimination
 * Block '<S39>/Constant' : Unused code path elimination
 * Block '<S4>/Reset' : Unused code path elimination
 * Block '<S4>/Reshapeyhat' : Unused code path elimination
 * Block '<S58>/CheckSignalProperties' : Unused code path elimination
 * Block '<Root>/                          ' : Eliminated since input and output rates are identical
 * Block '<Root>/                             ' : Eliminated since input and output rates are identical
 * Block '<Root>/                                     ' : Eliminated since input and output rates are identical
 * Block '<S59>/Conversion' : Eliminate redundant data type conversion
 * Block '<S60>/Conversion' : Eliminate redundant data type conversion
 * Block '<S22>/Conversion' : Eliminate redundant data type conversion
 * Block '<S23>/Conversion' : Eliminate redundant data type conversion
 * Block '<S24>/Conversion' : Eliminate redundant data type conversion
 * Block '<S25>/Conversion' : Eliminate redundant data type conversion
 * Block '<S4>/DataTypeConversionEnable' : Eliminate redundant data type conversion
 * Block '<S34>/Conversion' : Eliminate redundant data type conversion
 * Block '<S35>/Conversion' : Eliminate redundant data type conversion
 * Block '<S36>/Conversion' : Eliminate redundant data type conversion
 * Block '<S38>/Reshape' : Reshape block reduction
 * Block '<S4>/ReshapeX0' : Reshape block reduction
 * Block '<S4>/Reshapeu' : Reshape block reduction
 * Block '<S4>/Reshapexhat' : Reshape block reduction
 * Block '<S4>/Reshapey' : Reshape block reduction
 * Block '<Root>/Rate Transition' : Eliminated since input and output rates are identical
 * Block '<S7>/Reshape' : Reshape block reduction
 * Block '<S7>/Reshape1' : Reshape block reduction
 * Block '<S8>/Reshape' : Reshape block reduction
 * Block '<S9>/Reshape' : Reshape block reduction
 * Block '<S10>/Reshape' : Reshape block reduction
 * Block '<S11>/Reshape' : Reshape block reduction
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
 * '<Root>' : 'tunning_nominal'
 * '<S1>'   : 'tunning_nominal/Actuator_Fault'
 * '<S2>'   : 'tunning_nominal/FDD  '
 * '<S3>'   : 'tunning_nominal/FDD_Kalman'
 * '<S4>'   : 'tunning_nominal/Kalman Filter'
 * '<S5>'   : 'tunning_nominal/Test_config_and_data'
 * '<S6>'   : 'tunning_nominal/Thrust2command'
 * '<S7>'   : 'tunning_nominal/XY State Feedback'
 * '<S8>'   : 'tunning_nominal/pitch_controller_SF'
 * '<S9>'   : 'tunning_nominal/roll_controller_SF'
 * '<S10>'  : 'tunning_nominal/yaw_controller'
 * '<S11>'  : 'tunning_nominal/z_controller'
 * '<S12>'  : 'tunning_nominal/FDD  /Cross Product'
 * '<S13>'  : 'tunning_nominal/FDD  /MATLAB Function1'
 * '<S14>'  : 'tunning_nominal/FDD  /Cross Product/Subsystem'
 * '<S15>'  : 'tunning_nominal/FDD  /Cross Product/Subsystem2'
 * '<S16>'  : 'tunning_nominal/FDD_Kalman/Cross Product'
 * '<S17>'  : 'tunning_nominal/FDD_Kalman/MATLAB Function1'
 * '<S18>'  : 'tunning_nominal/FDD_Kalman/Cross Product/Subsystem'
 * '<S19>'  : 'tunning_nominal/FDD_Kalman/Cross Product/Subsystem2'
 * '<S20>'  : 'tunning_nominal/Kalman Filter/CalculatePL'
 * '<S21>'  : 'tunning_nominal/Kalman Filter/CalculateYhat'
 * '<S22>'  : 'tunning_nominal/Kalman Filter/DataTypeConversionA'
 * '<S23>'  : 'tunning_nominal/Kalman Filter/DataTypeConversionB'
 * '<S24>'  : 'tunning_nominal/Kalman Filter/DataTypeConversionC'
 * '<S25>'  : 'tunning_nominal/Kalman Filter/DataTypeConversionD'
 * '<S26>'  : 'tunning_nominal/Kalman Filter/DataTypeConversionG'
 * '<S27>'  : 'tunning_nominal/Kalman Filter/DataTypeConversionH'
 * '<S28>'  : 'tunning_nominal/Kalman Filter/DataTypeConversionN'
 * '<S29>'  : 'tunning_nominal/Kalman Filter/DataTypeConversionP'
 * '<S30>'  : 'tunning_nominal/Kalman Filter/DataTypeConversionP0'
 * '<S31>'  : 'tunning_nominal/Kalman Filter/DataTypeConversionQ'
 * '<S32>'  : 'tunning_nominal/Kalman Filter/DataTypeConversionR'
 * '<S33>'  : 'tunning_nominal/Kalman Filter/DataTypeConversionReset'
 * '<S34>'  : 'tunning_nominal/Kalman Filter/DataTypeConversionX'
 * '<S35>'  : 'tunning_nominal/Kalman Filter/DataTypeConversionX0'
 * '<S36>'  : 'tunning_nominal/Kalman Filter/DataTypeConversionu'
 * '<S37>'  : 'tunning_nominal/Kalman Filter/MemoryP'
 * '<S38>'  : 'tunning_nominal/Kalman Filter/Observer'
 * '<S39>'  : 'tunning_nominal/Kalman Filter/ReducedQRN'
 * '<S40>'  : 'tunning_nominal/Kalman Filter/ScalarExpansionP0'
 * '<S41>'  : 'tunning_nominal/Kalman Filter/ScalarExpansionQ'
 * '<S42>'  : 'tunning_nominal/Kalman Filter/ScalarExpansionR'
 * '<S43>'  : 'tunning_nominal/Kalman Filter/UseCurrentEstimator'
 * '<S44>'  : 'tunning_nominal/Kalman Filter/checkA'
 * '<S45>'  : 'tunning_nominal/Kalman Filter/checkB'
 * '<S46>'  : 'tunning_nominal/Kalman Filter/checkC'
 * '<S47>'  : 'tunning_nominal/Kalman Filter/checkD'
 * '<S48>'  : 'tunning_nominal/Kalman Filter/checkEnable'
 * '<S49>'  : 'tunning_nominal/Kalman Filter/checkG'
 * '<S50>'  : 'tunning_nominal/Kalman Filter/checkH'
 * '<S51>'  : 'tunning_nominal/Kalman Filter/checkN'
 * '<S52>'  : 'tunning_nominal/Kalman Filter/checkP0'
 * '<S53>'  : 'tunning_nominal/Kalman Filter/checkQ'
 * '<S54>'  : 'tunning_nominal/Kalman Filter/checkR'
 * '<S55>'  : 'tunning_nominal/Kalman Filter/checkReset'
 * '<S56>'  : 'tunning_nominal/Kalman Filter/checkX0'
 * '<S57>'  : 'tunning_nominal/Kalman Filter/checku'
 * '<S58>'  : 'tunning_nominal/Kalman Filter/checky'
 * '<S59>'  : 'tunning_nominal/Kalman Filter/CalculatePL/DataTypeConversionL'
 * '<S60>'  : 'tunning_nominal/Kalman Filter/CalculatePL/DataTypeConversionM'
 * '<S61>'  : 'tunning_nominal/Kalman Filter/CalculatePL/DataTypeConversionP'
 * '<S62>'  : 'tunning_nominal/Kalman Filter/CalculatePL/DataTypeConversionZ'
 * '<S63>'  : 'tunning_nominal/Kalman Filter/Observer/MeasurementUpdate'
 * '<S64>'  : 'tunning_nominal/Kalman Filter/UseCurrentEstimator/Enabled Subsystem'
 * '<S65>'  : 'tunning_nominal/Test_config_and_data/FFW'
 * '<S66>'  : 'tunning_nominal/Test_config_and_data/LOE_'
 * '<S67>'  : 'tunning_nominal/Test_config_and_data/MATLAB Function'
 */
#endif                                 /* RTW_HEADER_tunning_nominal_h_ */
