// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012156C-0x80121624 (184B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 DVDReadAsyncPrio(s32, s32, s32, s32, s32, s32, s32);
void fn_80121624(void);
extern char lbl_8039BA58[];
void fn_8012156C(void) {
    s32 temp_r29;
    s32 temp_r30;
    void *temp_r9;
    char *base;

    base = lbl_8039BA58;
    temp_r29 = *(s32 *)(base + 0x2C4);
    if (temp_r29 == 0) {
        temp_r30 = *(s32 *)(base + 0x2C8);
        if (temp_r30 == 1) {
            if ((u32) *(u32 *)(base + 0x2DC) > (u32) (*(u32 *)(base + 0x8C) - 1)) {
                if ((s32) *(s32 *)(base + 0x2CC) != 0) {
                    *(s32 *)(base + 0x2D4) = *(s32 *)(base + 0x2E4);
                    *(s32 *)(base + 0x2D8) = *(s32 *)(base + 0x2E8);
                    *(u32 *)(base + 0x2DC) = (u32) temp_r29;
                    goto block_5;
                }
            } else {
block_5:
                temp_r9 = base + 0x2F4;
                *(s32 *)(base + 0x2D0) = temp_r30;
                if (DVDReadAsyncPrio(base + 0xC, *(s32 *)((char *)temp_r9 + (*(s32 *)(base + 0x2EC) * 0x10)), *(s32 *)(base + 0x2D8), *(s32 *)(base + 0x2D4), (s32)fn_80121624, 2, temp_r9) != 1) {
                    *(s32 *)(base + 0x2D0) = temp_r29;
                    *(s32 *)(base + 0x2C4) = temp_r30;
                }
            }
        }
    }
}
