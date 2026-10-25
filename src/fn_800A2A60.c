// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A2A60-0x800A2B0C (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_80290628;
extern char lbl_802FFE98[];
extern s32 lbl_80301A44;
extern s32 lbl_80301A5C;
extern void *lbl_80301A60;
extern char lbl_80297D7C[];
void *Mem_NewZero(s32);
#include "qb_constants.h"
#include "structs.h"
void Script_GetInteger(void *, void *);
s32 fn_8001094C(void *, s32);
void * fn_8000F95C(void *a, void *b, s32, void *c);
bool fn_800A2A60(Unk_C8FEE62D *arg0) {
    s32 temp_r3;
    s32 *slot;
    Unk_C7387A53 *temp_r3_2;

    fn_800A2B0C();
    if (arg0 != 0) {
        slot = &lbl_80301A5C;
        temp_r3 = fn_8001094C(Mem_NewZero(0x1C), arg0);
        *slot = temp_r3;
        temp_r3_2 = fn_8000F95C(*(s32 *)(s32)lbl_802FFE98, temp_r3, 1, lbl_80297D7C);
        lbl_80301A60 = temp_r3_2;
        temp_r3_2->unk0x84 = 1;
        temp_r3_2->unk0x88 = (s32) (lbl_80301A44 - lbl_80290628);
        Script_GetInteger(QB_ENABLE_COIM_OBJECT_DEBUG, 0);
    }
    return false;
}
