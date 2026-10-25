// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801399D8-0x80139B00 (296B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

typedef struct A1 {
    char pad0x0[4];
    u8 f4;
    char pad0x5[0xF];
    s32 f14;
    s32 f18;
} A1;

typedef struct C {
    char pad0x0[0x18];
    s32 (*m18)(void *);
    s32 m1C;
    s32 m20;
} C;

extern char lbl_8029F350[];

s32 fn_801399D8(s32 arg0, A1 *arg1) {
    s32 sp8; char pad1[8];
    register s32 tag __asm__("r28");
    register s32 pg __asm__("r9");
    s32 temp_r3;
    s32 temp_r9_2;
    Unk_C7387A53 *temp_r9;
    CStruct *var_r10;
    register s32 cur __asm__("r10");
    register s32 nx __asm__("r11");
    s32 nxt;

    temp_r9 = (arg1->f4 * 0x18) + arg0;
    ((Unk_59AB5482 *)&sp8)->unk0x4 = (s32)temp_r9;
    ((Unk_59AB5482 *)&sp8)->unk0x8 = (s32)lbl_8029F350;
    var_r10 = temp_r9->unk0xC;
    if ((s32) var_r10->unk0x4 == -1) {
        var_r10 = NULL;
    }
    ((Unk_59AB5482 *)&sp8)->unk0x4 = (s32)var_r10;
    if (var_r10 == NULL) {
        __asm__("" : "+r"(var_r10));
        var_r10 = NULL;
    } else {
        var_r10 = (CStruct *)var_r10->unk0x4;
    }
    cur = (s32)var_r10;
    if (cur != 0) {
        __asm__ volatile("lis %0,%1@ha" : "=r"(pg) : "s"(lbl_8029F350));
        tag = (s32)pg - 0xCB0;
        __asm__("" : "+r"(tag));
loop_7:
        nx = (*(Unk_C7387A53 **)((char *)&sp8 + 4))->unk0xC;
        if ((s32) ((CStruct *)nx)->unk0x4 == -1) {
            nx = 0;
        }
        ((Unk_59AB5482 *)&sp8)->unk0x4 = nx;
        if (nx != 0) {
            nxt = ((CStruct *)nx)->unk0x4;
        } else {
            __asm__("" : "+r"(nx));
            nxt = 0;
        }
        temp_r9_2 = arg1->f14;
        if ((s32) (((C *)cur)->m20 & temp_r9_2) == temp_r9_2) {
            arg1->f18 = (s32) ((C *)cur)->m1C;
            temp_r3 = ((C *)cur)->m18(arg1);
            if ((temp_r3 == 0) || (temp_r3 == 2) || (temp_r3 == 5) || (temp_r3 == 3)) {
                ((Unk_59AB5482 *)&sp8)->unk0x8 = tag;
                return temp_r3;
            }
            if (temp_r3 != 4) {
                goto block_18;
            }
            goto block_19;
        }
block_18:
        cur = nxt;
        if (cur == 0) {
            goto block_19;
        }
        goto loop_7;
    }

block_19:
    __asm__("" : : "m"(pad1[0]));
    ((Unk_59AB5482 *)&sp8)->unk0x8 = (s32)lbl_8029F350;
    return 1;
}
