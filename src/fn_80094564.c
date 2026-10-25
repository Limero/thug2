// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80094564-0x800945E0 (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern void *lbl_8037B5E0;
void free(void *);
void fn_80094564(Unk_89783F6B *arg0) {
    Unk_FFAD6788 *node;
    Unk_FFAD6788 *next;

    if (lbl_8037B5E0 == arg0) {
        lbl_8037B5E0 = arg0->unk0x130;
    } else {
        node = lbl_8037B5E0;
        while (node->unk0x130 != NULL) {
            if (node->unk0x130 == arg0) {
                node->unk0x130 = arg0->unk0x130;
                break;
            }
            node = node->unk0x130;
        }
    }
    free(arg0->unk0x8);
    free(arg0);
}

