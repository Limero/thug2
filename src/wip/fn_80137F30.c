// PARKED 2026-10-21: 95.74% (2 of 47 words), size-exact 188B, flagless.
// Residual: at 0x80137F54 the scheduler emits `mr r6,r8` (the arg5 home copy)
// where retail has `mr r28,r7` (the arg4 spill); the two are swapped around the
// spA halfword store. Both are single-instruction moves with no dependencies
// between them, so this is a sched1 ready-list tie (doc-15 class). Measured
// inert/no-gain: a5 assignment moved before/after the zero stores or into the
// if-condition, explicit arg4 local (pinned r28 and plain), -fno-sched-spec /
// -fno-sched-interblock / -fno-delayed-branch / -Os / -fno-expensive-optimizations
// (all 2 diffs), -fno-schedule-insns2 (8), -fno-schedule-insns / -O1 (27+).
//
// The store/compare order that used to be the residual is FIXED and is not a
// delay-slot decision: retail's `cmpwi r5,0 ; stw r0,0x10(r31) ; beq` needs the
// +0x10 store written BEFORE the +0x4 store in source (ngccc emits the zero
// stores in reverse statement order), which also drops the asm barriers that
// earlier drafts needed. The shape was recovered from the matched sibling
// src/fn_80137E30.c, which is the same function with +0xC instead of +0x10.
//
// Identity: 0x14-byte descriptor fill from (name byte, u16 length, data ptr,
// flag byte, aux ptr). Clears +0x4/+0x10, optionally converts through
// fn_80137CF8, allocates (u16)length, copies, frees the converted buffer, then
// stores name/length/flags.
#include "types.h"
#include "mem.h"
void *memcpy(void *, const void *, s32);
s32 fn_80137CF8(u8 *, s16 *, s32, s32);
typedef struct {
    u8 unk0x0;
    u8 pad0x1;
    u16 unk0x2;
    s32 unk0x4;
    u8 unk0x8;
    char pad0x9[3];
    s32 unk0xC;
    s32 unk0x10;
} Unk_7F30;
void *fn_80137F30(Unk_7F30 *arg0, u8 arg1, s16 arg2, s32 arg3, s8 arg4, s32 arg5) {
    s16 spA;
    u8 sp8;
    s32 var_r29;
    s32 var_r30;
    void *p;
    register s32 a5 __asm__("r6");

    var_r30 = arg3;
    sp8 = arg1;
    spA = arg2;
    a5 = arg5;
    arg0->unk0x10 = 0;
    arg0->unk0x4 = 0;
    if (arg2 == 0) {
        goto end;
    }
    var_r29 = 0;
    if (a5 != 0) {
        var_r29 = fn_80137CF8(&sp8, &spA, var_r30, a5);
        if (var_r29 != 0) {
            var_r30 = var_r29;
        }
    }
    p = Mem_Alloc((u16) spA);
    arg0->unk0x4 = (s32) p;
    memcpy(p, (void *) var_r30, (u16) spA);
    if (var_r29 != 0) {
        Mem_Free2((void *) var_r29);
    }
end:
    arg0->unk0x0 = sp8;
    arg0->unk0x2 = (u16) spA;
    arg0->unk0x8 = arg4;
    return arg0;
}
