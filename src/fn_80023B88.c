// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80023B88-0x80023C8C (260B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct { void *start; void *end; u8 *cursor; void *limit; } buf_t;
extern buf_t *lbl_803CAF18;
void fn_8028D464(void);

void fn_80023B88(s32 arg0, u32 arg1, u32 arg2) {
    s32 b2;
    s32 b4;

    if ((u32)(lbl_803CAF18->cursor + 1) > (u32)lbl_803CAF18->limit) {
        fn_8028D464();
    }
    *lbl_803CAF18->cursor++ = 0x28;
    if ((u32)(lbl_803CAF18->cursor + 2) > (u32)lbl_803CAF18->limit) {
        fn_8028D464();
    }
    b2 = arg2 >> 8;
    arg1 = (((arg1 - 1) << 0xC) & 0xF000) | arg0;
    *lbl_803CAF18->cursor++ = b2;
    *lbl_803CAF18->cursor++ = arg2;
    if ((u32)(lbl_803CAF18->cursor + 2) > (u32)lbl_803CAF18->limit) {
        fn_8028D464();
    }
    b4 = arg1 >> 8;
    *lbl_803CAF18->cursor++ = b4;
    *lbl_803CAF18->cursor++ = arg1;
}
