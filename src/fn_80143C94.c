// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80143C94-0x80143D28 (148B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305F9C;
s32 fn_80141FA4(Unk_5FCDF30E *);
s32 fn_8021B55C(s32, s32);
s32 GetChecksum_3(Unk_6A70655D *, s32);
void fn_801F0DC8(s32, s32, s32, s32, s32);
void fn_801F0FC4(Unk_C7387A53 *);
void fn_800B33EC(CScript *, Unk_C8FEE62D *, s32, s32);
void fn_800CBCB4(s32);
void fn_80143C94(Unk_9D99273B *arg0) {
    s32 *temp_r28;
    s32 temp_r29;
    s32 temp_r3;

    temp_r29 = lbl_80305F9C;
    temp_r28 = (s32 *)fn_8021B55C(temp_r29, fn_80141FA4(arg0));
    temp_r3 = GetChecksum_3((s32)arg0, QB_SKATERFLIPANDROTATE);
    fn_801F0DC8(temp_r3, arg0->unk0x18, 0, *temp_r28, arg0->unk0xC8);
    fn_801F0FC4(temp_r3);
    fn_800B33EC(arg0->unk0x27C, QB_BOARD, 0, arg0->unk0xC8);
    fn_800CBCB4(arg0->unk0x278);
}
