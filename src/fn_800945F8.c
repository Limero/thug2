// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800945F8-0x80094858 (608B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    f32 f0;
    f32 pad4;
    f32 f8;
    char padC[0xC];
} T945F8row;

typedef struct {
    u32 unk0x0;
    char pad0x4[4];
    T945F8row *unk0x8;
    u8 map0xC[0x100];
    u8 map0x10C[0x30];
    s32 unk0x13C;
    char pad0x140[4];
    f32 unk0x144;
    f32 unk0x148;
} T945F8;

typedef struct {
    u8 sp8;
    char pad0x9[0x2F];
    volatile u32 w0;
    volatile u32 w1;
} T945F8fr;

extern f32 lbl_80297250;
extern f64 lbl_80297258;
extern f64 lbl_80297260;
extern T945F8 *lbl_80301840;
extern s32 DehexifyDigit(u8 *);
extern s32 fn_800537FC(u8 *);

void fn_800945F8(T945F8 *arg0, u8 *arg1, f32 *arg2, f32 *arg3) {
    register f32 var_f28 __asm__("fr28");
    register f32 var_f30 __asm__("fr30");
    register f32 var_f31 __asm__("fr31");
    register f64 var_f29 __asm__("fr29");
    register f32 var_f0 __asm__("fr0");
    f32 var_f13;
    f32 *var_f31p;
    register s32 var_r10 __asm__("r10");
    T945F8row *var_r11_2;
    u8 *var_r31;
    u8 *var_r3;
    s32 var_r9;
    register s32 var_pg __asm__("r11");
    register s32 var_r9b __asm__("r9");
    s32 var_r9c;
    T945F8 *var_r30;
    u8 var_r0;
    s32 var_sc;
    T945F8fr fr;
    u32 var_magic;
    f64 var_c;

    var_f31p = &lbl_80297250;
    var_f28 = arg0->unk0x144;
    var_f29 = lbl_80297258;
    var_f30 = arg0->unk0x148;
    var_f31 = *var_f31p;
    var_r31 = arg1;
    var_magic = 0x43300000;
loop_1:
    var_r11_2 = 0;
    var_r30 = arg0;
    var_r10 = 0;
    if (*var_r31 == '\\') {
        var_r31 += 1;
        if (*var_r31 == '\\') {
            goto body;
        }
        do {
            char *pg = (char *)0x80300000;
            switch ((s8)*var_r31) {
            case '\\':
                var_r10 = 1;
                break;
            case 'S':
            case 's':
                var_r31 += 1;
                var_r9 = DehexifyDigit(var_r31);
                var_r9b = arg0->map0x10C[var_r9];
                var_r11_2 = arg0->unk0x8;
                var_r10 = 1;
                goto blk_mul;
            case 'B':
            case 'b':
                var_r31 += 1;
                var_r3 = var_r31;
                goto blk_cvt;
            case 'M':
            case 'm':
                var_r31 += 1;
                fr.sp8 = fn_800537FC(var_r31);
                var_r3 = &fr.sp8;
blk_cvt:
                var_r9 = DehexifyDigit(var_r3);
                var_r30 = *(T945F8 **)(pg + 0x1840);
                var_r10 = 1;
                var_r9b = var_r30->map0x10C[var_r9];
                var_r11_2 = var_r30->unk0x8;
blk_mul:
                var_r11_2 = &var_r11_2[var_r9b];
                break;
            case 'L':
                var_r31 += 1;
                break;
            case 'U':
            case 'C':
            case 'c':
            case 'u':
                var_r31 += 2;
                break;
            }
            if (*var_r31 != '\\' || var_r10 != 0) {
                break;
            }
            var_r31 += 1;
        } while (*var_r31 != '\\');
    }
body:
    var_r0 = *var_r31;
    var_sc = (s8)var_r0;
    __asm__("" :: "r"(var_sc));
    if (var_sc == 0) {
        goto end;
    }
    if (var_sc == ' ' && var_r11_2 == 0) {
        goto space;
    }
    if (var_r11_2 == 0) {
        var_r9c = ((u8 *)var_r30)[var_r0 + 0xC];
        var_r11_2 = &var_r30->unk0x8[var_r9c];
    }
    {
        f32 a_ = var_r11_2->f8;
        f32 b_ = var_r11_2->f0;
        fr.w1 = (u32)arg0->unk0x13C ^ 0x80000000;
        __asm__ __volatile__("fsubs %0,%0,%1" : "+f"(a_) : "f"(b_));
        var_f13 = a_;
    }
    fr.w0 = var_magic;
    var_f0 = var_f13 * (f32)(*(volatile f64 *)&fr.w0 - var_f29) + var_f31;
    goto join;
space:
    var_f0 = var_f31 + var_f30;
join:
    var_f31 = var_f0 + var_f28;
    var_r31 += 1;
    goto loop_1;
end:
    *arg2 = var_f31;
    __asm__("lis %0,0x4330\n\tlis %1,0x8029" : "=r"(var_r10), "=r"(var_pg));
    var_c = *(volatile f64 *)((char *)var_pg + 0x7260);
    fr.w1 = arg0->unk0x0;
    fr.w0 = var_r10;
    *arg3 = (f32)(*(volatile f64 *)&fr.w0 - var_c);
}
