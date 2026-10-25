// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007E15C-0x8007E1C8 (108B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_8005FB4C(CStruct *, void *);
extern char lbl_80296118[];
void fn_8007E15C(Unk_C7387A53 *arg0, s32 arg1) {
    Unk_C7387A53 *temp_r3;

    temp_r3 = arg0->unk0x58;
    arg0->unk0x50 = (s32)lbl_80296118;
    if ((temp_r3 != NULL) && ((s32) temp_r3->unk0x48 != 0)) {
        Mem_Free(temp_r3->unk0x48);
        *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x58) + 0x48) = 0;
    }
    fn_8005FB4C(arg0, arg1);
}