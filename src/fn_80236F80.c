// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80236F80-0x80236FE4 (100B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_802432A0(Unk_9994C3F5 *);
s32 fn_802416FC(s32);
s32 fn_80236F80(CStruct *arg0, s32 arg1) {
    void *node = *((void * *)&arg0->unk0x84);
    s32 counter = arg0->unk0x8C - 1;
    if (node != NULL) {
        do {
            s32 val = fn_802416FC(fn_802432A0(node));
            if (counter == arg1) {
                return val;
            }
            node = *((void * *)&((Unk_C7387A53 *)node)->unk0xC);
            counter -= 1;
        } while (node != NULL);
    }
    return 0;
}
