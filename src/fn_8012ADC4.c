// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012ADC4-0x8012AF84 (448B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_8012A8F0(Unk_5B449B03 *, s32 *, s32 *);
s32 strlen(const char *);
s32 fn_80128B48(void *, void *);

typedef union {
    s32 i;
    f32 f;
} Value;

s32 fn_8012ADC4(Unk_5B449B03 *arg0, Unk_5B449B03 *arg1) {
    Value sp14;
    s32 sp10;
    Value spC;
    s32 sp8;
    u32 temp_r30;

    fn_8012A8F0(arg0, &sp8, (s32 *)&spC);
    fn_8012A8F0(arg1, &sp10, (s32 *)&sp14);

    switch (sp8) {
    case 1:
        if (sp10 != 2) {
            goto case1_integer;
        }
        return (f32)(f64)(s32)spC.i > sp14.f;
    case1_integer:
        if (sp10 != 1) {
            return 0;
        }
        return spC.i > sp14.i;
    case 2:
        if (sp10 != 1) {
            goto case2_float;
        }
        return spC.f > (f32)(f64)(s32)sp14.i;
    case2_float:
        if (sp10 != 2) {
            return 0;
        }
        return spC.f > sp14.f;
    case 3:
        if (sp10 != 3) {
            break;
        }
        temp_r30 = strlen((const char *)spC.i);
        return strlen((const char *)sp14.i) < temp_r30;
    case 4:
        if (sp10 != 4) {
            break;
        }
        temp_r30 = strlen((const char *)spC.i);
        return strlen((const char *)sp14.i) < temp_r30;
    case 10:
    case 20:
        if ((sp10 == 0xA) || (sp10 == 0x14)) {
            return fn_80128B48((void *)sp14.i, (void *)spC.i);
        }
        return 0;
    }
fail:
    return 0;
}
