// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000B58C-0x8000B5F8 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
//
// Identification: maps a platform index read from lbl_802FFE50 to a
// short console-name string: 1-3 -> "ps2", 4 -> "xbx", 5 -> "ngc",
// 6 -> "xen", anything else -> "???". Suggested rename: GetPlatformString.
#include "types.h"
extern char lbl_802FFE50[];
extern char lbl_80290190[];
extern char lbl_80290194[];
extern char lbl_80290198[];
extern char lbl_8029019C[];
extern char lbl_802901A0[];
char *fn_8000B58C(void) {
    switch (*(s32 *)&lbl_802FFE50) {
    case 1:
    case 2:
    case 3:
        return lbl_80290190;
    case 4:
        return lbl_80290194;
    case 5:
        return lbl_80290198;
    case 6:
        return lbl_8029019C;
    default:
        return lbl_802901A0;
    }
}
