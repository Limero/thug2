// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F4B50-0x801F4BB0 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_801F4B50(Unk_5FCDF30E *arg0, s32 arg1) {
    s32 temp_r9;
    s32 temp_r9_2;

    temp_r9 = arg0->unk0x114;
    arg0->unk0x2C4 = arg1;
    if (temp_r9 == QB_SKATETRIS) {
        goto block_5;
    }
    if ((u32) temp_r9 <= (u32) QB_SKATETRIS) {
        if (temp_r9 == QB_COMBOSKATETRIS) {
            goto block_5;
        }
        return;
    }
    if (temp_r9 == -QB_UNKNOWN_0x1584599A) {
        goto block_5;
    }
    return;
block_5:
    temp_r9_2 = arg0->unk0x2C4 - 5;
    if (arg0->unk0x2E4 > temp_r9_2) {
        arg0->unk0x2E4 = temp_r9_2;
    }
}
