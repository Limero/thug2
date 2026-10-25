// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801270B4-0x80127138 (132B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_801266EC(Unk_5D1D68CC *);
void fn_80117E28(void *);
void fn_801270B4(CStruct *arg0, s32 arg1) {
    register void *r28 asm("r28");
    register void *r29 asm("r29");
    register void *r30 asm("r30");
    register void *r31 asm("r31");
    register s32 r27 asm("r27");

    r29 = arg0;
    r27 = arg1;
    r28 = NULL;
    r31 = *((void * *)&arg0->unk0x4);
    if (r31 != NULL) {
        do {
            r30 = *((void * *)&((CStruct *)r31)->unk0xC);
            if (((CStruct *)r31)->unk0x4 == r27) {
                if (r28 != NULL) {
                    *((void * *)&((Unk_C7387A53 *)r28)->unk0xC) = r30;
                } else {
                    *((void * *)&((CStruct *)r29)->unk0x4) = r30;
                }
                fn_801266EC(r31);
                fn_80117E28(r31);
            } else {
                r28 = r31;
            }
            r31 = r30;
            __asm__ ("" : "+r"(r30));
        } while (r30 != NULL);
    }
}
