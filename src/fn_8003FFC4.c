// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003FFC4-0x80040090 (204B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void CObject_AddRefLink(CStruct *, Unk_9994C3F5 *);
void CObject_RemoveRefLink(CStruct *, CStruct *);

s32 fn_8003FFC4(Unk_31DE137E *arg0) {
    s32 *sp8;
    s32 *temp_r31;
    s32 *temp_r3;
    s32 *temp_r0;
    register s32 *entry_copy asm("r3");
    register s32 *loop_copy asm("r3");
    s32 var_r30;
    s32 padA;
    s32 padB;

    ((Unk_59AB5482 *)&sp8)->unk0x4 = 0;
    ((Unk_59AB5482 *)&sp8)->unk0x8 = 0;
    temp_r3 = arg0->unk0x64;
    sp8 = temp_r3;
    if (temp_r3 != NULL) {
        CObject_AddRefLink((CStruct *)temp_r3, &sp8);
    }
    temp_r0 = sp8;
    entry_copy = temp_r0;
    __asm__("" : "+r"(entry_copy));
    var_r30 = 0;
    if (temp_r0 != NULL) {
        do {
            temp_r31 = ((Unk_C7387A53 *)sp8)->unk0x70;
            if (sp8 != NULL) {
                CObject_RemoveRefLink(*(s32 *)((char *)&sp8), &sp8);
                sp8 = NULL;
            }
            sp8 = temp_r31;
            if (temp_r31 != NULL) {
                CObject_AddRefLink((CStruct *)temp_r31, &sp8);
            }
            temp_r0 = sp8;
            loop_copy = temp_r0;
            __asm__("" : "+r"(loop_copy));
            var_r30 += 1;
        } while (temp_r0 != NULL);
    }
    if (loop_copy != NULL) {
        CObject_RemoveRefLink(loop_copy, &sp8);
        sp8 = NULL;
    }
    __asm__("" : : "m"(sp8), "m"(padA), "m"(padB));
    return var_r30;
}