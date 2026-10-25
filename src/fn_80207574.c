// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80207574-0x8020773C (456B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern s32 fn_800145AC(void);
extern void fn_80207080(Unk_90685748 *, s32);
extern void fn_8020740C(void *, s32 *);
bool fn_80207574(void *arg0, void *arg1, s32 arg2) {
    Unk_41EA2015 *a1;
    s32 a2;
    s32 msk;
    s32 i;
    s32 state;
    s32 snap;
    s32 idx;
    register s32 a0 __asm__("r28");
    s32 off;
    s32 pr;
    s32 ts;
    s32 count;
    s32 t44;
    s32 prod;
    s32 lim;

    a0 = (s32)arg0;
    i = 0;
    count = ((Unk_38E1A68E *)a0)->unk0x99C;
    a1 = (s32)arg1;
    a2 = arg2;
    msk = 0x100;
    idx = ((Unk_38E1A68E *)a0)->unk0x99E;
    state = 0;
    snap = 0;
    if (i < count) {
        prod = idx * 0x18;
        t44 = prod + 0x44;
        __asm__ volatile("mr %0,%1" : "=&r"(off) : "r"(prod));
        pr = t44 + a0;
        do {
        
            s32 v;
            s32 v1;
            s32 v2;
            s32 *q40a;
            s32 *q40b;
            s32 ts1;
            s32 ts2;

            /* want: addi r9,r28,0x3c; lwzx r30,r9,r27 — force the indexed
               form; plain C folds to add+lwz (doc-49 strength-reduction). */
            {
                register s32 t9 __asm__("r9");
                __asm__ volatile("addi %0, %1, 0x3c" : "=r"(t9) : "r"(a0));
                __asm__ volatile("lwzx %0, %1, %2" : "=r"(ts) : "r"(t9), "r"(off));
            }
            lim = 0x3E8;
            if ((u32)(fn_800145AC() - ts) >= (u32)lim) {
                return false;
            }
            switch (state) {
            case 0:
                if ((((Unk_1D62F22E_2 *)pr)->unk0xC & msk) == 0) {
                    v = *(s32 *)(pr - 4);
                    if (v == 1 && *(s32 *)pr == a1->unk0x4) {
                        ((Unk_1D62F22E_2 *)pr)->unk0x8 = v;
                        state = 1;
                        snap = idx;
                    }
                }
                break;
            case 1:
                if (snap - idx > 2) {
                    return false;
                }
                v1 = *(s32 *)(pr - 4);
                q40a = (s32 *)(a0 + 0x40);
                if (v1 == 2 && *(s32 *)pr == ((Unk_59AB5482_2 *)a1)->unk0x8) {
                    return false;
                }
                if ((((Unk_1D62F22E_2 *)pr)->unk0xC & msk) == 0) {
                    ts1 = *(s32 *)((char *)q40a + off);
                    if (ts1 == 1 && *(s32 *)pr == a1->unk0x0) {
                        ((Unk_1D62F22E_2 *)pr)->unk0x8 = ts1;
                        state = 2;
                    }
                }
                break;
            case 2:
                v2 = *(s32 *)(pr - 4);
                q40b = (s32 *)(a0 + 0x40);
                if (v2 == 2 && *(s32 *)pr == ((Unk_59AB5482_2 *)a1)->unk0x8) {
                    return false;
                }
                ts2 = *(s32 *)((char *)q40b + off);
                if ((ts2 == 1 && *(s32 *)pr == ((Unk_59AB5482_2 *)a1)->unk0x8) || a2 != 0) {
                    fn_80207080(a0, 0x100);
                    fn_8020740C(a0, a1);
                    return true;
                }
                break;
            }
            pr -= 0x18;
            off -= 0x18;
            if (--idx < 0) {
                pr += 0x960;
                off += 0x960;
                idx += 0x64;
            }
            count = ((Unk_38E1A68E *)a0)->unk0x99C;
            i++;
        } while (i < count);
    }
    return false;
}
