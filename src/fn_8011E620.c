// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011E620-0x8011E6C4 (164B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8029D600[];
extern s32 fn_8001371C(Unk_C8FEE62D * arg0, s32 arg1, s32 arg2);
extern s32 fn_800132A4(CStruct * arg0);
extern s32 fn_800132F8(Unk_DB0E2BAB * arg0, void *arg1, s32 arg2, s32 arg3);
extern void fn_80013788(s32 arg0);
bool fn_8011E620(CStruct *arg0, s32 arg1) {
    s32 sp8[64];
    s32 h;
    s32 sz;

    sprintf(sp8, lbl_8029D600, arg1);
    if ((h = fn_8001371C(sp8, 1, 0x64)) != 0) {
        sz = fn_800132A4(h);
        arg0->unk0x4 = sz;
        if (sz > 0xFFF) {
            fn_80013788(h);
        } else {
            fn_800132F8(h, (char *)arg0 + 8, 1, sz);
            fn_80013788(h);
            *(s32 *)arg0 = arg1;
            return true;
        }
    }
    return false;
}
