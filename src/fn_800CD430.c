// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CD430-0x800CD480 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80302C34;
s32 fn_8011B9F4(Unk_DB0E2BAB *, s32, CStruct *, Unk_FFAD6788 *, s32, s32);
s32 fn_800CD430(Unk_FFAD6788 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 farg0, f32 farg1, f32 farg2) {
    struct unk {
        f32 unk0;
        f32 unk4;
        f32 unk8;
        s32 unkC;
    } sp8;
    s32 tbl;

    tbl = *(s32 *)&lbl_80302C34;
    sp8.unkC = arg2;
    sp8.unk4 = farg0;
    sp8.unk0 = farg1;
    sp8.unk8 = farg2;
    return fn_8011B9F4(tbl, arg1, &sp8, arg0, arg3, arg4);
}
