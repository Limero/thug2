// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F4D6C-0x801F4DC8 (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_801F4C88(void *, void *, void *);
#include "structs.h"
s32 fn_801F1940(s32, s32);
void fn_801F4D6C(Unk_5FCDF30E *arg0) {
    s32 var_r30;
    s32 ret;

    var_r30 = 0;
    while (var_r30 < *(u8 *)((char *)arg0 + (s32)0x2BA)) {
        ret = fn_801F1940(arg0->unk0x2C0, var_r30);
        fn_801F4C88(arg0, var_r30, ret);
        var_r30 += 1;
    }
}
