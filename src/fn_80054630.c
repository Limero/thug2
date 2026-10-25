// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80054630-0x80054670 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80054424(CStruct *);
extern char lbl_80364C10[];
void fn_80054630(s32 arg0, s32 arg1) {
    if ((arg1 == 0xFFFF) && (arg0 != 0)) {
        fn_80054424(lbl_80364C10);
    }
}
