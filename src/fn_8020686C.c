// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020686C-0x802068B4 (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// ID: QB script callback — resolves the global QB_CAG_WORKSPACE key at
// lbl_80366478 via fn_8005CF80 and binds the texture to the object's
// unk0x20 handle via fn_8005C070.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80366478[];

void fn_8020686C(Unk_C7387A53 *arg0) {
    extern s32 fn_8005CF80(Unk_9994C3F5 *, s32);
    extern void fn_8005C070(s32, s32);
    s32 texture = fn_8005CF80(*(s32 *)lbl_80366478, QB_CAG_WORKSPACE);
    fn_8005C070(arg0->unk0x20, texture);
}