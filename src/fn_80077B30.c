// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80077B30-0x80077B64 (52B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void fn_8006E9AC(Unk_C7387A53 *);
void fn_80077B30(CStruct *arg0, s32 arg1) {
    s32 v;
    if (arg1 != 0 && (v = arg0->unk0x10) != 0) {
        fn_8006E9AC(v);
    }
}
