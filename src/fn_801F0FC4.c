// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F0FC4-0x801F1038 (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_800CC138(void *, void *, void *, void *, void *);
#include "qb_constants.h"
#include "structs.h"
s32 fn_8021B55C(s32, s32);
s32 GetChecksum_3(void *, s32);
extern char lbl_80305F9C[];
void fn_801F0FC4(Unk_C7387A53 *arg0) {
    s32 *temp_r28;
    s32 temp_r29;
    s32 temp_r30;
    CScript *temp_r9;

    temp_r28 = (s32 *)fn_8021B55C(*(s32 *)&lbl_80305F9C, *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0xC) + 0x2E8));
    temp_r9 = arg0->unk0xC;
    temp_r29 = arg0->unk0x2C;
    temp_r30 = temp_r9->unk0x18;
    fn_800CC138(temp_r29, temp_r30, *(s32 *)((char *)(GetChecksum_3(temp_r9, QB_SKATERSTATE)) + 0x34), *((s32 *)temp_r28), 1);
}
