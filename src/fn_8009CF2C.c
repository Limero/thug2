// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009CF2C-0x8009CFA0 (116B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_8009CFA0(void);
extern s32 fn_8013E2BC(void);
s32 fn_8009CF2C(CStruct *arg0) {
    s32 var_r3;
    s32 temp;
    temp = fn_8009CFA0();
    var_r3 = 0;
    if (temp == 0) goto epi;
    var_r3 = arg0->unk0x8;
    if (var_r3 == 0) goto check_c;
    temp = fn_8013E2BC();
    var_r3 = 1;
    if (temp == 0) goto epi;
check_c:
    var_r3 = arg0->unk0xC;
    if (var_r3 == 0) goto done;
    temp = fn_8013E2BC();
    var_r3 = 1;
    if (temp == 0) goto epi;
done:
    var_r3 = 0;
epi:
    return var_r3;
}
