// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80058A70-0x80058B48 (216B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_8005872C(void *);
extern char lbl_802FFE98[];
#include "structs.h"
typedef struct VT_7A53 {
    char pad0x0[0x20];
    s16 unk0x20;
    char pad0x22[0x2];
    void (*unk0x24)(void *);
} VT_7A53;
s32 Mem_Alloc(s32);
extern char lbl_802933B8[];
extern char lbl_802FFE98[];
void fn_8000F2F8(s32, s32);
void fn_8000F320(Unk_F12C5E01 *self);
void fn_80058A70(CStruct *arg0, s32 arg1, f32 farg0) {
    volatile double _dummy;
    s32 var_r29;
    void *temp_r30;
    Unk_89783F6B *temp_r3;
    VT_7A53 *temp_r9;
    void *var_r31;

    if ( arg0->unk0x4 == NULL) {
        var_r29 = 0x5F;
        temp_r3 = *(void **)lbl_802FFE98;
        fn_8000F2F8(temp_r3, temp_r3->unk0x124);
        temp_r30 = Mem_Alloc(0x3C8) + 8;
        *(s32 *)((char *)temp_r30 - 0x8) = 0x60;
        var_r31 = temp_r30;
        do {
            fn_8005872C(var_r31);
            var_r31 += 0xA;
        } while (--var_r29 != -1);
        {
            /* sandwich: want [lis r9,@ha][stw r30,4(r28)][lwz r3,@l(r9)][bl]
               — every plain form materializes the whole call arg AFTER the
               store. pins are block-scoped (die at }), recipe 6as/70-144. */
            register s32 pg __asm__("r9");
            register s32 g320 __asm__("r3");
            __asm__ volatile("lis %0,%1@ha" : "=r"(pg) : "s"(lbl_802FFE98) : "memory");
            arg0->unk0x4 = temp_r30;
            __asm__ volatile("lwz %0,%1@l(%2)" : "=r"(g320) : "s"(lbl_802FFE98), "r"(pg) : "memory");
            fn_8000F320((Unk_F12C5E01 *)g320);
        }
    }
    *(u16 *)((char *)((arg1 * 0xA) + arg0->unk0x4) + 0x8) = (s16) (farg0 * *(f32 *)(s32)lbl_802933B8);
    temp_r9 = *(VT_7A53 **)((char *)arg0 + 0x50);
    temp_r9->unk0x24((char *)arg0 + temp_r9->unk0x20);
}
