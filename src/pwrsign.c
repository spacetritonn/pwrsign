#include "pwrsign.h"

void wmain(void)
{
    int argc = 0;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);

    POWER_ACTION pwra = 0;
    SYSTEM_POWER_STATE sps = 0;
    BOOLEAN async = 0;
    ParseArguments(argc, argv, &pwra, &sps, &async);
    if (pwra == 0 || sps == 0) goto exit;

    HMODULE ntdll = LoadLibraryW(L"ntdll.dll");
    fRtlAdjustPrivilege RtlAdjustPrivilege = (fRtlAdjustPrivilege)GetProcAddress(ntdll, "RtlAdjustPrivilege");
    fNtInitiatePowerAction NtInitiatePowerAction = (fNtInitiatePowerAction)GetProcAddress(ntdll, "NtInitiatePowerAction");
    if (RtlAdjustPrivilege != NULL || NtInitiatePowerAction != NULL)
    {
        PrintW(L"[+] ntdll.dll loaded to process, functions retrieved.\n");
    }
    else
    {
        PrintW(L"[!] Failed to retrieve functions from ntdll.dll\n");
        goto exit;
    }

    BOOLEAN dum = 0;
    if (NT_SUCCESS(RtlAdjustPrivilege(19, TRUE, FALSE, &dum)))
    {
        PrintW(L"[+] Shutdown privilege retrieved.\n");
    }
    else
    {
        PrintW(L"[!] Failed to retrieve shutdown privilege.");
        goto exit;
    }
    if (NT_SUCCESS(NtInitiatePowerAction(pwra, sps, POWER_ACTION_CRITICAL, async)))
    {
        PrintW(L"[+] Power state transition signal sent to device.\n");
    }
    else
    {
        PrintW(L"[!] Failed to send power state transition signal to device.");
    }

    exit:
    LocalFree(argv);
    if (ntdll != NULL) FreeLibrary(ntdll);
    ExitProcess(0);
}