// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F1388-0x801F13D0 (72B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void fn_8009F010(s32, s32, s32);
void fn_801F1388(Unk_C7387A53 *arg0, s32 arg1) {
    if (arg1 != (s32) arg0->unk0x20) {
        arg0->unk0x20 = arg1;
        fn_8009F010(arg0->unk0xC, QB_ONSKATERPHYSICSSTATECHANGE, 0);
    }
}
