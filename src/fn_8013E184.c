// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013E184-0x8013E21C (152B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8029F480[];
s32 fn_8013E034(s32 arg0, void *arg1);
s32 fn_8013E068(s32 arg0, void *arg1);
void fn_8013F808(void *o, s32 v);
void fn_8013E0F8(void *arg0);
void fn_8013E184(s32 *arg0, s32 arg1) {
    s32 zPadA;
    s32 zPadB;
    s32 zPadC;
    s32 sp8;
    s32 var_r3;

    ((Unk_59AB5482 *)&sp8)->unk0x8 = (s32)lbl_8029F480;
    ((Unk_59AB5482 *)&sp8)->unk0x4 = NULL;
    if (arg1 == 0) {
        *arg0 += 1;
        var_r3 = fn_8013E034((s32)arg0, (void *)&sp8);
        if (var_r3 != 0) {
            do {
                register void *pi __asm__("r4");
                fn_8013F808((void *)var_r3, 1);
                pi = (void *)&sp8;
                var_r3 = fn_8013E068((s32)arg0, pi);
            } while (var_r3 != 0);
        }
    }
    fn_8013E0F8((void *)arg0);
    ((Unk_59AB5482 *)&sp8)->unk0x8 = (s32)lbl_8029F480;
    __asm__("" : : "m"(zPadA), "m"(zPadB), "m"(zPadC));
}
