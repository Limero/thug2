// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802448E4-0x80244924 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8023F87C(void *);
void fn_80244924(Unk_5AA7B5D7 *);
void fn_802448E4(Unk_5AA7B5D7 *arg0, s32 arg1) {
    fn_80244924(arg0);
    if (arg1 & 1) {
        fn_8023F87C(arg0);
    }
}
