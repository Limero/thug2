// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802566E0-0x802568C0 (480B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern s32 fn_80253C60(Unk_C7387A53 * pool, s32 size);
extern s32 fn_80258840(s32 a, s32 b);
extern s32 fn_80258938(CStruct * a, s32 * b, s32 c, s32 d, s32 e, s32 f);

// Vtable0x8030804C method 14: interleaved vertex-data array builder.
// Walks per-plane/per-row data blocks (stride math from t1s header, row-mask
// selection via mbases bit test), fills a scratch array and streams rows
// through fn_80258938; returns 0 on full-scan or -1 errors.
// FIX (sweep): moved the asm volatile barrier ABOVE `vlak = 0` so the
// plane==0 cr4 compare is emitted before the independent li (WANT order).
bool Vtable0x8030804C_m14(s32 arg0, void *arg1, s32 arg2, s32 *arg3, s32 arg4) {
    register s32 dataoff __asm__("r14");
    register s32 vlak __asm__("r17");
    register s32 plane __asm__("r18");
    register s32 t1s __asm__("r19");
    register s32 cnt __asm__("r20");
    register s32 t2s __asm__("r21");
    register s32 v2 __asm__("r22");
    register s32 mbases __asm__("r23");
    register s32 dc __asm__("r24");
    register s32 arrks __asm__("r26");
    register s32 a1s __asm__("r27");
    register s32 dof __asm__("r28");
    register s32 rows __asm__("r29");
    register s32 k __asm__("r30");
    s32 quot;
    volatile s32 a2;
    s32 * volatile arr;
    s32 rowoff;
    register s32 cps __asm__("r11");

    a1s = (s32)arg1;
    t1s = *(s32 *)a1s;
    cps = *(s32 *)(a1s + 0x10);
    a2 = arg2;
    k = 0;
    t2s = *(s32 *)((char *)t1s + 8);
    quot = (*(s32 *)((char *)t1s + 4) - *(s32 *)((char *)t1s)) / t2s;
    cnt = *(s32 *)cps;
    arr = fn_80253C60(arg0, ((quot + cnt - 1) / cnt) * 4);
    __asm__ volatile("" ::: "memory");

    if (k < arg4 && *(s32 *)arg3 == 0) {
        s32 *p4 = arg3;

        do {
            k += 1;
        } while (k < arg4 && *++p4 == 0);
    }
    if (k == arg4) {
        return false;
    }

    __asm__("li %0,0" : "=r"(plane));
    if (plane < *(s32 *)(a1s + 8)) {
        dataoff = 0;
        do {
        __asm__ volatile("li %0,0" : "=r"(k));
        if (k < quot) {
            arrks = (s32)arr;
            __asm__("" : "+r"(arrks));
        __asm__ volatile("");
            vlak = 0;
        mid_head:
            if (plane == 0) {
                s32 idx = fn_80258840(*(s32 *)(a1s + 0x10), arg0 + 4);

                if (idx == -1) {
                    return false;
                }
                {
                    register s32 shw __asm__("r9");
                    s32 *tbl;

                    __asm__("slwi %0,%1,2" : "=r"(shw) : "r"(idx));
                    tbl = *(s32 **)(a1s + 0x1c);
                    if ((*(s32 *)arrks = *(s32 *)((char *)(shw + (s32)tbl))) == 0) {
                        return false;
                    }
                }
            }
            rows = 0;
            if (rows < cnt && k < quot) {
                rowoff = k * t2s;
                __asm__("mr %0,%1" : "=r"(v2) : "r"(vlak));
                mbases = (s32)((char *)t1s + 0x14);
                __asm__("mr %0,%1" : "=r"(dc) : "r"(dataoff));
                dof = 0;
            inner_head:
                {
                    s32 v = *(s32 *)((char *)arr + v2);
                    register s32 d1w __asm__("r11");
                    s32 mw;
                    s32 d2c;

                    d1w = *(s32 *)((char *)(dof + v));
                    d1w <<= 2;
                    mw = *(s32 *)((char *)mbases + d1w);
                    if (((mw >> plane) & 1) != 0) {
                        {
                            register s32 mav __asm__("r9");

                            mav = *(s32 *)(a1s + 0x14);
                            d1w = *(s32 *)((char *)(d1w + mav));
                        }
                        d2c = *(s32 *)((char *)(dc + d1w));

                        if (d2c != 0) {
                            if (fn_80258938(d2c, a2, rowoff + *(s32 *)((char *)t1s + 0), arg4, arg0 + 4, t2s) == -1) {
                                return false;
                            }
                        }
                    }
                }
                rows += 1;
                dof += 4;
                rowoff += t2s;
                k += 1;
                if (rows >= cnt) {
                    goto k_latch;
                }
                if (k < quot) {
                    goto inner_head;
                }
            }
        k_latch:
            vlak += 4;
            arrks += 4;
            if (k < quot) {
                goto mid_head;
            }
        }
        plane += 1;
        dataoff += 4;
        } while (plane < *(s32 *)(a1s + 8));
    }
    return false;
}
