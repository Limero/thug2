// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A6C4C-0x801A6CCC (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_801A6CD4(Unk_93C2DF4D *, s32);
void fn_801A6C4C(Unk_93C2DF4D *arg0, s32 arg1) {
    s32 var_r30;
    char *pa;
    char *pb;
    char *pc;
    char *pd;
    s32 idx;

    var_r30 = arg1;
    if (var_r30 == -1) {
        var_r30 = arg0->unk0x630;
    } else {
        arg0->unk0x630 = var_r30;
    }
    fn_801A6CD4(arg0, arg0->unk0x630);
    pa = (char *)arg0 + 4;
    pb = (char *)arg0 + 8;
    pc = (char *)arg0 + 0x2A4;
    pd = (char *)arg0 + 0x2A8;
    idx = var_r30 << 5;
    arg0->unk0x544 = *(s32 *)(pa + idx);
    arg0->unk0x548 = *(s32 *)(pb + idx);
    arg0->unk0x564 = *(s32 *)(pc + idx);
    arg0->unk0x568 = *(s32 *)(pd + idx);
}
