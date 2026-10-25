// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800ABCA8-0x800ABD08 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
u32 fn_8000A7F8(u32, s8 *);
void sprintf(char *, const char *, ...);
extern char lbl_80298568[];
void fn_800ABCA8(Unk_9B16FFA5 *arg0, s8 *arg1, s32 arg2) {
    char sp8[0x200];
    s8 *p;
    s32 h;

    if (arg2 == -1) {
        p = arg1;
        h = arg0->unk0x34BC;
    } else {
        sprintf(sp8, lbl_80298568, arg1, arg2);
        p = (s8 *)sp8;
        h = arg0->unk0x34BC;
    }
    fn_8000A7F8(h, p);
}
