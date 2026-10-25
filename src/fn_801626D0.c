// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801626D0-0x80162838 (360B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8005C338(void *, void *, void *, void *, void *, void *, void *, void *);
s32 fn_8005C5BC(void *);
s32 fn_8005C5F0(void *);
s32 fn_8005CF80(void *, void *);
s32 GetInteger(void *, void *, void *, void *);
s32 GetChecksum_2(void *, void *, void *, void *);
extern void * lbl_80366474;
bool ScriptAdjustTextureRegion(s32 arg0) {
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    s32 sp18;
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 temp_r3;

    GetChecksum_2(arg0, 0, &sp8, 0);
    temp_r3 = fn_8005CF80(lbl_80366474, sp8);
    if (temp_r3 != 0) {
        spC = 0;
        sp10 = 0;
        sp14 = fn_8005C5BC(temp_r3);
        sp18 = fn_8005C5F0(temp_r3);
        sp1C = 0;
        sp20 = 0;
        sp24 = 0;
        GetInteger(arg0, QB_XPOS, &spC, 0);
        GetInteger(arg0, QB_YPOS, &sp10, 0);
        GetInteger(arg0, QB_WIDTH, &sp14, 0);
        GetInteger(arg0, QB_HEIGHT, &sp18, 0);
        GetInteger(arg0, QB_SPLIT_AXIS, &sp1C, 0);
        GetInteger(arg0, QB_START_POINT, &sp20, 0);
        GetInteger(arg0, QB_END_POINT, &sp24, 0);
        fn_8005C338(temp_r3, ((Unk_B0EC4F37 *)&spC)->unk0x2, ((Unk_B0EC4F37 *)&sp10)->unk0x2, ((Unk_B0EC4F37 *)&sp14)->unk0x2, ((Unk_B0EC4F37 *)&sp18)->unk0x2, sp1C, ((Unk_B0EC4F37 *)&sp20)->unk0x2, ((Unk_B0EC4F37 *)&sp24)->unk0x2);
    }
    return true;
}
