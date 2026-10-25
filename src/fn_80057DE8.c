// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80057DE8-0x80057E2C (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

// arg0+0x10: optional override object; arg0+0x14: default object whose u16
// at +4 carries a bit-2 flag.  Kept as a file-local layout on purpose — the
// shared CStruct types 0x10 as s32 and has no member at 0x14, and changing
// the shared header is out of scope for this worker.
typedef struct {
    char pad0x0[0x10];
    void *unk0x10;
    void *unk0x14;
} S_80057DE8;

typedef struct {
    u16 flags;
} S_80057DE8Flags;

extern s32 fn_8005F224(void *sub);

s32 fn_80057DE8(S_80057DE8 *arg0) {
    void *sub = arg0->unk0x10;
    if (sub != 0) {
        return fn_8005F224(sub);
    }
    return !(((S_80057DE8Flags *)((char *)arg0->unk0x14 + 4))->flags & 4);
}
