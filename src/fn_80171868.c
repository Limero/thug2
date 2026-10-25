// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80171868-0x801718DC (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "types.h"
void fn_80170930(void *, void *);
void fn_8016F120(void *, void *, void *);
#include "qb_constants.h"
#include "structs.h"
s32 fn_8012543C(s32);
void fn_80171868(Unk_E9D95610 *arg0, s32 arg1) {
    s32 var_r30;
    void *temp_r5;
    void *var_r31;

    arg0->unk0x354 = 1;
    var_r31 = (char *)arg0 + 0xC;
    *(s32 *)(fn_8012543C(QB_TODMANAGER_TEMP_TOD_CHANGED) + 0xC) = 1;
    var_r30 = 2;
    do {
        temp_r5 = var_r31;
        fn_8016F120(arg0, arg1, temp_r5);
        var_r31 += 0x190;
        var_r30 -= 1;
    } while (var_r30 != 0);
    fn_80170930(arg0, 1);
}