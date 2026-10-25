// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80128FB4-0x80128FF4 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80042220(void *);
void fn_80128FFC(Unk_F8A5095F *);
void fn_80128FB4(Unk_F8A5095F *arg0, s32 arg1) {
    fn_80128FFC(arg0);
    if (arg1 & 1) {
        fn_80042220(arg0);
    }
}
