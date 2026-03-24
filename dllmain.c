#include <windows.h>
#include <stdio.h>
#include <psapi.h>

#include "MinHook.h"
#include "mem.h"

void (*fpCheck)(bool *netState);

void detour_check(bool *netState)
{
    fpCheck(netState);
    Sleep(250);
}

void InitASI()
{
    HMODULE modBase = GetModuleHandle(NULL);
    MODULEINFO modInfo;
    GetModuleInformation(GetCurrentProcess(), modBase, &modInfo, sizeof(modInfo));

    void *netcheck = Scan("\x48\x89\x5c\x24\x10\x48\x89\x6c\x24\x18\x48\x89\x74\x24\x20\x57\x48\x83\xec\x30\x65\x48\x8b\x04\x25\x58\x00\x00\x00",
                          "xxxxxxxxxxxxxxxxxxxxxxxxxxx", (void *)modBase, modInfo.SizeOfImage);

    if (MH_Initialize() != MH_OK)
    {
        MessageBox(NULL, "Failed to initialize MinHook!\n", "DS2NetFix", MB_ICONERROR);
        return;
    }

    if (MH_CreateHook(netcheck, &detour_check, (void *)&fpCheck) != MH_OK)
    {
        MessageBox(NULL, "Failed to create hook!\n", "DS2NetFix", MB_ICONERROR);
        return;
    }

    if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
    {
        MessageBox(NULL, "Failed to enable hook!\n", "DS2NetFix", MB_ICONERROR);
        return;
    }
}

static LONG InitCount = 0;
__declspec(dllexport) void InitializeASI()
{
    if ( _InterlockedCompareExchange( &InitCount, 1, 0 ) != 0 ) return;
    InitASI();
}
