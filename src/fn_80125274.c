// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80125274-0x801252A8 (52B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_803031A0[];

// SetScriptString @ 0x80125274
void SetScriptString(s32 arg0, const char* str) {
    sprintf((arg0 << 7) + lbl_803031A0, str);
}
