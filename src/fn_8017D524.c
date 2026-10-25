// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8017D524-0x8017DC0C (1768B). Byte-identical.
#include "types.h"
#include "structs.h"

static void *fn_80139510(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
extern s32 fn_801746A4(Unk_C7387A53 * arg0, s32 arg1);
extern s32 fn_80141FA4(Unk_5FCDF30E * o);

static void fn_8017C2CC(void);
static void fn_8017C8F4(void);
static void fn_8017981C(void);
static void fn_8017977C(void);
static void fn_8017A3F8(void);
static void fn_8017A4B8(void);
static void fn_8017A564(void);
static void fn_8017C1A8(void);
static void fn_8017C0F8(void);
static void fn_8017C170(void);
static void fn_8017BB28(void);
static void fn_801789F8(void);
static void fn_80179040(void);
static void fn_801790E0(void);
static void fn_8017A5C0(void);
static void fn_8017A6E4(void);
static void fn_8017B9C4(void);
static void fn_8017B7EC(void);
static void fn_8017B444(void);
static void fn_801796B4(void);
static void fn_801792D4(void);
static void fn_8017B268(void);
static void fn_80179654(void);
static void fn_8017A79C(void);
static void fn_8017AB84(void);
static void fn_8017B390(void);
static void fn_80182ADC(void);
static void fn_801CCB68(void);
static void fn_801CC75C(void);
static void fn_801C5AA0(void);

void fn_8017D524(Unk_C7387A53 *arg0, s32 arg1, s32 arg2) {
    s32 ctx;
    register s32 lctx __asm__("r22");
    s32 ctx3;
    u32 var_r21;
    Unk_FFAD6788 *temp_r3;

    ctx = arg1 + 4;
    fn_80139510(ctx, 0x33, (s32)fn_8017C2CC, 0, arg0, 0x80);
    fn_80139510(ctx, 0x23, (s32)fn_8017C8F4, 3, arg0, 0x80);
    fn_80139510(ctx, 0x29, (s32)fn_8017981C, 0, arg0, 0x80);
    fn_80139510(ctx, 0x7F, (s32)fn_8017977C, 0, arg0, 0x80);
    fn_80139510(ctx, 0x2B, (s32)fn_8017981C, 0, arg0, 0x80);
    fn_80139510(ctx, 0x76, (s32)fn_8017981C, 0, arg0, 0x80);
    var_r21 = 0U;
    fn_80139510(ctx, 0x8C, (s32)fn_8017981C, 0, arg0, 0x80);
    fn_80139510(ctx, 0x77, (s32)fn_8017981C, 0, arg0, 0x80);
    fn_80139510(ctx, 0x78, (s32)fn_8017981C, 0, arg0, 0x80);
    fn_80139510(ctx, 0x2A, (s32)fn_8017981C, 0, arg0, 0x80);
    fn_80139510(ctx, 0x2C, (s32)fn_8017981C, 0, arg0, 0xFF);
    fn_80139510(ctx, 0x2C, (s32)fn_8017A3F8, 0, arg0, 0x80);
    fn_80139510(ctx, 0x3C, (s32)fn_8017981C, 0, arg0, 0x80);
    fn_80139510(ctx, 0x3D, (s32)fn_8017981C, 0, arg0, 0x80);
    fn_80139510(ctx, 0x3E, (s32)fn_8017981C, 0, arg0, 0x80);
    fn_80139510(ctx, 0x41, (s32)fn_8017981C, 0, arg0, 0x80);
    fn_80139510(ctx, 0x2D, (s32)fn_8017A4B8, 2, arg0, 0x80);
    fn_80139510(ctx, 0x32, (s32)fn_8017A564, 2, arg0, 0x80);
    fn_80139510(ctx, 0x35, (s32)fn_8017C1A8, 0, arg0, 0x80);
    fn_80139510(ctx, 0x36, (s32)fn_8017C1A8, 0, arg0, 0x80);
    fn_80139510(ctx, 0x37, (s32)fn_8017C0F8, 0, arg0, 0x80);
    fn_80139510(ctx, 0x38, (s32)fn_8017C0F8, 0, arg0, 0x80);
    fn_80139510(ctx, 0x39, (s32)fn_8017C170, 0, arg0, 0x80);
    fn_80139510(ctx, 0x3A, (s32)fn_8017C170, 0, arg0, 0x80);
    fn_80139510(ctx, 0x40, (s32)fn_8017BB28, 2, arg0, 0x80);
    fn_80139510(ctx, 0x46, (s32)fn_801789F8, 0, arg0, 0x80);
    fn_80139510(ctx, 0x48, (s32)fn_80179040, 2, arg0, 0x80);
    fn_80139510(ctx, 0x49, (s32)fn_801790E0, 2, arg0, 0x80);
    fn_80139510(ctx, 0x51, (s32)fn_8017A5C0, 2, arg0, 0x80);
    fn_80139510(ctx, 0x56, (s32)fn_8017A5C0, 2, arg0, 0x80);
    fn_80139510(ctx, 0x5B, (s32)fn_8017A6E4, 0, arg0, 0x80);
    fn_80139510(ctx, 0x5C, (s32)fn_8017B9C4, 0, arg0, 0x80);
    fn_80139510(ctx, 0x7E, (s32)fn_8017B7EC, 0, arg0, 0x80);
    fn_80139510(ctx, 0x96, (s32)fn_8017B444, 0, arg0, 0x80);
    fn_80139510(ctx, 0x97, (s32)fn_8017B444, 0, arg0, 0x80);
    fn_80139510(ctx, 0x98, (s32)fn_8017B444, 0, arg0, 0x80);
    fn_80139510(ctx, 0x9A, (s32)fn_8017B444, 0, arg0, 0x80);
    fn_80139510(ctx, 0x82, (s32)fn_801796B4, 0, arg0, 0x80);
    fn_80139510(ctx, 0x83, (s32)fn_801792D4, 0, arg0, 0x80);
    fn_80139510(ctx, 0x8F, (s32)fn_8017B268, 0, arg0, 0x80);
    fn_80139510(ctx, 0x89, (s32)fn_80179654, 0, arg0, 0x80);
    fn_80139510(ctx, 0x95, (s32)fn_8017A79C, 0, arg0, 0x80);
    fn_80139510(ctx, 0x93, (s32)fn_8017A79C, 0, arg0, 0x80);
    fn_80139510(ctx, 0x90, (s32)fn_8017AB84, 0, arg0, 0x80);
    fn_80139510(ctx, 0x99, (s32)fn_8017B390, 0, arg0, 0x80);
    lctx = ctx;
    do {
        temp_r3 = (void *)fn_801746A4((s32)arg0, var_r21);
        if ((temp_r3 != NULL) && (temp_r3->unk0xC8 != 0) && (fn_80141FA4(temp_r3) == arg2)) {
            fn_80139510(lctx, 0x3B, (s32)fn_80182ADC, 0, temp_r3, 0x80);
            fn_80139510(lctx, 0x44, (s32)fn_801CCB68, 0, temp_r3, 0x80);
            fn_80139510(lctx, 0x43, (s32)fn_801CCB68, 0, temp_r3, 0x80);
            fn_80139510(lctx, 0x85, (s32)fn_801CC75C, 0, temp_r3, 0x80);
            fn_80139510(lctx, 0x84, (s32)fn_801CC75C, 0, temp_r3, 0x80);
            fn_80139510(lctx, 0x4B, (s32)fn_801C5AA0, 0, temp_r3, 0x80);
        }
        var_r21 += 1;
    } while (var_r21 <= 7U);
    if (arg2 == 0) {
        ctx3 = arg1 + 4;
        fn_80139510(ctx3, 0x91, (s32)fn_8017A79C, 0, arg0, 0x80);
        fn_80139510(ctx3, 0x92, (s32)fn_8017A79C, 0, arg0, 0x80);
        fn_80139510(ctx3, 0x94, (s32)fn_8017A79C, 0, arg0, 0x80);
    }
}
