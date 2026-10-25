// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80125CE4-0x80125D54 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
unsigned int fn_8000A778(const char *str);
void *fn_80125568(s32 arg0);
void fn_801263A0(s32 arg0, const char *arg1);

void fn_80125CE4(const char **arg0, u32 arg1) {
    u32 i;
    s32 j;
    u8 nine;

    i = 0;
    if (i < arg1) {
        nine = 9;
        j = 0;
        do {
            s32 nm = *(s32 *)((char *)(j + (s32)arg0));
            s32 crc = (s32)fn_8000A778((const char *)nm);
            s32 nm2 = *(s32 *)((char *)(j + (s32)arg0));
            i++;
            fn_801263A0(crc, (const char *)nm2);
            j += 4;
            *(u8 *)((char *)fn_80125568(crc) + 2) = nine;
        } while (i < arg1);
    }
}
