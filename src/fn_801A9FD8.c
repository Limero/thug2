// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A9FD8-0x801AA0B8 (224B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802ABA64;
extern f32 lbl_802ABA68;
extern f32 lbl_802ABA6C;
extern f32 lbl_802ABA70;
extern void fn_801A0DA8(Unk_6A70655D *);
extern void fn_801A0E48(Unk_6A70655D *, CStruct *);
extern s32 GetChecksum_3(Unk_6A70655D *, s32);
extern void fn_800D6490(CScript *, s32);
extern s32 fn_800D64DC(CScript *);
extern s32 Script_RunScript(s32, s32, s32, s32, s32);
extern void fn_800B61F4(CScript *);
void fn_801A9FD8(Unk_6A70655D * arg0, CStruct *arg1) {
    Unk_EFE13F4E *temp_r9;
    Unk_C7387A53 *temp_r30;
    f32 temp_f13;
    f32 temp_f12;
    f32 temp_f0;

    fn_801A0DA8(arg0);
    fn_801A0E48(arg0, arg1);
    temp_r30 = GetChecksum_3(arg0, QB_MOTION);
    temp_f13 = lbl_802ABA64;
    temp_f12 = lbl_802ABA68;
    temp_f0 = lbl_802ABA6C;
    *((f32 *)&temp_r30->unk0x30) = temp_f13;
    *((f32 *)&temp_r30->unk0x28) = temp_f12;
    *((f32 *)&temp_r30->unk0x2C) = temp_f0;
    temp_r30->unk0x78 = 0;
    fn_800D6490(temp_r30, arg0);
    *(f32 *)((char *)fn_800D64DC(temp_r30) + (s32)0xA0) = lbl_802ABA70;
    Script_RunScript(QB_CAR_ADD_COMPONENTS, arg1, arg0, 0, 0);
    temp_r9 = *((void * *)&arg0->unk0x8);
    ((void (*)(void *))(*((void * *)&temp_r9->unk0x4C)))((char *)arg0 + temp_r9->unk0x48);
    fn_800B61F4(GetChecksum_3(arg0, QB_MODEL));
}
