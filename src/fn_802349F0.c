// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802349F0-0x80234A60 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_80128294(CStruct *, void *, void *, void *);
s32 fn_80128A90(CStruct *, void *);
s32 fn_80232F24(Unk_C7387A53 *, void *, void *, void *);
extern char lbl_80305FF8[];
extern char lbl_802B0A00[];
extern char lbl_802B0A08[];
bool ScriptLoadParkFromDisk(CStruct *pParams, CScript *pScript) {
    s32 temp_r5;
    s32 sp8;

    sp8 = 0;
    fn_80128294(pParams, lbl_802B0A00, &sp8, 1);
    temp_r5 = fn_80128A90(pParams, lbl_802B0A08);
    fn_80232F24(*(s32 *)&lbl_80305FF8, 0, sp8, temp_r5);
    return true;
}