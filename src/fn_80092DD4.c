// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80092DD4-0x80092EA4 (208B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_803017F0;
extern u32 lbl_803017F4;
extern char lbl_803792E0[];
bool fn_80092DD4(f32 *arg0, s32 arg1) {
    u32 count = lbl_803017F4;
    register u32 i __asm__("r10") = 0;
    u32 offset;
    u32 limit;
    u32 slot;
    char *base;
    char *ctr_base;
    s32 *counter;

    if (i < count) {
        base = lbl_803792E0;
        ctr_base = base + 0x50;
        __asm__("mr %0,%1" : "=r"(limit) : "r"(count));
        slot = lbl_803017F0 << 2;
        offset = 0;
        counter = (s32 *)(ctr_base + slot);
        __asm__ __volatile__("" ::: "memory");
        do {
            s32 hit = 1;
            f32 neg = -arg0[3];
            register f32 x __asm__("fr7") = arg0[0];
            register f32 y __asm__("fr9") = arg0[1];
            register f32 z __asm__("fr10") = arg0[2];
            f32 *rows = (f32 *)((char *)offset + (s32)base);
            s32 k = 5;

            do {
                if (rows[0] * x + rows[1] * y + rows[2] * z - rows[3] >= neg) {
                    hit = 0;
                    break;
                }
                rows += 4;
            } while (--k != 0);

            if (hit != 0) {
                *counter += arg1;
                return true;
            }
            i++;
            counter = (s32 *)((char *)counter + 0x60);
            offset += 0x60;
        } while (i < limit);
    }
    return false;
}
