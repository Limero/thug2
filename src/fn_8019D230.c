// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019D230-0x8019D2E0 (176B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void* lbl_802FFE98;
extern s32 lbl_80303148;
extern s32 lbl_8030191C;
extern void fn_8000F2F8(Unk_9F352E7C * arg0, s32 arg1);
extern void fn_8000A578(s32 arg0, s32 arg1);
extern void fn_8000F320(Unk_F12C5E01 * arg0);
void fn_8019D230(CScript *arg0) {
    s32 *var_r29;
    CScript *temp_r30;
    s32 temp_r31;
    s32 temp_r27;
    s32 temp_r11;
    s32 var_r28;

    var_r29 = (s32 *)((char *)arg0 + 0x28);
    var_r28 = 4;
    fn_8000F2F8(lbl_802FFE98, ((Unk_9960D53C *)lbl_802FFE98)->unk0x124);
    fn_8000A578(lbl_80303148 + 8, arg0->unk0x18);
    temp_r31 = lbl_8030191C;
    temp_r27 = temp_r31 + 8;
    do {
        temp_r30 = *var_r29++;
        fn_8000A578(temp_r30->unk0x24 * 0x94 + temp_r31 + 0xC, temp_r30);
        temp_r11 = temp_r30->unk0x24 * 0x94;
        temp_r30->unk0x1C = temp_r11 + temp_r31 + 0x58;
        temp_r30->unk0x20 = *(s32 *)(temp_r27 + temp_r11);
    } while (--var_r28 != 0);
    fn_8000F320(lbl_802FFE98);
}
