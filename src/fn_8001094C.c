// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001094C-0x800109AC (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "qb_constants.h"
void fn_800107A0(void *, s32, s32);
void *Mem_Alloc(s32);
extern char lbl_802905F8[];
void *fn_8001094C(void *arg0, s32 arg1) {
    void *temp_r3;

    *(s32 *)((char *)arg0 + 0x18) = (s32)lbl_802905F8;
    if (arg1 != 0) {
        arg1 = arg1 & QB_UNKNOWN_0xFFFFFFF0;
        temp_r3 = Mem_Alloc(arg1);
        *(s32 *)((char *)arg0 + 4) = (s32)temp_r3;
        fn_800107A0(arg0, (s32)temp_r3, (s32)temp_r3 + arg1);
    }
    return arg0;
}
