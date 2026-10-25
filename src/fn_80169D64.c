// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80169D64-0x80169E00 (156B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_80290B50[];
extern s32 BannerCheck(s32 arg0);
extern s32 fn_80015A58(void *arg0, void *arg1, void *arg2);
extern void fn_800158D8(void);
s32 ScriptCardIsDamaged(CStruct *pParams, CScript *pScript) {
    struct { s32 a; s32 b; s32 c; s32 d; } fr;
    s32 *wp1;
    s32 *wp2;
    s32 lblv;
    s32 temp_r0;
    s32 scopy;
    s32 temp_r30;
    CStruct *temp_r3;

    wp1 = (s32 *)&fr;
    lblv = (s32)lbl_80290B50;
    wp1[3] = lblv;
    temp_r0 = BannerCheck(0);
    scopy = temp_r0;
    wp2 = (s32 *)&fr.b;
    wp2[1] = scopy;
    temp_r3 = (void *)fn_80015A58((void *)temp_r0, (void *)0, (void *)0);
    if (temp_r3 != NULL) {
        temp_r30 = temp_r3->unk0x10;
        wp1[3] = lblv;
        fn_800158D8();
        return temp_r30;
    }
    if (((Unk_C7387A53 *)((CStruct *)wp2)->unk0x4)->unk0x24 != 0) {
        wp1[3] = lblv;
        fn_800158D8();
        return 1;
    }
    wp1[3] = lblv;
    fn_800158D8();
    return 0;
}
