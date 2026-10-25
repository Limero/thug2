// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801371D4-0x8013725C (136B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void fn_8013E27C(void *arg0);

void fn_801371D4(Unk_F386DC9F *arg0, Unk_82779A3F *arg1) {
    register void *temp_r9 __asm__("r9");
    CStruct *temp_r10;

    temp_r9 = (char *)arg1 + 0x1808;
    *(s32 *)(((Unk_F5317C5D *)temp_r9)->unk0x10 + 0xC) = ((Unk_F5317C5D *)temp_r9)->unk0xC;
    temp_r10 = (void *)((Unk_F5317C5D *)temp_r9)->unk0xC;
    temp_r10->unk0x10 = ((Unk_F5317C5D *)temp_r9)->unk0x10;
    ((Unk_F5317C5D *)temp_r9)->unk0xC = temp_r9;
    ((Unk_F5317C5D *)temp_r9)->unk0x10 = temp_r9;
    fn_8013E27C(arg1);
    if (arg1 != NULL) {
        temp_r9 = arg1->unk0x2300;
        ((void (*)(void *, s32))((Unk_F5317C5D *)temp_r9)->unk0xC)(
            (char *)arg1 + ((Unk_F5317C5D *)temp_r9)->unk0x8, 3);
    }
    arg0->unk0x22E8 = arg0->unk0x22E8 - 1;
}
