// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80249898-0x8024994C (180B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -msdata=eabi -G4
// QB-keyed object builder: resolves a 0x118-byte block via the lbl_803CA320
// factory, seeds it from arg0 (fn_80249A00/fn_80249B70), and conditionally
// computes + validates the unk0x114 field (fn_8024EA14/74) with a release
// path through fn_8024EA94/fn_80249A10 on failure.
// Suggested rename: fn_80249898_build_object_from_key.
#include "types.h"
#include "structs.h"
extern void fn_80249A00(s32, s32, s32);
extern s32 (*lbl_803CA320)(s32);
extern s32 fn_8024C104(void *);
extern s32 fn_80249B70(Unk_5B449B03 *, Unk_5B449B03 *);
extern s32 fn_8024EA14(s32, s32, s32);
extern s32 fn_8024EA74(s32, s32, s32, s32);
extern void fn_8024EA94(s32);
extern void fn_80249A10(Unk_5B449B03 *, s32);

void *fn_80249898(Unk_DB0E2BAB *arg0) {
    Unk_31DE137E *var_r30;
    s32 temp_r3;

    fn_80249A00(arg0->unk0xC, arg0->unk0x10, arg0->unk0x14);
    var_r30 = (void *)fn_8024C104(lbl_803CA320(0x118));
    fn_80249B70(var_r30, arg0);
    if (arg0->unk0x8 & 4) {
        temp_r3 = fn_8024EA14(arg0->unk0xC, arg0->unk0x10, arg0->unk0x18);
        var_r30->unk0x114 = temp_r3;
        if (fn_8024EA74(temp_r3, arg0->unk0x20, arg0->unk0x24, arg0->unk0x1C) == 0) {
            fn_8024EA94(var_r30->unk0x114);
            if (var_r30 != NULL) {
                fn_80249A10(var_r30, 3);
            }
            var_r30 = NULL;
        }
    }
    return var_r30;
}
