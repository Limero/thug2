// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022AABC-0x8022AB24 (104B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"

extern void CStruct_delete(CStruct * arg0, s32 arg1);
extern void fn_8003A7A4(CStruct * arg0, s32 arg1);

void fn_8022AABC(Unk_31DE137E *arg0, s32 arg1) {
    void *p;

    p = *((void * *)&arg0->unk0x1C);
    if (p != NULL) {
        CStruct_delete((char *)p + 0x6C, 2);
        fn_8003A7A4((char *)p + 4, 2);
        Mem_Free(p);
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
