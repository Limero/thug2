// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013FF08-0x8013FF5C (84B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void CStruct_delete(CStruct *, s32);
extern char lbl_8029F700[];
void fn_8013FF08(Unk_C7387A53 *arg0, s32 arg1) {
    arg0->unk0xC = (s32)lbl_8029F700;
    CStruct_delete((s32)((char *)arg0 + 4), 2);
    if (arg1 & 1) {
        Mem_Free((s32)arg0);
    }
}
