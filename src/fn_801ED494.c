// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801ED494-0x801ED4FC (104B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802AD924[];
extern s32 fn_8012587C(s32 hashstr, s32 len);
extern s32 fn_8020773C(Unk_90685748 * a, s32 b, s32 c, s32 d);
bool fn_801ED494(Unk_FF487DD2 *arg0) {
    s32 h;
    s32 t;

    h = fn_8012587C((s32)lbl_802AD924, 1);
    t = fn_8020773C(arg0->unk0x15AC, h, 0, 1);
    if (t != 0) {
        arg0->unk0x368 = -1;
        return true;
    }
    return false;
}
