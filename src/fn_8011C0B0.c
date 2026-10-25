// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011C0B0-0x8011C11C (108B). Byte-identical.
#include "types.h"
s32 fn_8011BC38(void);
s32 fn_80120824(s32, s32);
f32 fn_801204CC(f32);
// _PlayMusicTrack @ 0x8011C0B0
bool _PlayMusicTrack(s32 arg0, f32 farg0) {
    volatile double _dummy;
    if (fn_8011BC38() != 0) {
        return false;
    }
    if (fn_80120824(arg0, 0) == 0) {
        return false;
    }
    fn_801204CC(farg0);
    return true;
}
