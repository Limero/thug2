// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80125C70-0x80125CE4 (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
unsigned int fn_8000A778(const char *str);
void *fn_80125568(s32 arg0);
void fn_801263A0(s32 arg0, const char *arg1);

typedef struct {
    s32 name;
    s32 next;
} Elem8;

void fn_80125C70(void *arg0, u32 arg1) {
    u32 i;
    u8 eight;
    Elem8 *var;
    s32 nm;
    s32 crc;
    s32 nm2;
    void *node;
    s32 nxt;

    i = 0;
    if (i < arg1) {
        var = arg0;
        eight = 8;
        do {
            nm = var->name;
            i++;
            crc = (s32)fn_8000A778((const char *)nm);
            nm2 = var->name;
            fn_801263A0(crc, (const char *)nm2);
            node = fn_80125568(crc);
            *(u8 *)((char *)node + 2) = eight;
            nxt = var->next;
            var = (Elem8 *)((char *)var + 8);
            *(s32 *)((char *)node + 0xC) = nxt;
        } while (i < arg1);
    }
}
