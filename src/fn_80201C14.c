// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80201C14-0x80201C80 (108B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetChecksum_3(Unk_6A70655D * arg0, s32 arg1);
void fn_80201C14(Unk_59E38960 *arg0, Unk_6A70655D *arg1) {
    arg0->unk0xA9C = arg1;
    if (arg1 == 0) {
        arg0->unk0xAA0 = 0;
        arg0->unk0xAA4 = 0;
    } else {
        arg0->unk0xAA0 = GetChecksum_3(arg1, QB_SKATERSTATE);
        arg0->unk0xAA4 = GetChecksum_3(arg0->unk0xA9C, QB_SKATERPHYSICSCONTROL);
    }
}
