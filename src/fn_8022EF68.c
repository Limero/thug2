// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022EF68-0x8022F0D8 (368B). Byte-identical.
#include "types.h"
extern void* lbl_802FFE98;
extern s32 lbl_80301B40;
#include "qb_constants.h"
#include "structs.h"

void fn_8022EDDC(Unk_9994C3F5 *, Unk_DB0E2BAB *);
s32 fn_801FC0E0(void);
s32 fn_801FB358(Unk_C7387A53 *);
s32 fn_801F1FCC(void);
void fn_8022F1F0(Unk_C8FEE62D *, void *);
s32 fn_8022CBBC(CStruct *);
s32 fn_800F1F2C(Unk_A231C4C2 *, u32);
void fn_800F1E1C(void *, u32);
s32 fn_800F6430(Unk_31DE137E *, u32, s32);
void fn_8022F434(Unk_9994C3F5 *, CStruct *, s32 *);
void fn_8022F5B0(s32 *, CStruct *, s32 *);
s32 fn_801FB394(Unk_C7387A53 *, CStruct *, s32 *, u32);
void fn_8022F840(void *, s32, s32 *);
void fn_8022F3FC(s32 *);
void fn_801F1CE8(void *, s32 *, s32);
s32 fn_800F1C34(Unk_A231C4C2 *, u32, s32);
void fn_800F1B24(Unk_06D4670B *, s32);
void ScriptParseNodeArray(s32, s32);

void fn_8022EF68(s32 * arg0, void *arg1) {
    struct { s32 sp8; char pad[0x14]; s32 sp20[2]; } fr;
    s32 temp_r27;
    s32 temp_r28;
    s32 temp_r30;

    fn_8022EDDC(arg0, &fr.sp8);
    fr.sp8 += fn_801FB358((void *)fn_801FC0E0());
    fr.sp8 += fn_801F1FCC();
    fn_8022F1F0(arg0, arg1);
    fr.sp8 += fn_8022CBBC((s32)((char *)arg0 + 0x5C));
    temp_r27 = lbl_80301B40;
    if (fn_800F1F2C(temp_r27, QB_NODEARRAY) != 0) {
        fn_800F1E1C(temp_r27, QB_NODEARRAY);
    }
    temp_r28 = (s32)((char *)arg0 + 0x494);
    temp_r30 = fn_800F6430(temp_r28, QB_NODEARRAY, fr.sp8);
    fr.sp20[0] = 0;
    fn_8022F434(arg0, temp_r30, &fr.sp20[0]);
    fn_8022F5B0(arg0, temp_r30, &fr.sp20[0]);
    fn_801FB394(fn_801FC0E0(), temp_r30, &fr.sp20[0], 0x3D0901);
    fn_8022F840(arg0, temp_r30, &fr.sp20[0]);
    fn_8022F3FC(arg0);
    fn_801F1CE8(temp_r30, &fr.sp20[0], ((Unk_4216A3DD *)lbl_802FFE98)->unk0x118);
    fn_800F1C34(temp_r27, QB_NODEARRAY, 1);
    fn_800F1B24(temp_r27, temp_r28);
    ScriptParseNodeArray(0, 0);
    *(s32 *)arg0 |= 0x20;
}
