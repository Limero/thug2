// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800E28F8-0x800E2958 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-expensive-optimizations
#include "types.h"
#include "structs.h"
s32 fn_80069890(s32);
s32 fn_800699A8(s32, s32, s32);
s32 fn_80128D40(CStruct *, void *, CStruct *, void *);
bool fn_800E28F8(Unk_C7387A53 *arg0, CStruct *arg1) {
    s32 sp8[4];
    fn_80128D40(arg1, 0, &sp8[0], 1);
    if ((s32) arg0->unk0x20 != 0) {
        fn_800699A8((s32) arg0->unk0x20, 0, &sp8[0]);
        fn_80069890(arg0->unk0x20);
    }
    return true;
}
