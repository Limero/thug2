// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800643E8-0x80064494 (172B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8012EE64(Unk_069CE08E *, s32);
void fn_8012F260(Unk_15EF4A35 *, s32, Unk_C8FEE62D *, CStruct *);
void fn_80126FF4(Unk_80577C09 *, CStruct *);
void CStruct_new(s32);
s32 fn_80032088(s32);
void fn_800643E8(Unk_FFAD6788 *arg0, s32 arg1, CStruct *arg2, CStruct *arg3) {
    if (arg1 != 0) {
        if ((s32) arg0->unk0x104 == 0) {
            fn_80032088(0xF8);
            arg0->unk0x104 = fn_8012ED98();
        }
        if ((s32) arg0->unk0x10C == 0) {
            CStruct_new(8);
            arg0->unk0x10C = CStruct_ctor();
        }
        fn_80126FF4(arg0->unk0x10C, arg2);
        fn_8012F260(arg0->unk0x104, arg1, arg0->unk0x10C, arg3);
        return;
    }
    if ((s32) arg0->unk0x104 != 0) {
        fn_8012EE64(arg0->unk0x104, 3);
    }
    arg0->unk0x104 = arg1;
}
