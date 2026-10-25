// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009F558-0x8009F5C4 (108B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_80131C48(void *);
extern char lbl_80297AB0[];
void fn_8009F558(Unk_C8FEE62D *arg0, s32 arg1) {
    s32 var_r9;

    arg0->unk0x18 = (s32)lbl_80297AB0;
    var_r9 = 1;
    if (!(arg0->unk0x8 & 2)) {
        var_r9 = 0;
    }
    if (var_r9 != 0) {
        fn_80131C48(arg0);
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
