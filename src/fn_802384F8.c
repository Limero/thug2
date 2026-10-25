// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802384F8-0x8023862C (308B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80239ECC(void *);
void fn_802432A8(void *);
s32 fn_80239924(void *, void *);
s32 fn_802399E8(void *, void *, s32, s32, s32, void *);
void fn_80239CF4(void *);
void fn_80239D84(void *, s32);
void fn_80239E18(void *, void *);

bool fn_802384F8(Unk_C8FEE62D *arg0, Unk_897A0ACF *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 sp8;
    s32 r28;

    r28 = 4;
    if (arg4 != 0) {
        r28 = 6;
    }
    if (arg5 != 0) {
        r28 |= 1;
    }
    fn_80239ECC(arg0);
    if (arg0->unk0xC != 0) {
        fn_802432A8(arg0->unk0xC);
    }
    arg0->unk0xC = 0;
    arg0->unk0x10 = 0;
    arg0->unk0x14 = 0;
    if (arg5 != 0) {
        *(s32 *)&sp8 = *(s32 *)arg1;
        ((Unk_638CF717 *)&sp8)->unk0x4 = arg1->unk0x4;
        if (fn_80239924(arg0, &sp8) != 0) {
            return false;
        }
    }
    *(s32 *)&sp8 = *(s32 *)arg1;
    ((Unk_638CF717 *)&sp8)->unk0x4 = arg1->unk0x4;
    if (fn_802399E8(arg0, &sp8, arg2, arg3, r28, (char *)arg0 + 0xC) != 1) {
        fn_80239CF4(arg0);
        return false;
    }
    fn_80239D84(arg0, arg0->unk0xC);
    if (arg4 == 0) {
        *(s32 *)&sp8 = *(s32 *)arg1;
        ((Unk_638CF717 *)&sp8)->unk0x4 = arg1->unk0x4;
        fn_80239E18(arg0, &sp8);
    }
    return true;
}
