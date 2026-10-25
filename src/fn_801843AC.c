// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801843AC-0x80184458 (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    s16 m0;
    s16 pad;
    union {
        s32 (*f1)(void *);
        void (*f3)(void *, s32, s32);
    } fn;
} Ent;

typedef struct {
    char pad0x0[0x14];
    Ent *vt;
} Obj;

extern s32 fn_80184168(void *arg0);
extern s32 fn_8018B4C0(void *arg0, s32 *arg1, s32 *arg2);

void fn_801843AC(void *arg0, s32 arg1) {
    s32 spC;
    s32 sp8;
    Obj *o;

    for (sp8 = 0; sp8 < fn_80184168(arg0); sp8++) {
        o = (Obj *)fn_8018B4C0((char *)arg0 + 4, &sp8, &spC);
        if (o->vt[4].fn.f1((char *)o + o->vt[4].m0) != 0) {
            o->vt[0xE].fn.f3((char *)o + o->vt[0xE].m0, arg1, 1);
        }
    }
}
