// WIP DRAFT (non-matching) — C body REBUILT by hand from the DOL disassembly
// family=m2c range=0x8004EAC0-0x8004F108 size=1608B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// STATUS 2026-10-30: 4.7% -> 33.8% (DIFF). Object is now the EXACT want
// length (0x648 = 1608 B = 402 instructions); 70.1% of the instruction
// stream is byte-identical under a branch-displacement-masked, difflib-
// aligned diff (AGENTS 6es: with a length shift the index-aligned masked
// score understates the body, so both numbers are reported).
// The old FPR-frame `volatile double _dummy` is GONE: the frame is now
// ngccc-native AND equals want's (stwu -0x78 / stmw r25,0x3c / f28..f31 at
// 0x58..0x70 / LR 0x7c) with no dummy at all.
//
// WHAT THE REBUILD FIXED (each measured, in the order it paid):
//  1. Callee arity/return audit. Every callee is now declared with the
//     signature the retail prologue proves (CObject_AddRefLink/RemoveRefLink
//     2-arg, fn_800422D8/E0 -> f32, CScreenElement_SetJust 3-arg, one-arg
//     CStruct_ctor, AddInteger 3-arg, fn_800A54AC 7-arg mixed ABI). The
//     m2c draft had none of them, so 10+ spurious `crclr cr1eq` plus a
//     146-instruction overshoot (548 words vs 402) disappeared.
//  2. ONE name for the list cursor. The draft kept a second variable
//     (`nxt`) alongside the stack cursor `sp8`, so the value got a
//     callee-saved home plus an `mr r3,rN` at every call site. Retail
//     keeps it in the ARGUMENT register r3 (`lwz r3,0x64(r30)` /
//     `stw r3,8(r1)` / `bl`) with no copy — 8 sites, ~8 instructions.
//     Also: store the two zero/flag fields BEFORE assigning the cursor, so
//     the two zero stores land in the guard block like want.
//  3. FPR class pinned. Retail's float class is {f28=C_ae8, f29=C_ae0/acc-
//     copy, f30=C_adc, f31=prod}; plain C allocated {f28=acc, f29=acc},
//     i.e. the whole class one slot low. `register f32 acc __asm__("fr30")`
//     plus `register f32 mx __asm__("fr29")` fixes it (AGENTS 6ds-2: a
//     register-class rotation is a POOL OFFSET — pin one member, the rest
//     fall into place). Worth 61.9% -> 68.8% structural on its own.
//  4. Caller-saved page anchors for the two multiply constants. lbl_80292AE4
//     and lbl_80292AE8 are read in four different blocks, so `reload` gave
//     each ONE function-wide pseudo that had to live across every loop —
//     2 extra callee-saved GPRs (r23/r24) and an 8-byte-too-big frame.
//     The CF() macro materialises a FRESH @ha anchor in a caller-saved
//     register at each use site, exactly like want's r9/r11 (AGENTS 6br /
//     6bg-6). This is what made the prologue byte-exact: 9 saved GPRs and
//     frame -0x80 -> the correct 7 and -0x78. 68.8% -> 70.0% structural and
//     10.7% -> 20.6% masked.
//  5. The 0x2000-flag block polarity. m2c's
//     `if (f_1A8 != 0) {...} else if (acc > f_178) goto b42;` emits `bgt`;
//     want emits `ble`. Restating the else arm as `if (acc <= f_178) {} else
//     { f_178 = acc; goto b42; }` flips it and gains 2 instructions of
//     length plus the whole block's block-layout. 20.6% -> 26.4% masked.
//  6. The two CR triples. WANT contains, at the head of each of loops 1 and
//     2, `rotlwi r31,r31,0x10 ; mtcrf 8,r31 ; rotlwi r31,r31,0x10` — a
//     CR4->CR0 copy (rotlwi 0x10 puts CR4's bits at CR0's position) that
//     GCC 2.95 NEVER emits: it re-materialises the scc from the boolean in
//     r25 instead (`mcrf cr4,cr0` + `beq cr4`). Probed exhaustively — two
//     hand-built stand-alone probes (one plain, one with a call between the
//     two uses, the operator mapped with a 10-line probe) all give
//     `cmpwi 0,28,0`, never a CR4 pseudo. These 6 instructions are the ONLY
//     reason the object was 6 words short, so they are emitted literally as
//     one 3-instruction volatile asm per site: object becomes EXACTLY
//     1608 B and the masked score jumps 22.4% -> 33.8%.
//
// STILL PARKED (the residual, in descending order of size):
//  a. The scc is still materialised as `mcrf cr4,cr0` + `beq cr4` where
//     want has `mfcr r31` + `beq` (1 instruction x 2 sites). Same root cause
//     as (6) and presumably needs the same treatment, but the `mfcr r31`
//     must not disturb the r31 home the CR triples need.
//  b. In loops 1 and 2 the node field is loaded into f28 and the getter
//     result copied with `fmr f31,f1` before `fmuls f31,f28,f31`; want has
//     the field in f31 and multiplies `fmuls f31,f31,f1` straight off the
//     call result — 1 extra instruction per site, 2 sites. Inlining the
//     getter into the multiply (to delete the copy) was measured and is
//     WORSE: 403 words and 59.6% structural, so the staged `f1v` form is
//     right and the copy is a cc1 coalesce artefact.
//  c. Loop-head `stw r31,8(r1)` / `lwz r3,8(r1)` placement: 3 stores and 2
//     reloads land 3-4 slots away from want. Statement-order and
//     comma-expression variants were tried; the current form is the best of
//     them.
//  d. The loops-3/4 head still lays the `f_1A8` THEN arm out of line and
//     the ELSE arm inline; want is the other way round. Inverting the test
//     was measured (both polarities) and costs 2 points of structural
//     agreement, so the current polarity stays.
//  e. The common tail's two CF() anchors are scheduled a few slots from
//     want's positions.
//
// LEVERS MEASURED AND FOUND INERT on this body (do not re-run): every
// scheduling/GCSE flag in the project set — -fno-schedule-insns2 (29.6%),
// -fno-gcse (1.2%), -fno-rerun-cse-after-loop, -fno-sched-spec, -fno-sched-
// interblock, -fno-thread-jumps (10.6%), -fno-expensive-optimizations, -Os
// (2.2%), -O3; declaration-order permutations; `volatile` on the preloaded
// constants (costs 2 x 8 bytes of frame, 6as-199); function-wide preloading
// of AE4/AE8 (5 words longer); the scalar-vs-array extern form for the two
// anchored constants (byte-identical output, 6ek did not fire here);
// the inverted `f_1A8` test in loops 3/4 and in the 0x2000 block.
//
// ASM DENSITY: 12 emitted instructions of 402 (3.0%) — the 6 `CF` @ha
// anchors from (4) and the 6 CR-triple words from (6). All logic, all data
// access and all control flow is C. The `CF`
// anchors are address materialisation only, each replacing a `lis` the
// compiler would otherwise have emitted. Well inside the 4g / 6af-180 30%
// budget, and no `__volatile__`-vs-plain asm subtlety was load-bearing (both
// spellings of the triple score identically).
#include "types.h"
#include "qb_constants.h"
extern f32 lbl_80292ADC;
extern f32 lbl_80292AE0;
extern char lbl_80292AE4[];
extern char lbl_80292AE8[];

#define ANCH_R(reg, sym) ({ register s32 a_ __asm__(reg); \
    __asm__ volatile("lis %0,%1@ha" : "=r"(a_) : "s"(sym)); a_; })
#define CF(reg, sym, off) (*(f32 *)((char *)ANCH_R(reg, sym) + (off)))

extern f32 lbl_80292AEC;
extern s32 lbl_80301A78;
typedef struct { void *v; void *prev; void *next; } Ck_t;
typedef struct {
    char _00[0x0C]; s32 f_0C;
    char _10[0x54]; void *head;
    char _68[0x110];
    f32 f_178; f32 f_17C;
    char _180[0x10];
    s32 f_190; void *f_194; s32 f_198; s32 f_19C;
    f32 f_1A0; f32 f_1A4; s32 f_1A8;
    f32 f_1AC; f32 f_1B0; f32 f_1B4;
} Obj;
typedef struct {
    char _00[0x0C]; s32 f_0C;
    char _10[0x60];
    void *next;
    char _74[0x104];
    f32 f_178; f32 f_17C;
} Node;
void CObject_AddRefLink(void *, void *);
void CObject_RemoveRefLink(void *, void *);
f32 fn_800422D8(char *);
f32 fn_800422E0(char *);
s32 fn_8004195C(void *, void *);
void CScreenElement_SetJust(void *, f32, f32);
void CScreenElement_SetPos(void *, s32, f32, f32);
void fn_8004E734(void *, s32, s32, s32);
void CStruct_ctor(void *);
void AddInteger(void *, s32, s32);
s32 fn_800A54AC(s32, s32, s32, s32, s32, s32, f32);
void CStruct_delete(void *, s32);

void fn_8004EAC0(Obj *arg0) {
    s32 *sp8;
    s32 *nxt;
    s32 p0; s32 p1; s32 p2; s32 p3; s32 p4; s32 p5;
    s32 p6; s32 p7; s32 p8; s32 p9; s32 p10;
    s32 flag;
    void *r26;
    f32 prod, tmp;
    register f32 acc __asm__("fr30");
    register f32 mx __asm__("fr29");
    f32 t1, t2, f1v, e4a;

    acc = lbl_80292ADC;
    flag = (arg0->f_1AC > lbl_80292AE0);
    mx = acc;
    if (flag) {
        ((Ck_t *)&sp8)->prev = 0;
        ((Ck_t *)&sp8)->next = 0;
        sp8 = arg0->head;
        if (sp8 != NULL) {
            CObject_AddRefLink(sp8, &sp8);
        }
        __asm__ volatile("rotlwi 31,31,16\n\tmtcrf 8,31\n\trotlwi 31,31,16");
        r26 = (char *)arg0 + 0xD0;
        if (sp8 != NULL) {
            do {
                if (arg0->f_1A8 != 0) {
                    t1 = ((Node *)sp8)->f_178;
                    f1v = fn_800422D8((char *)sp8 + 0x88);
                } else {
                    t1 = ((Node *)sp8)->f_17C;
                    f1v = fn_800422E0((char *)sp8 + 0x88);
                }
                prod = t1 * f1v;
                acc += arg0->f_1AC;
                if (prod > mx) {
                    mx = prod;
                }
                nxt = (s32 *)((Node *)sp8)->next;
                if (sp8 != NULL) {
                    CObject_RemoveRefLink(sp8, &sp8);
                    sp8 = NULL;
                }
                sp8 = nxt;
                if (sp8 != NULL) {
                    CObject_AddRefLink(sp8, &sp8);
                }
            } while (sp8 != NULL);
        }
    } else {
        ((Ck_t *)&sp8)->prev = 0;
        ((Ck_t *)&sp8)->next = 0;
        sp8 = arg0->head;
        if (sp8 != NULL) {
            CObject_AddRefLink(sp8, &sp8);
        }
        __asm__ volatile("rotlwi 31,31,16\n\tmtcrf 8,31\n\trotlwi 31,31,16");
        r26 = (char *)arg0 + 0xD0;
        if (sp8 != NULL) {
            do {
                if (arg0->f_1A8 != 0) {
                    t1 = ((Node *)sp8)->f_17C;
                    t2 = ((Node *)sp8)->f_178;
                } else {
                    t1 = ((Node *)sp8)->f_178;
                    t2 = ((Node *)sp8)->f_17C;
                }
                prod = t2 * arg0->f_1B0;
                tmp = t1 * arg0->f_1B0;
                acc += tmp + arg0->f_1B4;
                if (prod > mx) {
                    mx = prod;
                }
                nxt = (s32 *)((Node *)sp8)->next;
                if (sp8 != NULL) {
                    CObject_RemoveRefLink(sp8, &sp8);
                    sp8 = NULL;
                }
                sp8 = nxt;
                if (sp8 != NULL) {
                    CObject_AddRefLink(sp8, &sp8);
                }
            } while (sp8 != NULL);
        }
        acc -= arg0->f_1B4;
    }
    if (sp8 != NULL) {
        CObject_RemoveRefLink(sp8, &sp8);
        sp8 = NULL;
    }
    if (arg0->f_0C & 0x2000) {
        if (arg0->f_1A8 == 0) {
            if (acc <= arg0->f_178) {
            } else {
                arg0->f_178 = acc;
                goto b42;
            }
        } else if (acc > arg0->f_17C) {
            arg0->f_17C = acc;
        }
    } else if (arg0->f_1A8 != 0) {
        arg0->f_17C = acc;
        arg0->f_178 = mx;
    } else {
        arg0->f_17C = mx;
b42:
        arg0->f_178 = acc;
    }
    fn_8004195C(arg0, r26);
    arg0->f_0C = arg0->f_0C | 0x400;
    if (arg0->f_1A8 != 0) {
        t1 = arg0->f_1A4;
        t2 = arg0->f_17C;
    } else {
        t1 = arg0->f_1A0;
        t2 = arg0->f_178;
    }
    tmp = (t1 + CF("r9", lbl_80292AE4, 0x2AE4)) * (t2 - acc) * CF("r11", lbl_80292AE8, 0x2AE8);
    if (flag) {
        ((Ck_t *)&sp8)->prev = 0;
        ((Ck_t *)&sp8)->next = 0;
        f1v = CF("r9", lbl_80292AE8, 0x2AE8);
        e4a = CF("r11", lbl_80292AE4, 0x2AE4);
        acc = arg0->f_1AC * f1v + tmp;
        sp8 = arg0->head;
        if (sp8 != NULL) {
            CObject_AddRefLink(sp8, &sp8);
        }
        if (sp8 != NULL) {
            do {
                if (arg0->f_1A8 != 0) {
                    CScreenElement_SetJust(sp8, arg0->f_1A0, lbl_80292ADC);
                    CScreenElement_SetPos(sp8, 1, (arg0->f_1A0 + e4a) * arg0->f_178 * f1v, acc);
                } else {
                    CScreenElement_SetJust(sp8, lbl_80292ADC, arg0->f_1A4);
                    CScreenElement_SetPos(sp8, 1, acc, (arg0->f_1A4 + e4a) * arg0->f_17C * f1v);
                }
                nxt = (s32 *)((Node *)sp8)->next;
                acc += arg0->f_1AC;
                if (sp8 != NULL) {
                    CObject_RemoveRefLink(sp8, &sp8);
                    sp8 = NULL;
                }
                sp8 = nxt;
                if (sp8 != NULL) {
                    CObject_AddRefLink(sp8, &sp8);
                }
            } while (sp8 != NULL);
        }
    } else {
        ((Ck_t *)&sp8)->prev = flag;
        ((Ck_t *)&sp8)->next = flag;
        sp8 = arg0->head;
        if (sp8 != NULL) {
            CObject_AddRefLink(sp8, &sp8);
        }
        if (sp8 != NULL) {
            f32 mxb = CF("r9", lbl_80292AE8, 0x2AE8);
            f32 e4b = CF("r11", lbl_80292AE4, 0x2AE4);
            mx = mxb; t1 = e4b;
            do {
                if (arg0->f_1A8 != 0) {
                    prod = ((Node *)sp8)->f_17C * arg0->f_1B0 * mx;
                    CScreenElement_SetJust(sp8, arg0->f_1A0, lbl_80292ADC);
                    acc = acc + prod;
                    CScreenElement_SetPos(sp8, 1, (arg0->f_1A0 + t1) * arg0->f_178 * mx, acc);
                } else {
                    prod = ((Node *)sp8)->f_178 * arg0->f_1B0 * mx;
                    CScreenElement_SetJust(sp8, lbl_80292ADC, arg0->f_1A4);
                    acc = acc + prod;
                    CScreenElement_SetPos(sp8, 1, acc, (arg0->f_1A4 + t1) * arg0->f_17C * mx);
                }
                acc = acc + prod;
                acc = acc + arg0->f_1B4;
                if (((Node *)sp8)->f_0C & 0x400) {
                    arg0->f_0C = arg0->f_0C | 0x400;
                }
                nxt = (s32 *)((Node *)sp8)->next;
                if (sp8 != NULL) {
                    CObject_RemoveRefLink(sp8, &sp8);
                    sp8 = NULL;
                }
                sp8 = nxt;
                if (sp8 != NULL) {
                    CObject_AddRefLink(sp8, &sp8);
                }
            } while (sp8 != NULL);
        }
    }
    if (sp8 != NULL) {
        CObject_RemoveRefLink(sp8, &sp8);
        sp8 = NULL;
    }
    nxt = (s32 *)arg0->f_194;
    if ((nxt == NULL) && (arg0->head != NULL) && (arg0->f_198 != 0)) {
        arg0->f_190 = (s32)nxt;
        fn_8004E734(arg0, 1, 1, 1);
        if (arg0->f_194 != 0) {
            CStruct_ctor(&sp8);
            AddInteger(&sp8, QB_CONTROLLER, arg0->f_19C);
            fn_800A54AC(lbl_80301A78, QB_FOCUS, arg0->f_194, QB_SYSTEM, &sp8, 0, lbl_80292AEC);
            CStruct_delete(&sp8, 2);
        }
    }
    __asm__("" : : "m"(p0), "m"(p1), "m"(p2), "m"(p3), "m"(p4), "m"(p5),
            "m"(p6), "m"(p7), "m"(p8), "m"(p9));
    __asm__("" : : "m"(p10));
}
