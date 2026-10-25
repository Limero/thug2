// PARKED: 21.2% — semantic rebuild COMPLETE and structurally faithful
// family=m2c range=0x8022F1F0-0x8022F3FC size=524B
// (hidden-arg chains, hash if-chain replacing m2c's bogus switch, s16 vtable
// offset, lbl-symbol string args, per-site flag reloads via "+r" barrier).
// Remaining walls, stacked:
//   * Saved-reg homes cascade from r17-base vs want r20-base (frame 0x48 vs
//     0x38): want time-shares r30 between outer idx AND entry hash with a
//     pre-computed next-idx in r22 (addi r22,r30,1 hoisted before the inner
//     loop); every C shape gives fresh webs + more saved regs.
//   * Hash compare constants: want rematerializes lis/ori PER SITE in
//     scratch r0; GCC parks them in callee-saved regs across the loop
//     (-fno-gcse tested: 20.8%, also shifts stmw to r14 — removed).
//   * want entry test is fused or. r23,r27,r27 (copy+test on the arg);
//     GCC emits cmpwi for every loop-condition spelling (M4.18 pattern-10
//     family on a rotated list-walk).
//   * want has a DEAD addi r28,r25,0x5c at +0x20 killed by mr r28,r3 at
//     +0xD8 — want-extra-dead-insn class (docs/parkings/33-adjacent).
// Fixes applied that DID work: new-style proto void* fn_802416F8(void *)
// kills the chained-call crclr; "+r" barrier splits the flags andi.-merge.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
// FLAG: -Os

extern char lbl_802FFE98[];
extern char lbl_802B0614[];
extern char lbl_802B0628[];
extern f32 lbl_802B063C;
extern f32 lbl_802B0640;
extern f32 lbl_802B0644;

void fn_8022F3FC(void *);
void fn_8000F2F8(Unk_9F352E7C *, s32);
void fn_8000F320(Unk_F12C5E01 *);
s32 fn_8023FB5C(s32, s32);
void fn_8022CC20(Unk_C8FEE62D *, s32, s32, s32);
s32 fn_802432A0(Unk_9994C3F5 *);
void *fn_802416F8(void *);
s32 fn_80241EB8();
void *fn_80240C80();
s32 fn_80240ED0(CStruct *);
void *fn_8022CBE4(CStruct *, u32, s32);
s32 fn_8022CDB4(Unk_C8FEE62D *);
void fn_8022CE48(Unk_C8FEE62D *, void *);
void fn_8022C8E0(Unk_C8FEE62D *, CStruct *, CStruct *, s32, s32, f32);
void fn_8022CB28(Unk_950BD505 *, void *);

void fn_8022F1F0(Unk_C8FEE62D *arg0, void *arg1) {
    f32 var_f1;
    s32 temp_r0;
    s32 temp_r21;
    s32 temp_r29;
    s32 temp_r30;
    s32 temp_r30_2;
    s32 temp_r3_4;
    s32 var_r24;
    s32 var_r3;
    CStruct *mgr;
    Unk_C8FEE62D *temp_r28;
    Unk_9994C3F5 *glob;

    fn_8022F3FC(arg0);
    glob = *(void **)&lbl_802FFE98;
    fn_8000F2F8(glob, glob->unk0x118);
    temp_r30 = fn_8023FB5C((s32)lbl_802B0614, -1);
    fn_8022CC20((char *)arg0 + (s32)0x5C, temp_r30, fn_8023FB5C((s32)lbl_802B0628, -1), 0);
    fn_8000F320(*(void **)&lbl_802FFE98);
    for (; arg1 != NULL; arg1 = *((void * *)&((Unk_C7387A53 *)arg1)->unk0xC)) {
        mgr = fn_802416F8(fn_802432A0(arg1));
        temp_r0 = mgr->unk0x8;
        if (temp_r0 & 4) {
            __asm__("" : "+r"(temp_r0));
            if (!(temp_r0 & 0x400)) {
            temp_r30 = 0;
            temp_r21 = fn_80241EB8();
            while (temp_r30 < temp_r21) {
                {
                    void *vt = mgr->unk0x38;

                    ((s32 (*)(void *, s32))((Unk_F5317C5D *)vt)->unk0xC)((char *)mgr + ((Unk_F5317C5D *)vt)->unk0x8, temp_r30);
                }
                temp_r28 = fn_80240C80(mgr);
                {
                    s32 nxt;

                    nxt = temp_r30 + 1;
                    for (var_r24 = 0; ; var_r24++) {
                        temp_r30_2 = **((s32 * *)&temp_r28->unk0x14);
                        temp_r3_4 = (s32)fn_8022CBE4((char *)arg0 + (s32)0x24, temp_r30_2, var_r24);
                        if (temp_r3_4 == 0) {
                            break;
                        }
                        temp_r29 = fn_8022CDB4((s32)((char *)arg0 + (s32)0x5C));
                        var_r3 = fn_80240ED0(temp_r28);
                        if (mgr->unk0x8 & 8) {
                            var_r3 = 0;
                        }
                        if ((temp_r30_2 == QB_SK6ED_LADDERSMALL) || (temp_r30_2 == QB_SK6ED_LADDERMID) || (temp_r30_2 == (s32)QB_SK6ED_LADDERTALL)) {
                            var_f1 = lbl_802B0640;
                        } else {
                            var_f1 = lbl_802B063C;
                        }
                        if (temp_r30_2 == (s32)QB_SK6ED_LAMP) {
                            fn_8022CE48((s32)((char *)arg0 + (s32)0x5C), temp_r29);
                        } else {
                            if ((temp_r30_2 == (s32)QB_SK6ED_LAMP_HALF) || (temp_r30_2 == (s32)QB_SK5ED_TELE02)) {
                                var_f1 = lbl_802B0644;
                            }
                            fn_8022C8E0(temp_r29, temp_r3_4, (char *)temp_r28 + (s32)0x18, temp_r28->unk0x28, var_r3, var_f1);
                            fn_8022CB28((s32)((char *)arg0 + (s32)0x5C), temp_r29);
                        }
                    }
                    temp_r30 = nxt;
                }
            }
            }
        }
    }
}
