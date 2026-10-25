// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80216C4C-0x80216D10 (196B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_80173910(void *, void *);
void fn_8021C7EC(void *, void *);
s32 fn_8022986C(void *);
CScript *fn_8021D454(void *, void *, s32);
s32 fn_8021D4E8(s32, s32, s32);
s32 fn_80141FA4(s32);
extern s32 lbl_80305EAC;
extern char lbl_802A83F8[];
typedef struct { s32 unk0x0; s32 unk0x4; s32 unk0x8; s32 unk0xC; } Sp8_80216C4C;
void fn_80216C4C(Unk_9994C3F5 *arg0) {
    volatile Sp8_80216C4C sp8;
    Sp8_80216C4C *p;
    Sp8_80216C4C *q;
    s32 temp_r28;
    void *temp_r30;
    CScript *var_r31;
    q = &sp8;
    q->unk0x8 = (s32)lbl_802A83F8;
    temp_r28 = *(volatile s32 *)&lbl_80305EAC;
    q->unk0x4 = 0;
    var_r31 = fn_8021D454(arg0, q, 1);
    if (var_r31 != NULL) {
        do {
            temp_r30 = (void *)fn_8021D4E8((s32)arg0, (s32)&sp8, 1);
            if (((s32) var_r31->unk0x18 != 0) && ((fn_80141FA4(var_r31->unk0x18) != 0) || (fn_8022986C(var_r31) == 0))) {
                fn_80173910((void *)temp_r28, (void *)var_r31->unk0x18);
            }
            fn_8021C7EC(arg0, var_r31);
            var_r31 = temp_r30;
        } while (var_r31 != NULL);
    }
    p = &sp8;
    p->unk0x8 = (s32)lbl_802A83F8;
}
