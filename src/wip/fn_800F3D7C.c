// UPDATED 2026-09-13 (c): extended flag matrix (recipe 49) found `-fno-expensive-optimizations` -> 30.16% to 42.86%.
// PARKED 2026-08-31: needs full manual frame rebuild (m2c got the whole
// frame wrong: want stwu -0x120/stmw r26@0x108 with the sp8 slot at r1+8;
// this body compiles to -0x28 / stmw r26@0x10 — every stack-relative word
// differs). Fixed the bogus `memcpy(var_r31, arg2)` m2c line (want is
// fn_8026AE28(arg1, arg2) before the count store at +0x24). References the
// doc-49 pool functions (fn_8000F320 pop, fn_8000F2F8, fn_800F36C8); part
// of the same memory-pool allocator subsystem. Same-family as fn_800F36C8.
// family=m2c range=0x800F3D7C-0x800F3E78 size=252B (compiles now; DIFF).
// FLAG: -fno-expensive-optimizations
#include "types.h"
#include "structs.h"
extern char lbl_8029B5CC[];
extern char lbl_8029B5EC[];
extern char lbl_802FFE98[];
void fn_8001075C(s32 *);
void fn_800F36C8(void *, s32, s32, s32, s32, s32);
void fn_8000F2F8(Unk_9F352E7C *, s32);
void fn_8001BC9C(s32);
void sprintf(void *, char *);
s32 Mem_Alloc_3(s32);
void memcpy(s32, s32);
void fn_80010760(void);
void fn_8000F320(Unk_F12C5E01 *);
s32 fn_800F3D7C(Unk_C7387A53 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 sp8;
    s32 var_r31;
    Unk_C7387A53 *temp_r3;
    Unk_C7387A53 *temp_r9;

    var_r31 = arg1;
    fn_8001075C((s32)lbl_8029B5CC);
    fn_800F36C8(arg0, var_r31, arg2, arg3, arg4, arg5);
    if (arg3 != 0) {
        temp_r3 = *(void * *)&lbl_802FFE98;
        fn_8000F2F8(temp_r3, temp_r3->unk0x164);
        fn_8001BC9C(0);
        sprintf(&sp8, lbl_8029B5EC);
        fn_8001075C(&sp8);
        arg0->unk0x24 = Mem_Alloc_3(arg2);
        memcpy(var_r31, arg2);
        var_r31 = arg0->unk0x24;
        fn_80010760();
        fn_8000F320(*(void * *)&lbl_802FFE98);
        fn_8001BC9C(3);
    }
    temp_r9 = arg0->unk0x50;
    ((s32 (*)(void *, void *, void *))temp_r9->unk0x74)((char *)arg0 + temp_r9->unk0x70, var_r31, arg2);
    fn_80010760();
    return 0;
}