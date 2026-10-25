// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80168780-0x801687C4 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void *lbl_802FFF6C;
s32 fn_80015A58(void *, s32, s32);
s32 BannerExists(Unk_C8FEE62D *);

s32 ScriptCardIsFormatted(CStruct *pParams, CScript *pScript) {
    s32 temp_r3;

    temp_r3 = fn_80015A58(lbl_802FFF6C, 0, 0);
    if (temp_r3 != 0) {
        return BannerExists(temp_r3);
    }
    return 0;
}
