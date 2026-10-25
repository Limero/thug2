// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A6848-0x801A68D0 (136B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_802AB888[];
extern s32 fn_801AF244(void * arg0);
extern s32 CStruct_new(s32 arg0);
extern s32 CStruct_ctor(s32 arg0);
extern void fn_801A6984(Unk_93C2DF4D * arg0, s32 arg1, s32 arg2);
void *fn_801A6848(Unk_1BB97F07 *arg0) {
    s32 var_zero;
    u32 var_r30;
    s32 *var_r31;

    arg0->unk0x6E8 = (s32)lbl_802AB888;
    var_r30 = 0U;
    var_zero = 0;
    var_r31 = (s32 *)((char *)arg0 + 0x690);
    do {
        var_r31[-21] = fn_801AF244(Mem_Alloc2(0x1C));
        var_r31[0] = var_zero;
        var_r31 += 1;
        var_r30 += 1;
    } while (var_r30 <= 20U);
    arg0->unk0x6E4 = CStruct_ctor(CStruct_new(8));
    fn_801A6984(arg0, 1, 0);
    return arg0;
}
