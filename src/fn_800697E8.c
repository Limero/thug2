// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800697E8-0x80069838 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_800691AC(Unk_4004120E *);
void fn_80069F74(s32);
void fn_800697E8(Unk_7A675EAB *arg0) {
    Unk_89391A04 *temp_r9;

    fn_80069F74((char *)arg0 + 8);
    fn_800691AC(arg0);
    temp_r9 = arg0->unk0x1B8;
    ((s32 (*)(void *))temp_r9->unk0x14)((char *)arg0 + temp_r9->unk0x10);
}