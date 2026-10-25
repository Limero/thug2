// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802424AC-0x80242528 (124B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void *fn_80241E38(void *, u32);
extern s32 fn_80240C80(s32);
extern void fn_8024144C(s32 *, s32, s32);
void fn_802424AC(Unk_C7387A53 *arg0, s32 arg1, s32 arg2) {
    u32 i;

    for (i = 0; i < *((u32 *)&arg0->unk0x30); i++) {
        void *ent = fn_80241E38(arg0, i);
        void *obj = *((void * *)&((Unk_9994C3F5 *)ent)->unk0x8);

        if (((CStruct *)obj)->unk0x4 & 2) {
            fn_8024144C(fn_80240C80(obj), arg1, arg2);
        }
    }
}
