// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80034E44-0x80034E74 (48B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Sets arg0->unk0x14 to the address of lbl_80291E58, then calls
// fn_80033560(arg0) — a 1-arg call (r4 untouched at the call site).
// Suggested rename: SetNameAndNotify
#include "types.h"
#include "structs.h"
extern char lbl_80291E58[];
extern void fn_80033560(void *);
void fn_80034E44(Unk_C8FEE62D *arg0) {
    arg0->unk0x14 = (s32)lbl_80291E58;
    fn_80033560(arg0);
}