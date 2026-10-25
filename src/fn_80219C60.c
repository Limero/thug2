// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80219C60-0x80219D34 (212B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802AFDD0[];
extern char lbl_802AFDD8[];
extern s32 Script_GenerateCRC(void *arg0);
extern s32 fn_8012591C(s32 arg0, s32 arg1);
extern void CStruct_new(s32 arg0);
extern s32 CStruct_ctor(void);
extern void AddComponent(CStruct * arg0, s32 arg1, s32 arg2, void *arg3);
extern s32 fn_80127E70(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 fn_8021E024(void * arg0);
extern void fn_801400C0(s32 arg0, s32 arg1, CStruct * arg2);

void fn_80219C60(void *arg0, s32 arg1) {
    struct {
        char pad0[0x20];
        s32 sp28;
        char pad2[0x18];
    } fr;

    s32 temp_r28;
    s32 temp_r30;

    sprintf(&fr, (s32)lbl_802AFDD0, arg1);
    temp_r28 = Script_GenerateCRC(&fr);
    sprintf(&fr.sp28, (s32)lbl_802AFDD8, arg1, fn_8012591C(QB_NETMENU_STR_PLAYERS, 0));
    CStruct_new(8);
    temp_r30 = CStruct_ctor();
    AddComponent(temp_r30, QB_UI_STRING, 3, &fr.sp28);
    fn_80127E70(temp_r30, QB_CHECKSUM, 0xD, temp_r28);
    fn_801400C0(fn_8021E024(arg0), QB_NUM_PLAYERS, temp_r30);
}
