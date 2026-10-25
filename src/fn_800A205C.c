// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A205C-0x800A20B8 (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern s32 lbl_803C9E80[];
void fn_800A205C(Unk_C7387A53 *arg0, Unk_C8FEE62D *arg1) {
    s32 key = arg1->unk0x4;
    u32 i = 0;
    while (i < (u32)arg0->unk0x50) {
        if (*(s32 *)((char *)arg0 + 0x54 + (i * 8)) == key) {
            arg1->unk0x14 = lbl_803C9E80[i];
            lbl_803C9E80[i] = (s32)arg1;
            return;
        }
        i++;
    }
}