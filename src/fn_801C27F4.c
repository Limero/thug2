// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C27F4-0x801C2870 (124B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void* lbl_80305EAC;
extern s32 fn_801770D4(Unk_C7387A53 * arg0);
extern void fn_801AF4A8(CStruct * arg0);
extern s32 fn_801A6B80(Unk_93C2DF4D * arg0);
extern s32 Script_SpawnScript(Unk_15EF4A35 * arg0, s32 arg1, s32 arg2, Unk_80577C09 * arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9);
void fn_801C27F4(void) {
    fn_801AF4A8(fn_801770D4(lbl_80305EAC));
    if (fn_801A6B80(((Unk_C7387A53 *)lbl_80305EAC)->unk0x24) != 0) {
        Script_SpawnScript(QB_PROCESSALLGAPSREWARD, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    }
}
