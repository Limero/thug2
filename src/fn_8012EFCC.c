// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012EFCC-0x8012F024 (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_800A5B64(s32, s32, s32);
extern char lbl_80301A78[];
void fn_8012EFCC(Unk_FFAD6788 *arg0, s32 arg1) {
    arg0->unk0xA8 = arg1;
    arg0->unk0xA4 = 3;
    if (arg1 != 0) {
        fn_800A5B64(*(s32 *)&lbl_80301A78, arg1, arg0);
        arg0->unk0xCC = (s32) (arg0->unk0xCC | QB_UNKNOWN_0x08000000);
    }
}
