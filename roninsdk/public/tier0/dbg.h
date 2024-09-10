//========== Copyright (c) Valve Corporation, All rights reserved. ==========//
//
// Purpose:  
//
// $NoKeywords: $
//
//===========================================================================//
#ifndef DBG_H
#define DBG_H
#define AssertDbg assert
#define Verify( _exp ) ( _exp )
#include "tier0/dbgflag.h"

bool HushAsserts();
//-----------------------------------------------------------------------------
// Used by engine spew func
enum class SpewType_t
{
	SPEW_MESSAGE = 0,

	SPEW_WARNING,
	SPEW_ASSERT,
	SPEW_ERROR,
	SPEW_LOG,

	SPEW_TYPE_COUNT
};
//-----------------------------------------------------------------------------
enum class eDLL_T : int
{
	//-------------------------------------------------------------------------
	// Script enumerants
	//-------------------------------------------------------------------------
	SCRIPT_SERVER = -3,
	SCRIPT_CLIENT = -2,
	SCRIPT_UI = -1,

	//-------------------------------------------------------------------------
	// Native enumerants
	//-------------------------------------------------------------------------
	SERVER = 0, // server.dll                (GameDLL)
	CLIENT = 1, // client.dll                (GameDLL)
	UI = 2, // ui.dll                    (GameDLL)
	ENGINE = 3, // engine.dll                (Wrapper)
	FS = 4, // filesystem_stdio.dll      (FileSystem API)
	RTECH = 5, // rtech_game.dll            (RTech API)
	MS = 6, // materialsystem_dx11.dll   (MaterialSystem API)
	AUDIO = 7, // binkawin64/mileswin64.dll (AudioSystem API)
	VIDEO = 8, // bink2w64                  (VideoSystem API)
	NETCON = 9, // netconsole impl           (RCON wire)

	//-------------------------------------------------------------------------
	// Common enumerants
	//-------------------------------------------------------------------------
	RONIN_GEN = 10, // general         (No specific subsystem)
	RONIN_CKF = 11,  // no context
	NONE = 12
};
//-----------------------------------------------------------------------------
enum class LogType_t
{
	LOG_INFO = 0,
	LOG_NET,
	LOG_WARNING,
	LOG_ERROR,
	SQ_INFO,
	SQ_WARNING
};
//-----------------------------------------------------------------------------
enum class LogLevel_t
{
	LEVEL_DISK_ONLY = 0,
	LEVEL_CONSOLE, // Emit to console panels
	LEVEL_NOTIFY   // Emit to in-game mini console
};
//-----------------------------------------------------------------------------
static const char* sDLL_T[11] =
{
	"[NATIVE SV]",
	"[NATIVE CL]",
	"[NATIVE UI]",
	"[NATIVE EN]",
	"[NATIVE FS]",
	"[RSPN TECH]",
	"[MAT SYSTM]",
	"[MILES SND]",
	"[BINKVIDEO]",
	"[NATIVE EN]",
	""
};
//-----------------------------------------------------------------------------
constexpr const char s_DefaultAnsiColor[] = "\033[38;2;255;204;153m";
/*
	case eDLL_T::SERVER:
	case eDLL_T::CLIENT:
	case eDLL_T::UI:
	case eDLL_T::ENGINE:
	case eDLL_T::FS:
	case eDLL_T::RTECH:
	case eDLL_T::MS:
	case eDLL_T::AUDIO:
	case eDLL_T::VIDEO:
	case eDLL_T::RONIN_GEN:
*/

static const std::regex s_AnsiRowRegex("\\\033\\[.*?m");
extern std::mutex g_LogMutex;

//////////////////////////////////////////////////////////////////////////
// Legacy Logging System
//////////////////////////////////////////////////////////////////////////

void CoreMsgV(LogType_t logType, LogLevel_t logLevel, eDLL_T context, const char* pszLogger,
	const char* pszFormat, va_list args, const UINT exitCode = NO_ERROR);
void CoreMsg(LogType_t logType, LogLevel_t logLevel, eDLL_T context,
	const UINT exitCode, const char* pszLogger, const char* pszFormat, ...);

// These functions do not return.
PLATFORM_INTERFACE void DevMsg(eDLL_T context, const char* fmt, ...) FMTFUNCTION(2, 3);
#ifndef DEDICATED
PLATFORM_INTERFACE void NetMsg(LogType_t logType, eDLL_T context, const char* uptime, const char* fmt, ...) FMTFUNCTION(4, 5);
#endif // !DEDICATED
PLATFORM_INTERFACE void Warning(eDLL_T context, const char* fmt, ...) FMTFUNCTION(2, 3);
PLATFORM_INTERFACE void Error(eDLL_T context, const UINT code, const char* fmt, ...) FMTFUNCTION(3, 4);

// You can use this macro like a runtime assert macro.
// If the condition fails, then Error is called with the message. This macro is called
// like AssertMsg, where msg must be enclosed in parenthesis:
//
// ErrorIfNot( bCondition, ("a b c %d %d %d", 1, 2, 3) );
#define ErrorIfNot( condition, msg ) \
	if ( (condition) )		\
		;					\
	else 					\
	{						\
		Error msg;			\
	}

//-----------------------------------------------------------------------------
// Templates to assist in validating pointers:

// Have to use these stubs so we don't have to include windows.h here.
/*PLATFORM_INTERFACE*/ void _AssertValidReadPtr(void* ptr, int count = 1);
/*PLATFORM_INTERFACE*/ void _AssertValidWritePtr(void* ptr, int count = 1);
/*PLATFORM_INTERFACE*/ void _AssertValidReadWritePtr(void* ptr, int count = 1);
/*PLATFORM_INTERFACE*/ void _AssertValidStringPtr(const TCHAR* ptr, int maxchar);

#ifdef DBGFLAG_ASSERT
inline void AssertValidStringPtr(const TCHAR* ptr, int maxchar = 0xFFFFFF) { _AssertValidStringPtr(ptr, maxchar); }
template<class T> inline void AssertValidReadPtr(T* ptr, int count = 1) { _AssertValidReadPtr((void*)ptr, count); }
template<class T> inline void AssertValidWritePtr(T* ptr, int count = 1) { _AssertValidWritePtr((void*)ptr, count); }
template<class T> inline void AssertValidReadWritePtr(T* ptr, int count = 1) { _AssertValidReadWritePtr((void*)ptr, count); }
#define AssertValidThis() AssertValidReadWritePtr(this,sizeof(*this))

#else

inline void AssertValidStringPtr(const TCHAR* /*ptr*/, int maxchar = 0xFFFFFF) { NOTE_UNUSED(maxchar); }
template<class T> inline void AssertValidReadPtr(T* /*ptr*/, int count = 1) { NOTE_UNUSED(count); }
template<class T> inline void AssertValidWritePtr(T* /*ptr*/, int count = 1) { NOTE_UNUSED(count); }
template<class T> inline void AssertValidReadWritePtr(T* /*ptr*/, int count = 1) { NOTE_UNUSED(count); }
#define AssertValidThis() 
#endif

#endif /* DBG_H */
