// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800331F8-0x80033310 (280B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_80291B58[];
typedef s32 (*Unk_800331F8_t)(void *, f32, f32, s32);
s32 fn_80032A60();
s32 fn_80033198(void *);
s32 fn_80033530(void *);
void fn_8002BA5C(s32, s32);
void fn_8002BA64(s32, s32);
void fn_800331F8(void *arg0, f32 farg0, f32 farg1) {
    volatile double _dummy;
    volatile double _stack_double;
    f32 temp_f0;
    s32 temp_r30;
    u32 var_r28;
    s32 var_r29;
    void *temp_r11;
    void *temp_sub;
    Unk_800331F8_t temp_fn;

    if (*(s32 *)((char *)arg0 + 0x74) != 0 && fn_80032A60() == 2) {
        temp_f0 = *(f32 *)lbl_80291B58;
        farg0 = farg0 * temp_f0;
        farg1 = farg1 * temp_f0;
        if (*(s32 *)((char *)arg0 + 0x2C) == 0) {
            if (farg0 > farg1) {
                fn_80033198(arg0);
                farg0 = *(f32 *)((char *)arg0 + 0x1C);
            }
        } else {
            if (farg1 > farg0) {
                fn_80033198(arg0);
                farg0 = *(f32 *)((char *)arg0 + 0x1C);
            }
        }
        var_r28 = 0U;
        if (var_r28 < (u32) *(u32 *)((char *)arg0 + 0x70)) {
            var_r29 = 0;
            do {
                fn_8002BA5C(*(s32 *)((char *)arg0 + 0x6C) + var_r29, 1);
                temp_r11 = var_r29 + *(s32 *)((char *)arg0 + 0x6C);
                temp_sub = *(void **)((char *)temp_r11 + 0x8);
                temp_fn = *(Unk_800331F8_t *)((char *)temp_sub + 0x14);
                if (temp_fn((char *)temp_r11 + *(s16 *)((char *)temp_sub + 0x10), farg0, farg1, 0) != 0) {
                    temp_r30 = *(s32 *)((char *)arg0 + 0x6C) + var_r29;
                    fn_8002BA64(temp_r30, fn_80033530(arg0));
                }
                var_r28 += 1;
                var_r29 += 0x14;
            } while (var_r28 < (u32) *(u32 *)((char *)arg0 + 0x70));
        }
    }
}
