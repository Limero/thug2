// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CBFB4-0x800CBFF4 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80030ADC(void *);
void fn_800CBFB4(Unk_C7387A53 *arg0) {
    void *node = *((void * *)&arg0->unk0x38);
    s32 f = ((CStruct *)node)->unk0x4;
    void *result = node;
    if (f == -1) {
        result = NULL;
    }
    if (result != NULL) {
        fn_80030ADC(result);
    }
}
