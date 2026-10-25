// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80195E0C-0x80195F98 (396B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Identification: object interaction/script handler — looks up a named object
// (lbl_80305EAC via fn_801745B4), checks hash properties and +0x144 flags,
// calls the +0xAC vtable callback.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EAC;
s32 fn_801960B0(Unk_C7387A53 * arg0, s32 arg1);
s32 fn_8018D924(Unk_C7387A53 * arg0);
s32 fn_801745B4(s32 arg0);
s32 GetChecksum_3(Unk_6A70655D * arg0, s32 arg1);
s32 Game_GetGoalManager(void);
s32 fn_8018E24C(Unk_C7387A53 * arg0);
s32 fn_80183BC0(Unk_C7387A53 * arg0, s32 arg1, s32 arg2);
s32 GetChecksum_2(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
s32 fn_8018D8D0(s32 arg0, s32 arg1, s32 arg2);

// PARKED 100% (masked): instruction stream is byte-exact vs want via the
// natural (f32)(f64)(s32) casts — but ngccc synthesizes its private
// 0x4330000080000000 int->double pool constant into MODULE .rodata, while
// the game keeps it in .rodata2 at lbl_802AA240 (= 0x4330000080000000,
// verified dump). Doc-14/.rodata2 routing blocker => promote would shift
// the DOL (same class as fn_801594D4, §6v-108). Manual union dance
// referencing lbl_802AA240 folds the stw/stw/lfd pack into registers
// (never matches); volatile/statement-expression variants break slot
// sharing + saved-reg span. Unpark when dtk can route module .rodata to
// .rodata2 or a source shape forces real stores without volatility.
void fn_80195E0C(Unk_C8FEE62D *arg0, s32 arg1) {
    s32 sp8;
    s32 temp_r28;
    s32 temp_r29;
    Unk_C7387A53 *temp_r30;
    Unk_C8FEE62D *temp_r8;
    Unk_5BE2D2B7 *temp_r9;

    temp_r28 = fn_801960B0(arg0, arg1);
    if (temp_r28 != 0) {
        temp_r9 = *((void * *)&arg0->unk0x14);
        if (temp_r9->unk0xAC(
                (char *)arg0 + temp_r9->unk0xA8) == 0) {
            if (fn_8018D924((s32)arg0) == 0) {
                temp_r29 = fn_801745B4(lbl_80305EAC);
                if (temp_r29 != 0) {
                    temp_r30 = GetChecksum_3(temp_r29, QB_SKATERSTATE);
                    temp_r8 = (void *)(*(s32 *)((char *)GetChecksum_3(
                        temp_r29, QB_SKATERSCORE) + (s32)0x1C));
                    if ((temp_r30->unk0x144 != 0) ||
                        ((s32)((f32)(f64)temp_r8->unk0x18 *
                              *((f32 *)&temp_r8->unk0x6C)) >
                         0)) {
                        temp_r9 = *((void * *)&arg0->unk0x14);
                        if (temp_r9->unk0x24(
                                (char *)arg0 +
                                temp_r9->unk0x20) ==
                            0) {
                            fn_80183BC0(Game_GetGoalManager(),
                                        fn_8018E24C((s32)arg0), 0);
                        }
                        GetChecksum_2(temp_r28, QB_FLAG, &sp8, 1);
                        if (fn_8018D8D0(arg0, sp8, 0) == 0) {
                            temp_r9 =
                                *((void * *)&arg0->unk0x14);
                            temp_r9->unk0xA4(
                                (char *)arg0 +
                                    temp_r9->unk0xA0,
                                sp8, 1, 0);
                        }
                    }
                }
            }
        }
    }
}
