// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80122560-0x801225F8 (152B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern void *lbl_802FFE98;
void fn_8000F2F8(void *, void *);
void fn_8000F320(void *);
s32 MemAvailable(s32);
void fn_80010D94(void *, s32);
void fn_80010E78(void *);
void *Mem_Alloc(s32);

s32 fn_80122560(s32 arg0) {
    void *r;

    fn_8000F2F8(lbl_802FFE98, *(void **)((char *)lbl_802FFE98 + 0x118));
    if (MemAvailable(*(s32 *)((char *)*(void **)((char *)lbl_802FFE98 + 0x118) + 0x34)) < arg0) {
        fn_8000F320(lbl_802FFE98);
        fn_8000F2F8(lbl_802FFE98, *(void **)((char *)lbl_802FFE98 + 0x11C));
    }
    fn_80010D94(*(void **)((char *)lbl_802FFE98 + 0x11C), 0x20);
    r = Mem_Alloc(arg0);
    fn_80010E78(*(void **)((char *)lbl_802FFE98 + 0x11C));
    fn_8000F320(lbl_802FFE98);
    return (s32)r;
}
