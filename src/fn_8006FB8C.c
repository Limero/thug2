// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006FB8C-0x8006FBCC (64B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8005F984(s32, s32);
void fn_8006FB50(Unk_5E1C040A *, s32);
void fn_8006FB8C(CStruct *arg0, s32 arg1) {
    arg0->unk0x4 = arg1;
    fn_8006FB50(arg0, 0);
    fn_8005F984(arg0->unk0x4, 1);
}
