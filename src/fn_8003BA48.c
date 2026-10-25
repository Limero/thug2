// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003BA48-0x8003BAAC (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern Unk_DB0E2BAB *lbl_803003EC;
extern CStruct *lbl_803003F0;
s32 fn_800379CC(Unk_DB0E2BAB *, CStruct *);
s32 fn_80128E04(CStruct *, void *, void *, s32);
s32 fn_8003BA48(void) {
    CStruct *node = lbl_803003F0;
    CStruct *body = 0;
    s32 found;

    found = fn_80128E04((CStruct *)((char *)node + 0x58), QB_BODY_SHAPE, &body, 0);
    if (found != 0) {
        return fn_800379CC(lbl_803003EC, body);
    }
    return 0;
}
