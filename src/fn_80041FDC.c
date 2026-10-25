// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80041FDC-0x80042110 (308B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-expensive-optimizations
#include "types.h"
extern f32 lbl_80292398;
extern char lbl_80301A78[];
#include "qb_constants.h"
#include "structs.h"
s32 fn_800A54AC(Unk_AD65BA9A *, void *, s32, s32, void *, s32, f32);
s32 fn_800A3B90(s32, s32, s32);
s32 CStruct_delete(s32, s32);
void AddInteger(CStruct *, void *, void *);
void CStruct_ctor(s32);
s32 fn_800A3BDC(CStruct *);
s32 fn_8009EF74(Unk_C8FEE62D *, void *);
s32 fn_8004C858(s32, s32);
s32 fn_80042180(Unk_C7387A53 *);
s32 fn_8004C414(Unk_9E4B1D7B *, s32);
bool fn_80041FDC(Unk_F6E3A2C3 *arg0, s32 *arg1) {
    s32 sp8;
    s32 temp_r30;
    s32 temp_r30_2;
    s32 temp_r9;

    temp_r30 = arg0->unk0x10;
    if (((fn_8004215C() != 0) && (fn_8004C414(temp_r30, *arg1) != 0) && ((fn_80042180(arg0) == 0) || (fn_8004C858(temp_r30, arg0->unk0x18) == 0))) || (fn_8009EF74(arg0, arg1) == 0)) {
        return false;
    }
    temp_r9 = *arg1;
    if ((temp_r9 == QB_FOCUS) || (temp_r9 == QB_UNFOCUS)) {
        if ((s32) arg0->unk0x190 != 0) {
            temp_r30_2 = fn_800A3BDC(arg1);
            CStruct_ctor(&sp8);
            AddInteger(&sp8, QB_CONTROLLER, temp_r30_2);
            fn_800A54AC(*(s32 *)&lbl_80301A78, *arg1, arg0->unk0x190, QB_SYSTEM, &sp8, 0, lbl_80292398);
            CStruct_delete(&sp8, 2);
        }
        fn_800A3B90(arg1, arg0->unk0x18, 0);
    }
    return true;
}
