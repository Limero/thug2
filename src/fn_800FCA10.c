// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800FCA10-0x800FCAA4 (148B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_800FCA10(CStruct *arg0) {
    register void *t __asm__("r9");
    register void *first __asm__("r11");
    s32 result;
    s32 v;
    CStruct *cur;
    s32 found;
    Unk_C7387A53 *node;
    Unk_89391A04 *vt;
    s16 off;
    CStruct *next;
    t = *((void * *)&arg0->unk0x10);
    result = 1;
    first = *((void * *)&((Unk_C7387A53 *)t)->unk0xC);
    v = ((CStruct *)first)->unk0x4;
    cur = first;
    for (; (v == -1 && (cur = NULL), cur != NULL); ) {
        found = 0;
        if (result != 0) {
            node = *((void * *)&cur->unk0x4);
            vt = *((void * *)&node->unk0xC);
            off = vt->unk0x10;
            if (((s32 (*)(void *))(*((void * *)&vt->unk0x14)))((char *)node + off) != 0) {
                found = 1;
            }
        }
        next = *((void * *)&cur->unk0xC);
        result = found;
        v = next->unk0x4;
        cur = next;
    }
    return result;
}