// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80070638-0x800706AC (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetInteger(CStruct *, s32, s32 *, s32);
bool fn_80070638(Unk_B8B99A6B *arg0, CStruct *arg1) {
    Unk_E01B0030 sp8;
    Unk_E01B0030 *p;

    *((u32 *)&sp8) = QB_UNKNOWN_0x80808080;
    p = &sp8;
    GetInteger(arg1, 0, (s32 *)p, 0);
    *((u8 *)((char *)arg0 + 0x24)) = (u8) p->unk0x3;
    *((s8 *)((char *)arg0 + 0x25)) = (s8) (*((u32 *)p) >> 8U);
    *((s8 *)((char *)arg0 + 0x26)) = (s8) (*((u32 *)p) >> 0x10U);
    *((s8 *)((char *)arg0 + 0x27)) = (s8) (*((u32 *)p) >> 0x18U);
    return true;
}
