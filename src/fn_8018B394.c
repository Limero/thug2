// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018B394-0x8018B3D4 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_8018B33C(CStruct *);
void fn_8018B394(CStruct *arg0, s32 arg1) {
    fn_8018B33C(arg0);
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
