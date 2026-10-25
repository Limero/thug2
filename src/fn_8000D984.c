// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000D984-0x8000DAB8 (308B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    s32 unk0x0;
    char *unk0x4;
    char pad0x8[0x3C];
} Elem_t;

typedef struct {
    char pad0x0[0x14];
    void *unk0x14;
    char pad0x18[4];
    Elem_t unk0x1C[8];
    s32 unk0x23C;
} Obj_t;

extern void *lbl_802FFE98;
void *fn_800099AC(s32, void *, s32);
void *fn_8000CB0C(void *, void *, s32);
void fn_8000EC94(void *, void *, s32);

void fn_8000D984(Obj_t *self, s32 key, void *arg2) {
    s32 i;
    void *mgr;
    i = 0;
    while (i < self->unk0x23C) {
        if (self->unk0x1C[i].unk0x0 == key) {
            void *o;
            s32 n;
            mgr = self->unk0x14;
            o = fn_800099AC(0x1C, *(void **)((char *)lbl_802FFE98 + 0x118), 1);
            fn_8000EC94(mgr, &self->unk0x1C[i].unk0x4,
                        fn_8000CB0C(o, arg2, 0));
            n = self->unk0x23C - 1;
            self->unk0x23C = n;
            *(Elem_t *)((char *)self + 0x1C + i * 0x44) =
                *(Elem_t *)((char *)self + 0x1C + n * 0x44);
            return;
        }
        i += 1;
    }
}
