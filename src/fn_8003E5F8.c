// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003E5F8-0x8003E6C8 (208B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_80366474;
#include "qb_constants.h"
s32 fn_8003DB0C(void *, void *, s32, void *, s32 *);
s32 GetFacePointsStruct(void *, s32);
s32 fn_8005CF80(void *, s32);
s32 GetStructure_2(void *, void *, s32 *, void *);
s32 GetChecksum_2(void *, void *, s32 *, void *);
s32 ContainsFlag(void *, void *);
struct ALL { s32 buf[14]; s8 a, b, c, d; s32 q44; s32 q48; };
bool ScriptMassageFaceTexture(void *arg0) {
    struct ALL sp8;
    s32 temp_r30;
    s32 temp_r31;

    GetChecksum_2(arg0, QB_TEXTURE, &sp8.q44, 0);
    temp_r30 = fn_8005CF80((void *)lbl_80366474, sp8.q44);
    if (temp_r30 != 0) {
        sp8.q48 = 0;
        GetStructure_2(arg0, QB_FACE_POINTS, &sp8.q48, 0);
        temp_r31 = ContainsFlag(arg0, QB_NO_PALETTE_GEN) == 0;
        if (sp8.q48 != 0) {
            GetFacePointsStruct(&sp8, sp8.q48);
            sp8.a = -0x80;
            sp8.b = -0x80;
            sp8.c = -0x80;
            sp8.d = -0x80;
            fn_8003DB0C((void *)temp_r30, &sp8, temp_r31, 0, &sp8.a);
        }
    }
    return true;
}
