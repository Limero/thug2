// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012F064-0x8012F1A8 (324B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern s32 lbl_8030342C;
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
s32 fn_8012F2D8(Unk_C8FEE62D *, CStruct *);
void fn_8012F360(Unk_15EF4A35 *);
void CObject_RemoveRefLink(CStruct *, CStruct *);
void CObject_AddRefLink(CStruct *, Unk_9994C3F5 *);
void fn_80126FF4(Unk_80577C09 *, CStruct *);
void CStruct_delete(CStruct *, s32);
u8 *fn_8013465C(CScript *, s32);
s32 fn_8012DC0C(CStruct *, CStruct *, s32);
void fn_8012F4DC(Unk_FFAD6788 *);
void fn_8012F064(Unk_15EF4A35 *arg0, s32 arg1, s32 arg2, Unk_C8FEE62D *arg3, CStruct *arg4) {
    Unk_9994C3F5 *temp_r28;
    CStruct *temp_r29;
    CStruct *temp_r0;
    CStruct *temp_r3;

    temp_r28 = (Unk_9994C3F5 *)&arg0->unk0xBC;
    temp_r29 = fn_8012F2D8((Unk_C8FEE62D *)arg0, (CStruct *)arg3);
    fn_8012F360(arg0);
    arg0->unk0x14 = CStruct_ctor(CStruct_new(8));
    arg0->unk0xC8 = arg1;
    temp_r0 = (CStruct *)arg0->unk0xBC;
    if (temp_r0 != 0) {
        CObject_RemoveRefLink(temp_r0, temp_r28);
        arg0->unk0xBC = 0;
    }
    arg0->unk0xBC = (s32)arg4;
    if (arg4 != 0) {
        CObject_AddRefLink(arg4, temp_r28);
    }
    arg0->unk0x18 = CStruct_ctor(CStruct_new(8));
    if (arg2 != 0) {
        arg0->unk0x10 = arg2;
    } else {
        temp_r3 = fn_8013465C((CScript *)lbl_8030342C, arg1);
        arg0->unk0x10 = (s32)temp_r3;
        if (temp_r3 == 0) {
            if (temp_r29 != 0) {
                CStruct_delete(temp_r29, 3);
            }
            fn_8012F360(arg0);
            fn_8012F4DC(arg0);
            return;
        }
    }
    arg0->unk0x10 = fn_8012DC0C((CStruct *)arg0->unk0x18, (CStruct *)arg0->unk0x10, 0);
    if (temp_r29 != 0) {
        fn_80126FF4((Unk_80577C09 *)arg0->unk0x18, temp_r29);
        CStruct_delete(temp_r29, 3);
        return;
    }
    fn_80126FF4((Unk_80577C09 *)arg0->unk0x18, (CStruct *)arg3);
}
