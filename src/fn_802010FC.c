// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802010FC-0x802011B8 (188B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern Unk_71062261 *lbl_80305EAC;
extern s32 lbl_80305EC0;
s32 IsTrue(s32, void *);
s32 fn_80174AB8(Unk_71062261 *, s32);
s32 GetChecksum_2(s32, s32, s32 *, s32);

s32 fn_802010FC(Unk_BC7B49A5 *arg0) {
    s32 sp8;
    Unk_71062261 *temp_r31;

    if ((s32) arg0->unk0xA9C != 0) {
        temp_r31 = lbl_80305EAC;
        if ((IsTrue(lbl_80305EC0, QB_IS_CAREER) != 0) && ((s32) arg0->unk0x9F8 != 0) && ((s32) temp_r31->unk0x388 != -QB_UNKNOWN_0x16D13502)) {
            GetChecksum_2(fn_80174AB8(lbl_80305EAC, 0) + 0x6C, QB_NAME, &sp8, 1);
            return ((sp8 ^ QB_CUSTOM) == 0);
        }
    }
    return 0;
}
