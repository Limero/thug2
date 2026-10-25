// WIP DRAFT (non-matching) — hand-rebuilt from the disassembly, 2026-09-30
// family=m2c range=0x8004BEB0-0x8004BFE4 size=308B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-10-30: 51.9% -> 87.0%. SIZE exact — object
// .text = 0x134 = 308 B = symbols.txt `size:0x134` = header range.
// 67/77 words match under the relocation mask; 10 diffs in 3 clusters.
//
// WHAT THE FUNCTION IS (decoded from 0x8004BEB0):
//   arg0 is a `Lnk` (12-byte intrusive-list link {unk0x0=object,
//   unk0x4=next, unk0x8=prev}); the return value is arg0.  arg1 (r4) is
//   never read.  Walk the list from `(*arg2)->unk0x64` held in a stack
//   `Lnk sp`; while sp.unk0x0 != NULL, call
//   fn_8009E408(node, QB_TAG_LOCAL_ID /*0x9494A525*/, &v); on a hit copy
//   the node into arg0, AddRefLink it, then jump to the shared cleanup
//   guard; otherwise next = node->unk0x70, RemoveRefLink, sp.unk0x0 = next,
//   AddRefLink(next).  The shared tail zeroes arg0->{4,8,0} and then
//   RemoveRefLinks whatever is left in sp.  Callee arities audited against
//   the promoted twins: CObject_AddRefLink/CObject_RemoveRefLink 2-arg
//   (src/fn_8009DFA0.c, src/fn_8009DFC0.c), fn_8009E408 3-arg
//   (src/fn_8009E408.c).  QB_TAG_LOCAL_ID re-decoded by hand from
//   lis -0x6b6c | ori 0xa525 = 0x9494A525 (matches qb_constants.h).
//
// THE TWO EDITS THAT MATTERED THIS ROUND (51.9% -> 87.0%):
//  (1) MATCH-ARM ZERO MUST BE ITS OWN BIRTH, NOT THE LOOP-HOISTED ONE.
//      want has THREE zero births: r27 (loop preheader), r31 (match arm),
//      r31 (tail).  A bare `arg0->unk0x4 = NULL; arg0->unk0x8 = NULL;`
//      made local-alloc share the loop's r27 with the match arm, which
//      dropped want's `li` and shifted 1 word.  An OPAQUE asm birth with
//      a LOOP-VARIANT input is the only form that (a) is not folded back
//      to the constant pool and (b) is not hoisted into the preheader:
//          __asm__("li %0,0" : "=r"(zm) : "r"(a3));
//      Measured: bare NULL 51.9% | opaque, no input 56.4% (hoisted to the
//      preheader -> new r26 callee-saved home) | opaque VOLATILE, no
//      input 71.8% | opaque + "r"(a3) input 73.1%.  The loop-variant input
//      is load-bearing: it makes the insn non-invariant so loop.c cannot
//      hoist it (AGENTS §6ds2, the non-volatile-anchor form).  Pinning it
//      (`register s32 zm __asm__("r31")`) is 40.5% — the hard pin forces a
//      callee-saved save slot want does not have.
//  (2) THE TAIL'S ZERO MUST BE A NAMED VARIABLE SHARED WITH THE MATCH
//      ARM, so one `li` serves all four tail stores.  With bare NULLs GCC
//      emitted TWO constants in the tail (the block's arg0 stores and the
//      post-call `sp.unk0x0 = 0`), which is exactly the one surplus word
//      that re-aligned the whole tail:
//          zm = 0; arg0->unk0x4 = zm; arg0->unk0x8 = zm; arg0->unk0x0 = zm;
//      done: if (sp.unk0x0 != NULL) { RemoveRefLink(...); sp.unk0x0 = zm; }
//      73.1% -> 87.0%.  As a side effect the `zm` variable also DEFEATS
//      the store-class rotation (AGENTS §24/64/159/206): the bare-NULL tail
//      emitted 0,4,8 (rotated) and the `zm` tail emits 4,8,0 = source order,
//      which is what want has.
//
// RESIDUAL — the 10 non-matching words (want | got):
//   0x8004BEF4  mr r4, r29     | mr r4, r11     <- the FIRST AddRefLink's
//                               arg1 still reads the r11 `&sp` birth web
//                               instead of the r29 home.  `ps` and `psx`
//                               are already two names, but GCC coalesces
//                               the call arg back onto the birth pseudo.
//   At 0x8004BF58 the match-arm join reloads 8(r1) into r3 in the want but
//   into r9 here; at 0x8004BF5C the compare against zero reads that reload
//   (the want's compare is not a fresh load); at 0x8004BF60 the want takes an
//   unconditional branch to 0x8004bfbc while this body emits a conditional
//   branch on non-zero to 0x8004c064 whose flags are dead:
//                               consumed 20 bytes later by the TAIL's
//                               `beq` at 0x8004bfbc — one compare shared
//                               across the goto (AGENTS §6as-3 / §7b-3
//                               cr-cache via crossjump).  GCC instead
//                               materialises a local `bne` in r9.
//   The six-word tail block at 0x8004BFA4 through 0x8004BFB8 differs only in
//   order: the want loads, materialises the zero, stores to offsets 4 and 8,
//   compares, and stores the zero last (in the branch delay slot), while this
//   body zeroes first, performs the three stores, and only then loads and
//   compares.
//     Same CFG, same 6 insns; only the ORDER differs.  The guard's
//     `sp.unk0x0` load is the LAST source read (it is the `if` condition)
//     so its LUID is after the `li`/`stw` group and `reorder_basic_block`
//     (priority = #users, AGENTS §6bg-8) keeps it last; want's RTL has it
//     FIRST, i.e. retail's source read `sp.unk0x0` into a variable before
//     the zero-stores.  Every way of getting that read earlier that does
//     not add a callee-saved home was tried and measured (below).
//
// TWIN FOUND THIS ROUND (AGENTS §6dc/§6dr/§6fn — the whole function shape
// already exists, byte-identical and PROMOTED, 2 KB away, same 308 B size):
//   src/fn_8004C2DC.c  (fn_8004C2DC, 0x8004C2DC-0x8004C410) is the same
//   "walk a reflink list looking for one object" helper — same
//   CObject_AddRefLink/CObject_RemoveRefLink pair, same stack `sp` link,
//   same two-web `&sp` birth, same cleanup `if (sp[0]) RemoveRefLink(...)`.
//   It contributed the store-order and zero-web analysis above.  Its
//   `b = sp; b[1]=NULL; __asm__ volatile("" : "+r"(b)); p = b; b = sp;
//   b[2]=NULL;` init shape and its `__asm__ volatile("" ::: "memory")`
//   before the cleanup were BOTH tried here and both REGRESS (81.8% /
//   85.7%), so do not re-port them.
//
// MEASURED LEVERS THIS ROUND (cumulative unless noted; all 308 B except
// where a length is given):
//   baseline (inherited draft) ................................ 51.9%
//   opaque `li` birth, loop-variant input (fix 1) ............. 73.1%
//   + named shared `zm` in the tail (fix 2) ................... 87.0%  BEST
//   -- the two fixes are an AND: 51.9 / 73.1 / 87.0.
//   Regressions (do NOT re-try):
//     tail 3rd store moved inside the guard .............. 62.8% / 49.4%
//     tail load staged into a fresh temp `tt` ............ 22.5% (new r27
//        home — the temp's live range crosses the loop)
//     tail load staged into the existing `nd` ............ 23.8% / 39.2%
//     tail re-read `nd = sp.unk0x0` before `zm = 0` ...... 87.0% (no-op)
//     `done:` label between the 2nd and 3rd tail store ..... 87.0% (no-op)
//     `volatile("" ::: "memory")` before the tail guard ... 87.0% (no-op)
//     guard read as `*(s32*)&sp.unk0x0` .................. 87.0% (no-op)
//     comma trick `unk0x8 = (unk0x4 = zm, zm)` ........... 87.0% (no-op)
//     `+r`(ps) barrier right after the home copy .......... 85.7% (fixes
//        0x8004BEF4 but swaps `stw r9,8(r1)` past `cmpwi r9,0` at 0x8004BEE4)
//     `+r`(ps) before / inside the first AddRefLink ....... 85.7% / 13.0%
//     `&sp` instead of `ps` at the first AddRefLink only .. 87.0% (no-op)
//     drop the dead `nd = sp.unk0x0` re-read .............. 87.0% (no-op)
//     unconditional `goto done` at the match-arm end ...... 53.2%
//     match-arm join without the `nd` temps ................ 78.2% (both
//        `if (sp.unk0x0 != 0) goto done;` and the `==0/!=0`
//        inverted form)
//     twin-shaped `b`/`p` two-web init (with/without barrier) 81.8 / 85.7%
//     twin-shaped init with the r11 pin on `b` ............ 16.7%
//     `register s32 next __asm__("r31")` (force `next`'s home
//        so the match-arm zero recycles r31) ............. 33.8%
//     `register s32 zm __asm__("r31")` .................... 40.5%
//     named zero for the tail WITHOUT sharing it with the
//       match arm (4 bare uses) ........................... 42.9%
//     separate `zt` for the match arm, plain `zt = 0` .... 42.9%
//     opaque `li` birth in the TAIL as well ............... 87.0% (no-op)
//     both zero births opaque, 3rd store in guard ......... 87.0% (no-op)
//   Flags, re-measured on the FIXED body: -fno-schedule-insns2 /
//   -fno-sched-spec / -fno-sched-interblock / -fno-gcse /
//   -fno-rerun-cse-after-loop / -fno-expensive-optimizations /
//   -fno-thread-jumps / -O3 : all 87.0% (no-op).  -fno-schedule-insns
//   11.7%.  (The inherited header's flag list was measured on the OLD
//   body and is superseded; there is no FLAG line and none is wanted.)
//
// INLINE ASM: 1 emitted instruction of 77 (1.3%) — the `li %0,0` birth.
// Plus 3 zero-instruction `register ... __asm__` pins (r29 for the `&sp`
// home, r11 for its birth, r28 for arg3) and 0 barriers.
//
// AUDIT: object .text 0x134 == symbols.txt size:0x134 == header range;
//   only .text + .rela.text in the object, so no private .rodata and no
//   doc-14 pool caveat (masked-NEAR anyway, not promote-ready);
//   10/10 intra-function R_PPC_REL14 (type 11, section-relative) addends
//   land on want's exact branch sites; 6/6 R_PPC_REL24 call targets match
//   want's `bl`s in order (CObject_AddRefLink x3, fn_8009E408,
//   CObject_RemoveRefLink x2); NO `extern lbl_` data symbol in the body, so
//   the masked-wrong-label hazard (AGENTS 277) cannot apply; the single
//   QB hash is a lis/ori immediate pair (unmasked, byte-verified) =
//   0x9494A525 = QB_TAG_LOCAL_ID.  `tools/ps_diff.py` was not needed: the
//   want has no opcode-4 words.
//   The 3 residual clusters above still move blocks, so this is a PARK,
//   not an EXACT.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 89.6% ([1]asc->89.6%).
#include "types.h"
#include "qb_constants.h"

typedef struct { void *unk0x0; void *unk0x4; void *unk0x8; } Lnk;
typedef struct { char p0[0x64]; void *unk0x64; char p1[0x8]; void *unk0x70; } Obj;

extern void CObject_AddRefLink(void *o, Lnk *l);
extern void CObject_RemoveRefLink(void *o, Lnk *l);
extern s32 fn_8009E408(Obj *o, s32 hash, s32 *out);

void *fn_8004BEB0(Lnk *arg0, s32 arg1, void **arg2, s32 arg3) {
    Lnk sp;
    register s32 ps __asm__("r29");
    s32 v;
    void *next;
    register s32 a3 __asm__("r28");
    void *nd;
    s32 zm;

    nd = ((Obj *)*arg2)->unk0x64;
    {
        register s32 psx __asm__("r11");
        psx = (s32)&sp;
        ((Lnk *)psx)->unk0x4 = NULL;
        ((Lnk *)psx)->unk0x8 = NULL;
        ps = psx;
    }
    a3 = arg3;
    sp.unk0x0 = nd;
    if (nd != NULL) {
        CObject_AddRefLink(nd, (Lnk *)ps);
    }
    if (sp.unk0x0 != NULL) {
        do {
            if ((fn_8009E408((Obj *)sp.unk0x0, QB_TAG_LOCAL_ID, &v) != 0) && (v == a3)) {
                __asm__("li %0,0" : "=r"(zm) : "r"(a3));
                arg0->unk0x4 = zm;
                arg0->unk0x8 = zm;
                arg0->unk0x0 = sp.unk0x0;
                if (sp.unk0x0 != NULL) {
                    CObject_AddRefLink(sp.unk0x0, arg0);
                }
                nd = sp.unk0x0;
                if (nd != NULL) {
                    goto done;
                }
                nd = sp.unk0x0;
            }
            next = ((Obj *)sp.unk0x0)->unk0x70;
            if (sp.unk0x0 != NULL) {
                CObject_RemoveRefLink(sp.unk0x0, (Lnk *)ps);
                sp.unk0x0 = NULL;
            }
            sp.unk0x0 = next;
            if (next != NULL) {
                CObject_AddRefLink(next, (Lnk *)ps);
            }
        } while (sp.unk0x0 != NULL);
    }
    zm = 0;
    arg0->unk0x0 = zm;
    arg0->unk0x4 = zm;
    arg0->unk0x8 = zm;
done:
    if (sp.unk0x0 != NULL) {
        CObject_RemoveRefLink(sp.unk0x0, (Lnk *)ps);
        sp.unk0x0 = zm;
    }
    return arg0;
}
