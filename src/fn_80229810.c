// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80229810-0x8022986C (92B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802FFE98[];
extern void fn_8000F2F8(Unk_9F352E7C * arg0, s32 arg1);
extern void fn_8000F320(Unk_F12C5E01 * arg0);
extern s32 Mem_NewZero(s32 arg0);
extern s32 fn_801A44A0(void *arg0);
extern void fn_801A44E8(void *arg0, void *arg1);
void fn_80229810(void *arg0, s32 arg1) {
    register void *a0 __asm__("r28");
    register s32 a1 __asm__("r30");
    Unk_B0F19D72 *mgr;
    s32 mgr2;
    register s32 pg __asm__("r29");

    __asm__ volatile("lis %0,%1@ha" : "=r"(pg) : "s"(lbl_802FFE98));
    a0 = arg0;
    __asm__ volatile("lwz %0,%1@l(%2)" : "=r"(mgr) : "s"(lbl_802FFE98), "r"(pg));
    a1 = (s32)arg1;
    fn_8000F2F8((void *)mgr, mgr->unk0x5F8);
    ((Unk_C7387A53 *)a0)->unk0x50 = fn_801A44A0((void *)Mem_NewZero(0x74));
    fn_801A44E8(((Unk_C7387A53 *)a0)->unk0x50, (void *)a1);
    __asm__ volatile("lwz %0,%1@l(%2)" : "=r"(mgr2) : "s"(lbl_802FFE98), "r"(pg));
    fn_8000F320((void *)mgr2);
}
