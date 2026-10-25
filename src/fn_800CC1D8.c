// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CC1D8-0x800CC268 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct Obj {
    s32 pad[0x44 / 4];
    void *f44;
} Obj;

typedef struct Node {
    void *f0;
    void *f4;
} Node;

typedef struct Sub {
    s32 pad[0x14 / 4];
    void *f14;
} Sub;

typedef struct Vt {
    s32 pad0[4];
    s16 off;
    s32 fn;
} Vt;

typedef struct It {
    void *f0;
    s32 f4;
    void *f8;
} It;

void fn_800CC1D8(Obj *arg0, s32 arg1) {
    It it;
    Sub *o;
    Vt *vt;

    it.f0 = (arg0->f44 != NULL) ? ((Node *)arg0->f44)->f4 : NULL;
    it.f8 = arg0->f44;
    while (it.f0 != it.f8) {
        o = ((Node *)it.f0)->f0;
        vt = (Vt *)o->f14;
        ((void (*)(void *, s32))vt->fn)((char *)o + vt->off, arg1);
        it.f0 = ((Node *)it.f0)->f4;
        it.f8 = arg0->f44;
    }
}
