// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022E414-0x8022E5B4 (416B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
// WIP DRAFT (PARKED 2026-08-25) — 96.2% masked (100/104).
// Structure fully recovered & matched: 3-arg->void loop over arg1 array,
// chained stub call fn_80240C7C(fn_8022DC74(arg0)) (or.-fused test),
// u32 switch tree rooted at 0x28673697 w/ unsigned split, sp10 re-read
// from stack after the *(temp_r31+0x24) store (aliasing reload ✓).
// Remaining 2 diffs = doc-15 signature at site2 (GetChecksum_2 entry,
// 0xA1DC81F9): want [lis][stw spC][ORI r4-lo][MR r3,r30] vs got
// [lis][stw][MR][ORI] + spC reload lands in r0 vs want r4.
// Resisted: void/s32/u32/void*-first param protos, const-local hash,
// comma out-param init, "+r" barrier (adds copy), -fno-schedule-insns
// (-insns2 hurts), -fno-sched-spec, -fno-rerun-cse-after-loop,
// -fno-expensive-optimizations. Twin-site divergence: site3 wants
// mr-BEFORE-ori (matches naturally) while site2 wants ori-first —
// per-site expand_call artifact (§6v-121 class). Retry after any new
// doc-15 discovery.
extern s32 fn_80129528(CStruct *, s32);
extern void GetChecksum_2(CStruct *, u32, s32 *, s32);
extern s32 fn_8022DC74(Unk_C7387A53 *, s32);
extern s32 fn_80240C7C(s32);
extern s32 ContainsFlag(CStruct *, s32);

void fn_8022E414(Unk_C7387A53 *arg0, CStruct *arg1) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    u32 i;
    s32 entry;
    s32 t;
    Unk_DB0E2BAB *temp_r31;

    for (i = 0; (u32)i < *((u32 *)&arg1->unk0x4); i++) {
        entry = fn_80129528((s32)arg1, i);
        sp8 = 0;
        GetChecksum_2(entry, QB_CLASS, &sp8, 0);
        if ((u32)sp8 == QB_LEVELGEOMETRY || (u32)sp8 == QB_GAMEOBJECT) {
            spC = 0;
            GetChecksum_2(entry, QB_NAME, &spC, 0);
            if (spC != 0) {
                if ((t = fn_8022DC74(arg0, spC)) != 0) {
                    temp_r31 = fn_80240C7C(t);
                    if ((u32)sp8 == QB_GAMEOBJECT) {
                        *((u32 *)&temp_r31->unk0x4) |= 0x400;
                        if (ContainsFlag(entry, QB_ABSENTINNETGAMES) != 0) {
                            *((u32 *)&temp_r31->unk0x4) |= 0x800;
                        }
                    }
                    sp10 = 0;
                    GetChecksum_2(entry, QB_TRIGGERSCRIPT, &sp10, 0);
                    if (sp10 != 0) {
                        temp_r31->unk0x24 = sp10;
                        switch ((u32)sp10) {
                        case QB_SK6ED_CRATESCRIPT:
                        case QB_BO_CLASSIC_BARRELSCRIPT:
                        case QB_TRGP_ARCOWINDOWSCRIPT:
                        case QB_SK6ED_BAGLASSSCRIPT:
                            *((u32 *)&temp_r31->unk0x4) |= 0x4000;
                            break;
                        }
                    }
                }
            }
        }
    }
}
