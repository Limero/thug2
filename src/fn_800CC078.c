// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CC078-0x800CC0B8 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_800306D0(Unk_C7387A53 *);
void fn_800CC078(Unk_C7387A53 *arg0) {
    void *node = *((void * *)&arg0->unk0x38);
    s32 f = ((CStruct *)node)->unk0x4;
    void *result = node;
    if (f == -1) {
        result = NULL;
    }
    if (result != NULL) {
        fn_800306D0(result);
    }
}
