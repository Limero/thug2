// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800553EC-0x8005546C (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// ID: tagged-arg forwarder — logs via fn_8001075C(lbl_8029317C string)
// then tail-forwards all 8 args to fn_800771FC, finishing with the
// fn_80010760 leave. EXACT via raw-lit→symbol patch (doc-51).
// Suggested rename: LogAndForward8Args.
#include "types.h"
#include "structs.h"
extern char lbl_8029317C[];
s32 fn_800771FC(s32, s32, s32, s32, s32, s32, s32, s32);
void fn_8001075C(s32);
s32 fn_800553EC(Unk_FFAD6788 *arg0, Unk_78674569 *arg1, s32 arg2, Unk_FFAD6788 *arg3, Unk_9994C3F5 *arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 temp_r30;

    fn_8001075C((s32)lbl_8029317C);
    temp_r30 = fn_800771FC(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    fn_80010760();
    return temp_r30;
}
