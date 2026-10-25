// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80206AD4-0x80206B50 (124B). Byte-identical.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8009F53C(void);
void fn_801A98F4(Unk_03123917 *);
void fn_80206C48(Unk_CF8B1206 *);
extern char lbl_802AF3D8[];
void *fn_80206AD4(Unk_709BED05 *arg0) {
    fn_8009F53C();
    arg0->unk0x18 = (s32)lbl_802AF3D8;
    fn_801A98F4((char *)arg0 + 0x1404);
    arg0->unk0x38 = 0;
    arg0->unk0x4 = QB_TRICK;
    arg0->unk0xA6C = 0;
    arg0->unk0x20 = 0;
    arg0->unk0x24 = 0;
    arg0->unk0x28 = 0;
    arg0->unk0x2C = 0;
    arg0->unk0x30 = 0;
    arg0->unk0x34 = 0;
    fn_80206C48(arg0);
    return arg0;
}
