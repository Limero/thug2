// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80198190-0x80198278 (232B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void* lbl_802FFE98;
extern char lbl_802AA808[];

extern void fn_801980C4(CScript * arg0);
extern s32 GetArray(CStruct * arg0, s32 arg1, s32 *arg2, s32 arg3);
extern void fn_8000F2F8(Unk_9F352E7C * arg0, s32 arg1);
extern s32 fn_80129528(CStruct * arg0, s32 arg1);
extern s32 fn_80199C44(CStruct * arg0);
extern s32 Mem_NewZero(s32 arg0);
extern void fn_8000F320(Unk_F12C5E01 * arg0);

void fn_80198190(s32 arg0) {
    s32 sp8;
    Unk_B0F19D72 *temp_r3;
    Unk_C8FEE62D *temp_r3_2;
    s32 temp_r30;
    s32 idx;
    s32 next;
    u32 var_r29;
    register s32 anchor __asm__("r9");
    register s32 lblbase __asm__("r27");
    register s32 zerov __asm__("r28");

    fn_801980C4(arg0);
    if (GetArray((char *)arg0 + 4, QB_VICTORY_CONDITIONS, &sp8, 0) != 0) {
        var_r29 = 0U;
        temp_r3 = lbl_802FFE98;
        fn_8000F2F8(temp_r3, temp_r3->unk0x5F8);
        if (var_r29 < *((u32 *)&((CStruct *)sp8)->unk0x4)) {
            __asm__ __volatile__("");
            __asm__ volatile("lis %0,%1@ha" : "=r"(anchor) : "s"(lbl_802AA808));
            arg0 = (s32)((char *)arg0 + 0xC);
            __asm__("" : "+r"(arg0));
            lblbase = anchor - 0x57F8;
            zerov = 0;
            do {
                temp_r30 = fn_80199C44(fn_80129528(sp8, (idx = var_r29, var_r29 += 1U, idx)));
                temp_r3_2 = Mem_NewZero(0x18);
                *((volatile s32 *)&temp_r3_2->unk0xC) = temp_r3_2;
                *((volatile s32 *)&temp_r3_2->unk0x10) = temp_r3_2;
                temp_r3_2->unk0x4 = temp_r30;
                temp_r3_2->unk0x14 = lblbase;
                temp_r3_2->unk0x8 = zerov;
                temp_r3_2->unk0xC = (next = ((CStruct *)arg0)->unk0x10, arg0);
                temp_r3_2->unk0x10 = next;
                *(s32 *)(((CStruct *)arg0)->unk0x10 + 0xC) = temp_r3_2;
                ((CStruct *)arg0)->unk0x10 = temp_r3_2;
            } while (var_r29 < *((u32 *)&((CStruct *)sp8)->unk0x4));
        }
        fn_8000F320(lbl_802FFE98);
    }
}
