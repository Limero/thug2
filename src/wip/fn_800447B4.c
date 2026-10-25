// family=hand range=0x800447B4-0x800448D0 size=284B
// PARKED 2026-10-05 — 12.7% true / 14.1% masked, and NOT a shift
// artefact: the object is 9 words short (248 B vs 284 B) but at the best
// alignment (-2 words, tools probe `shift.py`) the residual is still 57/71
// words.  Two further reconstructions measured this round, both worse: a
// while-loop with no pointer locals (direct `&cur`/`&nxt`) = 2.8% / 240 B, and
// the same with named `node` temporaries = 5.3% / 300 B (4 words OVER).
//
// WANT (fully decoded, for whoever retries): frame 0x38, stmw r28.  r28 = &cur
// (computed as `addi r9,r1,8; mr r28,r9` — the source has BOTH the address
// expression and a pointer variable), r31 = &nxt (its `addi` sits in the loop
// preheader at 0x80044800, so `pnxt = &nxt` is hoisted), r29 = the running sum,
// r30 = the 0 constant.  Cell = 0x10 B {node@0, f4@4, f8@8} at sp+8 / sp+0x18;
// every cell write is `f4 = 0; f8 = 0; node = <v>`.  CFG: test1 `if (cur.node)
// AddRefLink(cur.node, &cur)`; test2 the rotated `while (cur.node)` guard;
// latch test3 with the SAME `lwz r0,8(r1); mr r3,r0; cmpwi r0,0` shape; test4 the
// trailing `if (cur.node) { RemoveRefLink; cur.node = 0; }` (redundant after the
// latch, which is why it survives).  The recurring `lwz rX ; mr r3,rX ; cmpwi`
// pattern is the whole length gap here: the loaded pseudo lands in r0 and the
// call argument then needs an explicit copy to r3, which this draft's spelling
// does not produce (it loads straight into r3).  Tuning it needs the source
// form that gives that pseudo a longer live range than the call argument.
//
// 0x800447B4 - ref-counted list walk summing a per-node cost.
// STATUS 2026-09-25: 14.1% (was 47.9% DIFF m2c). The m2c body was a husk:
//   it passed the ADDRESS of the stack cell as AddRefLink's arg0 instead of
//   the node pointer, and modelled the two 16-byte ref-cells as overlapping
//   (Unk_59AB5482 overlays). Rewritten with a real 16-byte RefCell
//   {node,f4,f8,pad} and hoisted base pointers pcur/pnxt, which fixes the
//   frame (-0x30 -> -0x38), the prologue, and every cell store offset.
//   Residual: got is 248B vs want 284B - ngccc drops the `mr r3,r0` copy
//   after each cell reload (9 insns short), so the positional compare
//   collapses. Tried: 3 field-store orderings, pcur-copy split, lazy pnxt,
//   zeros-before-node. All score 7-14%; the length gap is a web-shaping
//   difference (the reload result feeds both the call arg and the test in
//   want, which needs an explicit temp - out of scope without asm).
#include "types.h"
#include "structs.h"

typedef struct RefCell {
    void *node;
    s32 f4;
    s32 f8;
    s32 pad0xC;
} RefCell;

s32 fn_80042AD8(void *);
void CObject_AddRefLink(void *, void *);
void CObject_RemoveRefLink(void *, void *);

s32 fn_800447B4(Unk_31DE137E *arg0) {
    RefCell cur;
    RefCell nxt;
    RefCell *pcur;
    RefCell *pnxt;
    s32 var_r29;
    s32 temp_r3;

    pcur = &cur;
    pnxt = &nxt;
    cur.node = arg0->unk0x64;
    var_r29 = 0;
    cur.f4 = 0;
    cur.f8 = 0;
    if (cur.node != NULL) {
        CObject_AddRefLink(cur.node, pcur);
    }
    if (cur.node != NULL) {
        do {
            temp_r3 = ((Unk_C7387A53 *)cur.node)->unk0x70;
            nxt.node = temp_r3;
            nxt.f4 = 0;
            nxt.f8 = 0;
            if (nxt.node != NULL) {
                CObject_AddRefLink(nxt.node, pnxt);
            }
            var_r29 += fn_80042AD8(cur.node);
            if (nxt.node != NULL) {
                var_r29 += 1;
            }
            if (cur.node != NULL) {
                CObject_RemoveRefLink(cur.node, pcur);
                cur.node = 0;
            }
            cur.node = nxt.node;
            if (cur.node != NULL) {
                CObject_AddRefLink(cur.node, pcur);
            }
            if (nxt.node != NULL) {
                CObject_RemoveRefLink(nxt.node, pnxt);
                nxt.node = 0;
            }
        } while (cur.node != NULL);
    }
    if (cur.node != NULL) {
        CObject_RemoveRefLink(cur.node, pcur);
        cur.node = 0;
    }
    return var_r29;
}
