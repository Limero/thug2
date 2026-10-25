// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800BE7A4-0x800BE854 (176B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void CObject_RemoveRefLink(CStruct *, CStruct *);
void fn_80105C34(void *, s32);
void fn_8009F558(Unk_C8FEE62D *, s32);
extern char lbl_80299220[];
void fn_800BE7A4(Unk_9D99273B *arg0, s32 arg1) {
    s32 temp_r9;
    void *temp_r11;
    void *var_r31;
    s32 var_r29;

    temp_r11 = *((void * *)&arg0->unk0x2F0);
    arg0->unk0x18 = (s32)lbl_80299220;
    if (temp_r11 != NULL) {
        temp_r9 = *(s32 *)((char *)temp_r11 - 0x8);
        var_r31 = (char *)temp_r11 + (((temp_r9 * 0x10) - temp_r9) << 5);
        if (temp_r11 != var_r31) {
            var_r29 = 0;
            do {
                void *var_field;
                var_r31 -= 0x1E0;
                var_field = (char *)var_r31 + (s32)0x1C8;
                if (*(s32 *)var_field != 0) {
                    CObject_RemoveRefLink((void *)*(s32 *)var_field, var_field);
                    *(s32 *)var_field = var_r29;
                }
            } while (*((void * *)&arg0->unk0x2F0) != var_r31);
        }
        Mem_Free2((void *)(arg0->unk0x2F0 - 8));
    }
    fn_80105C34((char *)arg0 + 0x338, 2);
    fn_8009F558(arg0, arg1);
}
