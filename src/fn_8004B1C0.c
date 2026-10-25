// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004B1C0-0x8004B270 (176B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8003FDF0(Unk_C7387A53 *, s32);
void CObject_AddRefLink(CStruct *, Unk_9994C3F5 *);
void CObject_RemoveRefLink(CStruct *, CStruct *);
void fn_8004B1C0(CStruct *arg0, s32 arg1) {
    struct { s32 a; s32 b; s32 c; s32 d; } sp8;
    s32 *sp8p;
    s32 temp_r0;
    s32 temp_r3;
    CStruct *temp_r9;
    CStruct *var_r31;
    CStruct *var_r9;

    var_r9 = arg0->unk0x10;
    if ((s32) var_r9->unk0x4 == -1) {
        var_r9 = NULL;
    }
    var_r31 = var_r9;
    if (var_r31 != NULL) {
        do {
            sp8p = (s32 *)&sp8;
            temp_r3 = var_r31->unk0x4;
            ((CStruct *)sp8p)->unk0x4 = 0;
            ((CStruct *)sp8p)->unk0x8 = 0;
            *sp8p = temp_r3;
            if (temp_r3 != 0) {
                CObject_AddRefLink(*sp8p, sp8p);
            }
            fn_8003FDF0(*sp8p, arg1);
            temp_r9 = var_r31->unk0xC;
            temp_r0 = temp_r9->unk0x4;
            var_r31 = temp_r9;
            if (temp_r0 == -1) {
                var_r31 = NULL;
            }
            if (*sp8p != 0) {
                CObject_RemoveRefLink(*sp8p, sp8p);
                *sp8p = 0;
            }
        } while (var_r31 != NULL);
    }
}
