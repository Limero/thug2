// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80106078-0x801060F8 (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

/* 8-byte list row at arg0 + 0x20 + i*8: a handle/pointer word then a value
 * word.  The removal copies the LAST row over the found one, so both words
 * must be written. */
typedef struct {
    s32 f0;
    s32 f1;
} Entry;

void fn_80106078(Unk_5CB48605 *arg0, s32 arg1) {
    s32 i = arg0->unk0xFC4;
    s32 n0 = arg0->unk0xFC0;
    s32 off = (i << 3) + 0x20;
    Entry *p = (Entry *)((char *)(off + (s32)arg0));

    if (i >= n0)
        return;
    if (*(s32 *)((char *)(off + (s32)arg0)) == arg1) {
        s32 last = n0 - 1;
        arg0->unk0xFC0 = last;
        { char *q = (char *)((last << 3) + (s32)arg0) + 0x20; *p = *(Entry *)q; }
        arg0->unk0xFC8 = arg0->unk0xFC8 - 1;
    } else {
        s32 n;
        do {
            n = *(volatile s32 *)&arg0->unk0xFC0;
            p++;
            if (++i >= n)
                return;
        } while (p->f0 != arg1);
        {
            s32 last = n - 1;
            arg0->unk0xFC0 = last;
            { char *q = (char *)((last << 3) + (s32)arg0) + 0x20; *p = *(Entry *)q; }
            arg0->unk0xFC8 = arg0->unk0xFC8 - 1;
        }
    }
}
