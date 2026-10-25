// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80114028-0x8011405C (52B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8011C924(s32);
void GetChecksum_2(CStruct *, s32, s32 *, s32);
// ScriptPreLoadStreamDone @ 0x80114028
void ScriptPreLoadStreamDone(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    GetChecksum_2(pParams, 0, &sp8, 1);
    fn_8011C924(sp8);
}
