// File : .\RtsFactory.cpp

#include "StdAfx.h"
#include "RtsSim.h"
#include "Controller.h"



int main();

int main()
{

	INIT_SIMULATION
	Controller* pObject = new Controller();
	pObject->StartStateMachine();
	printf("Hit return to exit\n");
	while (getchar() != '\n');
	delete pObject;
	END_SIMULATION
	return 0;
}
