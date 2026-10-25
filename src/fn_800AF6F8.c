// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800AF6F8-0x800AF738 (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct {
    char pad0x0[0x10];
    void *unk0x10;
    char pad0x14[0xC];
    Unk_C8FEE62D *unk0x20;
    char pad0x24[0x3460];
    f32 unk0x3484;
    char pad0x3488[0x4];
    f32 unk0x348C;
} Unk_0771A7B9T;
void fn_80026D34(Unk_C8FEE62D *, void *, void *, void *, void *, f32);
void fn_800AF6F8(Unk_0771A7B9T *arg0, void *arg1, void *arg2) {
    s32 sp8;

    sp8 = 0;
    fn_80026D34(arg0->unk0x20, arg1, arg2, &sp8, arg0->unk0x10,
                arg0->unk0x3484 - arg0->unk0x348C);
}
