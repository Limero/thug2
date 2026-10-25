// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80169E00-0x80169E7C (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_80290B50[];
extern s32 BannerCheck(s32);
extern s32 fn_80015A58(s32, s32, s32);
extern void fn_800158D8(void);
extern s32 fn_80015B94(Unk_C8FEE62D *);
// EXACT 100% (31/31, 124B): ported the plain-C staging shape from the
// byte-identical sibling fn_80169D64. Keeping the BannerCheck result in a named
// handle, copying it through the local frame, and passing that handle to
// fn_80015A58 keeps the call's li r3,0 before the first message-slot store.
s32 ScriptCardIsForeign(void) {
    struct {
        s32 a;
        s32 b;
        s32 c;
        s32 d;
    } fr;
    s32 *ptr;
    s32 msg;
    s32 handle;
    s32 copy;
    s32 chk;
    s32 result;

    ptr = (s32 *)&fr;
    msg = (s32)lbl_80290B50;
    ptr[3] = msg;
    handle = BannerCheck(0);
    copy = handle;
    fr.c = copy;
    chk = fn_80015A58(handle, 0, 0);
    if (chk != 0) {
        result = fn_80015B94((Unk_C8FEE62D *)chk);
        ptr[3] = msg;
        fn_800158D8();
        return result;
    }
    ptr[3] = msg;
    fn_800158D8();
    return 0;
}
