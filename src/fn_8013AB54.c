// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013AB54-0x8013AC98 (324B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8013E2BC(void);
void fn_80139600(void *);
s32 fn_80139510(void *, s32, void *, s32, s32, s32);
void fn_80139BDC(void);
void fn_80139EF4(void);
void fn_8013A398(void);
void fn_8013A508(void);
void fn_8013A8D0(void);
void fn_8013A93C(void);
bool fn_8013AB54(Unk_BDBFA817 *arg0) {
    s32 temp_r3;
    void *temp_r30;

    temp_r3 = fn_8013E2BC();
    if (temp_r3 == 0) {
        arg0->unk0x1820 = temp_r3;
    }
    temp_r30 = (char *)arg0 + 4;
    arg0->unk0x1844 = 0;
    arg0->unk0x17F4 = 0;
    arg0->unk0x17F0 = 0;
    arg0->unk0x17F8 = 0;
    arg0->unk0x17FC = 0;
    arg0->unk0x1800 = 0;
    arg0->unk0x1804 = 0;
    fn_80139600(temp_r30);
    fn_80139510(temp_r30, 8, fn_80139BDC, 3, 0, 0x80);
    fn_80139510(temp_r30, 7, fn_8013A508, 2, 0, 0x80);
    fn_80139510(temp_r30, 0x12, fn_8013A398, 3, 0, 0x80);
    fn_80139510(temp_r30, 0xE, fn_80139EF4, 2, 0, 0x80);
    fn_80139510(temp_r30, 0xF, fn_80139EF4, 2, 0, 0x80);
    fn_80139510(temp_r30, 1, fn_8013A8D0, 2, 0, 0x80);
    fn_80139510(temp_r30, 2, fn_8013A93C, 2, 0, 0x80);
    return true;
}
