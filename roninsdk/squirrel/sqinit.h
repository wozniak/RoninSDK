#pragma once

#include "squirrel/sqclasstypes.h"
#include "speedrunning/roninversion.h"


namespace SHARED
{
	//-----------------------------------------------------------------------------
	// Purpose: Returns SDK Version as a string
	//-----------------------------------------------------------------------------
	template<ScriptContext context>
	SQRESULT GetSdkVersion(HSquirrelVM* sqvm)
	{
		g_pSQManager<context>->PushString(sqvm, RONIN_VERSION, strlen(RONIN_VERSION));
		return SQRESULT_NOTNULL;
	}

	//-----------------------------------------------------------------------------
	// Purpose: Returns passed string as an asset
	//-----------------------------------------------------------------------------
	template<ScriptContext context>
	SQRESULT StringToAsset(HSquirrelVM* sqvm)
	{
		g_pSQManager<context>->PushAsset(sqvm, g_pSQManager<context>->GetString(sqvm, 1), -1);
		return SQRESULT_NOTNULL;
	}

	//-----------------------------------------------------------------------------
	// Purpose: Prints the location of an entity in memory
	//-----------------------------------------------------------------------------
	template<ScriptContext context>
	SQRESULT PrintEntityAddress(HSquirrelVM* sqvm)
	{
		CMemory player = CMemory(g_pSQManager<context>->GetEntity<void>(sqvm, 1));

		DevMsg(eDLL_T::RONIN_GEN, "%p", g_pSQManager<context>->GetEntity<void>(sqvm, 1));
		return SQRESULT_NOTNULL;
	}
}
namespace SERVER
{
}
namespace CLIENT
{
}
namespace UI
{
}