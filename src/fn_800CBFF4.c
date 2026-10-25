// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CBFF4-0x800CC038 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8002FC8C(void *, s32, s32, s32, s32);
void fn_800CBFF4(Unk_C7387A53 *arg0, s32 a1, s32 a2, s32 a3, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    void *node = *((void * *)&arg0->unk0x38);
    s32 f = ((CStruct *)node)->unk0x4;
    void *result = node;
    if (f == -1) {
        result = NULL;
    }
    if (result != NULL) {
        fn_8002FC8C(result, a1, a2, a3, 0);
    }
}
