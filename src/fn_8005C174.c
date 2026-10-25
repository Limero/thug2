// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005C174-0x8005C1B4 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8005C174(Unk_9994C3F5 *o, u32 *arg, s32 arg0) {
    register u32 tmp asm("r0");
    u32 local;
    Unk_2C7D9FAD *t;
    tmp = *arg;
    t = *((void ** *)&o->unk0x8);
    local = tmp;
    ((void (*)(void *, u32 *))*((void * *)&t->unk0x6C))((char *)o + (s16)t->unk0x68, &local);
}
