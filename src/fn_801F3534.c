// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F3534-0x801F35DC (168B). Byte-identical.
// extra_cflags: -fno-strength-reduce
#include "types.h"
#include "structs.h"
typedef struct { u8 id; u8 f1; u8 f2; u8 f3; } slot_t;
void fn_801F3534(Unk_9A728979 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_r0;
    s32 found = 0;
    register s32 flag __asm__("r12") = 0;
    s32 i = 0;
    u8 *base;
    u8 *p303;
    u8 *p301;
    u8 *p300;
    u8 *p302;
    s32 off;
    s32 off2;

    temp_r0 = arg0->unk0x328;
    if (found < temp_r0) {
        base = (u8 *)arg0 + 0x300;
        if (arg0->unk0x300 != arg1) {
            for (;;) {
                temp_r0 = arg0->unk0x328;
                i += 1;
                if (i >= temp_r0) {
                    goto tail;
                }
                if (((slot_t *)base)[i].id == arg1) {
                    found = i;
                    goto setflag;
                }
            }
        }
    setflag:
        flag = 1;
    }
tail:
    if (flag == 0) {
        found = arg0->unk0x328;
        arg0->unk0x328 = found + 1;
    }
    p303 = (u8 *)arg0 + 0x303;
    p301 = (u8 *)arg0 + 0x301;
    p300 = (u8 *)arg0 + 0x300;
    p302 = (u8 *)arg0 + 0x302;
    off = found * 4;
    *(p303 + off) = arg4;
    *(p301 + off) = arg2;
    *(p300 + off) = arg1;
    *(p302 + off) = arg3 / 180;
}
