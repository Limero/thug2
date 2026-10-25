// PARKED: NEAR 95.5% (42/44 words byte-identical, object .text 176B ==
// symbols.txt size:0xB0). Residual = one 2-word transposition in the ENTRY
// block (counter store vs the `p = &s` home copy); see RESIDUAL below.
//
// WIP DRAFT (non-matching) -- C body derived from the DOL and reworked by hand.
// family=m2c range=0x80009F64-0x8000A014 size=176B
// INERT: not registered in splits.txt/configure.py -- never compiled, not
// counted in objdiff progress.  Verify with:
//   export LEAF_TMPDIR=<private dir>
//   tools/venv/bin/python tools/test_wip_drafts.py --addr 0x80009F64
// Diff: tools/venv/bin/python tools/want_got.py 0x80009F64
//
// WHAT THE FUNCTION IS (reconstructed from the DOL, 0x80009F64..0x8000A014):
// A list walk on a container.  It bumps a nesting counter at arg0+0x04, builds
// a 16-byte list node on the stack whose +0x08 slot is stamped with the
// base-class vtable lbl_8028FF40, then walks the list head at arg0+0x14:
// for every element it calls fn_80009C00 on the element's +0x04 back-pointer
// and sets arg0->0x24 = 1, stopping at the first element whose back-pointer is
// NULL (a +0x04 of -1 means "detached", folded to NULL).  Finally it re-stamps
// the vtable slot and decrements the counter.
//
// ---------------------------------------------------------------- ROUND R2 --
//
// WIN (93.2% -> 95.5%, 3 diffs -> 2): STATEMENT PLACEMENT in the entry block.
// The counter increment must be one of the LAST TWO statements and `p = &s`
// the other; `spv = &s` and `spv->vtable = lbl` must be the FIRST TWO.
// A clean 5x5 placement grid (5 slots, each statement used exactly once)
// gives four orderings that all reach 95.5%:
//   [spv, vtable, next, CNT, P]      <- this file (best; also [next,P,CNT],
//   [spv, vtable, next, P, CNT]           [vtable,P,next,CNT], [vtable,CNT,next,P])
// and every other placement is worse:
//   counter or P before the third node store -> 93.2%
//   P in slot 2 / counter in slots 0-1        -> 79.5%
//   P in slot 0                                -> 77.3%
//   P in slot 1                                -> 11.4%
// So the counter's position IS load-bearing (it was measured as inert earlier,
// at the 90.9% baseline, where the residual was elsewhere).  Re-measure
// statement-order levers after every semantic fix (AGENTS 6bx / 6dh).
//
// ------------------------------------------------------------------ RESIDUAL --
// 2 words, one transposition, in the ENTRY block: at 0x80009F98 the want
// stores r10 to 4(r31) while this build emits the home copy of r9 into r30,
// and at 0x80009F9C the two are swapped — the want emits the copy and this
// build emits the store.
// i.e. want emits the counter STORE last-but-one and the `p = &s` home copy
// (`movsi`, cost 512) LAST; ngccc emits the copy first.  Every other word --
// frame (0x20), stmw/lmw span, the rotated goto, all 4 branch displacements,
// all 5 other stores -- is already identical.
//
// ROOT CAUSE (cc1 -da, ProDG 3.9.3, full pass dumps; corrects the earlier
// sched2-tie note above -- the swap happens in sched1, not sched2):
//   pre-sched1 order (cse2/regmove dumps) is source order:
//     [15 stw vtable][19 stw next][26 stw cnt][29 r30=r9 copy].
//   post-sched1 order (.sched dump) is already [29][15][19][26]; post-reload
//   (.greg dump) keeps the copy before the stores. sched2 only settles it to
//   the observed [15][19][29][26]. So both schedulers pull the reg-only copy
//   early; it is NOT a same-cost tie decided late.
//   Mechanism is readiness chronology, verified against gcc-2.95 sched.c:
//   the copy's dep (r1-based &s addi) is ready ~t=3 and it takes the first
//   free IU slot (t=5, starved at t=3/t=4 by taller work); the counter store
//   needs the load+addi chain (ready t=6). LSU ties break by stable LUID
//   (rank_for_schedule falls through to INSN_LUID), i.e. source order.
//   Confirmed: moving the counter store before the next store in source
//   yields exactly [vtable][cnt][copy][next] (3 diffs) -- LSU follows LUIDs
//   while the copy still floats first. Want [vtable][next][cnt][copy] needs
//   the copy delayed a cycle, which needs a later dep for r9 (unavailable:
//   r1-based) or a shorter load chain (r31-dep fundamental). A volatile
//   reg-only wall between the two reshuffles the block globally (68%);
//
// LEVERS TRIED FOR THE RESIDUAL (all measured on THIS body, all byte-neutral
// or worse; ~70 compiles total):
//   statement placement : the full 5x5 grid above (25 compiles) -- 95.5% is
//       the maximum, and 4 different orderings tie there.
//   store/load order    : counter store before the two node stores (93.2%),
//       node stores after the counter (79.5%), node stores swapped (90.9%).
//   types / aliases     : typed `self->cnt` counter struct (75.0%), typed
//       container with the counter as the first member (95.5% no-op),
//       `s32*` temp instead of `void**` (95.5% no-op), `p = &s + 0` (95.5%),
//       `p = spv` / `p = tmp` (95.5%), `s32`-alias hard pin on r30 (75.0%).
//   pins                : move the pin from `p` to `spv`@r9 (75.0%) or
//       `spv`@r30 (59.1%); pin a COPY of `p` and use the copy (75.0%);
//       drop the pin entirely (13.6% -- `p` coalesces into r9, the frame and
//       every store collapse); `s32`-alias pin (75.0%); nested-scope pin
//       around the assignment (75.0%).
//   volatile / barriers : volatile on the counter STORE (95.5%), on the
//       node stores one at a time (95.5%) or both (90.9%), `volatile S9F64 s`
//       (95.5%), volatile on all three (81.8%), volatile on the `p`
//       declaration (95.5%); zero-code `"+r"` on `p` (70.5%), on the counter
//       temp (95.5%), on the counter's lvalue (13.3%), on the counter's value
//       read (86.4%), on `spv` before `p` (86.4%), on `nbase` REMOVED
//       (88.6% -- it is load-bearing, keep it); `"" ::: "memory"` fence
//       between store and `p` (13.6%).
//   inline asm          : `__asm__("mr %0,%1" : "=r"(p) : "r"(spv))` -> 84.1%
//       non-volatile, 68.2% volatile.  An explicit `mr` PERTURBS the whole
//       allocation, so the 1-insn-asm route is not just inelegant here, it
//       is a regression.  (Same reminder as AGENTS 6fg: do not add
//       `__volatile__` to an otherwise identical `asm` -- it changed 100% to
//       97.3% there.)
//   flags (re-swept on the FIXED body per AGENTS 6bx) : all 95.5% no-ops:
//       -fno-sched-spec, -fno-sched-spec-load, -fno-sched-spec-load-dangerous,
//       -fno-sched-interblock, -fsched-verbose-1/2, -fno-gcse, -fcse-skip-blocks,
//       -fcse-follow-jumps, -ffunction-cse, -fno-thread-jumps,
//       -fno-expensive-optimizations, -fno-caller-saves, -fno-defer-pop,
//       -fno-unroll-loops, -fno-peephole, -fno-strict-aliasing, -fstrict-aliasing,
//       -fno-branch-count-reg, -fno-strength-reduce, -mno-sdata,
//       -fomit-frame-pointer, -O3, -Os, -mcpu=500, -mcpu=750.
//       Regressions: -fno-schedule-insns2 86.4%, -fno-schedule-insns 11.4%,
//       -fno-rerun-cse-after-loop 27.3%, -O1 13.6%, -mcpu=603 79.5%,
//       -mcpu=604 88.6%, -fno-omit-frame-pointer 4.3%,
//       -fcrossjumping does not exist in ProDG cc1.
//   the two remaining ideas, both measured and both dead:
//     (1) a 2-insn volatile asm window holding the counter store
//         (`addi %0,%0,1` / `stw %0,4(%1)`): 75.0% - it fixes the two target
//         words' order but re-allocates the entry block.
//     (2) splitting the RMW so the counter's operand is ready at entry
//         (`cnt = *(s32*)(arg0+4) + 1;` before the node stores, bare store in
//         the counter's slot): byte-neutral at 95.45%, and moving the load
//         after `p = &s` collapses to 9.1%.  The readiness chronology theory
//         in ROOT CAUSE above does not survive its own lever.
//
// ---------------------------------------------------------------- AUDIT --
// object .text = 176 B == symbols.txt size:0xB0 == header range/size   OK
// REL14 (type 11, section-relative, target = fn_addr + addend): 3/3 land on
//   a want branch target -- 0x68 -> 0x80009FCC, 0x7C -> 0x80009FE0,
//   0x40 -> 0x80009FA4.  (The 4th want branch, the entry `b`, is a local `b`
//   and is a REL24, below.)
// REL24 (type 10): local `b` addend 0x4C -> 0x80009FB0 = want's `b` target;
//   `bl` -> fn_80009C00 = want's `bl 0x80009c00`.
// ADDR16 (types 6=HA / 4=LO): 4 relocations, all against lbl_8028FF40, which
//   is a real symbols.txt entry; want's `lis -0x7fd7` + `addi -0xc0` = 0x8028FF40.
// object sections: .text + .rela.text only -- no .rodata/.data/.bss, so no
//   AGENTS-doc-14 int->float pool caveat and masked-EXACT would be promote-clean.
// inline asm: ONE zero-code `"+r"(nbase)` barrier = 0 emitted instructions
//   (0.0% of the 44 instructions).

extern char lbl_8028FF40[];

void fn_80009C00(void *arg0);

/* 16-byte list node built on the stack.  +0x08 is the class pointer:
   the byte-matched src/fn_8000A074.c writes lbl_8028FF40 (the base-class
   vtable) to unk0x8 of an object of this family, and the sibling draft
   src/wip/fn_80009D88.c stamps the same vtable into a stack node at +0x08.
   +0x04 is the link the walk stores the current element into. */
typedef struct S9F64 {
    s32 unk0x0;
    void *next;
    void *vtable;
    s32 unk0xC;
} S9F64;

void fn_80009F64(char *arg0) {
    S9F64 s;
    S9F64 *spv;
    register S9F64 *p __asm__("r30");
    char *nbase;
    register void *node __asm__("r11");
    void *v;

    spv = &s;
    spv->vtable = lbl_8028FF40;
    spv->next = 0;
    *(s32 *)(arg0 + 4) = *(s32 *)(arg0 + 4) + 1;
    p = &s;
    goto check;
loop:
    fn_80009C00(v);
    *(s32 *)(arg0 + 0x24) = 1;
check:
    nbase = arg0 + 8;
    p->next = nbase;
    __asm__("" : "+r"(nbase));
    node = *(void **)(nbase + 0xC);
    if (*(void **)((char *)node + 4) == (void *)-1) {
        node = 0;
    }
    p->next = node;
    v = (node != 0) ? *(void **)((char *)node + 4) : 0;
    if (v != 0) {
        goto loop;
    }
    p->vtable = lbl_8028FF40;
    *(s32 *)(arg0 + 4) = *(s32 *)(arg0 + 4) - 1;
}
