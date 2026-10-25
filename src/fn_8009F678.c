// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009F678-0x8009F7A4 (300B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f32 lbl_80297B54;
extern f32 lbl_80297B58;
extern char lbl_80297C08[];
void fn_8009E004(void *);

typedef struct F678 {
    char pad0x0[0x8];
    s32 unk0x8;
    s32 unk0xC;
    char pad0x10[0x48];
    f32 f0x58;
    f32 f0x5C;
    f32 f0x60;
    f32 f0x64;
    char pad0x68[0x10];
    f32 f0x78;
    f32 f0x7C;
    f32 f0x80;
    f32 f0x84;
    f32 f0x88;
    f32 f0x8C;
    f32 f0x90;
    f32 f0x94;
    f32 f0x98;
    f32 f0x9C;
    f32 f0xA0;
    f32 f0xA4;
    f32 f0xA8;
    f32 f0xAC;
    f32 f0xB0;
    f32 f0xB4;
    f32 f0xB8;
    f32 f0xBC;
    f32 f0xC0;
    f32 f0xC4;
    s32 unk0xC8;
    char pad0xCC[0x4];
    f32 f0xD0;
    f32 f0xD4;
    f32 f0xD8;
    f32 f0xDC;
    f32 f0xE0;
    f32 f0xE4;
    f32 f0xE8;
    f32 f0xEC;
    f32 f0xF0;
    f32 f0xF4;
    f32 f0xF8;
    f32 f0xFC;
    f32 f0x100;
    f32 f0x104;
    f32 f0x108;
    f32 f0x10C;
    s32 unk0x110;
    s32 unk0x114;
} F678;

typedef struct F678V {
    char _p[0x4];
    f32 a;
    f32 b;
    f32 c;
} F678V;

void *fn_8009F678(F678 *arg0) {
    f32 temp_f0;
    f32 temp_f13;
    s32 var_ctr;
    s32 var_ctr_2;
    F678V *temp_r7;
    F678V *temp_r8;

    fn_8009E004(arg0);
    var_ctr = 4;
    arg0->unk0x8 = (s32)lbl_80297C08;
    do {
        var_ctr -= 1;
    } while (var_ctr != 0);
    temp_r8 = (F678V *)((char *)arg0 + 0xB8);
    var_ctr_2 = 4;
    temp_r7 = (F678V *)((char *)arg0 + 0x58);
    do {
        var_ctr_2 -= 1;
    } while (var_ctr_2 != 0);
    temp_f0 = lbl_80297B54;
    temp_f13 = lbl_80297B58;
    arg0->unk0x114 = 0;
    arg0->f0xB8 = temp_f0;
    temp_r8->a = temp_f0;
    temp_r8->b = temp_f0;
    temp_r8->c = temp_f13;
    arg0->f0x58 = temp_f0;
    temp_r7->a = temp_f0;
    temp_r7->b = temp_f0;
    temp_r7->c = temp_f13;
    arg0->f0x78 = temp_f13;
    arg0->f0x7C = temp_f0;
    arg0->f0x80 = temp_f0;
    arg0->f0x84 = temp_f0;
    arg0->f0x88 = temp_f0;
    arg0->f0x8C = temp_f13;
    arg0->f0x90 = temp_f0;
    arg0->f0x94 = temp_f0;
    arg0->f0x98 = temp_f0;
    arg0->f0x9C = temp_f0;
    arg0->f0xA0 = temp_f13;
    arg0->f0xA4 = temp_f0;
    arg0->f0xA8 = temp_f0;
    arg0->f0xAC = temp_f0;
    arg0->f0xB0 = temp_f0;
    arg0->f0xB4 = temp_f13;
    arg0->f0xD0 = temp_f13;
    arg0->f0xD4 = temp_f0;
    arg0->f0xD8 = temp_f0;
    arg0->f0xDC = temp_f0;
    arg0->f0xE0 = temp_f0;
    arg0->f0xE4 = temp_f13;
    arg0->f0xE8 = temp_f0;
    arg0->f0xEC = temp_f0;
    arg0->f0xF0 = temp_f0;
    arg0->f0xF4 = temp_f0;
    arg0->f0xF8 = temp_f13;
    arg0->f0xFC = temp_f0;
    arg0->f0x100 = temp_f0;
    arg0->f0x104 = temp_f0;
    arg0->f0x108 = temp_f0;
    arg0->f0x10C = temp_f13;
    arg0->unk0x110 = 0;
    arg0->unk0x114 = 0;
    arg0->unk0xC8 = 0;
    arg0->unk0xC = (s32) (arg0->unk0xC | 0x20);
    return arg0;
}
