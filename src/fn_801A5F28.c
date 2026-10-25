// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A5F28-0x801A5FF8 (208B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void *lbl_802FFE98;
void fn_8000F2F8(Unk_9F352E7C *, s32);
void fn_8000F320(Unk_F12C5E01 *);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_801A65EC(Unk_C8FEE62D *, s32 *, s32 *);
s32 fn_801A572C(s32);
s32 fn_801A56F4(s32);
s32 fn_801A513C(s32, s32, CStruct *);
void fn_801A5CF0(void *, s32);
void fn_801A5F28(Unk_9994C3F5 *arg0, CStruct *arg1) {
    Unk_B0F19D72 *mgr;
    u32 count;
    u32 i;
    s32 sp8;
    s32 spC;
    s32 out;
    s32 entry;

    mgr = lbl_802FFE98;
    fn_8000F2F8(mgr, mgr->unk0x5F8);
    count = *((u32 *)&arg0->unk0x8);
    for (i = 0; i < count; i++) {
        sp8 = i;
        if (fn_801A572C(entry = fn_801A65EC((char *)arg0 + 4, &sp8, &spC)) != 0) {
            fn_801A513C(entry, fn_801A56F4(entry), arg1);
        }
    }
    out = 0;
    GetChecksum_2(arg1, QB_CURRENTSKATER, &out, 0);
    fn_801A5CF0(arg0, out);
    fn_8000F320(lbl_802FFE98);
}
