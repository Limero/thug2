// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80162838-0x801628FC (196B). Byte-identical.
#include "types.h"
extern void * lbl_80366474;
#include "qb_constants.h"
#include "structs.h"
s32 fn_8005C36C(void *, void *, void *, void *);
s32 fn_8005CF80(void *, void *);
s32 GetInteger(void *, void *, void *, void *);
s32 GetChecksum_2(void *, void *, void *, void *);
bool ScriptPullTextureToEdge(s32 arg0) {
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
        sp14 = 0;
        GetInteger(arg0, QB_POINT, &spC, 0);
        GetInteger(arg0, QB_AXIS, &sp10, 0);
        GetInteger(arg0, QB_NUM_PIXELS, &sp14, 0);
        fn_8005C36C(temp_r3, ((Unk_B0EC4F37 *)&spC)->unk0x2, sp10, sp14);
    }
    return true;
}
