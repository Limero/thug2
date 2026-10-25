// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020ABF8-0x8020ACB0 (184B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8020ABF8(Unk_90685748 *arg0) {
    register s32 idx __asm__("r10");
    register s32 h __asm__("r11");
    register s32 root __asm__("r8");
    s32 n;
    s32 ctr;
    s32 k;
    s32 off;
    char *walker;

    n = arg0->unk0x99C;
    idx = arg0->unk0x99E;
    if (n > 0xA) {
        n = 0xA;
    }
    if (n == 0) {
        return;
    }
    root = QB_DOWNRIGHT;
    off = idx * 0x18 + 0x40;
    walker = (char *)(off + (s32)arg0);
    ctr = n;
    do {
        h = ((Unk_4C649A8C *)walker)->unk0x4;
        if (h == root) {
            goto L_next;
        }
        if ((u32)h <= (u32)root) {
            k = QB_SQUARE;
            if (h == k) {
                goto L_next;
            }
            if ((u32)h <= (u32)k) {
                __asm__ volatile("lis %0,%1\n\tori %0,%0,%2"
                    : "=r"(k) : "i"(0x2068), "i"(0x9278));
                goto L_merge;
            }
            __asm__ volatile("lis %0,%1\n\tori %0,%0,%2"
                : "=r"(k) : "i"(0x6bf8), "i"(0xa7f4));
            goto L_merge;
        }
        k = QB_WHITE;
        if (h == k) {
            goto L_next;
        }
        if ((u32)h > (u32)k) {
            goto L_next;
        }
        k = QB_UPRIGHT;
L_merge:
        __asm__("cmpw %0,%1" : : "r"(h), "r"(k));
L_next:
        walker -= 0x18;
        idx -= 1;
        if (idx < 0) {
            walker += 0x960;
            idx += 0x64;
        }
    } while (--ctr != 0);
}
