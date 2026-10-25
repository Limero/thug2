#include <dolphin/dolphin.h>
#include <dolphin/os.h>

#include "__os.h"

#define ENQUEUE_INFO_PRIO(info, queue)               \
    do {                                             \
        OSResetFunctionInfo* __prev;                 \
        OSResetFunctionInfo* __next;                 \
        for (__next = (queue)->head; __next          \
          && (__next->priority <= (info)->priority); \
                __next = __next->next) ;             \
                                                     \
        if (__next == 0) {                           \
            __prev = (queue)->tail;                  \
            if (__prev == 0) {                       \
                (queue)->head = (info);              \
            } else {                                 \
                __prev->next = (info);               \
            }                                        \
            (info)->prev = __prev;                   \
            (info)->next = 0;                        \
            (queue)->tail = (info);                  \
        } else {                                     \
            (info)->next = __next;                   \
            __prev = __next->prev;                   \
            __next->prev = (info);                   \
            (info)->prev = __prev;                   \
            if (__prev == 0) {                       \
                (queue)->head = (info);              \
            } else {                                 \
                __prev->next = (info);               \
            }                                        \
        }                                            \
    } while(0);

static OSResetFunctionQueue ResetFunctionQueue;

void OSRegisterResetFunction(OSResetFunctionInfo* info) {
    ASSERTLINE(208, info->func);
    ENQUEUE_INFO_PRIO(info, &ResetFunctionQueue);
}

static int __OSCallResetFunctions(BOOL final) {
    OSResetFunctionInfo* info;
    int err;

    err = 0;
    for (info = ResetFunctionQueue.head; info != 0 && err == 0; info = info->next) {
        err |= !info->func(final);
    }
    err |= !__OSSyncSram();
    if (err) {
        return 0;
    }
    return 1;
}

static asm void Reset(u32 resetCode) {
    nofralloc
    b L_000001BC
L_000001A0:
    mfspr r8, HID0
    ori r8, r8, 0x8
    mtspr HID0, r8
    isync
    sync
    nop
    b L_000001C0
L_000001BC:
    b L_000001DC
L_000001C0:
    mftb r5, 268
L_000001C4:
    mftb r6, 268
    subf r7, r5, r6
    cmplwi r7, 0x1124
    blt L_000001C4
    nop
    b L_000001E0
L_000001DC:
    b L_000001FC
L_000001E0:
    lis r8, 0xcc00
    ori r8, r8, 0x3000
    li r4, 0x3
    stw r4, 0x24(r8)
    stw r3, 0x24(r8)
    nop
    b L_00000200
L_000001FC:
    b L_00000208
L_00000200:
    nop
    b L_00000200
L_00000208:
    b L_000001A0
}

void __OSDoHotReset(u32 resetCode) {
    OSDisableInterrupts();
    __VIRegs[1] = 0;
    ICFlashInvalidate();
    Reset(resetCode * 8);
}

void OSResetSystem(int reset, u32 resetCode, BOOL forceMenu) {
    OSSram* sram;
    OSResetFunctionInfo* info;
    OSThread* thread;
    OSThread* next;
    BOOL disableRecalibration;
    u32 unk[4]; // dumb compiler frame padding (byte-exact 0x40 frame)

    OSDisableScheduler();
    __OSStopAudioSystem();

    if (reset == OS_RESET_SHUTDOWN) {
        disableRecalibration = __PADDisableRecalibration(TRUE);
    }

    do {} while (!__OSCallResetFunctions(FALSE));

    if (reset == OS_RESET_HOTRESET && forceMenu) {
        sram = __OSLockSram();
        sram->flags |= 0x40;
        __OSUnlockSram(TRUE);
        do {} while (!__OSSyncSram());
    }

    OSDisableInterrupts();
    __OSCallResetFunctions(TRUE);
    LCDisable();

    if (reset == OS_RESET_HOTRESET) {
        __OSDoHotReset(resetCode);
    } else if (reset == OS_RESET_RESTART) {
        for (thread = __OSActiveThreadQueue.head; thread; thread = next) {
            next = thread->linkActive.next;
            switch (thread->state) {
            case 1:
            case 4:
                OSCancelThread(thread);
                break;
            default:
                break;
            }
        }
        OSEnableScheduler();
        __OSReboot(resetCode, forceMenu);
    }

    for (thread = __OSActiveThreadQueue.head; thread; thread = next) {
        next = thread->linkActive.next;
        switch (thread->state) {
        case 1:
        case 4:
            OSCancelThread(thread);
            break;
        default:
            break;
        }
    }

    memset(OSPhysicalToCached(0x40), 0, 0xCC - 0x40);
    memset(OSPhysicalToCached(0xD4), 0, 0xE8 - 0xD4);
    memset(OSPhysicalToCached(0xF4), 0, 0xF8 - 0xF4);
    memset(OSPhysicalToCached(0x3000), 0, 0xC0);
    memset(OSPhysicalToCached(0x30C8), 0, 0xD4 - 0xC8);
    memset(OSPhysicalToCached(0x30E2), 0, 1);

    __PADDisableRecalibration(disableRecalibration);
}

u32 OSGetResetCode(void) {
    if (__gUnknown800030E2 != 0) {
        return 0x80000000;
    }
    return (__PIRegs[9] & ~7) >> 3;
}
