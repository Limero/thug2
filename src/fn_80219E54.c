// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80219E54-0x80219F9C (328B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802AFDD0[];
extern char lbl_802AFDD8[];
extern char lbl_802AFDE0[];
extern s32 Script_GenerateCRC(void *arg0);
extern s32 fn_8012591C(s32 arg0, s32 arg1);
extern void CStruct_new(s32 arg0);
extern s32 CStruct_ctor(void);
extern void AddComponent(CStruct * arg0, s32 arg1, s32 arg2, void *arg3);
extern s32 fn_80127E70(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 fn_8021E024(void * arg0);
extern void fn_801400C0(s32 arg0, s32 arg1, CStruct * arg2);

void fn_80219E54(void *arg0, s32 arg1) {
    struct {
        char pad0[0x20];
        s32 sp28;
        char pad2[0x18];
    } fr;

    s32 temp;
    register s32 temp_r5 __asm__("r5");
    s32 temp_r29;
    s32 temp_r30;
    register void *wp __asm__("r30");

    sprintf(&fr, (s32)lbl_802AFDD0, arg1);
    temp_r29 = Script_GenerateCRC(&fr);
    if (arg1 == 0) {
        temp = fn_8012591C(QB_NETMENU_STR_NO_OBSERVERS, 0);
        wp = &fr.sp28;
        sprintf(&fr.sp28, temp);
        arg1 = (s32)wp;
    } else if (arg1 == 1) {
        temp_r5 = fn_8012591C(QB_NETMENU_STR_OBSERVER, 0);
        wp = &fr.sp28;
        sprintf(&fr.sp28, (s32)lbl_802AFDE0, temp_r5);
        arg1 = (s32)wp;
    } else {
        temp = fn_8012591C(QB_NETMENU_STR_OBSERVERS, 0);
        wp = &fr.sp28;
        sprintf(wp, (s32)lbl_802AFDD8, arg1, temp);
        arg1 = (s32)wp;
    }
    CStruct_new(8);
    temp_r30 = CStruct_ctor();
    AddComponent(temp_r30, QB_UI_STRING, 3, (void *)arg1);
    fn_80127E70(temp_r30, QB_CHECKSUM, 0xD, temp_r29);
    fn_801400C0(fn_8021E024(arg0), QB_NUM_OBSERVERS, temp_r30);
}
