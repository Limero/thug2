// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800627B4-0x80062924 (368B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern Unk_9994C3F5 *lbl_802FFE98;
extern s32 lbl_80366474;

void fn_8000F2F8(Unk_9994C3F5 *, s32);
void fn_8000F320(Unk_9994C3F5 *);
s32 fn_8003EDE0(void *);
s32 fn_8003EDE8(void *);
s32 fn_8003EED0(void *);
void fn_8003EDF0(void *, void *);
void *fn_8005CB10(s32, s32, s32, s32, s32, s32, s32, s32);
void *fn_8005CA70(s32, s32, s32, s32, s32);
s32 fn_8005C5B4(void *);
void fn_8005CC88(s32, void *);
s32 fn_80061140(void *, s32, s32, s32);
void fn_8003DAA0(void *);
void fn_8003DB00(void *);
s32 fn_8003DB0C(void *, void *, s32, void *, s32 *);
s32 GetStructure(s32, s32);
void GetFacePointsStruct(void *, s32);

typedef struct {
    s32 buf[14];
} FacePoints;

typedef struct {
    s32 buf[14];
    s8 a, b, c, d;
} FaceVert;

s32 fn_800627B4(void *arg0, void *arg1, s32 arg2, s32 arg3) {
    FacePoints sp8;
    FaceVert sp40;
    s32 v;
    void *heap;
    void *heap2;
    s32 r;

    fn_8000F2F8(lbl_802FFE98, lbl_802FFE98->unk0x118);
    heap = fn_8005CB10(lbl_80366474, fn_8003EDE0(arg1), fn_8003EDE8(arg1),
                       QB_DUMMY, 1, 1, 0, 1);
    heap2 = fn_8005CA70(lbl_80366474, fn_8003EED0(arg1), 1, 1, 1);
    fn_8000F320(lbl_802FFE98);
    GetFacePointsStruct(&sp8, GetStructure(QB_ORIGINAL_MODEL_FACE_POINTS, 1));
    fn_8003DAA0(&sp8);
    fn_8003DB00(heap2);
    fn_8003EDF0(&sp40, arg1);
    v = sp40.buf[8];
    sp40.a = -0x80;
    sp40.b = -0x80;
    sp40.c = -0x80;
    sp40.d = -0x80;
    fn_8003EDF0(&sp40, arg1);
    fn_8003DB0C(heap, &sp40, v, 0, &sp40.a);
    r = fn_80061140(arg0, arg3, arg2, fn_8005C5B4(heap));
    fn_8005CC88(lbl_80366474, heap);
    fn_8005CC88(lbl_80366474, heap2);
    return r;
}
