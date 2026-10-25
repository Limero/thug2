// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DEBB0-0x800DEC28 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_800A398C(s32, s32);
s32 GetChecksum_2(s32, s32, s32, s32);
extern char lbl_80301A38[];
s32 fn_80128978(void *, void *);
void fn_800DEBB0(CScript *arg0, CStruct *arg1) {
    s32 sp8;

    if (fn_80128978(arg1, QB_PROXIMTRIGGERTARGET) != 0) {
        GetChecksum_2(arg1, QB_PROXIMTRIGGERTARGET, &sp8, 0);
        arg0->unk0x1C = fn_800A398C(*(s32 *)lbl_80301A38, sp8);
    }
    arg0->unk0x20 = 0;
}
