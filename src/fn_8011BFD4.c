// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011BFD4-0x8011C03C (104B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_8011BC60(void);
extern s32 fn_8011BD7C(s32, s32);
extern void fn_80120F20(s32, f32, f32);
bool fn_8011BFD4(s32 arg0, CStruct *arg1) {
    s32 temp_r3;

    if (fn_8011BC60() != 0) {
        return true;
    }
    temp_r3 = fn_8011BD7C(arg0, 1);
    if (temp_r3 >= 0) {
        fn_80120F20(temp_r3, *((f32 *)&arg1->unk0x0), *((f32 *)&arg1->unk0x4));
        return true;
    }
    return false;
}
