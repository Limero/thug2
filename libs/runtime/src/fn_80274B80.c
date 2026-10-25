// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80274B80-0x80274BEC (108B). Byte-identical.
#include "types.h"
#include "structs.h"

extern char lbl_803AF2C4[];
extern s32 lbl_803AF2D4;
extern char lbl_803AF2D8[];

s32 fn_80274B80(void) {
    Unk_4C649A8C *p;
    if (lbl_803AF2D4 == 0) {
        lbl_803AF2D4 = 1;
        p = lbl_803AF2C4;
        memset((s32)p, 0, 0x10);
        p->unk0x4 = (s32)lbl_803AF2D8;
    }
    return (s32)lbl_803AF2C4;
}
