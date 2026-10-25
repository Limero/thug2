// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020432C-0x80204378 (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// ID: QB script callback — loads the global QB key at lbl_80305EAC,
// resolves it via fn_801745B4, registers it as QB_TRIGGER on the
// script object; returns the resource id (0 if unresolvable).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305EAC[];

s32 fn_8020432C(Unk_C7387A53 *arg0) {
    extern s32 fn_801745B4(s32);
    extern s32 GetChecksum_3(Unk_6A70655D *, s32);
    s32 resource = fn_801745B4(*(s32 *)lbl_80305EAC);
    if (resource != 0) {
        resource = GetChecksum_3(resource, QB_TRIGGER);
        arg0->unk0x28 = resource;
    }
    return resource;
}