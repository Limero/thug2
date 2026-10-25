// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800306D0-0x80030750 (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct W306D0_M {
    u8 _0[0x24];
    s32 *unk24;
} W306D0_M;

void fn_800306D0(W306D0_M *arg0) {
    s32 *p;
    s32 *q;
    s32 nul;

    p = arg0->unk24;
    nul = (p[1] == -1);
    q = p;
    if (nul) {
        q = NULL;
    }
    q = (q != NULL) ? q - 1 : NULL;
    if (q == NULL) {
        return;
    }
    q = p;
    if (nul) {
        q = NULL;
    }
    q = (q != NULL) ? q - 1 : NULL;
    q = q + 1;
    if (q[10] == 0) {
        q[10] = -1;
        return;
    }
    q[10] = 0;
}
