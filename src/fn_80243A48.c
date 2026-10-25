// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80243A48-0x80243B14 (204B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern void* lbl_80305EAC;
extern s32 fn_801770D4(Unk_C7387A53 *);
extern s32 fn_801AF2F4(CStruct *, char *);
extern s32 fn_801F672C(void);
extern void fn_801F65F0(s32, s32);
extern void fn_8022E0D4(s32);
void fn_80243A48(Unk_FFAD6788 *arg0, s32 arg1, s32 arg2) {
    s32 handle;
    s32 *walker;
    s32 k;
    s32 ret;
    s32 *tbl;
    s32 *base;
    s32 off;
    s32 i;
    s32 n;

    arg1 *= 4;
    tbl = (s32 *)((char *)arg0 + 4);
    handle = *(s32 *)((char *)tbl + arg1);
    walker = (s32 *)((char *)handle + 0xC);
    for (k = 2; k != 0; k--) {
        register s32 v __asm__("r4");
        v = *walker++;
        if (v != 0) {
            fn_8022E0D4(**((s32 * *)&arg0->unk0x104));
        }
    }
    if (arg2 != 0) {
        ret = fn_801AF2F4(fn_801770D4((void *)lbl_80305EAC), handle + 0xC0);
        if (ret >= 0) {
            fn_801F65F0(fn_801F672C(), ret);
        }
    }
    base = (s32 *)((char *)arg0 + 4);
    {
        register s32 rp __asm__("r9");
        rp = (s32)base;
        i = 0;
        off = 0;
        for (n = 0x20; n != 0; n--) {
            if (*(s32 *)((char *)(off + rp)) == handle) {
                *(s32 *)((char *)(off + (s32)base)) = i;
            }
            off += 4;
        }
    }
    Mem_Free(handle);
}
