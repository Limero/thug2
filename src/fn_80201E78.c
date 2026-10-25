// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80201E78-0x80201F54 (220B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef struct {
    char pad00[0x2C];
    s32 unk2C;
    s32 unk30;
    char pad34[0x9A0];
    char pad9D4[0x5C];
    __ps_t psA30;
    __ps_t psA38;
    __ps_t psA40;
    __ps_t psA48;
    s32 unkA50;
    char padA54[0x8];
    s32 unkA5C;
    char padA60[0x8];
    __ps_t psA68;
    __ps_t psA70;
    __ps_t psA78;
    __ps_t psA80;
    s32 unkA88;
    s32 unkA8C;
    s32 unkA90;
} E78_t;

extern s32 fn_802010FC(void *);
extern void Script_RunScript(s32, s32, s32, s32, s32);

void fn_80201E78(E78_t *arg0) {
    s32 var_ctr;
    s32 var_i;
    char *p30;
    char *p2C;
    __ps_t *dA;
    __ps_t *dB;
    __ps_t *sA;
    __ps_t *sB;
    __ps_t *dC;
    __ps_t *sC;
    __ps_t *dD;
    __ps_t *sD;

    if (fn_802010FC(arg0) != 0) {
        Script_RunScript(QB_STATS_MESSAGE_BAIL, 0, 0, 0, 0);
        var_ctr = 0x46;
        dA = &arg0->psA68;
        sA = &arg0->psA78;
        dB = &arg0->psA70;
        sB = &arg0->psA80;
        dC = &arg0->psA30;
        sC = &arg0->psA40;
        dD = &arg0->psA38;
        sD = &arg0->psA48;
        p30 = (char *)arg0 + 0x30;
        var_i = 0;
        do {
            if ((*(s32 *)((char *)(var_i + (s32)p30)) == 0) && (*(s32 *)((p2C = (char *)arg0 + 0x2C, p2C + var_i)) != 0)) {
                *(s32 *)(p2C + var_i) = 0;
            }
            var_i += 0x24;
        } while (--var_ctr != 0);
        arg0->unkA5C = 0;
        arg0->unkA88 = 0;
        arg0->unkA8C = 0;
        arg0->unkA90 = 0;
        *dA = *sA;
        *dB = *sB;
        *dC = *sC;
        *dD = *sD;
    }
}
