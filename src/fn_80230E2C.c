// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80230E2C-0x80230E8C (96B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802B0A88[];
extern char lbl_802B0AA8[];
void fn_80238920(void);
void fn_800A3C50(Unk_DB0E2BAB *, s32);
void fn_8009C8A8(Unk_C8FEE62D *, s32);
void fn_80230E2C(Unk_C8FEE62D *arg0, s32 arg1) {
    s32 o = arg0;
    ((Unk_C8FEE62D *)o)->unk0x30 = (s32)lbl_802B0A88;
    ((Unk_C8FEE62D *)o)->unk0x14 = (s32)lbl_802B0AA8;
    fn_80238920();
    fn_800A3C50(o + 0x18, 0);
    fn_8009C8A8(arg0, arg1);
}
