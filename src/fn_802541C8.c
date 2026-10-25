// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802541C8-0x802542EC (292B). Byte-identical.
#include "types.h"
#include "structs.h"

extern s32 fn_80257E48(CStruct * arg0, s32 arg1);
extern void fn_80253FF4(Unk_31DE137E * arg0);

s32 fn_802541C8(Unk_DB0E2BAB *arg0, CStruct *arg1) {
    register s32 var_r3 __asm__("r3");
    CStruct *temp_r28;
    s32 temp_r3;
    s32 temp_r9;

    var_r3 = -0x81;
    temp_r28 = *((void * *)&arg0->unk0x1C);
    if (temp_r28 == NULL) {
        return var_r3;
    }
    temp_r3 = fn_80257E48(arg1, 0x20);
    arg0->unk0x0 = temp_r3;
    var_r3 = -0x86;
    if (temp_r3 != 0) {
        return var_r3;
    }
    arg0->unk0x4 = fn_80257E48(arg1, 8);
    arg0->unk0x8 = fn_80257E48(arg1, 0x20);
    arg0->unk0xC = fn_80257E48(arg1, 0x20);
    arg0->unk0x10 = fn_80257E48(arg1, 0x20);
    arg0->unk0x14 = fn_80257E48(arg1, 0x20);
    temp_r28->unk0x0 = 1 << fn_80257E48(arg1, 4);
    temp_r9 = 1 << fn_80257E48(arg1, 4);
    temp_r28->unk0x4 = temp_r9;
    if ((arg0->unk0x8 <= 0) ||
        (arg0->unk0x4 <= 0) ||
        (temp_r28->unk0x0 <= 7) ||
        (temp_r9 < temp_r28->unk0x0)) {
        goto fail;
    }
    if (fn_80257E48(arg1, 1) == 1) {
        var_r3 = 0;
    } else {
fail:
        fn_80253FF4(arg0);
        var_r3 = -0x85;
    }
    return var_r3;
}
