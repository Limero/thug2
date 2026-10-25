// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006EA10-0x8006EB10 (256B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern s32 lbl_80300460;
extern void *lbl_80301438;
extern f32 lbl_80294C04;

float fn_800144C8(void);
void fn_8006F8C8(void *);
void *fn_8006F8DC(void *, s32);
void fn_80086D90(void *, float);
void fn_8006F998(void *, void *);

typedef struct Wip6EA10Vtbl {
    s32 unk0x0;
    s32 unk0x4;
    s16 unk0x8;
    s16 unk0xA;
    void (*unk0xC)(void *, s32);
} Wip6EA10Vtbl;

typedef struct Wip6EA10Obj {
    s32 unk0x0;
    s32 unk0x4;
    s32 unk0x8;
    s32 unk0xC;
    f32 unk0x10;
    s32 pad0x14[5];
    Wip6EA10Vtbl *unk0x28;
} Wip6EA10Obj;

// Retail's frame is -0x40: local area r1+8..0x23 = 0x1C bytes — sp8 is
// a 28-byte struct (only field 0 written here; &sp8 passed to
// fn_8006F998 as an out-param). A bare void* sp8 gives -0x30.
typedef struct Wip6EA10Node {
    Wip6EA10Obj *unk0x0;
    s32 unk0x4;
    s32 unk0x8;
    s32 unk0xC;
    s32 unk0x10;
} Wip6EA10Node;

void fn_8006EA10(void) {
    Wip6EA10Node sp8;
    f32 temp_f30;
    f32 temp_f31;
    Wip6EA10Vtbl *temp_r9;
    Wip6EA10Obj *var_r30;
    Wip6EA10Obj *var_r31;

    if ((lbl_80300460 == 0) && (lbl_80301438 != NULL)) {
        temp_f31 = fn_800144C8();
        fn_8006F8C8(lbl_80301438);
        var_r31 = fn_8006F8DC(lbl_80301438, 0);
        if (var_r31 != NULL) {
            temp_f30 = lbl_80294C04;
            do {
                var_r30 = NULL;
                var_r31->unk0x10 = var_r31->unk0x10 - temp_f31;
                if (var_r31->unk0x10 <= temp_f30) {
                    var_r30 = var_r31;
                } else {
                    fn_80086D90(var_r31, temp_f31);
                }
                var_r31 = fn_8006F8DC(lbl_80301438, 0);
                if (var_r30 != NULL) {
                    sp8.unk0x0 = var_r30;
                    fn_8006F998(lbl_80301438, &sp8);
                    temp_r9 = var_r30->unk0x28;
                    temp_r9->unk0xC((char *)var_r30 + temp_r9->unk0x8, 3);
                }
            } while (var_r31 != NULL);
        }
    }
}
