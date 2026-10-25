// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80221CFC-0x80221D58 (92B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void *lbl_80303148;
extern void *lbl_80305F9C;
extern s32 fn_8000A578(s32, s32);
bool ScriptEnteredNetworkGame(CStruct *pParams, CScript *pScript) {
    Unk_3BD30EA5 *mgr = lbl_80305F9C;
    void *entry = (void *)((char *)lbl_80303148 + 8);

    fn_8000A578(entry, mgr->unk0xE0);
    fn_8000A578(entry, mgr->unk0xD4);
    mgr->unk0x4C = 1;
    return true;
}
