// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016F120-0x8016F668 (1352B). Byte-identical.
#include "types.h"
extern f32 lbl_802A8C88;
extern f32 lbl_802A8C8C;
extern f32 lbl_802A8C90;
extern f32 lbl_802A8C94;
#include "qb_constants.h"
#include "structs.h"
extern s32 GetInteger(s32, u32, void *, s32);
extern s32 GetFloat(s32, u32, void *, s32);
extern s32 GetArray(s32, u32, void *, s32);
extern s32 fn_801293FC(s32, s32);
void fn_8016F120(s32 arg0, s32 arg1, Unk_DB0E2BAB *arg2) {
    f32 sp8;
    f32 defv;
    f32 *sp8p;
    s32 spC;
    u32 sp10;
    s32 sp14;
    u32 sp18;
    s32 var_r29;
    s32 var_r30;
    s32 var_r31;
    s32 var_zero;
    register s32 a1 __asm__("r28");
    register f32 *sp8p30 __asm__("r30");

    a1 = arg1;
    sp8p30 = &sp8;
    GetInteger(a1, QB_LEV_RED, (char *)arg2 + 0x28, 0);
    GetInteger(a1, QB_LEV_GREEN, (char *)arg2 + 0x2C, 0);
    GetInteger(a1, QB_LEV_BLUE, (char *)arg2 + 0x30, 0);
    GetInteger(a1, QB_SKY_RED, (char *)arg2 + 0x34, 0);
    GetInteger(a1, QB_SKY_GREEN, (char *)arg2 + 0x38, 0);
    GetInteger(a1, QB_SKY_BLUE, (char *)arg2 + 0x3C, 0);
    GetInteger(a1, QB_FOG_RED, (char *)arg2 + 0x44, 0);
    GetInteger(a1, QB_FOG_GREEN, (char *)arg2 + 0x48, 0);
    GetInteger(a1, QB_FOG_BLUE, (char *)arg2 + 0x4C, 0);
    GetInteger(a1, QB_FOG_ALPHA, (char *)arg2 + 0x50, 0);
    GetInteger(a1, QB_FOG_DIST, (char *)arg2 + 0x54, 0);
    GetInteger(a1, QB_AMBIENT_RED, (char *)arg2 + 0x58, 0);
    GetInteger(a1, QB_AMBIENT_GREEN, (char *)arg2 + 0x5C, 0);
    GetInteger(a1, QB_AMBIENT_BLUE, (char *)arg2 + 0x60, 0);
    GetFloat(a1, QB_AMBIENT_MOD_FACTOR_LO, (char *)arg2 + 0x64, 0);
    GetFloat(a1, QB_AMBIENT_MOD_FACTOR_HI, (char *)arg2 + 0x68, 0);
    GetFloat(a1, QB_HEADING_0, (char *)arg2 + 0x6C, 0);
    GetFloat(a1, QB_PITCH_0, (char *)arg2 + 0x70, 0);
    GetInteger(a1, QB_RED_0, (char *)arg2 + 0x74, 0);
    GetInteger(a1, QB_GREEN_0, (char *)arg2 + 0x78, 0);
    GetInteger(a1, QB_BLUE_0, (char *)arg2 + 0x7C, 0);
    GetFloat(a1, QB_MOD_FACTOR_0_LO, (char *)arg2 + 0x80, 0);
    GetFloat(a1, QB_MOD_FACTOR_0_HI, (char *)arg2 + 0x84, 0);
    GetFloat(a1, QB_HEADING_1, (char *)arg2 + 0x88, 0);
    GetFloat(a1, QB_PITCH_1, (char *)arg2 + 0x8C, 0);
    GetInteger(a1, QB_RED_1, (char *)arg2 + 0x90, 0);
    GetInteger(a1, QB_GREEN_1, (char *)arg2 + 0x94, 0);
    GetInteger(a1, QB_BLUE_1, (char *)arg2 + 0x98, 0);
    GetFloat(a1, QB_MOD_FACTOR_1_LO, (char *)arg2 + 0x9C, 0);
    GetFloat(a1, QB_MOD_FACTOR_1_HI, (char *)arg2 + 0xA0, 0);
    sp8 = lbl_802A8C88;
    if (GetFloat(a1, QB_SUN_THETA, sp8p30, 0) != 0) {
        *((f32 *)&arg2->unk0x14) = (sp8 * lbl_802A8C8C) / lbl_802A8C90;
    }
    if (GetFloat(a1, QB_SUN_PHI, sp8p30, 0) != 0) {
        *((f32 *)&arg2->unk0x18) = (sp8 * lbl_802A8C8C) / lbl_802A8C90;
    }
    defv = lbl_802A8C94;
    *((f32 *)&arg2->unk0x1C) = defv;
    *((f32 *)&arg2->unk0x24) = defv;
    *((f32 *)&arg2->unk0x20) = defv;
    if (GetFloat(a1, QB_SUN_RED, sp8p30, 0) != 0) {
        *((f32 *)&arg2->unk0x1C) = sp8;
    }
    if (GetFloat(a1, QB_SUN_GREEN, sp8p30, 0) != 0) {
        *((f32 *)&arg2->unk0x24) = sp8;
    }
    if (GetFloat(a1, QB_SUN_BLUE, sp8p30, 0) != 0) {
        *((f32 *)&arg2->unk0x20) = sp8;
    }
    GetInteger(a1, QB_BLOOM_ON, arg2, 0);
    if (arg2->unk0x0 != 0) {
        GetInteger(a1, QB_BLOOM1, (char *)arg2 + 4, 0);
        var_zero = 0;
        GetInteger(a1, QB_BLOOM2, (char *)arg2 + 8, 0);
        spC = var_zero;
        if (GetArray(a1, QB_BLOOM_STRENGTH, &spC, 0) != 0) {
            var_r29 = fn_801293FC(spC, 0);
            var_r30 = fn_801293FC(spC, 1);
            var_r31 = fn_801293FC(spC, 2);
            *(u8 *)&sp10 = var_r29;
            ((Unk_E01B0030 *)&sp10)->unk0x1 = var_r30;
            ((Unk_E01B0030 *)&sp10)->unk0x2 = var_r31;
            ((Unk_E01B0030 *)&sp10)->unk0x3 = var_zero;
            arg2->unk0xC = sp10;
        }
        sp14 = var_zero;
        if (GetArray(a1, QB_BLOOM_COLOR, &sp14, 0) != 0) {
            var_r30 = fn_801293FC(sp14, 0);
            var_r29 = fn_801293FC(sp14, 1);
            var_r31 = fn_801293FC(sp14, 2);
            *(u8 *)&sp18 = var_r30;
            ((Unk_E01B0030 *)&sp18)->unk0x1 = var_r29;
            ((Unk_E01B0030 *)&sp18)->unk0x2 = var_r31;
            ((Unk_E01B0030 *)&sp18)->unk0x3 = var_zero;
            arg2->unk0x10 = sp18;
        }
    }
}
