// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013465C-0x801347CC (368B). Byte-identical.
#include "types.h"
#include "structs.h"

extern s32 lbl_802FFE98;
extern void *fn_80125480(s32);
extern void *fn_80134CD8(void *, s32 *, s32);
extern void fn_80134524(CScript *, Unk_C8FEE62D *);
extern void fn_801345DC(void *, s32, u32);
extern void fn_80134D2C(s32);
extern void *fn_80134348();
extern s32 fn_8000F2F8(Unk_9F352E7C *, s32);
extern void fn_8000F320(Unk_F12C5E01 *);
extern void *Mem_Alloc_3(u32);
extern void fn_8000AF90(u8 *, u8 *, u32);
extern void fn_8012C8F0(void *);
extern void fn_80134D7C(CStruct *, s32 *, void *);

u8 *fn_8013465C(CScript *arg0, s32 arg1) {
    s32 sp8;
    u8 temp_r0;
    u32 temp_r26;
    u32 temp_r31;
    CStruct *temp_r27;
    Unk_F8A5095F *temp_r28;
    void *temp_r29;
    CStruct *temp_r30;
    CStruct *temp_r9;
    register void *var_r3 __asm__("r3");
    register void *var_r9 __asm__("r9");
    register u32 var_r10 __asm__("r10");
    register void *var_r11 __asm__("r11");

    sp8 = arg1;
    temp_r28 = fn_80125480(arg1);
    if (temp_r28 != NULL) {
        if (((Unk_ECD1B899 *)temp_r28)->unk0x2 != 7) {
            return NULL;
        }
        sp8 = *((s32 *)&temp_r28->unk0x4);
    }
    temp_r30 = fn_80134CD8(arg0->unk0x18, &sp8, 1);
    if (temp_r30 != NULL) {
        temp_r30->unk0xC += 1;
        fn_80134524(arg0, temp_r30);
        return *((void * *)&temp_r30->unk0x8);
    }
    if (temp_r28 != NULL) {
        temp_r9 = temp_r28->unk0xC;
        temp_r31 = *((u32 *)&temp_r9->unk0x4);
        temp_r26 = *((u32 *)&temp_r9->unk0x8);
        fn_801345DC(arg0, temp_r31, sp8);
        fn_80134D2C(0x18);
        temp_r27 = fn_80134348();
        fn_8000F2F8((void *)lbl_802FFE98, ((Unk_C7387A53 *)lbl_802FFE98)->unk0x12C);
        temp_r29 = Mem_Alloc_3(temp_r31);
        fn_8000F320((void *)lbl_802FFE98);
        if (temp_r31 > temp_r26) {
            fn_8000AF90(temp_r28->unk0xC + (s32)0x20, (void *)temp_r29, temp_r26);
        } else {
            var_r10 = 0U;
            var_r11 = temp_r29;
            var_r9 = temp_r28->unk0xC;
            var_r3 = (char *)var_r9 + (s32)0x20;
            if (var_r10 < temp_r31) {
                do {
                    temp_r0 = *(u8 *)var_r3;
                    var_r10 += 1;
                    var_r3 += 1;
                    *(u8 *)var_r11 = temp_r0;
                    var_r11 += 1;
                } while (var_r10 < temp_r31);
            }
        }
        fn_8012C8F0(temp_r29);
        temp_r27->unk0x8 = (s32)temp_r29;
        temp_r27->unk0xC = 1;
        temp_r27->unk0x4 = sp8;
        fn_80134D7C(arg0->unk0x18, &sp8, temp_r27);
        return *((void * *)&temp_r27->unk0x8);
    }
    return NULL;
}
