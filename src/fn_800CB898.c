// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CB898-0x800CB914 (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 AddChecksum(void *, void *, void *);
s32 fn_80128E34(s32, s32, s32, s32);
s32 fn_800CBEC0(Unk_C7387A53 *arg0, s32 arg1);
bool fn_800CB898(Unk_C7387A53 *arg0, s32 arg1, CStruct *arg2, CScript *arg3) {
    s32 sp8;

    sp8 = 0;
    fn_80128E34(arg2, QB_SUBSETID, &sp8, 0);
    if (fn_800CBEC0(arg0, sp8) != 0) {
        AddChecksum(arg3->unk0x18, 0, QB_UNKNOWN_0xC7C6228C);
        return true;
    }
    return false;
}
