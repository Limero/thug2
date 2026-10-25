// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80131A24-0x80131A88 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void *fn_8012ED7C(CStruct *);
void *fn_80131A24(s32 arg0) {
    Unk_FFAD6788 *r;
    r = fn_8012ED7C(0);
    while (r != 0) {
        Unk_FFAD6788 *nxt;
        nxt = fn_8012ED7C(r);
        if (r->unk0xCC < 0 && r->unk0xD4 == arg0) return r;
        r = nxt;
    }
    return 0;
}
