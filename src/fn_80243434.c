// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80243434-0x802434B0 (124B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void fn_80240B0C(Unk_F96D0DC8 *, s32, s32, s32, s32, s32, s32);
void *fn_80243434(Unk_12004030 *arg0) {
    u32 var_r29;
    void *p;

    var_r29 = 1;
    p = (char *)arg0 + 0x9C;
    do {
        fn_80240B0C(p, 0, 0, 0, 0, 0, 0);
        p = (char *)p + 6;
    } while (var_r29-- != 0);
    arg0->unk0xC = 0;
    arg0->unk0x10 = 0;
    arg0->unk0x14 = 0;
    arg0->unk0x18 = 0;
    arg0->unk0xEC = 0;
    return arg0;
}
