// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004C900-0x8004C9C0 (192B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-expensive-optimizations
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
// FLAG: -fno-expensive-optimizations
// UPDATED 2026-09-24: modeled the factory output as its three-word handle and
// used the call-site void ABI; independent masked verification is 100% (192B).
void AddChecksum(CStruct *arg0, s32 arg1, s32 arg2);
extern s32 lbl_80297F18;
extern char lbl_80300434[];
void CObject_RemoveRefLink(CStruct *, CStruct *);
void fn_8004A800(CStruct *arg0, Unk_C7387A53 *arg1, s32 arg2, s32 arg3, CStruct *arg4);
bool ScriptCreateScreenElement(CStruct *arg0, CScript *arg1) {
    s32 sp1C;
    s32 sp18;
    struct { void *f0; s32 f4; s32 f8; } sp8;
    s32 temp_r0;

    GetChecksum_2(arg0, QB_TYPE, &sp18, NULL);
    sp1C = lbl_80297F18;
    GetChecksum_2(arg0, QB_ID, &sp1C, 0);
    fn_8004A800(&sp8, *(s32 *)&lbl_80300434, sp18, sp1C, arg0);
    temp_r0 = ((CScript *)sp8.f0)->unk0x18;
    sp1C = temp_r0;
    AddChecksum(arg1->unk0x18, QB_ID, temp_r0);
    if (sp8.f0 != NULL) {
        CObject_RemoveRefLink(sp8.f0, (CStruct *)&sp8);
        sp8.f0 = NULL;
    }
    return true;
}
