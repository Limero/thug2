// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80143AF4-0x80143B7C (136B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_801C26D8(Unk_C7387A53 *);
s32 GetChecksum_3(Unk_6A70655D *, s32);
void fn_801F0734(Unk_C7387A53 *);
void fn_80203E10(s32);
void fn_800CBCB4(s32);
void fn_8012EE64(Unk_069CE08E *, s32);
void fn_80143AF4(Unk_3DDEEB97 *arg0) {
    if ((s32) arg0->unk0xC8 != 0) {
        fn_801C26D8(arg0->unk0x29C);
        fn_801F0734((void *)GetChecksum_3((s32)arg0, QB_SKATERBALANCETRICK));
    }
    fn_80203E10(GetChecksum_3((s32)arg0, QB_SPECIALITEM));
    fn_800CBCB4(arg0->unk0x278);
    if ((s32) arg0->unk0x14 != 0) {
        fn_8012EE64(arg0->unk0x14, 3);
        arg0->unk0x14 = 0;
    }
}
