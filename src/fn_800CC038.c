// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CC038-0x800CC078 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80030750(void *);
void fn_800CC038(Unk_C7387A53 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0) {
    void *node = *((void * *)&arg0->unk0x38);
    s32 f = ((CStruct *)node)->unk0x4;
    void *result = node;
    if (f == -1) {
        result = NULL;
    }
    if (result != NULL) {
        fn_80030750(result);
    }
}
