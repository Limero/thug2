// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80199E64-0x80199EAC (72B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void* lbl_80305EAC;
extern s32 fn_801746A4(Unk_C7387A53 * arg0, s32 arg1);
extern s32 fn_801403CC(void * arg0);
extern s32 fn_801813F0(CStruct * arg0);
bool fn_80199E64(void *arg0, s32 arg1) {
    s32 temp_r3;

    temp_r3 = fn_801403CC(fn_801746A4(lbl_80305EAC, arg1));
    if (temp_r3 != 0 && fn_801813F0(temp_r3) > 0) {
        return true;
    }
    return false;
}
