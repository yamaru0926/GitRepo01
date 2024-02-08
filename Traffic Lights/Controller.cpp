// File : .\Controller.cpp

#include "StdAfx.h"
#include "Controller.h"


static const RtsClassInfo RtsController_ClassInfo("43442151-fbf2-11d2-a53d-00104bb05af8", RTS_STM);




// Attribute initialization

SimFuncs Controller::classSpecificSimFuncs( &Controller::GetAttributeValue, &Controller::SetAttributeValue, &Controller::InjectEvent, Controller::TimerSet );

SimFuncs* Controller::m_SimFuncs = &classSpecificSimFuncs;


// Operation implementations

int Controller::InjectEvent(
	const char* strEvent,
	const int numParams,
	StringArray params,
	void* pInstance
)
{

return RtsInjectEvent((char*)strEvent, numParams, params, (Controller*)pInstance);
}

int Controller::GetAttributeValue(
	const char* strName,
	char* strValue,
	const int bufLen,
	void* pInstance
)
{

return RtsGetAttributeValue((char*)strName, strValue, bufLen, (Controller*)pInstance);
}

int Controller::SetAttributeValue(
	const char* strName,
	const char* strValue,
	void* pInstance
)
{

return RtsSetAttributeValue((char*)strName, (char*)strValue, (Controller*)pInstance);
}

int Controller::TimerSet(
	const bool bPaused,
	const RtsTimer* pTimerID,
	const unsigned long ulTimeToFire,
	void* pTimerDetails,
	const long lMultiplier
)
{

int ret = 1;
if(bPaused)
{
	RtsPauseTimer(pTimerID);
}
else
{
	RtsReStartTimer(pTimerID, ulTimeToFire, pTimerDetails);
}
return ret;
}

void Controller::StartStateMachine()
{


RtsCreateSemaphore(RtsBusy);
RtsLock(RtsBusy);

/* Initializing Timers */
RtsAttReady_Timer1 = NULL;
RtsAttCaution_Timer1 = NULL;
RtsAttGo_Timer1 = NULL;
RtsAttStop_Timer1 = NULL;
RtsAttFlashOn_Timer1 = NULL;
RtsAttFlashOff_Timer1 = NULL;

/* Initializing State Vectors to NotIn */
RtsCurrent_Controller=RtsController_States_NotIn_Controller;
RtsCurrent_Running=RtsRunning_States_NotIn_Running;
RtsCurrent_Crossing=RtsCrossing_States_NotIn_Crossing;

while(RtsRunToCompletion());
RtsUnlock(RtsBusy);
}

Controller::Controller():
ped_wait(0)
{
RtsNotifySynchronous(CREATE,"43442151-fbf2-11d2-a53d-00104bb05af8",0, NULL);


}

void CALLBACK Controller::RtsFlashOn_Timer1_CallBack(
	Controller* pInstance,
	BOOLEAN TimerOrWaitFired
)
{

pInstance->RtsFlashOn_Timer1();
}

void CALLBACK Controller::RtsFlashOff_Timer1_CallBack(
	Controller* pInstance,
	BOOLEAN TimerOrWaitFired
)
{

pInstance->RtsFlashOff_Timer1();
}

void CALLBACK Controller::RtsReady_Timer1_CallBack(
	Controller* pInstance,
	BOOLEAN TimerOrWaitFired
)
{

pInstance->RtsReady_Timer1();
}

void CALLBACK Controller::RtsCaution_Timer1_CallBack(
	Controller* pInstance,
	BOOLEAN TimerOrWaitFired
)
{

pInstance->RtsCaution_Timer1();
}

void CALLBACK Controller::RtsGo_Timer1_CallBack(
	Controller* pInstance,
	BOOLEAN TimerOrWaitFired
)
{

pInstance->RtsGo_Timer1();
}

void CALLBACK Controller::RtsStop_Timer1_CallBack(
	Controller* pInstance,
	BOOLEAN TimerOrWaitFired
)
{

pInstance->RtsStop_Timer1();
}

bool Controller::RtsRunToCompletion()
{


if (RtsCurrent_Running == RtsRunning_States_Crossing && RtsCurrent_Crossing == RtsCrossing_States_NotIn_Crossing)
{
	RtsExit_Crossing();
	/* Simulation support : Notification function calls for transition */
	RtsNotify(TRANSITION,"0018e622-fd6b-11d2-a540-00104bb05af8",0,NULL);
	
	RtsEnter_Go();
	return true;
}
if (RtsCurrent_Controller == RtsController_States_NotIn_Controller)
{
	/* Simulation support : Notification function calls for Entry and Exit of Initial state */
	RtsNotify(ENTER,"43442167-fbf2-11d2-a53d-00104bb05af8",0,NULL);
	RtsNotify(EXIT,"43442167-fbf2-11d2-a53d-00104bb05af8",0,NULL);
	
	/* Simulation support : Notification function calls for transition */
	RtsNotify(TRANSITION,"43442169-fbf2-11d2-a53d-00104bb05af8",0,NULL);
	
	RtsDefault_Running();
	return true;
}
return false;
}

Controller::~Controller()
{

RtsLock(RtsBusy);
RtsStopTimer(RtsAttReady_Timer1);
RtsStopTimer(RtsAttCaution_Timer1);
RtsStopTimer(RtsAttGo_Timer1);
RtsStopTimer(RtsAttStop_Timer1);
RtsStopTimer(RtsAttFlashOn_Timer1);
RtsStopTimer(RtsAttFlashOff_Timer1);
if (RtsCurrent_Controller == RtsController_States_Running)
{
	RtsExit_Running();
	/* Simulation support : Notification function call for transition to final state */
	RtsNotify(TRANSITION,"5b638f12-2e26-11d3-a571-00104bb05af8",0,NULL);
	
	RtsCurrent_Controller = RtsController_States_NotIn_Controller;
	
	/* Simulation support : Notification function call for entering final state */
	RtsNotify(ENTER,"a45ea742-fe1c-11d2-a541-00104bb05af8",0,NULL);
	
}
RtsUnlock(RtsBusy);
RtsDeleteSemaphore(RtsBusy);

RtsUnregister(this);
}

void Controller::RtsEnter_Off()
{

/* Simulation support : Notification function call for entering state : Off */
RtsNotify(ENTER,"5b638f17-2e26-11d3-a571-00104bb05af8",0,NULL);

RtsCurrent_Controller = RtsController_States_Off;

}

void Controller::RtsEnter_Running()
{

/* Simulation support : Notification function call for entering state : Running */
RtsNotify(ENTER,"43442165-fbf2-11d2-a53d-00104bb05af8",0,NULL);

RtsCurrent_Controller = RtsController_States_Running;

/* Entry Actions */

// ## Action [f6e23ed2-fd7b-11d2-a540-00104bb05af8] 
ped_wait=0;
// ## Action End 

}

void Controller::RtsEnter_Crossing()
{

/* Simulation support : Notification function call for entering state : Crossing */
RtsNotify(ENTER,"0018e609-fd6b-11d2-a540-00104bb05af8",0,NULL);

RtsCurrent_Running = RtsRunning_States_Crossing;

/* Entry Actions */

// ## Action [0018e617-fd6b-11d2-a540-00104bb05af8] 
Lights::Red(0);
ped_wait=0;
// ## Action End 

}

void Controller::RtsEnter_Ready()
{

/* Simulation support : Notification function call for entering state : Ready */
RtsNotify(ENTER,"4344215f-fbf2-11d2-a53d-00104bb05af8",0,NULL);

RtsCurrent_Running = RtsRunning_States_Ready;

/* Entry Actions */

// ## Action [4344219e-fbf2-11d2-a53d-00104bb05af8] 
Lights::Amber(1);
// ## Action End 

/* Start Timers */
RtsStartTimer(RtsAttReady_Timer1,RtsReady_Timer1_CallBack,2000);
}

void Controller::RtsEnter_Caution()
{

/* Simulation support : Notification function call for entering state : Caution */
RtsNotify(ENTER,"43442163-fbf2-11d2-a53d-00104bb05af8",0,NULL);

RtsCurrent_Running = RtsRunning_States_Caution;

/* Entry Actions */

// ## Action [434421a4-fbf2-11d2-a53d-00104bb05af8] 
Lights::Amber(1);
// ## Action End 

/* Start Timers */
RtsStartTimer(RtsAttCaution_Timer1,RtsCaution_Timer1_CallBack,2000);
}

void Controller::RtsEnter_Go()
{

/* Simulation support : Notification function call for entering state : Go */
RtsNotify(ENTER,"43442161-fbf2-11d2-a53d-00104bb05af8",0,NULL);

RtsCurrent_Running = RtsRunning_States_Go;

/* Entry Actions */

// ## Action [434421a7-fbf2-11d2-a53d-00104bb05af8] 
Lights::Green(1);
// ## Action End 

/* Start Timers */
RtsStartTimer(RtsAttGo_Timer1,RtsGo_Timer1_CallBack,4000);
}

void Controller::RtsEnter_Stop()
{

/* Simulation support : Notification function call for entering state : Stop */
RtsNotify(ENTER,"43442158-fbf2-11d2-a53d-00104bb05af8",0,NULL);

RtsCurrent_Running = RtsRunning_States_Stop;

/* Entry Actions */

// ## Action [43442198-fbf2-11d2-a53d-00104bb05af8] 
Lights::Red(1);
Lights::Wait(0);
// ## Action End 

/* Start Timers */
RtsStartTimer(RtsAttStop_Timer1,RtsStop_Timer1_CallBack,4000);
}

void Controller::RtsEnter_FlashOn()
{

/* Simulation support : Notification function call for entering state : FlashOn */
RtsNotify(ENTER,"b1665af3-fe27-11d2-a541-00104bb05af8",0,NULL);

RtsCurrent_Crossing = RtsCrossing_States_FlashOn;

/* Entry Actions */

// ## Action [b1665afe-fe27-11d2-a541-00104bb05af8] 
Lights::Amber(1);
// ## Action End 

/* Start Timers */
RtsStartTimer(RtsAttFlashOn_Timer1,RtsFlashOn_Timer1_CallBack,1000);
}

void Controller::RtsEnter_FlashOff()
{

/* Simulation support : Notification function call for entering state : FlashOff */
RtsNotify(ENTER,"b1665af5-fe27-11d2-a541-00104bb05af8",0,NULL);

RtsCurrent_Crossing = RtsCrossing_States_FlashOff;

/* Start Timers */
RtsStartTimer(RtsAttFlashOff_Timer1,RtsFlashOff_Timer1_CallBack,1000);
}

void Controller::RtsExit_Off()
{

if (RtsCurrent_Controller == RtsController_States_Off)
{
	/* Simulation support : Notification function call for exiting state : Off */
	RtsNotify(EXIT,"5b638f17-2e26-11d3-a571-00104bb05af8",0,NULL);
	
}
}

void Controller::RtsExit_Running()
{

if (RtsCurrent_Controller == RtsController_States_Running)
{
	/* Simulation support : Notification function call for exiting state : Running */
	RtsNotify(EXIT,"43442165-fbf2-11d2-a53d-00104bb05af8",0,NULL);
	
	switch(RtsCurrent_Running)
	{
		case RtsRunning_States_Crossing:
			RtsExit_Crossing();
			break;
		case RtsRunning_States_Ready:
			RtsExit_Ready();
			break;
		case RtsRunning_States_Caution:
			RtsExit_Caution();
			break;
		case RtsRunning_States_Go:
			RtsExit_Go();
			break;
		case RtsRunning_States_Stop:
			RtsExit_Stop();
			break;
		default:
			break;
	}
	RtsCurrent_Running = RtsRunning_States_NotIn_Running;
	
}
}

void Controller::RtsExit_Crossing()
{

if (RtsCurrent_Running == RtsRunning_States_Crossing)
{
	/* Simulation support : Notification function call for exiting state : Crossing */
	RtsNotify(EXIT,"0018e609-fd6b-11d2-a540-00104bb05af8",0,NULL);
	
	switch(RtsCurrent_Crossing)
	{
		case RtsCrossing_States_FlashOn:
			RtsExit_FlashOn();
			break;
		case RtsCrossing_States_FlashOff:
			RtsExit_FlashOff();
			break;
		default:
			break;
	}
	RtsCurrent_Crossing = RtsCrossing_States_NotIn_Crossing;
	
}
}

void Controller::RtsExit_Ready()
{

if (RtsCurrent_Running == RtsRunning_States_Ready)
{
	/* Simulation support : Notification function call for exiting state : Ready */
	RtsNotify(EXIT,"4344215f-fbf2-11d2-a53d-00104bb05af8",0,NULL);
	
	/* Exit Actions */
	
// ## Action [434421aa-fbf2-11d2-a53d-00104bb05af8] 
Lights::Red(0);
Lights::Amber(0);
// ## Action End 

	
	/* Stop Timers */
	RtsStopTimer(RtsAttReady_Timer1);
	
}
}

void Controller::RtsExit_Caution()
{

if (RtsCurrent_Running == RtsRunning_States_Caution)
{
	/* Simulation support : Notification function call for exiting state : Caution */
	RtsNotify(EXIT,"43442163-fbf2-11d2-a53d-00104bb05af8",0,NULL);
	
	/* Exit Actions */
	
// ## Action [434421a1-fbf2-11d2-a53d-00104bb05af8] 
Lights::Amber(0);
// ## Action End 

	
	/* Stop Timers */
	RtsStopTimer(RtsAttCaution_Timer1);
	
}
}

void Controller::RtsExit_Go()
{

if (RtsCurrent_Running == RtsRunning_States_Go)
{
	/* Simulation support : Notification function call for exiting state : Go */
	RtsNotify(EXIT,"43442161-fbf2-11d2-a53d-00104bb05af8",0,NULL);
	
	/* Exit Actions */
	
// ## Action [434421ad-fbf2-11d2-a53d-00104bb05af8] 
Lights::Green(0);
// ## Action End 

	
	/* Stop Timers */
	RtsStopTimer(RtsAttGo_Timer1);
	
}
}

void Controller::RtsExit_Stop()
{

if (RtsCurrent_Running == RtsRunning_States_Stop)
{
	/* Simulation support : Notification function call for exiting state : Stop */
	RtsNotify(EXIT,"43442158-fbf2-11d2-a53d-00104bb05af8",0,NULL);
	
	/* Stop Timers */
	RtsStopTimer(RtsAttStop_Timer1);
	
}
}

void Controller::RtsExit_FlashOn()
{

if (RtsCurrent_Crossing == RtsCrossing_States_FlashOn)
{
	/* Simulation support : Notification function call for exiting state : FlashOn */
	RtsNotify(EXIT,"b1665af3-fe27-11d2-a541-00104bb05af8",0,NULL);
	
	/* Exit Actions */
	
// ## Action [98368722-fe2c-11d2-a541-00104bb05af8] 
Lights::Amber(0);
// ## Action End 

	
	/* Stop Timers */
	RtsStopTimer(RtsAttFlashOn_Timer1);
	
}
}

void Controller::RtsExit_FlashOff()
{

if (RtsCurrent_Crossing == RtsCrossing_States_FlashOff)
{
	/* Simulation support : Notification function call for exiting state : FlashOff */
	RtsNotify(EXIT,"b1665af5-fe27-11d2-a541-00104bb05af8",0,NULL);
	
	/* Stop Timers */
	RtsStopTimer(RtsAttFlashOff_Timer1);
	
}
}

void Controller::RtsDefault_Running()
{

/* Simulation support : Notification function calls for entry and exit of initial state */
RtsNotify(ENTER,"43442156-fbf2-11d2-a53d-00104bb05af8",0,NULL);
RtsNotify(EXIT,"43442156-fbf2-11d2-a53d-00104bb05af8",0,NULL);
RtsEnter_Running();

/* Simulation support : Notification function calls for default transition */
RtsNotify(TRANSITION,"4344215a-fbf2-11d2-a53d-00104bb05af8",0,NULL);
RtsEnter_Stop();

}

void Controller::RtsDefault_Crossing()
{

/* Simulation support : Notification function calls for entry and exit of initial state */
RtsNotify(ENTER,"b1665af1-fe27-11d2-a541-00104bb05af8",0,NULL);
RtsNotify(EXIT,"b1665af1-fe27-11d2-a541-00104bb05af8",0,NULL);
RtsEnter_Crossing();

/* Simulation support : Notification function calls for default transition */
RtsNotify(TRANSITION,"b1665af9-fe27-11d2-a541-00104bb05af8",0,NULL);

// ## Action [b1665afb-fe27-11d2-a541-00104bb05af8] 
flashes=0;
// ## Action End 

RtsEnter_FlashOn();

}

int Controller::RtsInjectEvent(
	char* Event,
	const int NumParams,
	const StringArray params,
	Controller* pInstance
)
{

int Ret = 1;
if (strlen(Event) == 0)
{
	while(pInstance->RtsRunToCompletion());
}
else
{
	if ((strcmp(Event, "Activate") == 0))
	{
		if (Ret == 1)
		{
			pInstance->RtsActivate();
		}
	}
	
	else if ((strcmp(Event, "ButtonPress") == 0))
	{
		if (Ret == 1)
		{
			pInstance->RtsButtonPress();
		}
	}
	
	else if ((strcmp(Event, "Deactivate") == 0))
	{
		short i = (short)atoi(params[0]);
		if (Ret == 1)
		{
			pInstance->RtsDeactivate(i,*params[1]);
		}
	}
	
	else if ((strcmp(Event, "b1665b08-fe27-11d2-a541-00104bb05af8") == 0))
	{
		if (Ret == 1)
		{
			pInstance->RtsFlashOn_Timer1();
		}
	}
	
	else if ((strcmp(Event, "b1665b17-fe27-11d2-a541-00104bb05af8") == 0))
	{
		if (Ret == 1)
		{
			pInstance->RtsFlashOff_Timer1();
		}
	}
	
	else if ((strcmp(Event, "43442175-fbf2-11d2-a53d-00104bb05af8") == 0))
	{
		if (Ret == 1)
		{
			pInstance->RtsReady_Timer1();
		}
	}
	
	else if ((strcmp(Event, "4344217f-fbf2-11d2-a53d-00104bb05af8") == 0))
	{
		if (Ret == 1)
		{
			pInstance->RtsCaution_Timer1();
		}
	}
	
	else if ((strcmp(Event, "4344217a-fbf2-11d2-a53d-00104bb05af8") == 0))
	{
		if (Ret == 1)
		{
			pInstance->RtsGo_Timer1();
		}
	}
	
	else if ((strcmp(Event, "0018e61f-fd6b-11d2-a540-00104bb05af8") == 0))
	{
		if (Ret == 1)
		{
			pInstance->RtsStop_Timer1();
		}
	}
	
	else
	{
		/* Event Not Found */
		Ret = 0;
	}
	
}
return Ret;
}

int Controller::RtsGetAttributeValue(
	char* Name,
	char* Value,
	const int buflen,
	Controller* pInstance
)
{

int Ret = 1;
if (strcmp(Name, "ped_wait") == 0)
{
	sprintf(Value, "%d\0",(pInstance->ped_wait));
	
}
else if (strcmp(Name, "flashes") == 0)
{
	sprintf(Value, "%d\0",(pInstance->flashes));
	
}
else if (strcmp(Name, "RtsCurrent_Controller") == 0)
{
	/* cannot return or set the value of an attribute with no underlyingtype */
	Ret = 0;
}
else if (strcmp(Name, "RtsCurrent_Running") == 0)
{
	/* cannot return or set the value of an attribute with no underlyingtype */
	Ret = 0;
}
else if (strcmp(Name, "RtsCurrent_Crossing") == 0)
{
	/* cannot return or set the value of an attribute with no underlyingtype */
	Ret = 0;
}
else if (strcmp(Name, "RtsBusy") == 0)
{
	strncpy(Value, (RtsIsLocked((pInstance->RtsBusy))?"1":"0"), buflen );
}
else if (strcmp(Name, "RtsCurrent_Controller") == 0)
{
	switch((pInstance->RtsCurrent_Controller))
	{
		case RtsController_States_Off:
			strncpy(Value,"Off",buflen);
			break;
		case RtsController_States_Running:
			strncpy(Value,"Running",buflen);
			break;
		case RtsController_States_NotIn_Controller:
			strncpy(Value,"NotIn_Controller",buflen);
			break;
		default:
			/* Invalid enumeration */
			Ret = 0;
			break;
	}
}
else if (strcmp(Name, "RtsCurrent_Running") == 0)
{
	switch((pInstance->RtsCurrent_Running))
	{
		case RtsRunning_States_Crossing:
			strncpy(Value,"Crossing",buflen);
			break;
		case RtsRunning_States_Ready:
			strncpy(Value,"Ready",buflen);
			break;
		case RtsRunning_States_Caution:
			strncpy(Value,"Caution",buflen);
			break;
		case RtsRunning_States_Go:
			strncpy(Value,"Go",buflen);
			break;
		case RtsRunning_States_Stop:
			strncpy(Value,"Stop",buflen);
			break;
		case RtsRunning_States_NotIn_Running:
			strncpy(Value,"NotIn_Running",buflen);
			break;
		default:
			/* Invalid enumeration */
			Ret = 0;
			break;
	}
}
else if (strcmp(Name, "RtsCurrent_Crossing") == 0)
{
	switch((pInstance->RtsCurrent_Crossing))
	{
		case RtsCrossing_States_FlashOn:
			strncpy(Value,"FlashOn",buflen);
			break;
		case RtsCrossing_States_FlashOff:
			strncpy(Value,"FlashOff",buflen);
			break;
		case RtsCrossing_States_NotIn_Crossing:
			strncpy(Value,"NotIn_Crossing",buflen);
			break;
		default:
			/* Invalid enumeration */
			Ret = 0;
			break;
	}
}
else if (strcmp(Name, "RtsBusy") == 0)
{
	strncpy(Value, (RtsIsLocked((pInstance->RtsBusy))?"1":"0"), buflen );
}
else if (strcmp(Name,"$ClassID") == 0)
{
	/* Return the Current Class ID */
	strncpy(Value,"43442151-fbf2-11d2-a53d-00104bb05af8", buflen);
}
else if (strcmp(Name,"$Model") == 0)
{
	/* Return the Current Model ID */
	strncpy(Value,"43442142-fbf2-11d2-a53d-00104bb05af8", buflen);
}
else
{
	/* Attribute Not Found or attribute has a complex type */
	Ret = 0;
}
return Ret;
}

int Controller::RtsSetAttributeValue(
	char* Name,
	char* Value,
	Controller* pInstance
)
{

int Ret = 1;
if (strcmp(Name, "ped_wait") == 0)
{
	(pInstance->ped_wait) = (short)atoi(Value);
}
else if (strcmp(Name, "flashes") == 0)
{
	(pInstance->flashes) = (short)atoi(Value);
}
else if (strcmp(Name, "RtsCurrent_Controller") == 0)
{
	/* cannot return or set the value of an attribute with no underlyingtype */
	Ret = 0;
}
else if (strcmp(Name, "RtsCurrent_Running") == 0)
{
	/* cannot return or set the value of an attribute with no underlyingtype */
	Ret = 0;
}
else if (strcmp(Name, "RtsCurrent_Crossing") == 0)
{
	/* cannot return or set the value of an attribute with no underlyingtype */
	Ret = 0;
}
else if (strcmp(Name, "RtsCurrent_Controller") == 0)
{
	if (strcmp(Value, "Off") == 0 )
	{
		(pInstance->RtsCurrent_Controller) = RtsController_States_Off;
	}
	else if (strcmp(Value, "Running") == 0 )
	{
		(pInstance->RtsCurrent_Controller) = RtsController_States_Running;
	}
	else if (strcmp(Value, "NotIn_Controller") == 0 )
	{
		(pInstance->RtsCurrent_Controller) = RtsController_States_NotIn_Controller;
	}
	else
	{
		/* No matching enumeration */
		Ret = 0;
	}
}
else if (strcmp(Name, "RtsCurrent_Running") == 0)
{
	if (strcmp(Value, "Crossing") == 0 )
	{
		(pInstance->RtsCurrent_Running) = RtsRunning_States_Crossing;
	}
	else if (strcmp(Value, "Ready") == 0 )
	{
		(pInstance->RtsCurrent_Running) = RtsRunning_States_Ready;
	}
	else if (strcmp(Value, "Caution") == 0 )
	{
		(pInstance->RtsCurrent_Running) = RtsRunning_States_Caution;
	}
	else if (strcmp(Value, "Go") == 0 )
	{
		(pInstance->RtsCurrent_Running) = RtsRunning_States_Go;
	}
	else if (strcmp(Value, "Stop") == 0 )
	{
		(pInstance->RtsCurrent_Running) = RtsRunning_States_Stop;
	}
	else if (strcmp(Value, "NotIn_Running") == 0 )
	{
		(pInstance->RtsCurrent_Running) = RtsRunning_States_NotIn_Running;
	}
	else
	{
		/* No matching enumeration */
		Ret = 0;
	}
}
else if (strcmp(Name, "RtsCurrent_Crossing") == 0)
{
	if (strcmp(Value, "FlashOn") == 0 )
	{
		(pInstance->RtsCurrent_Crossing) = RtsCrossing_States_FlashOn;
	}
	else if (strcmp(Value, "FlashOff") == 0 )
	{
		(pInstance->RtsCurrent_Crossing) = RtsCrossing_States_FlashOff;
	}
	else if (strcmp(Value, "NotIn_Crossing") == 0 )
	{
		(pInstance->RtsCurrent_Crossing) = RtsCrossing_States_NotIn_Crossing;
	}
	else
	{
		/* No matching enumeration */
		Ret = 0;
	}
}
else
{
	/* Attribute Not Found or attribute has a complex type */
	Ret = 0;
}
return Ret;
}

void Controller::RtsActivate()
{

RtsLock(RtsBusy);
RtsActivate_In_Controller();
while(RtsRunToCompletion());
RtsUnlock(RtsBusy);

}

void Controller::RtsButtonPress()
{

RtsLock(RtsBusy);
RtsButtonPress_In_Controller();
while(RtsRunToCompletion());
RtsUnlock(RtsBusy);

}

void Controller::RtsDeactivate(
	const short i,
	const char j
)
{

RtsLock(RtsBusy);
RtsDeactivate_In_Controller(i, j);
while(RtsRunToCompletion());
RtsUnlock(RtsBusy);

}

void Controller::RtsFlashOn_Timer1()
{

RtsNotifyOP("43442151-fbf2-11d2-a53d-00104bb05af8", "e4cff314-81ac-4286-9534-6121cd753ccb", 0, 0);
RtsStopTimer(RtsAttFlashOn_Timer1);
RtsLock(RtsBusy);
RtsFlashOn_Timer1_In_Controller();
while(RtsRunToCompletion());
RtsUnlock(RtsBusy);

}

void Controller::RtsFlashOff_Timer1()
{

RtsNotifyOP("43442151-fbf2-11d2-a53d-00104bb05af8", "e4cff314-81ac-4286-9534-6121cd753ccb", 0, 0);
RtsStopTimer(RtsAttFlashOff_Timer1);
RtsLock(RtsBusy);
RtsFlashOff_Timer1_In_Controller();
while(RtsRunToCompletion());
RtsUnlock(RtsBusy);

}

void Controller::RtsReady_Timer1()
{

RtsNotifyOP("43442151-fbf2-11d2-a53d-00104bb05af8", "e4cff314-81ac-4286-9534-6121cd753ccb", 0, 0);
RtsStopTimer(RtsAttReady_Timer1);
RtsLock(RtsBusy);
RtsReady_Timer1_In_Controller();
while(RtsRunToCompletion());
RtsUnlock(RtsBusy);

}

void Controller::RtsCaution_Timer1()
{

RtsNotifyOP("43442151-fbf2-11d2-a53d-00104bb05af8", "e4cff314-81ac-4286-9534-6121cd753ccb", 0, 0);
RtsStopTimer(RtsAttCaution_Timer1);
RtsLock(RtsBusy);
RtsCaution_Timer1_In_Controller();
while(RtsRunToCompletion());
RtsUnlock(RtsBusy);

}

void Controller::RtsGo_Timer1()
{

RtsNotifyOP("43442151-fbf2-11d2-a53d-00104bb05af8", "e4cff314-81ac-4286-9534-6121cd753ccb", 0, 0);
RtsStopTimer(RtsAttGo_Timer1);
RtsLock(RtsBusy);
RtsGo_Timer1_In_Controller();
while(RtsRunToCompletion());
RtsUnlock(RtsBusy);

}

void Controller::RtsStop_Timer1()
{

RtsNotifyOP("43442151-fbf2-11d2-a53d-00104bb05af8", "e4cff314-81ac-4286-9534-6121cd753ccb", 0, 0);
RtsStopTimer(RtsAttStop_Timer1);
RtsLock(RtsBusy);
RtsStop_Timer1_In_Controller();
while(RtsRunToCompletion());
RtsUnlock(RtsBusy);

}

bool Controller::RtsActivate_In_Controller()
{

if (RtsCurrent_Controller == RtsController_States_Off)
{
	RtsExit_Off();
	/* Simulation support : Notification function calls for transition */
	RtsNotify(TRANSITION,"5b638f19-2e26-11d3-a571-00104bb05af8",0,NULL);
	
	RtsDefault_Running();
	
	return true;
}
return false;
}

bool Controller::RtsButtonPress_In_Controller()
{

if (RtsCurrent_Controller == RtsController_States_Running)
{
	/* Simulation support : Notification function calls for transition */
	RtsNotify(TRANSITION,"0018e602-fd6b-11d2-a540-00104bb05af8",0,NULL);
	
	
// ## Action [0018e602-fd6b-11d2-a540-00104bb05af8] 
ped_wait=1;
Lights::Wait(1);
// ## Action End 

	
	return true;
}
return false;
}

bool Controller::RtsDeactivate_In_Controller(
	const short i,
	const char j
)
{

if (RtsCurrent_Controller == RtsController_States_Running)
{
	RtsExit_Running();
	/* Simulation support : Notification function calls for transition */
	RtsNotify(TRANSITION,"a45ea744-fe1c-11d2-a541-00104bb05af8",0,NULL);
	
	RtsEnter_Off();
	
	return true;
}
return false;
}

bool Controller::RtsFlashOn_Timer1_In_Controller()
{

if (RtsCurrent_Controller == RtsController_States_Running)
{
	if (RtsFlashOn_Timer1_In_Running())
	{
		return true;
	}
}
return false;
}

bool Controller::RtsFlashOn_Timer1_In_Running()
{

if (RtsCurrent_Running == RtsRunning_States_Crossing)
{
	if (RtsFlashOn_Timer1_In_Crossing())
	{
		return true;
	}
}
return false;
}

bool Controller::RtsFlashOn_Timer1_In_Crossing()
{

if (RtsCurrent_Crossing == RtsCrossing_States_FlashOn)
{
	if (
// ## Guard [b1665b0e-fe27-11d2-a541-00104bb05af8] 
flashes < 3
// ## Guard End 
)
	{
		RtsExit_FlashOn();
		/* Simulation support : Notification function calls for transition */
		RtsNotify(TRANSITION,"b1665b06-fe27-11d2-a541-00104bb05af8",0,NULL);
		
		/* Simulation support : Notification function calls for transition */
		RtsNotify(TRANSITION,"b1665b0b-fe27-11d2-a541-00104bb05af8",0,NULL);
		
		
// ## Action [b1665b0d-fe27-11d2-a541-00104bb05af8] 
flashes++;
// ## Action End 

		RtsEnter_FlashOff();
		
		return true;
	}RtsExit_FlashOn();
	/* Simulation support : Notification function calls for transition */
	RtsNotify(TRANSITION,"b1665b06-fe27-11d2-a541-00104bb05af8",0,NULL);
	
	/* Simulation support : Notification function calls for transition */
	RtsNotify(TRANSITION,"b1665b10-fe27-11d2-a541-00104bb05af8",0,NULL);
	
	RtsCurrent_Crossing = RtsCrossing_States_NotIn_Crossing;
	/* Simulation support : Notification function call for entering final state */
	RtsNotify(ENTER,"b1665af7-fe27-11d2-a541-00104bb05af8",0,NULL);
	return true;
}
return false;
}

bool Controller::RtsFlashOff_Timer1_In_Controller()
{

if (RtsCurrent_Controller == RtsController_States_Running)
{
	if (RtsFlashOff_Timer1_In_Running())
	{
		return true;
	}
}
return false;
}

bool Controller::RtsFlashOff_Timer1_In_Running()
{

if (RtsCurrent_Running == RtsRunning_States_Crossing)
{
	if (RtsFlashOff_Timer1_In_Crossing())
	{
		return true;
	}
}
return false;
}

bool Controller::RtsFlashOff_Timer1_In_Crossing()
{

if (RtsCurrent_Crossing == RtsCrossing_States_FlashOff)
{
	RtsExit_FlashOff();
	/* Simulation support : Notification function calls for transition */
	RtsNotify(TRANSITION,"b1665b15-fe27-11d2-a541-00104bb05af8",0,NULL);
	
	RtsEnter_FlashOn();
	
	return true;
}
return false;
}

bool Controller::RtsReady_Timer1_In_Controller()
{

if (RtsCurrent_Controller == RtsController_States_Running)
{
	if (RtsReady_Timer1_In_Running())
	{
		return true;
	}
}
return false;
}

bool Controller::RtsReady_Timer1_In_Running()
{

if (RtsCurrent_Running == RtsRunning_States_Ready)
{
	RtsExit_Ready();
	/* Simulation support : Notification function calls for transition */
	RtsNotify(TRANSITION,"43442173-fbf2-11d2-a53d-00104bb05af8",0,NULL);
	
	RtsEnter_Go();
	
	return true;
}
return false;
}

bool Controller::RtsCaution_Timer1_In_Controller()
{

if (RtsCurrent_Controller == RtsController_States_Running)
{
	if (RtsCaution_Timer1_In_Running())
	{
		return true;
	}
}
return false;
}

bool Controller::RtsCaution_Timer1_In_Running()
{

if (RtsCurrent_Running == RtsRunning_States_Caution)
{
	RtsExit_Caution();
	/* Simulation support : Notification function calls for transition */
	RtsNotify(TRANSITION,"4344217d-fbf2-11d2-a53d-00104bb05af8",0,NULL);
	
	RtsEnter_Stop();
	
	return true;
}
return false;
}

bool Controller::RtsGo_Timer1_In_Controller()
{

if (RtsCurrent_Controller == RtsController_States_Running)
{
	if (RtsGo_Timer1_In_Running())
	{
		return true;
	}
}
return false;
}

bool Controller::RtsGo_Timer1_In_Running()
{

if (RtsCurrent_Running == RtsRunning_States_Go)
{
	RtsExit_Go();
	/* Simulation support : Notification function calls for transition */
	RtsNotify(TRANSITION,"43442178-fbf2-11d2-a53d-00104bb05af8",0,NULL);
	
	RtsEnter_Caution();
	
	return true;
}
return false;
}

bool Controller::RtsStop_Timer1_In_Controller()
{

if (RtsCurrent_Controller == RtsController_States_Running)
{
	if (RtsStop_Timer1_In_Running())
	{
		return true;
	}
}
return false;
}

bool Controller::RtsStop_Timer1_In_Running()
{

if (RtsCurrent_Running == RtsRunning_States_Stop)
{
	if (
// ## Guard [b1665ae7-fe27-11d2-a541-00104bb05af8] 
ped_wait==0
// ## Guard End 
)
	{
		RtsExit_Stop();
		/* Simulation support : Notification function calls for transition */
		RtsNotify(TRANSITION,"0018e61d-fd6b-11d2-a540-00104bb05af8",0,NULL);
		
		/* Simulation support : Notification function calls for transition */
		RtsNotify(TRANSITION,"b1665ae4-fe27-11d2-a541-00104bb05af8",0,NULL);
		
		RtsEnter_Ready();
		
		return true;
	}RtsExit_Stop();
	/* Simulation support : Notification function calls for transition */
	RtsNotify(TRANSITION,"0018e61d-fd6b-11d2-a540-00104bb05af8",0,NULL);
	
	/* Simulation support : Notification function calls for transition */
	RtsNotify(TRANSITION,"b1665ae9-fe27-11d2-a541-00104bb05af8",0,NULL);
	
	RtsDefault_Crossing();
	
	return true;
}
return false;
}

