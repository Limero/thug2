// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80062D44-0x80062DBC (120B). Byte-identical.
// extra_cflags: -fno-strength-reduce
#include "types.h"
#include "structs.h"
void CObject_ctor(void);
void fn_80062BE8(Unk_FFAD6788 *);
extern char lbl_802940B8[];
extern char lbl_802940D0[];
extern char lbl_80294100[];
void *fn_80062D44(Unk_DCEB657B *arg0) {
    Unk_C8FEE62D *temp_r9;

    CObject_ctor();
    temp_r9 = (char *)arg0 + 0xC;
    temp_r9->unk0x14 = (s32)lbl_80294100;
    temp_r9->unk0x4 = arg0;
    temp_r9->unk0x8 = 0;
    temp_r9->unk0xC = temp_r9;
    temp_r9->unk0x10 = temp_r9;
    arg0->unk0x20 = (s32)lbl_802940B8;
    arg0->unk0x8 = (s32)lbl_802940D0;
    arg0->unk0x128 = 0;
    fn_80062BE8(arg0);
    return arg0;
}
