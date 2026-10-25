// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80119F10-0x80119FB4 (164B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// fn_80119F10: unlink node from the lbl_80302C40 doubly-linked list (next +0x10 / prev +0x14),
// update head + decrement lbl_80302C4C; if flag && fn_8011A95C(arg0,id,0), notify fn_8011A6A8.
// Suggested rename: fn_ListUnlink.
#include "types.h"
#include "structs.h"
extern s32 fn_8011A95C(void *, s32, s32 *);
extern s32 fn_8011A6A8(s32, s32);
extern s32 *lbl_80302C40;
extern s32 lbl_80302C4C;
void fn_80119F10(void *arg0, Unk_DB0E2BAB *node, s32 flag) {
    Unk_C8FEE62D *t;
    CStruct *t2;

    node->unk0x8 = 0;
    if ((flag != 0) && (fn_8011A95C(arg0, node->unk0x0, 0) != 0)) {
        fn_8011A6A8((s32)arg0, node->unk0x0);
    }
    t = *((void * *)&node->unk0x10);
    if (t != NULL) {
        *((void * *)&t->unk0x14) = *((void * *)&node->unk0x14);
    }
    t2 = *((void * *)&node->unk0x14);
    if (t2 != NULL) {
        *((void * *)&t2->unk0x10) = *((void * *)&node->unk0x10);
    } else {
        lbl_80302C40 = *((void * *)&node->unk0x10);
    }
    lbl_80302C4C -= 1;
}
