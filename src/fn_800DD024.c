// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DD024-0x800DD1F0 (460B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
void fn_800DDAF0(void *, s32, s32);
extern char lbl_80299F88[];
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80299F7C[];
s32 GetChecksum_2(CStruct *arg0, s32 arg1, s32 *arg2, s32 arg3);
s32 ContainsFlag(CStruct *arg0, s32 arg1);
void fn_800DDCB8(Unk_C8FEE62D *arg0);
s32 GetString(CStruct *arg0, s32 arg1, s32 *arg2, s32 arg3);
s32 GetFloat(CStruct *arg0, s32 arg1, f32 *arg2, s32 arg3);

typedef struct {
    char pad0x0[0x18];
    s16 unk0x18;
    void *unk0x1C;
} DD024Vtbl;

void fn_800DD024(Unk_C8FEE62D *arg0, CStruct *arg1) {
    f32 sp1C;
    s32 sp18;
    __ps_t sp8[2];
    __ps_t *p;
    s32 var_r4;
    u32 temp_r9;
    void *temp_r11;
    DD024Vtbl *temp_r9_2;

    arg0->unk0x40 = QB_SIMPLE;
    GetChecksum_2(arg1, QB_SHADOWTYPE, (char *)arg0 + 0x40, 0);
    if (ContainsFlag(arg1, QB_NOAUTOUPDATE) != 0) {
        arg0->unk0x48 = 0;
    }
    if (arg0->unk0x1C != NULL) {
        fn_800DDCB8(arg0);
    }
    temp_r9 = arg0->unk0x40;
    switch (temp_r9) {
    case QB_SIMPLE:
        sp18 = (s32)lbl_80299F7C;
        GetString(arg1, QB_SHADOWMODEL, &sp18, 0);
        if (arg0->unk0x1C == NULL) {
            fn_800DDAF0(arg0, 2, sp18);
        }
        sp1C = *(f32 *)lbl_80299F88;
        GetFloat(arg1, QB_SHADOWSCALE, &sp1C, 0);
        temp_r11 = arg0->unk0x1C;
        *((f32 *)&((CStruct *)temp_r11)->unk0x10) = sp1C;
        p = sp8;
        sp8[0] = *(__ps_t *)((char *)arg0 + 0x30);
        *(__ps_t *)((char *)p + 8) = *(__ps_t *)((char *)arg0 + 0x38);
        temp_r9_2 = *(DD024Vtbl **)&((CStruct *)temp_r11)->unk0x8;
        ((s32 (*)(void *, void *, void *, __ps_t *))temp_r9_2->unk0x1C)(
            (char *)temp_r11 + temp_r9_2->unk0x18,
            (char *)arg0 + 0x20,
            (void *)(arg0->unk0xC + 0x78),
            p);
        return;
    case QB_UNKNOWN_0x76A54CD1:
        if (arg0->unk0x1C == NULL) {
            fn_800DDAF0(arg0, 1, 0);
        }
        return;
    case QB_VOLUME:
        if (arg0->unk0x1C == NULL) {
            fn_800DDAF0(arg0, 3, 0);
        }
        break;
    case QB_NONE:
        if (arg0->unk0x1C != NULL) {
            fn_800DDCB8(arg0);
        }
        break;
    }
}
