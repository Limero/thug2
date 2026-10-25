// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80240650-0x802406A4 (84B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void *GetStructure(s32, s32);
void GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_80240650(s32 arg0) {
    s32 sp8;
    void *temp_r3;
    temp_r3 = GetStructure(QB_DMA_USAGE, 1);
    sp8 = 1;
    GetInteger(temp_r3, arg0, &sp8, 0);
    return sp8;
}
