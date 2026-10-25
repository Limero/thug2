// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80219508-0x80219580 (120B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_802201A4(CScript * arg0);
extern s32 fn_800145AC(void);
extern void fn_80009C00(CStruct * arg0);
extern s32 Script_RunScript(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void fn_80219508(Unk_C7387A53 *arg0) {
    Unk_BF863306 *temp_r31;

    temp_r31 = arg0->unk0x20;
    if ((fn_802201A4(temp_r31) != 7) && ((u32) (fn_800145AC() - *((u32 *)&temp_r31->unk0x1D4)) > 0xEA60U)) {
        fn_80009C00(temp_r31->unk0xF0);
        Script_RunScript(QB_SHOWJOINTIMEOUTNOTICE, 0, 0, 0, 0);
    }
}
