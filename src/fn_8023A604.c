// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023A604-0x8023A670 (108B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_802432A0(Unk_9994C3F5 *);
void *fn_8023F778(s32);
void fn_8023A604(s32 unused, s32 arg1, void **arg2) {
    Unk_C7387A53 *node;

    node = *arg2;
    if (node != NULL) {
        do {
            if (fn_802432A0(node) == arg1) {
                return;
            }
            node = *((void * *)&node->unk0xC);
        } while (node != NULL);
    }
    {
        void *newNode = fn_8023F778(0x10);
        ((CStruct *)newNode)->unk0x8 = arg1;
        ((CStruct *)newNode)->unk0xC = (s32)*arg2;
        *arg2 = newNode;
    }
}
