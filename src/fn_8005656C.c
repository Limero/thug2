// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005656C-0x80056660 (244B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_80012A10(s32);
void fn_8010646C(Unk_C7387A53 *, s32);
bool fn_8005656C(void *arg0) {
    register void *bp __asm__("r29");
    register s32 t0 __asm__("r0");
    s32 bound;
    s32 temp_r30;
    s32 var_r31;
    void *temp_r9;
    Unk_F5317C5D *temp_r9_2;
    void *var_r31_2;

    bp = arg0;
    temp_r30 = ((Unk_B3493221 *)bp)->unk0xD4;
    if (temp_r30 != 0) {
        t0 = temp_r30 + 0x30;
        if (t0 != 0) {
            var_r31 = temp_r30 + 0x4B30;
            if (t0 != var_r31) {
                bound = t0;
                do {
                    var_r31 -= 0x30;
                    fn_8010646C(var_r31, 0);
                } while (bound != var_r31);
            }
        }
        Mem_Free(temp_r30);
        ((Unk_B3493221 *)bp)->unk0xD4 = 0;
    }
    temp_r9 = ((Unk_B3493221 *)bp)->unk0x15C;
    if (temp_r9 != NULL) {
        var_r31_2 = temp_r9 + (*(s32 *)((char *)temp_r9 - 0x8) * 0x10);
        if (temp_r9 != var_r31_2) {
            do {
                var_r31_2 -= 0x10;
                temp_r9_2 = ((Unk_C7387A53 *)var_r31_2)->unk0xC;
                ((s32 (*)(void *, s32))temp_r9_2->unk0xC)(var_r31_2 + temp_r9_2->unk0x8, 0);
            } while ( ((Unk_B3493221 *)bp)->unk0x15C != var_r31_2);
        }
        Mem_Free2(((Unk_B3493221 *)bp)->unk0x15C - 8);
        ((Unk_B3493221 *)bp)->unk0x15C = NULL;
    }
    if (((Unk_B3493221 *)bp)->unk0xD8 != 0) {
        fn_80012A10(bp + 0xD8);
        ((Unk_B3493221 *)bp)->unk0xD8 = 0;
    }
    return true;
}