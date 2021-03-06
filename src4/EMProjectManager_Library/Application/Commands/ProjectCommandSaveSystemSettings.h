/*******************************************************
* Creator: Martin Rudefelt
* Portability: non-native
*-------------------------------------------------------
* 
*******************************************************/

#include "EMGlobals.h"

#ifndef __PROJECT_COMMAND_SAVE_SYSTEM_SETTINGS
#define __PROJECT_COMMAND_SAVE_SYSTEM_SETTINGS

#include "EMCommand.h"

class ProjectCommandSaveSystemSettings : public EMCommand
{
public:
	ProjectCommandSaveSystemSettings();
	void ExecuteE() { };
	void* ExecuteE(void* p_upParameterOne, void* p_upParameterTwo, void* p_upParameterThree);
	bool IsUndoable();
	bool RequiresParameters();
};

#endif
