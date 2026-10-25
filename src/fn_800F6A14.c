// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F6A14-0x800F6A8C (120B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_800F6A14(Unk_C7387A53 *arg0, s32 arg1) {
    void **t;
    void **t2;
    void (*fp)(void *);
    s32 (*fp2)(void *, s32, s32, s32, s32, s32);

    t = *((void ** *)&arg0->unk0x50);
    fp = (void (*)(void *))t[0x3C / 4];
    fp((char *)arg0 + (signed short)((s16 *)t)[0x38 / 2]);
    t2 = *((void ** *)&arg0->unk0x50);
    fp2 = (s32 (*)(void *, s32, s32, s32, s32, s32))t2[0x2C / 4];
    return fp2((char *)arg0 + (signed short)((s16 *)t2)[0x28 / 2], arg1, 0, 0, 0, 0) == 0;
}
