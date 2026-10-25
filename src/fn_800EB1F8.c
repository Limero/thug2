// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800EB1F8-0x800EB268 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8020D2E4(s32, s32);
extern char lbl_8029ACA0[];
extern char lbl_8029AC7C[];
void fn_801EC3F0(Unk_83A1E37F *, void *);
s32 fn_800DF004(s32, s32, void *);
s32 fn_800EB67C(Unk_C8FEE62D *, void *);
void fn_800EB1F8(Unk_2215E5E2 *arg0) {
    void *temp_r30;
    fn_8020D2E4(arg0, 0);
    fn_801EC3F0(arg0->unk0x1858, (s32)lbl_8029ACA0);
    if ((s32) arg0->unk0x1940 != 0) {
        temp_r30 = (char *)arg0 + 0x1880;
        fn_800DF004(arg0->unk0x1848, (s32)lbl_8029AC7C, temp_r30);
        fn_800EB67C(arg0->unk0x1850, temp_r30);
    }
}
