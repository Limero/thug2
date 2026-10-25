// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800132A4-0x800132F8 (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8000E104(s32);
s32 fn_800132A4(CStruct *arg0) {
    if (arg0->unk0x34 != 0) {
        *(volatile s32 *)&arg0->unk0x0 = fn_8000E104(arg0->unk0x34);
        return arg0->unk0x0;
    }
    do {
    } while (*(volatile s32 *)&arg0->unk0x2C < 0);
    return *(volatile s32 *)&arg0->unk0x2C;
}
