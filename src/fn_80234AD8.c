// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80234AD8-0x80234B80 (168B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_80128170(CStruct *, void *, void *, s32);
void fn_80128294(CStruct *, void *, void *, s32);
void GetStructure_2(CStruct *, s32, s32 *, s32);
s32 fn_8023C598(s32);
void fn_8023D688(Unk_5492E6FA *, u8 *, s32);
void fn_8023D6FC(Unk_FFAD6788 *, CStruct *);
extern char lbl_802B0928[];
extern char lbl_802B0A24[];
// ScriptSetEditedParkGapInfo @ 0x80234AD8
bool ScriptSetEditedParkGapInfo(CStruct *pParams, CScript *pScript) {
    s32 sp10;
    s32 spC;
    s32 sp8;

    sp8 = 0;
    fn_80128170(pParams, (s32)lbl_802B0928, &sp8, 0);
    spC = -1;
    fn_80128294(pParams, (s32)lbl_802B0A24, &spC, 0);
    fn_8023D688(fn_8023C598(1), sp8, spC);
    sp10 = 0;
    GetStructure_2(pParams, QB_CANCEL_FLAGS, &sp10, 0);
    fn_8023D6FC(fn_8023C598(1), sp10);
    return true;
}
