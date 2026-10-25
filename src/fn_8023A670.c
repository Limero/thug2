// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023A670-0x8023A6F4 (132B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_802432A0(Unk_9994C3F5 *);
void fn_8023F7C8(void *);
void fn_8023A670(s32 unused, s32 arg1, void **arg2) {
    Unk_C7387A53 *prev;
    Unk_C7387A53 *node;

    prev = NULL;
    node = *arg2;
    while (node != NULL) {
        if (fn_802432A0(node) == arg1) {
            if (prev != NULL) {
                *((void * *)&prev->unk0xC) = *((void * *)&node->unk0xC);
            } else {
                *arg2 = *((void * *)&node->unk0xC);
            }
            fn_8023F7C8(node);
            return;
        }
        prev = node;
        node = *((void * *)&node->unk0xC);
    }
}
