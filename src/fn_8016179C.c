// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016179C-0x80161880 (228B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 lbl_80305F9C;
extern void GetChecksum_2(CStruct *, s32, s32 *, s32);
extern s32 GetVector(CStruct *, s32, CStruct *, s32);
extern s32 fn_8009CF2C(CStruct *);
extern s32 fn_8021B55C(s32, s32);
extern void fn_80137CB4(Unk_9F066EC1 *);
extern void fn_8013DE78(void *, Unk_C71E6DE1 *);

typedef struct { u8 b0; u8 _p1; s16 h2; void *p4; u8 _p8[4]; s32 c12; u8 b16; } rep_t;

bool ScriptReportObjectPlacement(CStruct *pParams, CScript *pScript) {
    typedef struct {
        f32 vec[4];      /* r1+0x08 */
        rep_t rep;       /* r1+0x18 */
        u8 hole[0x14];
        f32 copy[4];     /* r1+0x40 */
        s32 out;         /* r1+0x50 */
    } frame_t;
    frame_t fr;
    s32 prof;

    prof = lbl_80305F9C;
    GetChecksum_2(pParams, QB_OBJID, &fr.out, 0);
    GetVector(pParams, QB_POS, &fr.vec[0], 0);
    if (fn_8009CF2C(prof) != 0) {
        prof = fn_8021B55C(prof, 0);
    } else {
        prof = fn_8021B55C(prof, fr.out);
    }
    if (prof != 0) {
        fn_80137CB4(&fr.rep);
        fr.rep.b0 = 0x8F;
        *(__ps_t *)fr.copy = *(__ps_t *)fr.vec;
        *(__ps_t *)&fr.copy[2] = *(__ps_t *)&fr.vec[2];
        fr.rep.p4 = fr.copy;
        fr.rep.h2 = 0x10;
        fr.rep.c12 = 2;
        fr.rep.b16 = 8;
        fn_8013DE78(prof, &fr.rep);
    }
    return true;
}
