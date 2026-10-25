// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012EE64-0x8012EF68 (260B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_803032DC[];
extern s32 lbl_803032E0;
void fn_8003D404(void *);
void CObject_dtor(void * , s32);
void CObject_RemoveRefLink(CStruct *, CStruct *);
void fn_800A3D8C(void *, s32);
void fn_800A3D8C(void *, s32);
void CStruct_delete(CStruct *, s32);
void fn_8012CC68(void *);
void fn_8012F360(void);
void fn_8012F4DC(Unk_FFAD6788 *);
void fn_8012EE64(Unk_069CE08E *arg0, s32 arg1) {
    void *temp_r11;
    CStruct *temp_r3;
    CStruct *temp_r4;
    Unk_9994C3F5 *temp_r9;
    CStruct *temp_r9_2;

    fn_8012F360();
    fn_8012F4DC(arg0);
    if ((s32) arg0->unk0xDC != 0) {
        CStruct_delete(arg0->unk0xDC, 3);
    }
    temp_r11 = arg0->unk0x8;
    if (temp_r11 == NULL) {
        *(void * *)&lbl_803032DC = arg0->unk0x4;
    }
    temp_r9 = arg0->unk0x4;
    if (temp_r9 != NULL) {
        temp_r9->unk0x8 = temp_r11;
    }
    temp_r9_2 = arg0->unk0x8;
    if (temp_r9_2 != NULL) {
        temp_r9_2->unk0x4 =  arg0->unk0x4;
    }
    fn_8012CC68(arg0);
    temp_r3 = arg0->unk0xE0;
    if (temp_r3 != NULL) {
        if ((s32) temp_r3->unk0x10 != 0) {
            temp_r3->unk0x8 = 0;
        } else {
            fn_800A3D8C(temp_r3, 3);
        }
    }
    lbl_803032E0 -= 1;
    CObject_dtor((char *)arg0 + 0xEC, 2);
    temp_r3 = arg0->unk0xBC;
    temp_r4 = (CStruct *) &arg0->unk0xBC;
    if ((s32) temp_r3 != 0) {
        CObject_RemoveRefLink(temp_r3, temp_r4);
        arg0->unk0xBC = 0;
    }
    if (arg1 & 1) {
        fn_8003D404(arg0);
    }
}
