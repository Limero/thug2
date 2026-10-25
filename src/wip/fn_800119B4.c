// WIP DRAFT (non-matching) — hand-corrected C body, 62.3% (20/53 words differ)
// family=m2c range=0x800119B4-0x80011A88 size=212B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED: size-EXACT (212B = 0xD4 ✓) and instruction-for-instruction identical
// to WANT — the residual 20 words are ALL a callee-saved register permutation
// (r28-r31 roles rotated), not a structural difference. Verified with
// tools/want_got.py --file: every >>> row is the same mnemonic+shape with
// different register numbers.
//
// What this draft got right (levers that took it 38.2% -> 62.3%):
//  1. `lbl_802FFEE8` must be declared `extern s32` (folded `lis`+disp form),
//     not `extern char []`.
//  2. The vcall's offset field at +0x20 is **s16** (`lha`), not s32.
//  3. Both call results share the type of a 24+8 bitfield word at +0x8:
//         typedef struct { u32 hi : 24; u32 lo : 8; } W;   // lo == byte +0xB
//     That single type change fixes three things at once: `w.hi` reads as
//     `lwz`+`srwi 8`, `w.lo` reads as `lbz 0xB`, and the store `w.hi = sum`
//     emits the single `rlwimi rD,rS,8,0,0x17` WANT has.
//     (Probe-verified rule: `(w & 0xFF) | (v << 8)` emits `slwi`+`rlwimi`
//     = 2 insns; only a bitfield assignment emits the lone `rlwimi`. See the
//     24+8 type above — this is the general fix for that diff shape.)
//  4. The `lbl_802FFEE8 = 0;` store must reuse a named zero (`zero = 0;`
//     materialised as `li r25,0` right after the first call) instead of a
//     literal 0 (`li r0,0` at the store site).
//  5. The final sum needs a `(char *)` cast — typing the result pointer as the
//     bitfield struct makes the return a pointer-add and emits `mulli ×2`.
//
// Residual (exhaustively probed, no lever moved it): WANT homes the param copy
// (`mr r31,r4`), the first call result (r28), the second call result (r29) and
// the masked value (r30); GCC homes them r29/r30/r28/r29 — it coalesces the
// param copy with the masked value, needing only 6 callee-saved values where
// WANT uses 7. Tried with no effect (<0.1% delta): 8 declaration orders,
// arg1 used directly vs copied to a temp, u32 vs s32 for arg1 / the masked
// value / the call-result vars, a fresh name for the second temp, a staged
// second temp, u32 call-result typing, and an explicit extra live use of the
// param. Swapping the two `fn_80010768` cleanup calls (want's order is
// first-result-then-second) drops to 37.7% and an extra late use drops to
// 33.9%, so the statement order is already correct.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_80010B38(s32);
s32 fn_80010764(s32);
s32 fn_80011E00(CStruct *, void *);
s32 fn_80010768(void *);
extern s32 lbl_80290628;
extern s32 lbl_802FFEE8;

/* 24-bit field followed by the 8-bit byte at +0xB (see note 3 above). */
typedef struct {
    u32 hi : 24;
    u32 lo : 8;
} T119B4Word;

typedef struct {
    char _pad0[8];
    T119B4Word w;
} T119B4;

void *fn_800119B4(Unk_C7387A53 *arg0, s32 arg1, s32 arg2) {
    s32 temp_r30;
    s32 temp_r30_2;
    s32 temp_r31;
    T119B4 *temp_r29;
    T119B4 *temp_r3;
    Unk_C7387A53 *temp_r9;
    s32 zero;
    s32 vret;

    temp_r31 = arg1;
    lbl_802FFEE8 = 1;
    temp_r3 = (T119B4 *)fn_80010B38(arg2);
    zero = 0;
    temp_r9 = arg0->unk0x80;
    temp_r30_2 = (temp_r31 + 3) & QB_UNKNOWN_0xFFFFFFFC;
    vret = ((s32 (*)(void *, void *, s32))temp_r9->unk0x24)(
        (char *)arg0 + *((s16 *)&temp_r9->unk0x20),
        temp_r30_2 - temp_r3->w.hi, 1);
    temp_r29 = (T119B4 *)fn_80010B38(vret);
    fn_80010768(temp_r3);
    fn_80010768(temp_r29);
    temp_r31 = temp_r30_2 + temp_r3->w.lo;
    fn_80011E00((char *)arg0 + 4, 1);
    temp_r30 = lbl_80290628;
    temp_r29->w.hi = temp_r31 + temp_r30;
    fn_80010764(temp_r29);
    lbl_802FFEE8 = zero;
    return (char *)temp_r29 + temp_r30 + temp_r29->w.lo;
}
