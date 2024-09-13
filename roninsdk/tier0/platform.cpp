#include "core/stdafx.h"
#include "tier0/platform_internal.h"

//-----------------------------------------------------------------------------
// Purpose: gets the process up time in seconds
// Output : double
//-----------------------------------------------------------------------------
double Plat_FloatTime()
{
	return v_Plat_FloatTime();
}

//-----------------------------------------------------------------------------
// Purpose: gets the process up time in milliseconds
// Output : uint64_t
//-----------------------------------------------------------------------------
uint64_t Plat_MSTime()
{
	return v_Plat_MSTime();
}

//-----------------------------------------------------------------------------
// Purpose: gets the process up time ( !! INTERNAL ONLY !! DO NOT USE !! ).
// Output : const char*
//-----------------------------------------------------------------------------
const char* Plat_GetProcessUpTime()
{
	time_t rawtime;
	struct tm* timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, sizeof(buffer), "[%H:%M:%S] ", timeinfo);
	static std::string str(buffer);

	return str.c_str();
}

//-----------------------------------------------------------------------------
// Purpose: gets the process up time.
// Input  : *szBuf - 
//			nSize - 
//-----------------------------------------------------------------------------
void Plat_GetProcessUpTime(char* szBuf, size_t nSize)
{
	sprintf_s(szBuf, nSize, "[%.3f] ", v_Plat_FloatTime ? Plat_FloatTime() : 0.0);
}