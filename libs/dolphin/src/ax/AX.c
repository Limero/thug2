#include <dolphin/dolphin.h>
#include <dolphin/ax.h>

#include "__ax.h"

const char* __AXVersion = "<< Dolphin SDK - AX\trelease build: Mar 11 2003 11:19:39 (0x2301) >>";

void AXInit(void)
{
    OSRegisterVersion(__AXVersion);

    __AXAllocInit();
    __AXVPBInit();
    __AXSPBInit();
    __AXAuxInit();
    __AXClInit();
    __AXOutInit();
}

void AXQuit(void)
{
    __AXAllocQuit();
    __AXVPBQuit();
    __AXSPBQuit();
    __AXAuxQuit();
    __AXClQuit();
    __AXOutQuit();
}
