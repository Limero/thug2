// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016D3D4-0x8016D470 (156B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern void CStruct_delete(CStruct * arg0, s32 arg1);
void fn_80171844(CStruct * arg0);
extern void fn_80172858(CStruct * arg0, s32 arg1);
void fn_8016D3D4(CStruct *arg0, s32 arg1) {
    s32 sp0_zero;
    s32 *var_r31;
    s32 var_r30;

    sp0_zero = 0;
    var_r31 = (s32 *)((char *)arg0 + (s32)0x154);
    var_r30 = 2;
    do {
        if ((s32)*var_r31 != 0) {
            CStruct_delete(*var_r31, 3);
        }
        *var_r31 = sp0_zero;
        var_r30 -= 1;
        var_r31 = (s32 *)((char *)var_r31 + (s32)0x190);
    } while (var_r30 != 0);
    if ((s32)arg0->unk0x8 != 0) {
        CStruct_delete(arg0->unk0x8, 3);
    }
    fn_80171844(arg0);
    if ((s32)arg0->unk0x4 != 0) {
        fn_80172858(arg0->unk0x4, 3);
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
