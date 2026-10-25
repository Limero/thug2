// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80202548-0x802025AC (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 GetInteger(CStruct *, s32, s32 *, s32);
extern void AddInteger(CStruct *, s32, s32);
bool fn_80202548(Unk_59E38960 *arg0, CStruct *arg1, CScript *arg2) {
    s32 index;
    char *base;
    s32 off;

    GetInteger(arg1, 0, &index, 1);
    base = (char *)arg0 + 0x30;
    off = index * 0x24;
    AddInteger(arg2->unk0x18, QB_STATUS, *(s32 *)(base + off));
    return true;
}
