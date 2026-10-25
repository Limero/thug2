// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80241EC0-0x80241F00 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80241EC0(Unk_C7387A53 *arg0, u32 arg1) {
    if ((arg1 >= (u32) *((u32 *)&arg0->unk0x30)) || ((s32) arg1 < 0)) {
        return 0;
    }
    return *(s32 *)((char *)(fn_80241E38()) + (s32)0x8);
}
