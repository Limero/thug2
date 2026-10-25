// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B0EF8-0x801B0F68 (112B). Byte-identical.
#include "types.h"
#include "structs.h"

extern s32 fn_80009950(s32);
extern void *fn_801B092C(Unk_C8FEE62D *);

void fn_801B0EF8(CStruct *arg0, s32 arg1) {
    s32 sz;
    s32 temp_r29;
    s32 count;
    s32 var_r30;
    s32 var_r31;

    count = arg1;
    arg0->unk0x4 = count;
    sz = (count << 5) | 8;
    var_r31 = count - 1;
    temp_r29 = fn_80009950(sz) + 8;
    *(s32 *)((char *)temp_r29 - (s32)0x8) = count;
    var_r30 = temp_r29;
    if (count != 0) {
        do {
            fn_801B092C(var_r30);
            var_r30 += 0x20;
        } while (--var_r31 != -1);
    }
    arg0->unk0xC = temp_r29;
}
