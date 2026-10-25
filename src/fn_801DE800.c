// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801DE800-0x801DE8BC (188B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80303150[];
s32 Tmr_GetTime(void);
s32 fn_800AA074(CScript *);
s32 fn_8009F010(s32, s32, s32);
bool fn_801DE800(Unk_9AE08789 *arg0) {
    s32 field_15a0;
    s32 temp_r29;
    s32 temp_r30;
    CStruct *temp_r28;
    CStruct *temp_r30_2;
    CStruct *temp_r9;

    field_15a0 = arg0->unk0x15A0;
    temp_r9 = arg0->unk0x15BC + 0x24;
    if ((s32) temp_r9->unk0x4 != 0) {
        temp_r28 = field_15a0 + 0x1FC;
        temp_r29 = temp_r28->unk0x4;
        if (temp_r29 == 0) {
            temp_r30 = temp_r9->unk0x8;
            arg0->unk0x3F0 = (s32) ((*(s32 *)&lbl_80303150 + Tmr_GetTime()) - temp_r30);
            temp_r30_2 = arg0->unk0x15BC + 0x24;
            if ((s32) temp_r30_2->unk0x4 != 0) {
                temp_r30_2->unk0x4 = temp_r29;
                temp_r30_2->unk0x8 = (s32) (*(s32 *)&lbl_80303150 + Tmr_GetTime());
            }
            fn_800AA074(temp_r28);
            fn_8009F010(arg0->unk0xC, QB_OLLIED, 0);
            return true;
        }
    }
    return false;
}
