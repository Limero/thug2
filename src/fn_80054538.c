// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80054538-0x800545E0 (168B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
s32 fn_8009F498(void *);
void *GetChecksum_3(void *, s32);
s32 fn_80060E4C(s32, s32);
void Mem_Free2(void *);
void fn_80054538(char *arg0) {
    if (*(s32 *)(arg0 + 4) != 0) {
        s32 i;
        for (i = 0; i < *(s32 *)(arg0 + 8); i++) {
            void *p = (void *)fn_8009F498(*(void **)(*(s32 *)(arg0 + 4) + i * 4));
            if (p != 0) {
                fn_80060E4C(*(s32 *)((char *)GetChecksum_3(p, QB_MODEL) + 0x210), 0);
            }
        }
        if (*(s32 *)(arg0 + 4) != 0) {
            Mem_Free2(*(void **)(arg0 + 4));
        }
        *(s32 *)(arg0 + 4) = 0;
    }
    *(s32 *)(arg0 + 8) = 0;
}
