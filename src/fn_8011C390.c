// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011C390-0x8011C3D0 (64B). Byte-identical.
#include "types.h"
extern s32 fn_8011BC38(void);
extern s32 fn_80121314(s32 arg0);
s32 fn_8011C390(s32 arg0) {
    return fn_8011BC38() == 0 ? fn_80121314(arg0) : 0;
}
