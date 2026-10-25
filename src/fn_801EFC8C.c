// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801EFC8C-0x801EFD00 (116B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802ADE98[];
void fn_801A38DC(Unk_FFAD6788 *, s32);
void fn_8009F558(Unk_C8FEE62D *, s32);
void fn_801EFC8C(CScript *arg0, s32 arg1) {
    *((void * *)&arg0->unk0x18) = lbl_802ADE98;
    fn_801A38DC((char *)arg0 + 0x178, 2);
    fn_801A38DC((char *)arg0 + 0x108, 2);
    fn_801A38DC((char *)arg0 + 0x98, 2);
    fn_801A38DC((char *)arg0 + 0x28, 2);
    fn_8009F558(arg0, arg1);
}
