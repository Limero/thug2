// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80030A64-0x80030ADC (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct W30A64_M {
    u8 _0[0x24];
    s32 *unk24;
} W30A64_M;

typedef struct W30A64_Obj {
    u8 _0[0x28];
    f32 unk28;
} W30A64_Obj;

extern f32 lbl_802919F0;
extern f32 lbl_802919F4;

f32 fn_80030A64(W30A64_M *arg0, s32 arg1, s32 arg2) {
    s32 *p;
    W30A64_Obj *o;
    s32 nul;

    p = arg0->unk24;
    nul = (p[1] == -1);
    o = (W30A64_Obj *) p;
    if (nul) {
        o = NULL;
    }
    o = (o != NULL) ? (W30A64_Obj *) ((char *) o - 4) : NULL;
    if (o == NULL) {
        return lbl_802919F0;
    }
    o = (W30A64_Obj *) p;
    if (nul) {
        o = NULL;
    }
    o = (o != NULL) ? (W30A64_Obj *) ((char *) o - 4) : NULL;
    return o->unk28 * lbl_802919F4;
}
