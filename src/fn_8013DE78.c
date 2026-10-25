// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013DE78-0x8013DEE0 (104B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8029F480[];
extern s32 fn_8013E034(void *, CStruct *);
extern void fn_8013CC84(void *, s32, Unk_C71E6DE1 *);

void fn_8013DE78(void *arg0, Unk_C71E6DE1 *arg1) {
    struct { s32 unk0; s32 unk4; char *unk8; s32 unkC; } sp8;
    Unk_4C649A8C *var_sp;
    Unk_C7387A53 *temp_r3;

    var_sp = (char *)&sp8;
    var_sp->unk0x4 = 0;
    ((Unk_42076946_2 *)var_sp)->unk0x8 = lbl_8029F480;
    temp_r3 = (void *)fn_8013E034((void *)arg0, var_sp);
    if (temp_r3 != NULL) {
        fn_8013CC84(arg0, temp_r3->unk0x48, arg1);
    }
    ((Unk_42076946_2 *)var_sp)->unk0x8 = lbl_8029F480;
}
