// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B175C-0x801B17E4 (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

typedef struct {
    __ps_t o[4];        /* r1+8 .. r1+0x27 */
    char pad[0x88];     /* up to r1+0xAF */
    s32 ptr;            /* r1+0xB0 */
    char tail[0x14];    /* total 0xC0 -> frame 0xD8 */
} fr_t;

void fn_8010794C(Unk_C7387A53 *);
s32 fn_80107B20(Unk_E9DCA07D *, s32, void *);
void CObject_RemoveRefLink(CStruct *, CStruct *);

s32 fn_801B175C(s32 arg0, s32 arg1) {
    fr_t fr;
    __ps_t *v;
    s32 *pp;
    s32 temp_r30;

    fn_8010794C(&fr);
    fr.o[3] = *(__ps_t *)((char *)arg1 + 8);
    v = (__ps_t *)&fr;
    v[1] = *(__ps_t *)((char *)arg0 + 8);
    fr.o[0] = *(__ps_t *)((char *)arg0 + 0);
    fr.o[2] = *(__ps_t *)((char *)arg1 + 0);
    temp_r30 = fn_80107B20(&fr, 1, 0);
    if ((pp = (s32 *)&fr.ptr), fr.ptr != 0) {
        CObject_RemoveRefLink((void *)fr.ptr, pp);
        fr.ptr = 0;
    }
    return temp_r30;
}
