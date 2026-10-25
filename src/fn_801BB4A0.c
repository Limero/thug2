// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801BB4A0-0x801BB7DC (828B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

void *fn_80003E0C(void *arg0);

void fn_801BB4A0(f32 *arg0) {
    struct {
        s32 _08;
        char pad[0x3C];
        f32 t[16];
        void *mp;
        void *argcopy;
    } fr;
    __ps_t *dp;
    f32 *m;
    char *bp;
    s32 i;

    for (i = 0; i < 4; i++) {
    }
    bp = (char *)&fr.mp;
    fr.mp = fn_80003E0C(&fr._08);
    ((Unk_3DC8081F_3 *)bp)->unk0x4 = arg0;
    m = (f32 *)fr.mp;

    fr.t[0] = m[0] * arg0[0] + m[1] * arg0[4] + m[2] * arg0[8] + m[3] * arg0[12];
    fr.t[1] = m[0] * arg0[1] + m[1] * arg0[5] + m[2] * arg0[9] + m[3] * arg0[13];
    fr.t[2] = m[0] * arg0[2] + m[1] * arg0[6] + m[2] * arg0[10] + m[3] * arg0[14];
    fr.t[3] = m[0] * arg0[3] + m[1] * arg0[7] + m[2] * arg0[11] + m[3] * arg0[15];
    fr.t[4] = m[4] * arg0[0] + m[5] * arg0[4] + m[6] * arg0[8] + m[7] * arg0[12];
    fr.t[5] = m[4] * arg0[1] + m[5] * arg0[5] + m[6] * arg0[9] + m[7] * arg0[13];
    fr.t[6] = m[4] * arg0[2] + m[5] * arg0[6] + m[6] * arg0[10] + m[7] * arg0[14];
    fr.t[7] = m[4] * arg0[3] + m[5] * arg0[7] + m[6] * arg0[11] + m[7] * arg0[15];
    fr.t[8] = m[8] * arg0[0] + m[9] * arg0[4] + m[10] * arg0[8] + m[11] * arg0[12];
    fr.t[9] = m[8] * arg0[1] + m[9] * arg0[5] + m[10] * arg0[9] + m[11] * arg0[13];
    fr.t[10] = m[8] * arg0[2] + m[9] * arg0[6] + m[10] * arg0[10] + m[11] * arg0[14];
    fr.t[11] = m[8] * arg0[3] + m[9] * arg0[7] + m[10] * arg0[11] + m[11] * arg0[15];
    fr.t[12] = m[12] * arg0[0] + m[13] * arg0[4] + m[14] * arg0[8] + m[15] * arg0[12];
    fr.t[13] = m[12] * arg0[1] + m[13] * arg0[5] + m[14] * arg0[9] + m[15] * arg0[13];
    fr.t[14] = m[12] * arg0[2] + m[13] * arg0[6] + m[14] * arg0[10] + m[15] * arg0[14];
    fr.t[15] = m[12] * arg0[3] + m[13] * arg0[7] + m[14] * arg0[11] + m[15] * arg0[15];

    dp = (__ps_t *)arg0;
    dp[0] = *(__ps_t *)&fr.t[0];
    dp[1] = *(__ps_t *)&fr.t[2];
    dp[2] = *(__ps_t *)&fr.t[4];
    dp[3] = *(__ps_t *)&fr.t[6];
    dp[4] = *(__ps_t *)&fr.t[8];
    dp[5] = *(__ps_t *)&fr.t[10];
    dp[6] = *(__ps_t *)&fr.t[12];
    dp[7] = *(__ps_t *)&fr.t[14];
}
