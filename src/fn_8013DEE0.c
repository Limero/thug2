// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013DEE0-0x8013DF58 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern void *memcpy(void *, const void *, s32);
extern void fn_8013DF58(s32, s32, s32, void *, s32, s32);
void fn_8013DEE0(Unk_440CB216 *arg0, s8 arg1, s32 arg2, void *arg3, s32 arg4, s32 arg5, s32 arg6) {
    struct msg_s {
        u8 cmd;
        u16 len;
        u8 data[0x515];
        u16 len2;
    } __attribute__((packed)) msg;
    register s32 v5 __asm__("r5");
    s32 len;
    v5 = arg2;
    msg.cmd = arg1;
    msg.len2 = v5;
    msg.len = v5;
    len = v5 | arg2;
    if (len) {
        memcpy(msg.data, (void *)arg3, len);
    }
    fn_8013DF58(arg0, arg4, arg5, &msg, msg.len2 + 3, arg6);
}
