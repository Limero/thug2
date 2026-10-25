// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800FCDC4-0x800FCE48 (132B). Byte-identical.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
void fn_800FCDC4(CStruct *arg0, s32 arg1, s32 arg2) {
    register void *t __asm__("r9");
    register void *first __asm__("r11");
    s32 v;
    CStruct *cur;
    Unk_C7387A53 *node;
    Unk_BC571107 *vt;
    s16 off;
    CStruct *next;
    t = *((void * *)&arg0->unk0x10);
    first = *((void * *)&((Unk_C7387A53 *)t)->unk0xC);
    v = ((CStruct *)first)->unk0x4;
    cur = first;
    for (; (v == -1 && (cur = NULL), cur != NULL); ) {
        node = *((void * *)&cur->unk0x4);
        vt = *((void * *)&node->unk0xC);
        off = vt->unk0xA0;
        ((void (*)(void *, s32, s32))(*((void * *)&vt->unk0xA4)))(
            (char *)node + off, arg1, arg2);
        next = *((void * *)&cur->unk0xC);
        v = next->unk0x4;
        cur = next;
    }
}