// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801AFE44-0x801AFE94 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
extern s32 fn_801AFD88(CStruct *, s32);

void fn_801AFE44(CStruct *arg0, s32 arg1, __ps_t *arg2, __ps_t *arg3) {
    __ps_t *src = (__ps_t *)fn_801AFD88(arg0, arg1);

    arg2[0] = src[3];
    arg2[1] = src[4];
    arg3[0] = src[5];
    arg3[1] = src[6];
}
