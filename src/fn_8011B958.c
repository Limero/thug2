// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011B958-0x8011B9F4 (156B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern s32 fn_8011A95C(void *, s32, s32 *);
extern void *lbl_80302C40;
extern char lbl_80387E50[];

s32 fn_8011B958(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp8;
    s32 f;
    CStruct *node;
    char *pool;

    node = (void *)lbl_80302C40;
    if (node == NULL) {
        return 0;
    }
    pool = lbl_80387E50;
    while (node != NULL) {
        if (arg3 != 0) {
            f = node->unk0x4;
        } else {
            f = node->unk0x0;
        }
        if ((node->unk0xC == arg1) && (f == arg2)) {
            s32 res = fn_8011A95C(arg0, node->unk0x0, &sp8);
            s32 r = 0;
            if (res != 0) {
                r = sp8;
                r = r * 0x3C;
                r = r + (s32)pool;
            }
            return r;
        }
        node = *((void * *)&node->unk0x10);
    }
    return 0;
}
