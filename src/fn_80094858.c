// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80094858-0x800948AC (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Object init: fn_8009A484(arg0, 1), then unk0x10 = lbl_80297298,
// unk0x18 = 0, unk0x38 = lbl_80297268. Returns arg0.
// Suggested rename: InitWithLabelAndValue
#include "types.h"
#include "structs.h"
extern f32 lbl_80297268;
extern void fn_8009A484(void *, s32);
extern char lbl_80297298[];
void *fn_80094858(Unk_C8FEE62D *arg0) {
    fn_8009A484(arg0, 1);
    arg0->unk0x10 = (s32)lbl_80297298;
    arg0->unk0x18 = 0;
    *((f32 *)&arg0->unk0x38) = lbl_80297268;
    return arg0;
}