// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80023E94-0x80023F94 (256B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
//
// Identification: string-keyed settings getter — compares arg0 against the
// rodata names "buttonsngc", "dialog", "newtrickfont", "newtimerfont",
// "small", "testtitle" and returns the matching cached global
// (lbl_803CA280-294) or 0. Fix: strcmp args must be the rodata LABELS
// (lis+addi @ha/@l addressing) rather than literal s32 addresses (lis+ori).
// Suggested rename: GetFontSettingValue.
#include "types.h"
extern bool lbl_803CA280;
extern bool lbl_803CA284;
extern bool lbl_803CA288;
extern bool lbl_803CA28C;
extern bool lbl_803CA290;
extern bool lbl_803CA294;
extern char lbl_80291228[];
extern char lbl_80291234[];
extern char lbl_8029123C[];
extern char lbl_8029124C[];
extern char lbl_8029125C[];
extern char lbl_80291264[];
s32 fn_80023E94(s32 arg0) {
    if (strcmp(arg0, lbl_80291228) == 0) {
        return lbl_803CA280;
    }
    if (strcmp(arg0, lbl_80291234) == 0) {
        return lbl_803CA284;
    }
    if (strcmp(arg0, lbl_8029123C) == 0) {
        return lbl_803CA288;
    }
    if (strcmp(arg0, lbl_8029124C) == 0) {
        return lbl_803CA28C;
    }
    if (strcmp(arg0, lbl_8029125C) == 0) {
        return lbl_803CA290;
    }
    if (strcmp(arg0, lbl_80291264) == 0) {
        return lbl_803CA294;
    }
    return 0;
}
