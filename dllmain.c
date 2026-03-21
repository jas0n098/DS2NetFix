#include <windows.h>
#include <stdio.h>

#include "MinHook.h"

void (*fpCheck)(bool *netState);

void detour_check(bool *netState)
{
    fpCheck(netState);
    Sleep(250);
}

void InitASI()
{
    HMODULE modBase = GetModuleHandle(NULL);

    if (MH_Initialize() != MH_OK)
    {
        MessageBox(NULL, "Failed to initialize MinHook!\n", "DS2NetFix", MB_ICONERROR);
        return;
    }

    if (MH_CreateHook((void *)modBase + 0xfcd50, &detour_check, 
        (void *)&fpCheck) != MH_OK)
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
