// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FC678-0x801FC728 (176B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
extern s32 lbl_80305F80;
void fn_8010794C(Unk_C7387A53 *);
void fn_80107A80(Unk_C5652918 *, s32, s32);
void fn_80107B20(Unk_E9DCA07D *, s32, void *);
void CObject_RemoveRefLink(CStruct *, CStruct *);
s32 fn_801FC5DC(Unk_6BB06288 *);
s32 fn_801FC678(Unk_EA529D06 *arg0, Unk_EA529D06 *arg1) {
    s32 sp8[47];
    s32 zero;
    s32 ret;
    Unk_D69BF764 *p;

    zero = 0;
    lbl_80305F80 = zero;
    fn_8010794C(sp8);
    p = (char *)sp8;
    *(__ps_t *)(char *)sp8 = arg0->unk0x0;
    ((Unk_BE223D5D *)sp8)->unk0x10 = arg1->unk0x0;
    p->unk0x8 = arg0->unk0x8;
    ((Unk_BE223D5D *)sp8)->unk0x18 = arg1->unk0x8;
    fn_80107A80(p, 0, 0x50);
    p->unk0x20 = (s32)fn_801FC5DC;
    fn_80107B20(p, 1, 0);
    {
        s32 *op = (s32 *)((char *)sp8 + 0xa8);
        ret = lbl_80305F80;
        if (*op != 0) {
            CObject_RemoveRefLink(*op, op);
            *op = zero;
        }
    }
    return ret;
}
