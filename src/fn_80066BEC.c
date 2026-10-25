// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80066BEC-0x80066C8C (160B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_80062BC0(void *, s32);
void fn_80062DBC(Unk_EDE83D0E *, void *);
extern char lbl_802942B8[];
extern char lbl_802942D0[];
void fn_80066BEC(Unk_DCEB657B *arg0, s32 arg1) {
    void *temp_r10;
    void *var_r31;

    temp_r10 = arg0->unk0x100;
    arg0->unk0x20 = (s32)lbl_802942B8;
    arg0->unk0x8 = (s32)lbl_802942D0;
    if (temp_r10 != NULL) {
        var_r31 = temp_r10 + (*(s32 *)((char *)temp_r10 - 0x8) * 0x30);
        if (temp_r10 != var_r31) {
            do {
                var_r31 -= 0x30;
                fn_80062BC0(var_r31, 0);
            } while ( arg0->unk0x100 != var_r31);
        }
        Mem_Free2(arg0->unk0x100 - 8);
        arg0->unk0x100 = NULL;
    }
    fn_80062DBC(arg0, arg1);
}
