// WIP DRAFT — PARKED (non-matching). Hand-rebuilt from the want; the m2c draft
// compiled to 348 B of 740 B because its `switch` had NO case labels, so all
// nine arms folded into one block. (Same bug as fn_80139EF4 / fn_8012D190 —
// see AGENTS §6gw/§6gx; 8 drafts still carry it — see §6gz on stripping
// comments before running that scan.)
// reproduce: LEAF_TMPDIR=<scratch> \
//     tools/venv/bin/python tools/want_got.py 0x8012A260  -> 716B / 160 diffs / 10.61%
//
// family=m2c range=0x8012A260-0x8012A544 size=740B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// Progression: 348 B (husk, 79 diffs) -> 704 B -> 716 B, frame -0x28 exact.
//
// ------------------------------------------------------------------ decode
// 9 cases on `*(u8 *)(arg0 + 2)`, tested as a balanced tree: 1,2 / 3,4 / 5 / 6 /
// 0xA / 0xC / 0xD, with 0 and everything else falling to the shared exit.
//   1, 2, 0xD  share a body: cost = n * 4, loop fn_8012CB7C
//   3, 4        byte-copy loop (strings + a NUL pad), NOT s32 stores
//   5          cost = n * 8, two fn_8012CBA0 calls
//   6          cost = n * 0xC, three fn_8012CBA0 calls
//   0xA        loop fn_80129C08(elem, dst, left, arg3, 0)  -- FIVE args
//   0xC        recursive fn_8012A260(elem, dst, left, arg3)
//
// FOUR decode errors in the m2c draft, all arity/type:
//  1. Cases 3/4 wrote `*(s32 *)dst = ...` but want stores BYTES (`stb`). The
//     draft treated a string buffer as a word array.
//  2. fn_8012CB7C is TWO args (dst, elem). The draft passed four
//     `(arg0, arg1, dst, elem)`.
//  3. fn_80129C08 is FIVE args with a trailing literal 0 (`li r7,0`). The draft
//     passed five but with the wrong shape.
//  4. The element count is read with `clrlwi r4, r26, 0x10`, i.e. masked to 16
//     bits before the fn_8012CBD4 call -- the draft passed the raw field.
//
// Also: `*(s32 *)((char *)arg0 + 2)` in the draft is really a BYTE load (`lbz`)
// of the case selector, and the count is a separate `lwz` at +4.
//
// ------------------------------------------------------------------- parked
// Frame and prologue are exact (-0x28, stmw r24/8, LR 0x2c, r24/r28 for arg2/arg0).
// Remaining gap is switch-tree shape and register choice:
//   * want tests `cmpwi kind,4` / `cmpwi kind,3` first and reaches 5/6 via the
//     >4 arm; got tests `cmpwi kind,5` first. Same case SET, different tree -- so
//     want's source order is not simply ascending. Adding an explicit `case 0:`
//     did not change it. Not resolved; recorded rather than guessed at.
//   * want holds arg1/dst in r31 and arg3 in r27; got picks r9/r25.
// 24 B short of the want.
#include "types.h"

typedef struct Elem Elem;
struct Elem {
    char data[4];
};

s32 fn_8012CBD4(u8 *, u32);
void *fn_801291FC(void *);
s32 fn_8012CB7C(u8 *, Elem *);
s32 fn_8012CBA0(f32);
s32 fn_80129C08(Elem *, u8 *, u32, u32, u32);
s32 fn_8012A260(void *, u8 *, u32, u32);

s32 fn_8012A260(void *arg0, u8 *arg1, u32 arg2, u32 arg3) {
    u32 n;
    u32 left;
    u8 kind;
    u8 *dst;
    u32 i;
    void *list;
    Elem *e;
    s32 r;
    u32 cost;

    if (arg2 <= 2) {
        return 0;
    }
    n = *(u32 *)((char *)arg0 + 4);
    kind = *(u8 *)((char *)arg0 + 2);
    *arg1 = kind;
    dst = (u8 *)fn_8012CBD4(arg1 + 1, n & 0xFFFF);
    left = arg2 - 3;

    switch (kind) {
    case 1:
    case 2:
        goto shared_12d;

    case 3:
    case 4: {
        list = fn_801291FC(arg0);
        for (i = 0; i < n; i++) {
            char *s = (char *)((Elem **)list)[i];
            u8 nul = 0;
            if (*s == 0) {
                goto pad;
            }
            while (*s != 0) {
                if (left == 0) {
                    return 0;
                }
                left--;
                *dst++ = (u8)*s;
                s++;
            }
        pad:
            if (left == 0) {
                return 0;
            }
            *dst++ = nul;
            left--;
        }
        break;
    }

    case 5: {
        cost = n * 8;
        r = 0;
        if (cost > left) {
            break;
        }
        list = fn_801291FC(arg0);
        for (i = 0; i < n; i++) {
            e = ((Elem **)list)[i];
            r = fn_8012CBA0(*(f32 *)((char *)e + 4));
            r = fn_8012CBA0(*(f32 *)((char *)e + 8));
            dst = (u8 *)r;
        }
        left -= cost;
        break;
    }

    case 6: {
        cost = n * 0xC;
        r = 0;
        if (cost > left) {
            break;
        }
        list = fn_801291FC(arg0);
        for (i = 0; i < n; i++) {
            e = ((Elem **)list)[i];
            r = fn_8012CBA0(*(f32 *)((char *)e + 4));
            r = fn_8012CBA0(*(f32 *)((char *)e + 8));
            r = fn_8012CBA0(*(f32 *)((char *)e + 0xC));
            dst = (u8 *)r;
        }
        left -= cost;
        break;
    }

    case 0xA: {
        list = fn_801291FC(arg0);
        for (i = 0; i < n; i++) {
            e = ((Elem **)list)[i];
            r = fn_80129C08(e, dst, left, arg3, 0);
            if (r == 0) {
                return 0;
            }
            dst += r;
            left -= r;
        }
        break;
    }

    case 0xC: {
        list = fn_801291FC(arg0);
        for (i = 0; i < n; i++) {
            e = ((Elem **)list)[i];
            r = fn_8012A260(e, dst, left, arg3);
            if (r == 0) {
                return 0;
            }
            dst += r;
            left -= r;
        }
        break;
    }

    case 0xD:
    shared_12d:
        cost = n * 4;
        r = 0;
        if (cost > left) {
            break;
        }
        list = fn_801291FC(arg0);
        for (i = 0; i < n; i++) {
            e = ((Elem **)list)[i];
            dst = (u8 *)fn_8012CB7C(dst, e);
        }
        left -= cost;
        break;

    default:
        break;
    }
    return arg2 - left;
}