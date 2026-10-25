// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002F7D4-0x8002F9C4 (496B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct Track Track;
typedef struct Cont Cont;

struct Track {
    char pad00[0x4];
    s32 u04;
    char pad08[0x10];
    f32 f18;
    f32 f1C;
    f32 f20;
    char pad24[0x4];
    s32 u28;
    char pad2C[0x78];
    s32 uA4;
};

struct Cont {
    char pad00[0x14];
    Track *t;
};

typedef struct Obj {
    char pad00[0x24];
    s32 *key;
    char pad28[0x10];
    f32 f38;
    f32 f3C;
    f32 f40;
    f32 f44;
    f32 f48;
    char pad4C[0x20];
    f32 f6C;
    s32 f70;
    f32 f74;
    Cont *c78;
} Obj;

extern f32 lbl_802919A0;
f32 fn_800144C8(void);
void *fn_80032088(u32 n);
Track *fn_8012ED98(Track *t);
s32 fn_8012F030(Track *t, s32 x);
void fn_8012F024(Track *t);
void fn_8002DDAC(s32 *t, f32 *a, f32 *b, f32 *cc);

void fn_8002F7D4(Obj *arg0) {
    s32 *q;
    s32 *q2;
    s32 *q3;
    s32 *q4;
    s32 *w;
    s32 v;
    Cont *c;
    s32 flag;
    f32 lim;
    f32 acc;
    f32 d;
    f32 sp[3];
    f32 *pa;
    f32 *pb;
    f32 *pc;
    volatile double _dummy;

    q = arg0->key;
    if (q[1] == -1) {
        q = 0;
    }
    q2 = q ? q - 1 : 0;
    if (q2) {
        arg0->f6C = ((f32 *)q2)[8];
    }

    lim = lbl_802919A0;
    if (arg0->f48 > lim) {
        d = arg0->f48 - fn_800144C8();
        arg0->f48 = d;
        if (d > lim) {
            acc = d;
        } else {
            acc = lim;
        }
        arg0->f48 = acc;
        arg0->f38 = (acc / arg0->f44) * (arg0->f40 - arg0->f3C) + arg0->f3C;
    } else {
        arg0->f38 = arg0->f3C;
    }

    if (arg0->f70 != 0) {
        c = arg0->c78;
        if (c->t == 0) {
            c->t = fn_8012ED98(fn_80032088(0xF8));
        }
        flag = fn_8012F030(arg0->c78->t, 0);
        if (flag == 0) {
            fn_8012F024(arg0->c78->t);
            arg0->f70 = flag;
            return;
        }
        pa = &sp[0];
        pb = &sp[1];
        pc = &sp[2];
        sp[0] = lbl_802919A0;
        sp[1] = lbl_802919A0;
        sp[2] = lbl_802919A0;
        v = (arg0->key[1] == -1);
        __asm__("" : "+r"(v));
        q = arg0->key;
        if (v) {
            q = 0;
        }
        w = q ? q - 1 : 0;
        if (w) {
            q3 = arg0->key;
            if (v) {
                q3 = 0;
            }
            q4 = q3 ? q3 - 1 : 0;
            fn_8002DDAC(q4 + 1, pa, pb, pc);
        }
        if (sp[0] <= sp[2]) {
            if (sp[1] >= arg0->f74) {
                goto clear;
            }
        }
        if (sp[0] >= sp[2]) {
            if (sp[1] <= arg0->f74) {
                goto clear;
            }
        }
        goto done;
    clear:
        fn_8012F024(arg0->c78->t);
        arg0->f70 = 0;
    done:
        ;
    }
}
