// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802438A4-0x80243924 (128B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void* lbl_80305EAC;
extern s32 fn_801A6B64(Unk_93C2DF4D *, s32);
extern void fn_801AEF74(void *);
extern void fn_801AF004(void *, s32, s32, s32);
void fn_802438A4(s32 arg0) {
    s32 ret;
    s32 *p;

    ret = fn_801A6B64(((Unk_C7387A53 *)lbl_80305EAC)->unk0x24, -1);
    if (ret != 0) {
        fn_801AEF74(ret);
        p = (s32 *)((char *)arg0 + 4);
        do {
            s32 v = *p++;
            if (v != 0) {
                fn_801AF004(ret, v + 0xC0, 0, ((Unk_FFAD6788 *)v)->unk0xE0);
            }
        } while ((s32)p <= (s32)arg0 + 0x80);
    }
}
