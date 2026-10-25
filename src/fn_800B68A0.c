// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B68A0-0x800B6958 (184B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_80305F9C[];
s32 fn_8021D358(s32, u16);
s32 fn_8022986C(CScript *);
s32 fn_8022A9D0(void *);
s32 fn_8021B55C(s32, s32);
void fn_80137CB4(Unk_9F066EC1 *);
void fn_8013DE78(void *, Unk_C71E6DE1 *);
void fn_800B62A4(Unk_C7387A53 *);

void fn_800B68A0(Unk_C7387A53 *arg0) {
    struct {
        u8 mb;
        u16 mh;
        void *mp;
        char pad[0x20];
        u8 sp30;
    } fr;
    s32 temp_r29;
    s32 b55c;
    s32 temp_r3;

    fn_800B62A4((char *)arg0 + 0x40);
    fn_800B62A4((char *)arg0 + 0xD4);
    fn_800B62A4((char *)arg0 + 0x168);
    temp_r29 = *(s32 *)&lbl_80305F9C;
    temp_r3 = fn_8021D358(temp_r29, *(u16 *)(arg0->unk0xC + 0x1A));
    if ((temp_r3 != 0) && (fn_8022986C(temp_r3) != 0)) {
        fn_80137CB4(&fr);
        b55c = fn_8021B55C(temp_r29, fn_8022A9D0(temp_r3));
        fr.sp30 = (u8)*(volatile s32 *)(arg0->unk0xC + 0x18);
        fr.mp = &fr.sp30;
        fr.mh = 1;
        fr.mb = 0x8C;
        fn_8013DE78(b55c, &fr.mb);
    }
}