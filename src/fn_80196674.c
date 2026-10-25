// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80196674-0x801966DC (104B). Byte-identical.
#include "types.h"
#include "structs.h"

extern char lbl_802AA668[];

s32 fn_80126A30(Unk_5AA7B5D7 *);
s32 fn_80128FFC(Unk_F8A5095F *);
s32 fn_80128FB4(Unk_F8A5095F *, s32);
s32 fn_8018BED8(Unk_DB0E2BAB *, s32);

void fn_80196674(Unk_5BB06F5F *arg0, s32 arg1) {
    arg0->unk0x14 = (s32)lbl_802AA668;
    fn_80126A30(arg0->unk0x53C);
    fn_80128FFC(arg0->unk0x53C);
    if (arg0->unk0x53C != 0) {
        fn_80128FB4(arg0->unk0x53C, 3);
    }
    fn_8018BED8((s32)arg0, arg1);
}
