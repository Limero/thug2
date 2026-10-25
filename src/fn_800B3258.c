// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B3258-0x800B3378 (288B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

// The local at r1+8: 0x6C bytes, 4-aligned (0x74 of frame incl. GCC's
// 8-byte rounding). Only these offsets are provable from the DOL; the
// shared Unk_* classes have no members at 0x0/0x18/0x20/0x60 and are the
// wrong size, so a file-local layout is required.
typedef struct {
    s32 unk0x0;
    char pad0x4[0x14];
    s32 unk0x18;
    s32 unk0x1C;
    s32 unk0x20;
    char pad0x24[0x3C];
    s32 unk0x60;
    s32 unk0x64;
    s32 unk0x68;
    s32 unk0x6C;
} B3258Obj;

// File-local view of the object: the shared Unk_F8D48A89 has no members at
// 0x20/0x28, but retail psq_st's a 16-byte PS pair there (psq_st f0,0x20(r31)
// / psq_st f0,0x28(r31)), so the object really has __ps_t members at 0x20/0x28.
typedef struct {
    char pad0x0[0x4];
    s32 unk0x4;
    s32 unk0x8;
    s32 unk0xC;
    char pad0x10[0x4];
    s32 unk0x14;
    char pad0x18[0x8];
    __ps_t unk0x20;
    __ps_t unk0x28;
    char pad0x30[0x1E0];
    s32 unk0x210;
} B3258Obj2;

void *GetChecksum_3(void *, s32);       /* 0x8009FDD8, scope:global */
s32 fn_800C9780(void *);                 /* 0x800C9780 */
void fn_8003AEA0(B3258Obj *, s32, s32);  /* 3 args, see src/fn_8003AEA0.c */
void fn_8003AEEC(B3258Obj *, void *, s32, s32, s32);
void fn_800B61F4(void *);
/* real fn returns s32; void here = per-caller return-type flip (M8.31) */
void fn_800626E8(void *, void *);
s32 Script_GetInteger(s32, s32);         /* 0x801257B8, scope:global */
void fn_800B4488(s32);
void fn_8009E0B0(B3258Obj *, s32);

void fn_800B3258(B3258Obj2 *arg0, void *arg1, s32 arg2, s32 arg3, void *arg4) {
    B3258Obj sp8;
    s32 temp_r29;
    s32 temp_r3;
    void *temp_cs;
    s32 var_r30;
    s32 var_r11;
    s32 var_h;

    temp_r29 = arg0->unk0x210;
    var_r30 = 0;
    temp_cs = GetChecksum_3(arg0->unk0xC, QB_SKELETON);
    if (temp_cs != 0) {
        var_r30 = fn_800C9780(temp_cs);
    }
    fn_8003AEA0(&sp8, arg2, arg3);
    if (arg4 != 0) {
        fn_8003AEEC(&sp8, arg1, temp_r29, var_r30, arg4);
    } else {
        fn_8003AEEC(&sp8, arg1, temp_r29, var_r30, QB_CREATE_MODEL_FROM_APPEARANCE);
    }
    var_r11 = 1;
    temp_r3 = *(s32 *)(*(s32 *)((char *)arg0 + 0xC) + 0x114) & 0x20;
    if (temp_r3 == 0) {
        var_r11 = 0;
    }
    if (var_r11 != 0) {
        fn_800B61F4(arg0);
    }
    /* 16-byte paired-single out-param written by fn_800626E8 at r1+0x68 */
    fn_800626E8(&sp8.unk0x60, temp_r29);
    *(__ps_t *)&arg0->unk0x20 = *(__ps_t *)&sp8.unk0x60;
    *(__ps_t *)&arg0->unk0x28 = *(__ps_t *)&sp8.unk0x68;
    var_h = QB_GENERATEDEFAULTMODELCOLLDATA;
    temp_r3 = Script_GetInteger(var_h, 0);
    if (temp_r3 != 0) {
        fn_800B4488((s32)arg0);
    }
    fn_8009E0B0(&sp8, 2);
}
