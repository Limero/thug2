// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80138E24-0x80138EF0 (204B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_80139510(s32, s32, s32, s32, s32, s32);
s32 fn_8013AB54(void);
s32 fn_8013A9C0(void);
s32 fn_8013A9D0(void);
s32 fn_8013A7D4(void);
bool fn_80138E24(Unk_2D712DCE *arg0) {
    void *temp_r30;

    arg0->unk0x182C = 0;
    arg0->unk0x0 = 0;
    if (fn_8013AB54() == 0) {
        return false;
    }
    temp_r30 = (char *)arg0 + 4;
    fn_80139510((s32)temp_r30, 4, (s32)fn_8013A9C0, 3, 0, 0x80);
    fn_80139510((s32)temp_r30, 5, (s32)fn_8013A9D0, 2, 0, 0x80);
    fn_80139510((s32)temp_r30, 6, (s32)fn_8013A9D0, 2, 0, 0x80);
    fn_80139510((s32)temp_r30, 9, (s32)fn_8013A7D4, 3, 0, 0x80);
    return true;
}
