// WIP DRAFT (non-matching) — C body hand-reconstructed from the want bytes
// family=m2c range=0x8002D728-0x8002D9B0 size=648B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// BEST MEASURED: 92.6% (12 differing words; was 91.4%), object size EXACTLY 648B.
// 2026-10-18: rt_sweep memcpy void->s32 (+1.2) applied; residuals 1-4 unchanged.
// Was 13.0% (m2c bulk draft, 632B). Whole control-flow + every loop shape now
// matches; the residue is register *numbering* only.
//
// WHY PARKED (residual = 14 words, all register-number / 2-slot scheduling):
//  1. loop-2 index/cursor register pair is SWAPPED vs want:
//       want  index=r30  q=r31     (0x8002D7D0 li r30,0 / 0x8002D7D4 mr r31,r24)
//       got   q=r30      index=r31  -> 7 words differ (0x7D0,7D4,7DC,7FC,808,810,814)
//     Loop 5 wants index=r31/q5=r30 and GOT produces exactly that. The
//     allocator is self-consistent: with ONE shared cursor variable both loops
//     get index=r30 (loop 2 then matches, loop 5 breaks -> 90.1%); with two
//     separate cursors both get index=r31 (loop 5 matches, loop 2 breaks ->
//     91.4%, what is parked). WANT has BOTH, so the original had four distinct
//     pseudos whose allocation history crossed — see findings A/D: the pairing
//     is decided in the pre-IV RTL by a global free-list state that even the
//     function's tail can shift, so this is not fixable by editing loop 2 alone.
//  2. loop-3 `lwzx` addressing-operand slots are reversed (3 words:
//     0x85C/0x880/0x890). want `lwzx r3, r28, r9` (base,index), got
//     `lwzx r3, r9, r28`. Loops 2/5 agree with want; only loop 3 differs, and
//     its index is a fresh `slwi` result rather than a loop-carried IV.
//     Root cause + the spelling that fixes the slots (and its 1-word cost) is
//     finding C below; fixing it needs a base-first address whose index operand
//     is a *temporary*, which no source form found produces.
//  3. loop-5 preamble ORDER (2 words, 0x8F4/0x8FC): want emits the index init
//     `li r31,0` before `mr r30,r24` (cursor), GOT always emits the cursor
//     first regardless of source order (tried `m=0` before/after the call).
//  4. loop-5 memcpy arg load order (2 words, 0x918/0x920): want loads the
//     size (r5) then src then dst (natural reverse-arg ABI order); GOT loads
//     the dst first. Tried hoisting the size into a temp (no change).
//
// NEW FINDINGS (2025-10-04 session) — read these before touching the body:
//  A. ngccc (GCC 2.95) runs the induction-variable / strength-reduction passes
//     *AFTER* reload+local-alloc. Proof: `ngccc -dj` (see B) dumps the pre-IV
//     RTL for this function as `M[plus(mult(k,4), p)]` with a per-iteration
//     `ashift` and `i++` guards, while the object has pointer walks (loops 1/4),
//     byte-stepping IVs + `addic. -1` downcounters (loops 2/5) and slwi+copy
//     (loop 3). Consequences: (a) the callee-saved register NUMBERS are fixed
//     before that rewrite, so blocker 1 is decided by the pre-IV pseudo layout,
//     not by anything visible in the disassembly; (b) the final `lwzx` operand
//     slots in loops 2/5 are emitted by the IV pass, so the source MEM order
//     does not control them.
//  B. DEBUG TOOL: `-dj` dumps the post-jump (pre-reload) RTL with pseudo ids
//     (`<base>.TMP.jump` in the CWD — run from /tmp, it writes to the CWD);
//     `-dr` = final RTL, `-ds`/`-dt`/`-dw` = cse/cse2/flow2. There is no
//     local-alloc dump (`-du` unsupported). This is the fastest oracle for
//     register-allocation parks: it shows which pseudo is the IV, the preheader
//     insn order and the MEM plus order.
//  C. `lwzx` slot order is decided by the ORDER OF THE PLUS in the MEM, and the
//     plus order comes from the source spelling (verified with 30+ probes):
//       inline address  `p[k]` / `p + k` / `(char *)p + k * 4`
//            -> MEM plus(mult_or_index, base)  -> `lwzx rD, index, base`
//       address via a VARIABLE  `boff = k*4; *(T **)((char *)p + boff)`
//            -> MEM plus(base, boff)           -> `lwzx rD, base, index`
//     So want's loop 3 (all three `p[k]` loads with the base in RA) implies the
//     original spelled that address through an offset VARIABLE. Measured: doing
//     so reproduces all three slot orders BUT the slwi then writes straight into
//     the callee-saved reg, deleting want's `mr r29, r9` copy — loop 3 comes
//     out exactly 1 word short and everything after it shifts (95 diffs).
//     A base-first address whose index operand is a *temporary* was not found.
//  D. The loop-2/loop-5 register pairing is a GLOBAL allocation artifact, not a
//     local property: swapping the two trailing `Mem_Free2` calls moves `ptrs`
//     from r24 to r25 and changes both loops' pairs (23 diffs). That plus C is
//     why "one shared cursor" flips both loops and no local edit flips one.
//     Measured negatives this round: three separate loop indices; `m = 0`
//     before/after the F320 call; `q = ptrs`/`dst = buf` reorderings; cursor
//     initialised inside the for; `&buf[off]` and `buf + off * 1` as the memcpy
//     source; shared-role variables `a`/`b` (needs `*(void**)&b`, which defeats
//     the IV rewrite entirely -> 102 diffs).
//
// KEY FINDINGS for the recipes file (see "notes" below):
//  * ngccc's `lwzx rD, rA, rB` computes EA = rA + rB with the index **UNSCALED**
//    (verified with purpose-built probes: `((char*)p)[i]` -> `lwzx r3, r3, r4`,
//    `p[i]` -> `slwi r0,r4,2` + `lwzx r3, r3, r0`). The manual/objdump reading
//    (rB*4) is wrong for this target; this is why m2c's "scaled pointer
//    arithmetic" drafts looked wrong.
//  * `for (i = 0; i <= N; i++)` only survives as `slwi`+`addi i+1`+`cmpwi i,N;ble`
//    when the loop index is a SEPARATE source variable from the other loops'
//    (`k` here). Sharing one `i` makes GCC canonicalise it into a down-counter
//    (`li 0x32; addic. r27,-1; bne`) - that single rename was worth 5 words.
//  * `p[i]` written 3+ times keeps the indexed `lwzx` form; written once (via a
//    cached `Unk_Node *n`) GCC strength-reduces it to a pointer walk + limit.
//    That is exactly how WANT splits loops 1/4 (walk) from loops 2/3/5 (index).
//  * The two `fn_8002D2B0(arg0,0)` failure paths must be expressed as early
//    `return 0;` with a `goto` to a label inside the FIRST `if` block; plain
//    if/else nests both variants out of line (cost ~10 words + the whole tail
//    misaligns).
//  * Loop-2 store order `dst += sz;` BEFORE `*q = p[i]->unk0x10; q++;` is
//    load-bearing: the other order costs an extra rematerialised `lwzx`.
//  * Loop-5 order `off += p[m]->unk0x14;` BEFORE `p[m]->unk0x1C += delta;` is
//    load-bearing too (worth 7 words).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
#include "mem.h"

typedef struct Unk_Node {
    s32 pad0x0[3];
    s32 unk0xC;
    void *unk0x10;
    s32 unk0x14;
    char pad0x18[4];
    s32 unk0x1C;
    s32 unk0x20;
    char pad0x24[8];
    void *unk0x2C[0x12];
} Unk_Node;

extern char lbl_802FFE98[];
void fn_8000F2F8(void *, void *);
void fn_8000F320(void *);
s32 fn_80010400(s32, s32, s32);
void fn_8002D2B0(void *, s32);
void fn_8002CA8C(void *);
void fn_8002CF1C(void *);
s32 memcpy();
// 2026-10-18: rt_sweep void->s32 (+1.23, arg-setup order) — applied.

s32 fn_8002D728(Unk_Node **arg0) {
    s32 count;
    s32 total;
    s32 i;
    s32 j;
    s32 k;
    s32 m;
    s32 off;
    s32 delta;
    char *buf;
    char *dst;
    void **ptrs;
    void **q;
    void **q5;
    Unk_Node **p;
    Unk_Node *n;

    fn_8002D2B0(arg0, 1);
    p = arg0 + 1;
    count = 0;
    total = 0;
    for (i = 0; i < 0x32; i++) {
        if (p[i]->unk0x10 != 0) {
            total += p[i]->unk0x14;
            count++;
        }
    }
    buf = Mem_Alloc(total);
    ptrs = Mem_Alloc(count * 4);
    if (buf == NULL) {
err:
        fn_8002D2B0(arg0, 0);
        return 0;
    }
    if (ptrs == NULL) {
        Mem_Free2(buf);
        goto err;
    }
    dst = buf;
    i = 0;
    q = ptrs;
    for (; i < 0x32; i++) {
        if (p[i]->unk0x10 != 0) {
            memcpy(dst, p[i]->unk0x10, p[i]->unk0x14);
            dst += p[i]->unk0x14;
            *q = p[i]->unk0x10;
            q++;
        }
    }
    off = 0;
    fn_8000F2F8(*(void **)&lbl_802FFE98,
                (void *)fn_80010400(*(s32 *)&lbl_802FFE98, QB_ANIMHEAP, 1));
    for (k = 0; k <= 0x31; k++) {
        if (p[k]->unk0xC != 0) {
            if (p[k]->unk0x10 != 0) {
                Mem_Free2(p[k]->unk0x10);
            }
            p[k]->unk0x10 = 0;
            for (j = 0; j < 0x12; j++) {
                if (p[k]->unk0x2C[j] != 0) {
                    fn_8002CA8C(p[k]->unk0x2C[j]);
                }
            }
        }
    }
    for (i = 0; i < 50; i++) {
        n = p[i];
        if (n->unk0xC != 0) {
            n->unk0x10 = Mem_Alloc(n->unk0x14);
        }
    }
    q5 = ptrs;
    fn_8000F320(*(s32 *)&lbl_802FFE98);
    for (m = 0; m < 0x32; m++) {
        if (p[m]->unk0xC != 0) {
            memcpy(p[m]->unk0x10, buf + off, p[m]->unk0x14);
            delta = (s32)p[m]->unk0x10 - (s32)*q5;
            q5++;
            off += p[m]->unk0x14;
            p[m]->unk0x1C += delta;
            p[m]->unk0x20 += delta;
            fn_8002CF1C(p[m]);
        }
    }
    if (buf != NULL) {
        Mem_Free2(buf);
    }
    if (ptrs != NULL) {
        Mem_Free2(ptrs);
    }
    return 0;
}