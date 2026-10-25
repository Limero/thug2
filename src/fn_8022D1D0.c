// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022D1D0-0x8022D284 (180B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_800F63B8(Unk_C7387A53 *);
void fn_8022CAE4(void *);
void fn_80240B0C(Unk_F96D0DC8 *, s32, s32, s32, s32, s32, s32);
void *fn_8022D1D0(Unk_DB0E2BAB *arg0) {
    s32 temp_r3;
    s32 var_ctr;
    u32 var_r29;
    s32 var_r30;

    var_r29 = 0x11;
    var_r30 = (s32)((char *)arg0 + 0xA0);
    fn_8022CAE4((s32)((char *)arg0 + 0x24));
    fn_8022CAE4((s32)((char *)arg0 + 0x5C));
    do {
        temp_r3 = (s32)((char *)var_r30 + 0x14);
        var_r30 += 0x28;
        fn_80240B0C(temp_r3, 0, 0, 0, 0, 0, 0);
    } while (var_r29-- != 0);
    var_ctr = 0x10;
    do {
        var_ctr -= 1;
    } while (var_ctr != 0);
    fn_800F63B8((s32)((char *)arg0 + 0x494));
    arg0->unk0x0 = 0;
    arg0->unk0x4 = 0;
    arg0->unk0x8 = 0;
    arg0->unk0xC = 0;
    arg0->unk0x14 = 0;
    arg0->unk0x10 = 0;
    arg0->unk0x1C = 0x20;
    arg0->unk0x20 = 2;
    return arg0;
}
