// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80077428-0x80077498 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void *Mem_Alloc2(s32 arg0);
void *fn_80077BAC(void *arg0);
void *fn_8009B5D8(void *arg0);
s32 fn_8009B9D4(s32, CStruct *, s32, s32, s32);
void *fn_80077428(CStruct *arg0, s32 arg1, s32 arg2, s32 arg3) {
    Unk_C7387A53 *temp_r30;
    void *temp_r0;

    temp_r30 = (Unk_C7387A53 *)fn_80077BAC(Mem_Alloc2(0x10));
    temp_r0 = fn_8009B5D8(Mem_Alloc2(0x1C));
    temp_r30->unk0xC = (s32)temp_r0;
    fn_8009B9D4((s32)temp_r0, arg0, arg1, arg2, arg3);
    return temp_r30;
}
