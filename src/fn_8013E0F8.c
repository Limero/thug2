// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013E0F8-0x8013E184 (140B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8029F480[];
s32 fn_8013E034(s32 arg0, void *arg1);
s32 fn_8013E068(s32 arg0, void *arg1);
void fn_8013E0F8(Unk_82779A3F *arg0) {
    s32 zPadA;
    s32 zPadB;
    s32 zPadC;
    s32 sp8;
    s32 var_r3;
    Unk_89391A04 *temp_r9;

    ((Unk_59AB5482 *)&sp8)->unk0x8 = (s32)lbl_8029F480;
    ((Unk_59AB5482 *)&sp8)->unk0x4 = NULL;
    var_r3 = fn_8013E034((s32)arg0, (void *)&sp8);
    if (var_r3 != 0) {
        do {
            temp_r9 = arg0->unk0x2300;
            ((s32 (*)(void *, void *))temp_r9->unk0x24)(
                (char *)arg0 + temp_r9->unk0x20, (void *)var_r3);
            {
                register void *pi __asm__("r4");
                pi = (void *)&sp8;
                var_r3 = fn_8013E068((s32)arg0, pi);
            }
        } while (var_r3 != 0);
    }
    ((Unk_59AB5482 *)&sp8)->unk0x8 = (s32)lbl_8029F480;
    __asm__("" : : "m"(zPadA), "m"(zPadB), "m"(zPadC));
}
