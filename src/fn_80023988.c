// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80023988-0x80023A84 (252B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    void *start;
    void *end;
    u8 *cursor;
    u8 *limit;
} buffer_t;

void fn_8028D464(void);
extern buffer_t *lbl_803CAF18;

void fn_80023988(u32 arg0, s32 arg1) {
    u16 temp_r0;
    u8 *temp_r9_2;
    u8 *temp_r9_3;
    u8 *temp_r9_4;
    u8 *temp_r9_5;
    u8 *temp_r9_6;
    buffer_t *temp_r10;
    buffer_t *temp_r10_2;
    buffer_t *temp_r10_3;
    buffer_t *temp_r11;
    buffer_t *temp_r11_2;
    buffer_t *temp_r11_3;
    buffer_t *temp_r11_4;
    buffer_t *temp_r9;

    temp_r9 = lbl_803CAF18;
    if ((u32) temp_r9->cursor + 1 > (u32) temp_r9->limit) {
        fn_8028D464();
    }
    temp_r10 = lbl_803CAF18;
    __asm__ __volatile__("" ::: "memory");
    temp_r0 = arg1 - 1;
    __asm__ __volatile__("" ::: "memory");
    temp_r9_2 = temp_r10->cursor;
    *temp_r9_2 = 0x10;
    temp_r10->cursor = temp_r9_2 + 1;
    temp_r11 = lbl_803CAF18;
    if ((u32) temp_r11->cursor + 2 > (u32) temp_r11->limit) {
        fn_8028D464();
    }
    temp_r11_2 = lbl_803CAF18;
    temp_r9_3 = temp_r11_2->cursor;
    *temp_r9_3 = (u8) (temp_r0 >> 8U);
    temp_r11_2->cursor = temp_r9_3 + 1;
    temp_r10_2 = lbl_803CAF18;
    temp_r9_4 = temp_r10_2->cursor;
    *temp_r9_4 = (u8) temp_r0;
    temp_r10_2->cursor = temp_r9_4 + 1;
    temp_r11_3 = lbl_803CAF18;
    if ((u32) temp_r11_3->cursor + 2 > (u32) temp_r11_3->limit) {
        fn_8028D464();
    }
    temp_r10_3 = lbl_803CAF18;
    temp_r9_5 = temp_r10_3->cursor;
    *temp_r9_5 = (u8) (arg0 >> 8U);
    temp_r10_3->cursor = temp_r9_5 + 1;
    temp_r11_4 = lbl_803CAF18;
    temp_r9_6 = temp_r11_4->cursor;
    *temp_r9_6 = (u8) arg0;
    temp_r11_4->cursor = temp_r9_6 + 1;
}
