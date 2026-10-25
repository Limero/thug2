// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A37A0-0x801A383C (156B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_802AB648[];
void fn_8002448C(void *, s32);
void fn_80009C00(CStruct *);
s32 fn_80009C84(Unk_9994C3F5 *);

void fn_801A37A0(Unk_6A70655D *arg0, s32 arg1) {
    CScript *temp_r11;
    Unk_4E705049 *temp_r9;

    arg0->unk0x8 = (s32)lbl_802AB648;
    if (arg0->unk0xE4 != 0) {
        Mem_Free(arg0->unk0xE4);
    }
    if (arg0->unk0x108 != NULL) {
        if (fn_80009C84(arg0->unk0x108) != 0) {
            fn_80009C00(arg0->unk0x108);
        }
        temp_r11 = arg0->unk0x108;
        if (temp_r11 != NULL) {
            temp_r9 = temp_r11->unk0x18;
            ((s32 (*)(void *, s32))temp_r9->unk0x1C)((char *)temp_r11 + temp_r9->unk0x18, 3);
        }
    }
    fn_8002448C(arg0, arg1);
}
