// PARKED 2026-10-01 (agent sweep, non-parked pick): NEAR 40.3% (248B/248B,
// family=hand range=0x800596E4-0x800597DC size=248B
// 37 diffs), up from the 24.2% this file started at. Body is the best known;
// keep it if you edit.
//
// Two changes did all the work, in order of value:
//
// (1) `off += 4` must execute UNCONDITIONALLY at the TOP of the loop body,
//     immediately after `p += 1` and BEFORE the `node == 0` goto — not inside
//     the `if (flag != 0)` tail where m2c put it. In the want, r31 (off) is
//     advanced on every iteration including the one that takes the slot_free
//     exit, so the byte offset is already correct when slot_free does
//     `stwx r3, r30, r31`. Worth ~14 points on its own; every other
//     loop/tail permutation scored 24.2% or less.
//
// (2) `off` needs a SECOND NAME (`off2`) that holds the PRE-increment value
//     and is what slot_free actually indexes with, while `off` runs ahead as
//     the induction variable. Worth ~2 points, and it is the only thing that
//     moved the needle on the residual below — so the direction is right even
//     though it is not yet complete.
//
// STILL OPEN — the residual is register ALLOCATION, not semantics:
//   want copies the pre-increment offset into r11 at 0x59728 and recomputes the
//   offset as the saved value plus 4 into r31 at the loop latch at 0x59758.
// With `off2` the copy is emitted, but in the WRONG SLOT (it lands after the
// `addi` on p instead of before it) and in a different colour (r7 not r11).
// 40.3% is a hard floor: `char*` offset, u32/signed mixes, for-loop comma
// header, four declaration-order permutations of {i,n,off,base,p,node,ret,
// flag}, a second walking pointer, and dropping the `flag` temp all tied at
// 38.7% or regressed. Six distinct attempts landing on the identical score is
// the signature of an alloc-order artifact, not a missing statement — do NOT
// keep permuting the loop body. Next levers, in order: (a) find a way to make
// the copy precede the `p` increment (a barrier or an ordering pin between
// them), (b) shift the live-web count in the block the way the first-walk
// locals did on fn_800A3778, (c) `cc1 -dr` to see whether the post-reload RTL
// is already in want's order.
// The tail is already RIGHT — every tail rewrite tested scored worse (8-11%),
// so do not touch it.
#include "types.h"
#include "structs.h"
extern s32 *lbl_80300498[];
extern s32 lbl_80300898;
s32 fn_80059EB0(s32 arg0);
void *fn_800596E4(s32 arg0) {
    s32 i;
    s32 n;
    s32 off;
    s32 off2;
    s32 *base;
    s32 *p;
    s32 node;
    s32 ret;
    s32 flag;

    i = 0;
    n = lbl_80300898;
    if (i < n) {
        base = lbl_80300498;
        off = 0;
        off2 = 0;
        p = base;
        do {
            node = *p;
            p += 1;
            off2 = off;
            off = off + 4;
            if (node == 0) {
                goto slot_free;
            }
            flag = 1;
            if (((Unk_C7387A53 *)node)->unk0x2C == 0) {
                flag = 0;
            }
            if (flag != 0) {
                i += 1;
            } else {
                return (void *)node;
            }
        } while (i < lbl_80300898);
    }
    n = lbl_80300898;
    if ((n <= 0xFF) && (*(s32 *)((char *)(n * 4) + (s32)lbl_80300498) == 0)) {
        lbl_80300898 = n + 1;
        ret = fn_80059EB0(arg0);
        *(s32 *)((char *)((lbl_80300898 - 1) * 4) + (s32)lbl_80300498) = ret;
        return (void *)ret;
    }
    return 0;
slot_free:
    ret = fn_80059EB0(arg0);
    *(s32 *)((char *)off2 + (s32)base) = ret;
    return (void *)ret;
}
