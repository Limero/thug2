// family=m2c range=0x8007ED94-0x8007EE94 size=256B
// FLAG: -fno-strength-reduce
// PARKED 2026-10-03 (a55): NEAR 60.9% (25 bad of 64 words). Reproduce:
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x8007ED94
// Baseline was DIFF 21.2%. TWO changes took it there (both load-bearing, measured):
//   1. `// FLAG: -fno-strength-reduce` (recipes 89 / 6ap-1). Without it ProDG's loop
//      pass strength-reduces the 4-trip countdown loop into `li r0,4; mtctr r0`
//      DEAD code + `bdnz` on the dst pointer, which adds 8 bytes (264B vs 256B)
//      and shifts every instruction after 0x8007EDBC -> everything mismatches.
//      -fno-schedule-insns2 (recipe 89's other half) makes it WORSE here (50.0%).
//   2. `register s32 cnt __asm__("r8")` on the countdown var: want keeps the
//      counter in r8 and the load temp in r9; unpinned GCC picks r7 for cnt.
// Remaining diff is now PURE register allocation, no shape diff (same 256B, same
// instruction sequence, same prologue/epilogue, all 4 calls and arg loads match):
//   - want dst = r11 everywhere (`mr r11,r31` + all loop stw r11 + tail stw r11);
//     got dst = r7. Costs 2 + 7*2 = 16 of the 25 bad words.
//   - want uses r9 as the load temp for all six copies; got alternates r9/r0.
//   - `li r0,0x400` (want) vs `li r11,0x400` (got) — fallout of dst taking r7.
//   - tail store order: got emits unk0x68 SECOND (4,68,6c,0,5c,5e,58), want emits
//     it LAST (4,6c,0,5c,5e,58,68); ascending source order is what I used.
// RULED OUT (all measured, all with the FLAG in place):
//   - `register Rec_t *dst __asm__("r11")`: pinning dst to r11 brings the mtctr
//     conversion BACK (260B, 20.0%) even with -fno-strength-reduce and even with
//     -fno-branch-count-reg / -fno-gcse / -fno-schedule-insns2 added. Pinning
//     src=r10 too -> 264B. So the pin that would fix the register is exactly the
//     one that re-breaks the loop shape.
//   - struct assign `*dst = *src;` in the loop: 46.9%, same 256B.
//   - `s32 *d = (s32*)dst; d[0]=s[0]...` form: 60.9% (identical to the winner).
//   - explicit `t = src->fN; dst->fN = t;` temp for all six: compile FAIL.
//   - loop shapes: for/while/do-while, decrement-first, increment-first, byte-walk
//     `(char*)src+0x18`, `src = src+1`, cnt-init-first, dst-init-first: ALL 57.8%
//     unpinned / 60.9% pinned — none move the allocation.
//   - -fno-loop-optimize: cc1 FAIL (not a usable spelling in this ProDG).
//   - -fno-unroll-loops, -fno-branch-count-reg: no change (57.8%).
//   - descending tail store order: 18.8%, 220B (stores get reordered/merged).
// NEXT IDEA: the want's dst=r11 sits directly above src=r10 and cnt=r8, i.e. the
// whole loop web is the contiguous block r8..r11. Unpinned GCC allocates dst
// FIRST (gets the lowest free reg, r7) and only then the temp/counter. Try making
// the dst pointer's live range *start later* than the temp's — e.g. build the walk
// as `Rec_t *d2; d2 = p; ...` inside a nested block, or copy through a `char *`
// alias declared after the first copy statement — so dst lands after r9 is taken.
void *Mem_Alloc2(s32);
void *fn_80099428(void *);
void *fn_8007DF14(void *);
void fn_8009950C(void *, s32, s32);
void fn_8009951C(void *);
void fn_800994C8(void *, s32, s32);
void fn_800997BC(void *);
#include "types.h"
#include "structs.h"

typedef struct {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
} Rec_t;

typedef struct {
    s32 unk0x00;
    s32 unk0x04;
    s32 unk0x08;
    char _0C[0x10];
    s32 unk0x1C;
    s32 unk0x20;
    char _24[0x0C];
    s32 unk0x30;
    char _34[0x24];
    s32 unk0x58;
    s16 unk0x5C;
    s16 unk0x5E;
    char _60[0x08];
    s32 unk0x68;
    s32 unk0x6C;
} Head_t;

void *fn_8007ED94(CScript *arg0) {
    Head_t *p;
    Rec_t *src;
    Rec_t *dst;
    register s32 cnt __asm__("r8");

    p = (Head_t *)fn_80099428(Mem_Alloc2(0x70));
    src = (Rec_t *)fn_8007DF14((void *)arg0->unk0x18);
    dst = (Rec_t *)p;
    cnt = 0x60;
    do {
        dst->f0 = src->f0;
        dst->f4 = src->f4;
        dst->f8 = src->f8;
        dst->fC = src->fC;
        dst->f10 = src->f10;
        dst->f14 = src->f14;
        src += 1;
        dst += 1;
        cnt -= 0x18;
    } while (cnt != 0);
    dst->f0 = src->f0;
    dst->f4 = src->f4;
    dst->f8 = src->f8;
    dst->fC = src->fC;
    p->unk0x04 = 0x400;
    p->unk0x6C = cnt;
    p->unk0x00 = cnt;
    p->unk0x5C = (s16)cnt;
    p->unk0x5E = (s16)cnt;
    p->unk0x58 = cnt;
    p->unk0x68 = cnt;
    fn_8009950C(p, arg0->unk0x24, (s32)arg0->unk0x20);
    fn_8009951C(p);
    fn_800994C8(p, arg0->unk0x24, (s32)arg0->unk0x20);
    fn_800997BC(p);
    return p;
}
