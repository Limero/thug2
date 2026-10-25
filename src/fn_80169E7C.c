// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80169E7C-0x80169F04 (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_80290B50[];
extern s32 BannerCheck(s32);
extern s32 fn_80015A58(s32, s32, s32);
extern void fn_800158D8(void);
bool ScriptBadDevice(void) {
    struct {
        s32 pad0;
        s32 pad4;
        s32 handle;
        s32 msg;
    } blk;
    s32 *p1;
    s32 *p2;
    s32 msg;

    p1 = &blk.pad0;
    p2 = &blk.pad4;
    msg = (s32)lbl_80290B50;
    p1[3] = msg;
    p2[1] = BannerCheck(0);
    if ((fn_80015A58(p2[1], 0, 0) != 0) || (((Unk_C8FEE62D *)p2[1])->unk0x28 == 0)) {
        p1[3] = msg;
        fn_800158D8();
        return false;
    }
    p1[3] = msg;
    fn_800158D8();
    return true;
}
