// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802351F4-0x802353D0 (476B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct Mgr_s {
    void *f000;
    s32 f004;
    s32 f008;
    s32 f00C;
    char _010[0x8];
    s32 f018;
    s32 f01C;
    s32 f020;
    char _024[0x54];
    s32 f078;
    s32 f07C;
    s32 f080;
    s32 f084;
    s32 f088;
    s32 f08C;
    char _090[0x3490];
    s32 f3520;
    char _3524[0x4208];
} Mgr;

/* the >= 0x10000 part of the object, reached through ONE page base (r26) */
typedef struct Hi_s {
    char _0[0x772C];
    s32 f772C;
    u8 f7730;
    char _7731[0x97];
    s32 f77C8;
    s32 f77CC;
} Hi;

void *Mem_Alloc2(s32 size);
void *fn_8022D1D0(void *p);
s32 fn_80240B0C(void *p, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);
void fn_8023B6F0(void *p);
s32 Script_GenerateCRC(const char *s);
extern char lbl_802B0B84[];
extern char lbl_802B0B98[];
extern char lbl_802B0BA8[];

void *fn_802351F4(Mgr *self) {
    char sp8[0x80];
    char sp88[0x80];
    char sp108[0x80];
    s32 *t18;
    s32 *t1c;
    s32 *t20;
    char *base90;
    Hi *hi;
    s32 *p;
    char *q;
    s32 i;
    s32 j;
    s32 n;
    s32 m;
    s32 k;
    s32 z1;
    s32 z2;
    s32 zz;

    fn_80240B0C((char *)self + 0x3524, 0, 0, 0, 0, 0, 0);
    n = 7;
    fn_80240B0C((char *)self + 0x352A, 0, 0, 0, 0, 0, 0);
    q = (char *)self + 0x17770;
    do {
        fn_80240B0C(q, 0, 0, 0, 0, 0, 0);
        q += 6;
    } while (0 != n--);

    hi = (Hi *)((char *)self + 0x10000);
    t18 = &self->f018;
    t1c = &self->f01C;
    t20 = &self->f020;
    self->f000 = fn_8022D1D0(Mem_Alloc2(0x500));
    base90 = (char *)self + 0x90;
    z1 = 0;
    self->f080 = z1;
    self->f084 = z1;
    self->f088 = z1;
    self->f08C = z1;
    zz = 0;
    i = 0;
    do {
        p = (s32 *)((char *)(i * 0xE8 + (s32)base90) + 0xE4);
        j = 0x3A;
        do {
            *p = zz;
            p -= 1;
        } while (--j != 0);
        i = i + 1;
    } while (i <= 0x39);

    z2 = 0;
    __asm__("" : "+r"(z2));
    m = 0;
    __asm__("" : "+r"(m));
    self->f004 = z2;
    k = 0;
    hi->f772C = z2;
    self->f008 = z2;
    hi->f77C8 = z2;
    hi->f77CC = z2;
    do {
        m = m + 1;
        sprintf(sp8, lbl_802B0B84, m);
        t18[k] = Script_GenerateCRC(sp8);
        sprintf(sp88, lbl_802B0B98, m);
        t1c[k] = Script_GenerateCRC(sp88);
        sprintf(sp108, lbl_802B0BA8, m);
        t20[k] = Script_GenerateCRC(sp108);
        k += 3;
    } while (m <= 7);

    self->f3520 = 0;
    fn_8023B6F0(self);
    self->f00C = 0;
    hi->f7730 = 0;
    self->f078 = 0;
    self->f07C = 0;
    return self;
}
