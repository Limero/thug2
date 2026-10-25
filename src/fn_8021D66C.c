// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021D66C-0x8021D758 (236B). Byte-identical.
#include "types.h"
#include "structs.h"

void fn_8013E098(s32, void *);
void fn_8022AABC(Unk_31DE137E *, s32);

void fn_8021D66C(void *arg0, s32 arg1) {
    register void *base __asm__("r11");
    register void *temp_r9 __asm__("r9");
    Unk_C8FEE62D *temp_r30;
    s32 temp_r0;
    Unk_C8FEE62D *var_r31;

    base = arg0;
    temp_r9 = *((void * *)&((Unk_A7137CF0 *)base)->unk0x154);
    temp_r0 = ((CStruct *)temp_r9)->unk0x4;
    var_r31 = temp_r9;
    if (temp_r0 == -1) {
        var_r31 = NULL;
    }
    while (var_r31 != NULL) {
        temp_r30 = *((void * *)&var_r31->unk0x4);
        if (temp_r30 == arg1) {
            if (((Unk_A7137CF0 *)base)->unk0x8 != 0) {
                fn_8013E098(((Unk_A7137CF0 *)base)->unk0x8,
                            *((void * *)&temp_r30->unk0x14));
            } else if (temp_r30->unk0x14 != 0) {
                fn_8013E098(((Unk_A7137CF0 *)base)->unk0xC,
                            *((void * *)&temp_r30->unk0x14));
            }
            if (var_r31 != NULL) {
                void *vt = *((void * *)&var_r31->unk0x14);
                ((s32 (*)(void *, s32))((Unk_F5317C5D *)vt)->unk0xC)(
                    (char *)var_r31 + ((Unk_F5317C5D *)vt)->unk0x8, 3);
            }
            if (temp_r30 != NULL) {
                fn_8022AABC(temp_r30, 3);
            }
            return;
        }
        temp_r9 = *((void * *)&var_r31->unk0xC);
        temp_r0 = ((CStruct *)temp_r9)->unk0x4;
        var_r31 = temp_r9;
        if (temp_r0 == -1) {
            var_r31 = NULL;
        }
    }
}
