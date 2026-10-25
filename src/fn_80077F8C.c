// Promoted from src/wip (m2c draft hand-refined to exact match; fields at +4/+6 are u8
// here — lbz in want — via local cnt_t overlay; shared Unk_897A0ACF keeps u16 users).
// range 0x80077F8C-0x80077FBC (48B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct {
    char pad0x0[0x4];
    u8 unk0x4;
    char pad0x5[1];
    u8 unk0x6;
} cnt_t;
u16 fn_80077F8C(Unk_C7387A53 *arg0) {
    cnt_t *temp_r9;
    temp_r9 = (cnt_t *)arg0->unk0xC;
    if (temp_r9 != NULL) {
        return (u16) ((1 << temp_r9->unk0x6) - temp_r9->unk0x4);
    }
    return 0U;
}
