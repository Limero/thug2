// PARKED 2026-10-10: NEAR 56.2% (size-exact 256B). Tried: hoisted `limit`
// local assigned before frame + recomputed at loop bottom (byte-identical
// object — CSE normalises it away, so the top `add/divw(limit)` before
// `divw(frame)` and the bottom `add/divw` recompute are NOT source-reachable
// through a plain limit local). The div emission order + inner-loop reg map
// (r11 vs r0 base, slwi placement) are scheduler/allocator coins.
// Do not re-grind statement permutations.
// rewritten body — fn_80258938 (256B) from the want disassembly.
//
// Structure decoded from want (this is the strided float-ADD variant of the
// fn_80258880 row-copy loop; the whole 0x80258xxx zone uses fn_80258254 as a
// per-caller 2-arg (obj,key) lookup returning an index or -1):
//
//   The frame index is the quotient of arg2 by arg3, held in r31 with arg2 in
//   r25 and arg3 in r27. The outer loop pre-tests that quotient at 80258958
//   and recomputes it at the bottom from r25 plus r24 added in r6. The lookup
//   call takes two arguments only, arg0 in r3 (homed in r29) and arg4 in r4
//   (homed in r23); r5 is left as the untouched incoming arg2, since a 3-arg
//   call would have needed a register copy into r5 which the reference lacks.
//   A -1 result returns -1 immediately via a compare of r3 against -1, a load
//   of -1 into the return register, and a branch. The source pointer
//   formation takes the count word from the header into scratch, multiplies it
//   by the lookup index, shifts that to a byte offset, and adds it to the
//   table base; the unk0x10 field is a pointer and the index term is a byte
//   offset. The inner loop condition spells the unk0 field itself rather than
//   a cached local, reloading it every iteration from offset 0 off r29 at
//   80258A04, and the compiler turns that while into the guarded do-while the
//   reference has, pre-testing the zeroed r7 index register against the field
//   with the field value shared with the one feeding the multiply. Each inner
//   iteration loads the table entry into r9 off r8 as a byte offset used
//   unscaled by the indexed float load/store pair (so the load is a
//   byte-offset float read of the row), increments the r28 counter, loads the
//   source float into f13 off r3, advances the table pointer by 4, loads the
//   destination float into f0 indexed by r10 plus r9, and advances the source
//   pointer by 4. When the r28 counter reaches arg3 in r27, the wrap block
//   resets the table pointer from r26 and zeroes the counter, advances both
//   the r10 row pointer and the r30 running offset by 4 (the reference carries
//   both variables in step, so the source needs both), and increments the
//   frame index in r31. The iteration then adds f13 into f0, stores f0 back
//   indexed by r10 plus r9, and increments the r7 index. The function returns
//   zero with the return register cleared before the epilogue.
//
// row/rowoff: want's dst base is r10 = r30 = `frame * 4` with NO base add
// anywhere (no `add r10,base,r30`), and r10 is re-copied from r30 at the top
// of each outer iteration (`mr r10,r30`).  That is only reachable when the
// source materialises the pointer from the integer expression, so `row` is
// assigned from `rowoff` (an int -> pointer move, zero instructions) and both
// are advanced by 4 in the wrap block.
// family=m2c range=0x80258938-0x80258A38 size=256B
#include "types.h"
#include "structs.h"

typedef struct {
    s32 unk0;
    char pad0x4[0xc];
    void *unk0x10;
} S8938;

s32 fn_80258254(void *obj, s32 key);

s32 fn_80258938(S8938 *arg0, s32 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 frame;   /* r31 */
    s32 cnt;     /* r28 */
    s32 rowoff;  /* r30 */
    f32 *row;    /* r10 */
    s32 *tbl;    /* r8  */
    s32 i;       /* r7  */
    s32 ret;     /* r3  */
    f32 *src;    /* r3  */
    s32 off;     /* r9  */
    f32 v;       /* f13 */
    f32 d;       /* f0  */

    cnt = 0;
    frame = arg2 / arg3;
    rowoff = frame * 4;
    while (frame < (arg2 + arg5) / arg3) {
        ret = fn_80258254(arg0, arg4);
        if (ret == -1) {
            return -1;
        }
        i = 0;
        src = (f32 *)((char *)arg0->unk0x10 + ret * arg0->unk0 * 4);
        row = (f32 *)rowoff;
        tbl = &arg1[cnt];
        while (i < arg0->unk0) {
            off = *tbl;
            cnt += 1;
            v = *src;
            tbl += 1;
            d = *(f32 *)((char *)row + off);
            src += 1;
            if (cnt == arg3) {
                tbl = arg1;
                cnt = 0;
                row = (f32 *)((char *)row + 4);
                rowoff += 4;
                frame += 1;
            }
            d += v;
            *(f32 *)((char *)row + off) = d;
            i += 1;
        }
    }
    return 0;
}
