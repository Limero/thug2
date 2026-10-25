// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F0DC8-0x801F0E84 (188B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_80305F9C[];
void *fn_8021D358(s32, s32);
s32 fn_8022986C(CScript *);
void fn_80137CB4(Unk_9F066EC1 *);
s32 fn_8022A9D0(void *);
s32 fn_8021B55C(void *, s32);
void fn_8013DE78(void *, Unk_C71E6DE1 *);
typedef struct {
    s8 unk0;
    s16 unk2;
    s16 *unk4;
    char pad0x8[0x20];
} Rec_801F0DC8;
s32 fn_801F0DC8(Unk_31DE137E *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s16 sp30;
    Rec_801F0DC8 sp8;
    void *t30;
    s32 t3;
    s32 x;
    s32 ret;
    if (arg4 != 0) {
        t30 = *(void **)&lbl_80305F9C;
        t3 = (s32)fn_8021D358((s32)t30, (u16)arg1);
        if (t3 != 0 && fn_8022986C((CScript *)t3) != 0) {
            fn_80137CB4((Unk_9F066EC1 *)&sp8);
            x = fn_8021B55C(t30, fn_8022A9D0((void *)t3));
            sp30 = (s16)((u8)arg2 | ((u8)arg1 << 8));
            sp8.unk4 = &sp30;
            sp8.unk0 = 0x2A;
            sp8.unk2 = 2;
            fn_8013DE78((void *)x, (Unk_C71E6DE1 *)&sp8);
        }
    }
    ret = arg0->unk0x1C;
    arg0->unk0x1C = arg2;
    return ret;
}
