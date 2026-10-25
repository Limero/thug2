// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011A6A8-0x8011A708 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// fn_8011A6A8: voice find-and-kill wrapper — fn_80119934(arg0,arg1) >= 0
// (slot found) -> fn_8011F210(idx), 1; returns 1 immediately when fn_80119470()!=0.
// Suggested rename: fn_VoiceKillById.
#include "types.h"
extern s32 fn_80119470(void);
extern s32 fn_80119934(s32, s32);
extern void fn_8011F210(s32);
bool fn_8011A6A8(s32 arg0, s32 arg1) {
    s32 idx;

    if (fn_80119470() != 0) {
        return true;
    }
    idx = fn_80119934(arg0, arg1);
    if (idx < 0) {
        return false;
    }
    fn_8011F210(idx);
    return true;
}
