// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011C97C-0x8011CA08 (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_8038A820[];
s32 fn_8011BC60(void);
s32 fn_8011BD7C(s32 arg0, s32 arg1);
s32 fn_80121250(f32 farg0, f32 farg1, f32 farg2);
s32 fn_8011C97C(s32 arg0, CStruct *arg1, f32 farg0, s32 arg2) {
    volatile double _dummy;
    char *entry;
    s32 temp_r3;

    if (fn_8011BC60() != 0) {
        return 0;
    }
    temp_r3 = fn_8011BD7C(arg0, 1);
    if (temp_r3 >= 0) {
        entry = lbl_8038A820;
        entry += 0x18;
        *(s32 *)(entry + temp_r3 * 0x74) = arg2;
        return fn_80121250(*(f32 *)arg1, *((f32 *)&arg1->unk0x4), farg0);
    }
    return 0;
}
