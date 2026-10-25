// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A14E0-0x800A1538 (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetChecksum_3(Unk_6A70655D *, s32);
s32 fn_800A14E0(Unk_6A70655D *arg0, CStruct *arg1) {
    s32 sp8;

    GetChecksum_2(arg1, 0, &sp8, 1);
    return (GetChecksum_3(arg0, sp8) != 0);
}