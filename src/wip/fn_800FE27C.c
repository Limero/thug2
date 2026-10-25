// WIP draft - PARKED. See notes below.
// family=m2c range=0x800FE27C-0x800FE36C size=240B
// PARKED (90.0% masked match, 54/60 words): single-instruction scheduling
// slide — GCC will not hoist `cmpwi r27,0` above the field-copy window.
// WANT interleaves it at 0x800FE304 (right after the t-load); every source
// shape pins it after the stores at 0x800FE318. Tried: register-var pins
// r9/r10/r11/r0, "+r" staging barriers, memory-clobber barriers,
// -fno-schedule-insns/-insns2/-sched-spec/-sched-interblock/-fno-expensive-
// optimizations/-fcse variants, if/else-if vs nested-else, tail-block-first
// order (regressed to 48% via global regalloc shift), volatile vs plain
// t-load. All other 59 bytes match exactly. Doc-15-family compare-hoist
// coin-flip.
#include "structs.h"
extern void *fn_80103A50(Unk_87891B5F *, s32, s32);
extern void *Mem_Alloc2(s32);
extern void *fn_800FF93C(Unk_C7387A53 *);
extern void *fn_800FE130(Unk_C7387A53 *);
extern void fn_800FFE40(Unk_377B7C81 *, void *);

void fn_800FFE40(Unk_377B7C81 *, void *);

void *fn_800FE27C(CStruct *arg0, void *arg1) {
    volatile double _dummy;
    void *var_r29;
    CStruct *var_r31;
    Unk_5B449B03 *var_r28;
    void *var_r27;

    if (arg1 != NULL) {
        var_r29 = *((void * *)&arg0->unk0x8);
    } else {
        var_r29 = fn_80103A50(*((void * *)&arg0->unk0x8), 0, 1);
    }
    if (var_r29 == NULL) {
        return NULL;
    }
    var_r28 = NULL;
    var_r27 = NULL;
    if (arg1 != NULL) {
        var_r31 = fn_800FF93C(Mem_Alloc2(0xC0));
        var_r27 = var_r31;
    } else {
        var_r31 = fn_800FE130(Mem_Alloc2(0x10));
        var_r28 = var_r31;
    }
    {
        register void *t __asm__("r11");
        register void *c __asm__("r10");
        register void *a __asm__("r0");
        register void *b __asm__("r9");
        t = *((void * volatile *)&var_r31->unk0xC);
        __asm__ volatile("" : "+r"(t));
        c = *((void * *)&arg0->unk0x8);
        __asm__ volatile("" : "+r"(c));
        a = *((void * *)&arg0->unk0x0);
        b = *((void * *)&arg0->unk0x4);
        __asm__ volatile("" : "+r"(a));
        __asm__ volatile("" : "+r"(b));
        __asm__ volatile("stw %0, 0x08(%%r1)" : : "r"(t) : "memory");
        *((void * *)&var_r31->unk0x0) = a;
        *((void * *)&var_r31->unk0x4) = b;
        *((void * *)&var_r31->unk0x8) = c;
        *((void * *)&var_r31->unk0xC) = t;
    }
    if (var_r27 != NULL) {
        fn_800FFE40(var_r27, var_r29);
    } else if (var_r28 != NULL) {
        u16 h = var_r28->unk0x4;
        *((void * *)&var_r28->unk0x8) = var_r29;
        var_r28->unk0x4 = h | 0x8000;
    }
    return var_r31;
}
// 2026-10-22: 91.7% (was 90.0%): both `b` loads hoisted above the `+r` barriers.
