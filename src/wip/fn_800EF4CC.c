// WIP DRAFT — hand-written 2026-10-15 from want disasm (18 insns).
// Guarded bss init: unless arg1 is 0xFFFF with non-null arg0, returns arg0;
// otherwise zeroes a bss struct with a magic word and returns arg0.
// PARKED 2026-10-15: branches now exact (bnelr/beqlr via early returns).
// Residual is constant-CSE: want keeps THREE separate zero regs
// (li r11/r9/r10) + a page+0x98 decomposed base (lis r8 + addi r7);
// int-zero stores always share ONE li (merger is in cse/combine, not
// gcse — -fno-gcse identical). Tried: named zero temps (coalesced),
// absolute+pointer split refs (colour shifts, r10/r11 bases), magic-first
// ordering (two bases, scrambled stores, still one li), float members
// (worse: lfs pool loads). The 3-li shape may need distinct zero-valued
// sources (not literals) — SOLVED 2026-10-18: `register s32 zN`
// pinned to r11/r9/r10 + `zN = 0; __asm__("" : "+r"(zN))` forces three
// li-0 (barriers defeat const-prop/CSE merge). DIFF->50.0% NEAR.
// 2026-10-18 store-order campaign: last r7-store emits first, rest in
// source order ((m,c,d)->(+C,+4,+8); (m,d,c)->(+8,+4,+C)); want (+8,+C,+4)
// needs r7-seq (d,m,c) but magic-not-2nd flips base to lis r7. Explicit
// pinned r8/r7 bases are WRONG (want never fully materialises &lbl);
// early u32 magic temp, decl-init base (hoists over guards), assign-init
// base (emits copy) all fail. Kept: pin+barrier zeros, (a,magic,d,c),
// no base pins. Remaining: head lis order, li10-late, tail +4/+C swap.
// 2026-10-18 round 3: stmt_perm_search.pl hill-climb on the 4-store block:
// 50.0% -> 61.1% with source order (d,c,magic,a) [emits (magic,a,d,c)].
// lis r8 + lis r0 + li r10 + stw d now match; residual is 7 words (addi/ori
// earliness + store rotation). A 7-statement init+store perm search found
// nothing further (ordering optimum). Aggregate assign = DIFF; input
// barriers = DIFF (reverted). Structural gap: want delays addi r7 + ori
// below li r11/li r9 (critical-path height: addi feeds 3 r7-stores; the
// r8-direct a-store shows early-emitted stores skip the shared base).
// Next lever: a shape where fewer stores share r7 (height drop sinks addi),
// or magic value born late with ori still 8th. Kept: (d,c,magic,a).
// 2026-10-18 round 2 (all reverted to this best): magic-first source flips
// base pair to lis r7/addi r8 (first-store value reg steers the pair:
// a-first keeps r8/r7); 4th-var (m temp / p pointer, any home incl. r0/r12
// pins) also flips to r7/r8; late-z3 init flips allocation with magic-2nd;
// (a,c,magic,d) source = DIFF. Tail (c,d,magic) is not a rotation of any
// tried emission ((c,magic,d) observed); the d/magic tie needs the head
// fixed first (scheduler state). Do not retry without a new birth-order
// lever that puts lis r8 + lis r0 before li r11 with 3 live vars.
// family=leaf range=0x800EF4CC-0x800EF514 size=72B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// ORDERED 2026-09-11 (tools/stmt_perm_search.py): statement block lines 55..58 re-ordered; score now 61.1%.
#include "types.h"

typedef struct {
    s32 a;
    u32 magic;
    s32 c;
    s32 d;
} ObjEF4CC;

extern ObjEF4CC lbl_80380098;

void *fn_800EF4CC(void *arg0, s32 arg1) {
    register s32 z1 __asm__("r11");
    register s32 z2 __asm__("r9");
    register s32 z3 __asm__("r10");
    if (arg1 != 0xFFFF) {
        return arg0;
    }
    if (arg0 != NULL) {
        z1 = 0; __asm__("" : "+r"(z1));
        z2 = 0; __asm__("" : "+r"(z2));
        z3 = 0; __asm__("" : "+r"(z3));
        lbl_80380098.d = z3;
        lbl_80380098.c = z2;
        lbl_80380098.magic = 0x9738C23B;
        lbl_80380098.a = z1;
    }
    return arg0;
}
