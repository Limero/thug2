// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004F4E4-0x8004F6B8 (468B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f32 lbl_80292C6C;
extern s32 lbl_80301A78;
#include "qb_constants.h"
s32 fn_800A54AC(s32, s32, s32, s32, s32, s32, f32);
#include "structs.h"
void fn_800A3B90(Unk_C7387A53 *, s32, s32);
void fn_8004F85C(Unk_0055B719 *);
s32 fn_8009EF74(Unk_C8FEE62D *, void *);
s32 fn_8004C858(s32, s32);
s32 fn_80042180(Unk_C7387A53 *);
s32 fn_8004C414(Unk_9E4B1D7B *, s32);
bool fn_8004F4E4(Unk_AD9AE6AA *arg0, CStruct *arg1) {
    s32 temp_r29;
    s32 temp_r29_2;
    Unk_07FDFB02 *temp_r9;

    temp_r29 = arg0->unk0x10;
    if (((fn_8004215C() != 0) && (fn_8004C414(temp_r29, arg1->unk0x0) != 0) && ((fn_80042180(arg0) == 0) || (fn_8004C858(temp_r29, arg0->unk0x18) == 0))) || (fn_8009EF74(arg0, arg1) == 0)) {
        return false;
    }
    temp_r29_2 = *(s32 *)&lbl_80301A78;
    if ((s32) arg1->unk0x0 == QB_NOTIFY_CHILD_LOCK) {
        fn_8004F85C(arg0);
        temp_r9 = arg0->unk0x8;
        arg0->unk0x1C0 = 1;
        ((s32 (*)(void *))temp_r9->unk0x5C)((char *)arg0 + temp_r9->unk0x58);
        fn_800A3B90(arg1, arg0->unk0x18, 0);
    }
    if ((s32) arg1->unk0x0 == QB_FOCUS) {
        if ( arg0->unk0x1AC == NULL) {
            fn_8004F85C(arg0);
        }
        if ((s32) arg0->unk0x1BC == 0) {
            arg0->unk0x1BC = 1;
            fn_800A54AC(temp_r29_2, QB_FOCUS, *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x1AC) + 0x18), QB_SYSTEM, arg1->unk0x10, 0, *(f32 *)&lbl_80292C6C);
            fn_800A3B90(arg1, arg0->unk0x18, 0);
        }
    }
    if (((s32) arg1->unk0x0 == QB_UNFOCUS) && ((s32) arg0->unk0x1BC != 0)) {
        fn_8004F85C(arg0);
        arg0->unk0x1BC = 0;
        fn_800A54AC(temp_r29_2, QB_UNFOCUS, *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x1AC) + 0x18), QB_SYSTEM, 0, 0, *(f32 *)&lbl_80292C6C);
        fn_800A3B90(arg1, arg0->unk0x18, 0);
    }
    return true;
}
