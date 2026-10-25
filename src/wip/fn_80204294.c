// WIP DRAFT (non-matching) — best 84.2% (32/38 words, size-exact 152B).
// family=m2c range=0x80204294-0x8020432C size=152B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// FLAG: -fno-strength-reduce
//
// REWRITE 2026-10-12: old m2c draft was DIFF/34% with a
// byte-vs-word index bug (`(s32*)(base+i*0x18)+0x1E8` addresses base+i*0x18+
// 0x7A0, want reads base+i*0x18+0x1E8). Decoded want by hand:
//
//   skater = fn_801745B4(lbl_80305EAC) (returns pointer, was declared s32)
//   arg0->sk = skater; arg0->idx = -1
//   key = arg0->box->key            // box = *(arg0+0x0C), key at box+0x18
//   i = 0; if (key != skater->e[0].id) {
//     do { i++; if (i > 4) goto done; } while (key != arg0->sk->e[i].id);
//   }
//   arg0->idx = i;
// done: arg0->sk->e[arg0->idx].done = 1;
//   where e is 5 x 0x18-byte entries at skater+0x1E8 (id at +0, done at +4;
//   base+i*0x18+0x1E8 == (base+0x1E8)+i*0x18, so plain struct array works).
//
// WHAT EACH FIX WAS WORTH (score_wip.py, all size-exact unless noted):
//   struct-array + for/break seed ............ 30.6% (140-144B, short)
//   field-base reload in loop (arg0->sk->e[i])  26% (fixes lwz+add+lwz shape)
//   -fno-strength-reduce ..................... 68.4% (keeps mulli; base flags
//     strength-reduce i*0x18 into an incremental add, +1 insn, wrong shape)
//   deferred `arg0->idx = -1` (after key load)  84.2% (head order exact:
//     stw sk; li -1; lwz box; li i; lwz key; stw idx)
//   box local / index-first operand order .... no change (normalized away)
//
// PARKED 2026-10-12 at 84.2%, 6 diffs, all investigated:
//   1. 0x2D4: want `b TEST` vs got `beq STORE`. The head check MUST be a
//      separate local-based expression (want loads id straight off r3, the
//      still-live call result — no for/while formulation reproduces that AND
//      the per-iteration memory reload; while(field) was measured at 47% with
//      a 2-load head). But if+do-while structurally emits beq, never b. A
//      lone `b` needs goto/loop-header, which leaves the head cmpw dead — and
//      dead compares are deleted at -O2 (micro-tested). Both compares target
//      cr0 (raw words 0x7C080000 / 0x7C085800), so no cr-field trick. Tried:
//      if/else-empty-then, ==, while(field), for/break, byte-arithmetic,
//      goto-formulations (all add a word). No single-C-construct theory fits
//      [local-direct head] + [field loop] + [b entry]; likely a tiny
//      hand/odd shape. Next idea if revisited: A/B ProDG 3.5/3.7/3.8.1
//      codegen of if+do-while (branch layout differs by version).
// 2. RE-TESTED 2026-10-12: goto-to-condition shape (`cur` temp +
//      `goto test` into do-while) collapses to DIFF — the `cur` live temp
//      perturbs global allocation (struct-index loop load even goes lwzx),
//      with byte-arith loop load too. The if+do-while beq is structural.
//   3. Loop/tail register swap (0x2E4/2E8, 0x300/308/30C): want computes the
//      index product into r0 and loads base into r9; got does the reverse.
//      Operand order (base-first vs index-first) was A/B'd — normalized away.
//      Probably falls out once the branch layout changes (allocation state).
// 3. CLOSED 2026-10-12: ProDG 3.7 and 3.8.1 compile this exact body
//      to byte-identical 152B objects with the same 6 masked diffs (32/38 =
//      84.21% under the harness masks: +0x40 b-vs-beq, +0x50/+0x78 mulli
//      r10-vs-r9, +0x54/+0x6C/+0x74 lwz r9-vs-r0). The if+do-while branch
//      layout and the index/base colouring are version-independent — the
//      version A/B idea is dead, do not retry.
//   4. OPEN QUESTION: -fno-strength-reduce as a per-object flag claims this
//      TU built differently from base -O2. Plausible (or ProDG quirk); needs
//      a second function from the same TU confirming before promoting with it.
//      Sibling fn_8020432C is a different function (null-check + QB const),
//      not a twin — no confirmation available nearby.
#include "types.h"
#include "structs.h"
// FLAG: -fno-strength-reduce

typedef struct { s32 id; s32 done; char _8[0x10]; } Ent4294;

typedef struct {
    char _00[0x1E8];
    Ent4294 e[5];
} SkaterView4294;

typedef struct {
    char _00[0x18];
    s32 key;
} KeyBox4294;

typedef struct {
    char _00[0x0C];
    KeyBox4294 *box;
    char _10[0x0C];
    SkaterView4294 *sk;
    s32 idx;
} Ctx4294;

extern s32 lbl_80305EAC;
SkaterView4294 *fn_801745B4(s32);

void fn_80204294(Ctx4294 *arg0) {
    SkaterView4294 *sk = fn_801745B4(lbl_80305EAC);
    KeyBox4294 *box;
    s32 key;
    s32 i;

    arg0->sk = sk;
    box = arg0->box;
    key = box->key;
    arg0->idx = -1;
    i = 0;
    if (key != sk->e[0].id) {
        do {
            i += 1;
            if (i > 4) {
                goto done;
            }
        } while (key != *(s32 *)(i * 0x18 + (char *)arg0->sk + 0x1E8));
    }
    arg0->idx = i;
done:
    *(s32 *)(arg0->idx * 0x18 + (char *)arg0->sk + 0x1EC) = 1;
}
