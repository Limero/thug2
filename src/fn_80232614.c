// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80232614-0x802327DC (456B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80301A78;
extern f32 lbl_802B08D0;
s32 fn_8023C598(s32);
void fn_8023E18C(void *, s32);
void fn_8023E0F8(void *, s32);
void fn_80233450(s32);
void fn_800A54AC(void *, s32, s32, s32, s32, s32, f32);
void fn_80232614(Unk_C7387A53 *arg0) {
    s32 var_r9;
    s32 var_r9_2;
    s32 var_r9_3;
    s32 var_r9_4;

    var_r9 = 1;
    if (!(arg0->unk0x48 & 0x200)) {
        var_r9 = 0;
    }
    if (var_r9 != 0) {
        fn_8023E18C(fn_8023C598(1), -1);
        fn_80233450(arg0);
        fn_800A54AC(lbl_80301A78, QB_PARKED_MENU_UP, QB_SET_MENU_CONTAINER, QB_SYSTEM, 0, 0, lbl_802B08D0);
    }
    var_r9_2 = 1;
    if (!(arg0->unk0x48 & 0x400)) {
        var_r9_2 = 0;
    }
    if (var_r9_2 != 0) {
        fn_8023E18C(fn_8023C598(1), 1);
        fn_80233450(arg0);
        fn_800A54AC(lbl_80301A78, QB_PARKED_MENU_DOWN, QB_SET_MENU_CONTAINER, QB_SYSTEM, 0, 0, lbl_802B08D0);
    }
    var_r9_3 = 1;
    if (!(arg0->unk0x48 & 8)) {
        var_r9_3 = 0;
    }
    if (var_r9_3 != 0) {
        fn_8023E0F8(fn_8023C598(1), -1);
        fn_80233450(arg0);
        fn_800A54AC(lbl_80301A78, QB_PARKED_MENU_LEFT, QB_PIECE_MENU_CONTAINER, QB_SYSTEM, 0, 0, lbl_802B08D0);
    }
    var_r9_4 = 1;
    if (!(arg0->unk0x48 & 0x10)) {
        var_r9_4 = 0;
    }
    if (var_r9_4 != 0) {
        fn_8023E0F8(fn_8023C598(1), 1);
        fn_80233450(arg0);
        fn_800A54AC(lbl_80301A78, QB_PARKED_MENU_RIGHT, QB_PIECE_MENU_CONTAINER, QB_SYSTEM, 0, 0, lbl_802B08D0);
    }
}
