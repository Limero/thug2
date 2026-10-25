// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800FCE98-0x800FCEE8 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_800FCE98(CStruct *arg0) {
    register void *t __asm__("r9");
    register void *cur __asm__("r11");
    void *node;
    Unk_EFE13F4E *vt;
    t = *((void * *)&arg0->unk0x10);
    cur = *((void * *)&((Unk_C7387A53 *)t)->unk0xC);
    if (((CStruct *)cur)->unk0x4 == -1) {
        cur = NULL;
    }
    node = *((void * *)&((CStruct *)cur)->unk0x4);
    vt = *((void * *)&((Unk_C7387A53 *)node)->unk0xC);
    ((s32 (*)(void *))(*((void * *)&vt->unk0x4C)))(node + vt->unk0x48);
}