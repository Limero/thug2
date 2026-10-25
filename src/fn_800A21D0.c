// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A21D0-0x800A2234 (100B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_800A27BC(void *);
void fn_8009F7A4(Unk_6A70655D *, void *);
extern char lbl_80297E50[];
void fn_800A21D0(Unk_9994C3F5 *arg0, s32 arg1) {
    arg0->unk0x8 = (s32)lbl_80297E50;
    if ((s32) arg0->unk0x11C != 0) {
        Mem_Free(*((void * *)&arg0->unk0x11C));
        arg0->unk0x11C = 0;
    }
    fn_800A27BC(arg0);
    fn_8009F7A4(arg0, arg1);
}
