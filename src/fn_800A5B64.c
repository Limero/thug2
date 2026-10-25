// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A5B64-0x800A5BF4 (144B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802FFE98[];
void fn_8000F320(Unk_F12C5E01 *);
void fn_800A5DBC(CStruct *, s32);
void fn_800A6E5C(CStruct *, s32 *, s32);
void fn_800A6E0C(s32);
s32 fn_800A6DB8(s32, s32, s32);
void fn_8000F2F8(Unk_9F352E7C *, s32);
void fn_800A5B64(CStruct *arg0, s32 arg1, s32 arg2) {
    s32 sp8;
    s32 var_r31;
    Unk_C7387A53 *temp_r3;

    temp_r3 = *(void * *)&lbl_802FFE98;
    sp8 = arg1;
    fn_8000F2F8(temp_r3, temp_r3->unk0x12C);
    var_r31 = fn_800A6DB8(arg0->unk0x10, &sp8, 1);
    if (var_r31 == 0) {
        fn_800A6E0C(0x1C);
        var_r31 = fn_800A5D90();
        fn_800A6E5C(arg0->unk0x10, &sp8, var_r31);
    }
    fn_800A5DBC(var_r31, arg2);
    fn_8000F320(*(void * *)&lbl_802FFE98);
}
