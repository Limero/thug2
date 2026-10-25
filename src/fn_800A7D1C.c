// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A7D1C-0x800A7DB4 (152B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 Mem_Free2(s32);
void CObject_RemoveRefLink(CStruct *, CStruct *);
void Mem_Free(void *);
void fn_800A7D1C(void **arg0, s32 arg1) {
    s32 *var_r31;
    s32 temp_r3;
    void *temp_r9;

    temp_r9 = *arg0;
    if (temp_r9 != NULL) {
        var_r31 = temp_r9 + (*(s32 *)((char *)temp_r9 - 0x8) * 0xC);
        if (temp_r9 != var_r31) {            do {
                var_r31 = (s32 *)((char *)var_r31 - 0xC);
                temp_r3 = *(s32 *)var_r31;
                if (temp_r3 != 0) {
                    CObject_RemoveRefLink(temp_r3, var_r31);
                    *((s32 *)var_r31) = 0;
                }
            } while ((void *)*arg0 != var_r31);
        }
        Mem_Free2(*arg0 - 8);
        *arg0 = NULL;
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
