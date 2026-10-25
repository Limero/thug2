// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80131234-0x801312C4 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern bool lbl_803032E8;
extern bool lbl_803032EC;
Unk_FFAD6788 *fn_8012ED7C(Unk_FFAD6788 *);
void fn_8012EE64(Unk_FFAD6788 *, s32);
void fn_80131234(void) {
    Unk_FFAD6788 *cur;
    Unk_FFAD6788 *next;
    s32 flags;
    if (lbl_803032E8 != 0) {
        lbl_803032EC = 1;
    } else {
        cur = fn_8012ED7C(NULL);
        if (cur != NULL) {
            do {
                next = fn_8012ED7C(cur);
                flags = cur->unk0xCC;
                if (flags < 0 && !(flags & QB_UNKNOWN_0x40000000) && cur != NULL) {
                    fn_8012EE64(cur, 3);
                }
                cur = next;
            } while (cur != NULL);
        }
    }
}
