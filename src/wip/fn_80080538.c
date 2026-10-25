// PARKED 2026-10-03 (b18): NEAR 90.7% (was DIFF 16.2% — the m2c draft was a
// wrong-length/garbage body; this is a from-scratch reconstruction off the
// disassembly, so the pct went UP, not down).
// repro: LEAF_TMPDIR=<scratch> tools/venv/bin/python \
//          tools/test_wip_drafts.py --addr 0x80080538
// The body is now instruction-for-instruction and block-for-block identical
// to the want: .text = 428B == symbol size, frame 0x30 / stmw r22,8(r1) /
// LR 0x34, all 17 branch displacements equal (verified by decoding the BD
// field of every branch in both), all 10 callee-saved registers (r22-r31)
// in the want's roles, no private .rodata, no asm.
// REMAINING DIFF = 10 words, all ONE cause: two volatile-register colours.
// The loop index lives in r4 in the want but in r11 in the output. Its zero
// materialisation, its word compare against r12, its copy from r7 and its
// second word compare against r12 all follow that home. The found flag lives
// in r3 in the want but in r4 in the output. Its zero materialisation, its
// word compare against r30, its one materialisation and its immediate zero
// compare all follow that home. The successor value lives in r7 in the want
// but in r3 in the output, formed by adding 1 to the index home in each case.
// RULED OUT (all measured, all dead ends):
//  - `register __asm__("r4"/"r3")` pins for j/found: CASCADE — pinning j to
//    r4 pushes cnt into r31 and off into r3, drops 1 instruction (106 vs 107).
//    Same as doc-05's warning. Don't retry pins here.
//  - declaration order of the 5 body temps (5 permutations), `found` hoisted to
//    the function top, `tag` inlined, `s2` inlined: all byte-identical output.
//    Pseudo birth order does not drive this allocation.
//  - `while (++j < cnt)` (pre-increment in the latch condition): no change.
//  - `j++` at the TOP of the body: gets j=r3/found=r4 (right colours, wrong
//    roles) but emits 106 insns — GCC drops the latch `mr` copy-back. Wrong
//    length, so unusable.
//  - -fno-schedule-insns / -fno-schedule-insns2: DIFF (loses the want's
//    software-pipelined load schedule and the colours with it).
//  - -fno-expensive-optimizations: dead here (the byte-wise u16 reads come from
//    the source `(p[0]<<8)|p[1]`, not from that flag).
// MOST PROMISING NEXT IDEA: `j+1` is what steals r3 in the body (it is born at
// the top of the body in got but after the `or` in the want). If the source can
// be made to delay that increment without letting GCC fold it into `j`
// (i.e. keep both `addi tmp,j,1` and the latch `mr j,tmp`), `found` should
// inherit r3 and `j` r4 in one step.
// 2026-10-15: `__asm__("" : "+r"(j))` after the append block REVERTED
// (90.7% -> 86.0%): the mid-loop barrier pins j's materialization and swaps
// the or/add schedule function-wide (or r0/add r6 swap, li/mr cascade). A
// barrier INSIDE this loop body perturbs scheduling globally, unlike the
// pre-loop/entry barriers that worked on fn_8018BC14/fn_80061F9C. The
// increment-delay idea needs a non-barrier spelling (or a barrier whose
// operands don't include the loop-carried j).
//
// LOAD-BEARING FINDINGS (worth filing in AGENTS-recipes.md):
//  1. `-fno-strength-reduce` is REQUIRED here (plain -O2 scores DIFF). With it,
//     loop.c's memory-address IV creation does NOT promote `cur + 1` to a
//     second induction variable. Without it you get +1 instruction and a
//     duplicated cursor IV: `lbz r0,-1(r6)` instead of `lbz r0,0(r6)` +
//     `lbz r8,1(r6)`, `lbzx (r6,rStr)` instead of `add q=cur+rStr; lbz 1(q)`.
//     It is the only flag that stops that promotion (-fno-expensive-optimizations
//     does not). Whether retail really used it or the original source avoided
//     the pattern is unresolved; flag line kept because it is byte-exact.
//  2. The base/index operand order of a commutative PLUS IS inherited from the
//     C source order through expand. Writing the output store as
//     `*(s32 *)((char *)off + (s32)arg1) = key;` (offset FIRST) emits
//     `stwx r8,r5,r28`; the natural `((char *)arg1 + off)` emits
//     `stwx r8,r28,r5`. Worth 2 words and applies to every indexed stwx/stbx.
//  3. Declaring `strideB` (field +0x26) BEFORE `strideA` (field +0x2A) — while
//     both are declared before the `if (cur < end)` — is what puts strideA's
//     `add` before the `cmplw`/branch and strideB's after, matching the want's
//     live-range lengths, which in turn fixes the r24/r27 callee-saved
//     assignment (61.7% -> 71.0%).  Live-range length drives global-alloc
//     priority, so *declaration order* is a colour lever here, not just a
//     frame/slot lever.
//  4. The command-count loop must be `j = 0; if (j < cnt) { off = off4; do
//     {...; j++;} while (j < cnt); }` — the plain `for` puts `off = off4`
//     before the pre-test branch and the latch then jumps to it (84.1 ->
//     88.8%).  Same "pre-header between test and latch" rule as the brief.
//  5. Return type must be `s32`; `u16` adds an `rlwinm r3,r30,0,0xffff`.
//  6. Frame: the want has ZERO addressable locals (48 = 8 fixed gap + 40 saved);
//     an extra live GPR pushes an 11th callee-save (stmw r21) and costs 8
//     bytes of frame, which then shifts every colour.
// family=m2c range=0x80080538-0x800806E4 size=428B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// FLAG: -fno-strength-reduce
#include "types.h"
#include "structs.h"

void *fn_8007DF14(void *);

typedef struct V_80538 {
    char pad0x0[0x14];
    void *f14;
} V_80538;

s32 fn_80080538(CScript *arg0, s32 *arg1, s32 *arg2) {
    s32 n = 0;
    u32 i;

    if (*(s32 *)((char *)fn_8007DF14((void *)arg0->unk0x18) + 8) != 0) {
        for (i = 0; i < (u32)arg0->unk0x24; i++) {
            V_80538 *v = *(V_80538 **)((char *)arg0->unk0x20 + i * 4);
            void *sub = v->f14;
            u8 *base = (u8 *)sub + 0x40;
            u8 *end = base + *(s32 *)sub;
            u8 *cur = base + *(u16 *)((char *)sub + 0x24);
            s32 strideB = *(u16 *)((char *)sub + 0x26) * 2;
            s32 strideA = *(u8 *)((char *)sub + 0x2A) * 2;
            s32 off4;

            if (cur < end) {
                off4 = n * 4;
                while (cur < end) {
                    s32 tag = *(u8 *)cur & 0xF8;
                    s32 cnt;
                    s32 j;
                    s32 off;

                    if (tag == 0x98 || tag == 0x90 || tag == 0x80) {
                        cnt = (*(u8 *)(cur + 1) << 8) | *(u8 *)(cur + 2);
                        cur += 3;
                        j = 0;
                        if (j < cnt) {
                          off = off4;
                          do {
                            void *s2 = v->f14;
                            s32 key = ((s32)cur[0] << 8 | cur[1])
                                      + *(s32 *)((char *)s2 + 0x38);
                            s32 idx = (cur[strideA] << 8) | cur[strideA + 1];
                            s32 found = 0;
                            s32 k;

                            cur += strideB;
                            for (k = 0; k < n; k++) {
                                if (*(s32 *)((char *)arg1 + k * 4) == key) {
                                    if (*(s32 *)((char *)arg2 + k * 4) == idx) {
                                        found = 1;
                                        break;
                                    }
                                }
                            }
                            if (found == 0) {
                                *(s32 *)((char *)off + (s32)arg1) = key;
                                off4 += 4;
                                *(s32 *)((char *)off + (s32)arg2) = idx;
                                n++;
                                off += 4;
                            }
                            j++;
                          } while (j < cnt);
                        }
                    } else {
                        break;
                    }
                }
            }
        }
    }
    return n;
}
