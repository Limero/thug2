// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800EC448-0x800EC544 (252B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct VT_800EC448 {
    char pad0x00[0x40];
    s16 off0x40;
    char pad0x42[2];
    s32 (*fn0x44)(void *, s32, f32, f32, f32);
    char pad0x48[0x38];
    s16 off0x80;
    char pad0x82[2];
    s32 (*fn0x84)(void *, s32, s32);
} VT_800EC448;
void fn_800EC448(Unk_C7387A53 *arg0) {
    s32 (*temp_lr)(void *, s32, f32, f32, f32);
    f32 temp_f1;
    f32 temp_f2;
    f32 temp_f3;
    u32 var_r30;
    s32 one;
    char *var_r31;
    void *st_node;
    void *node;
    VT_800EC448 *vt;

    var_r30 = 1U;
    if (var_r30 < (u32)*(s32 *)&arg0->unk0x20) {
        var_r31 = (char *)arg0 + 0x78;
        one = 1;
        do {
            st_node = *(void **)((char *)var_r31 - 4);
            *(s32 *)((char *)st_node + 0x14) = one;
            node = *(void **)((char *)var_r31 - 4);
            vt = (VT_800EC448 *)((s32 *)node)[8];
            ((s32 (*)(void *, s32, s32))vt->fn0x84)((char *)node + vt->off0x80, 0, 0xFF);
            node = *(void **)((char *)var_r31 - 4);
            vt = (VT_800EC448 *)((s32 *)node)[8];
            temp_f1 = *(f32 *)((char *)var_r31 - 0x50);
            temp_f2 = *(f32 *)((char *)var_r31 - 0x4C);
            temp_f3 = *(f32 *)((char *)var_r31 - 0x48);
            temp_lr = vt->fn0x44;
            ((s32 (*)(void *, s32, f32, f32, f32))temp_lr)((char *)node + vt->off0x40, 0, temp_f1, temp_f2, temp_f3);
            node = *(void **)((char *)var_r31 - 4);
            vt = (VT_800EC448 *)((s32 *)node)[8];
            ((s32 (*)(void *, s32, s32))vt->fn0x84)((char *)node + vt->off0x80, 1, 0xFF);
            node = *(void **)((char *)var_r31 - 4);
            vt = (VT_800EC448 *)((s32 *)node)[8];
            temp_f1 = *(f32 *)((char *)var_r31 + 0x0);
            temp_f2 = *(f32 *)((char *)var_r31 + 0x4);
            temp_f3 = *(f32 *)((char *)var_r31 + 0x8);
            temp_lr = vt->fn0x44;
            var_r31 += 0x50;
            ((s32 (*)(void *, s32, f32, f32, f32))temp_lr)((char *)node + vt->off0x40, 1, temp_f1, temp_f2, temp_f3);
            var_r30 += 1;
        } while (var_r30 < (u32)*(s32 *)&arg0->unk0x20);
    }
}
