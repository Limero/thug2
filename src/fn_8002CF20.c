// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002CF20-0x8002CF60 (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

typedef struct ScriptRecord {
    char pad0x0[0x2C];
    s32 entries[1];
} ScriptRecord;

s16 fn_8002CAE4(CScript *, s32);

s16 fn_8002CF20(ScriptRecord *arg0, s32 arg1, s16 arg2) {
    CScript *entry = (CScript *)arg0->entries[arg1];
    return entry != 0 ? fn_8002CAE4(entry, arg2) : 0;
}
