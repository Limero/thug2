// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80222538-0x80222660 (296B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802A83F8[];
extern char lbl_802AFD94[];
extern char lbl_802AFDA0[];
extern s32 lbl_80305F9C;
extern s32 lbl_80305FF8;
void fn_80137CB4(Unk_9F066EC1 *);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_8021B55C(s32, s32);
s32 fn_802332B8(s32, s32);
void fn_8013DDE4(s32, s32, s32, void *, void *, s32, s32, s32);
s32 fn_801FC0E0(void);
s32 fn_801FA284(void);
void fn_8013DE78(void *, Unk_C71E6DE1 *);
bool ScriptFCFSRequestChangeLevel(CStruct *pParams, CScript *pScript) {
    struct {
        u8 msg[0x28];
        s32 sp30;
        s32 sp34;
    } fr;
    s32 mgr;
    s32 b55cret;

    
    mgr = lbl_80305F9C;
    fn_80137CB4(&fr.msg[0]);
    fr.sp30 = 0;
    GetChecksum_2(pParams, QB_LEVEL, &fr.sp30, 0);
    fr.sp34 = fr.sp30;
    b55cret = fn_8021B55C(mgr, 0);
    if (fr.sp30 == QB_LOAD_SK5ED_GAMEPLAY) {
        fn_8013DDE4(b55cret, 0x6C, 0x3A98, fn_802332B8(lbl_80305FF8, 0), (s32)lbl_802AFD94, 8, 1, 0);
        fn_801FC0E0();
        fn_801FC0E0();
        fn_8013DDE4(b55cret, 0x88, 0x1132, fn_801FA284(), (s32)lbl_802AFDA0, 8, 1, 0);
    }
    *(void **)&fr.msg[4] = &fr.sp34;
    *(u16 *)&fr.msg[2] = 4;
    fr.msg[0] = 0x62;
    *(s32 *)&fr.msg[0xC] = 2;
    fr.msg[0x10] = 8;
    fn_8013DE78(b55cret, &fr.msg[0]);
    return true;
}
