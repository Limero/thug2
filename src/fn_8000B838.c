// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000B838-0x8000B934 (252B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_802901F0[];
extern char lbl_80290208[];
extern char lbl_80290238[];
extern void *Mem_NewZero(s32);
extern void *fn_80009B04(void *, void *);
extern Unk_7C9BF17E *fn_8000B7F0(CScript *, s32, s32, s32);
extern void fn_8000B6F8(Unk_C7387A53 *);
extern void fn_8000C5A4(Unk_7C9BF17E *);
void *fn_8000B838(CScript *arg0) {
    Unk_C8FEE62D *temp_r28;
    Unk_C8FEE62D *temp_r29;
    Unk_C8FEE62D *temp_r31;
    Unk_7C9BF17E *temp_r3;
    CStruct *temp_r9;
    s32 prev;
    register s32 temp_r0 __asm__("r0");
    register s32 temp_r11 __asm__("r11");
    register s32 temp_r9_addr __asm__("r9");
    void (*temp_r30)(Unk_C7387A53 *);
    s32 var_r25;
    s32 var_r26;
    s32 var_r30;

    temp_r29 = (Unk_C8FEE62D *)((char *)arg0 + 4);
    arg0->unk0x20 = (s32)lbl_802901F0;
    temp_r29->unk0xC = (s32)temp_r29;
    temp_r29->unk0x10 = (s32)temp_r29;
    temp_r0 = -1;
    __asm__("li %0,0" : "=&r"(temp_r11));
    temp_r9_addr = (s32)lbl_80290208;
    temp_r29->unk0x14 = temp_r9_addr;
    __asm__("mr %0,%1" : "=&r"(temp_r31) : "r"(temp_r29));
    temp_r29->unk0x4 = temp_r0, var_r25 = 0, temp_r29->unk0x8 = temp_r11;
    var_r26 = 0;
    temp_r28 = (Unk_C8FEE62D *)Mem_NewZero(0x24);
    temp_r30 = fn_8000B6F8;
    fn_80009B04(temp_r28, 0);
    temp_r28->unk0x1C = (s32)temp_r30;
    temp_r28->unk0x20 = (s32)temp_r29;
    temp_r28->unk0x18 = (s32)lbl_80290238;
    arg0->unk0x1C = (s32)temp_r28;
    do {
        for (var_r30 = 0; var_r30 <= 0; var_r30++) {
            temp_r3 = fn_8000B7F0(arg0, var_r25, var_r26, var_r30);
            if (temp_r3 != NULL) {
                temp_r9 = (CStruct *)temp_r3->unk0x4;
                var_r25 += 1;
                prev = temp_r31->unk0x10;
                temp_r9->unk0xC = (s32)temp_r31;
                temp_r9->unk0x10 = prev;
                *(s32 *)(temp_r31->unk0x10 + 0xC) = (s32)temp_r9;
                temp_r31->unk0x10 = (s32)temp_r9;
                fn_8000C5A4(temp_r3);
            }
        }
        var_r26 += 1;
    } while (var_r26 <= 3);
    return arg0;
}
