// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016158C-0x80161608 (124B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305F9C;
s32 GetInteger(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
s32 fn_8021D358(s32, u16);

s32 ScriptPlacedLessThan(CStruct *arg0, Unk_FFAD6788 *arg1) {
    s32 sp8;
    s32 ctx;
    Unk_EE36B018 *temp_r9;
    Unk_C7387A53 *node;

    ctx = lbl_80305F9C;
    GetInteger(arg0, 0, &sp8, 0);
    temp_r9 = *((void * *)&arg1->unk0xBC);
    if (temp_r9 != NULL) {
        node = (void *)fn_8021D358(ctx, temp_r9->unk0x1A);
        if (node != NULL) {
            return node->unk0x38 < sp8;
        }
    }
    return 0;
}
