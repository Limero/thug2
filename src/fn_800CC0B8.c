// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CC0B8-0x800CC0F8 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8002FFA8(void *);
void fn_800CC0B8(Unk_C7387A53 *arg0, s32 arg1, f32 farg0) {
    void *node = *((void * *)&arg0->unk0x38);
    s32 f = ((CStruct *)node)->unk0x4;
    void *result = node;
    if (f == -1) {
        result = NULL;
    }
    if (result != NULL) {
        fn_8002FFA8(result);
    }
}
