// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A5CF0-0x801A5D88 (152B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void *lbl_802FFE98;
void fn_8000F2F8(Unk_9F352E7C *, s32);
void fn_8000F320(Unk_F12C5E01 *);
s32 fn_801A5DAC(void *, s32);
s32 fn_801A44E8(s32, s32);
void fn_801A5CF0(void *arg0, s32 arg1) {
    register s32 a0 __asm__("r31");
    register s32 a1 __asm__("r29");
    Unk_B0F19D72 *mgr;
    s32 nv;
    s32 old;
    s32 idx;
    s32 *b;

    a0 = (s32)arg0;
    a1 = arg1;
    mgr = lbl_802FFE98;
    fn_8000F2F8(mgr, mgr->unk0x5F8);
    idx = ((Unk_C7387A53 *)a0)->unk0x24;
    if (idx == 0) {
        nv = fn_801A5DAC((void *)a0, a1);
        b = (s32 *)((char *)a0 + 0x1C);
        b[((Unk_C7387A53 *)a0)->unk0x24] = nv;
    } else {
        b = (s32 *)((char *)a0 + 0x1C);
        old = b[idx];
        fn_801A44E8(old, fn_801A5DAC((void *)a0, a1));
    }
    fn_8000F320(lbl_802FFE98);
}
