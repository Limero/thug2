// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801966DC-0x80196740 (100B). Byte-identical.
#include "types.h"
#include "structs.h"

void fn_80196DA4(void *);
s32 fn_8018C080(Unk_672A1C0D *);

s32 fn_801966DC(Unk_C041285A *arg0) {
    Unk_89391A04 *temp_r9;

    arg0->unk0x540 = 0;
    temp_r9 = arg0->unk0x14;
    if (temp_r9->unk0x24(
            (char *)arg0 + temp_r9->unk0x20) == 0) {
        fn_80196DA4(arg0);
        return fn_8018C080((s32)arg0);
    }
    return 0;
}
