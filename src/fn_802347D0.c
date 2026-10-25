// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802347D0-0x80234864 (148B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void AddInteger(s32, s32, s32);
void *fn_80238964(void);
bool ScriptGetCurrentParkBounds(void *arg0, void *arg1) {
    s32 sp8;
    void *temp_r3;

    temp_r3 = fn_80238964();
    sp8 = ((Unk_BE7EBD4F *)temp_r3)->unk0x3524;
    *(u16 *)((char *)&sp8 + 0x4) = (u16) ((Unk_BE7EBD4F *)temp_r3)->unk0x3528;
    AddInteger(*(s32 *)((char *)arg1 + (s32)0x18), QB_X, ((u8 *) &sp8)[0]);
    AddInteger(*(s32 *)((char *)arg1 + (s32)0x18), QB_Z, ((u8 *) &sp8)[2]);
    AddInteger(*(s32 *)((char *)arg1 + (s32)0x18), QB_W, ((u8 *) &sp8)[3]);
    AddInteger(*(s32 *)((char *)arg1 + (s32)0x18), QB_L, ((u8 *) &sp8)[5]);
    return true;
}
