// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80119510-0x80119578 (104B). Byte-identical.
#include "types.h"
extern char lbl_80302C34[];
extern s32 lbl_80302C38;
s32 fn_800099AC(s32, s32, s32);
s32 fn_80119794(void);
s32 fn_80119510(s32 arg0) {
    if (((s32) *(s32 *)&lbl_80302C34 == 0) && (arg0 != 0)) {
        fn_800099AC(0xC, 0, 1);
        *(s32 *)&lbl_80302C34 = fn_80119794();
    }
    lbl_80302C38 += 1;
    return *(s32 *)&lbl_80302C34;
}
