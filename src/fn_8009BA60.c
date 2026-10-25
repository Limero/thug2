// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009BA60-0x8009BAC0 (96B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_80070AE8(Unk_C7387A53 *, void *);
extern char lbl_80297738[];
void fn_8009BA60(Unk_C7387A53 *arg0, s32 arg1) {
    arg0->unk0x20 = (s32)lbl_80297738;
    if (((s32) arg0->unk0xC == 1) && ((s32) arg0->unk0x28 != 0)) {
        Mem_Free(*((void * *)&arg0->unk0x28));
    }
    fn_80070AE8(arg0, arg1);
}
