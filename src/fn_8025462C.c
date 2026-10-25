// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8025462C-0x80254720 (244B). Byte-identical.
#include "types.h"
#include "structs.h"

extern void fn_80257CC4(void *arg0, s32 arg1);
extern s32 fn_80257E48(CStruct * arg0, s32 arg1);
extern s32 fn_802541C8(Unk_DB0E2BAB * arg0, CStruct * arg1);
extern s32 fn_802542EC(Unk_31DE137E * arg0, CStruct * arg1);

s32 fn_8025462C(Unk_9994C3F5 *arg0, CStruct *arg1) {
    struct {
        s32 pos;
        s32 bit;
        s32 w8;
        s32 wC;
        s32 w10;
    } sp;
    CStruct *spp;
    s32 temp_r30;
    s32 temp_r29;
    s32 temp_r3;
    s32 temp_r9;
    s32 var_r11;
    s32 var_r3;

    if (arg1 == NULL) {
        return -0x85;
    }
    spp = &sp;
    temp_r30 = arg1->unk0x0;
    temp_r29 = arg1->unk0x4;
    fn_80257CC4(spp, 0x14);
    spp->unk0xC = temp_r30;
    spp->unk0x8 = temp_r30;
    spp->unk0x10 = temp_r29;
    temp_r3 = fn_80257E48(spp, 8);
    temp_r9 = spp->unk0x4;
    var_r11 = (temp_r9 + 0x30) / 8;
    spp->unk0xC += var_r11;
    *(s32 *)spp += var_r11;
    spp->unk0x4 = (temp_r9 + 0x30) & 7;
    switch (temp_r3) {
    case 1:
        var_r3 = -0x85;
        if (arg0->unk0x8 == 0) {
            var_r3 = fn_802541C8(arg0, spp);
        }
        return var_r3;
    case 5:
        var_r3 = -0x85;
        if (arg0->unk0x8 != 0) {
            var_r3 = fn_802542EC(arg0, spp);
        }
        return var_r3;
    }
    return -0x85;
}
