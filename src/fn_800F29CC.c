// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F29CC-0x800F2A48 (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern s32 fn_800F2A48(Unk_C7387A53 *, s32, Unk_C7387A53 *);
extern void fn_800F2334(Unk_C7387A53 *, Unk_C7387A53 *);

s32 fn_800F29CC(Unk_C7387A53 *arg0, s32 arg1, s32 arg2, Unk_C7387A53 *arg3) {
    Unk_C7387A53 *temp_r3;
    Unk_C7387A53 *temp_r9;
    s32 var_r3;
    s32 res;

    temp_r3 = (Unk_C7387A53 *)fn_800F2A48(arg0, arg1, arg3);
    if (temp_r3 == NULL) {
        goto fail;
    }
    fn_800F2334(arg0, temp_r3);
    temp_r9 = (Unk_C7387A53 *)temp_r3->unk0x50;
    res = ((s32 (*)(void *, void *))temp_r9->unk0x44)((char *)temp_r3 + *(s16 *)&temp_r9->unk0x40, (void *)arg2);
    var_r3 = 1;
    if (res == 0) {
        var_r3 = 0;
    }
    return var_r3;
fail:
    return 0;
}
