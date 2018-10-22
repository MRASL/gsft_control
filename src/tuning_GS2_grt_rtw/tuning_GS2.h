/*
 * tuning_GS2.h
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "tuning_GS2".
 *
 * Model version              : 1.2170
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C++ source code generated on : Sun Oct 21 17:27:35 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Passed (1), Warnings (3), Error (0)
 */

#ifndef RTW_HEADER_tuning_GS2_h_
#define RTW_HEADER_tuning_GS2_h_
#include <cmath>
#include <string.h>
#ifndef tuning_GS2_COMMON_INCLUDES_
# define tuning_GS2_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* tuning_GS2_COMMON_INCLUDES_ */

#include "tuning_GS2_types.h"

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
  real_T LOE_FDD[6];                   /* '<Root>/Vector Concatenate' */
  real_T Sum1;                         /* '<S23>/Sum1' */
  real_T Sum1_e;                       /* '<S24>/Sum1' */
  real_T T_outer[3];                   /* '<S5>/T_outer' */
  real_T Fcn1;                         /* '<S5>/Fcn1' */
  real_T Fcn;                          /* '<S5>/Fcn' */
  real_T u[6];                         /* '<Root>/                   ' */
  real_T Sum3;                         /* '<S21>/Sum3' */
  real_T Sum3_f;                       /* '<S23>/Sum3' */
  real_T Sum3_f3;                      /* '<S24>/Sum3' */
  real_T Sum3_j;                       /* '<S25>/Sum3' */
  real_T Product2[6];                  /* '<S84>/Product2' */
  real_T Product3[6];                  /* '<S83>/Product3' */
} B_tuning_GS2_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T MemoryX_DSTATE[6];            /* '<S7>/MemoryX' */
  real_T Memory_PreviousInput[6];      /* '<S3>/Memory' */
  uint8_T icLoad;                      /* '<S7>/MemoryX' */
  boolean_T MeasurementUpdate_MODE;    /* '<S58>/MeasurementUpdate' */
  boolean_T EnabledSubsystem_MODE;     /* '<S63>/Enabled Subsystem' */
} DW_tuning_GS2_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T Integrator1_CSTATE;           /* '<S25>/Integrator1' */
  real_T Integrator1_CSTATE_e;         /* '<S23>/Integrator1' */
  real_T Integrator1_CSTATE_p;         /* '<S24>/Integrator1' */
  real_T Integrator1_CSTATE_j;         /* '<S21>/Integrator1' */
} X_tuning_GS2_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T Integrator1_CSTATE;           /* '<S25>/Integrator1' */
  real_T Integrator1_CSTATE_e;         /* '<S23>/Integrator1' */
  real_T Integrator1_CSTATE_p;         /* '<S24>/Integrator1' */
  real_T Integrator1_CSTATE_j;         /* '<S21>/Integrator1' */
} XDot_tuning_GS2_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator1_CSTATE;        /* '<S25>/Integrator1' */
  boolean_T Integrator1_CSTATE_e;      /* '<S23>/Integrator1' */
  boolean_T Integrator1_CSTATE_p;      /* '<S24>/Integrator1' */
  boolean_T Integrator1_CSTATE_j;      /* '<S21>/Integrator1' */
} XDis_tuning_GS2_T;

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
  /* Expression: M_bias'
   * Referenced by: '<S3>/Constant'
   */
  real_T Constant_Value[3];

  /* Expression: Ib
   * Referenced by: '<S3>/Constant1'
   */
  real_T Constant1_Value[9];

  /* Expression: pInitialization.M
   * Referenced by: '<S40>/KalmanGainM'
   */
  real_T KalmanGainM_Value[18];

  /* Expression: pInitialization.C
   * Referenced by: '<S7>/C'
   */
  real_T C_Value[18];

  /* Expression: Trans
   * Referenced by: '<S5>/Control Allocation'
   */
  real_T ControlAllocation_Gain[24];

  /* Expression: B_ENU_inv
   * Referenced by: '<Root>/Control Allocation'
   */
  real_T ControlAllocation_Gain_c[24];

  /* Expression: pInitialization.A
   * Referenced by: '<S7>/A'
   */
  real_T A_Value[36];

  /* Expression: pInitialization.L
   * Referenced by: '<S40>/KalmanGainL'
   */
  real_T KalmanGainL_Value[18];
} ConstP_tuning_GS2_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T X[12];                        /* '<Root>/X' */
  real_T Y0[4];                        /* '<Root>/Y0' */
  real_T mode;                         /* '<Root>/mode' */
  real_T ref[4];                       /* '<Root>/ref' */
  real_T LOE_t[6];                     /* '<Root>/LOE_t' */
  real_T LOE_a[6];                     /* '<Root>/LOE_a' */
  real_T gain[18];                     /* '<Root>/gain' */
  real_T LOE_calcul[6];                /* '<Root>/LOE_calcul' */
  real_T LOE_mode;                     /* '<Root>/LOE_mode' */
} ExtU_tuning_GS2_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T motor_command[6];             /* '<Root>/motor_command' */
  real_T ref_out[4];                   /* '<Root>/ref_out' */
  real_T LOE_true[6];                  /* '<Root>/LOE_true' */
  real_T LOE13_estimated[3];           /* '<Root>/LOE13_estimated' */
  real_T thrust_pre[6];                /* '<Root>/thrust_pre' */
  real_T thrust_after[6];              /* '<Root>/thrust_after' */
  real_T acc_Kalman[3];                /* '<Root>/acc_Kalman' */
  real_T M_Kalman[3];                  /* '<Root>/M_Kalman' */
  real_T vel_Kalman[3];                /* '<Root>/vel_Kalman' */
  real_T gain_GS[12];                  /* '<Root>/gain_GS' */
  real_T virtual_control[4];           /* '<Root>/virtual_control' */
} ExtY_tuning_GS2_T;

/* Real-time Model Data Structure */
struct tag_RTM_tuning_GS2_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_tuning_GS2_T *contStates;
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
extern const ConstP_tuning_GS2_T tuning_GS2_ConstP;

/* Class declaration for model tuning_GS2 */
class tuning_GS2ModelClass {
  /* public data and function members */
 public:
  /* External inputs */
  ExtU_tuning_GS2_T tuning_GS2_U;

  /* External outputs */
  ExtY_tuning_GS2_T tuning_GS2_Y;

  /* model initialize function */
  void initialize();

  /* model step function */
  void step();

  /* model terminate function */
  void terminate();

  /* Constructor */
  tuning_GS2ModelClass();

  /* Destructor */
  ~tuning_GS2ModelClass();

  /* Real-Time Model get method */
  RT_MODEL_tuning_GS2_T * getRTM();

  /* private data and function members */
 private:
  /* Block signals */
  B_tuning_GS2_T tuning_GS2_B;

  /* Block states */
  DW_tuning_GS2_T tuning_GS2_DW;
  X_tuning_GS2_T tuning_GS2_X;         /* Block continuous states */

  /* Real-Time Model */
  RT_MODEL_tuning_GS2_T tuning_GS2_M;

  /* Continuous states update member function*/
  void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si );

  /* Derivatives member function */
  void tuning_GS2_derivatives();
};

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S40>/ConstantP' : Unused code path elimination
 * Block '<S40>/CovarianceZ' : Unused code path elimination
 * Block '<S79>/Data Type Duplicate' : Unused code path elimination
 * Block '<S80>/Data Type Duplicate' : Unused code path elimination
 * Block '<S81>/Conversion' : Unused code path elimination
 * Block '<S81>/Data Type Duplicate' : Unused code path elimination
 * Block '<S82>/Conversion' : Unused code path elimination
 * Block '<S82>/Data Type Duplicate' : Unused code path elimination
 * Block '<S41>/Add1' : Unused code path elimination
 * Block '<S41>/Product' : Unused code path elimination
 * Block '<S41>/Product1' : Unused code path elimination
 * Block '<S42>/Data Type Duplicate' : Unused code path elimination
 * Block '<S43>/Data Type Duplicate' : Unused code path elimination
 * Block '<S44>/Data Type Duplicate' : Unused code path elimination
 * Block '<S45>/Data Type Duplicate' : Unused code path elimination
 * Block '<S46>/Conversion' : Unused code path elimination
 * Block '<S46>/Data Type Duplicate' : Unused code path elimination
 * Block '<S47>/Conversion' : Unused code path elimination
 * Block '<S47>/Data Type Duplicate' : Unused code path elimination
 * Block '<S48>/Conversion' : Unused code path elimination
 * Block '<S48>/Data Type Duplicate' : Unused code path elimination
 * Block '<S49>/Conversion' : Unused code path elimination
 * Block '<S49>/Data Type Duplicate' : Unused code path elimination
 * Block '<S50>/Conversion' : Unused code path elimination
 * Block '<S50>/Data Type Duplicate' : Unused code path elimination
 * Block '<S51>/Conversion' : Unused code path elimination
 * Block '<S51>/Data Type Duplicate' : Unused code path elimination
 * Block '<S52>/Conversion' : Unused code path elimination
 * Block '<S52>/Data Type Duplicate' : Unused code path elimination
 * Block '<S53>/Conversion' : Unused code path elimination
 * Block '<S53>/Data Type Duplicate' : Unused code path elimination
 * Block '<S54>/Data Type Duplicate' : Unused code path elimination
 * Block '<S55>/Data Type Duplicate' : Unused code path elimination
 * Block '<S56>/Data Type Duplicate' : Unused code path elimination
 * Block '<S7>/G' : Unused code path elimination
 * Block '<S7>/H' : Unused code path elimination
 * Block '<S7>/ManualSwitchPZ' : Unused code path elimination
 * Block '<S7>/N' : Unused code path elimination
 * Block '<S7>/P0' : Unused code path elimination
 * Block '<S7>/Q' : Unused code path elimination
 * Block '<S7>/R' : Unused code path elimination
 * Block '<S59>/Constant' : Unused code path elimination
 * Block '<S7>/Reset' : Unused code path elimination
 * Block '<S7>/Reshapeyhat' : Unused code path elimination
 * Block '<S78>/CheckSignalProperties' : Unused code path elimination
 * Block '<Root>/                          ' : Eliminated since input and output rates are identical
 * Block '<Root>/                             ' : Eliminated since input and output rates are identical
 * Block '<Root>/                                     ' : Eliminated since input and output rates are identical
 * Block '<S79>/Conversion' : Eliminate redundant data type conversion
 * Block '<S80>/Conversion' : Eliminate redundant data type conversion
 * Block '<S42>/Conversion' : Eliminate redundant data type conversion
 * Block '<S43>/Conversion' : Eliminate redundant data type conversion
 * Block '<S44>/Conversion' : Eliminate redundant data type conversion
 * Block '<S45>/Conversion' : Eliminate redundant data type conversion
 * Block '<S7>/DataTypeConversionEnable' : Eliminate redundant data type conversion
 * Block '<S54>/Conversion' : Eliminate redundant data type conversion
 * Block '<S55>/Conversion' : Eliminate redundant data type conversion
 * Block '<S56>/Conversion' : Eliminate redundant data type conversion
 * Block '<S58>/Reshape' : Reshape block reduction
 * Block '<S7>/ReshapeX0' : Reshape block reduction
 * Block '<S7>/Reshapeu' : Reshape block reduction
 * Block '<S7>/Reshapexhat' : Reshape block reduction
 * Block '<S7>/Reshapey' : Reshape block reduction
 * Block '<Root>/Rate Transition' : Eliminated since input and output rates are identical
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
 * '<Root>' : 'tuning_GS2'
 * '<S1>'   : 'tuning_GS2/Actuator_Fault'
 * '<S2>'   : 'tuning_GS2/FDD'
 * '<S3>'   : 'tuning_GS2/FDD_Kalman'
 * '<S4>'   : 'tuning_GS2/GS1'
 * '<S5>'   : 'tuning_GS2/GS2_Controller'
 * '<S6>'   : 'tuning_GS2/GS_controller1'
 * '<S7>'   : 'tuning_GS2/Kalman Filter'
 * '<S8>'   : 'tuning_GS2/Test_config_and_data'
 * '<S9>'   : 'tuning_GS2/Thrust2command'
 * '<S10>'  : 'tuning_GS2/FDD_Kalman/Cross Product'
 * '<S11>'  : 'tuning_GS2/FDD_Kalman/MATLAB Function1'
 * '<S12>'  : 'tuning_GS2/FDD_Kalman/Cross Product/Subsystem'
 * '<S13>'  : 'tuning_GS2/FDD_Kalman/Cross Product/Subsystem2'
 * '<S14>'  : 'tuning_GS2/GS1/pitch_controller_SF'
 * '<S15>'  : 'tuning_GS2/GS1/roll_controller_SF'
 * '<S16>'  : 'tuning_GS2/GS1/x_GS2_controller'
 * '<S17>'  : 'tuning_GS2/GS1/y_GS2_controller'
 * '<S18>'  : 'tuning_GS2/GS1/x_GS2_controller/MATLAB Function'
 * '<S19>'  : 'tuning_GS2/GS1/y_GS2_controller/MATLAB Function'
 * '<S20>'  : 'tuning_GS2/GS2_Controller/pitch_GS2_controller'
 * '<S21>'  : 'tuning_GS2/GS2_Controller/psi_GS2_controller'
 * '<S22>'  : 'tuning_GS2/GS2_Controller/roll_GS2_controller'
 * '<S23>'  : 'tuning_GS2/GS2_Controller/x_GS2_controller'
 * '<S24>'  : 'tuning_GS2/GS2_Controller/y_GS2_controller'
 * '<S25>'  : 'tuning_GS2/GS2_Controller/z_GS2_controller'
 * '<S26>'  : 'tuning_GS2/GS2_Controller/pitch_GS2_controller/MATLAB Function'
 * '<S27>'  : 'tuning_GS2/GS2_Controller/psi_GS2_controller/MATLAB Function'
 * '<S28>'  : 'tuning_GS2/GS2_Controller/roll_GS2_controller/MATLAB Function'
 * '<S29>'  : 'tuning_GS2/GS2_Controller/x_GS2_controller/MATLAB Function'
 * '<S30>'  : 'tuning_GS2/GS2_Controller/y_GS2_controller/MATLAB Function'
 * '<S31>'  : 'tuning_GS2/GS2_Controller/z_GS2_controller/MATLAB Function'
 * '<S32>'  : 'tuning_GS2/GS_controller1/psi_GS_controller'
 * '<S33>'  : 'tuning_GS2/GS_controller1/x_GS_controller'
 * '<S34>'  : 'tuning_GS2/GS_controller1/y_GS_controller'
 * '<S35>'  : 'tuning_GS2/GS_controller1/z_GS_controller'
 * '<S36>'  : 'tuning_GS2/GS_controller1/psi_GS_controller/MATLAB Function'
 * '<S37>'  : 'tuning_GS2/GS_controller1/x_GS_controller/MATLAB Function'
 * '<S38>'  : 'tuning_GS2/GS_controller1/y_GS_controller/MATLAB Function'
 * '<S39>'  : 'tuning_GS2/GS_controller1/z_GS_controller/MATLAB Function'
 * '<S40>'  : 'tuning_GS2/Kalman Filter/CalculatePL'
 * '<S41>'  : 'tuning_GS2/Kalman Filter/CalculateYhat'
 * '<S42>'  : 'tuning_GS2/Kalman Filter/DataTypeConversionA'
 * '<S43>'  : 'tuning_GS2/Kalman Filter/DataTypeConversionB'
 * '<S44>'  : 'tuning_GS2/Kalman Filter/DataTypeConversionC'
 * '<S45>'  : 'tuning_GS2/Kalman Filter/DataTypeConversionD'
 * '<S46>'  : 'tuning_GS2/Kalman Filter/DataTypeConversionG'
 * '<S47>'  : 'tuning_GS2/Kalman Filter/DataTypeConversionH'
 * '<S48>'  : 'tuning_GS2/Kalman Filter/DataTypeConversionN'
 * '<S49>'  : 'tuning_GS2/Kalman Filter/DataTypeConversionP'
 * '<S50>'  : 'tuning_GS2/Kalman Filter/DataTypeConversionP0'
 * '<S51>'  : 'tuning_GS2/Kalman Filter/DataTypeConversionQ'
 * '<S52>'  : 'tuning_GS2/Kalman Filter/DataTypeConversionR'
 * '<S53>'  : 'tuning_GS2/Kalman Filter/DataTypeConversionReset'
 * '<S54>'  : 'tuning_GS2/Kalman Filter/DataTypeConversionX'
 * '<S55>'  : 'tuning_GS2/Kalman Filter/DataTypeConversionX0'
 * '<S56>'  : 'tuning_GS2/Kalman Filter/DataTypeConversionu'
 * '<S57>'  : 'tuning_GS2/Kalman Filter/MemoryP'
 * '<S58>'  : 'tuning_GS2/Kalman Filter/Observer'
 * '<S59>'  : 'tuning_GS2/Kalman Filter/ReducedQRN'
 * '<S60>'  : 'tuning_GS2/Kalman Filter/ScalarExpansionP0'
 * '<S61>'  : 'tuning_GS2/Kalman Filter/ScalarExpansionQ'
 * '<S62>'  : 'tuning_GS2/Kalman Filter/ScalarExpansionR'
 * '<S63>'  : 'tuning_GS2/Kalman Filter/UseCurrentEstimator'
 * '<S64>'  : 'tuning_GS2/Kalman Filter/checkA'
 * '<S65>'  : 'tuning_GS2/Kalman Filter/checkB'
 * '<S66>'  : 'tuning_GS2/Kalman Filter/checkC'
 * '<S67>'  : 'tuning_GS2/Kalman Filter/checkD'
 * '<S68>'  : 'tuning_GS2/Kalman Filter/checkEnable'
 * '<S69>'  : 'tuning_GS2/Kalman Filter/checkG'
 * '<S70>'  : 'tuning_GS2/Kalman Filter/checkH'
 * '<S71>'  : 'tuning_GS2/Kalman Filter/checkN'
 * '<S72>'  : 'tuning_GS2/Kalman Filter/checkP0'
 * '<S73>'  : 'tuning_GS2/Kalman Filter/checkQ'
 * '<S74>'  : 'tuning_GS2/Kalman Filter/checkR'
 * '<S75>'  : 'tuning_GS2/Kalman Filter/checkReset'
 * '<S76>'  : 'tuning_GS2/Kalman Filter/checkX0'
 * '<S77>'  : 'tuning_GS2/Kalman Filter/checku'
 * '<S78>'  : 'tuning_GS2/Kalman Filter/checky'
 * '<S79>'  : 'tuning_GS2/Kalman Filter/CalculatePL/DataTypeConversionL'
 * '<S80>'  : 'tuning_GS2/Kalman Filter/CalculatePL/DataTypeConversionM'
 * '<S81>'  : 'tuning_GS2/Kalman Filter/CalculatePL/DataTypeConversionP'
 * '<S82>'  : 'tuning_GS2/Kalman Filter/CalculatePL/DataTypeConversionZ'
 * '<S83>'  : 'tuning_GS2/Kalman Filter/Observer/MeasurementUpdate'
 * '<S84>'  : 'tuning_GS2/Kalman Filter/UseCurrentEstimator/Enabled Subsystem'
 * '<S85>'  : 'tuning_GS2/Test_config_and_data/FFW'
 * '<S86>'  : 'tuning_GS2/Test_config_and_data/LOE_'
 * '<S87>'  : 'tuning_GS2/Test_config_and_data/MATLAB Function'
 */
#endif                                 /* RTW_HEADER_tuning_GS2_h_ */
