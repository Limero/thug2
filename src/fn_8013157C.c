// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013157C-0x801316D8 (348B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -Os
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void *fn_80125480(Unk_15EF4A35 *arg0);
void fn_8000F2F8(void *arg0, s32 arg1);
void fn_80032088(s32 arg0);
Unk_FFAD6788 *fn_8012ED98(void);
void fn_8000F320(void *arg0);
void fn_8012EE64(void *arg0, s32 arg1);
void fn_8012F260(void *arg0, void *arg1, void *arg2, void *arg3);
s32 CStruct_new(s32 arg0);
Unk_80577C09 *CStruct_ctor(s32 arg0);
void fn_80126F88(void *arg0, void *arg1);
s32 fn_8009CF2C(CStruct *arg0);
void fn_80131474(void *arg0, void *arg1, s32 arg2, s32 arg3);
extern char lbl_802FFE98[];
extern char lbl_80305F9C[];
// Script_SpawnScript @ 0x8013157C
void *Script_SpawnScript(Unk_15EF4A35 *arg0, Unk_C8FEE62D *arg1, s32 arg2, CStruct *arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp8, s32 arg_spC) {
    Unk_FFAD6788 *temp_r31;
    void *temp_r31_2;
    Unk_5AA7B5D7 *temp_r3;
    Unk_C7387A53 *temp_r3_2;
    Unk_80577C09 *temp_dc;
    CStruct *temp_g;
    union {
        u32 w;
        struct { u32 b31:1; u32 b30:1; u32 b29:1; u32 b28:1; u32 rest:28; } b;
    } u;

    temp_r3 = fn_80125480(arg0);
    if ((temp_r3 != NULL) && (*(u8 *)((char *)temp_r3 + 2) == 8)) {
        temp_r3_2 = *(void **)lbl_802FFE98;
        fn_8000F2F8(temp_r3_2, temp_r3_2->unk0x12C);
        fn_80032088(0xF8);
        temp_r31_2 = fn_8012ED98();
        fn_8000F320(*(void **)lbl_802FFE98);
        ((s32 (*)(void *, void *))temp_r3->unk0xC)(arg1, temp_r31_2);
        if (temp_r31_2 != NULL) {
            fn_8012EE64(temp_r31_2, 3);
        }
        return NULL;
    }
    fn_80032088(0xF8);
    temp_r31 = fn_8012ED98();
    fn_8012F260(temp_r31, arg0, arg1, NULL);
    temp_r31->unk0xD4 = arg5;
    temp_r31->unk0xB8 = arg4;
    u.w = (u32) ((temp_r31->unk0xCC | 0x80000000) & ~0x20000000);
    u.b.b30 = (u32) arg_sp8;
    u.b.b28 = (u32) arg_spC;
    temp_r31->unk0xCC = (s32) u.w;
    if (arg2 != 0) {
        temp_r31->unk0xD8 = arg2;
        temp_dc = CStruct_ctor(CStruct_new(8));
        temp_r31->unk0xDC = (s32)temp_dc;
        if (arg3 != 0) {
            fn_80126F88(temp_dc, arg3);
        }
    }
    temp_g = *(CStruct **)lbl_80305F9C;
    if ((arg6 != 0) && (fn_8009CF2C(temp_g) != 0)) {
        fn_80131474(arg0, 0, arg4, arg7);
    }
    return temp_r31;
}
