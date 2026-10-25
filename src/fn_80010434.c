// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80010434-0x80010544 (272B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8000F95C(s32, s32, s32, s32);
void strcpy(s32, s32);
void * Mem_NewZero(s32 size);
char * fn_8000F10C(Unk_4897C6F8 *this, s32 a, s32 b, Unk_E15B2970 *disp);
void fn_800107A0(Unk_C8FEE62D *arg0, s32 arg1, s32 arg2);
s32 fn_8001094C(s32, s32);
void fn_8001BC9C(s32 arg0);
extern char lbl_802FFE98[];
void fn_80010434(Unk_9D99273B *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_r11;
    s32 temp_r3_3;
    s32 var_r10;
    void *buf;
    char *base;
    Unk_C7387A53 *temp_r3_2;
    void *var_r31;

    var_r10 = 0;
    var_r31 = NULL;
    if ((s32) arg0->unk0x290 == 0) {
        var_r31 = (char *)arg0 + 0x204;
    } else {
loop_2:
        var_r10 += 1;
        if (var_r10 <= 6) {
            temp_r11 = var_r10 * 0x90;
            base = (char *)arg0 + 0x290;
            if ((s32) *(s32 *)(base + temp_r11) == 0) {
                var_r31 = (char *)arg0 + (temp_r11 + 0x204);
            } else {
                goto loop_2;
            }
        }
    }
    ((CStruct *)var_r31)->unk0x8 = arg1;
    strcpy((char *)var_r31 + 0xC, arg3);
    if (arg4 != 0) {
        buf = Mem_NewZero(0x1C);
        ((CStruct *)var_r31)->unk0x0 = fn_8001094C(buf, 0);
        fn_8001BC9C(3);
        temp_r3_2 = *(void **)lbl_802FFE98;
        temp_r3_3 = fn_8000F10C(temp_r3_2, arg2, 1, temp_r3_2->unk0x164);
        fn_800107A0(((CStruct *)var_r31)->unk0x0, temp_r3_3, temp_r3_3 + arg2);
    } else {
        buf = Mem_NewZero(0x1C);
        ((CStruct *)var_r31)->unk0x0 = fn_8001094C(buf, arg2);
    }
    ((CStruct *)var_r31)->unk0x4 = fn_8000F95C(arg0, ((CStruct *)var_r31)->unk0x0, 1, (char *)var_r31 + 0xC);
    ((CStruct *)var_r31)->unk0x8C = 1;
}
