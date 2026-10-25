// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000CC48-0x8000CCBC (116B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_8000E5A4(CStruct *, s32);
void fn_8000E508(CStruct *);
void fn_8000E7BC(s32, s32, s32);
void fn_8000CAEC(void);
void fn_8000CC48(CStruct *arg0, s32 arg1) {
    Mem_Free(arg0->unk0x4);
    fn_8000E7BC(arg0->unk0xC, (s32)fn_8000CAEC, 0);
    fn_8000E508(arg0->unk0xC);
    if ((s32) arg0->unk0xC != 0) {
        fn_8000E5A4(arg0->unk0xC, 3);
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
