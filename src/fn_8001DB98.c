// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001DB98-0x8001DBC0 (40B). Byte-identical.
#include "types.h"

extern char lbl_80362AA8[];
extern s32 lbl_80362A94;
extern char lbl_803627E4[];

s32 fn_8001DB98(void) {
    return *(s32 *)&lbl_80362AA8 - ((s32 *)&lbl_803627E4)[lbl_80362A94];
}
