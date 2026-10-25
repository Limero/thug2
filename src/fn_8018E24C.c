// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018E24C-0x8018E28C (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 GetChecksum_4(s32, s32, s32, s32);
extern char lbl_802A9640[];
s32 fn_8018E24C(Unk_C7387A53 *arg0) {
    s32 sp8;

    sp8 = 0;
    GetChecksum_4(arg0->unk0x20, (s32)lbl_802A9640, (s32)&sp8, 1);
    return sp8;
}
