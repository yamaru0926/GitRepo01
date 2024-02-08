// File : .\Lights.h
//
//
#ifndef __Lights
#define __Lights

#include "RtsSim.h"
class Lights
{


// ARTiSAN generated constructor
public:
	Lights();

// ARTiSAN generated destructor
public:
	~Lights();

public:
  
  // Public|Package attributes
  
  static SimFuncs* m_SimFuncs;
  
  
  // Public|Package operations
  
  static void Red(
  	const short on
  );
  
  
  static void Green(
  	const short on
  );
  
  
  static void Amber(
  	const short on
  );
  
  
  static void Wait(
  	const short on
  );


private:
  
  // Private attributes
  
  static SimFuncs classSpecificSimFuncs;
  
  
  // Private operations
  
  static int RtsInjectEvent(
  	char* Event,
  	const int NumParams,
  	const StringArray params,
  	Lights* pInstance
  );
  
  
  static int RtsGetAttributeValue(
  	char* Name,
  	char* Value,
  	const int buflen,
  	Lights* pInstance
  );
  
  
  static int RtsSetAttributeValue(
  	char* Name,
  	char* Value,
  	Lights* pInstance
  );
  
  
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


};

#endif
// comment..