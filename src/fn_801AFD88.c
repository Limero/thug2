// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801AFD88-0x801AFDD8 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
void *fn_801AFD88(CStruct *arg0, s32 arg1) {
    register void *r9 asm("r9");
    register void *r3 asm("r3");
    register s32 r0 asm("r0");
    register s32 r11 asm("r11");

    r9 = *((void * *)&arg0->unk0x10);
    r0 = ((CStruct *)r9)->unk0x4;
    if (r0 == -1) r9 = NULL;
    r11 = 0;
    r3 = r9;
    while (r3 != NULL) {
        if (r11 == arg1) return r3;
        r9 = *((void * *)&((Unk_C7387A53 *)r3)->unk0xC);
        r0 = ((CStruct *)r9)->unk0x4;
        if (r0 == -1) r9 = NULL;
        r11 += 1;
        r3 = r9;
    }
    return NULL;
}
