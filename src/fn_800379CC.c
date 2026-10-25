// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800379CC-0x80037B7C (432B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 GetInteger(CStruct *arg0, s32 arg1, s32 *arg2, s32 arg3);
s32 GetVector(CStruct *arg0, s32 arg1, CStruct *arg2, s32 arg3);
s32 GetChecksum(CStruct *arg0, s32 arg1);
s32 fn_801259C8(s32 arg0, s32 arg1);
s32 fn_80037BF0(void *arg0, s32 arg1, void *arg2);
void fn_80037C40(void *arg0, s32 arg1, void *arg2, s32 arg3);
/* 0x3F800000 — the 1.0f bit pattern, read as a WORD and broadcast */
extern s32 lbl_80291EE8;

typedef struct { f32 x, y, z, w; } V4;
typedef union { s32 i[4]; f32 f[4]; } VU;

bool fn_800379CC(Unk_DB0E2BAB *arg0, CStruct *arg1) {
    V4 v;
    VU m;
    V4 *pv;
    VU *pm;
    s32 sc;
    s32 i;
    s32 h;
    CStruct *node;
    s32 j;
    s32 scaleOK;
    s32 g;

    if (arg1 == 0) {
        return false;
    }
    sc = 0;
    GetInteger(arg1, QB_SCALEFROMORIGIN, &sc, 0);
    i = 0;
    scaleOK = (sc == 0);
    if (i < arg0->unk0x14) {
        pv = &v;
        do {
            if (GetVector(arg1, ((s32 *)arg0->unk0x18)[i * 8], (CStruct *)&v, 0) != 0) {
                h = ((s32 *)arg0->unk0x18)[i * 8];
                if ((arg0->unk0x0 & QB_UNKNOWN_0x10000000) && (h == QB_HEAD)) {
                    h = (s32)0xDFEE29AC;
                }
                node = (CStruct *)fn_801259C8(QB_NONLOCAL_BONES, 0);
                if (node != 0) {
                    j = 0;
                    if ((u32)j < (u32)*((u32 *)node + 1)) {
                        do {
                            if (GetChecksum(node, j) == h) {
                                scaleOK = 0;
                            }
                            j = j + 1;
                        } while ((u32)j < (u32)*((u32 *)node + 1));
                    }
                }
                pm = &m;
                g = lbl_80291EE8;
                m.i[0] = g;
                pm->i[1] = g;
                pm->i[2] = g;
                pm->i[3] = g;
                if (fn_80037BF0(arg0, h, (void *)pm) != 0) {
                    m.f[0] = m.f[0] * v.x;
                    m.f[1] = m.f[1] * v.y;
                    m.f[2] = m.f[2] * pv->z;
                    m.i[3] = g;
                    fn_80037C40(arg0, h, (void *)pm, scaleOK);
                }
            }
            i = i + 1;
        } while (i < arg0->unk0x14);
    }
    return true;
}
