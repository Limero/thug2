// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A362C-0x801A374C (288B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

void *fn_801A362C(void *arg0, Unk_FFAD6788 *arg1) {
    volatile s32 sp8;
    register s32 temp_r9 __asm__("r9");
    register s32 var_r7 __asm__("r7");
    char *var_r10;
    volatile char *var_r8;
    __ps_t *psd;
    __ps_t *pss;
    s32 t2;
    register void *a0 __asm__("r11");

    a0 = arg0;
    var_r10 = (char *)arg1;
    sp8 = ((Unk_9994C3F5 *)a0)->unk0x8;
    var_r8 = (char *)a0;
    var_r7 = 0x48;
    do {
        var_r7 -= 0x18;
        temp_r9 = ((Unk_DB0E2BAB *)var_r10)->unk0x0;
        ((Unk_DB0E2BAB *)var_r8)->unk0x0 = temp_r9;
        temp_r9 = ((Unk_DB0E2BAB *)var_r10)->unk0x4;
        ((Unk_DB0E2BAB *)var_r8)->unk0x4 = temp_r9;
        temp_r9 = ((Unk_DB0E2BAB *)var_r10)->unk0x8;
        ((Unk_DB0E2BAB *)var_r8)->unk0x8 = temp_r9;
        temp_r9 = ((Unk_DB0E2BAB *)var_r10)->unk0xC;
        ((Unk_DB0E2BAB *)var_r8)->unk0xC = temp_r9;
        temp_r9 = ((Unk_DB0E2BAB *)var_r10)->unk0x10;
        ((Unk_DB0E2BAB *)var_r8)->unk0x10 = temp_r9;
        temp_r9 = ((Unk_DB0E2BAB *)var_r10)->unk0x14;
        var_r10 += 0x18;
        ((Unk_DB0E2BAB *)var_r8)->unk0x14 = temp_r9;
        var_r8 += 0x18;
    } while (var_r7 != 0);
    temp_r9 = ((Unk_DB0E2BAB *)var_r10)->unk0x0;
    t2 = sp8;
    __asm__("" : "+r"(t2));
    ((Unk_DB0E2BAB *)var_r8)->unk0x0 = temp_r9;
    temp_r9 = ((Unk_DB0E2BAB *)var_r10)->unk0x4;
    ((Unk_DB0E2BAB *)var_r8)->unk0x4 = temp_r9;
    temp_r9 = ((Unk_DB0E2BAB *)var_r10)->unk0x8;
    ((Unk_DB0E2BAB *)var_r8)->unk0x8 = temp_r9;
    temp_r9 = ((Unk_DB0E2BAB *)var_r10)->unk0xC;
    ((Unk_DB0E2BAB *)var_r8)->unk0xC = temp_r9;
    ((Unk_9994C3F5 *)a0)->unk0x8 = t2;
    psd = (__ps_t *)((char *)a0 + (s32)0x58);
    pss = (__ps_t *)((char *)arg1 + (s32)0x58);
    psd[0] = pss[0];
    psd[1] = pss[1];
    psd[2] = pss[2];
    psd[3] = pss[3];
    psd[4] = pss[4];
    psd[5] = pss[5];
    psd[6] = pss[6];
    psd[7] = pss[7];
    psd[8] = pss[8];
    psd[9] = pss[9];
    psd[10] = pss[10];
    psd[11] = pss[11];
    *((f32 *)&((Unk_9994C3F5 *)a0)->unk0xB8) = *((f32 *)&arg1->unk0xB8);
    *((f32 *)&((Unk_9994C3F5 *)a0)->unk0xBC) = *((f32 *)&arg1->unk0xBC);
    ((Unk_9994C3F5 *)a0)->unk0xC0 = *((f32 *)&arg1->unk0xC0);
    *((f32 *)&((Unk_9994C3F5 *)a0)->unk0xC4) = *((f32 *)&arg1->unk0xC4);
    *((f32 *)&((Unk_9994C3F5 *)a0)->unk0xC8) = *((f32 *)&arg1->unk0xC8);
    ((Unk_9994C3F5 *)a0)->unk0xCC = *((f32 *)&arg1->unk0xCC);
    return a0;
}
