// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802361E8-0x80236260 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_80239FAC(void *, void *, s32);
void fn_8023FC44(void *);
s32 fn_80230BEC(s32);
s32 fn_80233404(void);
void fn_80230C54(void);
extern char lbl_8029FBE8[];
s32 fn_802361E8(Unk_7BAE36EB *arg0, void *arg1, s32 arg2) {
    char buf[112];
    s32 r;
    register s32 d __asm__("r3");
    fn_80239FAC(arg0, arg1, 0);
    d = 1;
    if (arg2 != 0) {
        register s32 pp __asm__("r28");
        pp = (s32)buf;
        __asm__("" : "+r"(pp));
        fn_8023FC44(buf);
        (*(s32 *)((char *)pp + 12)) = (s32)lbl_8029FBE8;
        { register s32 t __asm__("r0"); t = fn_80230BEC(0); *(volatile s32 *)&buf[8] = t; }
        { register s32 q __asm__("r29"); q = fn_80233404() ^ 1; r = q; }
        __asm__ __volatile__("" ::: "memory");
        (*(s32 *)((char *)pp + 12)) = (s32)lbl_8029FBE8;
        fn_80230C54();
        return r;
    }
    return d;
}
