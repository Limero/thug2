// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A1A84-0x800A1AE8 (100B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8009E274(Unk_31DE137E *, s32);
s32 fn_8009F678(Unk_6A70655D *);
s32 Mem_NewZero(s32);
s32 fn_800A1A84(Unk_C7387A53 *arg0) {
    s32 temp_r30;
    Unk_89391A04 *temp_r9;

    temp_r30 = fn_8009F678(Mem_NewZero(0x118));
    fn_8009E274(temp_r30, QB_OBJECT_TYPE_COMPOSITE);
    temp_r9 = arg0->unk0x2C;
    ((s32 (*)(void *, void *))temp_r9->unk0x14)((char *)arg0 + temp_r9->unk0x10, temp_r30);
    return temp_r30;
}
