// WIP DRAFT (non-matching) — PS record allocator / initialiser.
// family=hand range=0x800598C8-0x800599B0 size=232B
// extra_cflags: -mps-float
//
// Carves a 0x28-byte record out of the static pool at lbl_80364CC8 using the
// index counter lbl_8030089C (capacity 0x96), installs the 16-byte paired-single
// payload from arg1, records arg0 in the record's +0x18 slot and runs the four
// init helpers.
//
// 2026-10-22: 79.31% -> 82.76% (12 -> 10 words, 232B exact). The counter value
// (`t8`) AND the incremented value stored back are two separate webs, and want
// keeps both in r0; pinning the store's operand to r0 as well (a second
// `register s32 inc __asm__("r0")`) is what closes them. Pinning only the load
// (r0 or r8) is worse (77.6%), and r8 for the load with r0 for the increment
// leaves the call's value in the wrong register (74.1%).
//
// REMAINING 10 words: the counter page stays in a scratch other than want's r7,
// the increment comes out as `addic` instead of `addi`, and the prologue copy
// order differs (arg0's save among the float saves). Statement-order and
// flag-style levers that were already measured are listed below.
#include "types.h"
#include "structs.h"
extern char lbl_80364CC8[];
extern f32 lbl_802934B8;
extern f32 lbl_802934BC;
extern s32 lbl_8030089C;
void fn_8005A00C(void *, f32);
void fn_8005A060(void *, s32 *);
void fn_80059F8C(void *, f32);
void fn_8005A180(void *, CStruct *);
void fn_80054E40(void);
void fn_8005ABC8(s32);
void *fn_800598C8(s32 arg0, const __ps_t *arg1, s32 *arg2, CStruct *arg3, f32 farg0, f32 farg1) {
    s32 sp8;
    register s32 a0 __asm__("r28");
    register s32 a3 __asm__("r29");
    register s32 t8 __asm__("r0");
    s32 temp_r10;
    register s32 inc __asm__("r0");
    s32 temp_r30;
    CScript *temp_r31;

    t8 = lbl_8030089C;
    temp_r30 = *arg2;
    a0 = arg0;
    a3 = (s32)arg3;

    if (t8 <= 0x95) {
        temp_r10 = t8 * 0x28;
        temp_r31 = (CScript *)(lbl_80364CC8 + temp_r10);
        inc = t8 + 1;
        lbl_8030089C = inc;
        temp_r31->unk0x18 = a0;
        ((__ps_t *)temp_r31)[0] = arg1[0];
        ((__ps_t *)temp_r31)[1] = arg1[1];
        fn_8005A00C(temp_r31, farg0 * lbl_802934B8);
        sp8 = temp_r30;
        fn_8005A060(temp_r31, &sp8);
        fn_80059F8C(temp_r31, farg1);
        fn_8005A180(temp_r31, (CStruct *)a3);
        if (farg0 > lbl_802934BC) {
            fn_80054E40();
            fn_8005ABC8(a0);
        }
        return temp_r31;
    }
    return NULL;
}
