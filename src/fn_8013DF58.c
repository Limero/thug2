// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013DF58-0x8013DFE4 (140B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void memset(s32, s32, s32);
void fn_8013B538(s32 arg0, u8 *arg1, u16 *arg2, s32 arg3, s32 *arg4);

bool fn_8013DF58(Unk_440CB216 *arg0, s32 arg1, s32 arg2, void *arg3, s32 arg4, s32 arg5) {
    struct { u8 b0; u8 b1; u16 h2; s32 w4; s32 out; s32 padC; } sp8;
    char *var_sp;
    register s32 flags __asm__("r9");

    var_sp = (char *)&sp8;
    var_sp[0] = 8;
    memset((s32)var_sp, 0, 8);
    flags = arg0->unk0x2274;
    var_sp[1] = 2;
    ((Unk_7887B1E2 *)var_sp)->unk0x2 = 0;
    ((Unk_7887B1E2 *)var_sp)->unk0x4 = arg1;
    if (flags & 0x20) {
        fn_8013B538((s32)arg0, (u8 *)arg3, (u16 *)((char *)arg0 + 0x184C), arg4, &sp8.out);
    }
    return true;
}
