// WIP fn_80012754 (144B). L2: r3 pinned only, natural r9 allocation.
#include "types.h"
#include "structs.h"
extern char lbl_8031349C[];
s32 fn_800122C4(s32 arg0);
void *fn_80012284(CStruct *arg0, s32 arg1);
void *fn_80012754(s32 arg0) {
    s32 *var_r29;
    s32 var_r30;
    register void *var_r3 __asm__("r3");
    void *var_r9;
    s32 var_r31;
    s32 temp_r3;
    s32 i;

    var_r29 = (s32 *)lbl_8031349C;
    do {
        temp_r3 = *var_r29;
        var_r29 += 1;
        if (temp_r3 != 0) {
            var_r3 = (void *)fn_800122C4(temp_r3);
            var_r30 = *(s32 *)((char *)var_r3 + 0x8);
            var_r9 = (char *)var_r3 + 0xc;
            i = 0;
            while (i < var_r30) {
                if (*(s32 *)((char *)var_r9 + 0xc) == arg0) {
                    return var_r9;
                }
                var_r9 = fn_80012284(var_r9, 1);
                i += 1;
            }
        }
    } while ((s32)var_r29 <= (s32)((char *)lbl_8031349C + 0x18c));
    return NULL;
}