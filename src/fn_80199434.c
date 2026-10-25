// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80199434-0x80199490 (92B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
s32 fn_8012EE64(Unk_069CE08E *, s32);
extern char lbl_802AA850[];
void fn_80199434(CStruct *arg0, s32 arg1) {
    s32 field;

    field = arg0->unk0x4;
    arg0->unk0x10 = (s32)lbl_802AA850;
    if (field != 0) {
        fn_8012EE64(field, 3);
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
