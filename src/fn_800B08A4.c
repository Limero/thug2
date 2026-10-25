// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B08A4-0x800B090C (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
typedef struct P4 { __ps_t a; __ps_t b; __ps_t c; __ps_t d; } P4;
typedef struct Obj {
    char pad0[0x2C];
    s32 unk2C;
    char pad30[8];
    void *unk38;
    char pad3C[4];
    P4 pair;
} Obj;
__ps_t *fn_80057E2C(__ps_t *);
void fn_800B08A4(Obj *arg0, __ps_t *arg1) {
    arg0->unk38 = arg1;
    if ((arg1 != NULL) && (arg0->unk2C == 0)) {
        __ps_t *p = fn_80057E2C(arg1);
        arg0->pair.a = p[0];
        arg0->pair.b = p[1];
        arg0->pair.c = p[2];
        arg0->pair.d = p[3];
    }
}
