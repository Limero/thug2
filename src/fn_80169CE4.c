// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80169CE4-0x80169D64 (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_80290B50[];
extern s32 BannerCheck(s32);
extern s32 fn_80015A58(s32, s32, s32);
extern void fn_800158D8(void);
bool ScriptSectorSizeOK(void) {
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
    Unk_9994C3F5 *chk;

    ptr = (s32 *)&fr;
    msg = (s32)lbl_80290B50;
    ptr[3] = msg;
    handle = BannerCheck(0);
    copy = handle;
    fr.c = copy;
    chk = (Unk_9994C3F5 *)fn_80015A58(handle, 0, 0);
    if ((chk != NULL) && (chk->unk0x8 == 0x2000)) {
        ptr[3] = msg;
        fn_800158D8();
        return true;
    }
    ptr[3] = msg;
    fn_800158D8();
    return false;
}
