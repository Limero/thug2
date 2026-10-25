// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80125568-0x801255B8 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_80125A9C(s32);
CStruct *fn_80125388(void);
void fn_80125548(void);
void *fn_80125568(s32 arg0) {
    CStruct *temp_r3;
    s32 flags;

    fn_80125A9C(0x14);
    temp_r3 = fn_80125388();
    flags = temp_r3->unk0x0;
    temp_r3->unk0x4 = arg0;
    temp_r3->unk0x0 = flags | 0x800000;
    fn_80125548();
    return temp_r3;
}
