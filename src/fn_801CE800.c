// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CE800-0x801CE8A8 (168B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern s32 Tmr_GetTime(void);
extern s32 lbl_80303150;
bool fn_801CE800(Unk_7258DEBD *arg0, CStruct *arg1) {
    s32 sp8;
    s32 var_r29;
    Unk_4C649A8C *p;

    var_r29 = 0;
    sp8 = 0;
    GetChecksum_2(arg1, 0, &sp8, 1);
    if (sp8 == QB_SLIDE) {
        p = *((char * *)&arg0->unk0x15BC) + 0x78;
        var_r29 = 1;
        if (p->unk0x4 != 1) {
            p->unk0x4 = var_r29;
            p->unk0x8 = lbl_80303150 + Tmr_GetTime();
        }
    } else {
        p = *((char * *)&arg0->unk0x15BC) + 0x78;
        if (p->unk0x4 != 0) {
            p->unk0x4 = var_r29;
            p->unk0x8 = lbl_80303150 + Tmr_GetTime();
        }
    }
    *(s32 *)(arg0->unk0x15A8 + 0x24) = var_r29;
    __asm__ __volatile__("");
    return true;
}
