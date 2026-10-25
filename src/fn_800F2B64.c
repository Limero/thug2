// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F2B64-0x800F2BA8 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
//
// Identification: registry-keyed lookup wrapper: resolves the object id
// arg1 through Script_GenerateCRC and forwards (arg0, id, arg2) to the registry
// store fn_800F2AD8 (base registry at lbl_80301B48). Suggested rename:
// RegistrySetByIdResolved.
#include "types.h"
#include "structs.h"
s32 fn_800F2AD8(void *, void *, void *);
s32 Script_GenerateCRC(void *);
void fn_800F2B64(Unk_C7387A53 *arg0, void *arg1, void *arg2) {
    fn_800F2AD8(arg0, Script_GenerateCRC(arg1), arg2);
}
