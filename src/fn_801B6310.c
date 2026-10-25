// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B6310-0x801B65D8 (712B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
#include "dolphin/SN_PS.h"
s32 GetChecksum_2(s32, s32, s32 *, s32);
s32 fn_800F0F84(s32, s32);
void fn_801B301C(Unk_A9157FE7 *, s32, void *);
s32 fn_801B65D8(Unk_A9157FE7 *, s32);
void fn_801B6A60(Unk_A9157FE7 *);
void fn_801B6690(Unk_A9157FE7 *, void *);
void fn_801B668C(Unk_A9157FE7 *, void *);
void fn_801B67CC(Unk_A9157FE7 *, void *);
void fn_801B6310(Unk_A9157FE7 *arg0) {
    s32 sp18;
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 temp_r0;
    s32 temp_r3;
    s32 temp_r9;
    s32 temp_r10;
    s32 temp_r11;
    s32 temp_r28;
    s32 temp_r29;
    s32 temp_r30;
    s32 temp_r30_2;
    temp_r0 = arg0->unk0x24;
    temp_r28 = arg0->unk0x5C;
    temp_r9 = temp_r0 & QB_UNKNOWN_0xFFFFFFCF;
    temp_r29 = arg0->unk0x58;
    arg0->unk0x24 = temp_r9;
    if (temp_r0 & 8) {
        arg0->unk0x24 = temp_r9 | 0x10;
    }
    arg0->unk0x24 &= QB_UNKNOWN_0xFFFFF7FF;
    *(sn_ps *)((char *)arg0 + 0x68) = *(sn_ps *)((char *)arg0 + 0x78);
    *(sn_ps *)((char *)arg0 + 0x70) = *(sn_ps *)((char *)arg0 + 0x80);
    *(sn_ps *)((char *)arg0 + 0x78) = *(sn_ps *)((char *)arg0 + 0x88);
    *(sn_ps *)((char *)arg0 + 0x80) = *(sn_ps *)((char *)arg0 + 0x90);
    temp_r11 = arg0->unk0x5C;
    temp_r10 = arg0->unk0x60;
    arg0->unk0x58 = temp_r11;
    arg0->unk0x5C = temp_r10;
    if ((*(s32 *)&arg0->unk0x1C == 0) && (temp_r29 == temp_r10)) {
        fn_801B301C(arg0, QB_PED_WALKER_HIT_DEAD_END, 0);
    }
    arg0->unk0x24 &= QB_UNKNOWN_0xFFFFFFF7;
    temp_r30 = fn_800F0F84(arg0->unk0x5C, 1);
    arg0->unk0x24 &= QB_UNKNOWN_0xFFFF7FFF;
    if ((GetChecksum_2(temp_r30, QB_PEDTYPE, &sp8, 0) != 0) && (sp8 == QB_SKATE)) {
        GetChecksum_2(temp_r30, QB_SKATEACTION, &spC, 1);
        if (fn_801B65D8(arg0, arg0->unk0x5C) != 0) {
            arg0->unk0x24 |= 8;
        }
        if ((spC == QB_VERT_GRAB) || (spC == QB_JUMP)) {
            if ((GetChecksum_2(fn_800F0F84(arg0->unk0x58, 1), QB_SKATEACTION, &sp10, 1) != 0) && (sp10 != QB_GRIND)) {
                if (!(arg0->unk0x24 & 0x14)) {
                    arg0->unk0x24 |= 0x100;
                }
            }
        }
        if (spC == QB_VERT_LIP) {
            arg0->unk0x24 |= 0x8000;
        }
    }
    fn_801B6A60(arg0);
    if (fn_801B65D8(arg0, arg0->unk0x60) != 0) {
        arg0->unk0x24 |= 0x20;
    }
    temp_r30_2 = fn_800F0F84(temp_r29, 1);
    temp_r3 = fn_800F0F84(temp_r28, 1);
    fn_801B6690(arg0, temp_r3);
    /* RETAIL SHAPE (0x801B653C..0x801B6558): the SKATEACTION test short-circuits
       to the PEDTYPE block -- `beq B` on c1==0 -- and only `sp14 == VERT_GRAB`
       skips the rest (`beq TAIL`). The old `(c1 != 0) && (sp14 != VERT_GRAB) &&
       (c2 != 0)` chain instead sent c1==0 to the TAIL, a real control-flow
       difference (promote_wip caught it as the single wrong branch target at
       0x801B6540). An empty then-arm with the work in the else-arm is what
       emits retail's `beq BODY` / `beq TAIL` pair.) */
    if ((GetChecksum_2(temp_r30_2, QB_SKATEACTION, &sp14, 0) != 0) && (sp14 == QB_VERT_GRAB)) {
        /* retail: SKATEACTION run with a VERT_GRAB anim -> nothing to do */
    } else {
        if (GetChecksum_2(temp_r3, QB_PEDTYPE, &sp18, 0) != 0) {
            if (sp18 != QB_SKATE) {
                if (sp18 == QB_WALK) {
                    fn_801B668C(arg0, temp_r3);
                }
            } else {
                fn_801B67CC(arg0, temp_r3);
            }
        }
    }
    arg0->unk0x9C = 0;
    arg0->unk0x98 = 0;
}
