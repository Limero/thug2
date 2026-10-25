// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801AAC24-0x801AAC74 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802ABB10[];
extern void fn_801AAC84(Unk_EE1FD121 *);
extern void fn_8009F7A4(Unk_6A70655D *, s32);
void fn_801AAC24(Unk_361D6392 *arg0, s32 arg1) {
    arg0->unk0x8 = (s32)lbl_802ABB10;
    fn_801AAC84(arg0);
    arg0->unk0x120 = 0;
    fn_8009F7A4(arg0, arg1);
}
