// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DA908-0x800DAA58 (336B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern f32 lbl_80299C6C;
extern char lbl_80299C58[];

s32 ContainsFlag(CStruct *, s32);
s32 Mem_NewZero(s32);
s32 fn_800A72E4(s32);
void fn_800A7324(s32, s32);
void fn_800A734C(s32);
s32 fn_80128A90(CStruct *, void *);
typedef struct { u32 a : 2; u32 b : 1; u32 c : 29; } DA908Bits;
Unk_C7387A53 *GetChecksum_3(s32, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);

void fn_800DA908(Unk_FD25FE4D *arg0, CStruct *arg1) {
    s32 spC;
    f32 sp8;
    s32 temp_r3;
    Unk_C7387A53 *temp_r3_2;

    temp_r3 = ContainsFlag(arg1, QB_OFF);
    if (temp_r3 != 0) {
        arg0->unk0x1C = (s32) (arg0->unk0x1C & QB_UNKNOWN_0xFFFFFDFF);
        if (arg0->unk0x208 != NULL) {
            fn_800A7324(arg0->unk0x208, 3);
            arg0->unk0x208 = NULL;
        }
    } else {
        arg0->unk0x20C = fn_80128A90(arg1, lbl_80299C58);
        arg0->unk0x1C = (s32) ((arg0->unk0x1C | 0x200) & QB_UNKNOWN_0xFFFFFFF7);
        temp_r3_2 = GetChecksum_3(*((s32 *)&arg0->unk0xC), QB_LOCKOBJ);
        ((DA908Bits *)&temp_r3_2->unk0x90)->b = temp_r3;
        if (arg0->unk0x208 == NULL) {
            arg0->unk0x208 = fn_800A72E4(Mem_NewZero(0x430));
        }
        fn_800A734C(arg0->unk0x208);
        sp8 = lbl_80299C6C;
        GetFloat(arg1, QB_DISTANCE, &sp8, 0);
        *(f32 *)(*(s32 *)((char *)((char *)arg0) + 0x208) + 0x428) = sp8;
        spC = temp_r3;
        GetChecksum_2(arg1, QB_NAME, &spC, 0);
        *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x208) + 0x410) = spC;
        if (ContainsFlag(arg1, QB_ORIENTY) != 0) {
            *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x208) + 0x42C) = 1;
        }
    }
}
