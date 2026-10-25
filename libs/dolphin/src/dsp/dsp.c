#include <dolphin/dolphin.h>
#include <dolphin/dsp.h>
#include <dolphin/hw_regs.h>

#include "__dsp.h"

const char* __DSPVersion = "<< Dolphin SDK - DSP\trelease build: Sep  5 2002 05:35:13 (0x2301) >>";

static BOOL __DSP_init_flag;

u32 DSPCheckMailToDSP(void) {
    return (__DSPRegs[0] >> 0xF) & 1;
}

u32 DSPCheckMailFromDSP(void) {
    return (__DSPRegs[2] >> 0xF) & 1;
}

u32 DSPReadMailFromDSP(void) {
    u16 reg1;
    u16 reg2;

    reg1 = __DSPRegs[2];
    reg2 = __DSPRegs[3];
    return reg1 << 16 | reg2;
}

void DSPSendMailToDSP(u32 mail) {
    __DSPRegs[0] = mail >> 16;
    __DSPRegs[1] = mail;
}

void DSPInit(void) {
    u32 oldInt;
    u16 reg;

    __DSP_debug_printf("DSPInit(): Build Date: %s %s\n", "Sep  5 2002", "05:35:13");

    if (__DSP_init_flag == 1) {
        return;
    }

    OSRegisterVersion(__DSPVersion);

    oldInt = OSDisableInterrupts();
    __OSSetInterruptHandler(7, __DSPHandler);
    __OSUnmaskInterrupts(0x1000000);

    reg = __DSPRegs[5];
    reg = (reg & ~0xA8) | 0x800;
    __DSPRegs[5] = reg;

    reg = __DSPRegs[5];
    reg = reg & ~0xAC;
    __DSPRegs[5] = reg;

    __DSP_tmp_task = 0;
    __DSP_curr_task = 0;
    __DSP_last_task = 0;
    __DSP_first_task = 0;
    __DSP_init_flag = 1;
    OSRestoreInterrupts(oldInt);
}

BOOL DSPCheckInit(void) {
    return __DSP_init_flag;
}

DECL_WEAK DSPTaskInfo* DSPAddTask(DSPTaskInfo* task) {
    u32 oldInt;

    oldInt = OSDisableInterrupts();
    __DSP_insert_task(task);
    task->state = 0;
    task->flags = 1;
    OSRestoreInterrupts(oldInt);

    if (task == __DSP_first_task) {
        __DSP_boot_task(task);
    }

    return task;
}

DSPTaskInfo* DSPCancelTask(DSPTaskInfo* task) {
    BOOL old;

    old = OSDisableInterrupts();
    task->flags |= 2;
    OSRestoreInterrupts(old);
    return task;
}

DSPTaskInfo* DSPAssertTask(DSPTaskInfo* task) {
    s32 old;

    old = OSDisableInterrupts();

    if (__DSP_curr_task == task) {
        __DSP_rude_task = task;
        __DSP_rude_task_pending = 1;
        OSRestoreInterrupts(old);
        return task;
    }

    if (task->priority < __DSP_curr_task->priority) {
        __DSP_rude_task = task;
        __DSP_rude_task_pending = 1;

        if (__DSP_curr_task->state == 1) {
            u32 enabled;

            enabled = OSDisableInterrupts();

            __DSPRegs[5] = (__DSPRegs[5] & ~0xA8) | 2;

            OSRestoreInterrupts(enabled);
        }

        OSRestoreInterrupts(old);
        return task;
    }

    OSRestoreInterrupts(old);
    return NULL;
}
