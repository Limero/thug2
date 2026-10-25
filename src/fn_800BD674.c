// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800BD674-0x800BD770 (252B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
extern char lbl_80298E3C[];
extern char lbl_80298E40[];
extern char lbl_80298E44[];
extern char lbl_80298E48[];
extern void Mem_Free2(void *);
extern void *Mem_Alloc(s32);
typedef struct { char pad0x0[0x64]; s32 unk0x64; char pad0x68[0x2C]; u16 unk0x94; } S_d674;
typedef struct { f32 a; f32 b; f32 c; f32 d; } Rec_d674;
void fn_800BD674(S_d674 *arg0, f32 farg0, f32 farg1) {
    volatile double _dummy;
    volatile double _dummy2;
    f32 c_f12;
    f32 temp_f0;
    f32 temp_f10;
    f32 temp_f13;
    f32 c_f11;
    f32 r_f13;
    f32 r_f0;
    register u32 var_r9 __asm__("r9");
    register u32 pgB __asm__("r10");
    register u32 pgC __asm__("r11");
    u16 var_r30;
    Rec_d674 *temp_r3;

    arg0->unk0x94 = 5U;
    if (arg0->unk0x64 != NULL) {
        Mem_Free2((void *) arg0->unk0x64);
    }
    var_r30 = arg0->unk0x94;
    temp_r3 = (Rec_d674 *)Mem_Alloc(var_r30 * 0x10);
    temp_f10 = -farg1;
    var_r9 = var_r30 - 1;
    if ((s32)var_r30 != 0) {
        while (var_r9-- != 0) {
        }
    }
    __asm__ volatile("lis %0,%1@ha" : "=r"(var_r9) : "s"(lbl_80298E3C));
    __asm__ volatile("lis %0,%1@ha" : "=r"(pgB) : "s"(lbl_80298E40));
    c_f12 = *(f32 *)((char *)pgB - 0x71C0);
    __asm__ volatile("lis %0,%1@ha" : "=r"(pgC) : "s"(lbl_80298E48));
    r_f13 = *(f32 *)((char *)var_r9 - 0x71C4);
    r_f0 = *(f32 *)((char *)pgC - 0x71B8);
    __asm__ volatile("lis %0,%1@ha" : "=r"(var_r9) : "s"(lbl_80298E44));
    c_f11 = *(f32 *)((char *)var_r9 - 0x71BC);
    temp_f13 = farg0 * r_f13;
    temp_r3[4].d = c_f12;
    temp_f0 = farg0 * r_f0;
    arg0->unk0x64 = (s32)temp_r3;
    temp_r3[3].a = farg1;
    temp_r3[3].b = temp_f13;
    temp_r3[3].c = temp_f10;
    temp_r3[4].b = temp_f0;
    temp_r3[4].c = c_f11;
    temp_r3[0].a = farg1;
    temp_r3[0].b = temp_f13;
    temp_r3[0].c = farg1;
    temp_r3[0].d = c_f12;
    temp_r3[1].a = temp_f10;
    temp_r3[1].b = temp_f13;
    temp_r3[1].c = farg1;
    temp_r3[1].d = c_f12;
    temp_r3[2].a = temp_f10;
    temp_r3[2].b = temp_f13;
    temp_r3[2].c = temp_f10;
    temp_r3[2].d = c_f12;
    temp_r3[3].d = c_f12;
    temp_r3[4].a = c_f11;
}
