// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000A59C-0x8000A5D4 (56B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80009F64(Unk_DB0E2BAB *);
void fn_8000A59C(Unk_C7387A53 *arg0) {
    if ((s32) arg0->unk0x44 != 0) {
        fn_8000A5D4();
        return;
    }
    fn_80009F64(arg0->unk0x40);
}
