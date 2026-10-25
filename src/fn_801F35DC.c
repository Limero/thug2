// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F35DC-0x801F366C (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    char pad0x0[0x300];
    s32 unk0x300;
    s32 unk0x304;
    char pad0x308[0x20];
    s32 unk0x328;
} Rec_801F35DC;

void fn_801F35DC(Rec_801F35DC *arg0, s32 arg1) {
    s32 count = arg0->unk0x328;
    s32 found = 0;
    s32 i = 0;
    u8 *p;
    s32 off;
    s32 lim;

    if (found < count) {
        p = (u8 *)arg0 + 0x300;
        off = 0;
        do {
            s32 v = *(u8 *)p;
            p += 4;
            if (v == arg1) {
                if (i < count - 1) {
                    Rec_801F35DC *q = (Rec_801F35DC *)(off + (s32)arg0);
                    do {
                        s32 t = q->unk0x304;
                        i += 1;
                        q->unk0x300 = t;
                        q = (Rec_801F35DC *)((char *)q + 4);
                        lim = arg0->unk0x328;
                        lim -= 1;
                    } while (i < lim);
                }
                found = 1;
                break;
            }
            count = arg0->unk0x328;
            i += 1;
            off += 4;
        } while (i < count);
    }
    if (found != 0) {
        arg0->unk0x328--;
    }
}
