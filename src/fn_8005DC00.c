// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005DC00-0x8005DC6C (108B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void * lbl_803009EC;
void fn_8005DB64(void *, s32, s32);
void fn_8005DBA0(void *, s32, s32);
void *fn_8005DC00(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    CStruct *temp_r31;

    temp_r31 = lbl_803009EC;
    if (temp_r31 != NULL) {
        lbl_803009EC = temp_r31->unk0x10;
    }
    fn_8005DB64(temp_r31, arg0, arg1);
    fn_8005DBA0(temp_r31, arg2, arg3);
    return temp_r31;
}
