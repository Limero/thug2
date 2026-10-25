// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022755C-0x80227794 (568B). Byte-identical.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802A83F8[];
extern char lbl_802B0130[];
extern s32 lbl_80305EC0;
extern s32 fn_8021D358(s32, u16);
extern s32 CStruct_new(s32);
extern s32 CStruct_ctor(s32);
extern s32 fn_8022986C(CScript *);
extern s32 fn_80198B10(s32);
extern s32 fn_801258E8(void *, s32);
extern void AddComponent(CStruct *, s32, s32, void *);
extern s32 Script_RunScript(s32, s32, s32, s32, s32);
extern void CStruct_delete(CStruct *, s32);
extern s32 fn_8021D454(s32, CStruct *, s32);
extern s32 fn_8021D4E8(s32, CStruct *, s32);
extern s32 fn_80198B68(s32);
bool fn_8022755C(CScript *arg0) {
    struct {
        s32 o0;
        s32 o4;
        s32 o8;
        u8 padA[4];
        char msg[0x40];
    } fr;
    register s32 *wp __asm__("r9");
    register s32 *wpsave __asm__("r26");
    s32 temp_r27;
    Unk_1D62F22E *temp_r28;
    Unk_C7387A53 *temp_r29;
    s32 temp_r31;
    Unk_C7387A53 *var_r3;
    s32 found;
    s32 count;
    s32 var_zero = 0;

    temp_r28 = *(void **)arg0;
    wp = &fr.o0;
    temp_r27 = *((void * *)&arg0->unk0x18);
    wp[2] = (s32)lbl_802A83F8;
    __asm__("" : "+r"(wp));
    __asm__ volatile("mr %0,%1" : "=r"(wpsave) : "r"(wp));
    __asm__("" : "+r"(wp));
    wp[1] = var_zero;
    __asm__ volatile("" ::: "memory");
    {
        register s32 stage3 __asm__("r3");
        __asm__ volatile("mr %0,%1" : "=r"(stage3) : "r"(temp_r27));
        if ((temp_r29 = (void *)fn_8021D358(stage3, (u16)(s8)*(u8 *)temp_r28)) != NULL) {
            temp_r29->unk0x34 = (s32)(s8)temp_r28->unk0x1;
            sprintf((void *)&fr.msg, (s32)lbl_802B0130, (s8)temp_r28->unk0x1 + 1);
            temp_r31 = (void *)CStruct_ctor(CStruct_new(8));
            if (fn_8022986C(temp_r29) != 0) {
                if (fn_80198B10(lbl_80305EC0) != 0) {
                    AddComponent((s32)temp_r31, QB_STRING0, 3, fn_801258E8((void *)&fr.msg, 0));
                    Script_RunScript(QB_JOINED_TEAM_YOU, temp_r31, 0, 0, 0);
                }
            } else {
                if (fn_80198B10(lbl_80305EC0) != 0) {
                    AddComponent((s32)temp_r31, QB_STRING0, 3, (char *)temp_r29 + 0x3C);
                    AddComponent((s32)temp_r31, QB_STRING1, 3, fn_801258E8((void *)&fr.msg, 0));
                    Script_RunScript(QB_JOINED_TEAM_OTHER, temp_r31, 0, 0, 0);
                }
            }
            if ((s32)temp_r31 != 0) {
                CStruct_delete((s32)temp_r31, 3);
            }
            found = 1;
            var_r3 = (void *)fn_8021D454((s32)temp_r27, (void *)&fr.o0, 0);
            count = 0;
            if ((s32)var_r3 != 0) {
                do {
                    if ((s32)var_r3 != (s32)temp_r29) {
                        count += 1;
                        if ((s8)temp_r28->unk0x1 != var_r3->unk0x34) {
                            found = 0;
                        }
                    }
                    var_r3 = (void *)fn_8021D4E8((s32)temp_r27, (void *)&fr.o0, 0);
                } while ((s32)var_r3 != 0);
            }
            if (found != 0) {
                if ((s32)count > 0) {
                    if (fn_80198B68(lbl_80305EC0) > 0) {
                        Script_RunScript(QB_WARN_ALL_SAME_TEAM, 0, 0, 0, 0);
                    }
                }
            }
        }
    }
    wpsave[2] = (s32)lbl_802A83F8;
    return true;
}
