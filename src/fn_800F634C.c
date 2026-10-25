// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F634C-0x800F6384 (56B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_800ADCD4(Unk_4A70D538 *);
void fn_800F634C(Unk_C7387A53 *arg0) {
    void **t;
    s32 (*fp)(void *);

    t = *((void ** *)&arg0->unk0x50);
    fp = (s32 (*)(void *))t[0x14 / 4];
    fn_800ADCD4(fp((char *)arg0 + (signed short)((s16 *)t)[0x10 / 2]));
}
