// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80119BF8-0x80119C38 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80300460;
extern char lbl_803009B0[];
s32 fn_80119BF8(CStruct *arg0) {
    s32 r;

    r = 1;
    if ((s32) arg0->unk0x4 != 0) {
        return 0;
    }
    if ((s32) *(s32 *)&lbl_803009B0 != 0) {
        return r;
    }
    if (lbl_80300460 != 0) {
        return r;
    }
    return 0;
}
