// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800534DC-0x8005352C (80B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80053460(Unk_DB0E2BAB *, s32);
extern char lbl_80364620[];
void fn_800534DC(s32 arg0, s32 arg1) {
    s32 var_ctr;

    if ((arg1 == 0xFFFF) && (arg0 != 0)) {
        fn_80053460(lbl_80364620, 8);
        var_ctr = 0x40;
        do {
            var_ctr -= 1;
        } while (var_ctr != 0);
    }
}
