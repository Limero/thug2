// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C1250-0x801C12A4 (84B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_801C1A54(Unk_31DE137E * arg0);
void fn_80119640(void *arg0, s32 arg1);
void fn_8009F558(Unk_C8FEE62D * arg0, s32 arg1);
extern char lbl_802AC7C8[];
void fn_801C1250(CScript *arg0, s32 arg1) {
    arg0->unk0x18 = (s32)lbl_802AC7C8;
    fn_801C1A54(arg0);
    fn_80119640((char *)arg0 + 0x2C, 2);
    fn_8009F558(arg0, arg1);
}
