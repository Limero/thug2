// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801EC684-0x801EC7C4 (320B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802AD8E4;
extern void fn_80107AB4(void *, void *, void *);
extern void fn_80107A80(Unk_C5652918 *, s32, s32);
extern s32 fn_80107B20(Unk_E9DCA07D *, s32, void *);
extern f32 fn_8012570C(s32 hash, s32 flag);
extern f32 sinf(f32 x);
s32 fn_801EC684(Unk_E2C810EF *arg0, s32 arg1, s32 arg2) {
    Unk_6BB06288 *temp_r28;
    s32 var_r29;
    s32 flags;
    s32 bit1;
    s32 bflag;
    s32 bit8;
    s32 bit4;
    f32 sp8[4];

    temp_r28 = (void *)((char *)arg0 + (s32)0xB0);
    fn_80107AB4(temp_r28, (void *)((char *)arg0 + (s32)0x230), (void *)((char *)arg0 + (s32)0x240));
    fn_80107A80(temp_r28, arg1, arg2);
    var_r29 = fn_80107B20(temp_r28, 1, 0);
    if (var_r29 == 0) {
        return 0;
    }
    if (temp_r28->unk0x60 != 0) {
        bflag = 1;
        if (temp_r28->unk0x75 == 0) {
            bflag = 0;
        }
        if (bflag != 0) {
            temp_r28->unk0x64 = 0;
        }
    }
    *(__ps_t *)&sp8[0] = arg0->unk0x148;
    arg0->unk0x258 = 0;
    flags = arg0->unk0x108;
    *(__ps_t *)&sp8[2] = arg0->unk0x150;
    arg0->unk0x254 = (flags >> 3) & 1;
    bit1 = flags & 1;
    if (bit1 == 0) {
        if (flags & 2) {
            arg0->unk0x250 = bit1;
        } else {
            bit8 = flags & 8;
            if (bit8 == 0) {
                bit4 = flags & 4;
                if (bit4 != 0) {
                    arg0->unk0x250 = bit8;
                    arg0->unk0x258 = 1;
                } else if (sp8[1] < sinf(fn_8012570C(QB_WALL_NON_SKATABLE_ANGLE, 1) * lbl_802AD8E4)) {
                    arg0->unk0x250 = bit4;
                } else {
                    arg0->unk0x250 = 1;
                }
            } else {
                arg0->unk0x250 = 1;
            }
        }
    } else {
        arg0->unk0x250 = 1;
    }
    return var_r29;
}
