// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023DFB8-0x8023E09C (228B). Byte-identical.
// extra_cflags: -fno-gcse
#include "types.h"
#include "structs.h"
extern void fn_80245128(Unk_09BB4394 * arg0, CStruct * arg1, Unk_C7387A53 * arg2);
extern s32 fn_80237D14(s32 arg0, Unk_8C3FE072 * arg1, s32 arg2, Unk_4CED4D63 * arg3, void * arg4);
extern void fn_80243318(CStruct * arg0, s32 arg1);
extern void fn_80243320(s32 * arg0, s32 arg1);
extern s32 fn_8024336C(CStruct * arg0);
extern s32 fn_802432A0(Unk_9994C3F5 * arg0);
extern s32 fn_802416F8(void);
extern void fn_802424AC(Unk_C7387A53 * arg0, s32 arg1, s32 arg2);

void fn_8023DFB8(Unk_D329255D *arg0, Unk_C7387A53 *arg1) {
    struct { s32 unk0; u16 unk4; } sp10;
    volatile s32 sp8;
    char *p8;
    Unk_C7387A53 *var_r31;
    s32 temp_r3;

    if (arg0->unk0x74 == 5) {
        temp_r3 = arg0->unk0x64;
        if (temp_r3 != 0) {
            fn_80245128(temp_r3, arg0, arg1);
        }
    } else {
        sp10.unk0 = arg0->unk0x4;
        sp10.unk4 = arg0->unk0x8;
        fn_80243318(&sp8, fn_80237D14(arg0->unk0x0, &sp10, 0, 0, 0));
        p8 = (char *)&sp8;
        if (sp8 == 0) {
            fn_80243320((s32 *)p8, 2);
        } else {
            var_r31 = fn_8024336C(p8);
            while (var_r31 != NULL) {
                fn_802432A0(var_r31);
                fn_802424AC(fn_802416F8(), arg1, 0);
                var_r31 = var_r31->unk0xC;
            }
            fn_80243320(&sp8, 2);
        }
    }
}
