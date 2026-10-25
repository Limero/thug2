// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800137C4-0x80013860 (156B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern volatile s32 lbl_802FFF14;
extern Unk_C7387A53 *lbl_803C9C38[16];
void fn_80013A3C(void);
s32 fn_80013238(Unk_C7387A53 *self);

void fn_800137C4(s32 arg0) {
    s32 base = (s32)lbl_803C9C38;
    s32 ok;
    s32 p;
    s32 end;

    for (;;) {
        if (lbl_802FFF14 == 0) {
            while (lbl_802FFF14 == 0) {
            }
        }
        fn_80013A3C();
        ok = 1;
        if (arg0 != 0) {
            p = base;
            end = base + 0x3C;
            while (p <= end) {
                Unk_C7387A53 *e = *(Unk_C7387A53 **)p;
                p += 4;
                if (fn_80013238(e) != 0) {
                    ok = 0;
                    break;
                }
            }
        }
        if (ok != 0) {
            break;
        }
    }
}
