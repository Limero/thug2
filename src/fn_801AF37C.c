// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801AF37C-0x801AF434 (184B). Byte-identical.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
extern s32 strcmp(char *, char *);
extern char *fn_801AED74(s32);
extern void fn_801AEDBC(__ps_t *, __ps_t *, __ps_t *);
void fn_801AF37C(CStruct *arg0, char *arg1, void *arg2, void *arg3) {
    __ps_t sp8[2];
    __ps_t sp18[2];
    register s32 walk_r9 __asm__("r9");
    register __ps_t *outp __asm__("r30");
    register void *a2 __asm__("r29");
    register void *a3 __asm__("r28");
    Unk_C7387A53 *var_r31;

    walk_r9 = arg0->unk0x10;
    a2 = arg2;
    __asm__ volatile("" : "+r"(a2));
    a3 = arg3;
    __asm__ volatile("" : "+r"(a3));
    if (((CStruct *)walk_r9)->unk0x4 == -1) {
        walk_r9 = NULL;
    }
    var_r31 = walk_r9;
    if (var_r31 != NULL) {
        outp = (__ps_t *)&sp8[0];
    loop:
        if (strcmp(fn_801AED74(var_r31), arg1) == 0) {
            sp8[0] = ((Unk_EA529D06 *)a2)->unk0x0;
            outp[1] = ((Unk_EA529D06 *)a2)->unk0x8;
            sp18[1] = ((Unk_EA529D06 *)a3)->unk0x8;
            sp18[0] = ((Unk_EA529D06 *)a3)->unk0x0;
            fn_801AEDBC((__ps_t *)var_r31, outp, (__ps_t *)&sp18[0]);
            goto exit;
        }
        walk_r9 = var_r31->unk0xC;
        if (((CStruct *)walk_r9)->unk0x4 == -1) {
            walk_r9 = NULL;
        }
        var_r31 = walk_r9;
        if (var_r31 != NULL) {
            goto loop;
        }
    }
exit:;
}
