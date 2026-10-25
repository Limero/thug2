// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800FE3B4-0x800FE42C (120B). Byte-identical.
#include "types.h"
#include "structs.h"
bool fn_800FE3B4(Unk_9994C3F5 *arg0, Unk_DB0E2BAB *arg1) {
    register f32 a __asm__("fr13");
    char *m = *((char * *)&arg0->unk0x8);
    Unk_B36D6286 *hi;
    a = *((f32 *)&arg1->unk0x0);
    hi = m + 0x10;
    if (a > hi->unk0x10) goto fail;
    if ((a = ((Unk_B36D6286 *)m)->unk0x10) > *((f32 *)&arg1->unk0x10)) goto fail;
    if ((a = *((f32 *)&arg1->unk0x8)) > hi->unk0x18) goto fail;
    if ((a = ((Unk_B36D6286 *)m)->unk0x18) > *((f32 *)&arg1->unk0x18)) goto fail;
    a = hi->unk0x14;
    if (*((f32 *)&arg1->unk0x4) > a) goto fail;
    if (!((a = ((Unk_B36D6286 *)m)->unk0x14) > *((f32 *)&arg1->unk0x14))) {
        goto ok;
    }
fail:
    return false;
ok:
    return true;
}