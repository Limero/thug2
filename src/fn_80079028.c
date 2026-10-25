// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80079028-0x8007904C (36B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Word-fill loop (memset-like): fills arg0 with the word at *arg2,
// stepping by arg1*4 bytes for arg3 iterations (mtctr/bdnz countdown).
// Suggested rename: fn_80079028_fill_words.
#include "types.h"
void fn_80079028(s32 *arg0, s32 arg1, s32 *arg2, s32 arg3) {
    s32 fill;
    s32 *var_r3;
    s32 var_ctr;

    fill = *arg2;
    var_r3 = arg0;
    var_ctr = arg3;
    if (var_ctr > 0) {
        do {
            *var_r3 = fill;
            var_r3 += arg1;
            var_ctr -= 1;
        } while (var_ctr != 0);
    }
}