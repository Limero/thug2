// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801321F4-0x80132260 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef struct S_1F4_W {
	u32 a : 4;
	u32 b : 1;
	u32 c : 1;
	u32 d : 26;
} S_1F4_W;

typedef struct S_1F4_E {
	char _pad[0x28];
	S_1F4_W w;
} S_1F4_E;

typedef struct S_1F4_O {
	char _p00[0x38];
	s32 cnt;
	char _p3C[0x58];
	void * volatile tbl;
	char _p98[0x1C];
	u32 flags;
} S_1F4_O;

void fn_801321F4(S_1F4_O *arg0) {
    s32 c = arg0->cnt;
    s32 t = (s32)(arg0->flags >> 0x1F);
    s32 off;
    s32 cur;
    s32 hi;

    if (0 == c--) return;
    off = c * 0x2C;
    cur = off;
    hi = 0;
    do {
        if (t) {
            S_1F4_E *e = (S_1F4_E *)(off + (s32)arg0->tbl);
            e->w.a = hi;
            return;
        }
        t = (s32)((S_1F4_E *)(cur + (s32)arg0->tbl))->w.c;
        cur -= 0x2C;
        off -= 0x2C;
    } while (0 != c--);
}
