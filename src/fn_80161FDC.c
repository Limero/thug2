// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80161FDC-0x8016207C (160B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void* lbl_80305EAC;
extern s32 lbl_80366474;
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_80174A58(void *, CStruct *);
s32 fn_8003AE20(Unk_31DE137E *);
s32 fn_8003EDE0(void);
s32 fn_8003EDE8(s32);
s32 fn_8005CB10(CStruct *, s32, s32, s32, s32, s32, s32, s32);

s32 ScriptLoadFaceTextureFromProfile(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r28;
    s32 temp_r29;
    s32 temp_r30;

    GetChecksum_2(pParams, QB_CHECKSUM, &sp8, 1);
    temp_r30 = fn_8003AE20(fn_80174A58(lbl_80305EAC, 0) + 4);
    temp_r28 = lbl_80366474;
    temp_r29 = fn_8003EDE0();
    return fn_8005CB10(temp_r28, temp_r29, fn_8003EDE8(temp_r30), sp8, 1, 1, 1, 1) ? 1 : 0;
}
