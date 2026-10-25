// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800AC93C-0x800AC9B4 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern s32 lbl_80301B48;
void fn_800F2384(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void fn_800AC93C(Unk_6849630D *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 *base;
    fn_800F2384(lbl_80301B48, arg1, 5, 0, arg2, arg3, 0, 1, 0, 0);
    base = (s32 *)((char *)arg0 + 0x2c5c);
    base[arg0->unk0x345C] = arg1;
    arg0->unk0x345C = arg0->unk0x345C + 1;
}
