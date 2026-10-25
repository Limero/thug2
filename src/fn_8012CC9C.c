// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012CC9C-0x8012CCCC (48B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

void fn_8012CC9C(Unk_667BA59C *arg0) {
    u16 i;

    for (i = 0; i < (u16)*((u16 *)&arg0->unk0xC); i++) {
        u8 *p = (u8 *)arg0 + 0x16;

        p[i] = (u8)i;
    }
}
