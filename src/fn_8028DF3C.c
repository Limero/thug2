// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8028DF3C-0x8028DF98 (92B). Byte-identical.
#include "types.h"
extern bool lbl_80310AB0;
void InitializeUART(s32);
void WriteUARTN(s32, s32);
s32 fn_8028DF3C(s32 arg0, s32 arg1) {
    if (lbl_80310AB0 != 0) {
        lbl_80310AB0 = 0;
        InitializeUART(0);
    }
    WriteUARTN(arg0, arg1);
    return arg1;
}
