// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012E0AC-0x8012E168 (188B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void *Mem_Alloc_3(s32);
u32 strlen(char *);
char *strcpy(char *, char *);
void fn_801263A0(s32, u8 *);
extern char lbl_803032B8[];
void fn_8012E0AC(s32 arg0, u8 *arg1) {
    s32 temp_r11;
    s32 temp_r9;
    register u8 *var_r29 __asm__("r29");
    CStruct *temp_r31;
    register CStruct *var_r30 __asm__("r30");
    char *temp_r0;

    temp_r11 = *(s32 *)&lbl_803032B8;
    temp_r9 = (arg0 & 0xFFF) * 0xC;
    temp_r31 = (CStruct *)(temp_r11 + temp_r9);
    var_r30 = (CStruct *)temp_r31->unk0x4;
    var_r29 = arg1;
    if (var_r30 != NULL) {
        var_r30 = (CStruct *)Mem_Alloc_3(0xC);
        var_r30->unk0x0 = arg0;
        temp_r0 = (char *)Mem_Alloc_3(strlen((char *)var_r29) + 1);
        var_r30->unk0x4 = (s32)temp_r0;
        strcpy(temp_r0, (char *)var_r29);
        var_r30->unk0x8 = temp_r31->unk0x8;
    } else {
        temp_r31->unk0x0 = arg0;
        temp_r0 = (char *)Mem_Alloc_3(strlen((char *)var_r29) + 1);
        temp_r31->unk0x4 = (s32)temp_r0;
        strcpy(temp_r0, (char *)var_r29);
    }
    temp_r31->unk0x8 = (s32)var_r30;
    fn_801263A0(arg0, var_r29);
}
