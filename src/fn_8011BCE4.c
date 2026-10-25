// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011BCE4-0x8011BD0C (40B). Byte-identical.
#include "types.h"
#include "structs.h"
typedef struct { /*8011BD10*/ s32 unk0; s32 unk4; } struct_8011BCE4_8;
s32 fn_8011BCE4(CScript *arg0) {
    s32 temp_r9;
    s32 temp_r0;
    char *var_r9;

    temp_r9 = arg0->unk0x1C;
    if (temp_r9 < (s32) arg0->unk0x20) {
        temp_r0 = temp_r9 * 8;
        var_r9 = (char *)arg0 + (s32)0x34;
        return *(s32 *)(var_r9 + temp_r0);
    }
    return 0;
}
