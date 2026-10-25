// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CF4F0-0x801CF5AC (188B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetArray(CStruct *, s32, s32 *, s32);
extern f32 fn_80129420(Unk_5AA7B5D7 *, s32);
extern s32 Tmr_GetTime(void);
extern s32 GetFloat(CStruct *, s32, f32 *, s32);
extern s32 lbl_80303150;
bool fn_801CF4F0(Unk_C5855798 *arg0, CStruct *arg1) {
    void *sp8;
    s32 max;

    sp8 = NULL;
    GetArray(arg1, 0, &sp8, 0);
    max = ((CStruct *)sp8)->unk0x4;
    if (arg0->unk0x37C >= max) {
        arg0->unk0x37C = max - 1;
    }
    arg0->unk0x378 = fn_80129420(sp8, arg0->unk0x37C);
    if (arg0->unk0x37C == 0) {
        arg0->unk0x380 = lbl_80303150 + Tmr_GetTime();
    }
    arg0->unk0x37C = arg0->unk0x37C + 1;
    GetFloat(arg1, QB_DURATION, (char *)arg0 + 0x384, 0);
    return true;
}
