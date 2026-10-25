// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003DB0C-0x8003DBC0 (180B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802FFE98[];
extern s32 lbl_8030042C;
void fn_8000F2F8(Unk_9F352E7C *, s32);
void fn_8000F320(Unk_F12C5E01 *);
s32 fn_8003DBC0(Unk_9994C3F5 *, void *, s8 *, s32 *);
void fn_8003E0B8(void *, Unk_C7387A53 *);
void fn_8005C0D8(s32, s32, s32);
void fn_8005C10C(s32, s32, s32);
void fn_8005C6E8(s32, s32, s32);
bool fn_8003DB0C(Unk_9994C3F5 *arg0, Unk_C7387A53 *arg1, s32 arg2, void *arg3, s32 *arg4) {
    s32 sp8;
    s32 temp_r27;
    Unk_9994C3F5 *temp_r3;

    temp_r3 = *(void * *)&lbl_802FFE98;
    temp_r27 = *arg4;
    fn_8000F2F8(temp_r3, temp_r3->unk0x11C);
    fn_8005C0D8(arg0, 0, 0);
    fn_8000F320(*(void * *)&lbl_802FFE98);
    sp8 = temp_r27;
    fn_8003DBC0(arg0, arg1, arg3, &sp8);
    fn_8003E0B8(arg0, arg1);
    if (lbl_8030042C != 0) {
        fn_8005C6E8(arg0, lbl_8030042C, arg2);
    }
    fn_8005C10C(arg0, arg2, 0);
    return true;
}
