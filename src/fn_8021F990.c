// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021F990-0x8021FA48 (184B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_80137B4C(Unk_F386DC9F *);
void fn_80137B54(Unk_F386DC9F *, s32);
void fn_8021F964(CScript *);
void fn_8021FA48(CScript *, s32);
extern char lbl_80303448[];
extern char lbl_80305F9C[];
s32 Script_RunScript(s32, s32, s32, s32, s32);
void fn_8021F990(void) {
    Unk_F386DC9F *temp_r30;
    s32 temp_r3;
    CScript *temp_r31;

    temp_r30 = *(Unk_F386DC9F **)lbl_80303448;
    temp_r31 = *(CScript **)lbl_80305F9C;
    temp_r3 = fn_80137B4C(temp_r30);
    switch (temp_r3) {
    case 0:
    case 1:
        fn_8021F964(temp_r31);
        fn_8021FA48(temp_r31, 0);
        break;
    case 9:
        fn_8021F964(temp_r31);
        break;
    case 5:
        fn_8021F964(temp_r31);
        Script_RunScript(temp_r31->unk0x1F4, 0, 0, 0, 0);
        break;
    case 2:
        fn_80137B54(temp_r30, 6);
        break;
    }
}
