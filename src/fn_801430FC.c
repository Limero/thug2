// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801430FC-0x80143258 (348B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_8029F808[];
extern char lbl_8029F80C[];
extern char lbl_8029F810[];
extern s32 lbl_80305F9C;
#include "qb_constants.h"
#include "structs.h"
/* fn_801427A4 is really 2-arg (reads r3+r4) but WANT's call site passes
   nothing, so the no-arg spelling is the one that matches. */
static void fn_801427A4(void);
static s32 ScriptInMultiplayerGame(s32 arg0, s32 arg1);
static s32 fn_8021B55C(s32 arg0, s32 arg1);
static void *fn_80139510(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
static void *GetChecksum_3(void *arg0, u32 arg1);
/* Address-taken only (1-arg each per their own prologues) -- the arity is
   irrelevant to this object's codegen. */
static void fn_80182ADC(void);
static void fn_801CCB68(void);
static void fn_801CC75C(void);
static void fn_801C5AA0(void);
void fn_801430FC(void *arg0) {
    register s32 self __asm__("r31");
    register s32 temp_r30 __asm__("r30");
    Unk_C7387A53 *temp_r3;
    register s32 pa __asm__("r11");
    register s32 pc __asm__("r10");
    register s32 pb __asm__("r9");
    register f32 f_a __asm__("fr12");
    register f32 f_b __asm__("fr13");
    register f32 f_c __asm__("fr0");

    self = (s32)arg0;
    fn_801427A4();
    temp_r30 = lbl_80305F9C;
    if ((((Unk_9472DC69 *)self)->unk0xC8 != 0) && (ScriptInMultiplayerGame(0, 0) != 0)) {
        temp_r30 = fn_8021B55C(temp_r30, ((Unk_9472DC69 *)self)->unk0x2E8) + 4;
        fn_80139510(temp_r30, 0x3B, (s32)fn_80182ADC, 0, self, 0x80);
        fn_80139510(temp_r30, 0x44, (s32)fn_801CCB68, 0, self, 0x80);
        fn_80139510(temp_r30, 0x43, (s32)fn_801CCB68, 0, self, 0x80);
        fn_80139510(temp_r30, 0x85, (s32)fn_801CC75C, 0, self, 0x80);
        fn_80139510(temp_r30, 0x84, (s32)fn_801CC75C, 0, self, 0x80);
        fn_80139510(temp_r30, 0x4B, (s32)fn_801C5AA0, 0, self, 0x80);
    }
    temp_r3 = GetChecksum_3((void *)self, QB_SUSPEND);
    if (temp_r3 != NULL) {
        __asm__ volatile ("lis %0,%3@ha\n\tlis %1,%4@ha\n\tlis %2,%5@ha"
                          : "=r"(pa), "=r"(pc), "=r"(pb)
                          : "s"(lbl_8029F808), "s"(lbl_8029F80C), "s"(lbl_8029F810));
        f_a = *(f32 *)((char *)pa - 0x7F8);
        f_b = *(f32 *)((char *)pb - 0x7F0);
        f_c = *(f32 *)((char *)pc - 0x7F4);
        *((f32 *)&temp_r3->unk0x44) = f_b;
        *((f32 *)&temp_r3->unk0x3C) = f_a;
        *((f32 *)&temp_r3->unk0x40) = f_c;
        *((f32 *)&temp_r3->unk0x48) = f_b;
    }
}
