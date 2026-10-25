// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80203660-0x80203698 (56B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void AddInteger(CStruct *, s32, s32);
bool fn_80203660(Unk_C7387A53 *arg0, void *dummy, CScript *arg2) {
    AddInteger(arg2->unk0x18, QB_PAGERMESSAGECOUNT, arg0->unk0x20);
    return true;
}
