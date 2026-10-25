// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80227288-0x802273FC (372B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80008EB0(Unk_DB0E2BAB *);
void fn_80008ED4(Unk_DB0E2BAB *, s32, s32);
s32 fn_8000901C(Unk_DB0E2BAB *, s32);
void fn_800090F0(Unk_DB0E2BAB *, s32);
s32 fn_80008F10(Unk_C8FEE62D *);
bool fn_80227288(CStruct *arg0) {
    volatile u8 sp8[0x18];
    u8 temp_r29;
    s32 temp_r3;
    u8 var_r30;

    var_r30 = 0;
    fn_80008EB0((void *)sp8);
    fn_80008ED4((void *)sp8, arg0->unk0x0, 0x400);
    temp_r29 = fn_8000901C((void *)sp8, 8);
    do {
        if (((s32)temp_r29 >> var_r30) & 1) {
            fn_8000901C((void *)sp8, 0x10);
            temp_r3 = fn_8000901C((void *)sp8, 9);
            if (temp_r3 & 1) {
                fn_800090F0((void *)sp8, 0x10);
            }
            if (temp_r3 & 2) {
                fn_800090F0((void *)sp8, 0x10);
            }
            if (temp_r3 & 4) {
                fn_800090F0((void *)sp8, 0x10);
            }
            if (temp_r3 & 8) {
                fn_800090F0((void *)sp8, 0x10);
            }
            if (temp_r3 & 0x10) {
                fn_800090F0((void *)sp8, 0x10);
            }
            if (temp_r3 & 0x20) {
                fn_800090F0((void *)sp8, 0x10);
            }
            if (temp_r3 & 0x40) {
                fn_8000901C((void *)sp8, 4);
                fn_8000901C((void *)sp8, 6);
                fn_8000901C((void *)sp8, 1);
                fn_8000901C((void *)sp8, 1);
            }
            if (temp_r3 & 0x80) {
                fn_8000901C((void *)sp8, 8);
            }
            if (temp_r3 & 0x100) {
                fn_800090F0((void *)sp8, 0x20);
            }
        }
        var_r30 += 1;
    } while (var_r30 <= 7U);
    arg0->unk0x8 = fn_80008F10((void *)sp8);
    return true;
}
