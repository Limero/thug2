// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018CD64-0x8018D080 (796B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Identification: object active-state gate — dispatches through the object's
// vtable (+0x14) callbacks (0x24/0x9C/0x4C/...) and toggles QB_ACTIVE via
// fn_801907E0; returns 1 to keep the object active, 0 to deactivate.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802A9614;
extern char lbl_802A9618[];
extern char lbl_802A9620[];
extern s32 lbl_80305EAC;
extern s32 lbl_80305EC0;
extern s32 fn_801907E0(s32 arg0, s32 arg1);
extern f32 fn_800144C8(void);
extern s32 fn_80198BA0(s32 arg0);
extern s32 Script_RunScript(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 fn_80190738(Unk_C7387A53 * arg0);
extern s32 ContainsFlag(CStruct * arg0, s32 arg1);
extern s32 fn_801745B4(s32 arg0);
extern void *fn_801403CC(void * arg0);
extern s32 AddChecksum(CStruct * arg0, s32 arg1, s32 arg2);

bool fn_8018CD64(Unk_C8FEE62D *arg0) {
    Unk_89391A04 *temp_r9;

    temp_r9 = arg0->unk0x14;
    if ((temp_r9->unk0x24((void *)((char *)arg0 + temp_r9->unk0x20)) != 0)) {
        temp_r9 = arg0->unk0x14;
        if (temp_r9->unk0x9C((void *)((char *)arg0 + temp_r9->unk0x98)) == 0) {
            fn_801907E0(arg0, QB_ACTIVE);
        }
    }
    temp_r9 = arg0->unk0x14;
    if (temp_r9->unk0x24((void *)((char *)arg0 + temp_r9->unk0x20)) == 0) {
        return true;
    }
    temp_r9 = arg0->unk0x14;
    if (temp_r9->unk0x9C((void *)((char *)arg0 + temp_r9->unk0x98)) != 0) {
        return true;
    }
    temp_r9 = arg0->unk0x14;
    if (((s32 (*)(void *))temp_r9->unk0x4C)((void *)((char *)arg0 + temp_r9->unk0x48)) != 0) {
        {
            s32 var_r30;

            var_r30 = arg0->unk0x54;
            if (var_r30 > 0) {
                arg0->unk0x54 = arg0->unk0x54 - (u32)(fn_800144C8() * lbl_802A9614);
                arg0->unk0x64 += (u32)(fn_800144C8() * lbl_802A9614);
                if (arg0->unk0x54 <= 9999) {
                    if (var_r30 / 1000 > arg0->unk0x54 / 1000) {
                        temp_r9 = arg0->unk0x14;
                        if (((s32 (*)(void *))temp_r9->unk0x54)((void *)((char *)arg0 + temp_r9->unk0x50)) != 0) {
                            if (fn_80198BA0(*(s32 *)&lbl_80305EC0) != 0) {
                                Script_RunScript(QB_TIMER_RUNOUT_BEEP, 0, 0, 0, 0);
                            }
                        }
                    }
                }
            }
        }
    }
    if (fn_80190738((s32)arg0) != 0) {
        if (ContainsFlag(arg0->unk0x20, QB_COMBO_STARTED) == 0) {
            {
                s32 temp_r3;
                void *ptr;

                temp_r3 = fn_801745B4(*(s32 *)&lbl_80305EAC);
                if (temp_r3 != 0) {
                    ptr = fn_801403CC(temp_r3);
                    if (ptr != NULL) {
                        if ((s32)((f32)(f64)((Unk_C8FEE62D *)ptr)->unk0x18 * *((f32 *)&((Unk_C8FEE62D *)ptr)->unk0x6C)) > 0) {
                            AddChecksum(arg0->unk0x20, 0, QB_COMBO_STARTED);
                        }
                    }
                }
            }
        }
    }
    temp_r9 = arg0->unk0x14;
    if (((s32 (*)(void *))temp_r9->unk0x4C)((void *)((char *)arg0 + temp_r9->unk0x48)) == 0) {
        return true;
    }
    temp_r9 = arg0->unk0x14;
    if (((s32 (*)(void *))temp_r9->unk0x14)((void *)((char *)arg0 + temp_r9->unk0x10)) == 0) {
        return true;
    }
    temp_r9 = arg0->unk0x14;
    temp_r9->unk0x34((void *)((char *)arg0 + temp_r9->unk0x30));
    return true;
}
