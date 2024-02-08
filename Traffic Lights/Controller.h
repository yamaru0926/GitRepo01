// File : .\Controller.h
//
//
//
#ifndef __Controller
#define __Controller
//
#include "RtsSim.h"
#include "Lights.h"

class Controller
{


public:
  // \ART_SMG :: Created for state : Controller
  enum RtsController_States
  {
  	RtsController_States_Off,
  	RtsController_States_Running,
  	RtsController_States_NotIn_Controller
  	
  };
  // \ART_SMG :: Created for state : Running
  enum RtsRunning_States
  {
  	RtsRunning_States_Crossing,
  	RtsRunning_States_Ready,
  	RtsRunning_States_Caution,
  	RtsRunning_States_Go,
  	RtsRunning_States_Stop,
  	RtsRunning_States_NotIn_Running
  	
  };
  // \ART_SMG :: Created for state : Crossing
  enum RtsCrossing_States
  {
  	RtsCrossing_States_FlashOn,
  	RtsCrossing_States_FlashOff,
  	RtsCrossing_States_NotIn_Crossing
  	
  };
  
  // Public|Package attributes
  
  static SimFuncs* m_SimFuncs;
  
  
  // Public|Package operations
  
  // \PTC_SMG :: Created to initiate the state machine
  void StartStateMachine();
  
  
  // \PTC_SMG :: Created for state machine simulation
  Controller();
  
  
  // \ART_SMG :: Destructor
  ~Controller();
  
  
  // \ART_SMG :: Created for state : Off
  void RtsActivate();
  
  
  // \ART_SMG :: Created for state : Running
  void RtsButtonPress();
  
  
  // \ART_SMG :: Created for state : Running
  void RtsDeactivate(
  	const short i,
  	const char j
  );


private:
  
  // Private attributes
  
  short ped_wait;
  
  short flashes;
  
  static SimFuncs classSpecificSimFuncs;
  
  // \ART_SMG :: Created for state : Controller
  RtsController_States RtsCurrent_Controller;
  
  // \ART_SMG :: Created for state : Running
  RtsRunning_States RtsCurrent_Running;
  
  // \ART_SMG :: Created for state : Ready
  RtsTimer RtsAttReady_Timer1;
  
  // \ART_SMG :: Created for state : Caution
  RtsTimer RtsAttCaution_Timer1;
  
  // \ART_SMG :: Created for state : Go
  RtsTimer RtsAttGo_Timer1;
  
  // \ART_SMG :: Created for state : Stop
  RtsTimer RtsAttStop_Timer1;
  
  // \ART_SMG :: Created for state : Crossing
  RtsCrossing_States RtsCurrent_Crossing;
  
  // \ART_SMG :: Created for state : FlashOn
  RtsTimer RtsAttFlashOn_Timer1;
  
  // \ART_SMG :: Created for state : FlashOff
  RtsTimer RtsAttFlashOff_Timer1;
  
  // \ART_SMG :: Always Created
  RtsSemaphore RtsBusy;
  
  
  // Private roles
  
  Lights rLights;
  
  
  // Private operations
  
  static int InjectEvent(
  	const char* strEvent,
  	const int numParams,
  	StringArray params,
  	void* pInstance
  );
  
  
  static int GetAttributeValue(
  	const char* strName,
  	char* strValue,
  	const int bufLen,
  	void* pInstance
  );
  
  
  static int SetAttributeValue(
  	const char* strName,
  	const char* strValue,
  	void* pInstance
  );
  
  
  static int TimerSet(
  	const bool bPaused,
  	const RtsTimer* pTimerID,
  	const unsigned long ulTimeToFire,
  	void* pTimerDetails,
  	const long lMultiplier
  );
  
  
  // \ART_SMG :: Created for state : FlashOn
  static void CALLBACK RtsFlashOn_Timer1_CallBack(
  	Controller* pInstance,
  	BOOLEAN TimerOrWaitFired
  );
  
  
  // \ART_SMG :: Created for state : FlashOff
  static void CALLBACK RtsFlashOff_Timer1_CallBack(
  	Controller* pInstance,
  	BOOLEAN TimerOrWaitFired
  );
  
  
  // \ART_SMG :: Created for state : Ready
  static void CALLBACK RtsReady_Timer1_CallBack(
  	Controller* pInstance,
  	BOOLEAN TimerOrWaitFired
  );
  
  
  // \ART_SMG :: Created for state : Caution
  static void CALLBACK RtsCaution_Timer1_CallBack(
  	Controller* pInstance,
  	BOOLEAN TimerOrWaitFired
  );
  
  
  // \ART_SMG :: Created for state : Go
  static void CALLBACK RtsGo_Timer1_CallBack(
  	Controller* pInstance,
  	BOOLEAN TimerOrWaitFired
  );
  
  
  // \ART_SMG :: Created for state : Stop
  static void CALLBACK RtsStop_Timer1_CallBack(
  	Controller* pInstance,
  	BOOLEAN TimerOrWaitFired
  );
  
  
  bool RtsRunToCompletion();
  
  
  // \ART_SMG :: Created for state : Off
  void RtsEnter_Off();
  
  
  // \ART_SMG :: Created for state : Running
  void RtsEnter_Running();
  
  
  // \ART_SMG :: Created for state : Crossing
  void RtsEnter_Crossing();
  
  
  // \ART_SMG :: Created for state : Ready
  void RtsEnter_Ready();
  
  
  // \ART_SMG :: Created for state : Caution
  void RtsEnter_Caution();
  
  
  // \ART_SMG :: Created for state : Go
  void RtsEnter_Go();
  
  
  // \ART_SMG :: Created for state : Stop
  void RtsEnter_Stop();
  
  
  // \ART_SMG :: Created for state : FlashOn
  void RtsEnter_FlashOn();
  
  
  // \ART_SMG :: Created for state : FlashOff
  void RtsEnter_FlashOff();
  
  
  // \ART_SMG :: Created for state : Off
  void RtsExit_Off();
  
  
  // \ART_SMG :: Created for state : Running
  void RtsExit_Running();
  
  
  // \ART_SMG :: Created for state : Crossing
  void RtsExit_Crossing();
  
  
  // \ART_SMG :: Created for state : Ready
  void RtsExit_Ready();
  
  
  // \ART_SMG :: Created for state : Caution
  void RtsExit_Caution();
  
  
  // \ART_SMG :: Created for state : Go
  void RtsExit_Go();
  
  
  // \ART_SMG :: Created for state : Stop
  void RtsExit_Stop();
  
  
  // \ART_SMG :: Created for state : FlashOn
  void RtsExit_FlashOn();
  
  
  // \ART_SMG :: Created for state : FlashOff
  void RtsExit_FlashOff();
  
  
  // \ART_SMG :: Created for state : Running
  void RtsDefault_Running();
  
  
  // \ART_SMG :: Created for state : Crossing
  void RtsDefault_Crossing();
  
  
  static int RtsInjectEvent(
  	char* Event,
  	const int NumParams,
  	const StringArray params,
  	Controller* pInstance
  );
  
  
  static int RtsGetAttributeValue(
  	char* Name,
  	char* Value,
  	const int buflen,
  	Controller* pInstance
  );
  
  
  static int RtsSetAttributeValue(
  	char* Name,
  	char* Value,
  	Controller* pInstance
  );
  
  
  // \ART_SMG :: Created for state : FlashOn
  void RtsFlashOn_Timer1();
  
  
  // \ART_SMG :: Created for state : FlashOff
  void RtsFlashOff_Timer1();
  
  
  // \ART_SMG :: Created for state : Ready
  void RtsReady_Timer1();
  
  
  // \ART_SMG :: Created for state : Caution
  void RtsCaution_Timer1();
  
  
  // \ART_SMG :: Created for state : Go
  void RtsGo_Timer1();
  
  
  // \ART_SMG :: Created for state : Stop
  void RtsStop_Timer1();
  
  
  bool RtsActivate_In_Controller();
  
  
  bool RtsButtonPress_In_Controller();
  
  
  bool RtsDeactivate_In_Controller(
  	const short i,
  	const char j
  );
  
  
  bool RtsFlashOn_Timer1_In_Controller();
  
  
  bool RtsFlashOn_Timer1_In_Running();
  
  
  bool RtsFlashOn_Timer1_In_Crossing();
  
  
  bool RtsFlashOff_Timer1_In_Controller();
  
  
  bool RtsFlashOff_Timer1_In_Running();
  
  
  bool RtsFlashOff_Timer1_In_Crossing();
  
  
  bool RtsReady_Timer1_In_Controller();
  
  
  bool RtsReady_Timer1_In_Running();
  
  
  bool RtsCaution_Timer1_In_Controller();
  
  
  bool RtsCaution_Timer1_In_Running();
  
  
  bool RtsGo_Timer1_In_Controller();
  
  
  bool RtsGo_Timer1_In_Running();
  
  
  bool RtsStop_Timer1_In_Controller();
  
  
  bool RtsStop_Timer1_In_Running();


};

#endif
