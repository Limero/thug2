// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011348C-0x801134FC (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern s32 lbl_80302C34;

s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_8011A6A8(void *, s32);
s32 Script_GetInteger(s32, s32);

s32 ScriptStopSound(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 stopped;

    if (GetChecksum_2(pParams, 0, &sp8, 0) != 0) {
        stopped = fn_8011A6A8(*(void **)&lbl_80302C34, sp8);
        if (stopped == 0) {
            Script_GetInteger(0xD7BB618D, 0);
        }
        return stopped;
    }
    return 0;
}
