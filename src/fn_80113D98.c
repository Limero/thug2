// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80113D98-0x80113DD0 (56B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
s32 ContainsFlag(s32, s32);
void ClearPlaylist(s32 arg0);

bool ScriptClearMusicTrackList(s32 arg0) {
    s32 temp_r3;

    temp_r3 = ContainsFlag(arg0, QB_FLAG_PERM);
    ClearPlaylist((temp_r3 == 0));
    return true;
}

// PARK-NOTE 2026-08-30: class-B M2C_CARRY bool-fold artifact resolved via
// recipe-100 equality rewrite — `(0 - X) + X + M2C_CARRY` -> `(X == 0)`
// (want's xor;subfic;adde idiom). Removes the .bss payload static.
