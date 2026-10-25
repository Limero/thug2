// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F5898-0x801F59CC (308B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"

typedef struct {
    s32 unk0x0;
    char _pad1[0x2BE - 0x04];
    u8 unk0x2BE;
    char _pad2[0x2C0 - 0x2BF];
    s32 unk0x2C0;
} S5898_node;

typedef struct {
    char _pad0[0xAC00];
    s32 unk0xAC00;
} S5898_obj;

s32 GetChecksum_2(s32, s32, s32, s32);
s32 GetString(s32, s32, s32, s32);
s32 GetInteger(void *, s32, s32 *, s32);
s32 fn_801F16E8(void);
void *fn_801F5808(void *, s32);
void *fn_801F576C(void *, void *);

void *fn_801F5898(S5898_obj *arg0, void *arg1) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 temp_r8;
    s32 var_ctr;
    s32 var_r11;
    s32 var_r3;
    S5898_node *var_r9;

    sp8 = 0;
    temp_r3 = GetChecksum_2((s32)arg1, QB_GOAL_ID, &sp8, 0);
    if (temp_r3 != 0) {
        return fn_801F5808(arg0, sp8);
    }
    spC = temp_r3;
    temp_r3_2 = GetString((s32)arg1, QB_GOAL_NAME, &spC, 0);
    if (temp_r3_2 != 0) {
        return fn_801F576C(arg0, spC);
    }
    sp10 = temp_r3_2;
    if (GetInteger(arg1, QB_GOAL_INDEX, &sp10, 0) != 0) {
        temp_r8 = fn_801F16E8();
        var_ctr = 0x32;
        var_r9 = (S5898_node *)((char *)arg0 + 0x20);
        var_r3 = 0;
        do {
            var_r11 = 1;
            if (var_r9->unk0x2BE == 0) {
                var_r11 = 0;
            }
            if (var_r11 != 0) {
                if (var_r9->unk0x0 == temp_r8) {
                    if (var_r9->unk0x2C0 == sp10) {
                        return (char *)arg0 + (var_r3 + 0x20);
                    }
                }
            }
            var_r9 = (S5898_node *)((char *)var_r9 + 0x370);
            var_r3 += 0x370;
            var_ctr -= 1;
        } while (var_ctr != 0);
        return 0;
    }
    return (void *)arg0->unk0xAC00;
}
