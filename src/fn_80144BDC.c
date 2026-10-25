// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80144BDC-0x80144C34 (88B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 Script_RunScript(s32, s32, void *, s32, s32);
void fn_80144BDC(Unk_31DE137E *arg0) {
    if ((s32) arg0->unk0x188 != 0) {
        Script_RunScript(QB_SKATERPARTICLES_SPARKSOFF, 0, arg0, 0, 0);
        arg0->unk0x188 = 0;
    }
}
