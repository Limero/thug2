// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80138748-0x801387FC (180B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_80139510(s32, s32, s32, s32, s32, s32);
s32 fn_8013A9FC(void);
s32 fn_8013A6FC(void);
s32 fn_8013A744(void);
s32 fn_8013AB54(void);
bool fn_80138748(Unk_2E8E04CA *arg0) {
    void *temp_r30;

    arg0->unk0x0 = 0;
    arg0->unk0x182C = 0;
    arg0->unk0x1848 = 0;
    if (fn_8013AB54() == 0) {
        return false;
    }
    temp_r30 = (char *)arg0 + 4;
    fn_80139510((s32)temp_r30, 3, (s32)fn_8013A9FC, 3, 0, 0xFF);
    fn_80139510((s32)temp_r30, 9, (s32)fn_8013A6FC, 3, 0, 0x80);
    fn_80139510((s32)temp_r30, 0xB, (s32)fn_8013A744, 2, 0, 0xFF);
    return true;
}
