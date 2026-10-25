// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80222898-0x80222930 (152B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305F9C[];
s32 fn_80137CB4(Unk_9F066EC1 * arg0);
s32 GetChecksum_2(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
s32 fn_8021B55C(void *arg0, s32 arg1);
s32 fn_8013DE78(void * arg0, Unk_C71E6DE1 * arg1);

bool ScriptFCFSRequestToggleGoalSelection(CStruct *pParams, CScript *pScript) {
    struct {
        u8 blk[0x28];
        s32 sp30;
        s32 pw;
    } fr;
    s32 mgr;
    s32 ret;

    mgr = *(s32 *)&lbl_80305F9C;
    fn_80137CB4(&fr.blk);
    GetChecksum_2((void *)pParams, QB_NAME, &fr.sp30, 1);
    ret = fn_8021B55C((void *)mgr, 0);
    fr.pw = fr.sp30;
    *(s32 *)((char *)fr.blk + 4) = (s32)&fr.pw;
    *(u16 *)((char *)fr.blk + 2) = 4;
    *(u8 *)((char *)fr.blk + 0) = 0x64;
    *(s32 *)((char *)fr.blk + 0xC) = 2;
    *(u8 *)((char *)fr.blk + 0x10) = 8;
    fn_8013DE78(ret, &fr.blk);
    return true;
}
