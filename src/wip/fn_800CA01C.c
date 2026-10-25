// PARKED: 24.2%, full want-decoded rewrite (was an m2c husk). The store run
// now follows the original's emission order (0xC,4,8,0), which is where the
// last gain came from; the adjacent lfs pair is still swapped (reloc-proven
// B,A emission vs want A,B) in every variant tried (locals z/w either order,
// direct-global stores, split stores). Body wall: allocator freg choices
// diverge wholesale (t1->f9 vs f11, a4->f7 vs f6, d2->r8 vs r10) despite exact
// want op ordering.
// Semantically correct: o=arg0->unk0xC (0xC offset verified), d2=buf,
// delay loop, ret=0, buf math chain + overwrites all decoded from want.
// family=m2c range=0x800CA01C-0x800CA1A8 size=396B
// FLAG: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "structs.h"

extern f32 lbl_80299358;
extern f32 lbl_8029935C;

s32 fn_8003951C(void *);

typedef struct {
    char pad0x0[0xC];
    void *unk0xC;
    char pad0x10[0xC];
    void *unk0x1C;
} ArgCA;

typedef struct {
    f32 unk0x0;
    f32 unk0x4;
    f32 unk0x8;
    f32 unk0xC;
} Arg2CA;

s32 fn_800CA01C(ArgCA *arg0, s32 arg1, Arg2CA *arg2) {
    __ps_t buf[12];
    __ps_t *d2;
    __ps_t *o;
    __ps_t t0, t1, t2;
    s32 ret;
    s32 i;
    f32 *fb;
    f32 c3;
    f32 z, w;
    f32 a0, a4, a8, ac;
    f32 x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14;

    (void)arg1;
    if (fn_8003951C(arg0->unk0x1C) == 0) {
        z = lbl_80299358;
        arg2->unk0x8 = z;
        w = lbl_8029935C;
        arg2->unk0x4 = z;
        arg2->unk0x0 = z;
        arg2->unk0xC = w;
    }
    o = (__ps_t *)arg0->unk0xC;
    d2 = buf;
    __asm__("" : "+r"(d2));
    for (i = 4; i != 0; i--) {
        __asm__ volatile("" : "+r"(d2) : : "memory");
    }
    fb = (f32 *)buf;
    t0 = o[15];
    c3 = lbl_8029935C;
    ret = 0;
    buf[0] = t0;
    t1 = o[16];
    a4 = arg2->unk0x4;
    d2[1] = t1;
    t2 = o[17];
    a0 = arg2->unk0x0;
    buf[2] = t2;
    x0 = fb[0];
    t0 = o[18];
    x1 = fb[5];
    buf[3] = t0;
    x2 = fb[4];
    x1 = a4 * x1;
    t1 = o[19];
    x2 = a4 * x2;
    x3 = fb[1];
    buf[4] = t1;
    x0 = a0 * x0 + x2;
    x3 = a0 * x3 + x1;
    t2 = o[20];
    buf[5] = t2;
    t1 = o[21];
    a8 = arg2->unk0x8;
    buf[6] = t1;
    x4 = fb[8];
    t2 = o[22];
    x4 = a8 * x4 + x0;
    buf[7] = t2;
    t1 = o[11];
    buf[6] = t1;
    ac = arg2->unk0xC;
    x5 = fb[9];
    x6 = fb[12];
    x7 = fb[13];
    x5 = a8 * x5 + x3;
    x6 = ac * x6 + x4;
    t1 = o[12];
    x7 = ac * x7 + x5;
    buf[7] = t1;
    fb[15] = c3;
    fb[20] = x6;
    fb[21] = x7;
    x8 = fb[6];
    t0 = buf[10];
    x8 = a4 * x8;
    x9 = fb[10];
    x10 = ((f32 *)d2)[2];
    x11 = fb[7];
    x10 = a0 * x10 + x8;
    a4 = a4 * x11;
    x12 = fb[3];
    x9 = a8 * x9 + x10;
    x13 = fb[11];
    a0 = a0 * x12 + a4;
    x14 = fb[14];
    a8 = a8 * x13 + a0;
    x14 = ac * x14 + x9;
    a8 = a8 + ac;
    fb[22] = x14;
    fb[23] = a8;
    ((__ps_t *)arg2)[0] = t0;
    t1 = buf[10];
    t2 = buf[11];
    buf[8] = t1;
    ((__ps_t *)arg2)[1] = t2;
    buf[9] = buf[11];
    return ret;
}
