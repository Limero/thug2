// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80010910-0x8001094C (60B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_800107A0(CScript *);
extern char lbl_80290610[];
void *fn_80010910(CScript *arg0, s32 arg1) {
    arg0->unk0x18 = (s32)lbl_80290610;
    fn_800107A0(arg0);
    return arg0;
}
