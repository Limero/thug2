// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80255F18-0x80255F5C (68B). Byte-identical.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
extern s32 lbl_803CA340;
static void fn_802555BC();
static void fn_8024EBD8(s32 heap, void *ptr);

void fn_80255F18(Unk_C7387A53 *arg0) {
    if (arg0->unk0x30 != 0) {
        fn_802555BC();
        fn_8024EBD8((
            {
                s32 heap;
                heap = lbl_803CA340;
                heap;
            }),
            arg0);
    }
}
