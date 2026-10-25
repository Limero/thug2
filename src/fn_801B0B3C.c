// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B0B3C-0x801B0C78 (316B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 GetStructure_2(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern void fn_801B07D4(CStruct * arg0, CStruct * arg1);
extern void fn_801B04AC(CStruct * arg0, CStruct * arg1);

void fn_801B0B3C(Unk_C8FEE62D *arg0, CStruct *arg1) {
    s32 sp8;

    sp8 = 0;
    GetStructure_2(arg1, QB_HIGHSCORES, &sp8, 0);
    fn_801B07D4(arg0->unk0x4, sp8);
    GetStructure_2(arg1, QB_BESTCOMBOS, &sp8, 0);
    fn_801B07D4(arg0->unk0x8, sp8);
    if (GetStructure_2(arg1, QB_ARCADESCORES, &sp8, 0) != 0) {
        fn_801B07D4(arg0->unk0xC, sp8);
    }
    GetStructure_2(arg1, QB_LONGESTCOMBO, &sp8, 0);
    fn_801B04AC(arg0->unk0x1C, sp8);
    GetStructure_2(arg1, QB_LONGESTGRIND, &sp8, 0);
    fn_801B04AC(arg0->unk0x10, sp8);
    GetStructure_2(arg1, QB_LONGESTLIPTRICK, &sp8, 0);
    fn_801B04AC(arg0->unk0x18, sp8);
    GetStructure_2(arg1, QB_LONGESTMANUAL, &sp8, 0);
    fn_801B04AC(arg0->unk0x14, sp8);
}
