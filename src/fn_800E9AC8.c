// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800E9AC8-0x800E9B78 (176B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_8029AB8C[];
extern char lbl_8029ABA4[];
extern f32 lbl_8029AB7C;
extern f32 lbl_8029AB80;

void fn_8020D2E4(void *, s32);
void fn_8009F010(CScript *, s32, s32);
void fn_801EC3F0(void *, void *);
s32 fn_800DF004(s32, s32, void *);
s32 fn_800EB67C(s32, void *);

void fn_800E9AC8(Unk_2215E5E2 *arg0) {
    f32 temp_f13;
    f32 temp_f0;
    void *temp_r30;
    CStruct *temp_r9;

    fn_8020D2E4(arg0, 0);
    fn_8009F010(arg0->unk0xC, QB_SKATEREXITHANG, 0);
    fn_801EC3F0((void *)arg0->unk0x1858, lbl_8029ABA4);
    if ((s32) arg0->unk0x1940 != 0) {
        temp_r30 = (char *)arg0 + 0x1880;
        fn_800DF004(arg0->unk0x1848, (s32)lbl_8029AB8C, temp_r30);
        fn_800EB67C(arg0->unk0x1850, temp_r30);
    }
    temp_f13 = lbl_8029AB7C;
    temp_f0 = lbl_8029AB80;
    temp_r9 = (char *)arg0 + 0x7D8;
    *((f32 *)&arg0->unk0x7D8) = temp_f13;
    *((f32 *)&temp_r9->unk0x4) = temp_f13;
    *((f32 *)&temp_r9->unk0x8) = temp_f13;
    *((f32 *)&temp_r9->unk0xC) = temp_f0;
    *((f32 *)&arg0->unk0xB4) = *((f32 *)&arg0->unk0x1A04);
}
