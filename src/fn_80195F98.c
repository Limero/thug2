// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80195F98-0x801960B0 (280B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Identification: score-based script handler — reads a script s32 prop
// (0x1B35D319), computes the scorepot-style (f32)(f64)(s32)*0x18 * *0x6C
// value, and fires fn_80183F08 when it drops below the threshold.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f64 lbl_802AA248;
extern s32 lbl_80305EAC;
s32 Game_GetGoalManager(void);
s32 fn_8018D7BC(Unk_C7387A53 * arg0);
s32 GetInteger(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
s32 fn_801745B4(s32 arg0);
s32 fn_801403CC(void * arg0);
s32 fn_801813F0(CStruct * arg0);
s32 fn_8018E24C(Unk_C7387A53 * arg0);
s32 fn_80183F08(Unk_C7387A53 * arg0, s32 arg1);
s32 fn_80183D68(Unk_C7387A53 * arg0, s32 arg1);

// PARKED 100% (masked): instruction stream is byte-exact vs want via the
// natural (f32)(f64)(s32) casts — but ngccc synthesizes its private
// 0x4330000080000000 int->double pool constant into MODULE .rodata, while
// the game keeps it in .rodata2 at lbl_802AA248 (= 0x4330000080000000,
// verified dump; same value duplicated at lbl_802AA240 for fn_80195E0C —
// one pool copy per conversion site). Doc-14/.rodata2 routing blocker =>
// promote would shift the DOL (same class as fn_801594D4, §6v-108).
// Manual union dance referencing lbl_802AA248 folds the stw/stw/lfd pack;
// volatile variants break slot sharing. Also note fn_801403CC/fn_801813F0
// are NOT 0-arg: both read r3 (r3 = arg0 passthrough at their bl sites,
// 403cc's return chained into 813f0). Unpark when dtk can route module
// .rodata to .rodata2 or a no-pool source shape appears.
void fn_80195F98(Unk_C7387A53 *arg0) {
    union {
        u32 w[2];
        f64 d;
    } cvt;
    s32 sp8;
    s32 temp_r29;
    Unk_C8FEE62D *temp_r30;
    s32 temp_rX;

    temp_r29 = Game_GetGoalManager();
    if (fn_8018D7BC((s32)arg0) != 0) {
        if (GetInteger(arg0->unk0x20, QB_REQUIRED_SCORE, &sp8,
                        0) != 0) {
            temp_rX = fn_801745B4(lbl_80305EAC);
            if (temp_rX != 0) {
                if ((fn_801813F0(temp_r30 = fn_801403CC(temp_rX)) +
                     (s32)((f32)(f64)temp_r30->unk0x18 *
                           *((f32 *)&temp_r30->unk0x6C)) < sp8)) {
                    fn_80183F08(temp_r29, fn_8018E24C((s32)arg0));
                } else {
                    fn_80183D68(temp_r29, fn_8018E24C((s32)arg0));
                }
            }
        } else {
            fn_80183D68(temp_r29, fn_8018E24C((s32)arg0));
        }
    } else {
        fn_80183F08(temp_r29, fn_8018E24C((s32)arg0));
    }
}
