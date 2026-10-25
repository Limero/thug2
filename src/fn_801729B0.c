// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801729B0-0x80172A18 (104B). Byte-identical.
#include "types.h"
extern char lbl_80305EAC[];
extern s32 lbl_80305EB0;
s32 fn_800099AC(s32, s32, s32);
s32 fn_801740D8(void);
s32 fn_801729B0(s32 arg0) {
    if (((s32) *(s32 *)&lbl_80305EAC == 0) && (arg0 != 0)) {
        fn_800099AC(0x448, 0, 1);
        *(s32 *)&lbl_80305EAC = fn_801740D8();
    }
    lbl_80305EB0 += 1;
    return *(s32 *)&lbl_80305EAC;
}
