// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005C2B8-0x8005C2F8 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8005C2B8(Unk_9994C3F5 *o, s32 x1, s32 x2, s32 x3, u32 *arg, s32 arg0, s32 arg1, s32 arg2) {
    register u32 tmp asm("r0");
    u32 local;
    Unk_89391A04 *t;
    tmp = *arg;
    t = *((void ** *)&o->unk0x8);
    local = tmp;
    ((void (*)(void *, s32, s32, s32, u32 *))*((void * *)&t->unk0x9C))((char *)o + (s16)t->unk0x98, x1, x2, x3, &local);
}
