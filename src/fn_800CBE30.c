// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CBE30-0x800CBE7C (76B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80299450[];
f32 fn_8002F700(void *);
f32 fn_800CBE30(Unk_C7387A53 *arg0, s32 arg1) {
    void *node = *((void * *)&arg0->unk0x38);
    s32 f = ((CStruct *)node)->unk0x4;
    void *result = node;
    if (f == -1) {
        result = NULL;
    }
    if (result != NULL) {
        return fn_8002F700(result);
    }
    return *(f32 *)lbl_80299450;
}
