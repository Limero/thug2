// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023862C-0x8023869C (112B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80239CF4(void *);
s32 fn_802432A0(Unk_9994C3F5 *);
s32 fn_802416F8(s32);
s32 fn_80237A88(Unk_673C6403 *, CStruct *, s32, s32, s32);
void fn_8023862C(Unk_C7387A53 *arg0) {
    CStruct *node;

    fn_80239CF4(arg0);
    node = *((void * *)&arg0->unk0xC);
    if (node != NULL) {
        do {
            node->unk0x8 =
                fn_80237A88(arg0, fn_802416F8(fn_802432A0(node)), 0, -node->unk0x4, 0);
            node = *((void * *)&node->unk0xC);
        } while (node != NULL);
    }
}
