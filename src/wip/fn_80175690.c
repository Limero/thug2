// PARKED 2026-09-28: 97.2% -> 98.9% (179/181 words, size-exact
// 724B). ScriptChangeLevel: checksum fallback + one guarded do/while change-list walk.
// RESIDUAL: 2 words, both the SAME two-instruction transposition at ONE call site.
//   0x80175738/0x8017573C, fn_8021D454(temp_r31, pa, 1):
//     want `mr r3,r31 ; mr r4,r30`   got `mr r4,r30 ; mr r3,r31`
//   Both moves are expand_call's arg0/arg1 setup for the same callee; the sibling
//   tail call fn_8021D4E8(temp_r31,&fr.iter,1) at 0x8017590C already emits r3-first
//   correctly, so only this one site is rotated. Classic doc-15 2-word transposition:
// 2026-10-12: the 8007272C pin+barrier lever moves it but trades ties:
//   * r3/r4-pinned arg copies ALONE coalesce away (zero change — GPR pins
//     don't stick without a barrier, same as 8007272C's fr1/fr2 pair).
//   * plain copy `a0 = temp_r31` + `__asm__("" : "+r"(a0))` barrier (r3 pin
//     DROPPED as unnecessary) fixes the mrs to want's `mr r3,r31; mr r4,r30`
//     BUT the fenced region re-prioritises the sunk `pb->warning` stb above
//     the arg2 `li r5,1`: residual becomes `li/stb` swapped at 0x80175744/48
//     (still 2 diffs, 98.90%). Kept: it proves the mrs order-fixable and
//     isolates ONE li-vs-sunk-store tie (want sinks the pre-call stb past
//     the whole setup; the fenced scheduler emits it before the li).
//   * NOT tried: moving the pb store (semantics unproven - the call may
//     read pb; want's pre-bl stb does not license a post-call move).
//     Do not re-try pins alone.
//   * TRIED 2026-10-13: staging arg2 (`s32 one2 = 1` in the block, call
//     uses one2) — identical 2 diffs (cprop folds the constant or sched
//     keeps the order; REVERTED).
//   invariant to every param type, return type, decl order and scheduling flag tested.
//
// WHAT WORKED THIS ROUND (three changes, all semantic except the flag):
// 1. `-Os -fno-gcse` added to // FLAG:. gcse was the pass that replaced the loop-head
//    call's ADDR operand with the hoisted/hoistable address register, turning WANT's
//    `addi r3,r1,0x20` into `mr r3,r26`. (Diagnosis: -fno-cse-follow-jumps,
//    -fno-cse-skip-blocks, -frerun-loop-opt, -fno-rerun-loop-opt are all no-ops, so it
//    is gcse, not cse.c and not loop.c.) -fno-rerun-cse-after-loop is now redundant.
//    NOTE this was previously rejected as "destroys the allocation" (19.4%) on the OLD
//    body; with change 2 below it is exactly right, so re-test flags AFTER the source
//    fix, never before.
// 2. `eight`/`one` moved OUT of declaration initialisers into plain statements
//    (C89 forces the decls first, so the li's always got the earliest LUIDs). WANT's
//    loop preheader is `addi r26,r1,0x20 ; li r25,1 ; li r24,8`, i.e. creation order
//    address, one, eight. `one` additionally needs an explicit r25 pin now that
//    -fno-gcse shifts the colouring (sp20p would otherwise take r25 and one r26).
// 3. Named `char *sp20p` in the preheader feeding the two fn_8013CC84 arg2 uses, so
//    the address is a source statement rather than a hoisted invariant. Fresh
//    `&fr.sp20` at fn_80137CB4 is then NOT unified with it.
//
// ARITY AUDIT (the prompt's primary lever) — BOTH NAMED CALLEES ARE FALSE POSITIVES:
//  * 0x800145AC: prologue `stwu r1,-0x10(r1)`; it never reads r3..r9. The `mr r6,r10`
//    / `mr r3,r10` are scratch uses of r10 (it also overwrites r10 itself later, and
//    the caller `bl 0x800145ac` at 0x8017576C sets up no argument registers at all).
//    It is genuinely 0-arg and returns s32 (fctiwz -> lwz r3). `s32 fn_800145AC(void)`
//    is CORRECT. This is the "elapsed-tick" getter; other parked drafts that flag it
//    can skip it.
//  * 0x801FC0E0: `stwu r1,-8(r1)`; `lwz r3,0x1a38(r9)` OVERWRITES r3 before any use and
//    r4 is set with the hash constant, so it reads no argument register either —
//    genuinely 0-arg (it just calls fn_800a398c then fn_8009fdd8 and returns).
//    WANT calls it twice at 0x801757EC/F0 with no arg setup and discards both results;
//    the second call's return chains into fn_801FA284. Current protos are right.
//
// DEAD ENDS THIS ROUND (all byte-identical or worse, do not re-run):
//  * fn_8021D454 proto matrix (void*/Unk_C7387A53*/CStruct*/s32 for arg0, void*/s32 for
//    arg1, void return) x4 - all 97.2% before the fix, all 98.9% after: the A residual
//    is completely proto-independent.
//  * fn_800145AC / fn_801FC0E0 arity and return-type flips - no-op, as predicted above.
//  * Removing any of the pa(r30)/pb(r28)/qa(r22)/qb(r23) pins - all are load-bearing;
//    dropping pa alone drops the whole r22/r28 map (97.8%). Removing the eight(r24) pin
//    is a no-op.
//  * Statement-order variants around the fn_8021D454 call: swap pb stores (96.7%),
//    move temp_r27 = fn_8021B554 before/after the pb stores (95.0/95.6%),
//    move the call itself before the pb stores (76.8%), swap pa->next / pa->sentinel
//    (98.3%, same 3 diffs), stage arg0 into a temp (98.9%, same 2 diffs).
//  * Passing arg2 as the `one` variable instead of the literal 1 - 86.2%.
//  * Flags, all no-ops at 98.9%: -fno-sched-spec, -fno-sched-interblock,
//    -fno-thread-jumps, -fno-delayed-branch, -fno-optimize-register-move, -fno-peephole,
//    -fno-expensive-optimizations, -fcall-used-r3, -fmove-all-movables, -fregmove,
//    -freduce-all-givs, -fno-strength-reduce, -frerun-cse-after-loop.
//    -O1 62.4% / -O2 18.7% / -O3 18.7%; -Os is mandatory.
//  * inline asm for the A transposition: non-volatile 2-insn `mr`/`mr` window
//    allocates its outputs to r4/r31 (97.8%), "=&r" window 97.8%, nested-block and
//    function-scope hard `register s32 __asm__("r3"/"r4")` pins are SILENTLY IGNORED by
//    this cc1 for arg registers (identical output to baseline). Do not re-attempt.
//  * inline asm for the fresh addi: volatile 54.4%, non-volatile 54.4% (breaks the
//    loop CFG), opaque "" "=r" re-birth of the ADDR 28.7%. All worse.
//  * `sp20p` declared with an initialiser / assigned after `eight` - 96.7%; it must be
//    the FIRST statement of the guarded body.
//  * 2026-10-13 edge-asm campaign for the li/stb tie (all 98.9%, T1/T2 trade):
//    routing the stb value through `asm("" : "=r"(warnv) : "r"(warning),"r"(one3))`
//    with the call passing a `one3` variable fixes li/stb to want's [li, stb] BUT
//    flips the UPSTREAM lwz/mr tie to [mr, lwz] (same 2 diffs, new address).
//    Isolation: one3-variable ALONE changes nothing (T1 right, T2 wrong); the EDGE
//    NODES flip T1 — proof the scheduler is global (later nodes reorder an earlier
//    tie), so the two ties are anti-correlated and no local edge fixes both.
//    Non-volatile `li`-asm (one3 born late, ordered on a0+pa) beats volatile
//    (97.8%/96.1% cascades: volatile splits regions, qa/qb + spill recolor).
//    `+r` barrier on the temp_r27 call result is TOXIC (reload recolors the a0
//    chain: `mr r0,r31`, 12 diffs); pins (a0->r3, temp->r27) + named sp48v reload
//    do not save it. Volatile-stb alone is a no-op (base 98.9% retained).
//    Kept: base body (fewest hacks, same score); the T2 fix is real but costs T1.
//
// PREVIOUS ROUNDS (kept for history; all superseded by the above):
//  * 2026-09-28 b2_06: 81.8% -> 97.2%. Fixed the fn_8021D454/fn_8021D4E8 protos to their
//    real definitions (s32,CStruct*,s32), typed fn_8013DC7C as the real 9-arg callee,
//    fn_80137CB4/fn_801FC0E0/fn_801FA284/fn_8022A9B8/fn_802332B8/fn_80222DF4 as
//    pointer-valued, fn_80128978 as returning a separate s32 warning. Left a
//    value-correct alias `(char*)lbl_802A843C - 0x44` for the &lbl_802A83F8 sentinel:
//    naming it directly makes gcse common the two sentinel stores and grows the frame
//    0x88 -> 0x90 (85.1%). Keep the alias.
//  * 2026-09-25: 66.9% -> 81.8% (semantic arity/return-type audit of the QB-script
//    callee family).
//
// Family: doc-15 (arg-setup scheduling) + a gcse loop-invariant-address unification
// that IS source-reachable given the right preheader statement order.
// NO INLINE ASM in this body (0 emitted instructions / 181).
// WIP DRAFT (non-matching) - C body originally generated by tools/fill_wip_drafts.py
// family=m2c range=0x80175690-0x80175964 size=724B
// INERT: not registered in splits.txt/configure.py - never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 30.2% ([4]rev->29.7% [5]rev->30.2%).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef struct ChangeIter {
    s32 value;
    s32 next;
    void *sentinel;
} ChangeIter;

typedef struct ChangeHeader {
    s32 level;
    u8 warning;
    u8 pad0[3];
} ChangeHeader;

// FLAG: -Os -fno-gcse
extern Unk_C7387A53 *lbl_80305F9C;
extern s32 lbl_80305FF8;
extern Unk_59AB5482 lbl_802A83F8;
extern char lbl_802A843C[];
extern char lbl_802A8DC4[];
extern char lbl_802A8DD0[];
extern char lbl_802A8DDC[];
extern s32 GetChecksum_2(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern s32 fn_8021F748(Unk_C7387A53 * arg0);
extern void fn_8021F5C8(Unk_C7387A53 * arg0, s32 arg1);
extern s32 fn_80128978(CStruct * arg0, s32 arg1);
extern s32 StopMusic(s32 arg0);
extern void *fn_8021B554(Unk_C7387A53 * arg0);
extern s32 fn_8021D454(s32 arg0, CStruct * arg1, s32 arg2);
extern void *fn_80137CB4(Unk_9F066EC1 * arg0);
extern s32 fn_800145AC(void);
extern s32 fn_8022986C(CScript * arg0);
extern void *fn_8022A9B8(CScript * arg0);
extern void *fn_802332B8(s32 arg0, s32 arg1);
extern void fn_8013DC7C(void * a, void * b, s32 c, s32 d, void * e, char * f, s32 g, s32 h, s32 i);
extern void *fn_801FC0E0(void);
extern void *fn_801FA284(void * arg0);
extern void fn_8013CC84(void * arg0, void * arg1, Unk_C71E6DE1 * arg2);
extern s32 fn_80222D6C(Unk_C7387A53 * arg0);
extern void fn_80222DA4(Unk_B8D659B7 * arg0, s32 arg1);
extern s32 fn_80222DFC(Unk_C5BAE83F * arg0);
extern void *fn_80222DF4(void * arg0);
extern void fn_8022A8E0(CScript * arg0, s32 arg1);
extern s32 fn_8021D4E8(s32 arg0, CStruct * arg1, s32 arg2);
extern s32 fn_8009CF2C(Unk_C7387A53 * arg0);
extern void fn_8013E184(void * arg0, s32 arg1);
bool ScriptChangeLevel(CStruct *params, CScript *script) {
    struct frame {
        ChangeIter iter;
        char _1C[4];
        u8 sp20;
        u8 sp21;
        u16 sp22;
        void *sp24;
        char _28[4];
        s32 sp2C;
        u8 sp30;
        char _31[0x17];
        s32 sp48;
        char _4C[4];
        ChangeHeader header;
        s32 sp58;
        char _5C[4];
    } fr;
    Unk_C7387A53 *temp_r31;
    register ChangeIter *pa __asm__("r30");
    register ChangeHeader *pb __asm__("r28");
    register ChangeIter *qa __asm__("r22");
    register ChangeHeader *qb __asm__("r23");
    void *temp_r27;
    CScript *var_r28;
    void *temp_r30;
    void *temp_r7;
    void *temp_r30_2;
    void *temp_r7_2;
    void *temp_r29_2;
    u16 temp_r30_3;
    void *temp_r7_3;
    s32 warning;
    temp_r31 = lbl_80305F9C;
    GetChecksum_2(params, QB_LEVEL, &fr.sp48, 1);
    if (fr.sp48 == QB_USE_PREFERENCES) {
        fr.sp48 = fn_8021F748(temp_r31);
    }
    pa = &fr.iter;
    pb = &fr.header;
    fn_8021F5C8(temp_r31, fr.sp48);
    qa = pa;
    qb = pb;
    warning = fn_80128978(params, QB_SHOW_WARNING);
    StopMusic(warning);
    pa->next = 0;
    pa->sentinel = &lbl_802A83F8;
    temp_r27 = fn_8021B554(temp_r31);
    pb->level = fr.sp48;
    pb->warning = warning;
    {
        Unk_C7387A53 *a0;
        a0 = temp_r31;
        __asm__("" : "+r"(a0));
        var_r28 = fn_8021D454(a0, pa, 1);
    }
    if (var_r28 != 0) {
        register s32 eight __asm__("r24");
        register s32 one __asm__("r25");
        char *sp20p;
        sp20p = &fr.sp20;
        one = 1;
        eight = 8;
        do {
            fn_80137CB4(&fr.sp20);
            fr.sp58 = fn_800145AC();
            if ((fn_8022986C(var_r28) == 0) && (fr.sp48 == QB_LOAD_SK5ED_GAMEPLAY)) {
                temp_r30 = fn_8022A9B8(var_r28);
                temp_r7 = fn_802332B8(lbl_80305FF8, 0);
                fn_8013DC7C(temp_r27, temp_r30, 0x6C, 0x3A98U, temp_r7, lbl_802A8DC4, 8, 0, one);
                temp_r30_2 = fn_8022A9B8(var_r28);
                fn_801FC0E0();
                temp_r7_2 = fn_801FA284(fn_801FC0E0());
                fn_8013DC7C(temp_r27, temp_r30_2, 0x88, 0x1132U, temp_r7_2, lbl_802A8DD0, 8, 0, one);
            }
            fr.sp24 = qb;
            fr.sp22 = eight;
            fr.sp30 = eight;
            fr.sp20 = 0x46;
            fr.sp2C = 2;
            fn_8013CC84(temp_r27, fn_8022A9B8(var_r28), sp20p);
            if ((fn_8022986C(var_r28) == 0) && (fn_80222D6C(temp_r31) != 0)) {
                fn_80222DA4(temp_r31, fr.sp48);
                temp_r29_2 = fn_8022A9B8(var_r28);
                temp_r30_3 = fn_80222DFC(temp_r31);
                temp_r7_3 = fn_80222DF4(temp_r31);
                fn_8013DC7C(temp_r27, temp_r29_2, 0x87, temp_r30_3, temp_r7_3, lbl_802A8DDC, 8, 0, one);
            }
            fr.sp24 = &fr.sp58;
            fr.sp22 = 4;
            fr.sp20 = 0x25;
            fn_8013CC84(temp_r27, fn_8022A9B8(var_r28), sp20p);
            fn_8022A8E0(var_r28, fr.sp58);
            var_r28 = fn_8021D4E8(temp_r31, &fr.iter, 1);
        } while (var_r28 != 0);
    }
    if (fn_8009CF2C(temp_r31) == 0) {
        fn_8013E184(temp_r27, 0);
    }
    qa->sentinel = (char *)lbl_802A843C - 0x44;
    return true;
}
// 2026-10-22: 98.9% (was 91.2%): `fr.sp24 = qb` first in the sp20..sp2C block and `fn_8022A9B8` above
// `fn_802332B8`; the residual is the call-site `li r5,1`/`stb` transposition already noted.
