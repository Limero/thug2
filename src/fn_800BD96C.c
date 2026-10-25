// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800BD96C-0x800BDAD4 (360B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-sched-interblock
#include "types.h"
#include "structs.h"
typedef struct { f32 x, y, z; } Vec3;
typedef struct { f32 a, y, z; } Row;
extern char lbl_80298E60[];
extern f32 lbl_80298E64;
s32 Mem_Free2(s32 arg0);
s32 Mem_Alloc(s32 arg0);
void fn_800BD96C(Unk_8A4B2B78 *arg0, Vec3 *arg1) {
    f32 one;
    f32 w;
    f32 zf;
    s32 off;
    s32 tblv;
    s32 flip;
    u16 temp_r30;
    s32 var_r9;
    Row *zp;
    register s32 anch __asm__("r7");

    arg0->unk0x94 = 6U;
    if (arg0->unk0x64 != 0) {
        Mem_Free2(arg0->unk0x64);
    }
    temp_r30 = arg0->unk0x94;
    tblv = Mem_Alloc((s32)temp_r30 * 0x10);
    var_r9 = temp_r30 - 1;
    if ((s32)temp_r30 != 0) {
        do {
            __asm__("" : : "r"(var_r9), "r"(temp_r30));
            var_r9 -= 1;
        } while (var_r9 != -1);
    }
    flip = 0;
    __asm__("lis %0,%1@ha" : "=r"(anch) : "s"(lbl_80298E60));
    off = 0;
    arg0->unk0x64 = tblv;
    w = lbl_80298E64;
    do {
        *(f32 *)(off + arg0->unk0x64) = arg1->x;
        *(f32 *)(off + arg0->unk0x64 + 4) = -arg1->y;
        zf = arg1->z;
        zp = (Row *)((char *)(off + arg0->unk0x64));
        if (flip != 0) {
            zf = -zf;
        }
        zp->z = zf;
        one = *(f32 *)((char *)anch - 0x71A0);
        __asm__ volatile("" : "+f"(one));
        *(f32 *)(off + arg0->unk0x64 + 0xC) = one;
        off += 16;
        *(f32 *)(off + arg0->unk0x64) = -arg1->x;
        *(f32 *)(off + arg0->unk0x64 + 4) = -arg1->y;
        zf = arg1->z;
        zp = (Row *)((char *)(off + arg0->unk0x64));
        if (flip != 0) {
            zf = -zf;
        }
        zp->z = zf;
        *(f32 *)(off + arg0->unk0x64 + 0xC) = one;
        off += 16;
        *(f32 *)(off + arg0->unk0x64) = w;
        *(f32 *)(off + arg0->unk0x64 + 4) = arg1->y;
        zf = arg1->z;
        zp = (Row *)((char *)(off + arg0->unk0x64));
        if (flip != 0) {
            zf = -zf;
        }
        zp->z = zf;
        *(f32 *)(off + arg0->unk0x64 + 0xC) = one;
        off += 16;
        flip ^= 1;
    } while (flip != 0);
}
