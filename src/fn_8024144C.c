// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8024144C-0x80241540 (244B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct { s8 a; s8 b; s8 c; s8 d; } B4;
typedef struct Obj Obj;
/* method-offset slot at +0x38 is a SIGNED 16-bit field (lha), fn ptr at +0x3C */
typedef struct VT { char pad0[0x38]; s16 off; void (*fn)(Obj *, void *); } VT;
struct Obj { char pad0[0x14]; VT *vt; };

extern s32 fn_800546A0(s32);
extern s32 fn_80057CA0(Obj *);
extern s32 fn_80241540(Obj *, void *);
extern void fn_8005F0CC(Obj *);

void fn_8024144C(s32 *arg0, s32 arg1, s8 arg2) {
    s32 sp8[2];
    B4 sp10;
    B4 sp14;
    s32 sp18;
    Obj *a;
    Obj *n;
    VT *vt;

    a = (Obj *)fn_800546A0(*arg0);
    if (a == 0) return;
    n = (Obj *)fn_80057CA0(a);
    if (n == 0) return;
    if (arg1 != 0) {
        if (arg2 != 0) {
            s32 *pp = &sp8[0];
            sp10.a = -0x60; sp10.b = 0x64; sp10.c = -0x60; sp10.d = 0;
            sp8[0] = *(s32 *)&sp10;
            vt = n->vt;
            vt->fn((Obj *)((char *)n + vt->off), pp);
        } else {
            sp14.a = -0x60; sp14.b = 0x64; sp14.c = 0x64; sp14.d = arg2;
            sp8[0] = *(s32 *)&sp14;
            vt = n->vt;
            vt->fn((Obj *)((char *)n + vt->off), &sp8[0]);
        }
    } else {
        if (fn_80241540((Obj *)arg0, &sp18) == 0) goto L_f0;
        sp8[0] = sp18;
        vt = n->vt;
        vt->fn((Obj *)((char *)n + vt->off), &sp8[0]);
    }
    return;
L_f0:
    fn_8005F0CC(n);
}
