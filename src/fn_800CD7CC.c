// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CD7CC-0x800CD83C (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
s32 fn_80024660(void *);
s32 fn_800B0A08(s32, Unk_C7387A53 *, void *);
s32 fn_800CD7CC(CStruct *arg0, Unk_C7387A53 *arg1, void *arg2) {
    s32 var_r30;
    CStruct *var_r9;

    var_r30 = arg1->unk0x28;
    if ((var_r30 != 0) && (arg2 != 0)) {
        fn_800B0A08(arg0, var_r30, fn_80024660(arg2));
    } else {
        var_r9 = *((u32 *)&arg1->unk0xC);
        ((__ps_t *)arg0)[0] = ((__ps_t *)((char *)var_r9 + 0x58))[0];
        ((__ps_t *)arg0)[1] = ((__ps_t *)((char *)var_r9 + 0x58))[1];
    }
    return arg0;
}
