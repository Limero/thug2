// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F3170-0x801F33B4 (580B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern char lbl_802AE328[];

extern void fn_801F203C(Unk_5FCDF30E *);
extern s32 fn_801F16A0(CStruct *);
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern void fn_801F4858(Unk_CD19EEE4 *, s32);
extern s32 GetString(CStruct *, s32 *, s32 *, s32);
extern void strcpy(void *, void *);
extern s32 GetArray(CStruct *, s32, s32 *, s32);
extern s32 fn_80129528(CStruct *, s32);
extern void GetVector(CStruct *, s32, CStruct *, s32);
extern s32 GetFloat(CStruct *, s32, f32 *, s32);
extern void fn_801F4128(Unk_4D38C000 *, CStruct *);

void fn_801F3170(Unk_127FDB99 *arg0, CStruct *arg1) {
    s32 sp8;
    void *spC;
    s32 zero;
    u32 var_r26;
    s32 count;
    void *entry;
    char *w1;
    char *w2;
    char *w3;

    zero = 0;
    fn_801F203C(arg0);
    arg0->unk0x2BD = zero;
    arg0->unk0x2BE = 1;
    arg0->unk0x0 = fn_801F16A0(arg1);
    GetInteger(arg1, QB_LEVEL_GOAL_INDEX, (char *)arg0 + 0x2C0, 0);
    GetChecksum_2(arg1, QB_GOAL_TYPE, (char *)arg0 + 0x114, 0);
    fn_801F4858(arg0, arg0->unk0x114);
    GetInteger(arg1, QB_SCORE, (char *)arg0 + 0x2CC, 0);
    GetInteger(arg1, QB_TIME_LIMIT, (char *)arg0 + 0x2C4, 0);
    GetChecksum_2(arg1, QB_CONTROL_TYPE, (char *)arg0 + 0x2C8, 0);
    sp8 = (s32)lbl_802AE328;
    GetString(arg1, QB_VIEW_GOALS_TEXT, &sp8, 0);
    strcpy((char *)arg0 + 4, sp8);
    sp8 = (s32)lbl_802AE328;
    GetString(arg1, QB_GOAL_DESCRIPTION, &sp8, 0);
    strcpy((char *)arg0 + 0x4B, sp8);
    sp8 = (s32)lbl_802AE328;
    GetString(arg1, QB_WIN_MESSAGE, &sp8, 0);
    strcpy((char *)arg0 + 0xAF, sp8);
    sp8 = (s32)lbl_802AE328;
    GetString(arg1, QB_PED_NAME, &sp8, 0);
    strcpy((char *)arg0 + 0x36, sp8);
    spC = NULL;
    if (GetArray(arg1, QB_NODE_POSITIONS, &spC, 0) != 0) {
        count = ((CStruct *)spC)->unk0x4;
        arg0->unk0x2BA = count;
        var_r26 = 0;
        if ((u32)var_r26 < arg0->unk0x2BA) {
            w3 = (char *)arg0 + 0x134;
            w2 = (char *)arg0 + 0x130;
            w1 = (char *)arg0 + 0x120;
            do {
                entry = fn_80129528(spC, var_r26++);
                GetVector(entry, QB_POS, w1, 0);
                w1 += 0x20;
                GetFloat(entry, QB_HEIGHT, w2, 0);
                w2 += 0x20;
                GetFloat(entry, QB_ANGLE, w3, 0);
                w3 += 0x20;
            } while ((u32)var_r26 < arg0->unk0x2BA);
        }
    }
    fn_801F4128(arg0, arg1);
}
