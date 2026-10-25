// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002CAE4-0x8002CB04 (32B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

// Bitfield view of CScript::unk0x1E4 (big-endian bit order: hi first).
typedef struct {
    u32 hi:15; /* bits 31..17 */
    u32 lo:17; /* bits 16..0  */
} CScriptV3E4;

s16 fn_8002CAE4(CScript *arg0, s32 arg1) {
    s32 old = arg0->unk0x1E4;
    s16 diff = arg1 - (old >> 0x11);
    ((CScriptV3E4 *)&arg0->unk0x1E4)->hi = arg1;
    return diff;
}
