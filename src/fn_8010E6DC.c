// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010E6DC-0x8010E820 (324B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80301A38;
void GetVector(CStruct *, s32, CStruct *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_800A398C(s32, s32);
void fn_8012788C(CStruct *, s32, f32, f32, f32);

typedef union {
    __ps_t p;
    f32 f[2];
} Pair;

typedef union {
    __ps_t p[2];
    f32 f[4];
} Quad;

typedef struct {
    f32 in[4];
    Pair a;
    Pair b;
    volatile Pair c;
    volatile Pair d;
    Quad rows;
    s32 checksum;
} Frame;

bool ScriptTransformLocalToWorld(CStruct *arg0, CScript *arg1) {
    Frame fr;
    Unk_6A70655D *temp_r9;
    f32 *matrix;

    GetVector(arg0, QB_LOCAL_OFFSET, fr.in, 0);
    GetChecksum_2(arg0, QB_OBJECT, &fr.checksum, 0);
    temp_r9 = fn_800A398C(lbl_80301A38, fr.checksum);
    matrix = (f32 *)temp_r9;
    fr.rows.f[0] = (fr.in[3] * matrix[64]) + ((fr.in[2] * matrix[60]) + ((fr.in[0] * matrix[52]) + (fr.in[1] * matrix[56])));
    fr.rows.f[1] = (fr.in[3] * matrix[65]) + ((fr.in[2] * matrix[61]) + ((fr.in[0] * matrix[53]) + (fr.in[1] * matrix[57])));
    fr.rows.f[2] = (fr.in[3] * matrix[66]) + ((fr.in[2] * matrix[62]) + ((fr.in[0] * matrix[54]) + (fr.in[1] * matrix[58])));
    fr.rows.f[3] = (fr.in[3] * matrix[67]) + ((fr.in[2] * matrix[63]) + ((fr.in[0] * matrix[55]) + (fr.in[1] * matrix[59])));
    fr.a.p = fr.rows.p[0];
    fr.c.p = fr.rows.p[0];
    fr.b.p = fr.rows.p[1];
    fr.d.p = fr.rows.p[1];
    fn_8012788C(arg1->unk0x18, QB_WORLD_OFFSET, fr.a.f[0], fr.a.f[1], fr.b.f[0]);
    return true;
}
