// UPDATE 2026-10-19: now 95.0% (76/80, size-exact) — residual (b) (p3 reload
// hoist) is FIXED; remaining are (a) s2 birth [addi r3][mr r30] vs got
// [addi r30][mr r3] and (c) 07B20 setup [li r4][mr r3] vs got reversed.
// Ruled out 2026-10-19: two-var birth-in-scratch (`t=&sp8; s2=t; fn(t)`)
// coalesces into the r30 pin (identical 95.0%). Want's full 07B20 window
// (ps_disasm): bl 07A80 / lis+addi(cb) / li r4,1 / mr r3,r30 / stw cb /
// li r5,0 / stw wB8 / bl — i.e. the cb/wB8 stores INTERLEAVE with the arg
// setup, so this is scheduler interleave order, not source order.
// PARKED 2026-10-13: 7.0% -> 90.0% (72/80 words),
// size-exact 320B. Full hand-decode via tools/ps_disasm.py (plain disasm
// STALLS at 0x800DEE0C on PS words; the m2c draft was PS-blind).
// LEVERS THAT LANDED (all delta-verified):
//  - matched-callee protos from src/: 0794C returns void* (takes S*),
//    07A80 takes (S*,s16,s16), 09DFC0=CObject_RemoveRefLink void 2-arg.
//  - frame struct S (0xC0 @r1+8): pairs px0@+0 / p0@+8 / p10@+0x10 / p18@+0x18
//    (S+8 reached via s2+8, NOT S+0 — the two first stores do NOT overwrite;
//    8(r1)=20-pair, 8(r30)=28-pair, 24/32(r1)=58/60-pairs).
//  - p reloaded via FRESH names per region (p1..p4, caller-saved r9); fp view
//    for f24+ (addi r11, f20 direct); homed set {arg0,s2,flag} -> stmw r29.
//  - `register S_DED84 *s2 __asm__("r30")` pin seats arg0->r31/s2->r30.
//  - cb as matched DESIGNATOR `s2->cb = fn_800DF3F0` (reloc-masked; numerics
//    always expand lis+ori (probe-proven), symbols give lis+addi).
//    cb sits at S+0x20 (want `stw r9,0x20(r30)` @0xEE74) — NOT 0xBC; wB8
//    stays @0xB8 (want `stw r31,0xb8(r30)` @0xEE7C). A 0xBC placement
//    scores 88.75% (9 diffs); 0x20 restores 90.00% (8 diffs).
//  - `s32 *pw = &sp8.wA8` precomputed before the trailing copies (want hoists
//    the addi above them); wA8 trio via sp8-direct (r1+0xB0 addressing).
//  - float-== materializes via fcmpu cr7 + mfcr + rlwinm (FP setcc idiom).
// RESIDUAL (8 words): (a) s2 birth 0xA0: want [addi r3][mr r30], got
//  [addi r30][mr r3] — the pin precolors home; unpinned swaps seating;
//  micro-probes show heavy-later-use always births in home (both
//  `s2=&sp;fn(s2)` and `fn(s2=&sp)` forms). (b) p3 reload 0xB4: want hoists
//  above call setup, got sinks below 40-load (pure tie; pre-call placement
//  would home p3 and break the frame). (c) 07B20 setup 0xE4: want [li r4]
//  [mr r3], got reversed (tie).
// NEGATIVE PROBES (recorded so future agents don't retry): volatile p0 keeps
//  both stores but CSE-merges bases (wrong); a0-pin (frame break + r31
//  conflict); -fno-schedule-insns2 (worse); assignment-in-arg (same birth).
// family=m2c range=0x800DED84-0x800DEEC4 size=320B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// FLAG: -fno-rerun-cse-after-loop -fno-schedule-insns
#include "types.h"
#include "structs.h"
typedef struct P_DED84 P_DED84;
typedef struct A_DED84 A_DED84;
typedef struct S_DED84 S_DED84;
struct P_DED84 {
    char _00[0x58];
    f32 f58;
    f32 f5C;
    f32 f60;
    f32 f64;
    char _68[0xAC];
    s32 f114;
};
struct A_DED84 {
    char _00[0x0C];
    P_DED84 *p0C;
    char _10[0x10];
    f32 f20;
};
struct S_DED84 {
    __ps_t px0;
    __ps_t p0;
    __ps_t p10;
    __ps_t p18;
    void (*cb)(void *);  /* +0x20 */
    char _24[0x84];
    s32 wA8;             /* +0xA8 */
    char _AC[0x0C];
    A_DED84 *wB8;        /* +0xB8 */
    char _BC[4];
};
void fn_8010794C(S_DED84 *);
void fn_80107A80(S_DED84 *, s32, s32);
void fn_80107B20(S_DED84 *, s32, s32);
void CObject_RemoveRefLink(CStruct *, CStruct *);
void fn_800DF3F0(Unk_FFAD6788 *);

void fn_800DED84(A_DED84 *arg0) {
    S_DED84 sp8;
    register S_DED84 *s2 __asm__("r30");
    P_DED84 *p1;
    P_DED84 *p2;
    P_DED84 *p3;
    P_DED84 *p4;
    s32 *pw;
    f32 *fp;
    s32 t = 0;
    s32 flag;
    s32 w;

    p1 = arg0->p0C;
    fp = &arg0->f20;
    if (arg0->f20 == p1->f58 && fp[1] == p1->f5C && fp[2] == p1->f60) {
        t = (fp[3] == p1->f64);
    }
    if (t != 0) {
        return;
    }
    p2 = arg0->p0C;
    flag = 1;
    if ((p2->f114 & 8) == 0) {
        flag = 0;
    }
    if (flag != 0) {
        *(__ps_t *)((char *)arg0 + 0x20) = *(__ps_t *)((char *)p2 + 0x58);
        *(__ps_t *)((char *)arg0 + 0x28) = *(__ps_t *)((char *)p2 + 0x60);
        return;
    }
    fn_8010794C(s2 = &sp8);
    p3 = arg0->p0C;
    sp8.px0 = *(__ps_t *)((char *)arg0 + 0x20);
    s2->p0 = *(__ps_t *)((char *)arg0 + 0x28);
    sp8.p10 = *(__ps_t *)((char *)p3 + 0x58);
    sp8.p18 = *(__ps_t *)((char *)p3 + 0x60);
    fn_80107A80(s2, 0, 0x50);
    s2->cb = fn_800DF3F0;
    s2->wB8 = arg0;
    fn_80107B20(s2, 1, 0);
    p4 = arg0->p0C;
    w = sp8.wA8;
    pw = &sp8.wA8;
    *(__ps_t *)((char *)arg0 + 0x20) = *(__ps_t *)((char *)p4 + 0x58);
    *(__ps_t *)((char *)arg0 + 0x28) = *(__ps_t *)((char *)p4 + 0x60);
    if (w != 0) {
        CObject_RemoveRefLink((CStruct *)w, (CStruct *)pw);
        sp8.wA8 = flag;
    }
}
