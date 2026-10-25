// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80031EC8-0x80031FA0 (216B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305F9C;
void fn_80031FA0(Unk_C8FEE62D *, s32);
s32 fn_8022986C(CScript *);
void *fn_8021D358(s32, u16);
void fn_80137CB4(void *);
s32 fn_8021B55C(void *, s32);
void fn_8013DE78(void *, void *);
s32 fn_8022A9D0(void *);

s32 fn_80031EC8(Unk_C8FEE62D *arg0, s32 arg1, void *arg2, s32 arg3, s32 arg4) {
    struct {
        u8 op;       /* +0x00 */
        u8 _pad1;
        u16 nargs;   /* +0x02 */
        void *args;  /* +0x04 */
        char _rest[0x20];
    } msg;
    u16 sp30;
    register s32 temp_r29 __asm__("r29");
    s32 temp_r30;
    s32 temp_r3;
    s32 b55c;
    register s32 hi8 __asm__("r0");
    u8 lo8;
    if ((arg4 != 0) && (arg0->unk0x30 == 0)) {
        temp_r29 = lbl_80305F9C;
        temp_r3 = (s32)fn_8021D358(temp_r29, (u16)arg1);
        if ((temp_r3 != 0) && (fn_8022986C(temp_r3) != 0)) {
            fn_80137CB4(&msg);
            b55c = fn_8021B55C(temp_r29, fn_8022A9D0(temp_r3));
            hi8 = (u8)arg1;
            lo8 = (u8)arg2;
            __asm__("slwi %0,%0,8" : "+r"(hi8));
            __asm__("or %0,%0,%1" : "+r"(hi8) : "r"(lo8));
            sp30 = (u16)hi8;
            msg.args = &sp30;
            msg.nargs = 2;
            msg.op = 0x2C;
            fn_8013DE78(b55c, &msg);
        }
    }
    temp_r30 = (u32)arg0->unk0x64 >> 0x1D & 1;
    fn_80031FA0(arg0, (void *)arg2);
    return temp_r30;
}
