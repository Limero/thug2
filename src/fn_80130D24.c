// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80130D24-0x80130D74 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct S130D24 {
    char pad0[0x38];
    s32 unk38;
    char pad3C[0x58];
    s32 unk94;
    char pad98[0x30];
    s32 unkC8;
} S130D24;
bool fn_80130D24(S130D24 *arg0, s32 arg1) {
    s32 i;
    s32 *p;

    if (arg0->unkC8 == arg1)
        return true;
    i = 0;
    if (i < arg0->unk38) {
        p = (s32 *)arg0->unk94;
        do {
            s32 v = *p;
            p = (s32 *)((char *)p + 0x2C);
            if (v == arg1)
                return true;
            i++;
        } while (i < arg0->unk38);
    }
    return false;
}
