// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80217F08-0x8021805C (340B). Byte-identical.
// extra_cflags: -fno-gcse
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8021D990(void *);
s32 fn_80219698(CStruct *);
void GetElement_2(void *, s32, s32, s32);
void Script_RunScript(s32, s32, s32, s32, s32);
void CObject_RemoveRefLink(CStruct *, CStruct *);
void fn_8021FAB4(Unk_9994C3F5 *, s32, s32, char *, char *, s32, s32, s32, s32);
bool ScriptAllPlayersAreReady(s32, s32);
s32 fn_800145AC(void);
void fn_8021F120(void *);
void fn_80009C00(CStruct *);
extern bool lbl_80305FA8;
extern s32 lbl_80300434;
extern u32 lbl_803A3140;
extern char lbl_802AFD68[];

void fn_80217F08(Unk_C7387A53 *arg0) {
    struct {
        s32 a;
        s32 b;
        s32 c;
    } out;
    Unk_FFAD6788 *temp_r31;

    temp_r31 = arg0->unk0x20;
    if (fn_8021D990((void *)temp_r31) > 0) {
        if (fn_80219698(temp_r31) != 0) {
            temp_r31 = lbl_80305FA8;
            if (temp_r31 == 0) {
                GetElement_2(&out, lbl_80300434, QB_CURRENT_MENU_ANCHOR, 0);
                if (out.a == 0) {
                    Script_RunScript(QB_CREATEWAITFORPLAYERSDIALOG, 0, 0, 0, 0);
                    lbl_80305FA8 = 1;
                }
                __asm__("" ::: "memory");
                if (out.a != 0) {
                    CObject_RemoveRefLink((void *)out.a, &out);
                    out.a = temp_r31;
                }
            }
        } else if (lbl_80305FA8 == 0) {
            fn_8021FAB4((void *)temp_r31, 1, QB_NET_MESSAGE_GAME_WILL_START, 0, 0, 0, (s32)lbl_802AFD68, 0, 0x7D0);
            lbl_80305FA8 = 1;
        }
    } else {
        if ((ScriptAllPlayersAreReady(0, 0) != 0) && (fn_800145AC() >= lbl_803A3140)) {
            lbl_80305FA8 = 0;
            fn_8021F120((void *)temp_r31);
            fn_80009C00(temp_r31->unk0xF4);
        }
    }
}
