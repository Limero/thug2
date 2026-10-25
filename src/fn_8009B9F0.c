// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009B9F0-0x8009BA60 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80297738[];
void fn_80070A7C(void);
void *fn_8009B9F0(Unk_C8FEE62D *arg0) {
    fn_80070A7C();
    arg0->unk0x20 = (s32)lbl_80297738;
    arg0->unk0x28 = 0;
    arg0->unk0x2C = 0;
    arg0->unk0x30 = 0;
    arg0->unk0x34 = 0;
    arg0->unk0x40 = 0;
    arg0->unk0x44 = 0;
    arg0->unk0x48 = QB_UNKNOWN_0x80808080;
    arg0->unk0x4 = arg0->unk0x4 | 1;
    return arg0;
}
