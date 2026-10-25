// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CB098-0x800CB178 (224B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void *Mem_NewZero(s32);
s32 fn_8002DF68(void *, s32, s32, s32);
s32 fn_8000F2F8(void *, void *);
void fn_8000F320(Unk_F12C5E01 *);
void fn_80030AE4(void *, s32);
extern Unk_9994C3F5 *lbl_802FFE98;
void fn_800CB098(Unk_C7387A53 *arg0, s32 arg1) {
    s32 var_r9;
    s32 probe;
    CStruct *temp_r31;
    CStruct *temp_r3;
    Unk_9994C3F5 *mgr;
    void *var_r31;
    CStruct *temp_r9;
    Unk_C7387A53 *temp_r9_2;

    temp_r31 = (char *)arg0 + 0x2C;
    var_r9 = 1;
    if ((s32) temp_r31->unk0x10 == temp_r31) {
        var_r9 = 0;
    }
    if (var_r9 == 0) {
        temp_r3 = (CStruct *)Mem_NewZero(0x84);
        temp_r3 = fn_8002DF68(temp_r3, arg0->unk0xC, arg0, 1);
        mgr = lbl_802FFE98;
        temp_r3->unk0x10 = temp_r31;
        temp_r3->unk0xC =  temp_r31->unk0xC;
        *(s32 *)(*(s32 *)((char *)((char *)temp_r31) + 0xC) + 0x10) = temp_r3;
        temp_r31->unk0xC = temp_r3;
        fn_8000F2F8(mgr, mgr->unk0x11C);
        temp_r9 = temp_r31->unk0xC;
        probe = (s32) temp_r9->unk0x4;
        /* register-recycling copy into the r31 home of the dead `arg0+0x2C`
           value; the 3rd operand only pins the lwz ahead of the mr */
        __asm__ ("mr %0,%1" : "=r" (var_r31) : "r" (temp_r9), "r" (probe));
        if (probe == -1) {
            var_r31 = NULL;
        }
        if (var_r31 != NULL) {
            temp_r9_2 = ((Unk_C8FEE62D *)var_r31)->unk0x14;
            ((s32 (*)(void *, void *))temp_r9_2->unk0x24)(var_r31 + *(s16 *)((char *)temp_r9_2 + 0x20), arg1);
            fn_80030AE4(var_r31, 1);
        }
        fn_8000F320(lbl_802FFE98);
    }
}
