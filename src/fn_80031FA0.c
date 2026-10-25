// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80031FA0-0x80031FC4 (36B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

void fn_80031FA0(Unk_C8FEE62D *arg0, s32 arg1) {
    u32 value = arg0->unk0x64 & 0xDFFFFFFF;
    u32 result = value;

    __asm__("" : "+r"(result));
    arg0->unk0x64 = value;
    if (arg1 != 0) {
        result |= 0x20000000;
    }
    arg0->unk0x64 = result;
}
