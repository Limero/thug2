// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80013FB4-0x80014004 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct {
    char p0[0x10];
    s32 count;
    char p1[4];
} Rec80013FB4;
void *fn_80013FB4(Rec80013FB4 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 i;

    for (i = 0; i < arg0->count; i++) {
        s32 *temp_r9 = (s32 *) ((char *) arg0 + 0x24) + i * 4;
        if ((temp_r9[-1] == arg1) && (temp_r9[0] == arg2)) {
            return (char *) arg0 + 0x18 + i * 0x10;
        }
    }
    return NULL;
}
