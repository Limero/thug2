// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021B37C-0x8021B3E0 (100B). Byte-identical.
#include "types.h"
#include "structs.h"
// MATCHED: byte-exact vs DOL (relocation-masked compile compare).
extern char lbl_80303448[];
void fn_801371D4(Unk_F386DC9F * arg0, Unk_82779A3F * arg1);
s32 fn_80009C00(CStruct * arg0);

s32 fn_8021B37C(Unk_C5BAE83F *arg0) {
    s32 var_r3;

    var_r3 = *(s32 *)&lbl_80303448;
    if ((s32)arg0->unk0x8 != 0) {
        fn_801371D4((void *)var_r3, arg0->unk0x8);
        fn_80009C00((void *)arg0->unk0xD8);
        var_r3 = fn_80009C00((void *)arg0->unk0xF4);
        arg0->unk0x8 = 0;
    }
    arg0->unk0x4 &= ~1;
    return var_r3;
}
