// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011AC40-0x8011AC94 (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// fn_8011AC40: voice pitch/param wrapper — fn_8011AC94(arg0, arg2,
// atan2f(arg1->f0, -(arg1->f8)) * lbl_8029D528).
// Suggested rename: fn_VoiceSetParam (verify).
#include "types.h"
#include "structs.h"
extern f32 atan2f(f32, f32);
extern void fn_8011AC94(s32, s32, f32);
extern f32 lbl_8029D528;
void fn_8011AC40(void *arg0, CStruct *arg1, s32 arg2) {
    fn_8011AC94(arg0, arg2,
                atan2f(*((f32 *)&arg1->unk0x0),
                            -(*((f32 *)&arg1->unk0x8))) * lbl_8029D528);
}
