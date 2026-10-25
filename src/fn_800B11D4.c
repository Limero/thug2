// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B11D4-0x800B120C (56B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80301B0C[];
void *fn_800B11D4(s32 arg0) {
    Unk_C8FEE62D *cur;

    cur = *(s32 *)((char *)(*(void * *)&lbl_80301B0C) + (s32)0x4);
    if (cur != NULL) {
        while (cur != NULL) {
            if (cur->unk0x4 == arg0) {
                return cur;
            }
            cur = cur->unk0xA8;
        }
    }
    return NULL;
}
