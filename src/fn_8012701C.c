// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012701C-0x8012705C (64B). Byte-identical.
#include "types.h"
#include "structs.h"
void CStruct_operator_delete(void *);
void CStruct_dtor(CStruct *);
// CStruct_delete @ 0x8012701C
void CStruct_delete(CStruct *arg0, s32 arg1) {
    CStruct_dtor(arg0);
    if (arg1 & 1) {
        CStruct_operator_delete(arg0);
    }
}
