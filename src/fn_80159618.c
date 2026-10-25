// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80159618-0x801596D4 (188B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Identification: ScriptSkaterGetScoreInfo — writes the skater's score info
// (score + score*multiplier) into the script's array argument.
// Suggested rename: keep ScriptSkaterGetScoreInfo.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_801568F4(void);
s32 fn_801813F0(CStruct *);
void AddInteger(CStruct *, s32, s32);

bool ScriptSkaterGetScoreInfo(void *arg0, CScript *arg1) {
    Unk_9AA07378 *temp_r3;

    temp_r3 = (void *)fn_801568F4();
    AddInteger(arg1->unk0x18, QB_SCOREPOT,
        (f32)(f64)(s32)temp_r3->unk0x18
        * *((f32 *)&temp_r3->unk0x6C));
    AddInteger(arg1->unk0x18, QB_TOTALSCORE,
        fn_801813F0(temp_r3));
    AddInteger(arg1->unk0x18, QB_LASTSCORELANDED,
        temp_r3->unk0x24);
    return true;
}
