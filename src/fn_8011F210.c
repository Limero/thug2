// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011F210-0x8011F25C (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// fn_8011F210: stop a voice — when fn_8011ED40(arg0), AXSetVoiceState(
// lbl_8038EBB8[arg0*2], 0). Suggested rename: fn_VoiceStop.
// 2026-09-04: decl cleanup — fn_8011ED40 was declared (void) and
// called with no args; retail passes arg0 through r3, so both compiled to the
// same bytes, but the (s32) decl now matches fn_8011ED40's true 1-arg arity.
#include "types.h"
extern s32 lbl_8038EBB8[];
extern void AXSetVoiceState(s32, s32);
extern s32 fn_8011ED40(s32);
void fn_8011F210(s32 arg0) {
    if (fn_8011ED40(arg0) != 0) {
        AXSetVoiceState(lbl_8038EBB8[arg0 * 2], 0);
    }
}
