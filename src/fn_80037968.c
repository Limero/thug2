// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80037968-0x800379CC (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

/* Wait-list entry: 0x20 stride (matches fn_80036328), id at +0x00,
   flag word at +0x08, the 16 bytes fn_80037BF0 copies out at +0x10. */
typedef struct {
    s32 key;
    s32 unk4;
    s32 flags;
    s32 unkC;
    f32 v0;
    f32 v1;
    f32 v2;
    f32 v3;
} WaitEntry;

WaitEntry *fn_80036328(Unk_C8FEE62D *arg0, s32 arg1);

s32 fn_80037968(Unk_C8FEE62D *arg0, s32 arg1, s32 arg2) {
    s32 found;
    s32 masked;
    s32 armed;
    WaitEntry *entry;

    entry = fn_80036328(arg0, arg1);
    if (entry != NULL) {
        masked = entry->flags & QB_UNKNOWN_0xBFFFFFFF;
        entry->flags = masked;
        armed = masked;
        if (arg2 == 0) {
            armed |= QB_UNKNOWN_0x40000000;
        }
        entry->flags = armed;
    }
    found = 1;
    if (entry == NULL) {
        found = 0;
    }
    return found;
}
