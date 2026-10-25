// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800542DC-0x80054388 (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_80293010[];
extern char lbl_80293014[];
extern char lbl_80293018[];
extern char lbl_80293024[];
s32 strstr(s32, s32);
s32 sprintf(s32, ...);
s32 fn_80009218(s32 arg0, s32 arg1);
s32 fn_800542DC(s32 arg0, s32 arg1, s32 arg2) {
    char sp8[0x200];

    if ((strstr(arg1, (s32)lbl_80293010) != 0)
        || (strstr(arg1, (s32)lbl_80293014) != 0)) {
        sprintf((s32)sp8, (s32)lbl_80293018, arg1);
    } else {
        sprintf((s32)sp8, (s32)lbl_80293024, arg1, arg1, arg2);
    }
    fn_80009218(arg0, (s32)sp8);
    return arg0;
}
