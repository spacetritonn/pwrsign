#pragma once
#include "pwrsign.h"

typedef NTSTATUS(NTAPI* fRtlAdjustPrivilege)(_In_ DWORD Privilege, _In_ BOOLEAN Enable, _In_ BOOLEAN CurrentThread, _Out_ PBOOLEAN Enabled);
typedef NTSTATUS(NTAPI* fNtPowerInformation)(_In_ POWER_INFORMATION_LEVEL InformationLevel, _In_reads_bytes_opt_(InputBufferLength) PVOID InputBuffer, _In_ DWORD InputBufferLength, _Out_writes_bytes_opt_(OutputBufferLength) PVOID OutputBuffer, _In_ DWORD OutputBufferLenght);
typedef NTSTATUS(NTAPI* fNtInitiatePowerAction)(_In_ POWER_ACTION SystemAction, _In_ SYSTEM_POWER_STATE LightestSystemState, _In_ DWORD Flags, _In_ BOOLEAN Asynchronous);
