// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022DDB8-0x8022DF2C (372B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern bool lbl_80306014;
extern void* lbl_802FFE98;
s32 *fn_80240C7C(void *);
void *fn_80240C80(void *);
s32 fn_8022DCD8(s32, s32, s32, s32, s32);
s32 fn_8023FB40(void);
void fn_8000F2F8(Unk_9F352E7C *, s32);
void *fn_80240E7C(Unk_C8FEE62D *);
void fn_8000F320(Unk_F12C5E01 *);
void fn_80240F28(CStruct *, s32, s32);
s32 fn_80241540(void *, void *);
s32 fn_800546A0(s32);
s32 fn_80057CA0(CStruct *);
void fn_8024077C(void *);
void *fn_8022DDB8(void *arg0, CStruct *arg1, s32 arg2) {
    register void *o __asm__("r26");
    struct { s32 sp8; char _p[4]; s32 sp10; } fr;
    s32 var_r5;
    s32 var_r6;
    register s32 *var_r28 __asm__("r28");
    register s32 temp_r27 __asm__("r27");
    s32 temp_r31;
    Unk_C6B642AC *vtbl;
    register s32 temp __asm__("r9");
    void *temp_r3;
    Unk_C8FEE62D *var_r11;
    Unk_DB0E2BAB *newnode;

    o = arg0;
    temp_r27 = arg2 & 0x324;
    if (arg1->unk0x4 & 1) {
        var_r28 = fn_80240C7C(arg1);
    } else {
        var_r28 = (s32 *)*(s32 *)((char *)fn_80240C80(arg1) + 0x14);
    }
    lbl_80306014 = 1;
    if (temp_r27 & 4) {
        temp_r31 = fn_8022DCD8(o, *var_r28, 1, 0, temp_r27);
    } else {
        temp_r31 = fn_8022DCD8(o, *var_r28, 0, 1, temp_r27);
    }
    lbl_80306014 = 0;
    fn_8000F2F8(lbl_802FFE98, fn_8023FB40());
    newnode = fn_80240E7C(Mem_Alloc2(0x30));
    fn_8000F320(lbl_802FFE98);
    newnode->unk0x0 = temp_r31;
    temp = ((Unk_DB0E2BAB *)o)->unk0x1C;
    newnode->unk0x10 = temp;
    temp = temp + 1;
    ((Unk_DB0E2BAB *)o)->unk0x1C = temp;
    newnode->unk0x14 = (s32)var_r28;
    fn_80240F28(newnode, 0, 0);
    newnode->unk0x4 |= temp_r27;
    if (fn_80241540(newnode, &fr.sp10) != 0) {
        temp_r3 = (void *)fn_800546A0(temp_r31);
        if (temp_r3 != 0) {
            var_r11 = (void *)fn_80057CA0((s32)temp_r3);
            if (var_r11 != NULL) {
                fr.sp8 = fr.sp10;
                vtbl = var_r11->unk0x14;
                ((s32 (*)(void *, void *))vtbl->unk0x3C)(
                    (char *)var_r11 + vtbl->unk0x38, &fr.sp8);
            }
        }
    }
    fn_8024077C(newnode);
    ((Unk_DB0E2BAB *)o)->unk0x0 |= 4;
    return newnode;
}
