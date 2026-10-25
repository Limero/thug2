// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80077FBC-0x80077FEC (48B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct {
    char pad0x0[0x5];
    u8 unk0x5;
    char pad0x6[1];
    u8 unk0x7;
} cnt_t;
u16 fn_80077FBC(Unk_C7387A53 *arg0) {
    cnt_t *temp_r9;
    temp_r9 = (cnt_t *)arg0->unk0xC;
    if (temp_r9 != NULL) {
        return (u16) ((1 << temp_r9->unk0x7) - temp_r9->unk0x5);
    }
    return 0U;
}
