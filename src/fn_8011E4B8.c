// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011E4B8-0x8011E500 (72B). Byte-identical.
#include "types.h"
extern s32 lbl_80302C94;
s32 fn_8011BC38(void);
s32 fn_80120578(s32);
// Pcm_LoadMusicHeader @ 0x8011E4B8
s32 Pcm_LoadMusicHeader(s32 arg0) {
    if (fn_8011BC38() == 0) {
        return lbl_80302C94 = fn_80120578(arg0);
    }
    return 0;
}
