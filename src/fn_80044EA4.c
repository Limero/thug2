// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80044EA4-0x80044F0C (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8003F360(Unk_2B0B333E *);
void fn_8009E274(Unk_31DE137E *, s32);
s32 fn_80054F98(void *);
extern char lbl_80292668[];
void *fn_80044EA4(Unk_4313CFEA *arg0) {
    fn_8003F360((Unk_2B0B333E *)arg0);
    arg0->unk0x190 = 0;
    arg0->unk0x8 = (s32)lbl_80292668;
    arg0->unk0x198 = fn_80054F98(0);
    arg0->unk0x194 = 1;
    fn_8009E274((Unk_31DE137E *)arg0, QB_SPRITEELEMENT);
    return arg0;
}
