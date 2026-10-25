// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020A384-0x8020A604 (640B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern char lbl_802AF370[];
extern s32 fn_801259C8(s32 arg0, s32 arg1);
extern s32 fn_80129528(CStruct * arg0, s32 arg1);
extern s32 GetStructure(s32 arg0, s32 arg1);
extern s32 GetArray(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern s32 GetString(CStruct * arg0, s32 * arg1, s32 * arg2, s32 arg3);
extern s32 GetChecksum_2(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern s32 GetStructure_2(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern s32 GetChecksum(CStruct * arg0, s32 arg1);
extern s32 fn_8012935C(Unk_F8A5095F * arg0, s32 arg1);
extern s32 Script_GenerateCRC(void *arg0);
extern void fn_801F0E84(CScript * arg0);
extern void fn_8009F204(Unk_C8FEE62D * arg0, void * arg1, Unk_C8FEE62D * arg2);
extern void fn_801309EC(Unk_DB0E2BAB * arg0);
extern void fn_8020C500(Unk_90685748 * arg0);

typedef struct {
    char buf[0x68];
    s32 v70;
    s32 v74;
    s32 v78;
    s32 v7C;
    s32 v80;
    s32 v84;
} A384_Frame;

bool fn_8020A384(Unk_C3FDC979 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    A384_Frame fr;
    s32 zero;
    void *a70;
    void *a78;
    void *a74;
    s32 temp_r3;
    s32 entry28;
    s32 entry2;
    s32 c74;
    s32 mask;
    s32 result;
    Unk_C8FEE62D *objptr;
    s32 pmsg;

    if (arg0->unk0x12F4 == 0) {
        goto L_fail;
    }
    zero = 0;
    arg0->unk0x12F4 = zero;
    temp_r3 = fn_801259C8(arg0->unk0x12F8, 0);
    if (temp_r3 == 0) {
        goto L_fail;
    }
    a70 = &fr.v70;
    a78 = &fr.v78;
    a74 = &fr.v74;
    GetArray((entry28 = fn_80129528(temp_r3, arg0->unk0x12FC)), QB_SCRIPTS, a70, (fr.v70 = zero, 0));
    fr.v74 = zero;
    GetArray(entry28, QB_TEMPLATE, a74, 0);
    fr.v78 = zero;
    GetString(entry28, QB_PREFIX, a78, 0);
    if (fr.v70 == 0) {
        c74 = fr.v74;
        if (c74 == 0) {
            fr.v7C = c74;
            GetChecksum_2(entry28, (s32)QB_TRICKSLOT, &fr.v7C, 0);
            if (fr.v7C != 0) {
                fr.v80 = c74;
                GetChecksum_2(arg0->unk0xA6C, fr.v7C, &fr.v80, 0);
                if (fr.v80 != 0) {
                    entry2 = GetStructure(fr.v80, 0);
                    if (entry2 != 0) {
                        GetArray(entry2, QB_SCRIPTS, a70, 0);
                        GetArray(entry2, QB_TEMPLATE, a74, 0);
                        GetString(entry2, QB_PREFIX, a78, 0);
                    }
                }
            }
        }
    }
    mask = 0;
    if (arg1 != 0) {
        mask |= 1;
    }
    if (arg2 != 0) {
        mask |= 2;
    }
    if (arg3 != 0) {
        mask |= 4;
    }
    if (arg4 != 0) {
        mask |= 8;
    }
    if (fr.v70 != 0) {
        result = GetChecksum(fr.v70, mask);
    } else {
        pmsg = fn_8012935C(fr.v74, mask);
        sprintf(&fr.buf[0], (s32)lbl_802AF370, fr.v78, pmsg);
        result = Script_GenerateCRC(&fr.buf[0]);
    }
    fr.v84 = 0;
    GetStructure_2(entry28, QB_PARAMS, &fr.v84, 0);
    objptr = arg0->unk0xC;
    if (objptr->unk0x1C == (s32)QB_OBJECT_TYPE_SKATER) {
        *(s32 *)(arg0->unk0x2C + (s32)0x428) = 0;
    }
    arg0->unk0xA68 = arg0->unk0x1308;
    fn_801F0E84(arg0->unk0x30);
    fn_8009F204(objptr, result, fr.v84);
    fn_801309EC(objptr->unk0x14);
    *(s32 *)(arg0->unk0x34 + (s32)0x144) = 1;
    fn_8020C500(arg0);
    return true;
L_fail:
    return false;
}
