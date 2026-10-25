// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80220400-0x8022046C (108B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void fn_80137CB4(Unk_9F066EC1 * arg0);
extern void fn_8013DE78(void * arg0, Unk_C71E6DE1 * arg1);
register s32 r31_guard __asm__("r31");

void fn_80220400(Unk_74087627 *arg0) {
    u8 sp8[0x28];

    fn_80137CB4((void *)sp8);
    ((Unk_7887B1E2 *)sp8)->unk0x4 = (s32)((char *)arg0 + 0x30);
    ((Unk_7887B1E2 *)sp8)->unk0x2 = 1;
    ((Unk_7887B1E2 *)sp8)->unk0x0 = 0x59;
    ((Unk_7887B1E2 *)sp8)->unk0xC = 2;
    ((Unk_7887B1E2 *)sp8)->unk0x10 = 8;
    fn_8013DE78(arg0->unk0xC, (void *)sp8);
    arg0->unk0x31 = arg0->unk0x30;
}
