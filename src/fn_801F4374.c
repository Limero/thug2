// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F4374-0x801F43E4 (112B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_801F4374(Unk_5FCDF30E *arg0, CStruct *arg1) {
    s32 sp8;

    sp8 = 0;
    GetChecksum_2(arg1, 0, &sp8, 0);
    if (((s32) arg0->unk0x114 == QB_COMBOSKATETRIS) && (sp8 == -QB_UNKNOWN_0x20B84EBC)) {
        arg0->unk0x2F0 = 0;
    }
}
