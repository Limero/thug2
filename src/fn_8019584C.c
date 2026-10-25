// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019584C-0x8019591C (208B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void AddInteger(CStruct * arg0, s32 arg1, s32 arg2);
s32 GetInteger(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
s32 fn_8018C080(Unk_672A1C0D * arg0);

// PARKED 96.2%: single remaining diff pair is a post-call register-role
// swap on the *(arg+0x80) readback multiply — want [lwz r0,0x80(r31);
// lwz r9,0xc(r1)] vs got [lwz r0,0xc(r1); lwz r9,0x80(r31)]. ngccc
// invariant: spC's pseudo (born at the pre-call addi r5,r1,0xc) always
// reloads FIRST into r0; the field pseudo born post-call always lands
// r9. Tried: named-temp staging, "+r"/volatile asm barriers, block-scoped
// tC staging, variable reuse, inline-paren tree shapes ((a*b)*c vs a*(b*c)
// — GCC reassociates regardless), volatile reads, register-pin-to-r0
// (collapses other webs), and flags -fno-schedule-insns/-insns2/-sched-
// spec/-sched-interblock/-strength-reduce/gcse (both orders + pair).
// Store-run rotate-right fix applied separately (source order now
// [78,80,7C,84,74] -> emits want's [74,78,80,7C,84]). Doc-15/recipe-51
// family member.
void fn_8019584C(Unk_132A52FF *arg0) {
    s32 spC;
    s32 sp8;
    s32 temp_r0;

    *((s32 *)&arg0->unk0x78) = 0;
    arg0->unk0x80 = 0;
    *((s32 *)&arg0->unk0x7C) = 0;
    *((s32 *)&arg0->unk0x84) = 0;
    *((s32 *)&arg0->unk0x74) = 0;
    AddInteger(arg0->unk0x20, QB_TIME_ON_CAMERA, 0);
    if (GetInteger(arg0->unk0x20, QB_TOTAL_TIME_REQUIRED, &sp8, 0) != 0) {
        *((s32 *)&arg0->unk0x7C) = sp8 * 0x3E8;
        GetInteger(arg0->unk0x20, QB_TIME, &spC, 1);
        temp_r0 = arg0->unk0x80 * 0x3E8;
        arg0->unk0x80 = temp_r0 * spC;
    } else {
        GetInteger(arg0->unk0x20, QB_TOTAL_SHOTS_REQUIRED,
                    (char *)arg0 + (s32)0x84, 0);
    }
    fn_8018C080((s32)arg0);
}
