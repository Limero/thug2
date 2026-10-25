// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801379D4-0x80137A04 (48B). Byte-identical.
#include "types.h"
#include "structs.h"
void strcpy(s32);
void fn_801379D4(Unk_F3F04A60 *arg0, s8 arg1) {
    if (arg1 == 0) {
        arg0->unk0x22A8 = arg1;
    }
    strcpy((char *)arg0 + 0x22A8);
}
