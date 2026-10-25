// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801811D4-0x801812B8 (228B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EAC;
extern s32 lbl_80305EC0;
s32 IsTrue(s32, void *);
s32 fn_801A6D80(Unk_93C2DF4D *, s32, s32);
void fn_801A6CF8(Unk_93C2DF4D *, s32, s32);
s32 fn_8017471C(void *, s32);
void fn_8009F310(CStruct *, Unk_15EF4A35 *, s32, s32, s32, s32);
void fn_801811D4(void *arg0, s32 arg1, s32 arg2) {
    register void *obj __asm__("r30");
    register s32 *p70 __asm__("r24");
    register s32 *p78 __asm__("r25");
    register s32 *p74 __asm__("r26");
    register s32 t31v __asm__("r31");
    register s32 t28v __asm__("r28");
    register s32 off __asm__("r29");
    register s32 cnt __asm__("r27");
    register s32 a0 __asm__("r21");
    register s32 a1 __asm__("r22");
    register s32 a2 __asm__("r23");

    a0 = (s32)arg0;
    a1 = arg1;
    obj = (void *)lbl_80305EAC;
    if (IsTrue(lbl_80305EC0, QB_IS_CAREER) != 0) {
        a2 = arg2;
        p70 = (s32 *)((char *)obj + 0x70);
        p78 = (s32 *)((char *)obj + 0x78);
        p74 = (s32 *)((char *)obj + 0x74);
        off = 0;
        cnt = 0x40;
        do {
            s32 t0 = *(s32 *)(off + (s32)p70);
            t31v = *(s32 *)(off + (s32)p78);
            t28v = *(s32 *)(off + (s32)p74);
            if ((t0 != 0) && (a1 < t0) && (a2 >= t0) && (fn_801A6D80(((Unk_C7387A53 *)obj)->unk0x24, t31v, -1) == 0)) {
                fn_801A6CF8(((Unk_C7387A53 *)obj)->unk0x24, t31v, -1);
                fn_8009F310(fn_8017471C(obj, ((Unk_667BA59C *)a0)->unk0xC), t28v, 0, 0, 0, 0);
            }
            off += 0xC;
        } while (--cnt != 0);
    }
}
