// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80184458-0x80184528 (208B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 fn_80184168(void *);
s32 fn_8018B4C0(void *, s32 *, s32 *);
s32 fn_8018EC90(void *);
typedef struct { s16 unk0x0; s16 pad; s32 (*unk0x4)(void *); } Ent;
typedef struct { char pad[0x14]; Ent *vt; } Obj;
void fn_80184458(void *arg0) {
    s32 spC;
    s32 sp8;
    Obj *o;

    for (sp8 = 0; sp8 < fn_80184168(arg0); sp8++) {
        o = (Obj *)fn_8018B4C0((char *)arg0 + 4, &sp8, &spC);
        if (o->vt[4].unk0x4((char *)o + o->vt[4].unk0x0) != 0) {
            continue;
        }
        if (o->vt[0x15].unk0x4((char *)o + o->vt[0x15].unk0x0) != 0) {
            continue;
        }
        if (fn_8018EC90(o) != 0) {
            continue;
        }
        o->vt[0xC].unk0x4((char *)o + o->vt[0xC].unk0x0);
    }
}
