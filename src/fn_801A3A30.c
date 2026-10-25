// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A3A30-0x801A3A98 (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern f32 lbl_802AB73C;
void fn_801812B8(s32, s32, f32);
void fn_801812DC(s32, s32, f32);
void fn_801A3A30(Unk_C7387A53 *arg0) {
    if ((s32) *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0xC) + 0x1C) != 0) {
        fn_801812B8(*(s32 *)(*(s32 *)((char *)((char *)arg0) + 0xC) + 0x1C), 0, lbl_802AB73C);
        fn_801812DC(*(s32 *)(*(s32 *)((char *)((char *)arg0) + 0xC) + 0x1C), 0, lbl_802AB73C);
    }
    arg0->unk0x48 = 0;
    arg0->unk0x4C = 0;
}