// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80054950-0x800549E0 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_80054894(s32, s32, s32);
void fn_8001075C(s32);
s32 fn_80076F8C(s32, Unk_9994C3F5 *, s32, s32, s32);
void fn_80010760(void);
void fn_80054A68(s32, s32, Unk_9994C3F5 *, s32, s32);
s32 fn_80054950(s32 arg0, Unk_9994C3F5 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    char sp8[0x80];
    s32 temp_r30;

    fn_80054894((s32)sp8, arg0, arg5);
    fn_8001075C((s32)sp8);
    temp_r30 = fn_80076F8C((s32)sp8, arg1, arg2, arg3, arg4);
    fn_80010760();
    fn_80054A68(temp_r30, arg0, arg1, 0, arg5);
    return temp_r30;
}
