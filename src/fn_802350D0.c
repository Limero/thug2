// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802350D0-0x80235114 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern f32 lbl_80306044;
extern f32 lbl_802B0A50;
void fn_8023FC44(void *);

s32 ScriptIsParkFull(CStruct *pParams, CScript *pScript)
{
    char buf[112];

    fn_8023FC44(buf);
    return lbl_80306044 >= lbl_802B0A50;
}
