// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013B42C-0x8013B4B8 (140B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8029F480[];
extern s32 fn_8013E034(void *, CStruct *);
extern void fn_801372B8(Unk_1624B368 *, s32);
extern s32 fn_8013E068(void *, CStruct *);

void fn_8013B42C(Unk_C7387A53 *arg0) {
    struct { s32 unk0; s32 unk4; char *unk8; s32 unkC; } sp8;
    register char *temp_r4 __asm__("r4");
    char *var_sp;
    s32 *temp_r30;
    s32 var_r31;

    temp_r4 = (char *)&sp8;
    ((Unk_42076946_2 *)temp_r4)->unk0x8 = lbl_8029F480;
    var_sp = temp_r4;
    ((Unk_4C649A8C *)temp_r4)->unk0x4 = 0;
    temp_r30 = *((s32 * *)&arg0->unk0x20);
    var_r31 = fn_8013E034(temp_r30, temp_r4);
    if (var_r31 != 0) {
        do {
            fn_801372B8(var_r31 + 0x20EC, *(s32 *)temp_r30);
            fn_801372B8(var_r31 + 0x34FC, *(s32 *)temp_r30);
            var_r31 = fn_8013E068(temp_r30, &sp8);
        } while (var_r31 != 0);
    }
    ((Unk_42076946_2 *)var_sp)->unk0x8 = lbl_8029F480;
}
