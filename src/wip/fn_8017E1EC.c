// REBUILT 2026-10-17 from want decode (was m2c husk at 10.1% with wrong
// callees, GPR-only frame, and bogus ctr do-whiles).
// PARKED 2026-10-17 at 62.4% NEAR (size-exact 340B, frame-exact 0x30, tail
// from bl 80182B88 to blr byte-identical). Frame needs `volatile double
// _dummy` (+8 quirk class); regs need local `register __asm__` pins
// (p->r30, p194->r28, p1A4->r27; arg0/counters fall into r31/r29).
// WHAT WAS RECOVERED (want fully decoded, all verified): empty 3-spin is
// `for (i = 3; i != 0; i--) {}` (ngccc keeps it); loop counts are 0x13/1
// with pre-test-dec latches (20+2 calls); fn_80182B88 is 2-arg (arg0, 0)
// (r4=0, no r5 setup); fn_801257B8(s32,s32)->s32 x2 (PRINT_TRICK_INFO,0 →
// bool at 0x98 via `b=1; if(a==0)b=0` shape; FOCUS_MAX_TIMES,1 → 0x8);
// fn_8012570C(s32,s32)->f32 (FOCUS_TIME_LIMIT,1 → stfs 0x4); local struct
// with f32 0x4/0x6C/0x90 + u16 0xC (sth); second zero-block written
// [30,34,38] in source so ngccc's right-rotation lands want's [38,30,34].
// WALLS (all measured, none reachable — same build/scheduler class as the
// M5.0c `mr r9,r3` and fn_8005E08C walls): (1) BOTH latch tests copy the
// counter to a scratch (`mr r0,r29` / `mr r28,r27`) — `n-- != 0` lowering
// always materialises the pre-dec value; no single-branch C shape tests the
// home directly (u32 counters tried: worse, 48.2%, cmplwi cascade).
// (2) Zero stores share one reg (r28, incl. the sth) while want splits
// r30 (stws, from dead walker) + r0 (sth, early-hoisted li); a same-reg
// pinned zero (27.6%) evicts the loop-2 counter and cascades. (3) The
// second n-store (0x74) schedules ahead of the first (0x78).
// family=m2c range=0x8017E1EC-0x8017E340 size=340B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern f32 lbl_802A9194;

void fn_80182E28(void *, s32);
void fn_80182ED8(void *, s32, s32);
void fn_80125000(void *);
void fn_80182B88(void *, s32);
s32 fn_801257B8(s32, s32);
f32 fn_8012570C(s32, s32);
void fn_80180A50(void *);

typedef struct {
    char pad0x0[0x4];
    f32 unk0x4;
    s32 unk0x8;
    u16 unk0xC;
    char pad0xE[0x2];
    s32 unk0x10;
    char pad0x14[0x4];
    s32 unk0x18;
    char pad0x1C[0x8];
    s32 unk0x24;
    s32 unk0x28;
    char pad0x2C[0x4];
    s32 unk0x30;
    s32 unk0x34;
    s32 unk0x38;
    char pad0x3C[0x2C];
    s32 unk0x68;
    f32 unk0x6C;
    char pad0x70[0x4];
    s32 unk0x74;
    s32 unk0x78;
    s32 unk0x7C;
    char pad0x80[0x10];
    f32 unk0x90;
    char pad0x94[0x4];
    s32 unk0x98;
} A1EC;

A1EC *fn_8017E1EC(A1EC *arg0) {
    register u8 *p __asm__("r30");
    s32 n1;
    s32 n2;
    register u8 *p194 __asm__("r28");
    register u8 *p1A4 __asm__("r27");
    s32 i;
    f32 f;
    s32 a;
    s32 b;
    volatile double _dummy;

    fn_80182E28((char *)arg0 + 0x3C, 0x10);
    fn_80182ED8((char *)arg0 + 0x54, 8, 8);
    for (i = 3; i != 0; i--) {
    }
    p = (u8 *)arg0 + 0xA0;
    n1 = 0x13;
    p194 = (u8 *)arg0 + 0x194;
    p1A4 = (u8 *)arg0 + 0x1A4;
    do {
        fn_80125000(p);
        p += 0xC;
    } while (n1-- != 0);
    p = p1A4;
    fn_80125000(p194);
    n2 = 1;
    do {
        fn_80125000(p);
        p += 0xC;
    } while (n2-- != 0);
    f = lbl_802A9194;
    arg0->unk0x78 = n2;
    arg0->unk0x10 = 0;
    arg0->unk0x18 = 0;
    arg0->unk0x24 = 0;
    arg0->unk0x28 = 0;
    arg0->unk0x68 = 0;
    arg0->unk0x6C = f;
    arg0->unk0x74 = n2;
    arg0->unk0x7C = 0;
    arg0->unk0xC = 0;
    fn_80182B88(arg0, 0);
    arg0->unk0x90 = f;
    arg0->unk0x30 = 0;
    arg0->unk0x34 = 0;
    arg0->unk0x38 = 0;
    a = fn_801257B8(QB_PRINT_TRICK_INFO, 0);
    b = 1;
    if (a == 0) {
        b = 0;
    }
    arg0->unk0x98 = b;
    arg0->unk0x4 = fn_8012570C(QB_FOCUS_TIME_LIMIT, 1);
    arg0->unk0x8 = fn_801257B8(QB_FOCUS_MAX_TIMES_IN_COMBO, 1);
    fn_80180A50(arg0);
    return arg0;
}
