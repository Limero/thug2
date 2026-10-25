// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A8794-0x801A87F8 (100B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_802AB998[];
void fn_801A9528(CStruct *);
void fn_801A9BB8(CStruct *, s32);
void fn_801A8794(CStruct * arg0, s32 arg1) {
    arg0->unk0x3C = (s32)lbl_802AB998;
    fn_801A9528(arg0);
    fn_801A9BB8((char *)arg0 + 0x20, 2);
    fn_801A9BB8((char *)arg0 + 8, 2);
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
