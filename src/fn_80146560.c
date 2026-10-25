// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80146560-0x8014687C (796B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
void fn_80146560(void *arg0, void *arg1) {
    f32 sp8[16];
    f32 sp48[16];
    s32 sp88;
    s32 var_ctr;
    f32 *vin;
    f32 *m;
    __ps_t *ps_dst;
    __ps_t *ps_src;

    var_ctr = 4;
    do {
        var_ctr -= 1;
    } while (var_ctr != 0);
    sp88 = (s32)arg0;
    __asm__("" ::: "memory");
    ((Unk_59AB5482 *)&sp88)->unk0x4 = (s32)arg1;
    vin = *(f32 **)&sp88;
    m = (f32 *)arg1;
    sp48[0] = vin[0] * m[0] + vin[1] * m[4] + vin[2] * m[8] + vin[3] * m[12];
    sp48[1] = vin[0] * m[1] + vin[1] * m[5] + vin[2] * m[9] + vin[3] * m[13];
    sp48[2] = vin[0] * m[2] + vin[1] * m[6] + vin[2] * m[10] + vin[3] * m[14];
    sp48[3] = vin[0] * m[3] + vin[1] * m[7] + vin[2] * m[11] + vin[3] * m[15];
    sp48[4] = vin[4] * m[0] + vin[5] * m[4] + vin[6] * m[8] + vin[7] * m[12];
    sp48[5] = vin[4] * m[1] + vin[5] * m[5] + vin[6] * m[9] + vin[7] * m[13];
    sp48[6] = vin[4] * m[2] + vin[5] * m[6] + vin[6] * m[10] + vin[7] * m[14];
    sp48[7] = vin[4] * m[3] + vin[5] * m[7] + vin[6] * m[11] + vin[7] * m[15];
    sp48[8] = vin[8] * m[0] + vin[9] * m[4] + vin[10] * m[8] + vin[11] * m[12];
    sp48[9] = vin[8] * m[1] + vin[9] * m[5] + vin[10] * m[9] + vin[11] * m[13];
    sp48[10] = vin[8] * m[2] + vin[9] * m[6] + vin[10] * m[10] + vin[11] * m[14];
    sp48[11] = vin[8] * m[3] + vin[9] * m[7] + vin[10] * m[11] + vin[11] * m[15];
    sp48[12] = vin[12] * m[0] + vin[13] * m[4] + vin[14] * m[8] + vin[15] * m[12];
    sp48[13] = vin[12] * m[1] + vin[13] * m[5] + vin[14] * m[9] + vin[15] * m[13];
    sp48[14] = vin[12] * m[2] + vin[13] * m[6] + vin[14] * m[10] + vin[15] * m[14];
    sp48[15] = vin[12] * m[3] + vin[13] * m[7] + vin[14] * m[11] + vin[15] * m[15];
    ps_dst = (__ps_t *)sp8;
    ps_src = (__ps_t *)sp48;
    ps_dst[0] = ps_src[0];
    ps_dst[1] = ps_src[1];
    ps_dst[2] = ps_src[2];
    ps_dst[3] = ps_src[3];
    ps_dst[4] = ps_src[4];
    ps_dst[5] = ps_src[5];
    ps_dst[6] = ps_src[6];
    ps_dst[7] = ps_src[7];
}
