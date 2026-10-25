// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C11D0-0x801C1250 (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802AC7AC;
extern char lbl_802AC7C8[];
extern void fn_8009F53C(void *);
extern void fn_801195DC(char *);

void *fn_801C11D0(Unk_140809A5 *arg0) {
    fn_8009F53C(arg0);
    arg0->unk0x18 = (s32)lbl_802AC7C8;
    fn_801195DC((char *)arg0 + 0x2C);
    arg0->unk0x4 = QB_SKATERLOOPINGSOUND;
    arg0->unk0xF4 = lbl_802AC7AC;
    arg0->unk0xEC = 0;
    arg0->unk0xE8 = 0;
    arg0->unk0xDC = 0;
    arg0->unk0xE0 = 1;
    arg0->unk0x54 = 1;
    arg0->unk0xF8 = 1;
    arg0->unk0xE4 = 0;
    return arg0;
}
