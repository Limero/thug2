// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80098DF8-0x80098E38 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8037B7E8[];
void queue_front(Unk_C7387A53 *);
void fn_80098DF8(s32 arg0, s32 arg1) {
    if ((arg1 == 0xFFFF) && (arg0 != 0)) {
        queue_front((s32)lbl_8037B7E8);
    }
}
