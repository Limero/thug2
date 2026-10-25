// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002CC78-0x8002CDE4 (364B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_802FFE98;
s32 fn_8002D2A0(void);
u32 fn_8002D720(void *);
void fn_8000F2F8(void *, void *);
u32 fn_8000F16C(void *);
void fn_8000F320(void *);
s32 fn_80010400(s32, s32, s32);
s32 Mem_Alloc(s32);
u32 fn_8002CC78(Unk_998B8376 *arg0, s32 arg1, s16 arg2, s32 arg3, s32 arg4, s32 arg5) {
    u8 var_r0;
    u32 temp_r10;
    u32 temp_r0;
    s32 temp_r3;

    *(u16 *)((char *)arg0 + (s32)0x166) = arg2;
    arg0->unk0x168 = (s32) (arg0->unk0x168 | 0x10000);
    arg0->unk0xC = arg5;
    switch (arg5) {
    case 2:
        var_r0 = 8;
        goto block_10;
    case 3:
        var_r0 = 0x10;
        goto block_10;
    case 4:
        *(u8 *)((char *)arg0 + (s32)0x74) = 0x14;
        *(u8 *)((char *)arg0 + (s32)0x75) = 0x10;
        break;
    default:
        var_r0 = 0;
        goto block_10;
    block_10:
        *(u8 *)((char *)arg0 + (s32)0x74) = var_r0;
        *(u8 *)((char *)arg0 + (s32)0x75) = var_r0;
        break;
    }
    temp_r10 = fn_8002D720((void *) (s32)fn_8002D2A0());
    temp_r0 = (arg3 * *(u8 *)((char *)arg0 + (s32)0x74)) + (arg4 * *(u8 *)((char *)arg0 + (s32)0x75));
    arg0->unk0x18 = temp_r0;
    arg0->unk0x14 = (u32) ((temp_r0 / temp_r10 + 1) * temp_r10);
    fn_8000F2F8((void *) (s32)lbl_802FFE98, (void *) (s32)fn_80010400((s32)lbl_802FFE98, QB_ANIMHEAP, 1));
    if (fn_8000F16C((void *) (s32)lbl_802FFE98) < arg0->unk0x14) {
        arg0->unk0xC = 0;
        fn_8000F320((void *) (s32)lbl_802FFE98);
        return 0U;
    }
    arg0->unk0x4 = arg1;
    temp_r3 = Mem_Alloc(arg0->unk0x14);
    arg0->unk0x10 = temp_r3;
    arg0->unk0x1C = temp_r3;
    arg0->unk0x20 = temp_r3 + (arg3 * *(u8 *)((char *)arg0 + (s32)0x74));
    fn_8000F320((void *) (s32)lbl_802FFE98);
    arg0->unk0x8 = 0;
    arg0->unk0x168 = (s32) (arg0->unk0x168 & QB_UNKNOWN_0xFFFCFFFF);
    return arg0->unk0x14;
}
