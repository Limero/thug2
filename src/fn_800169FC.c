// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800169FC-0x80016A88 (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct P3 { f32 a; f32 b; f32 c; } P3;
typedef struct Obj {
    char pad0[0x30];
    P3 subA;
    P3 subB;
    char pad48[0x60];
    s32 unkA8;
} Obj;
extern f32 lbl_80290BEC;
extern f32 lbl_80290BF0;
void fn_8001D424(P3 *);
void Camera_orthographic(Obj *, s32, s32, s32, s32);
// queue_front @ 0x800169FC
void *queue_front(Obj *self) {
    f32 v;
    P3 *a = &self->subA;
    P3 *b = &self->subB;
    fn_8001D424(a);
    fn_8001D424(b);
    Camera_orthographic(self, 0, 0, 0x200, 0x180);
    v = lbl_80290BEC;
    a->a = v;
    a->b = lbl_80290BF0;
    a->c = v;
    b->a = v;
    b->b = v;
    b->c = v;
    self->unkA8 = 0;
    return self;
}
