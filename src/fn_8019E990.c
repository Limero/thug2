// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019E990-0x8019EA50 (192B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802AB040[];
extern s32 lbl_80301B48;
extern void fn_80009C00(CStruct * list);
extern s32 fn_800F2A48(s32 mgr, s32 val, s32 flag);
extern void fn_800F28E4(Unk_C7387A53 * a, CStruct * b);
extern void fn_8009F7A4(Unk_6A70655D * obj, s32 arg1);
void fn_8019E990(Unk_361D6392 *arg0, s32 arg1) {
    s32 temp_r31;
    s32 temp_r3;
    CScript *temp_r11;
    Unk_4E705049 *temp_r9;

    arg0->unk0x8 = (s32)lbl_802AB040;
    fn_80009C00(arg0->unk0x118);
    if ((s32) arg0->unk0x130 != 0) {
        temp_r31 = lbl_80301B48;
        temp_r3 = fn_800F2A48(temp_r31, arg0->unk0x130, 0);
        if (temp_r3 != 0) {
            fn_800F28E4(temp_r31, temp_r3);
            fn_800F2A48(temp_r31, arg0->unk0x130, 0);
        }
        arg0->unk0x130 = 0;
    }
    temp_r11 = arg0->unk0x118;
    if (temp_r11 != NULL) {
        temp_r9 = temp_r11->unk0x18;
        ((s32 (*)(void *, s32))temp_r9->unk0x1C)((char *)temp_r11 + temp_r9->unk0x18, 3);
    }
    fn_8009F7A4(arg0, arg1);
}
