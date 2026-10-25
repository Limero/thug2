// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80227D64-0x80227EBC (344B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_802A83F8[];
extern s32 lbl_80305EC0;
extern s32 fn_8021F6CC(Unk_2EC243AC *);
extern s32 Game_GetGoalManager();
extern s32 GoalManager_GetGoal(s32, s32, s32);
extern s32 fn_80198B10(s32);
extern s32 fn_8021D2C4(s32, s32);
extern s32 fn_80137CB4(Unk_9F066EC1 *);
extern s32 fn_8021D454(s32, CStruct *, s32);
extern s32 fn_8021D4E8(s32, CStruct *, s32);
extern s32 fn_8022A9B8(Unk_31DE137E *);
extern void fn_8013CC84(void *, s32, Unk_C71E6DE1 *);
s32 fn_80227D64(void *arg0) {
    struct {
        s32 o0;
        s32 o4;
        s32 o8;
        u8 padX[4];
        u8 msgCmd;
        u8 padA;
        s16 msgLen;
        void *msgPtr;
        u8 padB[0x20];
        u8 subB;
        u8 padC[3];
        s32 subV;
    } fr;
    Unk_C8FEE62D *a0;
    register void *temp_r29 __asm__("r29");
    register void *sp18p __asm__("r26");
    register void *q3 __asm__("r3");
    void *temp_r28;
    CScript *temp_r31;
    Unk_C7387A53 *var_r3;
    s32 var_byte;
    s32 var_chk;

    a0 = arg0;
    temp_r28 = *((void * *)&a0->unk0x18);
    temp_r29 = *(void **)a0;
    var_chk = fn_8021F6CC((s32)temp_r28);
    if (*(u8 *)temp_r29 != var_chk) {
        return 4;
    }
    if (GoalManager_GetGoal(Game_GetGoalManager(), ((CStruct *)temp_r29)->unk0x4, 1) != 0) {
        if (fn_80198B10(lbl_80305EC0) != 0) {
            temp_r31 = (void *)fn_8021D2C4((s32)temp_r28, a0->unk0x10);
            if (temp_r31->unk0x18 != 0) {
                register s32 *wp __asm__("r30");
                s32 *wp2;
                char *subp;
                wp = &fr.o0;
                q3 = &fr.msgCmd;
                sp18p = q3;
                wp[2] = (s32)lbl_802A83F8;
                wp[1] = 0;
                fn_80137CB4(sp18p);
                subp = &fr.subB;
                ((Unk_4C649A8C *)subp)->unk0x4 = ((CStruct *)temp_r29)->unk0x4;
                var_byte = *(s32 *)((char *)*((s32 * *)&temp_r31->unk0x18) + 0x18);
                fr.msgPtr = subp;
                fr.subB = (u8)var_byte;
                fr.msgLen = 8;
                fr.msgCmd = 0x6F;
                var_r3 = (void *)fn_8021D454((s32)temp_r28, wp, 0);
                wp2 = (s32 *)&fr.o0;
                if ((s32)var_r3 != 0) {
                    do {
                        if (((s32)temp_r31 != (s32)var_r3) && (temp_r31->unk0x34 == var_r3->unk0x34)) {
                            wp = *((s32 * *)&a0->unk0xC);
                            fn_8013CC84((s32)wp, fn_8022A9B8((s32)var_r3), sp18p);
                        }
                        var_r3 = (void *)fn_8021D4E8((s32)temp_r28, (void *)&fr.o0, 0);
                    } while ((s32)var_r3 != 0);
                }
                wp2[2] = (s32)lbl_802A83F8;
            }
        }
    }
    return 1;
}
