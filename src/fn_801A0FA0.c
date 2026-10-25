// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A0FA0-0x801A0FF0 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802AB1D0[];
extern void fn_8002DD1C(Unk_C8FEE62D *, s32);
extern void fn_800AB15C(Unk_C8FEE62D *, s32);
void fn_801A0FA0(Unk_C8FEE62D *arg0, s32 arg1) {
    arg0->unk0x14 = (s32)lbl_802AB1D0;
    fn_8002DD1C((char *)arg0 + 0x40, 2);
    fn_800AB15C(arg0, arg1);
}
