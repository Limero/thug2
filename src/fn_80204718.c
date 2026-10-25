// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80204718-0x80204748 (48B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// IDENTIFIED (2026-09-01): object init helper, minimal variant of the
// fn_80204684 default-object initializer family — stores the shared data
// blob pointer lbl_802AF070 at obj+0x18 then calls the family post-init
// helper fn_8009F558(obj). Suggested rename: ObjSetDefaultData (or
// InitObject_80204718) — no symbol.txt name exists yet.
#include "types.h"
#include "structs.h"
extern char lbl_802AF070[];
void fn_8009F558(void *);
void fn_80204718(CScript *arg0) {
    arg0->unk0x18 = (s32)lbl_802AF070;
    fn_8009F558(arg0);
}
