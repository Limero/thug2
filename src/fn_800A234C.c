// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A234C-0x800A2430 (228B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern s32 lbl_80290628;
extern u32 lbl_80301A44;
extern u32 lbl_80301A48;

void fn_800A27BC(void *);
void fn_8009FD6C(void *);
s32 fn_800A2954(s32);
s32 fn_800A29DC(void);
s32 Mem_Alloc(s32);
void fn_800A28A4(void);

void fn_800A234C(Unk_107C2266 *arg0) {
    u32 val;
    u32 step;
    u32 cur;
    u32 d;
    u32 rem;
    u32 step2;

    if (arg0->unk0x110 == 0) {
        fn_800A27BC(arg0);
        return;
    }
    if (fn_800A2954(0) != 0) {
        fn_8009FD6C(arg0);
        arg0->unk0x118 += fn_800A29DC();
        if (fn_800A2954(0) != 0) {
            {
                u32 *pg;
                __asm__ volatile("lis %0,%1@ha" : "=r"(pg) : "s"(&lbl_80301A44));
                val = *(volatile u32 *)&arg0->unk0x118;
                __asm__ volatile("");
                step = *(volatile u32 *)((char *)pg + 0x1A44);
            }
            rem = (val / step + 1) * step;
            rem -= val;
            rem -= lbl_80290628;
            if (rem != 0) {
                rem = Mem_Alloc(rem);
            }
            arg0->unk0x11C = rem;
            arg0->unk0x118 += fn_800A29DC();
            step2 = *(u32 *)&lbl_80301A44;
            cur = *(u32 *)&lbl_80301A48;
            d = arg0->unk0x118 / step2;
            if (d < cur) {
                d = cur;
            }
            lbl_80301A48 = d;
        }
    } else {
        fn_800A28A4();
    }
}
