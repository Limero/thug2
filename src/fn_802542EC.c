// PROMOTED 2026-08-31 — 208/208 EXACT. Registered + DOL byte-identical.
// The section-C vtable dispatch was the last wall: `lbl_803CA358[v]` typed
// array indexing (not `(char*)lbl + v*4` char arithmetic) keeps the table
// base in r26 and the raw index in r3, so GCC emits the target's
// `lwzx r9,r26,r3` instead of folding the base into the index register
// (`lwzx r9,r3,r26`). The A/B blocks already used `lbl + v*4` and matched
// because their index was shifted first (slwi -> r0); C's index came
// straight from the call result. Recipe: for a byte-scaled vtable load
// whose index arrives unscaled in a register, use array syntax on a
// pointer-to-array extern (void *lbl_X[]) — not char* arithmetic.
// Entry-block note (2026-08-29): `s32 var_r3 = -0x81;` hoists the li before
// the cmpwi.
#include "types.h"
#include "structs.h"
extern s32 lbl_803CA340;

extern s32 fn_80257E48(CStruct * arg0, s32 arg1);
extern s32 fn_8024EECC(void * arg0, s32 arg1, s32 arg2);
extern s32 fn_80257F04(CStruct * arg0, Unk_DB0E2BAB * arg1);
extern void fn_80253FF4(Unk_31DE137E * arg0);
extern void *lbl_803CA350[];
extern void *lbl_80308040[];
extern void *lbl_803CA358[];

s32 fn_802542EC(Unk_31DE137E *arg0, CStruct *arg1) {
    s32 tbl;
    s32 var_r3 = -0x81;
    Unk_C8FEE62D *ctx;
    s32 i;
    s32 n;
    s32 nb;
    s32 v;
    s32 pA;
    s32 pF;
    s32 retC;
    s32 retD;
    s32 retE;
    s32 *walker;
    CStruct *obj;
    register s32 lblv __asm__("r3");

    ctx = *((void * *)&arg0->unk0x1C);
    if (ctx == NULL) {
    } else {
    i = 0;
    n = fn_80257E48(arg1, 8) + 1;
    ctx->unk0x18 = n;
    if (i < n) {
        walker = (s32 *)((char *)ctx + 0x720);
        i = 0;
        do {
            lblv = lbl_803CA340;
            pA = fn_8024EECC(lblv, 1, 0x34);
            *walker = pA;
            walker += 1;
            if (fn_80257F04(arg1, (void *)pA) != 0) {
                goto fail;
            }
        } while (++i < ctx->unk0x18);
    }
    nb = fn_80257E48(arg1, 6) + 1;
    for (i = 0; i < nb; i++) {
        if (fn_80257E48(arg1, 0x10) != 0) {
            goto fail;
        }
    }
    i = 0;
    n = fn_80257E48(arg1, 6) + 1;
    ctx->unk0x10 = n;
    if (i < n) {
        tbl = lbl_803CA350;
        walker = (s32 *)((char *)ctx + 0x420);
        i = 0;
        do {
            v = fn_80257E48(arg1, 0x10);
            *(s32 *)((char *)walker - 0x100) = v;
            if ((u32)v > 1U) {
                goto fail;
            }
            retC = ((s32 (*)(void *, s32))*(s32 *)((s32 *)lbl_803CA350)[v])(arg0, arg1);
            *walker = retC;
            if (retC == 0) {
                goto fail;
            }
            walker += 1;
        } while (++i < ctx->unk0x10);
    }
    i = 0;
    n = fn_80257E48(arg1, 6) + 1;
    ctx->unk0x14 = n;
    if (i < n) {
        tbl = (s32)lbl_80308040;
        walker = (s32 *)((char *)ctx + 0x620);
        i = 0;
        do {
            v = fn_80257E48(arg1, 0x10);
            *(s32 *)((char *)walker - 0x100) = v;
            if ((u32)v > 2U) {
                goto fail;
            }
            retD = ((s32 (*)(void *, s32))*(s32 *)((s32 *)lbl_80308040)[v])(arg0, arg1);
            *walker = retD;
            if (retD == 0) {
                goto fail;
            }
            walker += 1;
        } while (++i < ctx->unk0x14);
    }
    i = 0;
    n = fn_80257E48(arg1, 6) + 1;
    ctx->unk0xC = n;
    if (i < n) {
        walker = (s32 *)((char *)ctx + 0x220);
        i = 0;
        do {
            v = fn_80257E48(arg1, 0x10);
            *(s32 *)((char *)walker - 0x100) = v;
            if (v != 0) {
                goto fail;
            }
            retE = ((s32 (*)(void *, s32))*(s32 *)lbl_803CA358[v])(arg0, arg1);
            *walker = retE;
            if (retE == 0) {
                goto fail;
            }
            walker += 1;
        } while (++i < ctx->unk0xC);
    }
    i = 0;
    n = fn_80257E48(arg1, 6) + 1;
    ctx->unk0x8 = n;
    if (i < n) {
        walker = (s32 *)((char *)ctx + 0x20);
        i = 0;
        do {
            lblv = lbl_803CA340;
            *walker = fn_8024EECC(lblv, 1, 0x10);
            *(s32 *)((char *)(void *)*walker + 0) = fn_80257E48(arg1, 1);
            *(s32 *)((char *)(void *)*walker + 4) = fn_80257E48(arg1, 0x10);
            *(s32 *)((char *)(void *)*walker + 8) = fn_80257E48(arg1, 0x10);
            *(s32 *)((char *)(void *)*walker + 0xC) = fn_80257E48(arg1, 8);
            obj = (void *)*walker;
            if (obj->unk0x4 > 0) {
                goto fail;
            }
            if (obj->unk0x8 > 0) {
                goto fail;
            }
            if (obj->unk0xC >= ctx->unk0xC) {
                goto fail;
            }
            walker += 1;
        } while (++i < ctx->unk0x8);
    }
        if (fn_80257E48(arg1, 1) == 1) {
            var_r3 = 0;
        } else {
fail:
            fn_80253FF4(arg0);
            var_r3 = -0x85;
        }
    }
    return var_r3;
}
