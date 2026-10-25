// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F2D48-0x801F2EA0 (344B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern f32 lbl_802AE060[];

extern f32 fn_8012570C(s32, s32);

bool fn_801F2D48(Unk_13D0EFB0 *arg0, void *arg1) {
    volatile __ps_t sp8[2];
    volatile __ps_t *pv;
    struct { __ps_t p18; __ps_t p20; __ps_t p28; } fr;
    f32 temp_f31;
    f32 temp_f1;
    register f32 f8 __asm__("fr8");
    s32 count;
    s32 bound;
    s32 idx;
    s32 i;
    s32 lt;
    s32 typeIdx;
    s32 typeI;
    char *walker;
    Unk_4216A3DD *entryIdx;
    __ps_t c0;
    __ps_t c1;
    __ps_t d0;
    __ps_t d1;
    register __ps_t qv2 __asm__("fr9");
    register __ps_t pv2 __asm__("fr11");
    __ps_t sq;
    __ps_t t;
    register f32 distv __asm__("fr13");

    __asm__("" : : "m"(fr));

    temp_f31 = fn_8012570C(QB_GOALEDITOR_DEFAULTMINDISTBETWEENPOSITIONS, 0);
    temp_f1 = fn_8012570C(QB_GOALEDITOR_MINDISTBETWEENOBJECTSANDSKATER, 0);

    count = arg0->unk0x2BA;
    i = 0;
    if (i < count) {
        idx = arg0->unk0x2BB;
        __asm__("mr %0,%1" : "=r"(bound) : "r"(count));
        walker = (char *)arg0 + 0x120;
        entryIdx = (char *)arg0 + (idx << 5);
        pv = sp8;
        do {
            if (i == idx) {
                goto latch;
            }
            typeIdx = entryIdx->unk0x118;
            f8 = temp_f31;
            typeI = *(s32 *)(walker - 8);
            if ((typeIdx == 3 && typeI == 2) || (typeIdx == 2 && typeI == 3)) {
                f8 = temp_f1;
            }

            sp8[0] = ((__ps_t *)walker)[0];
            pv[1] = ((__ps_t *)walker)[1];
            *((f32 *)&((CStruct *)sp8)->unk0x4) += *((f32 *)&((Unk_42076946 *)walker)->unk0x10);
            c1 = pv[1];
            __asm__("" : "+f"(c1));
            c0 = sp8[0];
            __asm__("" : "+f"(c0));
            qv2 = ((__ps_t *)arg1)[0];
            d0 = c0 - qv2;
            pv2 = ((__ps_t *)arg1)[1];
            d1 = c1 - pv2;
            sq = __builtin_ps_mul(d1, d1);
            fr.p20 = d1;
            t = __builtin_ps_merge00(sq, ((__ps_t *)lbl_802AE060)[0]);
            d0 = __builtin_ps_madd(d0, d0, (fr.p18 = d0, t));
            d0 = __builtin_ps_sum0(d0, d0, d0);
            d0 = __builtin_ps_rsqrte(d0);
            fr.p28 = __builtin_ps_res(d0);
            {
                register f32 t28r __asm__("fr0");
                t28r = *(volatile f32 *)&fr.p28;
                __asm__("fmr %0,%1" : "=f"(distv) : "f"(t28r));
            }
            lt = (distv < f8);
            if (lt == 0) {
                goto latch;
            }
            return true;
        latch:;
            i += 1;
            walker += 0x20;
        } while (i < bound);
    }
    return false;
}
