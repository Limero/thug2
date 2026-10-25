// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80119E48-0x80119F10 (200B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// fn_80119E48: walk of the lbl_80302C40 Script-pool list — per node, look up its slot
// (fn_8011A95C); absent -> fn_80119F10(arg0,node,0), else refresh the slot
// (sp8*0x3C + lbl_80387E44) via fn_800CD2F4/fn_80119C38, removing on failure.
// Suggested rename: fn_RefreshPoolEntries.
#include "types.h"
#include "structs.h"
extern s32 fn_800145AC(void);
extern s32 fn_8011A95C(void *, s32, s32 *);
extern void fn_800CD2F4(s32, Unk_DB0E2BAB *);
extern s32 fn_80119C38(Unk_C8FEE62D *, Unk_FFAD6788 *, CStruct *, s32);
extern void fn_80119F10(void *, Unk_DB0E2BAB *, s32);
extern s32 *lbl_80302C40;
extern char lbl_80387E44[];
void fn_80119E48(Unk_C8FEE62D *arg0) {
    s32 sp8;
    s32 slot;
    s32 now;
    CStruct *node;
    void *walker;

    walker = (void *)lbl_80302C40;
    now = fn_800145AC();
    if (walker != NULL) {
        do {
            node = walker;
            walker = *((void * *)&node->unk0x10);
            if (fn_8011A95C(arg0, node->unk0x0, &sp8) == 0) {
                fn_80119F10(arg0, node, 0);
            } else {
                slot = sp8 * 0x3C + (s32)(s32 *)lbl_80387E44;
                fn_800CD2F4(node->unk0xC, (void *)(slot + 0xC));
                if (fn_80119C38(arg0, node->unk0xC, (void *)slot, now) == 0) {
                    fn_80119F10(arg0, node, 1);
                }
            }
        } while (walker != NULL);
    }
}
