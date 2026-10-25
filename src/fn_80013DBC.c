// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80013DBC-0x80013E2C (112B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void Mem_Free_3(void *);
void fn_80013788(void *);
extern char lbl_802909B0[];
void fn_80013DBC(Unk_F2F24C3E *arg0, s32 arg1) {
    arg0->unk0x2354 = (s32)lbl_802909B0;
    if ((s32) arg0->unk0x8 != 0) {
        Mem_Free_3(arg0->unk0x8);
        arg0->unk0x8 = 0;
    }
    if ((s32) arg0->unk0x4 != 0) {
        fn_80013788(arg0->unk0x4);
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
