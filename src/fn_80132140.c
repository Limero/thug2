// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80132140-0x801321B8 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

typedef struct S_140_E {
    char _p00[0x14];
    s32 f14;
} S_140_E;

typedef struct S_140_O {
    char _p00[0x38];
    s32 cnt;
    char _p3C[0x58];
    s32 tbl;
} S_140_O;

void fn_8012F8E8(void *, s32, void *);
void fn_801321B8(void *);

void fn_80132140(S_140_O *arg0) {
    s32 c;
    s32 off;
    s32 z;

    fn_801321B8(arg0);
    c = arg0->cnt;
    if (0 == c--) return;
    off = c * 0x2C;
    z = 0;
    do {
        S_140_E *e = (S_140_E *)(off + (s32)arg0->tbl);
        s32 v = e->f14;
        if (v != 0) {
            e->f14 = z;
            fn_8012F8E8(arg0, v, 0);
        }
        off = off - 0x2C;
    } while (0 != c--);
}
