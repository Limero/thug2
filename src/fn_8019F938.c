// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019F938-0x8019FB9C (612B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct CStruct CStruct;

// .rodata2 float literals. `const` on lbl_802AAFD8 is LOAD-BEARING: with a
// plain `extern f32` ngccc schedules `stfs f0,0x12c(arg0)` BEFORE
// `lfs f1,lbl@l(r9)` and the two words swap; `const` restores the want's
// load-then-store order (recipes 362 / 14497 / 16272 re-confirm `const` is the
// CORRECT declaration for a data:float .rodata2 symbol).  Adding `const` to
// lbl_802AAFDC / lbl_802AAFE0 as well REGRESSES to 624B/141 diffs — only the
// one that feeds the first `stfs`/`lfs` pair matters.
extern const f32 lbl_802AAFD8;
extern f32 lbl_802AAFDC;
extern f32 lbl_802AAFE0;

void *GetChecksum_3(void *, s32);
void fn_8019F830(void *, f32);
void fn_800CBBC4(void *, f32);
void fn_800CBB74(void *);
void fn_800CC078(void *, s32);
void fn_800CB498(void *);
void *CStruct_new(s32);
s32 CStruct_ctor(s32);
void fn_8012772C(void *, s32, f32);
void CStruct_delete(void *, s32);

void fn_8019F938(void *arg0, s32 arg1) {
    CStruct *c_then;
    CStruct *c_else;
    s16 off;
    void *node;
    void **t;
    void (*fp)(void *, s32, void *, s32);

    if (*(s32 *)((char *)arg0 + 0x134) == 0) {
        *(f32 *)((char *)arg0 + 0x12C) = *(f32 *)((char *)arg0 + 0x128);
        fn_8019F830(arg0, lbl_802AAFD8);
    }
    if (GetChecksum_3(arg0, 0x7149B753) != NULL) {
        if (arg1 != 0) {
            fn_800CBBC4(GetChecksum_3(arg0, 0x7149B753), lbl_802AAFDC);
            fn_800CBB74(GetChecksum_3(arg0, 0x7149B753));
            c_then = (CStruct *)CStruct_ctor(CStruct_new(8));
            fn_8012772C((void *)c_then, 0x06C9F278, lbl_802AAFDC);
            node = GetChecksum_3(arg0, 0x7149B753);
            t = *(void **)((char *)node + 0x18);
            fp = (void (*)(void *, s32, void *, s32))t[0x19];
            off = ((s16 *)t)[0x30];
            fp((char *)node + off, 0x6AAEB76F, c_then, 0);
            if (c_then != NULL) {
                CStruct_delete(c_then, 3);
            }
        } else {
            fn_800CC078(GetChecksum_3(arg0, 0x7149B753), 0);
            fn_800CBBC4(GetChecksum_3(arg0, 0x7149B753), lbl_802AAFE0);
            fn_800CBB74(GetChecksum_3(arg0, 0x7149B753));
            fn_800CC078(GetChecksum_3(arg0, 0x7149B753), 0);
            node = GetChecksum_3(arg0, 0x7149B753);
            t = *(void **)((char *)node + 0x18);
            fp = (void (*)(void *, s32, void *, s32))t[0x19];
            off = ((s16 *)t)[0x30];
            fp((char *)node + off, 0xF5E2B871, 0, 0);
            c_else = (CStruct *)CStruct_ctor(CStruct_new(8));
            fn_8012772C((void *)c_else, 0x06C9F278, lbl_802AAFE0);
            node = GetChecksum_3(arg0, 0x7149B753);
            t = *(void **)((char *)node + 0x18);
            fp = (void (*)(void *, s32, void *, s32))t[0x19];
            off = ((s16 *)t)[0x30];
            fp((char *)node + off, 0x6AAEB76F, c_else, 0);
            if (c_else != NULL) {
                CStruct_delete((void *)c_else, 3);
            }
            node = GetChecksum_3(arg0, 0x7149B753);
            t = *(void **)((char *)node + 0x18);
            fp = (void (*)(void *, s32, void *, s32))t[0x19];
            off = ((s16 *)t)[0x30];
            fp((char *)node + off, 0xF5E2B871, 0, 0);
        }
        fn_800CB498(GetChecksum_3(arg0, 0x7149B753));
    }
    *(s32 *)((char *)arg0 + 0x134) = 1;
}

// ── Reconstruction notes ────────────────────────────────────────
// Semantics recovered from the want at 0x8019F938 (612B / 153 insns):
//   * The 0x134 field is a "did the 0x7149B753 subtree already run" latch: it
//     guards a one-shot `field_0x12C = field_0x128; fn_8019F830(this, 0.0f)`
//     prologue, and it is set to 1 on EVERY exit path at the tail.
//   * `arg1` selects between two QUANTUM push sequences built around
//     `CStruct_new(8)` + `CStruct_ctor` + `fn_8012772C(obj, 0x06C9F278, dt)`,
//     where dt = lbl_802AAFDC (1/60) for arg1!=0 and lbl_802AAFE0 (-1/60) for
//     arg1==0.  The else arm brackets that push with two 0xF5E2B871
//     vtable calls and one 0x6AAEB76F.
//   * `fn_8012772C` is 3-arg (obj, tag, f32) — the draft had dropped the
//     object arg, which put the tag in r3 instead of r4.
//   * Every vtable dispatch is `fp = t[0x19]` (`t+0x64`) with the receiver
//     `node + (s16)t[0x30]` — a SIGNED 16-bit field at `t+0x60`, so the
//     `off` local is typed `s16` (the `lha`, recipes "the s16 (lha) fix").
//   * `off` is a NAMED s16 local rather than an inline `((s16 *)t)[0x30]`:
//     the inline form makes ngccc re-materialise the vtable pointer and
//     costs the want's single `lha r0,0x60(r9)` / `add r3,r3,r0` pair.
//   * The two CStruct temporaries are SEPARATE variables (`c_then`/`c_else`),
//     not one shared `temp_r29`.  With a single shared temp ngccc's global
//     register allocator gives arg0 r29 and arg1 r31 (the whole prologue
//     permutation flips); with per-branch temps it produces the want's exact
//     `mr r31,r3 / mr r30,r4 / stmw r29` mapping.  Verified by bisection:
//     collapsing either branch to the shared temp reproduces the wrong
//     prologue, and per-branch temps reproduce the right one at every body
//     size from 292B (empty else) to 612B (full body).
//
// Hand verification of the masked-out fields (per AGENTS §5):
//   * Every REL24 (`bl`) target in the want is one of the 11 real callees
//     (0x8009fdd8 GetChecksum_3, 0x800cbb74, 0x800cbbc4, 0x800cb498,
//     0x800cc078, 0x80019d08 CStruct_new, 0x80126eac CStruct_ctor,
//     0x8012701c CStruct_delete, 0x8012772c, 0x8019f830) — no computed or
//     mid-function targets, and the single `blrl` sites are the vtable
//     dispatches (mtlr from `t[0x19]`, never mtctr).
//   * The three `lis`/`lfs` pairs resolve to 0x802AAFD8 / 0x802AAFDC /
//     0x802AAFE0 (ha 0x802B0000 + negative lo -0x5028/-0x5024/-0x5020), i.e.
//     the three shipped .rodata2 symbols in symbols.txt:17698-17700.
//   * The two hash literals are 0x7149B753 / 0x06C9F278 / 0x6AAEB76F /
//     0xF5E2B871 built by lis+ori pairs.
//   * All four REL14 branches land on real basic-block starts inside the
//     0x8019F938-0x8019FB9C range.
