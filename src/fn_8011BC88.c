// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011BC88-0x8011BCE4 (92B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_8011BCE4(CScript *);
s32 fn_8011BC88(CScript *obj) {
    s32 cur = obj->unk0x1C + 1;
    obj->unk0x1C = cur;
    if (cur >= obj->unk0x20) {
        if (obj->unk0x18 == 0)
            return 0;
        obj->unk0x18 = obj->unk0x18 - 1;
        obj->unk0x1C = 0;
    }
    return fn_8011BCE4(obj);
}

