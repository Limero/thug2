// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80192230-0x80192438 (520B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802A98D4[];
extern char lbl_802A98E0[];
extern s32 lbl_80305EAC;
extern void* lbl_80305F9C;
extern s32 AddChecksum(CStruct * arg0, s32 arg1, s32 arg2);
extern s32 fn_801907E0(s32 arg0, s32 arg1);
extern s32 fn_8012720C(CStruct * arg0, s32 arg1);
extern s32 fn_8009CF2C(CStruct * arg0);
extern s32 fn_8019B728(Unk_31DE137E * arg0, s32 arg1);
extern s32 fn_801276E8(CStruct * arg0, void * arg1, s32 arg2);
extern s32 CStruct_new(s32 arg0);
extern s32 CStruct_ctor(s32 arg0);
extern void fn_801903B8(Unk_C7387A53 * arg0, CStruct * arg1);
extern s32 fn_80126FF4(Unk_80577C09 * arg0, CStruct * arg1);
extern s32 CStruct_delete(CStruct * arg0, s32 arg1);
extern s32 fn_801905EC(Unk_C7387A53 * arg0);
extern s32 fn_80127138(CStruct * arg0, void * arg1);
extern s32 fn_80127C90(CStruct * arg0, void * arg1, CStruct * arg2);
bool fn_80192230(Unk_C8FEE62D *arg0) {
    s32 var_r29;
    s32 temp_r29;
    s32 temp_r31;
    Unk_4AA2E777 *temp_r9;

    AddChecksum(arg0->unk0x20, 0, QB_JUST_WON_GOAL);
    fn_801907E0(arg0, QB_DEACTIVATE);
    fn_8012720C(arg0->unk0x20, QB_JUST_WON_GOAL);
    temp_r9 = *((void * *)&arg0->unk0x14);
    ((s32 (*)(void *))temp_r9->unk0x7C)((char *)arg0 + temp_r9->unk0x78);
    if (fn_8009CF2C(lbl_80305F9C) == 0) {
        temp_r31 = ((Unk_C2F9BED0 *)lbl_80305EAC)->unk0x370;
        var_r29 = 0x3E7;
        if (fn_8019B728(temp_r31, 1) != 0) {
            var_r29 = 1;
        } else if (fn_8019B728(temp_r31, 2) != 0) {
            var_r29 = 2;
        } else if (fn_8019B728(temp_r31, 3) != 0) {
            var_r29 = 3;
        }
        if (var_r29 < arg0->unk0x50) {
            fn_801276E8(arg0->unk0x20, (s32)lbl_802A98D4, var_r29);
            arg0->unk0x50 = var_r29;
        }
    }
    temp_r29 = CStruct_ctor(CStruct_new(8));
    temp_r9 = *((void * *)&arg0->unk0x14);
    if (temp_r9->unk0xAC((char *)arg0 + temp_r9->unk0xA8) == 0) {
        temp_r31 = CStruct_ctor(CStruct_new(8));
        __asm__("" : "+r"(temp_r31));
        fn_801903B8((s32)arg0, temp_r31);
        fn_80126FF4(temp_r29, temp_r31);
        if (temp_r31 != 0) {
            CStruct_delete(temp_r31, 3);
        }
        fn_801905EC((s32)arg0);
    } else {
        fn_80127138(arg0->unk0x20, (s32)lbl_802A98E0);
    }
    fn_80127C90(arg0->unk0x20, (s32)lbl_802A98E0, temp_r29);
    fn_801907E0(arg0, QB_SUCCESS);
    if (temp_r29 != 0) {
        CStruct_delete(temp_r29, 3);
    }
    temp_r9 = *((void * *)&arg0->unk0x14);
    if (temp_r9->unk0xAC((char *)arg0 + temp_r9->unk0xA8) == 0) {
        temp_r9 = *((void * *)&arg0->unk0x14);
        temp_r9->unk0xDC((char *)arg0 + temp_r9->unk0xD8);
    }
    return true;
}
