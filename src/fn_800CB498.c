// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CB498-0x800CB4D8 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8002FB00(Unk_132A52FF *);
void fn_800CB498(Unk_C7387A53 *arg0) {
    void *node = *((void * *)&arg0->unk0x38);
    s32 f = ((CStruct *)node)->unk0x4;
    void *result = node;
    if (f == -1) {
        result = NULL;
    }
    if (result != NULL) {
        fn_8002FB00(result);
    }
}
