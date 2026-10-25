// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80011BB8-0x80011CA4 (236B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-expensive-optimizations
#include "types.h"
#include "qb_constants.h"

/* Arena block header.  `sz` is the 24-bit big-endian payload size in bytes
   0x8..0xA; `lo` is the 1-byte back-offset tag in byte 0xB.  The field order
   matters: on this big-endian target the FIRST bitfield takes the MSBs. */
typedef struct {
    s32 unk0x0;                                        /* +0x00 next block   */
    s32 unk0x4;                                        /* +0x04              */
    struct { u32 sz : 24; u32 lo : 8; } unk0x8;        /* +0x08 size | tag   */
} NODE;

typedef struct { char _0[0x48]; s16 unk0x48; char _4A[2]; s32 unk0x4C; } VT11;
typedef struct { char _0[0x80]; VT11 *unk0x80; } OBJ;

extern s32 fn_80010768(s32);
extern void fn_80010764(s32);
extern s32 fn_80010B38(s32);
extern s32 fn_80011DE0(void *, s32);   /* void body; s32 return needed at THIS site */
extern s32 lbl_80290628;               /* 0xC — arena block header size */
extern s32 lbl_802FFEE8;               /* global "arena mutating" flag */

s32 fn_80011BB8(OBJ *arg0, s32 arg1, s32 arg2) {
    u32 temp_r0;      /* blk payload size                 */
    u32 temp_r31;     /* tail chunk size                  */
    u32 temp_r9;      /* lbl_80290628 == 0xC              */
    u32 temp_r9_3;    /* blk payload size, re-read        */
    NODE *temp_r30;   /* the block carved out of the tail */
    NODE *temp_r3;    /* the block that contains arg2     */
    VT11 *temp_r9_2;

    lbl_802FFEE8 = 1;
    temp_r3 = (NODE *)fn_80010B38(arg2);
    temp_r9 = lbl_80290628;
    temp_r0 = (u32)temp_r3->unk0x8.sz;
    temp_r31 = (temp_r0 - arg1) & QB_UNKNOWN_0xFFFFFFFC;
    if (temp_r31 > temp_r9) {
        /* new block header is lbl_80290628 bytes, so its payload is the
           tail minus that header; the block itself ends at arg2 + sz. */
        temp_r30 = (NODE *)((arg2 + temp_r0) - temp_r31);
        temp_r30->unk0x0 = (s32)arg0;
        temp_r30->unk0x8.sz = temp_r31 - temp_r9;
        temp_r30->unk0x8.lo = 0;
        fn_80010764((s32)temp_r30);
        fn_80011DE0((char *)arg0 + 4, 1);
        temp_r9_2 = arg0->unk0x80;
        ((s32 (*)(void *, void *))temp_r9_2->unk0x4C)((char *)arg0 + temp_r9_2->unk0x48, (s32)temp_r30);
        fn_80010768((s32)temp_r3);
        /* reload: the block shrank, so the size must be re-read, not reused */
        temp_r9_3 = (u32)temp_r3->unk0x8.sz;
        temp_r3->unk0x8.sz = temp_r9_3 - temp_r31;
        fn_80010764((s32)temp_r3);
    }
    lbl_802FFEE8 = 0;
    return arg2;
}
