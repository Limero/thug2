// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023DDCC-0x8023DDFC (48B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void fn_80244E48(Unk_09BB4394 * arg0, CStruct * arg1);
void fn_8023DDCC(Unk_31DE137E *arg0) {
    void *temp_r3;

    temp_r3 = *((void * *)&arg0->unk0x64);
    if (temp_r3 != NULL) {
        fn_80244E48(temp_r3, arg0);
    }
}
