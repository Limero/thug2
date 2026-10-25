// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007EE94-0x8007EF44 (176B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern Unk_9994C3F5 *lbl_802FFE98;
extern f32 lbl_80296254;
void fn_80003830(void *, void *, f32, f32, f32);
void fn_8000F2F8(void *, s32);
void fn_8000F320(void *);
void *Mem_Alloc2(s32);
void *fn_8007DF14(void *);
s32 fn_80062394(void *);
void *fn_80093E4C(void *, void *, void *, s32, s32);

// Dead saved-register slot: retail's stmw r25,0x4c(r1) + LR at 0x6c means
// r25..r31 are all saved and r31 is never referenced. File scope only.
register s32 g31 __asm__("r31");

bool fn_8007EE94(Unk_C7387A53 *arg0, Unk_FFAD6788 *arg1, Unk_9994C3F5 *arg2) {
    f32 sp8[16];
    register f32 t1 __asm__("fr1");
    f32 t2;
    f32 t3;
    s32 r26;
    register s32 a7 __asm__("r7");
    Unk_9994C3F5 *mgr;
    Unk_31DE137E *node;
    Unk_31DE137E *nd;
    register s32 a1 __asm__("r30");

    a1 = (s32)arg1;
    t1 = lbl_80296254;
    t2 = t1;
    t3 = t2;
    r26 = arg2->unk0x8;
    fn_80003830(sp8, (void *)a1, t1, t2, t3);
    mgr = lbl_802FFE98;
    arg0->unk0x34 = (s32)a1;
    fn_8000F2F8(mgr, mgr->unk0x118);
    nd = (Unk_31DE137E *)Mem_Alloc2(0x70);
    node = (Unk_31DE137E *)fn_80093E4C(nd, fn_8007DF14(((Unk_FFAD6788 *)a1)->unk0xC8), sp8, r26, (a7 = fn_80062394(arg2)));
    fn_8000F320(lbl_802FFE98);
    arg0->unk0x30 = (s32)node;
    node->unk0x60 = arg2;
    return true;
}
