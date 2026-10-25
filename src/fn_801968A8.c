// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801968A8-0x80196ACC (548B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f64 lbl_802AA600;
extern f32 lbl_802AA608;
void GetElement_2(void *, s32, s32, s32);
s32 GetInteger(CStruct *, u32, s32 *, s32);
s32 Game_GetGoalManager();
s32 fn_8018E24C(Unk_C7387A53 *);
s32 fn_80183D68(Unk_C7387A53 *, s32);
s32 fn_8018CD64(Unk_C8FEE62D *);
void fn_80197FA4(void *);
void fn_80196ACC(Unk_D4A84CA9 *);
void fn_80196EF8(void *, s32);

#define VCALL20(a0) \
    (*(s32 (*)(void *))*(s32 *)((char *)*(void **)((char *)(a0) + 0x14) + 0x24))((char *)(a0) + (int)*(s16 *)((char *)*(void **)((char *)(a0) + 0x14) + 0x20))
#define VCALL98(a0) \
    (*(s32 (*)(void *))*(s32 *)((char *)*(void **)((char *)(a0) + 0x14) + 0x9C))((char *)(a0) + (int)*(s16 *)((char *)*(void **)((char *)(a0) + 0x14) + 0x98))

s32 fn_801968A8(void *arg0) {
    s32 sp8[4];
    register s32 a0 __asm__("r31");
    s32 temp_r30;

    a0 = arg0;
    sp8[0] = 0;
    GetInteger(((Unk_A5B3FAA3 *)a0)->unk0x20, QB_WAIT_TO_ADD_TRICKS, &sp8[0], 0);
    if (sp8[0] != 0) {
        return fn_8018CD64(a0);
    }
    if (VCALL20(a0) != 0) {
        if (VCALL98(a0) == 0 && ((Unk_A5B3FAA3 *)a0)->unk0x548 >= ((Unk_A5B3FAA3 *)a0)->unk0x54C) {
            temp_r30 = Game_GetGoalManager();
            fn_80183D68((void *)temp_r30, fn_8018E24C(a0));
            return 1;
        }
    }
    if (VCALL20(a0) != 0) {
        if (VCALL98(a0) == 0) {
            fn_80197FA4(a0);
        }
    }
    if (VCALL20(a0) != 0) {
        s32 take;
        if ((((Unk_A5B3FAA3 *)a0)->unk0x70 & 0x80000) == 0) {
            {
                register u32 c4330 __asm__("r10");
                register f64 mg __asm__("fr13");
                register f32 lim __asm__("fr12");
                s32 xv;
                xv = ((Unk_A5B3FAA3 *)a0)->unk0x54;
                c4330 = QB_INT_TO_DOUBLE_BIAS;
                __asm__ volatile("" ::: "memory");
                mg = lbl_802AA600;
                sp8[3] = xv ^ 0x80000000;
                __asm__ volatile("" ::: "memory");
                lim = lbl_802AA608;
                sp8[2] = c4330;
                take = (f32)(*(f64 *)&sp8[2] - mg) > lim;
            }
            if (!take) {
                return fn_8018CD64(a0);
            }
        }
        if (VCALL98(a0) == 0) {
            s32 count = 0;
            char *pw;
            s32 i;
            fn_80196ACC(a0);
            pw = (char *)a0 + 0x88;
            for (i = 0x1E; i != 0; i--) {
                s32 v = *(s32 *)pw;
                pw += 0x28;
                if (v == 0) {
                    count += 1;
                }
            }
            GetInteger(((Unk_A5B3FAA3 *)a0)->unk0x20, QB_BLOCK_SIZE, &sp8[1], 1);
            if (count < sp8[1]) {
                s32 lim_a = ((Unk_A5B3FAA3 *)a0)->unk0x548;
                s32 lim_b = ((Unk_A5B3FAA3 *)a0)->unk0x54C;
                if (count + lim_a < lim_b) {
                    s32 mn;
                    s32 m1 = lim_b - lim_a - count;
                    s32 m2 = sp8[1] - count;
                    mn = m2;
                    if (m1 < m2) {
                        mn = m1;
                    }
                    fn_80196EF8(a0, mn);
                }
            }
        }
    }
    return fn_8018CD64(a0);
}
