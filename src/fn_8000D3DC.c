// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000D3DC-0x8000D478 (156B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_8000EB24(void *);
#include "structs.h"
s32 fn_8000CE8C(s32, s32);
s32 fn_8000EB38(void *, s32);
s32 fn_8000D3DC(Unk_C8FEE62D *arg0, s32 arg1) {
    s32 x;
    s32 v;

    if ((s32) arg0->unk0x10 == arg1) {
        return 0;
    }
    if ((s32) arg0->unk0x8 == arg1) {
        return arg0->unk0xC;
    }
    fn_8000EB24(arg0->unk0x14);
    while ((x = fn_8000EB38(arg0->unk0x14, 0)) != 0) {
        v = fn_8000CE8C(x, arg1);
        if (v != 0) {
            arg0->unk0x4 = x;
            arg0->unk0x8 = arg1;
            arg0->unk0xC = v;
            return v;
        }
    }
    arg0->unk0x10 = arg1;
    return 0;
}
