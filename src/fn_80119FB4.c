// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80119FB4-0x8011A014 (96B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 *lbl_80302C40;
void fn_80119F10(void *, Unk_DB0E2BAB *, s32);
void fn_80119FB4(void *arg0, s32 arg1) {
    void *cur;
    CStruct *node;

    cur = lbl_80302C40;
    while (cur != NULL) {
        node = cur;
        cur = *((void * *)&node->unk0x10);
        if (node->unk0xC == arg1) {
            fn_80119F10(arg0, node, 1);
        }
    }
}
