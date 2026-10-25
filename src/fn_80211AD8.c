// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80211AD8-0x80211B40 (104B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetChecksum_3(Unk_6A70655D * arg0, s32 arg1);
extern void fn_800DDD98(s32 arg0, void *arg1);
extern void fn_800DDDAC(s32 arg0, void *arg1);
void fn_80211AD8(Unk_3CB21567 *arg0, Unk_FFAD6788 *arg1) {
    register f32 temp_f13 __asm__("fr13");
    s32 temp_r30;
    Unk_31DE137E *temp_r9;
    void *temp_r28;

    temp_f13 = *((f32 *)&arg1->unk0x8C);
    temp_r9 = arg0->unk0x1854;
    *((f32 *)&temp_r9->unk0x18C) = *((f32 *)&arg0->unk0x2C) - temp_f13;
    temp_r28 = (char *)arg1 + 0x88;
    temp_r30 = GetChecksum_3(arg0->unk0xC, QB_SHADOW);
    fn_800DDD98(temp_r30, temp_r28);
    fn_800DDDAC(temp_r30, (char *)arg1 + 0x98);
}
