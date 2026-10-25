// PARKED 2026-10-05 — CONFIRMS the family wall. Do not re-run the ladder:
// this is the CR-field loop condition of AGENTS-recipes.md §"The CR-field loop
// condition (doc 28 / §6t-2 / §7a-133 family)" (~line 14430) and of
// docs/parkings/28-*: want keeps the loop-invariant fn_8013E2BC result in a
// callee-saved CONDITION-CODE field (mcrf cr4,cr0 ... latch `bgt cr4`), the
// cc1 -dr post-reload RTL is IDENTICAL in the working and failing variants,
// and the only difference is which hard register local-alloc hands the CR
// pseudo.  That recipe's operational rule applies verbatim: "if the post-
// reload RTL already matches and the only diff is which hard reg a pseudo
// gets, the blocker is local-alloc — park it, do not run a source/flag
// ladder."  The reduction/§4c-style sub-experiments named under "NEXT TO
// TRY" below were all part of that exhausted ladder; the doc-28 case
// fn_801392BC (~0x801392BC) is the same wall.
//
// WIP DRAFT (non-matching) — hand-rebuilt from the disasm; 81 consecutive
// instructions are byte-identical, the residual is one CR-save feature.
// Re-measured 2026-10-05: the object is 4 words SHORT (400 B vs 416 B), so the
// shift-0 sweep number is meaningless (2.9%).  At the best alignment (-3 words)
// the residual is 44/104 words, i.e. the "8 words differ" line further down is
// stale.  No body edit changed these numbers.
// family=m2c range=0x80138BA0-0x80138D40 size=416B
// INERT: not registered in splits.txt/configure.py — never compiled, not
// counted in objdiff progress.
//
// ---------------------------------------------------------------------------
// 2026-09-30 (pick, was 29.8% as the inherited m2c body — the file on
// disk when this pick started FAILED to compile; the "44.2%" in the old header
// was never re-measured and does not reproduce).
//
// FINAL: 2.0% masked / 400 B object vs 416 B want (4 instructions SHORT).
//        The object is 4 words short, so the masked compare is mis-aligned and
//        the 2.0% is a SHIFT ARTEFACT, not the true quality: 81 consecutive
//        instructions (0x80138BD4..0x80138C74 and 0x80138C80..0x80138D1C)
//        are byte-identical and only 8 words differ anywhere.
//
// CALLEE AUDIT (from each callee's own prologue; all are stwu-first = ProDG):
//   fn_8013E2BC  1-arg, s32  (leaf: lwz 0x2274(r3); li r3,1/0)
//   fn_8013BC8C  3-arg, ptr  (reads r3; cmpw r0,r4 / cmpw r0,r5)
//   fn_8013F708  1-arg, s32  (leaf: li r3,1; andi.; xori r3,r3,1)
//   fn_8013B5C4  4-arg, s32  (mr r29,r5; cmpwi r6,2; lhz r0,0(r4) -> r4 READ)
//   fn_80137364  3-arg, s32  (mr r31,r3; mr r29,r4; mr r28,r5)
//   fn_800145AC  1-arg, s32  (leaf, mflr-free; returns lwz 0xc(r1))
//   fn_8013BE28  4-arg, ptr  (mr r30,r3; mr r28,r4; mr r27,r5; mr r29,r6)
//   fn_8013EA38  2-arg, void (mr r30,r3; mr r26,r4)
//   fn_8013F6E4  1-arg, void (leaf, writes 0x68(r3))
// Two fixes fell out of the audit and are load-bearing:
//   * fn_8013B5C4 is 4-arg.  At the FIRST call site WANT sets r3/r4/r6 and
//     leaves r5 holding the already-loaded 0x60(node) from the range compare,
//     so the source passes `node->unk0x60` (CSE'd, no extra insn) — passing 0
//     there would emit a spurious `li r5,0`.
//   * `bl fn_80137364` has NO r3 setup before it, so the source is the CHAIN
//     fn_800145AC(fn_80137364(...)) (recipe 23 / §6bh).  fn_80137364 must be
//     declared s32-returning for r3 to stay live.
//
// STRUCT TYPES (file-local; the corpus classes are wrong for this function):
//   * `sp8_t` = the 8-byte frame local at r1+8: `stb 8` at +0 and an
//     UNWRITTEN word read at +4 (lwz r4,4(r28) / lwz r4,0xc(r1)).
//   * `N` (the node from fn_8013BC8C / fn_8013BE28): fields at 0x5C, 0x60,
//     0x70, 0x74.  The first draft had `char _q[0x8]` after unk0x60, which
//     put unk0x70/0x74 four bytes high (stw 0x78/0x74 instead of 0x74/0x70)
//     -- the §6dy "every interior gap is an explicit char pad" rule.
//   * `Unk_440CB216` re-declared locally with the 0x2270 pad so that 0x2274 and
//     0x2278 land right (the header class is right here, but the local copy
//     keeps the file self-contained and pins the 0x2278 slot as s32).
//
// EXPERIMENT LOG (masked % is the official shift-0 number; "aligned" is the
// residual after a +/-3 word re-alignment, i.e. the true diff count):
//   inherited m2c body (re-measured, undeclared callees added back)  29.8%
//   44.2% header claim ......................... DOES NOT REPRODUCE (see above)
//   hand rebuild, plain C, m2c field types .................... 3.0% / 59 @-4
//   + correct N layout (pad 0x8 -> 0x4) ........................ 3.0% / 53
//   + named &sp8 in a local (want's r28) ...................... 2.0% / 53
//   + hard pin  var_r27 -> r27 ................................ 2.0% / 45
//   + hard pin  &sp8     -> r28 (both pins together) .......... 2.0% / 45
//   + sp8's +4 word read via the pinned &sp8 pointer ........... 2.0% / 44
//   m2c's `do{}while(0)` -> `do{}while(c > 0)` (real back edge) 2.0% / 44
//   callee proto sweep on fn_80137364 (8 param-type variants) .. 2.0% / 44
//   two-statement fn_80137364/fn_800145AC instead of the chain  2.0% / 44
//   volatile sp8_t / named fp local / void* node / node2 reuse  no change
//   ~43 ngccc -f flags + every -O level ....................... no change
//
// RESIDUAL (the ONLY difference; everything else is byte-identical). At
// 0x80138BA8 the original saves the condition register into r12. At 0x80138BAC
// it saves r27 upward at frame offset 0x14, where this draft saves r26 upward
// at offset 0x10. At 0x80138BB4 it spills r12 at frame offset 0x10. At
// 0x80138BC8 it compares r3 against zero, where this draft instead ORs r3 with
// itself into r26 and records the condition. At 0x80138BD0 it moves condition
// field cr0 to cr4. At 0x80138C7C it loads 0x1c into r4, where this draft emits
// the same load two instructions earlier. At 0x80138D20 it branches on cr4
// greater-than back to 0x80138BD4, where this draft compares r26 against zero
// and branches greater-than to 0x80138D40. At 0x80138D28 it reloads r12 from
// frame offset 0x10. At 0x80138D30 it restores r27 upward from offset 0x14,
// where this draft restores r26 upward from 0x10. At 0x80138D34 it restores
// condition field 8 from r12.
//
// BLOCKER (one cause, 5 words): WANT keeps the LOOP CONDITION in a callee-
// saved CONDITION-CODE FIELD (cr4) instead of a callee-saved GPR.  The loop
// condition is the loop-invariant result of fn_8013E2BC, evaluated once in
// the preheader; the latch is `bgt cr4` (signed compare of the 4-bit CR field
// against 0), and because calls in the body clobber the CR, GCC has to
// mfcr/mtcrf it (doc 28 / §6t-2 / §7a-133 family).  Here GCC instead keeps
// `c` in r26 and re-materialises the compare in the latch.
//
//   * The spelling of the latch IS reachable in isolation: a standalone probe
//     proves `c > 0` -> `bgt cr4`, `c == 0` -> `beq cr4`, `c < 0` -> `blt cr4`,
//     i.e. any relational operator selects the branch, and a stripped-down
//     version of THIS function (first branch only) really does emit
//     `mfcr r12 / stw r12,0x10(r1) / cmpwi r3,0 / bne / mcrf cr4,cr0 ... /
//     bgt cr4` -- the exact WANT shape.
//   * Adding the `else` branch (`node2` path) loses it, and it is lost
//     CUMULATIVELY: single-line ablations of the full body never restore it,
//     while each of three individual sub-blocks (`if (b5c4(...)==0){}else{}`,
//     `node2->unk0x60 = ...; fn_8013F6E4(node2);`, the 3-arg vcall) loses it
//     on its own.  A single empty `else` arm does NOT.
//   * `cc1 -dr` (post-reload RTL) is IDENTICAL in the working and the failing
//     variant: the same `(set (reg:CC 93) (compare:CC (reg:SI 92) 0))` at insn
//     35 and the same `(jump_insn ... (if_then_else (eq (reg:CC 93) 0) ...))`
//     latch, with ONE use of reg 92 and ONE use of the CR pseudo.  So the
//     difference is purely local-alloc's choice of a hard CR field for that
//     pseudo vs. re-materialising the compare off a GPR -- an allocator
//     decision no source spelling, declaration order, flag, or PROTOTYPE
//     touches.  Per §6bz/§6ek the honest conclusion is an allocator coin-flip,
//     not a codegen wall: there is no flag, order or cast that reaches it.
//
//   Exhausted for this body: every loop shape (while / for / do-while /
//   goto-labels / early-return guard / `for(;;)+break` / latch polarity
//   sweep of 14 conditions), ~43 -f flags and -O0/1/2/3/Os, `volatile` on
//   the frame local, a named `fp` for the callback, `void *` vs struct-typed
//   `node`, reusing one variable for `node`/`node2`, dropping the
//   `var_r27`/`&sp8` hard pins, re-declaring fn_8013E2BC as returning
//   `void *`/`u32`, and the `c` variable being pointer- vs int-typed.
//
// NEXT TO TRY: (1) a `cc1 -da`/machine-desc dump to see whether the ProDG
// target's `reg_alloc_order` for CRmode is short -- if only one or two CR
// fields are offered, the CR pseudo loses whenever the body needs a third
// concurrent compare, and the fix would be to reduce simultaneous CR
// pressure (e.g. hoist one of the two `andi. r0x20` tests).  (2) Reduce
// simultaneous CR demand: the two `arg0->unk0x2274 & 0x20` tests and the two
// `fn_8013B5C4(...) == 0` compares each want cr0; if some could share a
// field the CR form may come back.  (3) The one remaining non-CR word is the
// `li r4,0x1c` / `addi r3,r31,0x20ec` arg-setup order at 0x80138C78
// (doc-15 class) -- try §6dl-1's permuted-parameter-list trick on the
// fn_80137364 call, or `-fno-schedule-insns2`.
// ---------------------------------------------------------------------------

typedef struct { s8 a; char _p[3]; s32 b; } sp8_t;

typedef struct Unk_440CB216 {
    s32 unk0x0;
    char pad0x4[0x2270];
    s32 unk0x2274;
    s32 unk0x2278;
} Unk_440CB216;

typedef struct N {
    char _p[0x5C];
    s32 unk0x5C;
    s32 unk0x60;
    char _q[0x4];
    s32 unk0x68;
    s32 unk0x6C;
    s32 unk0x70;
    s32 unk0x74;
} N;

s32 fn_8013E2BC(void *);
void *fn_8013BC8C(void *, s32, s32);
s32 fn_8013F708(void *);
s32 fn_8013B5C4(void *, void *, s32, s32);
s32 fn_80137364(void *, s32, s32);
s32 fn_800145AC(s32);
void *fn_8013BE28(void *, void *, s32, s32);
void fn_8013EA38(void *, s32);
void fn_8013F6E4(void *);

void fn_80138BA0(Unk_440CB216 *arg0) {
    sp8_t sp8;
    N *node;
    N *node2;
    void *temp_r29;
    register s32 sp8p __asm__("r28");
    register s32 var_r27 __asm__("r27");
    s32 c;

    sp8.a = 8;
    c = fn_8013E2BC(arg0);
    if (c == 0) {
        do {
            var_r27 = 0;
            if (arg0->unk0x2274 & 0x20) {
                var_r27 = -2;
            }
            sp8p = (s32)&sp8;
            node = fn_8013BC8C(arg0, *(s32 *)((char *)sp8p + 4), 0);
            if (node != NULL) {
                if (((fn_8013F708(node) != 0) || !(arg0->unk0x2274 & 0x20)) &&
                    ((u32)(node->unk0x60 + var_r27) < (u32)(node->unk0x5C + 0xA28))) {
                    if (fn_8013B5C4(arg0, (void *)((char *)arg0 + 0x1D60), node->unk0x60, 0) == 0) {
                        if (arg0->unk0x2278) {
                            ((s32 (*)(s32, s32, sp8_t *))arg0->unk0x2278)(node->unk0x60, 0, sp8p);
                        }
                    } else {
                        node->unk0x60 = node->unk0x60 + var_r27;
                        node->unk0x74 = fn_800145AC(fn_80137364((void *)((char *)node + 0x20EC), 0x1C, arg0->unk0x0));
                    }
                }
            } else {
                node2 = fn_8013BE28(arg0, *(void **)((char *)sp8p + 4), 0, 6);
                if (node2 != NULL) {
                    node2->unk0x70 = (s32)arg0;
                    temp_r29 = (void *)((char *)arg0 + 0x1D60);
                    if (fn_8013B5C4(arg0, temp_r29, node2->unk0x60, 0) == 0) {
                        if (arg0->unk0x2278) {
                            ((s32 (*)(void *, s32, sp8_t *))arg0->unk0x2278)(temp_r29, 0, sp8p);
                        }
                        fn_8013EA38(node2, 3);
                    } else {
                        node2->unk0x60 = node2->unk0x5C + var_r27;
                        fn_8013F6E4(node2);
                    }
                }
            }
        } while (c > 0);
    }
}
