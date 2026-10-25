// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800BD354-0x800BD438 (228B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern f32 lbl_80298E30[];
extern void *fn_801291FC(void *arg0);
void fn_800BD354(Unk_8A4B2B78 *arg0, CStruct *arg1) {
    s32 temp_r3;
    void **var_r3;
    s32 var_r8;
    register u32 var_r9 __asm__("r9");
    u16 temp_r30;
    u32 var_r7;
    f32 temp_f13;
    CStruct *temp_r10;

    temp_r3 = arg0->unk0x64;
    arg0->unk0x94 = (u16)*((volatile u32 *)&arg1->unk0x4);
    if (temp_r3 != 0) {
        Mem_Free2((void *)temp_r3);
    }
    temp_r30 = arg0->unk0x94;
    var_r3 = (void **)Mem_Alloc(temp_r30 * 0x10);
    var_r9 = temp_r30 - 1;
    if ((s32)temp_r30 != 0) {
        while (var_r9-- != 0) {
        }
    }
    __asm__ __volatile__("" : : "r"(temp_r30));
    arg0->unk0x64 = (s32)var_r3;
    var_r3 = fn_801291FC(arg1);
    var_r7 = 0U;
    if ((u32)var_r7 < (u16) arg0->unk0x94) {
        var_r8 = 0;
        temp_f13 = *lbl_80298E30;
        do {
            temp_r10 = *(void **)var_r3;
            var_r7 += 1;
            var_r3 += 1;
        *(f32 *)(var_r8 + arg0->unk0x64) = *((f32 *)&temp_r10->unk0x4);
        *(f32 *)(var_r8 + arg0->unk0x64 + (s32)0x4) = *((f32 *)&temp_r10->unk0x8);
        *(f32 *)(var_r8 + arg0->unk0x64 + (s32)0x8) = *((f32 *)&temp_r10->unk0xC);
            *(f32 *)(var_r8 + arg0->unk0x64 + (s32)0xC) = temp_f13;
            var_r8 += 0x10;
        } while (var_r7 < (u16) arg0->unk0x94);
    }
}
