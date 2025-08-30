#pragma once
#include "pwrsign.h"

BOOL PrintW(_In_ LPCWSTR lpbuf);
void PrintHelp(void);
void PrintPwrInfo(void);
void ParseArguments(_In_ int pargc, _In_ LPWSTR* pargv, _Out_ PPOWER_ACTION pwra, _Out_ PSYSTEM_POWER_STATE sps, _Out_ PBOOLEAN async);