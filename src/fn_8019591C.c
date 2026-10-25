// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019591C-0x80195AAC (400B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802AA0F4;
extern f64 lbl_802AA0F8;
void AddInteger(CStruct * arg0, s32 arg1, s32 arg2);
s32 fn_80195B14(Unk_C7387A53 * arg0);
f32 fn_800144C8(void);
s32 Game_GetGoalManager(void);
s32 fn_8018E24C(Unk_C7387A53 * arg0);
s32 fn_80183F08(Unk_C7387A53 * arg0, s32 arg1);
s32 fn_80183D68(Unk_C7387A53 * arg0, s32 arg1);
void fn_8018CD64(Unk_C8FEE62D * arg0);

void fn_8019591C(Unk_5B7A0D8F *arg0) {
    s32 var_r30;
    Unk_89391A04 *temp_r9;

    AddInteger(arg0->unk0x20, QB_LAST_TIME_ON_CAMERA,
                arg0->unk0x78);
    temp_r9 = arg0->unk0x14;
    if (temp_r9->unk0x24(
            (char *)arg0 + temp_r9->unk0x20) == 0)
        goto cd64;
    temp_r9 = arg0->unk0x14;
    if (temp_r9->unk0x9C(
            (char *)arg0 + temp_r9->unk0x98) != 0)
        goto cd64;
    {
        s32 t74;
        f32 tf1;
        s32 v9;
        s32 t78n;
        s32 c78;
        s32 c7c;
        s32 t84;

        t74 = arg0->unk0x74;
        var_r30 = 0;
        if (t74 != 0) {
            if (fn_80195B14((s32)arg0) != 0) {
                tf1 = fn_800144C8() * lbl_802AA0F4;
                if (!(tf1 >= lbl_802AA0F8)) {
                    v9 = (s32)tf1;
                } else {
                    v9 = (s32)(tf1 - lbl_802AA0F8) ^ (s32)0x80000000;
                }
                t78n = arg0->unk0x78 + v9;
                arg0->unk0x78 = t78n;
                AddInteger(arg0->unk0x20,
                            QB_TIME_ON_CAMERA, t78n);
            }
            c78 = arg0->unk0x78;
            c7c = arg0->unk0x7C;
            if ((u32)c78 >= (u32)c7c) {
                var_r30 = 1;
            } else if ((u32)(c7c - c78) >
                       arg0->unk0x54) {
                fn_80183F08(Game_GetGoalManager(), fn_8018E24C((s32)arg0));
                return;
            }
        } else {
            t84 = arg0->unk0x84;
            if ((t84 != 0) &&
                (arg0->unk0x88 >= t84)) {
                var_r30 = 1;
            }
        }
        if (var_r30 != 0) {
            fn_80183D68(Game_GetGoalManager(), fn_8018E24C((s32)arg0));
            return;
        }
    }
cd64:
    fn_8018CD64((s32)arg0);
}