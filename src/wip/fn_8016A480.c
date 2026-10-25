// RE-TRIAGED 2026-10-19: sweep NEAR 89.8%, size-exact — residuals B1/B2/C1
// stand (all post-front-end; levers in this header remain exhausted).
// Parked as-is.
// PARKED 2026-10-30: 70.1% -> 86.6%
// REFRESHED 2026-10-07 (pin-RETARGET sweep): 88.9764% -> 89.7638%
//   the SECOND `t3` pin was retargeted r3 -> r5 (nothing else touched); 508B == symbol.  From the pin-RETARGET sweep, AGENTS-recipes §6hk.
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 86.6142% -> 88.9764% per-object flags: -O1 -> -fno-gcse
// WIP DRAFT (non-matching) — LoadAllStartupQBFiles
// family=m2c range=0x8016A480-0x8016A67C size=508B
// FLAG: -fno-gcse
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// STATE: PARKED at 86.6% (official test_wip_drafts, object .text = 0x1FC =
// 508 B = symbols.txt size:0x1FC = the header marker; size-exact, so the
// masked score is meaningful). 0 inline asm, 0 emitted instructions.
//
// THIS ROUND'S THREE LOAD-BEARING EDITS (all three are needed — it is an
// AND, AGENTS §6bf-A; ablations in the log below):
//
//  (A) W 8016A494 lwz r3,-0x168(r9)  <- the lbl_802FFE98 load lands in the
//      ARG register;  G  lwz r9,0(r9) / mr r3,r9  <- reload coalesces
//      dest==base onto the page anchor.  FIX: a NESTED-SCOPE hard pin
//      `register s32 a0 __asm__("r3")` on the loaded value.  §6cs-2: nested
//      scope is required — at function scope cc1 re-births the value
//      directly into rN and the whole prologue/allocation moves (25.2%,
//      504B).  The pinned value is the callee's own arg0, so §72-143's
//      "arg registers for call arguments" is what the pin buys.
//      NOTE: the promoted byte-identical TWIN src/fn_80012C28.c
//      (ScriptLoadPipPre, `rg Pip_LoadPre src/`) uses the *identical*
//      spelling `fn_8000F2F8((void *)lbl_802FFE98,
//      ((Unk_9994C3F5 *)lbl_802FFE98)->unk0x118)` and needs no pin — its
//      call is inside a switch arm, not the entry block.  L1 (§6bc-1,
//      `extern T *lbl` + bare use) is therefore NOT the lever here and was
//      measured inert (a3 = 70.1%, byte-identical).
//
//  (B) `lbl_802A8974`'s address is live ACROSS `bl fn_8000F320` in want
//      (lis r30 at 8016A4EC, first use 8016A508), so the page anchor is a
//      callee-saved r30 materialised BEFORE that call.  FIX (§6eg's
//      page-anchor rule + §6et): give the address its own named local
//      `s32 a = (s32)lbl_802A8974;` placed BEFORE `fn_8000F320`, and use
//      `a` at BOTH call sites.  §6et: a statement the SOURCE writes in the
//      setup region keeps its position; without the local the anchor is
//      rematerialised at the first use, i.e. AFTER the call (base).
//      Ablation x1 (drop the local, keep the other two) = 504B / 25.2%.
//
//  (C) the strstr result: the want tests the r3 result in place, branches,
//      derives the plus-5 pointer into a fresh fourth register, and only
//      then restores the base into r3 from r30. The got instead tests into
//      r4, restores r3 from r30 first, and derives the plus-5 value from r4
//      itself — got coalesces the addition into the copy and colours it r4.
//      FIX (§6dp-3): a
//      NESTED-SCOPE `register s32 t3 __asm__("r3")` on the strstr result, so
//      the result lives in r3 (the test register want uses) and the `+5`
//      gets a fresh r4.  Ablation s1 (drop this pin, keep A and B) = 84.3%.
//
// WHAT IS STILL LEFT (3 windows, all post-front-end / expand_call, all
// proven by the post-reload RTL dump cited in the previous round):
//
//  (B1) fn_800127E4 arg-setup EMISSION order.
//      The want emits the four constant immediates for the second, third,
//      fourth, and fifth parameters first and the symbol-derived address for
//      the first parameter last; the got emits the address first and the
//      four constants after.
//      §6dl (permute the C arg list) cannot reach it: all five params are
//      `s32`, so value->register mapping and list order are the same axis.
//      5 permutations measured: 72.44% / 73.23% — all worse.  The post-
//      reload RTL already has GOT's order, so this is expand_call's
//      front-end order.
//
//  (B2) want `mr r0,r3; mr r31,r0` (two web boundaries) vs got
//      `mr r31,r3`.  The RTL shows ONE virtual reg after the call, so both
//      copies are allocation artifacts.  ~30 shapes measured for a +1 word:
//      named s32/u8*/char*/void* temps, 2- and 3-name chains, (u8*)(s32)
//      and (void*) round-trips, `+r` barriers on the result and on
//      var_r31, `=r`/`=&r`/`volatile` `mr` wedges, r0 and r31 register-var
//      pins (nested and function scope), a re-read of the value after the
//      call, keeping the result live across fn_80012AB4 (it loses 2 words
//      instead), var_r31 declared `s32` with casts at the use sites.
//      EVERY one of them is 504B (want-1) or 496B — the extra copy is
//      unreachable.  This is the single reason the object is not 508B with
//      both A and C fixed; A and C together cost one word that only this
//      window can give back.
//
//  (C1) the loop preheader anchor order: the want orders the r28 page
//      anchor, the zeroing of r11, the compare, and then the r1+8 derivation
//      into r30; the got leads with the r1+8 derivation and only then emits
//      the page anchor, the zeroing, and the compare.
//      §6et would want the lbl_802A8988 address written in the loop-setup
//      region — but naming it at all adds a word (512B) in BOTH placements
//      (t1 setup region 25.8%, t2 body 27.3%), which is §6ew's trap: a
//      named local is a NEW def with its own block.  Forcing the birth with
//      a volatile `lis` anchor pinned to r28 (1 insn == want's own `lis`)
//      also costs: u1/u4 = 83.5%.
//
// LEVERS MEASURED AND INERT (byte-identical object unless noted):
//  -O2 65.35 / size -44 ; -O3 65.35 / -44 ; -Os 55.91 / -44
//  -O1 + -fno-gcse / -fno-schedule-insns / -insns2 / -sched-spec /
//        -sched-interblock / -fno-thread-jumps / -fno-expensive-optimizations
//        / -fno-cse-follow-jumps          73.23 size +0 (9 flags)
//  (A) 24 declaration forms of lbl_802FFE98 (extern s32 / T * / void *),
//      arg0 bare vs (void *) vs pointer-typed, fn_8000F2F8 proto
//      (T*,s32)/(s32,s32)/(void*,s32), arg0/arg1 from one named local vs
//      the bare symbol, field hoisted into an s32 temp, field via
//      `*(s32 *)((char *)cur + 0x118)`, char* local, volatile load,
//      asm birth of the lwz, `+r` barrier on the loaded value, second name
//      for the field, `=r`/`=&r`/volatile `mr` wedges on the B2 result,
//      hard pins r0/r3/r4/r9/r10/r31            -> 70.1% (inert) or 504B
//  L1 on lbl_802FFE98 (extern T * + bare use, §6bc-1)        70.1% (inert)
//  L1 on lbl_802A8974 via a named `s32` / `char *` local   508B but the
//      extra word lands as `addi r30,r30,0; mr r3,r30` (want folds the @l
//      into each use instead)  -> 85.0%
//  fn_800127E4: 5 arg-list permutations 72.44/73.23 ; varargs proto 73.23
//      size +4 ; old-style proto 73.23 size +4 ; void proto = compile FAIL
//      ("void value not ignored") ; return type s32/u32/void*/char*/long
//      all identical
//  fn_80012AB4 arity/return-type matrix, fn_8000F2F8 proto matrix,
//      fn_8000F320 proto matrix: all inert
//  (a local `strcpy` declaration is a hard FAIL: "conflicting types for
//   built-in function 'strcpy'" with a nonzero exit — keep it implicit)
//
// AUDIT of the 86.6% body: object .text = 0x1FC = 508 B = symbols.txt
// size:0x1FC = header marker; only .text + .rela.text (no private
// .rodata, so no doc-14 pool caveat); 0 __asm__ statements / 0 .long /
// 0 emitted instructions (the 3 `register ... __asm__("rN")` declaration
// attributes cost nothing).  The 8 externs hand-decode from want's
// lis/addi pairs: 0x802A8944/954/964/974, 0x802A8988 (= 0x802B0000-0x7678),
// 0x802FFE48, 0x802FFE98, 0x802FFE38 (= 0x802F0000-0x1b8), all real
// config/G2TE52/symbols.txt entries, so the masked-100%-wrong-label hazard
// (277) cannot apply.  Branch displacement AUDIT NOT PASSED: the object is
// not byte-identical, so the §6bw REL14 addend check is not meaningful yet
// (the remaining diffs are permutation-only, no control-flow change).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_80012A10(s32 arg0);
void fn_800181A4(void *, void *);
void fn_8016A67C(s32 arg0, s32 arg1);
unsigned int fn_8000A778(const char *str);
void fn_8000F2F8(Unk_9994C3F5 *, s32);
void fn_8000F320(Unk_9994C3F5 *);
void Pip_LoadPre(s32);
s32 fn_800127E4(s32, s32, s32, s32, s32);
s32 fn_80012AB4(s32);
void fn_800126DC(s32);
void fn_8012515C(void);
void UseRegularStringHeap(void);
void fn_8016A6E4(void);
s32 fn_8012543C(s32);
s32 fn_8012DE30(s32);
char *strstr(char *, char *);
extern char lbl_802A8944[];
extern char lbl_802A8954[];
extern char lbl_802A8964[];
extern char lbl_802A8974[];
extern char lbl_802A8988[];
extern s32 lbl_802FFE48;
extern s32 lbl_802FFE98;
s32 LoadAllStartupQBFiles(void) {
    u8 sp8[0xCC];
    s32 language;
    s32 temp_r30;
    s32 var_r11;
    s32 var_r3;
    s32 zero;
    u8 *temp_r0_2;
    u8 *var_r29;
    u8 *var_r31;
    u8 var_r9;
    char *temp_r3_2;

    /* (A) lbl_802FFE98 must land in the arg register, not coalesce onto r9. */
    {
        register s32 a0 __asm__("r3");
        a0 = (s32)lbl_802FFE98;
        fn_8000F2F8((void *)a0, ((Unk_9994C3F5 *)a0)->unk0x118);
    }
    language = lbl_802FFE48;
    switch (language) {
    case 3:
        Pip_LoadPre((s32)lbl_802A8944);
        break;
    case 5:
        Pip_LoadPre((s32)lbl_802A8954);
        break;
    default:
        Pip_LoadPre((s32)lbl_802A8964);
        break;
    }
    /* (B) lbl_802A8974's page anchor is live across bl fn_8000F320. */
    {
        s32 a = (s32)lbl_802A8974;
        fn_8000F320((void *)lbl_802FFE98);
        var_r31 = (u8 *)fn_800127E4(a, 0, 0, 0, 0);
        temp_r30 = fn_80012AB4(a);
    }
    fn_8012515C();
    temp_r0_2 = &var_r31[temp_r30];
    if (var_r31 < temp_r0_2) {
        var_r29 = temp_r0_2;
        zero = 0;
        do {
            u8 *dst = &sp8[0];
            var_r11 = 0;
            if (var_r31 < var_r29) {
                var_r9 = *var_r31;
                if (((s8)var_r9 != 0xD) && ((s8)var_r9 != 0xA)) {
                    u8 *w = dst;
                    goto loop_12;
                loop_12:
                    w[var_r11] = var_r9;
                    var_r31 += 1;
                    var_r11 += 1;
                    if (var_r31 < var_r29) {
                        var_r9 = *var_r31;
                        if ((s8)var_r9 != 0xD) {
                            if ((s8)var_r9 != 0xA) {
                                goto loop_12;
                            }
                        }
                    }
                }
            }
            dst[var_r11] = zero;
            var_r31 += 1;
            if (sp8[0] != 0) {
                /* (C) the strstr result must stay in r3 so `+5` gets a new r4. */
                {
                    register s32 t3 __asm__("r5");
                    t3 = (s32)strstr(dst, lbl_802A8988);
                    if (t3 != 0) {
                        strcpy(dst, (char *)(t3 + 5));
                    }
                }
                fn_8000A778(dst);
                fn_8016A6E4();
                fn_8016A67C((s32)dst, 1);
            }
            fn_800181A4(0, 0);
        } while (var_r31 < var_r29);
    }
    UseRegularStringHeap();
    fn_80012A10((s32)lbl_802A8974);
    language = lbl_802FFE48;
    switch (language) {
    case 3:
        fn_800126DC((s32)lbl_802A8944);
        break;
    case 5:
        fn_800126DC((s32)lbl_802A8954);
        break;
    default:
        fn_800126DC((s32)lbl_802A8964);
        break;
    }
    var_r3 = fn_8012543C(QB_DEBUGGER_NAMES);
    if (var_r3 != 0) {
        var_r3 = fn_8012DE30(var_r3);
    }
    return var_r3;
}
