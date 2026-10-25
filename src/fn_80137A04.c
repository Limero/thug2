// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80137A04-0x80137A34 (48B). Byte-identical.
#include "types.h"
#include "structs.h"
void strcpy(s32);
void fn_80137A04(Unk_6F823D41 *arg0, s8 arg1) {
    if (arg1 == 0) {
        arg0->unk0x22C8 = arg1;
    }
    strcpy((char *)arg0 + 0x22C8);
}
