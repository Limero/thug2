// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CC314-0x800CC358 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8002FB24(Unk_C7387A53 *);
s32 fn_800CC314(Unk_C7387A53 *arg0) {
    void *node = *((void * *)&arg0->unk0x38);
    if (((CStruct *)node)->unk0x4 == -1) {
        node = NULL;
    }
    if (node != NULL) {
        return fn_8002FB24(node);
    }
    return 0;
}
