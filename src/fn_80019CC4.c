// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80019CC4-0x80019D08 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 GetInteger(CStruct *, s32, s32 *, s32);
extern s32 lbl_8037B7A0;
// arg0 is the QB data block, forwarded straight through to GetInteger
// (retail does NO copy: r3 flows r3->r3 into the call, so arg1 stays 0).
bool ScriptNgc_ReduceColors(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    if (GetInteger(pParams, 0, &sp8, 0) != 0) {
        lbl_8037B7A0 = sp8;
    }
    return true;
}