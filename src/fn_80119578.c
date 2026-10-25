// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80119578-0x801195DC (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
//
// Frame-countdown tick of the sound-system init cluster (0x8011xxxx, docs/
// neversoft-audio-engine.md §4.1). Decrements the global tick counter
// lbl_80302C38; once it reaches <= 1 and the state pointer lbl_80302C34 is
// non-null, dispatches fn_801197FC(state, 3) (which runs the state helpers
// fn_8011984C / Mem_Free), then clears both globals. Sibling of the
// init-outer fn_80119510 which sets the same globals.
// Suggested rename: SoundInitCountdownTick
#include "types.h"
extern s32 lbl_80302C34;
extern s32 lbl_80302C38;
void fn_801197FC(void *arg0, s32 arg1);
void fn_80119578(void) {
    s32 t;
    s32 f;
    t = lbl_80302C38;
    if ((u32)t > 1U) {
        lbl_80302C38 = t - 1;
        return;
    }
    f = lbl_80302C34;
    if (f != 0) {
        fn_801197FC((void *)f, 3);
    }
    lbl_80302C34 = 0;
    lbl_80302C38 = 0;
}
