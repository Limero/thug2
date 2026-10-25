// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80145058-0x801450B8 (96B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_3(Unk_6A70655D *, s32);
void fn_801C1A54(Unk_31DE137E *);
void fn_800DDCB8(Unk_C8FEE62D *);
void fn_8009F9AC(Unk_6A70655D *, s32);
void fn_80145058(Unk_9D99273B *arg0) {
    if (arg0->unk0xC8 != 0) {
        fn_801C1A54(GetChecksum_3((s32)arg0, QB_SKATERLOOPINGSOUND));
    }
    fn_800DDCB8(arg0->unk0x280);
    fn_8009F9AC(arg0, 1);
    arg0->unk0x2F0 = 0;
}
