// Promoted from src/wip (m2c draft hand-refined to exact match).
// range 0x80062DBC-0x80062F10 (340B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_8030044C[];
extern char lbl_802940B8[];
extern char lbl_802940D0[];
extern char lbl_80294100[];
void fn_80062BC0(void *, s32);
void fn_8012EE64(Unk_069CE08E *, s32);
void CStruct_delete(CStruct *, s32);
void fn_80068924(s32, void *);
void CObject_dtor(Unk_9994C3F5 *, s32);

void fn_80062DBC(Unk_EDE83D0E *arg0, s32 arg1) {
    Unk_C8FEE62D *temp_r30;
    void *temp_r9;
    void *var_r31;

    arg0->unk0x20 = (s32)lbl_802940B8;
    arg0->unk0x8 = (s32)lbl_802940D0;
    if (arg0->unk0x104 != 0) {
        fn_8012EE64((Unk_069CE08E *)arg0->unk0x104, 3);
    }
    if (arg0->unk0x108 != 0) {
        fn_8012EE64((Unk_069CE08E *)arg0->unk0x108, 3);
    }
    if (arg0->unk0x10C != 0) {
        CStruct_delete((CStruct *)arg0->unk0x10C, 3);
    }
    if (arg0->unk0x114 != 0) {
        Mem_Free2((void *)arg0->unk0x114);
    }
    if (arg0->unk0x118 != 0) {
        Mem_Free2((void *)arg0->unk0x118);
    }
    if (arg0->unk0x11C != 0) {
        Mem_Free2((void *)arg0->unk0x11C);
    }
    if (arg0->unk0x124 != 0) {
        Mem_Free2((void *)arg0->unk0x124);
    }
    temp_r9 = (void *)arg0->unk0x100;
    temp_r30 = (Unk_C8FEE62D *)((char *)arg0 + 0xC);
    if (temp_r9 != NULL) {
        var_r31 = (char *)temp_r9 + (*(s32 *)((char *)temp_r9 - 0x8) * 0x30);
        if (temp_r9 != var_r31) {
            do {
                var_r31 = (char *)var_r31 - 0x30;
                fn_80062BC0(var_r31, 0);
            } while (arg0->unk0x100 != (s32)var_r31);
        }
        Mem_Free2((void *)(arg0->unk0x100 - 8));
    }
    fn_80068924(*(s32 *)lbl_8030044C, arg0);
    temp_r30->unk0x14 = (s32)lbl_80294100;
    *(s32 *)((char *)temp_r30->unk0x10 + 0xC) = temp_r30->unk0xC;
    *(s32 *)((char *)temp_r30->unk0xC + 0x10) = temp_r30->unk0x10;
    temp_r30->unk0xC = (s32)temp_r30;
    temp_r30->unk0x10 = (s32)temp_r30;
    CObject_dtor((Unk_9994C3F5 *)arg0, arg1);
}
