// WIP DRAFT (non-matching) — hand-rebuilt from disasm (m2c husk was corrupt)
// family=ps range=0x8006821C-0x80068338 size=284B
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// 2026-09-24 decode notes:
// Draw-order comparator. Caller fn_80068630 passes it to
// fn_8026A07C(&arr, count, 4, 0x8006821C) (qsort-like over object ptrs).
//   cam = fn_80024660(fn_8005DE90(lbl_80300444)) — camera position,
//         stored as two SN_PS_type pairs.
//   d2K = |posK - cam|^2 per arm K in {A=*arg0, B=*arg1}: pos pairs at
//         +0x28/+0x30; subtract, multiply zw, merge with lbl_80294850,
//         madd xy, sum0. The B arm interleaves with the A arm.
//   r = (s32)(d2B - d2A) — fctiwz truncation from the high lanes.
//   tiebreak r==0: u8 +0x12C: r = B->order - A->order.
// 2026-09-25 rewrite: dropped all register pins and the ps_mr asm wedge
// (task policy: semantic C only). Stack slots V[10] mirror want's ten pair
// spill slots (V[0]=camA@8, V[1]=camB@16, V[2]=dAxy@24, V[3]=dAzw@32,
// V[4]=pA/dBxy@40, V[5]=pAz/dBzw@48, V[6]=pB@56, V[7]=pBz@64,
// V[8]=d2B@72, V[9]=d2A@80); the arithmetic chain runs through one
// register __ps_t temp. Callee protos from prologue audit: fn_8005DE90
// takes the lbl VALUE (want lwz r3,0x444(r9)) and returns a pointer
// (lwz r3,0x18(r3)); fn_80024660 is the addi +0x68 leaf (void*)->(void*).
// lbl_80294850 is a 0x3C rodata2 table whose first pair is (0,0).
// PARKED 2026-09-25 at 16/66 (24.2%) via tools/ps_diff.py (got 264B vs
// want 284B/71 words; prologue+calls+tail match, mid-body diverges).
// Tried and reverted: (a) SN_PS_type*vp=&V[0] for want's r11 base plus a
// live cA=camA temp -> 10/70 (14.3%), pointer web ballooned the frame;
// (b) B-arm loads interleaved into the A-arm math in source order ->
// 15/67 (22.4%), scheduler sank the stores anyway. Precise residue:
// want keeps camA live in f8 across the whole body (loaded once, never
// reloaded) while reloading camB twice through an r1+8-derived r11 base;
// want emits ps_mr+ps_sub (register copy) where plain C folds to one sub;
// and want's B-arm pair loads sit between A's mul and madd. All four are
// scheduler/allocator artifacts, not source-reachable from plain C;
// doc-06/doc-15 family. No asm/pins used per policy (a prior asm+pin
// variant scored 23/69 but is not kept: inline asm is banned).
#include "types.h"
#include "dolphin/SN_PS.h"

extern s32 lbl_80300444;
extern __ps_t lbl_80294850;
extern void *fn_8005DE90(s32);
extern void *fn_80024660(void *);

s32 fn_8006821C(void **arg0, void **arg1) {
    SN_PS_type V[10];
    __ps_t *cam;
    void *objA;
    void *objB;
    __ps_t zero;
    __ps_t tmp;
    f32 fA;
    f32 fB;
    s32 r;

    cam = (__ps_t *)fn_80024660(fn_8005DE90(lbl_80300444));
    objA = *arg0;
    objB = *arg1;
    zero = lbl_80294850;
    V[0].ps = cam[0];
    V[1].ps = cam[1];
    V[4].ps = ((__ps_t *)objA)[5];
    V[5].ps = ((__ps_t *)objA)[6];
    tmp = V[4].ps - V[0].ps;
    V[2].ps = tmp;
    tmp = V[5].ps - V[1].ps;
    V[3].ps = tmp;
    tmp = V[3].ps * V[3].ps;
    tmp = __builtin_ps_merge00(tmp, zero);
    tmp = __builtin_ps_madd(V[2].ps, V[2].ps, tmp);
    tmp = __builtin_ps_sum0(tmp, tmp, tmp);
    V[9].ps = tmp;
    V[6].ps = ((__ps_t *)objB)[5];
    V[7].ps = ((__ps_t *)objB)[6];
    tmp = V[6].ps - V[0].ps;
    V[4].ps = tmp;
    tmp = V[7].ps - V[1].ps;
    V[5].ps = tmp;
    tmp = V[5].ps * V[5].ps;
    tmp = __builtin_ps_merge00(tmp, zero);
    tmp = __builtin_ps_madd(V[4].ps, V[4].ps, tmp);
    tmp = __builtin_ps_sum0(tmp, tmp, tmp);
    V[8].ps = tmp;
    fA = V[9].flt.hi;
    fB = V[8].flt.hi;
    r = (s32)(fB - fA);
    if (r == 0) {
        r = *(u8 *)((char *)objB + 0x12C) - *(u8 *)((char *)objA + 0x12C);
    }
    return r;
}
