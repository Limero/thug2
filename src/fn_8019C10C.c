// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019C10C-0x8019C1F4 (232B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802AABEC[];
extern char lbl_802AAC04[];
extern char lbl_802AAC20[];
extern char lbl_802AAD08[];
s32 fn_80125994(s32 arg0, s32 arg1);
s32 fn_80125A08(s32 arg0, s32 arg1);
s32 CStruct_new(s32 arg0);
s32 fn_8003E7CC(s32 arg0);
s32 CStruct_ctor(s32 arg0);
void fn_80126FF4(Unk_80577C09 * arg0, CStruct * arg1);
void fn_80129068(Unk_5AA7B5D7 * arg0, s32 arg1, s32 arg2);
void fn_80126E28(Unk_5AA7B5D7 * arg0, Unk_5AA7B5D7 * arg1);
s32 fn_80128F94(Unk_9D4ED6AF * arg0);
void *fn_8019C10C(CStruct *arg0) {
    register s32 temp_r29 __asm__("r29");

    arg0->unk0xC = (s32)lbl_802AAD08;
    temp_r29 = fn_80125994((s32)lbl_802AABEC, 1);
    fn_80126FF4(arg0->unk0x0 = CStruct_ctor(CStruct_new(8)), temp_r29);
    temp_r29 = fn_80125A08((s32)lbl_802AAC04, 1);
    fn_80129068(arg0->unk0x4 = fn_80128F94(fn_8003E7CC(0xC)), 6, 0xA);
    fn_80126E28(arg0->unk0x4, temp_r29);
    temp_r29 = fn_80125A08((s32)lbl_802AAC20, 1);
    fn_80129068(arg0->unk0x8 = fn_80128F94(fn_8003E7CC(0xC)), 6, 0xA);
    fn_80126E28(arg0->unk0x8, temp_r29);
    return arg0;
}
