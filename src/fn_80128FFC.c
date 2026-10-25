// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80128FFC-0x80129068 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void Mem_Free_3(s32);
void fn_80128FFC(Unk_F8A5095F *arg0) {
    if (arg0->unk0x4 == 1) {
        if (arg0->unk0x8 != 0) {
            arg0->unk0x8 = 0;
        }
    } else {
        if (arg0->unk0x8 != 0) {
            Mem_Free_3(arg0->unk0x8);
            arg0->unk0x8 = 0;
        }
    }
    ((Unk_ECD1B899 *)arg0)->unk0x2 = 0;
    arg0->unk0x4 = 0;
}
