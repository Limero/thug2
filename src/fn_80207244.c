// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80207244-0x80207350 (268B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_800145AC(void);
bool fn_80207244(void *arg0, s32 arg1, s32 arg2, u32 arg3, s32 arg4) {
    register s32 a0 __asm__("r27");
    register s32 i __asm__("r28");
    register s32 a1 __asm__("r20");
    register s32 a2 __asm__("r21");
    register s32 a3 __asm__("r22");
    register s32 a4 __asm__("r23");
    register s32 fA __asm__("r24");
    register s32 fB __asm__("r25");
    register s32 fC __asm__("r26");
    register s32 idx __asm__("r29");
    register s32 t __asm__("r30");
    register s32 pr __asm__("r31");
    s32 count;
    s32 v;
    s32 w;
    s32 off;

    a0 = (s32)arg0;
    i = 0;
    count = ((Unk_38E1A68E *)a0)->unk0x99C;
    a1 = arg1;
    a2 = arg2;
    a3 = (s32)arg3;
    a4 = arg4;
    fA = 0;
    fB = 0;
    fC = 0;
    idx = ((Unk_38E1A68E *)a0)->unk0x99E;
    if (i < count) {
        off = idx * 0x18 + 0x4C;
        pr = off + a0;
        do {
            t = *(s32 *)(pr - 0x10);
            if ((u32)(fn_800145AC() - t) >= (u32)a3) {
                return false;
            }
            if ((((Unk_4C649A8C *)pr)->unk0x4 & a4) == 0) {
                v = *(s32 *)(pr - 0xC);
                if (v == 1) {
                    w = *(s32 *)(pr - 8);
                    if (w == a1) {
                        *(s32 *)pr = v;
                        if (fB != 0) {
                            return true;
                        }
                        fA = 1;
                        fC = 1;
                    } else if (w == a2) {
                        *(s32 *)pr = v;
                        if (fA != 0) {
                            return true;
                        }
                        fB = 1;
                        fC = 1;
                    } else if (fC != 0) {
                        return false;
                    }
                }
            }
            pr -= 0x18;
            if (--idx < 0) {
                pr += 0x960;
                idx += 0x64;
            }
            count = ((Unk_38E1A68E *)a0)->unk0x99C;
            i++;
        } while (i < count);
    }
    return false;
}
