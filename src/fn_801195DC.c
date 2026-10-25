// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801195DC-0x80119638 (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Object initialiser: copies a global pointer's +8 field into arg0+0x14
// (or NULL when the global is null), then memzeroes arg0's 0x14-byte head.
// memset declared `extern f32` so ngccc emits no crclr cr1eq before its bl
// (SN float-return convention, §4p item-27). Suggested name: InitLEState.
#include "types.h"
#include "structs.h"
extern char lbl_80302C34[];
extern f32 memset(void *, s32, s32);
void *fn_801195DC(Unk_C8FEE62D *arg0) {
    Unk_9994C3F5 *temp_r9;

    temp_r9 = *(void * *)&lbl_80302C34;
    if (temp_r9 != NULL) {
        arg0->unk0x14 =  temp_r9->unk0x8;
    } else {
        arg0->unk0x14 = temp_r9;
    }
    memset(arg0, 0, 0x14);
    return arg0;
}
