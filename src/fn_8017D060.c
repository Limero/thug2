// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8017D060-0x8017D524 (1220B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_80303148[];
extern char lbl_80305F9C[];

static void *fn_80139510(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
extern s32 fn_8009CFA0(s32 arg0);
extern void fn_8021B3E0(s32 arg0);
extern s32 fn_8021A31C(s32 arg0, s32 arg1, s32 arg2);
extern void fn_8000A578(s32 arg0, s32 arg1);
extern s32 fn_8013E2BC(s32 arg0);

static void fn_80178284(void);
static void fn_801783B4(void);
static void fn_80178324(void);
static void fn_80178520(void);
static void fn_801789BC(void);
static void fn_80178A28(void);
static void fn_8017B094(void);
static void fn_8017AC00(void);
static void fn_8017B7EC(void);
static void fn_8017B444(void);
static void fn_801784C8(void);
static void fn_801786EC(void);
static void fn_80178888(void);

void fn_8017D060(CScript *arg0) {
    s32 var_r29;
    s32 temp_r30;
    s32 temp_r31;
    s32 temp_r3;

    temp_r31 = *(s32 *)&lbl_80305F9C;
    temp_r30 = *(s32 *)&lbl_80303148;
    var_r29 = 0;
    if (fn_8009CFA0(temp_r31) != 0) {
        var_r29 = 1;
        fn_8021B3E0(temp_r31);
    }
    temp_r3 = fn_8021A31C(temp_r31, var_r29 ^ 1, 1);
    if (temp_r3 != 0) {
        temp_r30 += 8;
        temp_r31 = temp_r3 + 4;
        fn_8000A578(temp_r30, arg0->unk0x1C);
        fn_8000A578(temp_r30, arg0->unk0x20);
        fn_80139510(temp_r31, 0x3B, (s32)fn_80178284, 0, 0, 0x80);
        fn_80139510(temp_r31, 0x52, (s32)fn_801783B4, 0, (s32)arg0, 0x80);
        fn_80139510(temp_r31, 0x86, (s32)fn_80178324, 0, (s32)arg0, 0x80);
        fn_80139510(temp_r31, 0x4C, (s32)fn_80178520, 2, 0, 0x80);
        fn_80139510(temp_r31, 0x45, (s32)fn_801789BC, 2, 0, 0x80);
        fn_80139510(temp_r31, 0x23, (s32)fn_80178A28, 3, 0, 0x80);
        fn_80139510(temp_r31, 0x8F, (s32)fn_8017B094, 0, (s32)arg0, 0x80);
        fn_80139510(temp_r31, 0x90, (s32)fn_8017AC00, 0, (s32)arg0, 0x80);
        if (fn_8013E2BC(temp_r3) == 0) {
            fn_80139510(temp_r31, 0x7E, (s32)fn_8017B7EC, 0, 0, 0x80);
            fn_80139510(temp_r31, 0x97, (s32)fn_8017B444, 0, (s32)arg0, 0x80);
            fn_80139510(temp_r31, 0x98, (s32)fn_8017B444, 0, (s32)arg0, 0x80);
            fn_80139510(temp_r31, 0x9A, (s32)fn_8017B444, 0, (s32)arg0, 0x80);
            fn_80139510(temp_r31, 0x83, (s32)fn_80178520, 0, (s32)arg0, 0x80);
            fn_80139510(temp_r31, 0x99, (s32)fn_80178520, 0, 0, 0x80);
            fn_80139510(temp_r31, 0x89, (s32)fn_80178520, 0, 0, 0x80);
            fn_80139510(temp_r31, 0x89, (s32)fn_801784C8, 0, 0, 0x80);
            fn_80139510(temp_r31, 0x29, (s32)fn_80178520, 0, 0, 0x80);
            fn_80139510(temp_r31, 0x2B, (s32)fn_801786EC, 0, 0, 0x80);
            fn_80139510(temp_r31, 0x2A, (s32)fn_80178520, 0, 0, 0x80);
            fn_80139510(temp_r31, 0x76, (s32)fn_80178520, 0, 0, 0x80);
            fn_80139510(temp_r31, 0x8C, (s32)fn_80178520, 0, 0, 0x80);
            fn_80139510(temp_r31, 0x77, (s32)fn_80178520, 0, 0, 0x80);
            fn_80139510(temp_r31, 0x78, (s32)fn_80178520, 0, 0, 0x80);
            fn_80139510(temp_r31, 0x2C, (s32)fn_80178520, 0, 0, 0x80);
            fn_80139510(temp_r31, 0x3C, (s32)fn_801786EC, 0, 0, 0x80);
            fn_80139510(temp_r31, 0x3D, (s32)fn_80178520, 0, 0, 0x80);
            fn_80139510(temp_r31, 0x3E, (s32)fn_80178520, 0, 0, 0x80);
            fn_80139510(temp_r31, 0x41, (s32)fn_80178520, 0, 0, 0x80);
            fn_80139510(temp_r31, 0x35, (s32)fn_801786EC, 0, 0, 0x80);
            fn_80139510(temp_r31, 0x36, (s32)fn_80178520, 0, 0, 0x80);
            fn_80139510(temp_r31, 0x39, (s32)fn_80178520, 0, 0, 0x80);
            fn_80139510(temp_r31, 0x3A, (s32)fn_80178520, 0, 0, 0x80);
            fn_80139510(temp_r31, 0x37, (s32)fn_80178520, 0, 0, 0x80);
            fn_80139510(temp_r31, 0x38, (s32)fn_80178520, 2, 0, 0x80);
            fn_80139510(temp_r31, 0x48, (s32)fn_80178888, 2, 0, 0x80);
            fn_80139510(temp_r31, 0x49, (s32)fn_80178888, 2, 0, 0x80);
        }
    }
}
