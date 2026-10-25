// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80205574-0x80205664 (240B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_80205DE8(CScript *, s32, s32, s32);
extern f32 lbl_802AF124;
s32 fn_80205574(CScript *arg0, s32 arg1) {
    u32 swv1;
    switch (swv1 = arg1) {
    case QB_TAGNOW:
        arg0->unk0x1C = 0;
        break;
    case QB_VERTSTICKERSLAP:
        arg0->unk0x1C = 0;
        fn_80205DE8(arg0, 1, 0, 0);
        break;
    case QB_TAGCLEARFLAGS:
        arg0->unk0x1C = 0;
        arg0->unk0x20 = 0;
        *((f32 *)&arg0->unk0x28) = lbl_802AF124;
        arg0->unk0x24 = 0;
        break;
    case QB_BLOCKTAGGINGON:
        arg0->unk0x24 = 1;
        break;
    case QB_BLOCKTAGGINGOFF:
        arg0->unk0x24 = 0;
        break;
    default:
        return 2;
    }
    return 1;
}
