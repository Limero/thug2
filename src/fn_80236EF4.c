// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80236EF4-0x80236F80 (140B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_802432A0(Unk_9994C3F5 *);
s32 fn_802416FC(s32);
void *fn_80236EF4(CStruct *arg0, s32 arg1, s32 *arg2) {
    void *node = *((void * *)&arg0->unk0x84);
    s32 counter = arg0->unk0x8C - 1;
    if (node != NULL) {
        do {
            void *node2 = (void *)fn_802416FC(fn_802432A0(node));
            if (((Unk_C7387A53 *)node2)->unk0x34 == arg1) {
                if (arg2 != NULL) {
                    *arg2 = counter;
                }
                return node2;
            }
            node = *((void * *)&((Unk_C7387A53 *)node)->unk0xC);
            counter -= 1;
        } while (node != NULL);
    }
    return NULL;
}
