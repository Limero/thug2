// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007E7B8-0x8007E820 (104B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_80054C6C(Unk_9D99273B *, s32);
void fn_80062988(Unk_FFAD6788 *, s32);
extern char lbl_802961F8[];
void fn_8007E7B8(Unk_FFAD6788 *arg0, s32 arg1) {
    arg0->unk0xBC = (s32)lbl_802961F8;
    if ((s32) arg0->unk0xC0 != 0) {
        Mem_Free2(arg0->unk0xC0);
    }
    if ((s32) arg0->unk0xC8 != 0) {
        fn_80054C6C(arg0->unk0xC8, 1);
    }
    fn_80062988(arg0, arg1);
}
