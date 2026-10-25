// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800456F4-0x800457B8 (196B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

typedef union {
    u32 w;
    u8 b[4];
} F456F4Word;

typedef struct {
    char pad0[0x40];
    F456F4Word unk0x40;
} F456F4In;

typedef struct {
    char pad0[0x128];
    f32 unk0x128;
    char pad1[0x184 - 0x12C];
    f32 unk0x184;
    char pad2[0x194 - 0x188];
    Unk_C8FEE62D *unk0x194;
} F456F4Obj;

extern f32 lbl_8029270C;

void fn_8005EC1C(Unk_C7387A53 *, s32 *);
void fn_8005EBA4(Unk_C8FEE62D *, f32);
void fn_8005EB6C(void *, u32);

void fn_800456F4(F456F4Obj *arg0) {
    volatile s32 outv;
    s32 tmp;
    F456F4In *in;

    fn_8005EB6C(arg0->unk0x194, 0);
    fn_8005EBA4(arg0->unk0x194, arg0->unk0x184);
    in = (F456F4In *)((char *)arg0 + 0x88);
    tmp = in->unk0x40.w;
    if (arg0->unk0x128 >= lbl_8029270C) {
        *((u8 *)&tmp + 3) = (s8)((f32)(f64)(u32)in->unk0x40.b[3] * arg0->unk0x128);
    } else {
        *((u8 *)&tmp + 3) = 0;
    }
    outv = tmp;
    fn_8005EC1C((Unk_C7387A53 *)arg0->unk0x194, (s32 *)&outv);
}
