#include "pwrsign.h"

LPCWSTR param1[] = {L"slp", L"hib", L"shut", L"shutres", L"shutoff"};
LPCWSTR param2[] = {L"wrkst", L"slp1st", L"slp2st", L"slp3st", L"hibst", L"shutst"};
LPCWSTR param3[] = {L"sync", L"async"};
LPCWSTR pwrst[] = {L"Sleep state S1:", L"Sleep state S2:", L"Sleep state S3:", L"Hybrid sleep state S4:", L"Hibernation state S4:", L"Shutdown state S5:"};

BOOL PrintW(_In_ LPCWSTR lpbuf)
{
    return WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), lpbuf, lstrlenW(lpbuf), NULL, NULL);
}

void PrintHelp(void)
{
    WCHAR whelp[384];
    RtlZeroMemory(whelp, _countof(whelp));
    lstrcatW(whelp, L"pwrsign helper\r\npwrsign.exe param1, param2, param3\r\n\r\nparam1:\r\npwrinfo\r\n");

    for (int i = 0; i < _countof(param1); i++)
    {
        lstrcatW(whelp, param1[i]);
        lstrcatW(whelp, L"*\r\n");
    }

    lstrcatW(whelp, L"\r\nparam2:\r\n");
    for (int i = 0; i < _countof(param2); i++)
    {
        lstrcatW(whelp, param2[i]);
        lstrcatW(whelp, L"*\r\n");
    }

    lstrcatW(whelp, L"\r\nparam3:\r\n");
    for (int i = 0; i < _countof(param3); i++)
    {
        lstrcatW(whelp, param3[i]);
        lstrcatW(whelp, L"\r\n");
    }

    lstrcatW(whelp, L"\r\n* symbol indicate both paramters (param1 and param2) must be passed!\r\nexample:\r\npwrsign.exe slp slp1st sync\r\n");
    PrintW(whelp);
}

void PrintPwrInfo(void)
{
    HMODULE ntdll = LoadLibraryW(L"ntdll.dll");
    fNtPowerInformation NtPowerInformation = (fNtPowerInformation)GetProcAddress(ntdll, "NtPowerInformation");

    if (NtPowerInformation != NULL)
    {
        PrintW(L"[+] ntdll.dll loaded to process, functions retrieved.\n");
    }
    else
    {
        PrintW(L"[!] Failed to retrieve functions from ntdll.dll.");
        goto exit;
    }

    SYSTEM_POWER_CAPABILITIES spc;
    if (NT_SUCCESS(NtPowerInformation(SystemPowerCapabilities, NULL, 0, &spc, sizeof(SYSTEM_POWER_CAPABILITIES))))
    {
        PrintW(L"[+] Power information retrieved.\n");
    }
    else
    {
        PrintW(L"[!] Failed to retrieve power information.");
        goto exit;
    }

    WCHAR wspc[192];
    RtlZeroMemory(wspc, _countof(wspc));
    BOOLEAN tempspc[6] = {spc.SystemS1, spc.SystemS2, spc.SystemS3, spc.FastSystemS4, spc.SystemS4, spc.SystemS5};
    for (int i = 0; i < _countof(pwrst); i++)
    {
        lstrcatW(wspc, pwrst[i]);
        lstrcatW(wspc, (tempspc[i] == FALSE ? L"Not supported\r\n" : L"Supported\r\n"));
    }
    PrintW(wspc);

    exit:
    if (ntdll != NULL) FreeLibrary(ntdll);
    return;
}

void ParseArguments(_In_ int pargc, _In_ LPWSTR* pargv, _Out_ PPOWER_ACTION pwra, _Out_ PSYSTEM_POWER_STATE sps, _Out_ PBOOLEAN async)
{
    if (pargc > 1 && pargc <= 4)
    {
        if (lstrcmpiW(pargv[1], L"pwrinfo") == 0)
        {
            PrintPwrInfo();
            return;
        }

        for (int i = 0; i < _countof(param1); i++)
        {
            if (lstrcmpiW(pargv[1], param1[i]) == 0)
            {
                *pwra = (2 + i);
                break;
            }
        }

        for (int i = 0; i < _countof(param2); i++)
        {
            if (lstrcmpiW(pargv[2], param2[i]) == 0)
            {
                *sps = (1 + i);
                break;
            }
        }

    }

    if (pargc == 4)
    {
        for (int i = 0; i < _countof(param3); i++)
        {
            if (lstrcmpiW(pargv[3], param3[i]) == 0)
            {
                *async = i;
                break;
            }
        }
    }

    if (*pwra == 0 || *sps == 0)
    {
        PrintHelp();
    }
}