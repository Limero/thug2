// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009A4D8-0x8009A524 (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_80297610[];
void fn_8009A6C0(s32 **);
void fn_8009A4D8(CStruct *arg0, s32 arg1) {
    arg0->unk0x10 = (s32)lbl_80297610;
    fn_8009A6C0((s32 **)arg0);
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
