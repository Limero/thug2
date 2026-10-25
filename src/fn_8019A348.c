// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019A348-0x8019A3A4 (92B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_800091F4(CStruct *);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void *fn_8019A348(CStruct *arg0) {
    s32 var_r30;
    s32 var_r31;

    var_r30 = 7;
    var_r31 = (s32)arg0 + 0xC;
    do {
        fn_800091F4((void *)var_r31);
        var_r31 += 0x24;
    } while (--var_r30 != -1);
    arg0->unk0x4 = CStruct_ctor(CStruct_new(8));
    return arg0;
}
