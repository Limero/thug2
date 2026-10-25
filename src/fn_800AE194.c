// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800AE194-0x800AE234 (160B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern f32 lbl_8029861C;
void fn_800AB990(void);
s32 fn_8011CA60(void);
void fn_8011CA94(f32);
void fn_800ADE30(void *, s32, s32);

void fn_800AE194(Unk_4A70D538 *arg0, Unk_FFAD6788 *arg1, s32 arg2) {
    if (arg0->unk0x34B8 != 0) {
        fn_800AB990();
        if (arg0->unk0x3460 == 0) {
            if (fn_8011CA60() != 0) {
                fn_8011CA94(lbl_8029861C);
                arg0->unk0x3460 = 1;
                fn_800ADE30(arg0, arg1, arg2);
            }
        } else {
            fn_800ADE30(arg0, arg1, arg2);
        }
    } else {
        arg0->unk0x3460 = 1;
        fn_800ADE30(arg0, arg1, arg2);
    }
}
