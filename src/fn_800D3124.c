// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D3124-0x800D319C (120B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_800DB398(Unk_C7387A53 * arg0);
extern s32 fn_800DB3A4(Unk_C7387A53 * arg0, f32 * arg1);
extern void fn_800D3974(Unk_A9157FE7 * arg0);
extern void fn_800D498C(Unk_C8FEE62D * arg0);

void fn_800D3124(Unk_C7387A53 *arg0) {
    if ((fn_800DB398(arg0->unk0x58) == 0) && !(*(s32 *)(arg0->unk0xC + (s32)0xC) & 1) && (fn_800DB3A4(arg0->unk0x58, 0) != 0) && (arg0->unk0x50 != 0)) {
        fn_800D3974(arg0);
        fn_800D498C(arg0);
    }
}
