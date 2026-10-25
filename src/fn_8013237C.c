// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013237C-0x801323CC (80B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void fn_801322F8(Unk_B1CD4D9E *);
void fn_8013237C(Unk_90195219 *arg0) {
    if (((s32) arg0->unk0x144 != 0) ||
        ((arg0->unk0x4 & 0x7F0000) != 0) ||
        ((s32) arg0->unk0x1E8 != 0) ||
        ((s32) arg0->unk0x1F4 != 0)) {
        fn_801322F8(arg0);
    }
}
