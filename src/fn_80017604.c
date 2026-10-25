// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80017604-0x8001768C (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern f32 lbl_80290CA0;
extern char lbl_8031E664[];
extern char lbl_8031E670[];
extern char lbl_8031E67C[];
void *fn_8001D440(CStruct *, f32, f32, f32);
void fn_80017604(s32 arg0, s32 arg1) {
    register f32 a __asm__("fr1");
    f32 b, c;
    if ((arg1 == 0xFFFF) && (arg0 != 0)) {
        a = lbl_80290CA0; b = a; c = b;
        fn_8001D440((CStruct *)lbl_8031E664, a, b, c);
        a = lbl_80290CA0; b = a; c = b;
        fn_8001D440((CStruct *)lbl_8031E670, a, b, c);
        a = lbl_80290CA0; b = a; c = b;
        fn_8001D440((CStruct *)lbl_8031E67C, a, b, c);
    }
}
