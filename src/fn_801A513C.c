// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A513C-0x801A5210 (212B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetStructure_2(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern s32 GetInteger(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern void fn_8003A944(s32 arg0, CStruct * arg1, s32 arg2);
extern void CStruct_dtor(CStruct * arg0);
extern void fn_80126FF4(Unk_80577C09 * arg0, CStruct * arg1);
void fn_801A513C(s32 arg0, s32 arg1, CStruct *arg2) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 p;

    GetStructure_2(arg2, arg1, (sp8 = 0, &sp8), 0);
    if (sp8 != 0) {
        if (GetStructure_2(sp8, QB_APPEARANCE, (spC = 0, &spC), 0) != 0) {
            fn_8003A944((char *)arg0 + 4, spC, 1);
        }
        GetStructure_2(sp8, QB_INFO, (spC = 0, &spC), 0);
        p = arg0 + 0x6C;
        CStruct_dtor(p);
        fn_80126FF4(p, spC);
        GetInteger(sp8, QB_DECKFLAGS, (sp10 = 1, &sp10), 0);
    }
}
