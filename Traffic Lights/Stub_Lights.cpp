// File : .\Lights.cpp

#include "StdAfx.h"
#include "Lights.h"


static const RtsClassInfo RtsLights_ClassInfo("4344218c-fbf2-11d2-a53d-00104bb05af8", RTS_STUB);




// Attribute initialization

SimFuncs Lights::classSpecificSimFuncs( &Lights::GetAttributeValue, &Lights::SetAttributeValue, &Lights::InjectEvent, Lights::TimerSet );

SimFuncs* Lights::m_SimFuncs = &classSpecificSimFuncs;


// ARTiSAN generated constructor
Lights::Lights(){
	RtsNotifySynchronous(CREATE,"4344218c-fbf2-11d2-a53d-00104bb05af8",0, NULL);
	RtsRegisterStub(this);
}


// ARTiSAN generated destructor
Lights::~Lights()
{
	RtsUnregister(this);
}


// Operation implementations

void Lights::Red(
	const short on
)
{
  char rtsParam[1][100];
  StringArray rtsParamSA = new char*[1];
  rtsParamSA[0] = rtsParam[0];
  sprintf(rtsParam[0], "%d\0", on);
  RtsNotifyStaticOP("4344218c-fbf2-11d2-a53d-00104bb05af8", "43442192-fbf2-11d2-a53d-00104bb05af8", 1, rtsParamSA);
  RtsNotifyStatic(EVENT, "43442192-fbf2-11d2-a53d-00104bb05af8", 1, rtsParamSA);
}

void Lights::Green(
	const short on
)
{
  char rtsParam[1][100];
  StringArray rtsParamSA = new char*[1];
  rtsParamSA[0] = rtsParam[0];
  sprintf(rtsParam[0], "%d\0", on);
  RtsNotifyStaticOP("4344218c-fbf2-11d2-a53d-00104bb05af8", "43442193-fbf2-11d2-a53d-00104bb05af8", 1, rtsParamSA);
  RtsNotifyStatic(EVENT, "43442193-fbf2-11d2-a53d-00104bb05af8", 1, rtsParamSA);
}

void Lights::Amber(
	const short on
)
{
  char rtsParam[1][100];
  StringArray rtsParamSA = new char*[1];
  rtsParamSA[0] = rtsParam[0];
  sprintf(rtsParam[0], "%d\0", on);
  RtsNotifyStaticOP("4344218c-fbf2-11d2-a53d-00104bb05af8", "43442194-fbf2-11d2-a53d-00104bb05af8", 1, rtsParamSA);
  RtsNotifyStatic(EVENT, "43442194-fbf2-11d2-a53d-00104bb05af8", 1, rtsParamSA);
}

void Lights::Wait(
	const short on
)
{
  char rtsParam[1][100];
  StringArray rtsParamSA = new char*[1];
  rtsParamSA[0] = rtsParam[0];
  sprintf(rtsParam[0], "%d\0", on);
  RtsNotifyStaticOP("4344218c-fbf2-11d2-a53d-00104bb05af8", "bdb6f1a2-fd74-11d2-a540-00104bb05af8", 1, rtsParamSA);
  RtsNotifyStatic(EVENT, "bdb6f1a2-fd74-11d2-a540-00104bb05af8", 1, rtsParamSA);
}

int Lights::RtsInjectEvent(
	char* Event,
	const int NumParams,
	const StringArray params,
	Lights* pInstance
)
{

int Ret = 1;

if ((strcmp(Event, "Red") == 0) && (NumParams == 1))
{
	short on = (short)atoi(params[0]);
	if (Ret == 1)
	{
		pInstance->Red(on);
	}
}

else if ((strcmp(Event, "Green") == 0) && (NumParams == 1))
{
	short on = (short)atoi(params[0]);
	if (Ret == 1)
	{
		pInstance->Green(on);
	}
}

else if ((strcmp(Event, "Amber") == 0) && (NumParams == 1))
{
	short on = (short)atoi(params[0]);
	if (Ret == 1)
	{
		pInstance->Amber(on);
	}
}

else if ((strcmp(Event, "Wait") == 0) && (NumParams == 1))
{
	short on = (short)atoi(params[0]);
	if (Ret == 1)
	{
		pInstance->Wait(on);
	}
}

return Ret;
}

int Lights::RtsGetAttributeValue(
	char* Name,
	char* Value,
	const int buflen,
	Lights* pInstance
)
{

int Ret = 1;
if (strcmp(Name,"$ClassID") == 0)
{
	/* Return the Current Class ID */
	strncpy(Value,"4344218c-fbf2-11d2-a53d-00104bb05af8", buflen);
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

int Lights::RtsSetAttributeValue(
	char* Name,
	char* Value,
	Lights* pInstance
)
{

int Ret = 1;
/* Attribute Not Found or attribute has a complex type */
Ret = 0;
return Ret;
}

int Lights::InjectEvent(
	const char* strEvent,
	const int numParams,
	StringArray params,
	void* pInstance
)
{

return RtsInjectEvent((char*)strEvent, numParams, params, (Lights*)pInstance);
}

int Lights::GetAttributeValue(
	const char* strName,
	char* strValue,
	const int bufLen,
	void* pInstance
)
{

return RtsGetAttributeValue((char*)strName, strValue, bufLen, (Lights*)pInstance);
}

int Lights::SetAttributeValue(
	const char* strName,
	const char* strValue,
	void* pInstance
)
{

return RtsSetAttributeValue((char*)strName, (char*)strValue, (Lights*)pInstance);
}

int Lights::TimerSet(
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

