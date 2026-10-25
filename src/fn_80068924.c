// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80068924-0x80068954 (48B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80068924(s32 arg0, void *arg1) {
    CStruct *temp_r9;

    if (arg1 != 0) {
        temp_r9 = (char *)arg1 + 0xC;
        *(void **)(*((void * *)&temp_r9->unk0x10) + 0xC) = *((void * *)&temp_r9->unk0xC);
        *(void **)(*((void * *)&temp_r9->unk0xC) + 0x10) = *((void * *)&temp_r9->unk0x10);
        *((void * *)&temp_r9->unk0xC) = temp_r9;
        *((void * *)&temp_r9->unk0x10) = temp_r9;
    }
}