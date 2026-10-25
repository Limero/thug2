// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802281CC-0x802282B8 (236B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802B010C[];
extern char lbl_802B0160[];
s32 fn_801FC0E0(void);
s32 fn_801FA284(s32);
s32 fn_80222D6C(s32);
s32 fn_80222DFC(Unk_C5BAE83F *);
s32 fn_80222DF4(void *);
void fn_8013DC7C(s32, s32, s32, s32, void *, void *, s32, s32, s32);

bool fn_802281CC(Unk_71EAD930 *arg0) {
    u8 cmd;
    s32 f_c;
    s32 f_18;

    cmd = arg0->unk0x4;
    f_c = arg0->unk0xC;
    f_18 = arg0->unk0x18;
    if (cmd == 0x8B) {
        void *t = arg0->unk0x10;
        s32 t48 = ((Unk_C7387A53 *)t)->unk0x48;
        s32 tr7;
        fn_801FC0E0();
        tr7 = fn_801FA284(fn_801FC0E0());
        fn_8013DC7C(f_c, t48, 0x88, 0x1132, tr7, (s32)lbl_802B0160, 8, 0, 1);
    } else if ((cmd == 0x8A) && (fn_80222D6C(f_18) != 0)) {
        void *t = arg0->unk0x10;
        s32 t48 = ((Unk_C7387A53 *)t)->unk0x48;
        u16 u16v = (u16)fn_80222DFC(f_18);
        s32 tr7 = fn_80222DF4(f_18);
        fn_8013DC7C(f_c, t48, 0x87, u16v, tr7, (s32)lbl_802B010C, 8, 0, 1);
    }
    return true;
}
