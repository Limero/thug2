// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F2F58-0x801F3170 (536B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef struct Unk_8B4F0B1C {
    f32 unk0x0;
    f32 unk0x4;
    f32 unk0x8;
    s32 unk0xC;
    f32 unk0x10;
    f32 unk0x14;
    s32 unk0x18;
    s32 unk0x1C;
} Unk_8B4F0B1C;

s32 fn_8003E7CC(s32);
s32 fn_80128F94(Unk_5AA7B5D7 *);
void fn_80129068(Unk_5AA7B5D7 *, s32, s32);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void fn_80129314(CStruct *, s32, s32);
void AddArrayPointer(CStruct *, s32, s32);
void AddChecksum(CStruct *, s32, s32);
void AddInteger(CStruct *, s32, s32);
void AddString(CStruct *, s32, void *);
void fn_8012772C(CStruct *, s32, f32);
void fn_8012788C(CStruct *, s32, f32, f32, f32);
s32 fn_801F1940(s32, s32);
s32 fn_801F2184(Unk_5FCDF30E *);
void fn_801F3D30(Unk_5FCDF30E *, CStruct *, s32);

void fn_801F2F58(Unk_5FCDF30E *arg0, CStruct *arg1) {
    u8 *base;
    Unk_8B4F0B1C *node;
    Unk_5AA7B5D7 *temp_r26;
    CStruct *temp_r30;
    u32 i;
    u32 temp_r4;

    base = (u8 *)arg0;
    AddChecksum(arg1, 0, QB_EDITED_GOAL);
    AddChecksum(arg1, QB_LEVEL, arg0->unk0x0);
    AddInteger(arg1, QB_LEVEL_GOAL_INDEX, arg0->unk0x2C0);
    AddChecksum(arg1, QB_GOAL_ID, fn_801F2184(arg0));
    AddInteger(arg1, QB_TIME_LIMIT, arg0->unk0x2C4);
    AddInteger(arg1, QB_WON_GOAL, base[0x2BD]);
    AddChecksum(arg1, QB_CONTROL_TYPE, arg0->unk0x2C8);
    AddString(arg1, QB_VIEW_GOALS_TEXT, base + 4);
    AddString(arg1, QB_GOAL_DESCRIPTION, base + 0x4B);
    AddString(arg1, QB_WIN_MESSAGE, base + 0xAF);
    AddString(arg1, QB_PED_NAME, base + 0x36);
    AddChecksum(arg1, QB_GOAL_TYPE, arg0->unk0x114);
    AddChecksum(arg1, QB_PRO_NAME, fn_801F1940(arg0->unk0x2C0, 0));
    fn_801F3D30(arg0, arg1, 0);
    if ((s32)base[0x2BA] != 0) {
        i = 0;
        temp_r26 = fn_80128F94(fn_8003E7CC(0xC));
        fn_80129068(temp_r26, base[0x2BA], 0xA);
        if (i < (u32)base[0x2BA]) {
            node = (Unk_8B4F0B1C *)(base + 0x120);
            do {
                temp_r30 = CStruct_ctor(CStruct_new(8));
                fn_8012788C(temp_r30, QB_POS, node->unk0x0, node->unk0x4, node->unk0x8);
                fn_8012772C(temp_r30, QB_HEIGHT, node->unk0x10);
                fn_8012772C(temp_r30, QB_ANGLE, node->unk0x14);
                node++;
                temp_r4 = i;
                i += 1;
                fn_80129314(temp_r26, temp_r4, temp_r30);
            } while (i < (u32)base[0x2BA]);
        }
        AddArrayPointer(arg1, QB_NODE_POSITIONS, temp_r26);
    }
}
