// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B97F8-0x801B98B4 (188B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 GetChecksum_3(Unk_6A70655D * obj, s32 hash);
extern void fn_800B33EC(CScript * a0, Unk_C8FEE62D * hash, s32 on, s32 flag);

bool fn_801B97F8(Unk_C7387A53 *arg0, s32 arg1) {
    s32 temp_r3;

    if ((arg0->unk0x24 & 1) != 0) {
        temp_r3 = GetChecksum_3(arg0->unk0xC, QB_MODEL);
        if (temp_r3 != 0) {
            if (arg1 != 0) {
                if ((arg0->unk0x24 & 0x20000) == 0) {
                    fn_800B33EC(temp_r3, QB_BOARD, 1, 1);
                    arg0->unk0x24 |= 0x20000;
                }
            } else {
                if ((arg0->unk0x24 & 0x20000) != 0) {
                    fn_800B33EC(temp_r3, QB_BOARD, 0, 1);
                    arg0->unk0x24 &= ~0x20000;
                }
            }
        }
        return true;
    }
    return false;
}
