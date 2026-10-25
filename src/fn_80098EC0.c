// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80098EC0-0x80098F84 (196B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    char pad0x0[0x6];
    u8 b6;
    u8 b7;
    f32 f8;
    char pad0xC[2];
    u16 hE;
} D98_t;

typedef struct {
    char pad0x0[0x4];
    D98_t *d;
} S98_t;

typedef struct {
    char pad0x0[0x14];
    S98_t *sub;
} N98_t;

s32 fn_80098EC0(N98_t **arg0, N98_t **arg1) {
    N98_t *bn;
    N98_t *an;
    S98_t *bs;
    S98_t *as;
    D98_t *bd;
    D98_t *ad;
    f32 fb;
    f32 fa;

    an = *arg0;
    bn = *arg1;
    bs = bn->sub;
    as = an->sub;
    bd = bs->d;
    ad = as->d;
    fb = bd->f8;
    fa = ad->f8;
    if (fa == fb) {
        if ((ad->b6 & 1) == (bd->b6 & 1)) {
            if (ad == bd) {
                return 0;
            }
            if (ad->b7 == bd->b7) {
                if (ad->hE == bd->hE) {
                    return (u32)ad > (u32)bd ? 1 : -1;
                }
                return (ad->hE < bd->hE) ? 1 : -1;
            }
            return (ad->b7 > bd->b7) ? 1 : -1;
        }
        if (ad->b6 & 1) {
            return 1;
        }
        return -1;
    }
    return (fa > fb) ? 1 : -1;
}
