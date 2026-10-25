// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022A510-0x8022A848 (824B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 CStruct_new(s32);
extern s32 CStruct_ctor(s32);
extern s32 NextNewPlayerInfo(s32);
extern s32 fn_8022986C(CScript *);
extern s32 fn_80141FA4(Unk_5FCDF30E *);
extern void AddChecksum(CStruct *, s32, s32);
extern s32 Script_RunScript(s32, s32, s32, s32, s32);
extern void CStruct_delete(CStruct *, s32);
extern s32 fn_8009CF2C(CStruct *);
extern s32 fn_8021D358(s32, s32);
extern s32 fn_8014510C(Unk_EE36B018 *);
extern s32 AddString(CStruct *, s32, void *);
extern s32 fn_802203E4(Unk_C7387A53 *);
extern s32 fn_801AAC74(Unk_361D6392 *, s32);
extern s32 lbl_80305F9C;
extern s32 fn_80198F7C(s32);
extern s32 lbl_80305EC0;

void fn_8022A510(void *arg0, s32 arg1) {
    s32 flag9;
    s32 temp_r3;
    register s32 temp_r29 __asm__("r29");
    register s32 temp_r30 __asm__("r30");
    s32 temp_r31;
    s32 h;
    s32 strv;
    void *var_r3;

    temp_r29 = lbl_80305F9C;
    temp_r30 = (s32)arg0;
    if (arg1 != 0) {
        temp_r3 = NextNewPlayerInfo(temp_r29);
        if (temp_r3 != 0) {
            fn_8022A510((void *)temp_r3, 0);
        }
        flag9 = 1;
        __asm__("" : "+r"(flag9));
        if ((((CScript *)temp_r30)->unk0x1D8 & 0x80) == 0) {
            flag9 = 0;
        }
        if (flag9 == 0) {
            ((CScript *)temp_r30)->unk0x1D8 |= 0x80;
            if (fn_8022986C((void *)temp_r30) != 0) {
                temp_r31 = CStruct_ctor(CStruct_new(8));
                if (fn_80141FA4(((CScript *)temp_r30)->unk0x18) == 0) {
                    AddChecksum(temp_r31, QB_PLAYER_1, QB_PLAYER_1);
                } else {
                    AddChecksum(temp_r31, QB_PLAYER_2, QB_PLAYER_2);
                }
                Script_RunScript(QB_HIDE_CROWN_ARROW, temp_r31, 0, 0, 0);
                if (temp_r31 != 0) {
                    CStruct_delete(temp_r31, 3);
                }
                Script_RunScript(QB_NEWKINGYOU, 0, 0, 0, 0);
            } else {
                AddChecksum((h = CStruct_ctor(CStruct_new(8))), QB_PLAYER_1, QB_PLAYER_1);
                {
                    register s32 a3 __asm__("r3");
                    register s32 a4 __asm__("r4");
                    register s32 a5 __asm__("r5");
                    register s32 a6 __asm__("r6");
                    register s32 a7 __asm__("r7");
                    __asm__ volatile("lis %0,0x1dfd" : "=r"(a3));
                    a6 = 0;
                    a7 = 0;
                    __asm__ volatile("ori %0,%0,0x5982" : "+r"(a3));
                    a4 = h;
                    a5 = 0;
                    Script_RunScript(a3, a4, a5, a6, a7);
                }
                {
                    register s32 a3 __asm__("r3");
                    register s32 a4 __asm__("r4");
                    register s32 a5 __asm__("r5");
                    __asm__ volatile("lis %0,-0x5b50" : "=r"(a4));
                    a3 = h;
                    __asm__ volatile("ori %0,%0,0x8520" : "+r"(a4));
                    a5 = temp_r30 + 0x3C;
                    AddString(a3, a4, a5);
                }
                Script_RunScript(QB_NEWKINGOTHER, h, 0, 0, 0);
                if (h != 0) {
                    CStruct_delete(h, 3);
                }
            }
            if (fn_8009CF2C(temp_r29) == 0) {
                if (fn_8021D358(temp_r29, (((CScript *)((CScript *)temp_r30)->unk0x18)->unk0x18 == 0)) != 0) {
                    register s32 a3 __asm__("r3");
                    register s32 a4 __asm__("r4");
                    s32 pv;
                    temp_r31 = CStruct_ctor(CStruct_new(8));
                    pv = fn_8014510C(((CScript *)temp_r30)->unk0x18);
                    __asm__ volatile("lis %0,-0x5b50" : "=r"(a4));
                    a3 = temp_r31;
                    __asm__ volatile("ori %0,%0,0x8520" : "+r"(a4));
                    AddString(a3, a4, pv);
                    Script_RunScript(QB_NEWKINGOTHER, temp_r31, 0, 0, 0);
                    if (temp_r31 != 0) {
                        CStruct_delete(temp_r31, 3);
                    }
                }
            }
            ((CScript *)temp_r30)->unk0x1D8 |= 0x80;
        }
        var_r3 = fn_802203E4(temp_r29);
        if (var_r3 != NULL) {
            return (void *)fn_801AAC74((s32)var_r3, ((CScript *)temp_r30)->unk0x18);
        }
        return var_r3;
    } else {
        flag9 = 1;
        __asm__("" : "+r"(flag9));
        if ((((CScript *)temp_r30)->unk0x1D8 & 0x80) == 0) {
            flag9 = 0;
        }
        if (flag9 != 0) {
            __asm__ volatile("" ::: "r3");
            if (fn_8022986C((void *)temp_r30) != 0) {
                if ((fn_80198F7C(lbl_80305EC0) == QB_NETKING) || (fn_80198F7C(lbl_80305EC0) == QB_KING)) {
                    AddChecksum((h = CStruct_ctor(CStruct_new(8))), QB_PLAYER_1, QB_PLAYER_1);
                    AddChecksum(h, QB_PLAYER_2, QB_PLAYER_2);
                    Script_RunScript(QB_SHOW_CROWN_ARROW, h, 0, 0, 0);
                    if (h != 0) {
                        CStruct_delete(h, 3);
                    }
                }
            }
            ((CScript *)temp_r30)->unk0x1D8 &= QB_UNKNOWN_0xFFFFFF7F;
        }
        return;
    }
}
