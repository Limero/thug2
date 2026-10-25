// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022D7C0-0x8022D824 (100B). Byte-identical.
#include "types.h"
#include "structs.h"
void *fn_80240C80(void *);
void fn_80241580(s32 *, s32);

void fn_8022D7C0(Unk_9994C3F5 *arg0, s32 arg1) {
    Unk_9994C3F5 *p;
    void *next;

    p = *((void * *)&arg0->unk0x8);
    if (p != NULL) {
        do {
            next = *((void * *)&p->unk0x8);
            if (((*(s32 *)((char *)fn_80240C80(p) + (s32)4) & 0x40) != 0)) {
                fn_80241580(fn_80240C80(p), arg1);
            }
            p = next;
        } while (p != NULL);
    }
}
