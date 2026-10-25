// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C0AE4-0x801C0B34 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_801C0AE4(CScript *arg0) {
    Unk_89391A04 *tbl;

    arg0->unk0x24 = 1;
    tbl = arg0->unk0x18;
    ((s32 (*)(void *))tbl->unk0x14)((void *)((char *)arg0 + tbl->unk0x10));
    arg0->unk0x24 = 0;
}
