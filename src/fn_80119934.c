// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80119934-0x80119A08 (212B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// fn_80119934: voice-pool dual-field search — two passes over the 59 x 0x3C
// lbl_80387E44 slots: pass A matches slot->id1, pass B (i reset) slot->id2,
// both gated by fn_8011ED40(i); pass-B matches run Script_GetInteger QB side effects
// before returning i; miss -> -1. arg0 unused (2-arg ABI per fn_8011A6A8).
// Suggested rename: fn_VoicePoolFindId.
#include "types.h"
#include "qb_constants.h"
extern s32 fn_8011ED40(s32);
extern s32 Script_GetInteger(s32, s32);
typedef struct {
    s32 id1;
    s32 id2;
    char rest[0x34];
} PoolSlot;
extern PoolSlot lbl_80387E44[];
s32 fn_80119934(s32 arg0, s32 id) {
    s32 i;

    for (i = 0; i <= 0x3A; i++) {
        if ((lbl_80387E44[i].id1 == id) && (fn_8011ED40(i) != 0)) {
            return i;
        }
    }
    for (i = 0; i <= 0x3A; i++) {
        if ((lbl_80387E44[i].id2 == id) && (fn_8011ED40(i) != 0)) {
            if (Script_GetInteger(QB_UNKNOWN_0x6D2E270E, 0) == 0) {
                Script_GetInteger(QB_DEBUGSOUNDFX, 0);
            }
            return i;
        }
    }
    return -1;
}
