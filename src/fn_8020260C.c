// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020260C-0x80202644 (56B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void AddInteger(CStruct *, s32, s32);
bool fn_8020260C(Unk_59E38960 *arg0, void *dummy, CScript *arg2) {
    AddInteger(arg2->unk0x18, QB_LAST_AIR_COMBO_SCORE, arg0->unk0xA98);
    return true;
}
