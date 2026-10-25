// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80226F04-0x80226F54 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8021FAB4(Unk_9994C3F5 *, s32, s32, char *, char *, s32, s32, s32, s32);
bool fn_80226F04(CScript *arg0) {
    s32 sp8;
    char *temp_r6;

    temp_r6 = *(char **)arg0;
    sp8 = ((Unk_4C649A8C *)temp_r6)->unk0x8;
    fn_8021FAB4(arg0->unk0x18, 0, ((Unk_4C649A8C *)temp_r6)->unk0x4, (s32)(temp_r6 + 0xC), (s32)(temp_r6 + 0x1C), 0, 0, 0, sp8);
    return true;
}
