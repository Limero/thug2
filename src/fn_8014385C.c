// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8014385C-0x801439C0 (356B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_8029F890[];
extern char lbl_8029F940[];
void fn_8000C868(Unk_A0A7249E *);
void fn_8000C938(Unk_5031FAD7 *);
void fn_80143AF4(Unk_3DDEEB97 *);
void Script_RunScript(s32, s32, void *, s32, s32);
s32 fn_80141988(Unk_C7387A53 *);
void fn_800092B0(Unk_9994C3F5 *, s32);
void fn_8009F7A4(Unk_6A70655D *, s32);
void fn_8014385C(Unk_15257920 *arg0, s32 arg1) {
    Unk_C7387A53 *temp_r11;
    s32 temp_r28;
    s32 temp_r31;
    Unk_B1C93D59 *temp_r9;
    char *temp_r27;
    Unk_C8FEE62D *temp_r29;
    Unk_9994C3F5 *temp_r3;

    arg0->unk0x8 = (s32)lbl_8029F890;
    if (((s32) arg0->unk0x354 != 0) && ((s32) arg0->unk0xC8 != 0) && (arg0->unk0x290 != NULL)) {
        fn_8000C868(*(s32 *)((char *)(*(s32 *)((char *)(arg0->unk0x290) + (s32)0x51C)) + (s32)0x20));
        fn_8000C938(*(s32 *)((char *)(*(s32 *)((char *)(arg0->unk0x290) + (s32)0x51C)) + (s32)0x20));
    }
    temp_r29 = (char *)arg0 + (s32)0x260;
    fn_80143AF4(arg0);
    temp_r27 = (char *)arg0 + (s32)0x170;
    Script_RunScript(QB_DESTROYSKATERPARTICLES, 0, arg0, 0, 0);
    temp_r31 = (s32)arg0 + (s32)0x194;
    temp_r28 = (s32)arg0 + (s32)0x1BC;
    do {
        temp_r11 = *(void **)temp_r31;
        temp_r31 += 4;
        if (temp_r11 != NULL) {
            temp_r9 = temp_r11->unk0xC;
            temp_r9->unk0xC((char *)temp_r11 + temp_r9->unk0x8, 3);
        }
    } while (temp_r31 <= temp_r28);
    if (((s32) arg0->unk0xC8 != 0) && ((s32) arg0->unk0x2E8 == 1)) {
        temp_r3 = fn_80141988(arg0);
        if (temp_r3 != NULL) {
            temp_r9 = temp_r3->unk0x8;
            temp_r9->unk0x3C((char *)temp_r3 + temp_r9->unk0x38);
        }
    }
    temp_r29->unk0x14 = (s32)lbl_8029F940;
    *(s32 *)(temp_r29->unk0x10 + (s32)0xC) = temp_r29->unk0xC;
    *(s32 *)(temp_r29->unk0xC + (s32)0x10) = temp_r29->unk0x10;
    temp_r29->unk0xC = (s32)temp_r29;
    temp_r29->unk0x10 = (s32)temp_r29;
    fn_800092B0((s32)temp_r27, 2);
    fn_8009F7A4((s32)arg0, arg1);
}
