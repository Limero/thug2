// WIP DRAFT (non-matching) — hand rewrite from WANT disasm
// family=m2c range=0x801AFA18-0x801AFC34 size=540B
// FLAG: -mps-float -Os
// needs -mps-float (PS stack-temp pair copies)
//
// PARKED 2026-09-20 at 74.1% (size-exact, frame/callee-save set exact).
// The lever that got here was -Os: at default -O2 the body scores 62.2% and
// emits a stmw r21 frame (4 label addresses hoisted into r21-r24 for the
// whole loop); -Os drops the hoist and reproduces want's `stwu -0x38` +
// `stmw r25` + per-call `lis/ori` label materialisation exactly.
// Residual (in address order):
//  - arg2/arg3 homing is one register low (want r26/r27, got r27/r28);
//  - the walker tests use `or. r31,r9,r9` (record-form copy, 1 insn) where
//    got coalesces hd/walk into one register and emits `cmpwi r31,0`
//    (2 insns).  Assignment-in-condition forms (`while ((walk = hd) != NULL)`,
//    `if (... != NULL) {}`) and a `void *walk` type change both still
//    coalesce -- ngccc's copy coalescing eats the want's extra move
//    (same class as doc-15's mn/mr copy-shape wall);
//  - want hoists `lwz r3,0x18(r26)` above the `beq` of the loop-entry test
//    (got loads it after the branch).
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// RESTORED 2026-09-20 by tools/restore_best_body.py.  The working body
// scored 40.0% while git revision a66147db0 scores 62.2%;
// the pool's struct-ification sweep and/or tools/store_order_search.py had
// rewritten this body in place and kept the worse result while the notes
// above stayed put.  Winner picked from 16 distinct committed bodies.
// Re-verify with tools/score_addrs.py before editing again.
#include "types.h"
#include "qb_constants.h"

extern char lbl_802ABC94[];
extern char lbl_802ABCA0[];
extern char lbl_802ABCAC[];
extern char lbl_802ABCB4[];
extern void AddInteger(s32, s32, s32);
extern s32 fn_8003E7CC(s32);
extern s32 fn_80128F94(s32);
extern void fn_80129068(s32, s32, s32);
extern s32 fn_801AED20(s32);
extern s32 CStruct_new(s32);
extern s32 CStruct_ctor(s32);
extern void fn_801276E8(s32, s32, s32);
extern s32 fn_801AED74(s32);
extern void fn_801275D4(s32, s32, s32);
extern void fn_8012788C(s32, s32, f32, f32, f32);
extern void fn_80129314(s32, s32, s32);
extern void AddArrayPointer(s32, s32, s32);

s32 fn_801AFA18(s32 arg0, s32 arg1, s32 arg2) {
    __ps_t fr[2];
    __ps_t *base;
    s32 hd;
    s32 walk;
    s32 count;
    s32 handle;
    s32 idx;
    s32 good;
    s32 obj;

    base = (__ps_t *)arg0;
    hd = *(s32 *)((char *)base + 0x10);
    if (*(s32 *)((char *)hd + 4) == -1) {
        hd = 0;
    }
    count = 0;
    walk = hd;
    if (walk != NULL) {
        do {
            hd = *(s32 *)((char *)walk + 0xC);
            if (*(s32 *)((char *)hd + 4) == -1) {
                hd = 0;
            }
            count += 1;
            walk = hd;
        } while (walk != NULL);
    }
    AddInteger(*(s32 *)((char *)arg2 + 0x18), QB_ARRAY_SIZE, count);
    if (count == 0) {
        AddInteger(*(s32 *)((char *)arg2 + 0x18), 0x6A8A0061, 0);
        return 0;
    }
    fn_80129068(handle = fn_80128F94(fn_8003E7CC(0xC)), count, 0xA);
    hd = *(s32 *)((char *)base + 0x10);
    if (*(s32 *)((char *)hd + 4) == -1) {
        hd = 0;
    }
    idx = 0;
    good = 0;
    walk = hd;
    if (walk != NULL) {
        base = fr;
        do {
            if (fn_801AED20(walk) != 0) {
                good += 1;
            }
            fn_801276E8(obj = CStruct_ctor(CStruct_new(8)), (s32)lbl_802ABC94, *(s32 *)((char *)walk + 0x40));
            fn_801275D4(obj, (s32)lbl_802ABCA0, fn_801AED74(walk));
            fn_801276E8(obj, (s32)lbl_802ABCAC, fn_801AED20(walk));
            fn_801276E8(obj, (s32)lbl_802ABCB4, idx);
            fr[0] = *(__ps_t *)((char *)walk + 24);
            base[1] = *(__ps_t *)((char *)walk + 32);
            fn_8012788C(obj, 0x26A4E85A, *(f32 *)&fr[0], *(f32 *)((char *)&fr[0] + 4), *(f32 *)(base + 1));
            fr[0] = *(__ps_t *)((char *)walk + 40);
            base[1] = *(__ps_t *)((char *)walk + 48);
            fn_8012788C(obj, 0x1CD674E6, *(f32 *)&fr[0], *(f32 *)((char *)&fr[0] + 4), *(f32 *)(base + 1));
            fn_80129314(handle, idx, obj);
            hd = *(s32 *)((char *)walk + 0xC);
            if (*(s32 *)((char *)hd + 4) == -1) {
                hd = 0;
            }
            idx += 1;
            walk = hd;
        } while (walk != NULL);
    }
    AddArrayPointer(*(s32 *)((char *)arg2 + 0x18), 0x737449DE, handle);
    AddInteger(*(s32 *)((char *)arg2 + 0x18), 0x6A8A0061, good);
    return 1;
}
