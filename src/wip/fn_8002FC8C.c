// RE-TRIAGED 2026-10-13: still 19.4% DIFF, size-exact 556B.
// Frame wall (0x5c8 vs 0xa0, missing ~0x532B local) + local-order + regalloc
// per header. No new lever; body unchanged.
// PARKED 2026-10-03: DIFF 19.4% (baseline 18.7%).
// family=m2c range=0x8002FC8C-0x8002FEB8 size=556B
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x8002FC8C
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/want_vs_got.py 0x8002FC8C
//
// SEMANTICS FIXED THIS ROUND (all verified against the disassembly):
//  * 3 undeclared callees (fn_8022986C, fn_8002F298, fn_8013DE78) each cost an
//    extra `crclr cr1eq` word -> declare every callee (doc-56).
//  * fn_8021D358's 2nd arg is `lhz` (u16) at obj+0x1A, not s32/lwz.
//  * arg0->0x78 is loaded ONCE into r11 and reused; it is clobbered at
//    0x8002FD4C (`mr r11,r7`) and re-loaded at 0x8002FD60, so the source has a
//    single `p78` local read at +0x1A and +0x18.
//  * fn_8013DE78 is called with NINE int args, not ten: ngccc only passes 8 int
//    args in registers (proved with a probe TU: 9/10/11-arg calls put arg9..11 on
//    the stack at 8(r1)/0xc/0x10).  r11 in the original is NOT an arg register -
//    it just holds the 4th fctiwz value for the two `sth r11,0x4c/0x14` stores.
//    The 10-arg prototype did reproduce the arg setup, incl. the three dead
//    `mr r8/r10/r11,r7` copies.
//  * the four (s32)(farg*scale) values must stay s32 all the way to the call:
//    declared s16, ngccc emits 4 extra `extsh`.  The struct fields (s16) do the
//    narrowing via `sth`.
//  * the vcall's field at CScript+0x38 is loaded with `lha` (s16), and
//    (arg0->0x64 >> 29) & 1 does give `rlwinm r6,r6,3,0x1f,0x1f` - that part is
//    already exact.
//  * struct C (base +0x40) is a PACKED struct: a@0x40,b@0x41,c(s32)@0x42,
//    v[4]@0x46..0x4c (c is not 4-aligned).  With __attribute__((packed)) every
//    one of those offsets matches the original.
//
// REMAINING DIFF (blocking):
//  1. FRAME: got 0xa0, want 0x5c8.  The fctiwz `stfd` scratch slot is always the
//     last thing GCC allocates, right under the GPR save area: got 0x58 (frame
//     -0x48), want 0x580 (frame -0x48).  So the original body holds an extra
//     ~0x532-byte, 8-byte-aligned object between the last struct field (0x4e) and
//     that scratch slot which is never written or addressed in the emitted code.
//     Adding a pad of that size is the only way found to move the scratch slot;
//     its origin is unknown (not an outgoing-arg area: probe shows ngccc puts
//     stack args at 8(r1), not at the frame top).
//  2. LOCAL ORDER: want A=0x0c, B=0x18, <0x20 bytes>, C=0x40.  Got A=0x10,
//     <0x20 bytes>, C=0x40, B=0x50 - i.e. the two address-taken structs come out
//     in the order C,B regardless of declaration order (both [A,B,pad,C] and
//     [B,A,pad,C] compile byte-identically here).  pad20 is a `volatile s32[8]`
//     placeholder that does put C at 0x40; the original's 0x20 bytes there are
//     equally unexplained.
//  3. A is 4 bytes too high (0x10 vs 0x0c): the outgoing-arg/pad area at the
//     frame bottom differs by one word between the two bodies.
//  4. REGISTER ALLOCATION: got saves r24-r31 (8 GPRs), want saves r25-r29 (5).
//     The original keeps arg0->0x78 in volatile r11 and re-loads it after the
//     arg-setup clobber; it has no long-lived callee-saved copy of p78 /
//     lbl_80305F9C, so its source shape differs from this draft's.
//
// MOST PROMISING NEXT IDEA: reconstruct the real 0x532-byte local (find which
// sibling function in the same TU declares such a buffer - this looks like a
// shared debug/serialise helper), then re-tune A/B slot order; items 3 and 4
// should fall out once the frame is honest.
#include "types.h"
void fn_80031FC4(void *);
s32 fn_8022A9D0(void *arg0);
void fn_80137CB4(void *);
s32 fn_8022986C(void *);
void fn_8002F298(void *, f32);
void fn_8013DE78(void *, void *, void *, s32, s32, s32, s32, s32, s32);
extern f32 lbl_802919AC;
extern f32 lbl_802919B0;
extern char lbl_80305F9C[];
#include "qb_constants.h"
#include "structs.h"

void fn_8002FEF0(Unk_C7387A53 *, s32);
void fn_8002FEB8(void *);
void fn_8021B55C(s32, s32);
s32 fn_8021D358(s32, s32);

/* +0x0c in the frame: {s8,s8,s16[4]} - the param block written before the call */
typedef struct {
    s8 a;
    s8 b;
    s16 v[4];
} Unk_8002FC8C_A;

/* +0x18: initialised by fn_80137CB4, only its first 8 bytes are then set */
typedef struct {
    s8 a;
    s16 b;
    void *c;
} Unk_8002FC8C_B;

/* +0x40: packed - `c` sits at +2, v[] at +6 */
typedef struct __attribute__((packed)) {
    s8 a;
    s8 b;
    s32 c;
    s16 v[4];
} Unk_8002FC8C_C;

void fn_8002FC8C(Unk_A9157FE7 *arg0, s32 arg1, s32 arg2, s8 arg3, s32 arg4, f32 farg0, f32 farg1, f32 farg2, f32 farg3) {
    Unk_8002FC8C_A A;
    Unk_8002FC8C_B B;
    volatile s32 pad20[8];       /* placeholder: original has ~0x20 bytes here */
    Unk_8002FC8C_C C;
    f32 temp_f13;
    s32 temp_r0;
    s32 temp_r27;
    s32 temp_r3;
    s32 temp_r7;
    s32 temp_r8;
    s32 temp_r10;
    s32 temp_r11;
    s32 var_r28;
    s32 p78;
    Unk_C7387A53 *temp_r9;
    void *var_r11;
    void *var_r9;

    var_r28 = arg1;
    if (var_r28 == 0) {
        var_r28 = QB_DEFAULT;
    }
    if ((arg2 != 0) && ((s32) *((s32 *)&arg0->unk0x30) == 0)) {
        p78 = *(s32 *)((char *)arg0 + 0x78);
        temp_r27 = *(s32 *)&lbl_80305F9C;
        temp_r3 = fn_8021D358(temp_r27, *(u16 *)((char *)p78 + 0x1A));
        if ((temp_r3 != 0) && (fn_8022986C(temp_r3) != 0)) {
            fn_80137CB4(&B);
            fn_8021B55C(temp_r27, fn_8022A9D0(temp_r3));
            temp_f13 = lbl_802919AC;
            temp_r0 = *(s32 *)((char *)p78 + 0x18);
            temp_r7 = (s32) (farg0 * temp_f13);
            temp_r8 = (s32) (farg1 * temp_f13);
            temp_r10 = (s32) (farg2 * temp_f13);
            C.b = (s8) temp_r0;
            temp_r11 = (s32) (farg3 * temp_f13);
            C.v[0] = temp_r7;
            C.v[1] = temp_r8;
            C.v[2] = temp_r10;
            C.v[3] = temp_r11;
            B.c = &C;
            B.b = 0xE;
            B.a = 0x29;
            A.b = (s8) temp_r0;
            A.a = arg3;
            A.v[0] = temp_r7;
            A.v[1] = temp_r8;
            A.v[2] = temp_r10;
            A.v[3] = temp_r11;
            C.a = arg3;
            C.c = var_r28;
            fn_8013DE78(&B, &B, &C, 0xE, temp_r7, temp_r8, 0x29, temp_r10, var_r28);
        }
    }
    if ((farg2 == lbl_802919B0) || ((s32) arg0->unk0x54 == 0)) {
        fn_80031FC4(arg0);
    }
    fn_8002F298(arg0, farg2);
    var_r9 = arg0->unk0x24;
    if ((s32) ((CStruct *)var_r9)->unk0x4 == -1) {
        var_r9 = NULL;
    }
    var_r11 = NULL;
    if (var_r9 != NULL) {
        var_r11 = var_r9 - 4;
    }
    temp_r9 = ((CScript *)var_r11)->unk0x18;
    ((s32 (*)(void *, void *, void *, void *, void *, f32, f32, f32, f32))temp_r9->unk0x3C)(var_r11 + (s32)*(s16 *)&temp_r9->unk0x38, var_r28, arg3, ((u32) *((u32 *)&arg0->unk0x64) >> 0x1DU) & 1, arg4, farg0, farg1, farg2, farg3);
    fn_8002FEB8(arg0);
    fn_8002FEF0(arg0, var_r28);
}