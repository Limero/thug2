// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F03D4-0x800F0454 (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-expensive-optimizations
// NOTE 2026-09-20: MSL prototypes use the repo's const/unsigned forms
// (`u32 strlen(const char *)`, `char *strcpy(char *, const char *)`); the
// promoted draft's `s32 strlen(char *)` tripped ngccc's builtin-declaration
// warning.  Same codegen (re-verified 32/32 words against the DOL), and the
// tail is a three-arg call: fn_800F03A0 takes fn_8000A778's result as arg0.
#include "types.h"
u32 strlen(const char *);
char *strcpy(char *, const char *);
s32 fn_8000A778(char *);
void fn_800F03A0(s32, s32, void *);
void fn_800F03D4(char *arg0, s32 arg1, void *arg2) {
    char buf[0x68];
    char *p = arg0;
    s32 len = strlen(arg0);

    if (len != 0 && arg0[len - 1] == '_') {
        strcpy(buf, arg0);
        buf[len - 1] = 0;
        p = buf;
    }
    fn_800F03A0(fn_8000A778(p), arg1, arg2);
}
