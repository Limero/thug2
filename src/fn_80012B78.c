// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80012B78-0x80012C28 (176B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_8031349C[];
s32 strcasecmp(const char *, const char *);
s32 fn_800122C4(s32);
void *fn_80012284(void *, s32);

bool fn_80012B78(s32 arg0) {
    char *base;
    s32 nm;
    s32 i;
    s32 off;
    s32 entry;
    s32 cnt;
    s32 idx;
    void *p;
    void *q;

    nm = arg0;
    base = lbl_8031349C;
    for (i = 0, off = 0; i <= 0x63; i++, off += 4) {
        entry = *(s32 *) (off + (s32) base);
        if (entry != 0) {
            if (strcasecmp((const char *) entry, nm) == 0) {
                q = fn_800122C4(*(s32 *) (off + (s32) base));
                cnt = *(s32 *) ((char *) q + 0x8);
                p = (char *) q + 0xC;
                idx = 0;
                while (idx < cnt) {
                    if (*(u16 *) ((char *) p + 0xA) != 0) {
                        return true;
                    }
                    p = fn_80012284(p, 1);
                    idx += 1;
                }
            }
        }
    }
    return false;
}
