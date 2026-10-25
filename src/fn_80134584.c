// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80134584-0x801345DC (88B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80134B00(CStruct *, s32 *);
void fn_80134524(CScript *, Unk_C8FEE62D *);
void fn_80134368(Unk_9994C3F5 *, s32);
void fn_80134584(CScript *arg0, Unk_C8FEE62D *arg1) {
    fn_80134B00((void *)arg0->unk0x18, (char *)arg1 + 4);
    fn_80134524(arg0, (void *)arg1);
    if (arg1 != 0) {
        fn_80134368((void *)arg1, 3);
    }
}
