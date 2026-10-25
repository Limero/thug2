// PARKED 2026-10-04 (2nd pass): best word-match 30.9% = 76/246 words, harness
// verdict DIFF (NEAR band starts at 50%). Object 996B vs want 984B (+3 words).
// repro: LEAF_TMPDIR=<scratch> tools/venv/bin/python \
//          tools/test_wip_drafts.py --addr 0x80080A84
// Semantic content is finished and believed: every field offset, width and
// signedness is read off the disassembly (lhz 0x24/0x26 = u16, lbz 0x2a = u8,
// lwz 0x00/0x34/0x38 = s32, tag = *cur & 0xF8 as u8, key = raw16 + unk0x38),
// the frame (stwu -0x4e68 / stmw r20,0x4e38 / LR 0x4e6c), both 10 000-byte s32
// buffers at 0x08/0x2718, the six-loop nesting and the whole paired-single tail
// all match. What is left is ngccc's register colouring + one loop rotation.
//
// CLOSED THIS ROUND
//  * the vec3 copy loop is a COUNT-DOWN in the want (guard `cmpwi cnt,0 / ble`,
//    latch `addic. r,r,-1 / bne`). Source `for (i = cnt; i != 0; i--)` gives
//    exactly that (rotated, one body copy) and is 8 bytes smaller than the
//    `for (i = 0; i < cnt; i++)` spelling, which ngccc leaves top-tested.
//    => 1004B -> 996B. Still open: want guards on `cnt` itself
//    (`cmpwi r27,0`) while got tests the counter copy (`or. rX,rY,rY / beq`),
//    i.e. the want's preheader test predates the `i = cnt` copy.
//    `for (i = cnt; i > 0; i--)` gives the `ble` guard but a `bgt` latch.
//
// BLOCKER 1 (size, +10 words): GCC rotates the inner `for (k...)` remap loop
// and DUPLICATES ITS BODY, want has one copy. Verified with RTL dumps
// (see TOOL below): the post-expand RTL is exactly the want's shape
// (`k=0; goto test; ... k++; test: if (k<cnt) goto body; body: ...`) - the
// entry is a real `goto` that jumps OVER the `k++` to the latch's test, which
// is the want's `b 0x80080C24`. A later RTL pass turns that into
// [preheader test + body copy] + [latch test + body copy]; with k==0 known in
// the preheader copy CSE folds `keys[k]` to `lwz 0(base)` and `stb 0`. The
// first pass dump that shows the duplicate is the one written by the pass
// dumped as `combine` (`-dc`); `-dr` (post-expand) still has one body.
//  * MEASURED FIX (kept out of this draft only because it costs more word
//    matches than it wins - see below): writing that loop with explicit
//    gotos (`k = 0; goto k_test; k_body: ... k++; k_test: if (k<cnt) goto
//    k_body; k_done:;`) makes ngccc keep the front-end layout and reproduces
//    the want's k-loop EXACTLY - single body, `b` to the test, `slwi` index,
//    `lwzx` off r31/r12 - and it also fixes the two buffer bases to the want's
//    r31 (=r1+8) / r12 (=r21). Cost: lgra then drops r20 and slides every
//    callee-saved colour up by one (arg0 r26->r27, arg1 r20->r21), which is
//    why the raw match count drops 76 -> 73 even though the loop itself is
// right. Object becomes 960B (-24B). Kept at <scratch>
//  * the rotation is NOT a compiler-version artefact: ProDG 3.5, 3.7, 3.8.1
//    and 3.9.3 all emit the same duplicated body for the same source.
//  * `-fno-thread-jumps`, `-fno-gcse`, `-fno-cse-follow-jumps`,
//    `-fno-unroll-loops`, `-fno-delayed-branch` do not change it. ngccc 3.9.3
//    has no `-fivopts`/`-fivcanon`/`-fcrossjumping`/`-fcunroll`/`-fno-peel-
//    loops` at all (only strength-reduce / gcse / schedule-insns{,2} /
//    thread-jumps / delayed-branch / unroll-loops / expensive-optimizations
//    among the loop-ish ones).
//
// BLOCKER 2 (register colouring, ~6 words + a cascade): the want's allocation
// inside loop 1 is arg1=r20, vals=r21, i+1=r22, cache=r23, end=r24,
// strideB=r25, arg0=r26, cnt=r27, strideA=r28, sub=r29, ent=r30, keys=r31,
// and the OUTER loop counter `i` in the CALLER-SAVED r10 (with i+1 in r22,
// which is what survives the two calls). Got: end/strideB swapped, cnt=r29,
// sub=r12 (+2 reloads), keys=r27, and `i` in callee-saved r28 - because
// ngccc emits the outer loop's `i = 0` BEFORE the two calls (right after
// `bl fn_80080538`, verified in the RTL: the `flow2`/`jump2` dumps move the
// constant assignment from the source position after `Mem_Alloc` to the top of
// the merged preheader block), so the `i` pseudo is live across calls and lgra
// must give it a callee-saved register. The want keeps `li r10,0` AFTER
// `bl Mem_Alloc` (0x80080B18), so `i` is never live across a call.
// No C spelling tried moves that `li` back down (`i = 0` + `if`, plain `for`,
// plain `while`, `(u32)(i = 0) < n` all hoist it identically). The per-block
// register order (keys=r31, vals=r12) that the want shows is only reachable via
// the goto form of blocker 1.
//
// BLOCKER 3 (PS loop, 4 words, flag-induced): the want derives a byte-offset
// IV for `ents[i]` in the PS loop: `li r6,0` in the preheader, `addi r6,r6,4`
// in the body, `lwzx r10, r6, r9` off the reloaded `ents`. That is exactly
// what the DEFAULT flag set produces. `// FLAG: -fno-strength-reduce` (kept
// from the previous round because it is worth +1 word / +1 match elsewhere)
// DESTROYS it - with the flag the access becomes `slwi r11,i,2` + `lwzx`.
// Dropping the flag: 1000B and 75 matches (PS loop 0/75 either way, because
// the whole tail is 3-4 words out of alignment behind blockers 1+2).
//
// TOOL THAT MADE THIS ROUND POSSIBLE (worth adding to AGENTS-recipes.md):
// ngccc writes full RTL dumps next to the source: `ngccc <flags> -da -dl -c x.c`
// leaves `x.c<NNN>.TMP.<pass>` files (rtl, combine, jump, cse, cse2, flow,
// flow2, gcse, loop, lreg, greg, mach, regmove, sched, sched2, addressof, bp,
// plus .vcg browsable forms) in the CWD, and a single pass can be dumped with
// -dr (post-expand), -dc, -dj, -dJ, -df, -dg, -dl, -dL, -dF. Those dumps are
// the only way to tell "the front end emitted it wrong" from "a later pass
// rotated it": here the front end emits the want's loop layout verbatim and
// `combine` is what duplicates the body. (File mtimes do NOT give the pass
// order in this build - use the per-flag dumps.)
//
// family=m2c range=0x80080A84-0x80080E5C size=984B
// WIP DRAFT (non-matching) - from-scratch reconstruction off the disassembly
// INERT: not registered in splits.txt/configure.py - never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
// FLAG: -fno-strength-reduce
#include "types.h"
#include "structs.h"
#include "dolphin/SN_PS.h"
#include "mem.h"

extern f32 lbl_80296290;
extern __ps_t lbl_80296210;
extern void DCFlushRange(void *, u32);

typedef struct Node Node;
typedef struct Ent {
    char pad0x0[0x4];
    u16 unk0x4;
    char pad0x6[0x6];
    f32 unk0xC;
    char pad0x10[0x4];
    Node *unk0x14;
} Ent;

struct Node {
    s32 unk0x0;
    char pad0x4[0xC];
    f32 unk0x10;
    f32 unk0x14;
    f32 unk0x18;
    f32 unk0x1C;
    char pad0x20[0x4];
    u16 unk0x24;
    u16 unk0x26;
    u16 unk0x28;
    u8 unk0x2A;
    char pad0x2B[0x9];
    void *unk0x34;
    s32 unk0x38;
    char pad0x3C[0x4];
};

typedef struct Ctx {
    s32 unk0x0;
    s32 unk0x4;
    s32 unk0x8;
} Ctx;

typedef union PSVal {
    __ps_t ps;
    struct {
        f32 hi;
        f32 lo;
    } flt;
} PSVal;

typedef union Buf {
    struct {
        PSVal a;
        PSVal b;
        PSVal c;
        PSVal d;
        PSVal t0;
        PSVal t1;
        PSVal t2;
        PSVal t3;
        PSVal t4;
        PSVal t5;
    } ps;
    s32 i[2500];
    f32 f[2500];
} Buf;

Ctx *fn_8007DF14(s32);
void fn_8007E89C(void);
s32 fn_80080538(CScript *, s32 *, s32 *);
void fn_800071D4(s32 *);
void fn_8000728C(s32 *, f32 *);

void fn_80080A84(CScript *arg0, f32 *arg1) {
    Buf keys;
    Buf vals;
    PSVal scp;
    PSVal res;
    f32 *dst;
    f32 *src;
    s32 flag;
    s32 cnt;
    s32 i;
    void *cache;
    Node *sub;

    flag = 0;
    if (fn_8007DF14(arg0->unk0x18)->unk0x8 != 0) {
        s32 t = ((Ent **)(void *)arg0->unk0x20)[0]->unk0x4 & 0x10;

        flag = t == 0;
    }
    if (flag != 0) {
        if (fn_8007DF14(arg0->unk0x18)->unk0x8 != 0) {
            s32 j;

            cnt = fn_80080538(arg0, keys.i, vals.i);
            fn_8007E89C();
            cache = Mem_Alloc((cnt * 3) << 2);
            i = 0;
            if ((u32)i < (u32)arg0->unk0x24) {
              do {
                Ent *ent = ((Ent **)(void *)arg0->unk0x20)[i];

                if (ent->unk0x14->unk0x34 == NULL) {
                    u8 *base;
                    u8 *end;
                    u8 *cur;
                    s32 strideB;
                    s32 strideA;

                    ent->unk0x14->unk0x34 = cache;
                    if (i == 0) {
                        ent->unk0x4 |= 0x50;
                        ent->unk0x14->unk0x28 = (u16)cnt;
                    }
                    sub = ent->unk0x14;
                    base = (u8 *)sub + 0x40;
                    end = base + sub->unk0x0;
                    cur = base + sub->unk0x24;
                    strideB = sub->unk0x26 * 2;
                    strideA = sub->unk0x2A * 2;
                    while (cur < end) {
                        s32 tag = *cur & 0xF8;
                        s32 cn;
                        s32 k;

                        if (tag == 0x98 || tag == 0x90 || tag == 0x80) {
                            cn = ((s32)cur[1] << 8) | cur[2];
                            cur += 3;
                            j = 0;
                            if (j < cn) {
                              do {
                                s32 key = ((s32)cur[0] << 8 | cur[1])
                                          + ent->unk0x14->unk0x38;
                                s32 idx = (s32)cur[strideA] << 8
                                          | cur[strideA + 1];
                                u8 *next = cur + strideB;
                                s32 j1 = j + 1;

                                for (k = 0; k < cnt; k++) {
                                    if (keys.i[k] == key) {
                                        if (vals.i[k] == idx) {
                                            cur[0] = (u8)(k >> 8);
                                            cur[1] = (u8)k;
                                            break;
                                        }
                                    }
                                }
                                cur = next;
                                j = j1;
                              } while (j < cn);
                            }
                        } else {
                            break;
                        }
                    }
                    DCFlushRange((u8 *)ent->unk0x14 + 0x40,
                                 ent->unk0x14->unk0x0);
                }
                ent->unk0x14->unk0x38 = 0;
                fn_8007E89C();
                i++;
              } while ((u32)i < (u32)arg0->unk0x24);
            }
        } else {
            Node *sub = ((Ent **)(void *)arg0->unk0x20)[0]->unk0x14;

            cnt = sub->unk0x28;
            cache = sub->unk0x34;
        }
    } else {
        Node *sub = ((Ent **)(void *)arg0->unk0x20)[0]->unk0x14;

        cnt = sub->unk0x28;
        cache = sub->unk0x34;
    }
    {
        s32 bytes = cnt * 12;

        fn_800071D4(keys.i);
        dst = (f32 *)cache;
        src = arg1;
        for (i = cnt; i != 0; i--) {
            dst[0] = src[0];
            dst[1] = src[1];
            dst[2] = src[2];
            fn_8000728C(keys.i, src);
            src += 4;
            dst += 3;
        }
        DCFlushRange(cache, bytes);
    }
    if (fn_8007DF14(arg0->unk0x18)->unk0x8 != 0) {
        i = 0;
        if ((u32)i < (u32)arg0->unk0x24) {
          do {
            Ent *ent = ((Ent **)(void *)arg0->unk0x20)[i];
            Node *sub = ent->unk0x14;

            scp.flt.hi = lbl_80296290;
            keys.ps.t0.ps = __builtin_ps_sub(keys.ps.c.ps, keys.ps.a.ps);
            keys.ps.t1.ps = __builtin_ps_sub(keys.ps.d.ps, keys.ps.b.ps);
            keys.ps.t2.ps = __builtin_ps_muls0(keys.ps.t1.ps, scp.ps);
            keys.ps.t3.ps = __builtin_ps_muls0(keys.ps.t0.ps, scp.ps);
            keys.ps.t4.ps = __builtin_ps_add(keys.ps.a.ps, keys.ps.t3.ps);
            keys.ps.t5.ps = __builtin_ps_add(keys.ps.b.ps, keys.ps.t2.ps);
            sub->unk0x10 = keys.ps.t4.flt.hi;
            sub->unk0x14 = keys.ps.t4.flt.lo;
            sub->unk0x18 = keys.ps.t5.flt.hi;
            keys.ps.t1.ps = __builtin_ps_sub(keys.ps.d.ps, keys.ps.t5.ps);
            keys.ps.t0.ps = __builtin_ps_sub(keys.ps.c.ps, keys.ps.t4.ps);
            res.ps = __builtin_ps_merge00(
                __builtin_ps_mul(keys.ps.t1.ps, keys.ps.t1.ps),
                lbl_80296210);
            res.ps = __builtin_ps_madd(keys.ps.t0.ps, keys.ps.t0.ps, res.ps);
            res.ps = __builtin_ps_sum0(res.ps, res.ps, res.ps);
            res.ps = __builtin_ps_rsqrte(res.ps);
            res.ps = __builtin_ps_res(res.ps);
            sub->unk0x1C = res.flt.hi;
            ent->unk0xC = keys.f[1];
            i++;
          } while ((u32)i < (u32)arg0->unk0x24);
        }
    }
    fn_8007E89C();
}