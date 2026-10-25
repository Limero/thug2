// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B03E0-0x801B0430 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_801B0328(void);
s32 fn_801B0144(Unk_F96D0DC8 *, Unk_1D62F22E *);
s32 fn_801B0168(void *);
void fn_801B03E0(CStruct *arg0, void *arg1) {
    s32 temp_r30;

    if (fn_801B0328() != 0) {
        temp_r30 = arg0->unk0x4;
        fn_801B0144(temp_r30, fn_801B0168(arg1));
    }
}
