// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80015310-0x800153C4 (180B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern bool lbl_802FFF68;
void fn_800151F4(s32 *, s32 *, s32 *);
typedef struct E15310 {
    s32 a;
    s32 b;
    s32 key;
} E15310;
void *fn_80015310(s32 dummy, s32 *arg1) {
    s32 spC;
    s32 sp8;
    s32 *var_r4;
    E15310 *var_r3;
    u32 var_r9;
    if (lbl_802FFF68 != 0) {
        return NULL;
    }
    fn_800151F4(dummy, &sp8, &spC);
    var_r4 = arg1;
    while (*var_r4 != -1) {
        if (var_r4[1] == sp8) {
            var_r9 = 0U;
            var_r3 = (E15310 *)var_r4[2];
            while (var_r9 < (u32)var_r4[0]) {
                if (var_r3->key == spC) {
                    return var_r3;
                }
                var_r9 += 1;
                var_r3 += 1;
            }
        }
        var_r4 += 3;
    }
    return NULL;
}
