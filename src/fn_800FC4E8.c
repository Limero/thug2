// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800FC4E8-0x800FC56C (132B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8029C1F8[];
extern char lbl_8029C7B0[];
extern void fn_800FB0F0(Unk_5B449B03 *);
extern void fn_800071D4(void *);
extern void *Mem_NewZero(s32);
void *fn_800FC4E8(Unk_C8FEE62D *arg0) {
    Unk_C8FEE62D *temp_r9;

    fn_800FB0F0(arg0);
    arg0->unk0xC = (s32)lbl_8029C7B0;
    fn_800071D4((char *)arg0 + 0x18);
    temp_r9 = Mem_NewZero(0x18);
    temp_r9->unk0x14 = (s32)lbl_8029C1F8;
    temp_r9->unk0x4 = -1;
    temp_r9->unk0x8 = 0;
    temp_r9->unk0xC = temp_r9;
    temp_r9->unk0x10 = temp_r9;
    arg0->unk0x10 = temp_r9;
    arg0->unk0x38 = 1;
    arg0->unk0x40 = 0;
    return arg0;
}
