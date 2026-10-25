// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005C038-0x8005C070 (56B). Byte-identical.
// extra_cflags: -ffixed-r9
#include "types.h"
#include "structs.h"
void fn_8005C038(Unk_9994C3F5 *arg0, s32 arg1) {
    register void *r11 asm("r11");
    register s32 r4 asm("r4") = arg1;
    *(s32 *)arg0 = r4;
    asm volatile ("" ::: "memory");
    r11 = *((void * *)&arg0->unk0x8);
    ((Unk_89391A04 *)r11)->unk0x24((char *)arg0 + ((Unk_89391A04 *)r11)->unk0x20);
}
