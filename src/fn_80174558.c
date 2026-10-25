// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80174558-0x801745B4 (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_801746A4(s32);
s32 GetChecksum_3(s32, s32);
s32 fn_800DEB04(Unk_31DE137E *, s32);
s32 fn_80174558(s32 arg0, s32 arg1, Unk_31DE137E *arg2) {
    char *base;
    s32 var_r3;
    register s32 off __asm__("r0");

    base = (char *)arg0 + 0x3A4;
    off = arg1 * 0x10;
    *(s32 *)(base + off) = (s32)arg2;
    var_r3 = fn_801746A4(arg0);
    if (var_r3 != 0) {
        var_r3 = GetChecksum_3(var_r3, QB_VIBRATION);
        if (var_r3 != 0) {
            var_r3 = fn_800DEB04((Unk_31DE137E *)var_r3, (s32)arg2);
        }
    }
    return var_r3;
}
