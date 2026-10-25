// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D6490-0x800D64DC (76B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 Mem_NewZero(s32);
void *fn_800A84B4(Unk_AAECB680 *, s32);
void fn_800D6490(CScript *arg0, s32 arg1) {
    if (arg0->unk0x204 == 0) {
        arg0->unk0x204 = fn_800A84B4(Mem_NewZero(0xF8), arg1);
    }
}
