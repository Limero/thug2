// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800133B4-0x80013410 (92B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_800133B4(Unk_DB0E2BAB *arg0) {
    Unk_89391A04 *temp_r9;

    arg0->unk0x14 = 7;
    if (arg0->unk0x34 != 0) {
        arg0->unk0x0 = -1;
        return 1;
    }
    temp_r9 = *((void * *)&arg0->unk0x3C);
    return ((s32 (*)(void *))*((void * *)&temp_r9->unk0x9C))((char *)arg0 + temp_r9->unk0x98);
}
